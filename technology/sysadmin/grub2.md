Grub 2
========================

Important Files/Dirs
--------------------

* `/etc/default/grub` : the default settings (e.g. default boot os)
* `/etc/grub.d` : add or re-arrange menu entries here
* `/etc/grub.d/README` : read this file
* `/boot/grub/grub.cfg` : the file generated with `update-grub` cmd


Important Commands
-----------------------

* `sudo update-grub`
* `sudo grub-install <target>` 

FAQs
----------------

### Q. How to change menu entry order?
Go to `/etc/grub.d`. The executable scripts with two digit numbers, e.g. `10_linux` contribute to the menu entries in the startup grub menu. The first two digits in their name decide the order in which the menu entries are displayed.

### Q. How to delete a menu entry?
Locate the script in the `/etc/grub.d` that generates the menu entry and turn its execution bit off (i.e. run `sudo chomd -x <filename>` on it).

### Q. How Grub2 names partitions?
The first partition of the first disk is named as `(hd0,1)`. Notice the `1`.

### Q. How to recover Grub2?
When unable to boot into the current system, take a live linux CD and live boot from it. Open a command prompt and do the following (assuming root partitions id `/dev/sda1` and grub2 is to be installed on `/dev/sda`),

    sudo mount /dev/sda1 /mnt       # mount root partition
    sudo grub-install --root-directory=/mnt /dev/sda


If the above doesn't work, do the following (from live cd)


    sudo mount /dev/sda1 /mnt       # mount root partition
    sudo mount /dev/sda2 /mnt/boot  # if /boot is separate partition
    sudo mount --bind /dev /mnt/dev # bind the devices
    sudo chroot /mnt

    dpkg-configure grub-pc

    Ctrl-D # to exit from chroot environment

    sudo unmount /mnt/boot          # if mounted
    sudo unmount /mnt/dev
    sudo umount /mnt



        




Resources
------------------------

* [Grub2 Tutorial][1]
* [Official Ubuntu Grub2 Wiki][2]

[1]: https://www.dedoimedo.com/computers/grub-2.html "Grub2 Tutorial Dedoimedo"
[2]: https://wiki.ubuntu.com/Grub2
