# Step - 8: Powering On and Off (Cluster)
Write a shell script with the following lines of codes and save it as clusterup.sh
```console
#!/bin/bash
sudo scontrol update NodeName=node[01-02] state=resume
sinfo
echo "Nodes up and running"
```

Now, you need to setup password less super user access to perform the next action. To do that efficiently, we need to create admin groups
```console
sudo groupadd admin
```
Now add your users (or yourself) to that group
```console
sudo usermod -a -G admin pi
```
Now edit sudoers file 
```console
sudo nano /etc/sudoers
```
Add these lines or edit accordingly
```console
# User privilege specification
root	ALL=(ALL:ALL) ALL
# Allow members of group sudo to execute any command
%sudo	ALL=(ALL:ALL) ALL
%admin	ALL=(ALL) ALL
# See sudoers(5) for more information on "#include" directives:
%admin	ALL=(ALL) NOPASSWD: ALL
```
REPEAT this process for each node. Starting from admin group add.
Write a shell script with the following lines of codes and save it as clusterdown.sh
```console
#!/bin/bash
echo "WiPi Cluster Shutdown"
echo "====================="
sudo scontrol update NodeName=node[01-02] state=down reason="power down"
ssh node01 "sudo halt"
ssh node02 "sudo halt"
echo "Nodes disconnected and shutting down"
echo "Do you want to shutdown master node too?"
echo "Press 'y' to continue or q to abort"
count=0
while : ; do
read -n 1 k <&1
if [[ $k = y ]] ; then
printf "\nShutting down Master Node\n"
sudo halt
elif [[ $k = q ]] ; then
printf "\nShutdown aborted\n" 
break
else
((count=$count+1))
printf "\nWrong Key Pressed\n"
echo "Press 'q' to abort"
fi
done
```

Now make these scripts executable using the following command
```console
pi@master ~>chmod a+x clusterup.sh
pi@master ~>chmod a+x clusterdown.sh
```
Each time you power on your cluster, run this script at the startup using the following command.
```console
pi@master ~>./clusterup.sh
```
Each time you need to power off your cluster, run this script at the end using the following command.
```console
pi@master ~>./clusterdown.sh
```
