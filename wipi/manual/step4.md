# Step - 4: Setting Up the Worker Nodes
We already have the IPs for worker nodes [See Step - 2](#step---2-network-setup). Now let's prepare them one by one. Log into node01 by using the following command,
```console
ssh pi@10.10.0.12
```
It will ask for a password, use the default one “raspberry.” It will open up a terminal, the same that you had for the master. Now configure the node using 
```console
pi@raspberrypi~$ sudo raspi-config
```
It opens up the config utility. Next you should set the locale, timezone, and wifi country. Then, select finish and press enter to exit the utility. Exactly same what you did for the master node, except the password. 

Now let’s update the hostname.
```console
pi@raspberrypi ~> sudo hostname node01
```
Change "raspberrypi" to “node01” by editing the hostname file.
```console    
pi@raspberrypi ~> sudo nano /etc/hostname  
```
Now edit the hosts file
```console
pi@raspberrypi ~> sudo nano /etc/hosts  
```
Add the following
```console
127.0.1.1      node01
10.10.0.11     master
10.10.0.12     node01
10.10.0.13     node02
```
Next,

System Update and Upgrade
```console
pi@raspberrypi ~> sudo apt-get update && sudo apt-get upgrade
```
We can enable network time update here, just like master
```console
pi@raspberrypi ~> sudo apt install ntpdate -y
```
Now reboot the system to apply the effect of changes that have been made so far.
```console
pi@raspberrypi ~> sudo reboot
```

After the reboot, login to the system again.

### NFS MOUNT

To access the storage that we shared on master node from individual worker nodes, we need to install and configure NFS services.
```console
sudo apt install nfs-common -y
```
Now, we need to create the same directory in order to mount the storage.
```console
pi@node01 ~> sudo mkdir /shared_dir 
pi@node01 ~> sudo chown nobody.nogroup /shared_dir 
pi@node01 ~> sudo chmod -R 777 /shared_dir
```
To allow automatic mounting we need to edit the fstab file for each node. Use the following command to edit,
```console
pi@node01 ~> sudo nano /etc/fstab
```
And add the following line below the existing texts
```console
10.10.0.11:/shared_dir    /shared_dir    nfs    defaults   0 0
```
Now, use the following to finish the mounting
```console
pi@node01 ~> sudo mount -a
```
To check whether the shared storage is working. Open a new terminal window and login to your master node. Then create a blank file. 
```console
ssh pi@10.10.0.11
```
```console
pi@master ~> cd /shared_dir
pi@master ~> touch nas_test.dat
```
Now go back to the node01 terminal and check the contents of your shared directory
```console
pi@node01 ~> cd /shared_dir
pi@node01 ~> ls
```
If you see nas_test.dat file here, means you have successfully created a Network File System. If you can’t see, you may have to reboot the node once.

Now repeat the process for rest of the worker nodes. Remember to replace “node01” word with their respective node numbers.
