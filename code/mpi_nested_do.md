# Code Description

## mpi_nested_do.f95: 

This is a program to teach MPI nested-do loops.

```fortran
program mpi_test
implicit none
include 'mpif.h'

integer (kind = 4), parameter :: nx = 3
integer (kind = 4), parameter :: ny = 4
integer (kind = 4) i, j
integer (kind = 4) root, ny_loc, dim_array, nprocs, myrank, ierr

real, dimension (nx, ny) :: in, out
real, allocatable :: loc(:,:)

! INITIALIZING MPI
CALL MPI_INIT (ierr)
CALL MPI_COMM_SIZE (MPI_COMM_WORLD, nprocs, ierr)
CALL MPI_COMM_RANK (MPI_COMM_WORLD, myrank, ierr)

root = 0
ny_loc = ny / nprocs
allocate (loc(nx, ny_loc))
dim_array = nx*ny_loc

if (myrank == root) then
  do j = 1, ny
    do i = 1, nx
      in(i,j) = float(i) + float(j)
      print*, i, j, in(i,j),  "INPUT"
    enddo
  enddo
endif

call MPI_SCATTER (in, dim_array, MPI_REAL, loc, dim_array, MPI_REAL, root, MPI_COMM_WORLD, ierr)

do j = 1, ny_loc
  do i = 1, nx
    loc(i,j) = loc(i,j) + 1
    print*, i, j, j+ny_loc*myrank, loc(i,j), myrank
  enddo
enddo

call MPI_GATHER (loc, dim_array, MPI_REAL, out, dim_array, MPI_REAL, root, MPI_COMM_WORLD, ierr)

if (myrank == root) then
  do j = 1, ny
    do i = 1, nx
      print*, i, j, out(i,j), "OUTPUT"
    enddo
  enddo
endif

CALL MPI_FINALIZE(ierr)

end program mpi_test
```
