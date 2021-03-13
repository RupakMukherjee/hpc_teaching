High Performance Computing
==============================
a repository for teaching high performance computing architechture.

Instructor: [Dr. Rupak Mukherjee](https://github.com/RupakMukherjee)

Contributor: [Dr. Sayan Adhikari](https://github.com/sayanadhikari)

A series of lectures (in [Hinglish](https://en.wikipedia.org/wiki/Hinglish)) are available on youtube based on the materials archived in this repository. Click on the link provided below to access the lectures.


[Webinar on "High Performance Computing"](https://www.youtube.com/playlist?list=PLbX_ZyxeXxSIwXoFHHB6Vd2N4jvlyUTaQ)

[![Webinar on "High Performance Computing"](http://img.youtube.com/vi/IoTquSbTgoQ/0.jpg)](https://www.youtube.com/embed/videoseries?list=PLbX_ZyxeXxSIwXoFHHB6Vd2N4jvlyUTaQ)

# Lecture Description

# Lecture Description
[Lecture 1](lecture1.md) | [Lecture 2](lecture2.md)
------------ | ------------- 
[YouTube](https://youtu.be/MeyFQNDE15o)      | [YouTube](https://youtu.be/hdQ3O6RqL1M)

## Lecture 1
First I talk about some basic idea about particle simulation and then enter into the basic idea of computational complexity, decomposition into multiple computational domain. Then I stressed into the basic hardware architechture of personal computer / desktop, connecting multiple computation units via LAN cables, basic idea about few technical terms widely used in the high performance computing community like node, core etc. and then about the parallel computer software architechture namely, message passing interface (MPI) and OpenMP. I then briefly touched on few real examples of high performance clusters in India and then gave few glimpses of GPU and FPGA computing, architechtures and programming language. I also compared few examples of implementation of multicore (OpenMP) and multi-threaded (OpenACC) computing very crudely and then went into the same for multinode (MPI) architechture. Finally I ended with some 'funny' problems, relevant for current computation challenges!


## Lecture 2
In the first part of the lecture, I mostly revised the basic hardware structure of a computer, crude idea about connecting computers via LAN cables and thereby basic idea of multi-node computation architechture. Then I talked about potential of a Raspberry Pi to be used as a cluster for computation, explicitly showed a toy example, physical connections, basic units to make a cluster, some technical aspects, some idea of transatlantic network connectivity. Then showed some explicit example of multi-node computation in the toy Raspberry Pi cluster and finally some simple shell scripting techniques to launch multiple runs at a time. Then I touched upon some ideas about job-schedulers and few basic commands to launch, monitor and cancel jobs in any standard high-performance-clusters, available world-wide. Finally I concluded with comparison of commands in other job-schedulers available world-wide. 


# Code Description

## funny_script.sh
This scripts creates a file named test_results, copies the two files named addition.f95 and multiplication.f95, changing their variable values within the codes and then creates sub-directories within the file "test_results" pastes the programs accordingly and launches the runs in any slurm type hpc cluster!
