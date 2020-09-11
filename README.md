# HPC teaching
a repository for teaching high performance computing architechture
funny_script.sh: This scripts creates a file named test_results, copies the two files named addition.f95 and multiplication.f95, changing their variable values within the codes and then creates sub-directories within the file "test_results" pastes the programs accordingly and launches the runs in any slurm type hpc cluster!

## Lecture 1
First I talk about some basic idea about particle simulation and then enter into the basic idea of computational complexity, decomposition into multiple computational domain. Then I stressed into the basic hardware architechture of personal computer / desktop, connecting multiple computation units via LAN cables, basic idea about few technical terms widely used in the high performance computing community like node, core etc. and then about the parallel computer software architechture namely, message passing interface (MPI) and OpenMP. I then briefly touched on few real examples of high performance clusters in India and then gave few glimpses of GPU and FPGA computing, architechtures and programming language. I also compared few examples of implementation of multicore (OpenMP) and multi-threaded (OpenACC) computing very crudely and then went into the same for multinode (MPI) architechture. Finally I ended with some 'funny' problems, relevant for current computation challenges!


