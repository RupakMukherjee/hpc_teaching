# Step - 5: Configuring SLURM on master Node
Slurm is an open source, and highly scalable cluster management and job scheduling system. It can be used for both large and small Linux clusters. Let’s install it on our Pi cluster. To do that, first we need to login to the master node using ssh again,
```console
ssh pi@10.10.0.11
```
Then, go to the deployment directory inside the wipi repository,
```console
pi@master ~> cd /home/pi/wipi/deployment
```

To allow password-less ssh across the system, run the *password_less_ssh_master.sh* using the following command,
```console
pi@master~$ bash password_less_ssh_master.sh
```

Now run the script *slurm_config_master.sh* to prepare the master node for slurm.
```console
pi@master~$ sudo bash slurm_config_master.sh
```

To ensure smooth operation, the system will reboot at this point.
