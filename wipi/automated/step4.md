# Step - 4: Setting Up the Worker Nodes
We already have the IPs for worker nodes [See Step - 2](#step---2-network-setup). Now let's prepare them one by one. Log into node01 by using the following command,
```console
ssh pi@10.10.0.12
```
Upon connection use password *raspberry*. (Note: it is the default password)

Now, use the following command to download the shell script for worker node
```console
pi@raspberrypi~$ wget https://raw.githubusercontent.com/sayanadhikari/wipi/automated/deployment/node_deployment.sh
```
The script you just downloaded should be in */home/pi/* with the name *node_deployment.sh*. Now run the script to prepare the worker node.
```console
pi@raspberrypi~$ sudo bash ./node_deployment.sh node01
```
At the end of the script execution, the system will automatically reboot.

Now repeat the process for rest of the worker nodes. Login to rest of the worker nodes using their respective ips (information available at Step-2). Also, remember to replace “node01” word in the last command with their respective node numbers. 
