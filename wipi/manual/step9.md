# Step - 9: Password-less SSH

Now, we’ll set up password-less SSH on master node
```console
pi@master ~> ssh-keygen -t rsa
```
This would ask you for input, each time press enter key to proceed. After successful operation, the output will look like the following
```console
Generating public/private rsa key pair.
Enter file in which to save the key (/home/pi/.ssh/id_rsa): 
Created directory '/home/pi/.ssh'.
Enter passphrase (empty for no passphrase): 
Enter same passphrase again: 
Your identification has been saved in /home/pi/.ssh/id_rsa.
Your public key has been saved in /home/pi/.ssh/id_rsa.pub.
The key fingerprint is:
9b:98:c7:86:17:0a:1e:32:95:65:ee:1c:0f:48:48:ef pi@beira
The key's randomart image is:
+---[RSA 2048]----+
| .... o          |
|  .o *           |
|    = +          |
|   o o +         |
|  o E o S        |
|   + o * +       |
|    . = B        |
|       +         |
|                 |
+-----------------+
```
Now copy your rsa key to all the nodes
```console
pi@master ~> ssh-copy-id pi@node01
```
```console
pi@master ~> ssh-copy-id pi@node02
```
