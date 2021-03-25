# Code Description

## hybrid_do.f95: 

This is a program to teach Hybrid (= OpenMP + MPI) nested-do loops.

```fortran
program hybrid_test
use omp_lib
implicit none
include 'mpif.h'

integer (kind = 4), parameter :: nx = 3
integer (kind = 4), parameter :: ny = 4
integer (kind = 4) i, j
integer (kind = 4) root, ny_loc, dim_array
integer (kind = 4) nprocs, myrank, ierr 
integer (kind = 4) thread_num, proc_num, thread_id

real, dimension (nx, ny) :: in, out
real, allocatable :: loc(:,:)

!INITIALIZING OPENMP
proc_num = omp_get_num_procs()
thread_num = proc_num
call omp_set_num_threads (thread_num)

! INITIALIZING MPI
CALL MPI_INIT (ierr)
CALL MPI_COMM_SIZE (MPI_COMM_WORLD, nprocs, ierr)
CALL MPI_COMM_RANK (MPI_COMM_WORLD, myrank, ierr)

root = 0
ny_loc = ny / nprocs
allocate (loc(nx, ny_loc))
dim_array = nx*ny_loc

if (myrank == root) then
!$OMP PARALLEL SHARED (in) PRIVATE (i,j)
!$OMP DO
  do j = 1, ny
    do i = 1, nx
      in(i,j) = float(i) + float(j)
      print*, i, j, in(i,j),  "INPUT"
    enddo
  enddo
!$OMP END PARALLEL
endif

call MPI_SCATTER (in, dim_array, MPI_REAL, loc, dim_array, MPI_REAL, root, MPI_COMM_WORLD, ierr)

!$OMP PARALLEL SHARED (ny_loc,loc,myrank) PRIVATE (i,j,thread_id)
thread_id = omp_get_thread_num()
print*, myrank, thread_id
!$OMP DO 
do j = 1, ny_loc
  do i = 1, nx
    loc(i,j) = loc(i,j) + 1
    print*, i, j, j+ny_loc*myrank, loc(i,j), myrank, thread_id
  enddo
enddo
!$OMP END PARALLEL

call MPI_GATHER (loc, dim_array, MPI_REAL, out, dim_array, MPI_REAL, root, MPI_COMM_WORLD, ierr)

if (myrank == root) then
!$OMP PARALLEL SHARED (out) PRIVATE (i,j)
!$OMP DO
  do j = 1, ny
    do i = 1, nx
      print*, i, j, out(i,j), "OUTPUT"
    enddo
  enddo
!$OMP END PARALLEL
endif

CALL MPI_FINALIZE(ierr)

end program hybrid_test
```
