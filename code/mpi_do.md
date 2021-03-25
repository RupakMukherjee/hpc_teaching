# Code Description

## mpi_do.f95: 

This is a program to teach MPI do loops.

```fortran
!mpif90 block_loop.f90
!mpirun -np 4 ./a.out
PROGRAM main
INCLUDE 'mpif.h'
PARAMETER (n = 10)
DIMENSION a(n),b(n)
real, allocatable :: loc(:)
CALL MPI_INIT(ierr)
CALL MPI_COMM_SIZE(MPI_COMM_WORLD, nprocs, ierr)
CALL MPI_COMM_RANK(MPI_COMM_WORLD, myrank, ierr)
!print*, nprocs, myrank
root = 0
m = n / nprocs
allocate(loc(m))
if (myrank == root) then
DO i = 1, n
a(i) = float(i)
print*, i,a(i),"IN"
ENDDO
endif
call  MPI_SCATTER( a, m, MPI_REAL, loc, m, MPI_REAL, root, &
                                        MPI_COMM_WORLD, ierr )
print*,
DO i = 1,m
loc(i) = loc(i) + 1
print*, i+m*myrank,loc(i),myrank
ENDDO
print*,
call  MPI_GATHER( loc, m, MPI_REAL, b, m, MPI_REAL, root, &
                                        MPI_COMM_WORLD, ierr )
if (myrank == root) then                                      
DO i = 1, n
print*, i,b(i),"OUT"
ENDDO
endif
CALL MPI_FINALIZE(ierr)
END
```
