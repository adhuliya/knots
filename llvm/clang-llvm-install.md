Clang LLVM Installation Ubuntu
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


Description
-----------------

To download LLVM/CLANG 6 goto [this link][2]. Follow the instructions at the [clang.llvm.org][1] to figure out what to download. I downloaded the `lld` and the `lldb` too and placed it in the `llvm/tools` directory with their folder name `lld` and `lldb` respectively.

FAQs
----------------

### Q. What prerequisites I installed explicitly?

    # removes `editline/readline.h` file not found error
    sudo apt-get install libedit-dev

    sudo apt-get install doxygen
    sudo apt-get install swig

Resources
------------------------

* [Clang Getting Started][1]

[1]: http://clang.llvm.org/get_started.html
