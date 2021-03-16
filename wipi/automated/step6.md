# Step - 6: Configuring SLURM on Compute Nodes

We have successfully configured the master node, we need to do the same on compute nodes. Now, log into the one of the nodes let's say node01
```console
ssh pi@10.10.0.12
```

Then, go to the deployment directory inside the wipi repository,
```console
pi@node01 ~> cd /home/pi/wipi/deployment
```
Now run the script *slurm_config_nodes.sh* to prepare the worker node for slurm.
```console
pi@node01~$ sudo bash slurm_config_nodes.sh
```
To ensure smooth operation, the system will reboot at this point.

#### Diagnostic check for MUNGE
Now, we need to verify whether our the SLURM controller can successfully authenticate with the client nodes using munge. In order to do that, we need to login to master node and use the following command,
```console
pi@master ~> ssh pi@node01 munge -n | unmunge
```
Upon successful operation, you should get output something similar to the following,
```console
ssh pi@node01 munge -n | unmunge
pi@node01's password: 
STATUS:           Success (0)
ENCODE_HOST:      master (127.0.1.1)
ENCODE_TIME:      2020-08-30 22:45:00 +0200 (1598820300)
DECODE_TIME:      2020-08-30 22:45:00 +0200 (1598820300)
TTL:              300
CIPHER:           aes128 (4)
MAC:              sha256 (5)
ZIP:              none (0)
UID:              pi (1001)
GID:              pi (1001)
LENGTH:           0
```
Sometime, you might get an error, which indicates that you may have failed to copy the exact munge key to the nodes.

Now repeat this process on all the other nodes.

