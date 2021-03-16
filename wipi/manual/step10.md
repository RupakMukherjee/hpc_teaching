# Step - 10: OpenMPI

OpenMPI is the Open sourced Message Passing Interface. In short it is a very abstract description on how messages can be exchanged between different processes. It will allow us to run a job across multiple nodes connected to the same cluster.
```console
pi@master ~>sudo su -
#srun --nodes=2 apt install openmpi-bin openmpi-common libopenmpi3 libopenmpi-dev -y
```
Note: the number 2 was chosen based on our available nodes.

Now press Ctrl+d to exit from su-

If you are interested in using master node as well, you need to install the same for master node too.
```console
pi@master ~>sudo apt install openmpi-bin openmpi-common libopenmpi3 libopenmpi-dev -y
```
Now create a host file to run MPI jobs
```console
pi@master ~>nano hostfile
```
Now add the following (Change the ip addresses accordingly)
```console
10.10.0.11:4
10.10.0.12:4
10.10.0.13:4
```
NOTE: The last number “4” represents the number of cores(processors) in each CPU.

Now, we are ready to use MPI on our cluster. Let’s test a sample script.

Create a hello world program in C and save it as hello_mpi.c
```c
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    printf("Hello world from processor %s, rank %d"
           " out of %d processors\n",
           processor_name, world_rank, world_size);

    // Finalize the MPI environment.
    MPI_Finalize();
}
```
Now, compile the program using mpicc
```console
mpicc hello_mpi.c
```
This would create an executable name a.out
You can run the executable using the following command
```console
mpirun -np 2 -hostfile hostfile ./a.out
```
Now, let’s test the same using SLURM job manager. In order to do so, first we have to create a job script. Create a file named hello_mpi.sh and enter the following lines
```console
#!/bin/bash
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=4
#SBATCH --partition=picluster
cd $SLURM_SUBMIT_DIR
mpicc hello_mpi.c -o hello_mpi
mpirun ./hello_mpi
```
NOTE: The number 3 represents the number of nodes available in your cluster and the number 4 represents the number of cores(processors) available in each node.

To submit a job use the following command
```console
sbatch hello_mpi.sh 
```
To view the status of any job
```console
squeue -u pi
```    
NOTE: pi is your username
