# Step - 7: Test SLURM 
Login to master node using ssh and type the following command
```console
pi@master ~>sinfo
```
You should get an output something like this
```console
PARTITION  AVAIL  TIMELIMIT  NODES  STATE NODELIST
picluster*    up   infinite      2   idle node[01-03]
```

You can simply run a task to ask the hostname for each node
```console
pi@master ~>srun --nodes=2 hostname
```
It will give you an output similar to
```console
node02
node01
```
