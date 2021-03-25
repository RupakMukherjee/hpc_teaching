# Code Description

## fftw_mpi.f95: 

This is a program to teach how to use FFTW routine with MPI parallelization. This is a multi-node extension of fftw_2d.f95. Hence this code also takes a set of random numbers as input of two dimensional array, takes their Fourier transform using MPI parallel two dimensional FFTW library and then calculates the multi-node inverse Fourier transform, thus finally comparing the result with the input random numbers.

```fortran
program fft2

use, intrinsic :: iso_c_binding

implicit none

include 'mpif.h'

integer (C_INTPTR_T), parameter :: nx = 3
integer (C_INTPTR_T), parameter :: ny = 4
integer (C_INTPTR_T), parameter :: nh = (Nx/2) + 1
real (kind=8), parameter :: pi = 3.1428

include "fftw3-mpi.f03"

integer :: ierr, myid, nproc
integer (C_INTPTR_T) i,j
real(C_DOUBLE), dimension (nx,ny) :: ux,ux_dum
complex (C_DOUBLE_COMPLEX), dimension(nh,ny) ::  ukx, ukx_dum

type(C_PTR) :: plan_forward, plan_backward, cdatar, cdatac
integer(C_INTPTR_T) :: alloc_local, local_ny, local_j_offset
real(C_DOUBLE), pointer :: idata(:,:)
complex(C_DOUBLE_COMPLEX), pointer :: odata(:,:)

integer ( kind = 4 ) seed

seed = 9999999 

  call mpi_init (ierr)
  call MPI_COMM_SIZE(MPI_COMM_WORLD, nproc, ierr)
  call MPI_COMM_RANK(MPI_COMM_WORLD, myid, ierr)

do i = 1,nx
  do j = 1,ny
     ux(i,j) = ran(seed)
     seed=ux(i,j)*seed
     write(*,*) i, j, ux(i,j)
  enddo
enddo

write(*,*) "END OF INPUT"

  call fftw_mpi_init()

  alloc_local = fftw_mpi_local_size_2d (ny, nh, MPI_COMM_WORLD, local_ny, local_j_offset)
  cdatar = fftw_alloc_real(2*alloc_local)
  cdatac = fftw_alloc_complex(alloc_local)

  call c_f_pointer (cdatar, idata, [2*nh,local_ny])
  call c_f_pointer (cdatac, odata, [nh,local_ny])

  plan_forward = fftw_mpi_plan_dft_r2c_2d (Ny,Nx,idata,odata,MPI_COMM_WORLD,FFTW_MEASURE)
  plan_backward = fftw_mpi_plan_dft_c2r_2d (Ny,Nx,odata,idata,MPI_COMM_WORLD,FFTW_MEASURE)

do i= 1, nx
  do j = 1, local_ny
  idata(i,j) = ux(i,j + local_j_offset)
  enddo
enddo

  call fftw_mpi_execute_dft_r2c (plan_forward,idata,odata)

  call fftw_mpi_execute_dft_c2r (plan_backward,odata,idata)

do i = 1, nx
  do j = 1,local_ny
  ux_dum(i,j+local_j_offset) = idata(i,j)
  write(*,*) i,j,j+local_j_offset,local_j_offset,ux_dum(i,j)/(dfloat(Nx)*dfloat(Ny))
  enddo
enddo

write(*,*) "END OF OUTPUT - TRUELY?"

  call fftw_destroy_plan(plan_forward)
  call fftw_destroy_plan(plan_backward)
  call fftw_mpi_cleanup()
  call fftw_free(cdatar)
  call fftw_free(cdatac)

write(*,*) "No! I am id", myid

do i = 1, nx
  do j = 1,ny
  write(*,*) i,j,ux_dum(i,j)/(dfloat(Nx)*dfloat(Ny))
  enddo
enddo

write(*,*) "END OF OUTPUT - TRUELY? -YES"

  call mpi_finalize(ierr)

write(*,*) "Quiz - 8: How do you combine the results from the two nodes? Edit this program and print the output!"

end

```
