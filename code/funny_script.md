# Code Description

## funny_script.sh

This scripts creates a file named test_results, copies the two files named addition.f95 and multiplication.f95, changing their variable values within the codes and then creates sub-directories within the file "test_results" pastes the programs accordingly and launches the runs in any slurm type hpc cluster!

```console
mkdir -p test_results/{addition,multiplication}/values_{2.0,3.0}
echo test_results/addition/values_{2.0,3.0} | xargs -n 1 cp addition_jobfile.sh
echo test_results/addition/values_{2.0,3.0} | xargs -n 1 cp addition.f95
echo test_results/multiplication/values_{2.0,3.0} | xargs -n 1 cp multiplication_jobfile.sh
echo test_results/multiplication/values_{2.0,3.0} | xargs -n 1 cp multiplication.f95

cd test_results/addition

#---------------------------------------------------------------------------------------------
cd values_2.0
perl -pi -e 's/n = abc/n = 2 /g' addition.f95
#gfortran addition.f95; ./a.out
sbatch addition_jobfile.sh
cd ..
cd values_3.0
perl -pi -e 's/n = abc/n = 3 /g' addition.f95
#gfortran addition.f95; ./a.out
sbatch addition_jobfile.sh
cd ..
cd ..
cd ..

cd test_results/multiplication
#---------------------------------------------------------------------------------------------
cd values_2.0
perl -pi -e 's/m = xyz/m = 2 /g' multiplication.f95
#gfortran multiplication.f95; ./a.out
sbatch multiplication_jobfile.sh
cd ..
cd values_3.0
perl -pi -e 's/m = xyz/m = 3 /g' multiplication.f95
#gfortran multiplication.f95; ./a.out
sbatch multiplication_jobfile.sh
cd ..
cd ..
cd ..
```
