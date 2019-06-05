Build Virtual Machine
====================
For [ACM Summer School 2019](index.html)

Steps
------------
1. Download and install [VirtualBox][1].
2. Download [lubuntu 18.04](https://lubuntu.net/lubuntu-18-04-bionic-beaver-released/).
3. Create a virtual machine with the following settings,
   1. fixed size 30 GB disk space.
   2. 1.9 GiB ram. (2 GiB ram may not work on 4 GiB ram systems)
4. [Build Clang/LLVM 8](#buildclang)
5. [Misc Utils](#utils)

Build Clang/LLVM
---------------------

Building Clang/LLVM on the VM is probably not a good idea. So build it outside the VM, in a similar environment. See [getting started](../../compilers/llvm/get_started.html).

Once the build has succeeded, take the following steps,

1. Copy the build and source directories to the VM. Your VM can access your system through the IP your system has over the current network. For example, if the laptop's current ip is `192.168.0.7` one can copy the content using the following command,

        rsync -avz -e ssh /src/dir user@remote.host:dst/dir

   Using `scp` instead, would replace symbolic links with the actual files one will be gasping that 15GiB had to be copied and 19GiB has been copied! Where did the extra 4GiB come from? :)

2. Now wherever one copies the build/source directories in the VM, one has to make sure that the absolute path that `cmake` enjoyed on your machine used for the building, is also available on this machine. One can achieve it by creating the symbolic links.

  So when I compiled it on my machine the absolute path was,

        /home/codeman/llvm-clang8

  And the VM had only two accounts `student` and `admin`. Hence after copying the `llvm-clang8` folder to the location `/home/student/school/`, I did the following as a student user,

        sudo mkdir /home/codeman
        sudo chown -R student:student /home/codeman
        cd /home/codeman
        ln -s /home/student/school/llvm-clang8 llvm-clang8


Important Utilities installed in the VM <a name="utils"></a>
-------------------

* `sudo apt install nginx-light` (for webpage)
* `sudo apt install git`
* `sudo apt install python` (python 2.7 needed by cmake)
* `sudo apt install libz3-dev` (needed by cmake)
* `sudo apt install libxml2-dev`
* `sudo apt install libedit-dev`
* `sudo apt install valgrind`
* `sudo apt install python-pygments`

Notes
-------

* Had to create a symbolic link `student@acm-summer-school-2019:/usr/lib/x86_64-linux-gnu$ sudo ln -s libxml2.so.2 libxml2.so`

* For most of these commands/packages, one will find useful help on the web. We will try to add more help material with time.

Resources
---------------
1. [VirtualBox][1]

[1]: https://www.virtualbox.org/wiki/Downloads
   
<div class="footer">
<br/>
&copy; Anshuman Dhuliya, Uday Kehdker
<br/>
</div>

