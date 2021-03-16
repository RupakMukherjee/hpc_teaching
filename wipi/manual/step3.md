# Step - 3: Setting Up the Master Node

Now, log in to your master node using
```console
ssh pi@10.10.0.11
```
Upon connection use password raspberry. (Note: it is the default password)

Now, we need to configure the node before starting to use. 
```console
pi@raspberrypi~$ sudo raspi-config
```
It opens up the config utility. You can change the default password if you want (highly recommended). Next you should set the locale, timezone, and wifi country. Then, select finish and press enter to exit the utility.

A snapshot of the utility screen is provided below.

![Raspberry Pi Configuration Window](/images/raspi-config.jpg)


### System Update and Upgrade
```console
pi@raspberrypi ~> sudo apt-get update && sudo apt-get upgrade
```
Now, we need to decide the hostnames for master node as well as cluster nodes. I would recommend to stick with the usual ones. Set “master” for master node and for cluster nodes starting from “node01” to “node02” (for 2 node cluster). Use the following command to set it up on master node.
```console
pi@raspberrypi ~> sudo hostname master     # choice of yours
```
Change "raspberrypi" to “master” by editing the hostname file.

```console
pi@raspberrypi ~> sudo nano /etc/hostname  
```
Now edit the hosts file
```console
pi@raspberrypi ~> sudo nano /etc/hosts   
```

Add the following at the bottom of the existing information
```console
127.0.1.1      master
10.10.0.11     master
10.10.0.12     node01
10.10.0.13     node02
```

### Network time:

Now, since we are planning for a HPC system that uses a SLURM scheduler and the Munge authentication, we need to make sure that the system time is accurate. For that purpose we can install ntpdate package to periodically sync the system time in the background.
```console
pi@raspberrypi ~> sudo apt install ntpdate -y
```
To apply the effect of changes that have been made so far reboot the system using the following command
```console
sudo reboot
```
After, successful reboot, login to the master node again using ssh. 

### Next stop, shared storage:

The concept of cluster is based on idea of working together. In order to do so, they need to have access to the same files. We can arrange this mounting an external SSD drive (not necessary but convenient and faster) and exporting that storage as a network file system (NFS). It would allow us to access the files from all nodes.

First, insert the external storage into your master node. Now login to your master node using ssh and use the following command to see the dev location and mount point of your storage.
```console
pi@master ~> lsblk
NAME        MAJ:MIN RM  SIZE RO TYPE MOUNTPOINT
mmcblk0     105:0    0  7.4G  0 disk 
├─mmcblk0p1 105:1    0 43.8M  0 part /boot
└─mmcblk0p2 105:2    0  7.4G  0 part /
sda         3:16     0 59.2G  0 disk
└─sda1      3:17     0 59.2G  0 part
```

In our case, the main partition of the external storage is mounted at /dev/sda1
Before, using it as a NFS drive, we need to format it properly in ext4 file system. Use the following command to do that.
```console
sudo mkfs.ext4 /dev/sda1
```
:warning: Note: If you are not using any external storage, and want to use the Micro-SD card instead skip the formatting.

Now, we need to create a directory where the storage will be mounted. We can choose any name for that. But, lets choose something that is easy to remember e.g. “shared”,
```console
sudo mkdir /shared_dir
sudo chown nobody.nogroup -R /shared_dir
sudo chmod 777 -R /shared_dir
```

Now, we need to configure to mount the storage during boot. For, that we need the the UUID of the storage. We can find that using the following command,
```console
pi@master ~> blkid
```
```console
/dev/mmcblk0p1: LABEL_FATBOOT="boot" LABEL="boot" UUID="4BBD-D3E7" TYPE="vfat" PARTUUID="738a4d67-01"
/dev/mmcblk0p2: LABEL="rootfs" UUID="45e99191-771b-4e12-a526-0779148892cb" TYPE="ext4" PARTUUID="738a4d67-02"
/dev/sda1: UUID="50e407fc-37d8-4eb4-994d-ca6254c4e12e" TYPE="ext4"
```
Now, copy the number from /dev/sda1 if you are using external HDD. Otherwise, copy the number from /dev/mmcblk0p2. It’ll look like
UUID=“50e407fc-37d8-4eb4-994d-ca6254c4e12e”
Now, open and edit fstab to mount the drive on boot.
```console
pi@master ~> sudo nano /etc/fstab
```
Add the following line:
```console
UUID=78543e7a-4hy6-7yea-1274-01e0ff974531 /shared_dir ext4 defaults 0 2
```
All done, now we can mount the drive using the following command,
```console
pi@master ~> sudo mount -a
```
If it fails for some reason, reboot the master node and try again. If it is still not working double check the process and look for typo.

### Enable NFS Share


Now, we have a storage that can be shared but we need to install NFS server on master node in order to do so.
```console
pi@master ~> sudo apt install nfs-kernel-server -y
```
Now, edit /etc/exports and add the following line to export
```console
pi@master ~>sudo nano /etc/exports
```
```console
/shared_dir 10.10.0.0/24(rw,sync,no_root_squash,no_subtree_check)
```
Remember, depending upon the IP address schema used on your local network, the ip will be different for setup. For example, if your master node ip is 192.168.0.11, then you need to replace the ip with 192.168.0.0/24.

Now, we can update the configuration of the NFS kernel with the following command,
```console
sudo exportfs -a
```
One of the tasks for NFS to work remains unfinished which we will do in the next section.
