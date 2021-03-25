# Code Description

## omp_nested_do.f95: 

This is a program to teach OpenMP nested-do loops.

```fortran
program OMP_Nested_Do
! To run this program: gfortran -fopenmp omp_nested_do.f95; ./a.out
use omp_lib
implicit none
integer ( kind = 4 ) thread_num,num_thread,proc_num,thread_id ! OpenMP Variables
integer:: i,j,Nx,Ny
real*8 sum
! Define Number of Threads.
proc_num = omp_get_num_procs()
thread_num = proc_num
call omp_set_num_threads (thread_num)
write(*,*)
write(*,*) "Number of Processors=", proc_num, "Number of Threads=", thread_num 
write(*,*)
Nx = 10
Ny = 5
sum = 0.0d0
!$OMP PARALLEL SHARED(Nx,Ny) PRIVATE(i,j,thread_id)
!$OMP DO
do i = 1,Nx
  do j = 1,Ny
  thread_id = omp_get_thread_num()
  write(*,*) "Thread",thread_id,"says - I am loop index",i,j
  enddo
enddo 
!$OMP END DO
!$OMP END PARALLEL
write(*,*)
!$OMP PARALLEL SHARED(Nx,Ny) PRIVATE(i,j)
!$OMP DO REDUCTION (+:sum)
do i = 1,Nx
  do j = 1,Ny
  sum = sum + 1.0d0
  enddo
enddo
!$OMP END PARALLEL
write(*,*) "Total number of points in",Nx,"X",Ny,"grid is", int(sum)
write(*,*)
end program OMP_Nested_Do
```
