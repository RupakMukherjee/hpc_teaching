# Step - 3: Setting Up the Master Node

Now, log in to your master node using
```console
ssh pi@10.10.0.11
```
Upon connection use password *raspberry*. (Note: it is the default password)


Now, use the following command to download the shell script for master node
```console
pi@raspberrypi~$ wget https://raw.githubusercontent.com/sayanadhikari/wipi/automated/deployment/master_deployment.sh
```
The script you just downloaded should be in */home/pi/* with the name *master_deployment.sh*.

#### Safety check for shared storage:

Just before setting up the network, we inserted the external storage into master node. Now use the following command to see the dev location and mount point of your storage.
```console
pi@raspberrypi ~> lsblk
NAME        MAJ:MIN RM  SIZE RO TYPE MOUNTPOINT
mmcblk0     105:0    0  7.4G  0 disk 
├─mmcblk0p1 105:1    0 43.8M  0 part /boot
└─mmcblk0p2 105:2    0  7.4G  0 part /
sda         3:16     0 59.2G  0 disk
└─sda1      3:17     0 59.2G  0 part
```
In our case, the main partition of the external storage is mounted at */dev/sda1*. However, if it is different for you, you should edit the *master_deployment.sh* file and modify the following lines accordingly. (Note: replace */dev/sda1* with */dev/sda2* or whatever path you get from *lsblk* command)
```shell
mkfs.ext4 /dev/sda1
UUID=$(blkid -o value -s UUID /dev/sda1)
```

Now run the script to prepare the master node.
```console
pi@raspberrypi~$ sudo bash ./master_deployment.sh
```
At the end of the script execution, the system will automatically reboot. After reboot, log-in to the master node again using 
```console
ssh pi@10.10.0.11
```
and run the following command
```console
pi@master~$ sudo chmod 777 -R /shared_dir
```
