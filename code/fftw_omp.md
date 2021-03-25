# Code Description

## fftw_omp.f95: 

This is a program to teach how to use FFTW routine with OpenMP parallelization. This is a multi-core extension of fftw_2d.f95. Hence this code also takes a set of random numbers as input of two dimensional array in multiple cores, takes their Fourier transform using OpenMP parallel two dimensional FFTW library and then calculates the multi-core inverse Fourier transform, thus finally comparing the result with the input random numbers.

```fortran
program fft2

use omp_lib
implicit none

integer (kind=4), parameter :: Nx = 3
integer (kind=4), parameter :: Ny = 4
integer (kind=4), parameter :: Nh = (Nx/2) + 1
real (kind=8), parameter :: pi = 3.1428

include "fftw3.f"

integer (kind=4) i,j
integer (kind=4) thread_num,num_thread,proc_num,iret
real dx,dy,Lx,Ly
real (kind=8) x(Nx),y(Ny),ux(Nx,Ny),ux_dum(Nx,Ny)
complex (kind=8) ukx(Nh,Ny), ukx_dum(Nh,Ny)

integer (kind=8) plan_forward, plan_backward
integer ( kind = 4 ) seed

seed = 123456789

  proc_num = omp_get_num_procs()
  thread_num = proc_num
  call omp_set_num_threads (thread_num)
  print*, thread_num

Lx = 2.0d0*pi
Ly = 2.0d0*pi
dx = Lx/dfloat(Nx)
dy = Ly/dfloat(Ny)

do i = 1,Nx
x(i) = (i-1)*dx
  do j = 1,Ny
  y(j) = (j-1)*dy
     ux(i,j) = ran(seed)
     seed=ux(i,j)*seed
  enddo
enddo
  
  call dfftw_init_threads(iret)
  call dfftw_plan_with_nthreads(thread_num) 
  call dfftw_plan_dft_r2c_2d_ (plan_forward, Nx, Ny, ux, ukx, FFTW_ESTIMATE)
  call dfftw_execute_ (plan_forward)
  call dfftw_destroy_plan_ (plan_forward)

do i = 1,Nh
  do j = 1,Ny
  ukx_dum(i,j) = ukx(i,j)
!  write(*,*) i,j,ukx_dum(i,j)
  enddo
enddo
  call dfftw_init_threads(iret)
  call dfftw_plan_with_nthreads(thread_num)
  call dfftw_plan_dft_c2r_2d_ (plan_backward, Nx, Ny, ukx_dum, ux_dum, FFTW_ESTIMATE)
  call dfftw_execute_ (plan_backward)
  call dfftw_destroy_plan_ (plan_backward)

do i = 1, Nx
  do j = 1,Ny
  write(*,*) i,j, ux(i,j), ux_dum(i,j)/(dfloat(Nx)*dfloat(Ny))
  enddo
enddo

end

```
