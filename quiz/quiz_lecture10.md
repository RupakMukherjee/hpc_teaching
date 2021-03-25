# Quiz (Lecture 10)

I added some comments at the end of the program that we just wrote today. If you can run the program, it will print some comments those comments will give you some hint about, why for 2 nodes, it did not give us correct result.
    
Also, further at the end, it will print your Quiz - 8!

And finally what if, I send you a file and ask, what does [this program](https://rupakmukherjee.github.io/pseudo-spectral-crash-course/code/poisson_3d_hybrid.html) do?
To compile and run this file, you may use the following command:

```console
$ mpif90 -fopenmp -I/usr/local/include -L/usr/local/lib poisson_3d_hybrid.f95 -lfftw3_mpi -lfftw3_omp -lfftw3 -lm; mpirun -quiet -np 3 ./a.out
```

### Quiz - 6: 
Can you turn the code [hybrid_do.f95](https://rupakmukherjee.github.io/pseudo-spectral-crash-course/code/hybrid_do.html) into a 3d hybrid Poisson solver?
If you can solve Quiz - 9, this course is over!!!
