High Performance Computing
==============================
a repository for teaching high performance computing architechture.

Instructor: [Dr. Rupak Mukherjee](https://github.com/RupakMukherjee)

Contributor: [Dr. Sayan Adhikari](https://github.com/sayanadhikari)

A series of lectures (in [Hinglish](https://en.wikipedia.org/wiki/Hinglish)) are available on youtube based on the materials archived in this repository. Click on the link provided below to access the lectures.


[Webinar on "High Performance Computing"](https://www.youtube.com/playlist?list=PLbX_ZyxeXxSIwXoFHHB6Vd2N4jvlyUTaQ)

[![Webinar on "High Performance Computing"](http://img.youtube.com/vi/IoTquSbTgoQ/0.jpg)](https://www.youtube.com/embed/videoseries?list=PLbX_ZyxeXxSIwXoFHHB6Vd2N4jvlyUTaQ)


# Hands-on demonstration:

## Building High-Performance Computing (HPC) Cluster with Raspberry Pi 

### [With automated scripts (~ 1.5 hour)](wipi/automated/automated.md)

### [A detailed manual script (~ 4 hours)](wipi/manual/manual.md)


# Lecture Description

| [Lecture 1](lecture1.md) | [Lecture 2](lecture2.md) |
| ------------ | ------------- |
| [YouTube](https://youtu.be/MeyFQNDE15o) | [YouTube](https://youtu.be/hdQ3O6RqL1M) |

# Code Description

## [funny_script.sh](code/funny_script.md)
This scripts creates a file named test_results, copies the two files named [addition.f95](code/addition.md) and [multiplication.f95](code/multiplication.md), changing their variable values within the codes and then creates sub-directories within the file "test_results" pastes the programs accordingly and launches the runs in any slurm type hpc cluster!





# Lecture description

[Lecture 8](lecture8.md) | [Lecture 9](lecture9.md) | [Lecture 10](lecture10.md) | [Lecture 11](lecture11.md)
------------- | ------------ | ------------- | ------------
[Resources](resources/resource_lecture8.md) | [Resources](resources/resource_lecture9.md) | [Resources](resources/resource_lecture10.md)  | [Resources](resources/resource_lecture11.md)
None      | None      | [Quiz](quiz/quiz_lecture10.md)       | None
[YouTube](https://youtu.be/b35LvlSZOuc)      | [YouTube](https://youtu.be/7FRiqSK6mBU)      | [YouTube](https://youtu.be/87KAvsfV73w)       | [YouTube](https://youtu.be/mrAoE4lFvas)

# Code Reference
The name of the codes/programs have been modified to recognize the pupose of the codes easily. The names used in the lectures can be found from the following table:

Lecture | GitHub Code Name | Original Name | GitHub Code Name | Original Name 
------- | --------- | ------------- | --------- | -------------
Lecture 8 | [omp_do.f95](code/omp_do.md) | omp.f95 | [omp_nested_do.f95](code/omp_nested_do.md) | omp.f95
Lecture 9 | [mpi_do.f95](code/mpi_do.md) | mpi.f95
Lecture 10| [mpi_nested_do.f95](code/mpi_nested_do.md) | mpi.f95 | [hybrid_do.f95](code/hybrid_do.md) | hybrid.f95
Lecture 11| [fftw_omp.f95](code/fftw_omp.md) | 2d_fft.f95 | [fftw_mpi.f95](code/fftw_mpi.md) | 2d_fft.f95

# Commands to run the programs/codes
#### Serial Do Loop compilation
```console
gfortran <program_name.f95>; ./a.out
```
#### OpenMP Do Loop compilation
```console
gfortran -fopenmp <program_name.f95>; ./a.out
```
#### MPI Do Loop compilation
```console
mpif90 <program_name.f95>; mpirun -np 4 ./a.out
```
#### Hybrid Do Loop compilation
```console
mpif90 -fopenmp <program_name.f95>; mpirun -np 4 ./a.out
```
#### Serial FFTW compilation
```console
gfortran -I/usr/local/include -L/usr/local/lib <program_name.f95> -lfftw3 -lm; ./a.out
```
#### OpenMP FFTW compilation
```console
gfortran -fopenmp -I/usr/local/include -L/usr/local/lib <program_name.f95> -lfftw3_omp -lfftw3 -lm; ./a.out
```
#### MPI FFTW compilation
```console
mpif90 -I/usr/local/include -L/usr/local/lib <program_name.f95> -lfftw3_mpi -lfftw3 -lm; mpirun -np 4 ./a.out
```
#### Hybrid FFTW compilation
```console
mpif90 -fopenmp -I/usr/local/include -L/usr/local/lib <program_name.f95> -lfftw3_mpi -lfftw3_omp -lfftw3 -lm; mpirun -quiet -np 4 ./a.out
```
#### Hybrid FFTW compilation and running with hyperthreads in macOS
```console
mpif90 -fopenmp -I/usr/local/include -L/usr/local/lib <program_name.f95> -lfftw3_mpi -lfftw3_omp -lfftw3 -lm; mpirun --use-hwthread-cpus ./a.out
```
