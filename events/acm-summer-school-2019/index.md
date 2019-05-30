ACM Summer School - 2019 (June 2-3)
====================
Abstract Syntax Tree and its implementation in Clang

Index
------------
1. [Installing Clang/LLVM 8](../../compilers/llvm/get_started.html)
1. [Creating the virtual machine](build-vm.html).
1. [Important Commands](#commands)


Commands <a name="commands"></a>
----------------
### View the AST

    $ clang -Xclang -ast-dump -fsyntax-only test.c

### Run scan-build

    $ scan-build -V clang test.c

### Edit-compile-run your checker

    # STEP 1: goto the checkers dir
    $ acm-goto-checkers-dir

    # STEP 2: edit the appropriate checker
    $ vi ACMCheckers01.cpp    # edit the appropriate file
     
    # STEP 3: goto the build dir and rebuild the project
    $ acm-goto-build-dir
    $ ninja

    # REPEAT STEP 1-3 until the compilation is correct.

    # STEP 4: goto the workdir and run the checker
    $ acm-goto-workdir
    $ clang -c --analyze -Xanalyzer -analyzer-checker=debug.checker01 test.c

### View existing checkers

    clang -cc1 -analyzer-checker-help

### View Control Flow Graph

    $ clang -c --analyze -Xanalyzer -analyzer-checker=debug.ViewCFG test.c
    


Side Notes
-------------------
* Copying `llvm-clang8/` folder (contains llvm's source and build directories) using `scp ...` replaced all the symbolic links with copies of the files/directories! Instead use `rsync -avz -e ssh /src/dir user@remote.host:dst/dir`.
* Had to create a symbolic link `student@acm-summer-school-2019:/usr/lib/x86_64-linux-gnu$ sudo ln -s libxml2.so.2 libxml2.so`
* packages installed explicitly: `libxml2-dev`, `libedit-dev`, `valgrind`, `python-pygments`



   
<div class="footer">
<br/>
&copy; Anshuman Dhuliya, Uday Kehdker
<br/>
</div>

