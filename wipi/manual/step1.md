# Step - 1: Prepare the Micro-SD cards for Raspberry Pi OS
Download latest version of Raspbian Lite OS by using your MacOS/Linux terminal and type

```console
wget https://downloads.raspberrypi.org/raspbian_lite_latest -O raspbian_lite_latest.zip
```
Now extract the zipped file
```console
unzip raspbian_lite_latest.zip
```
Check the directory for the contents from the extraction and find the name of the disk image file with extension .img (e.g. 2020-02-13-raspbian-buster-lite.img)
Now insert a SD/Micro-SD card inside your laptop and check for the attached devices/mount point of the card For MacOs:
```console
diskutil list
```
For Linux:
```console
lsblk
```
Let’s say it is attached to dev/disk2. First unmount the disk,
```console
diskutil unmountDisk /dev/disk2
```
For linux (use "sudo" if necessary)
```console
umount /dev/disk2
```
Then flash the image to memory card
```console
sudo dd if=2020-02-13-raspbian-buster-lite.img of=/dev/disk2
```
If successful, a drive will be mounted under the name boot. Raspberry Pis usually comes with disabled SSH configuration. We don’t want that. To enable it create an empty file inside the boot directory. 

For MacOS, you can find it under /Volumes/boot
```console
cd /Volumes/boot/
```
Now, type
```console
touch ssh 
```
Now, we have successfully configured a Raspbian Lite OS having ssh enabled. 

Let’s eject the card from the Mac
```console
cd ..
```
```console
diskutil unmountDisk /dev/disk2
```

Repeat this process for all three memory cards. Now insert the cards to your Raspberry Pis. Remember to mark the master node to separate it from others.

Now plug in all the three memory cards in to the storage port of Raspberry Pis. Then connect the network cables(CAT5/6/6A) to in the ethernet port of Pis. Do not power on the Pis at the moment.
