# Step - 2: Network Setup

To do this part, you need a wireless router with DHCP enabled. The [Dynamic Host Configuration Protocol (DHCP)](https://en.wikipedia.org/wiki/Dynamic_Host_Configuration_Protocol) will allocate IPs as soon as we connect our Raspberry Pis to the network. If you have network switch, first plugin the other end of the ethernet cables connected to Pis. Now plugin one extra cable from switch to Wireless router. Physical network complete. Now power on the wireless router and the switch. 

**Note**: *If you do not have the network switch, then connect the network cables directly to the wireless router.*

Now, login to the wireless router management page using browser. If your laptop is connected to the same network, just type the gateway IP. e.g. if you IP is 10.10.0.10, usually your gateway is 10.10.0.1, it's really simple. If you have trouble getting into the management page look for proper information on the router body. It's written somewhere on the body. After getting into the management page, go to the connected devices page and keep it open.

## Setting up Wireless Router for the first time
:warning: Instructions are applicable for TP-Link Routers. :clapper: [Video instruction](https://youtu.be/Cg_gGECGLiY)

Similar informations are available for other manufactures:
- D-Link Routers: [Click Here](https://eu.dlink.com/uk/en/support/faq/routers/mydlink-routers/dir-810l/how-do-i-set-up-and-install-my-router) :point_left:
- NETGEAR Routers: [Click Here](https://kb.netgear.com/119/How-do-I-set-up-and-install-my-NETGEAR-router):point_left:

If you want to use the router as modem, you need to follow the instruction given in the picture below:
![Tp-link modem setup](/images/tp-link-3.png)
![Tp-link modem setup 2](/images/tp-link-2.png)
:warning: If you already have a modem and want use this device as a router only, follow the instruction below:
![Tp-link modem setup 3](/images/tp-link-1.png)
Now, power on the master node first by connecting the USB-C cable from a power outlet (or the 6-port USB power supply) and keep refresing the page. If everything goes well, you should see a new device named **raspberrypi** connected to the network. Now note down the IPV4 address associated with it.

Next, **power on** one of the compute nodes and do the same (note it as node01). Repeat the process for all the compute nodes. At the end, you should have something similar to the following information with you:

* master IPV4: **10.10.0.11**
* node01 IPV4: **10.10.0.12**
* node02 IPV4: **10.10.0.13**

Now, try to ping each of the Pis from your computer terminal and wait for couple of seconds, then kill it by pressing  Ctrl + c.
```console
ping 10.10.0.11
```
You should get an output very similar to the following
```console
PING 10.10.0.11: 56 data bytes
64 bytes from 10.10.0.11: icmp_seq=0 ttl=59 time=1.947 ms
64 bytes from 10.10.0.11: icmp_seq=1 ttl=59 time=3.582 ms
64 bytes from 10.10.0.11: icmp_seq=2 ttl=59 time=3.595 ms
64 bytes from 10.10.0.11: icmp_seq=3 ttl=59 time=3.619 ms
...
--- 10.10.0.11 ping statistics ---
6 packets transmitted, 6 packets received, 0.0% packet loss
round-trip min/avg/max/stddev = 1.947/3.317/3.635/0.614 ms
```

**Note**: *If you have options to reserve IP on your wireless router management page, it is advised to do so for all the Pis. However, it is not mandetory.*
