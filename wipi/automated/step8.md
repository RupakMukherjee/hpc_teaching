# Step - 8: Powering On and Off (Cluster)
Write a shell script with the following lines of codes and save it as clusterup.sh
```console
#!/bin/bash
sudo scontrol update NodeName=node[01-02] state=resume
sinfo
echo "Nodes up and running"
```
Each time you power on your cluster, run the following command at the startup,
```console
pi@master ~>clusterup
```
Each time you need to power off your cluster, run the following command,
```console
pi@master ~>clusterdown
```
If you wanr to check the temperatures of individual nodes use the following command,

```console
pi@master ~>tempcheck
```
