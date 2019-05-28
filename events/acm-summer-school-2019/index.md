ACM Summer School - 2019 (June 2-3)
====================
Abstract Syntax Tree and its implementation in Clang

Index
------------
1. [Creating the virtual machine](build-vm.html).
2. [Installing Clang/LLVM 8](../../compilers/llvm/get_started.html)



Side Notes
-------------------
* Copying `llvm-clang8/` folder (contains llvm's source and build directories) using `scp ...` replaced all the symbolic links with copies of the files/directories! Instead use `rsync -avz -e ssh /src/dir user@remote.host:dst/dir`.
* Had to create a symbolic link `student@acm-summer-school-2019:/usr/lib/x86_64-linux-gnu$ sudo ln -s libxml2.so.2 libxml2.so`
* packages installed explicitly: `libxml2-dev`, `libedit-dev`, `valgrind`



   
<div class="footer">
<br/>
&copy; Anshuman Dhuliya, Uday Kehdker
<br/>
</div>

