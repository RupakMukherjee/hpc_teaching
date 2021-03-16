# Step - 9: OpenMPI

OpenMPI is the Open sourced Message Passing Interface. In short it is a very abstract description on how messages can be exchanged between different processes. It will allow us to run a job across multiple nodes connected to the same cluster.

Now let's test OPENMPI, go to the *open_mpi* directory inside *shared_dir*
```console
pi@master ~>cd /shared_dir/open_mpi
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
Now, let’s test the same using SLURM job manager. In order to do so, first we have to create a job script. Go to the *slurm_jobs* directory inside *shared_dir*
```console
pi@master ~>cd /shared_dir/slurm_jobs
```
To submit a job use the following command
```console
sbatch hello_mpi_slurm.sh 
```
To view the status of any job
```console
squeue -u pi
```
NOTE: pi is your username
