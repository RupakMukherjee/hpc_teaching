#!/bin/bash
#SBATCH --job-name=multiplication_test      # Job name
#SBATCH --nodes=1                     # Run on a single CPU
#SBATCH --ntasks-per-node=1           # Run with a single thread
#SBATCH --time=00:01:00               # Time limit hrs:min:sec
#SBATCH --partition=picluster         # Name of the partition

cd $SLURM_SUBMIT_DIR
gfortran multiplication.f95
./a.out
