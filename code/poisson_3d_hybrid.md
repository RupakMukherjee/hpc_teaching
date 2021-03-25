```fortran
Program poisson3d

use omp_lib

use, intrinsic :: iso_c_binding

implicit none

include 'mpif.h'


integer (C_INTPTR_T), parameter :: Nx = 3

integer (C_INTPTR_T), parameter :: Ny = 3

integer (C_INTPTR_T), parameter :: Nz = 3

integer (C_INTPTR_T), parameter :: Nh = ( Nx / 2 ) + 1

real ( kind = 8 ), parameter :: pi=3.14159265358979323846d0


include "fftw3-mpi.f03"


integer(C_INTPTR_T) :: i,j,k

real(C_DOUBLE) :: Lx,Ly,Lz,dx,dy,dz,kx,ky,kz

real(C_DOUBLE) :: x(Nx),y(Ny),z(Nz)

real(C_DOUBLE), dimension(Nx,Ny,Nz) :: phi,phi_dum,rho,rho_dum

complex(C_DOUBLE_COMPLEX), dimension(Nh,Ny,Nz) :: rhok,rhok_dum,phik,phik_dum

real ( kind = 8 ) :: sum,tmp

integer :: ierr, myid, nproc, seed, root

INTEGER ( kind = 4 ) thread_num,num_thread,thread_id,proc_num,iret

type(C_PTR) :: planf, planb, cdatar, cdatac

integer(C_INTPTR_T) :: alloc_local, local_Nz, local_k_offset

real(C_DOUBLE), pointer :: idata(:,:,:),idata2(:,:,:)

complex(C_DOUBLE_complex), pointer :: odata(:,:,:),odata2(:,:,:)


open(unit=10,file='poisson.dat',status='unknown')

  proc_num = omp_get_num_procs()

  thread_num = proc_num

  call omp_set_num_threads (thread_num)

  call mpi_init(ierr)

  call MPI_COMM_SIZE(MPI_COMM_WORLD, nproc, ierr)

  call MPI_COMM_RANK(MPI_COMM_WORLD, myid, ierr)


root = 0

sum = 0.0d0


Lx = 2.0*pi

Ly = 2.0*pi

Lz = 2.0*pi

dx = Lx/float(Nx)

dy = Ly/float(Ny)

dz = Ly/float(Nz)


do i = 1, Nx

x(i)=dfloat(i-1)*dx

  do j = 1, Ny

  y(j)=dfloat(j-1)*dy

    do k = 1, Nz

      z(k)=dfloat(k-1)*dz

      rho(i,j,k) = dfloat(i+j+k)!3.0d0*sin(x(i))*cos(y(j))*sin(z(k))

      rho_dum(i,j,k) = rho(i,j,k)

    enddo

  end do

end do


  call fftw_mpi_init()

  

  ! get local data size and allocate (note dimension reversal)

  alloc_local = fftw_mpi_local_size_3d(Nz, Ny, Nh, MPI_COMM_WORLD, &

                                            local_Nz, local_k_offset)

  cdatar = fftw_alloc_real(2 * alloc_local)

  cdatac = fftw_alloc_complex(alloc_local)

  

  call c_f_pointer(cdatar, idata, [2*Nh,Ny,local_Nz])

  call c_f_pointer(cdatar, idata2, [2*Nh,Ny,local_Nz])

  call c_f_pointer(cdatac, odata, [Nh,Ny,local_Nz])

  call c_f_pointer(cdatac, odata2, [Nh,Ny,local_Nz])


  ! create MPI plan for out-of-place DFT (note dimension reversal)

  planf = fftw_mpi_plan_dft_r2c_3d(Nz, Ny, Nx, idata, odata, MPI_COMM_WORLD, &

                                                                FFTW_MEASURE)

  planb = fftw_mpi_plan_dft_c2r_3d(Nz, Ny, Nx, odata, idata, MPI_COMM_WORLD, &

                                                                 FFTW_MEASURE)

                                                                 

  !np = Nz/local_Nz                                                               

  

  ! initialize data to some function my_function(i,j,k) = idata(i,j,k)

  call MPI_Barrier(MPI_COMM_WORLD, ierr)


!$OMP PARALLEL SHARED (idata, rho_dum, local_Nz, local_k_offset, myid) PRIVATE (i,j,k)

!$OMP DO

  do i = 1, Nx

    do j = 1, Ny

      do k = 1, local_Nz

      idata(i, j, k) = rho_dum(i, j, k + local_k_offset)

      end do

    end do

  end do

!$OMP END PARALLEL
  
  ! compute transform (as many times as desired)

  call MPI_Barrier(MPI_COMM_WORLD, ierr)


  call dfftw_init_threads(iret)
  call dfftw_plan_with_nthreads(thread_num)
  call fftw_mpi_execute_dft_r2c(planf, idata, odata)


  call MPI_Barrier(MPI_COMM_WORLD, ierr)


  ! COPY TO OUTPUT ARRAY

!$OMP PARALLEL SHARED (odata, rhok, local_Nz) PRIVATE (i,j,k)

!$OMP DO

  do i = 1, Nh

    do j = 1, Ny

      do k = 1, local_Nz

      rhok(i,j,k) = odata(i,j,k)

      end do

    end do

  end do

!$OMP END PARALLEL

  call MPI_Barrier(MPI_COMM_WORLD, ierr)

!$OMP PARALLEL SHARED (rhok, phik, phik_dum, local_Nz, local_k_offset, myid) PRIVATE (i,j,k,thread_id)

thread_id = omp_get_thread_num()

!write(*,*) myid, thread_id

!$OMP DO

do i = 1,Nh

  do j = 1,Ny/2

    do k = 1,local_Nz

      kx = 2.0d0*pi*float(i-1)/Lx

      ky = 2.0d0*pi*float(j-1)/Ly

      kz = 2.0d0*pi*float(k+local_k_offset-1)/Lz

        if (kx .eq. 0.0d0 .and. ky .eq. 0.0d0 .and. kz .eq. 0.0d0) then

        phik(i,j,k) = 2.0d0 * rhok(i,j,k) !(0.0d0,0.0d0)

        elseif (k+local_k_offset-1 <= Nz/2) then

        kz = 2.0d0*pi*float(k+local_k_offset-1)/Lz

        phik(i,j,k) = 2.0d0 * rhok(i,j,k)!/( kx*kx + ky*ky + kz*kz) 

        else 

        kz = 2.0d0*pi*float(k+local_k_offset-1-Nz)/Lz

        phik(i,j,k) = 2.0d0 * rhok(i,j,k)!/( kx*kx + ky*ky + kz*kz) 

        endif

      phik_dum(i,j,k) = phik(i,j,k)

    enddo  

  enddo

  do j = Ny/2+1,Ny

    do k = 1,local_Nz

      kx = 2.0d0*pi*float(i-1)/Lx

      ky = 2.0d0*pi*float((j-1)-Ny)/Ly

      kz = 2.0d0*pi*float(k+local_k_offset-1)/Lz

        if (k+local_k_offset-1 <= Nz/2) then

        kz = 2.0d0*pi*float(k+local_k_offset-1)/Lz

        phik(i,j,k) = 2.0d0 * rhok(i,j,k)!/( kx*kx + ky*ky + kz*kz) 

        else 

        kz = 2.0d0*pi*float(k+local_k_offset-1-Nz)/Lz

        phik(i,j,k) = 2.0d0 * rhok(i,j,k)!/( kx*kx + ky*ky + kz*kz) 

        endif

      phik_dum(i,j,k) = phik(i,j,k)

    enddo  

  enddo

enddo

!$OMP END PARALLEL


  call MPI_Barrier(MPI_COMM_WORLD, ierr)


!$OMP PARALLEL SHARED (odata2, phik_dum, local_Nz) PRIVATE (i,j,k)

!$OMP DO
  
  do i = 1, Nh

    do j = 1, Ny

      do k = 1, local_Nz

      odata2(i, j, k) = phik_dum(i, j, k)

      end do

    end do

  end do

!$OMP END PARALLEL

  call MPI_Barrier(MPI_COMM_WORLD, ierr)

  call dfftw_init_threads(iret)
  call dfftw_plan_with_nthreads(thread_num)
  call fftw_mpi_execute_dft_c2r(planb, odata2, idata2)


  call MPI_Barrier(MPI_COMM_WORLD, ierr)


  ! COPY TO OUTPUT ARRAY

!$OMP PARALLEL SHARED (idata2, phi_dum, local_Nz) PRIVATE (i,j,k)

!$OMP DO REDUCTION (+:sum)
  
  do i = 1, Nx

    do j = 1, Ny

      do k = 1, local_Nz

      phi_dum(i,j,k) = idata2(i,j,k)/dfloat(Nx*Ny*Nz)

      sum = sum + phi_dum(i,j,k)

      end do

    end do

  end do

!$OMP END PARALLEL

  call MPI_Barrier(MPI_COMM_WORLD, ierr)


  call MPI_GATHER(phi_dum, nx*ny*local_nz, MPI_DOUBLE, phi, nx*ny*local_nz,&

                                      MPI_DOUBLE, root, MPI_COMM_WORLD, ierr)


  call MPI_Barrier(MPI_COMM_WORLD, ierr)


  CALL MPI_REDUCE(sum, tmp, 1, MPI_DOUBLE, MPI_SUM, root, MPI_COMM_WORLD, ierr)


  sum = tmp


  ! deallocate and destroy plans  

  call fftw_destroy_plan(planf)

  call fftw_destroy_plan(planb)

  call fftw_mpi_cleanup()

  call fftw_free(cdatar)

  call fftw_free(cdatac)


  call MPI_Barrier(MPI_COMM_WORLD, ierr)


if (myid == root) then

!$OMP PARALLEL SHARED (sum,rho,phi) PRIVATE (i,j,k,thread_id)

thread_id = omp_get_thread_num()

!write (*,*) "SUM =", sum, myid, thread_id

!$OMP DO

do i = 1, Nx

  do j = 1, Ny

    do k = 1, Nz

      write (*,*) x(i),y(j),z(k),rho(i,j,k),phi(i,j,k)

    enddo

  end do

end do

!$OMP END PARALLEL

endif

end program poisson3d
```
