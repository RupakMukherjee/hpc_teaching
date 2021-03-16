# Step - 5: Configuring SLURM on master Node
Slurm is an open source, and highly scalable cluster management and job scheduling system. It can be used for both large and small Linux clusters. Let’s install it on our Pi cluster.
```console
pi@master ~> sudo apt install slurm-wlm -y
```
Upon successful installation, we need to configure slurm,
```console
pi@master ~> cd /home/pi
pi@master ~> cp /usr/share/doc/slurm-client/examples/slurm.conf.simple.gz .
pi@master ~> gzip -d slurm.conf.simple.gz
pi@master ~> sudo mv slurm.conf.simple /etc/slurm-llnl/slurm.conf 
```
Now edit the configuration file by searching for the keyword on the left (e.g. “SlurmctlHost”) and edit the line as per the information provide below,
```console
pi@master ~> sudo nano /etc/slurm-llnl/slurm.conf
```
```console
SlurmctldHost=master(10.10.0.11)
SelectType=select/cons_res
SelectTypeParameters=CR_Core
ClusterName=cluster
```
Now we need to add the node information as well as partition at the end of the file. Delete the example entry for the compute node and add the following configurations for the cluster nodes:
```console
NodeName=master NodeAddr=10.10.0.11 CPUs=4 State=UNKNOWN
NodeName=node01 NodeAddr=10.10.0.12 CPUs=4 State=UNKNOWN
NodeName=node02 NodeAddr=10.10.0.13 CPUs=4 State=UNKNOWN
PartitionName=picluster Nodes=node[01-02] Default=YES MaxTime=INFINITE State=UP
```
Now we need to create a configuration for cgroup support
```console
pi@master ~> sudo nano /etc/slurm-llnl/cgroup.conf
```
Now, add the following,
```console
CgroupMountpoint="/sys/fs/cgroup"
CgroupAutomount=yes
CgroupReleaseAgentDir="/etc/slurm-llnl/cgroup"
AllowedDevicesFile="/etc/slurm-llnl/cgroup_allowed_devices_file.conf"
ConstrainCores=no
TaskAffinity=no
ConstrainRAMSpace=yes
ConstrainSwapSpace=no
ConstrainDevices=no
AllowedRamSpace=100
AllowedSwapSpace=0
MaxRAMPercent=100
MaxSwapPercent=100
MinRAMSpace=30
```

Now, we need to whitelist system devices by creating the file 

```console
pi@master ~> sudo nano /etc/slurm-llnl/cgroup_allowed_devices_file.conf
```
Now add the following lines,
```console
/dev/null
/dev/urandom
/dev/zero
/dev/sda*
/dev/cpu/*/*
/dev/pts/*
/shared_dir*
```
Now we need to set the same for all nodes. To do that we need to copy these files to the shared storage.
```console
pi@master ~> sudo cp /etc/slurm-llnl/*.conf /shared_dir
pi@master ~> sudo cp /etc/munge/munge.key /shared_dir
```

All done, now we need to enable and start SLURM Control Services and munge,
```console
pi@master ~> sudo systemctl enable munge
pi@master ~> sudo systemctl start munge
```
```console
pi@master ~> sudo systemctl enable slurmd
pi@master ~> sudo systemctl start slurmd
```
```console
pi@master ~> sudo systemctl enable slurmctld
pi@master ~> sudo systemctl start slurmctld
```

To ensure smooth operation, we need to reboot the system at this point.
