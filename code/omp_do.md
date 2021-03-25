# Code Description

## omp_do.f95: 

This is a program to teach OpenMP do loops.

```fortran
program OMP_Do
! To run this program: gfortran -fopenmp omp_do.f95; ./a.out
use omp_lib
implicit none
integer ( kind = 4 ) thread_num,num_thread,proc_num,thread_id ! OpenMP Variables
integer:: i,N
real*8 sum
! Define Number of Threads.
proc_num = omp_get_num_procs()
thread_num = proc_num
call omp_set_num_threads (thread_num)
write(*,*)
write(*,*) "Number of Processors=", proc_num, "Number of Threads=", thread_num 
write(*,*)
N = 10
sum = 0.0d0
!$OMP PARALLEL SHARED(N) PRIVATE(i,thread_id)
!$OMP DO
do i = 1,N
thread_id = omp_get_thread_num()
write(*,*) "Thread",thread_id,"says - I am loop index",i
enddo
!$OMP END DO
!$OMP END PARALLEL
write(*,*)
!$OMP PARALLEL SHARED(N) PRIVATE(i)
!$OMP DO REDUCTION (+:sum)
do i = 1,N
sum = sum + dfloat(i)
enddo
!$OMP END PARALLEL
write(*,*) "The sum of",N,"numbers is",int(sum)
write(*,*)
end program OMP_Do
```
