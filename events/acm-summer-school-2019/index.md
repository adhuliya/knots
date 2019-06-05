ACM Summer School - 2019 (June 3, 4)
====================
Abstract Syntax Tree and the Clang 8.0.0 AST

Index
------------
1. [Session Plan](plan.html)
1. [Installing Clang/LLVM 8](../../compilers/llvm/get_started.html)
1. [Creating the virtual machine](build-vm.html).
1. [Useful Commands](#commands)
1. [Notes](#notes)


Useful Commands <a name="commands"></a>
----------------
### View the AST

   * With color,

        clang -Xclang -ast-dump -fsyntax-only test.c | less -r

   * Without the color,

        clang -Xclang -ast-dump -fsyntax-only -fno-color-diagnostics test.c | less

### View all the checkers in the system

    clang -cc1 -analyzer-checker-help

### View Control Flow Graph

    clang -c --analyze -Xanalyzer -analyzer-checker=debug.ViewCFG test.c
    
### View Call Graph

    clang -c --analyze -Xanalyzer -analyzer-checker=debug.ViewCallGraph test.c
    
### View Exploded Graph

    clang -c --analyze -Xanalyzer -analyzer-checker=debug.ViewExplodedGraph test.c
    
### Run scan-build

   * Use this command to get a bug/warning report of your program

        scan-build -V clang test.c

   * To invoke a specific checker,

        scan-build -V -enable-checker debug.checker01 clang -c test.c

### View existing checkers

    clang -cc1 -analyzer-checker-help

### Writing a checker from scratch,

   1. Goto the checker directory,
    
        cd $LLVM/llvm/tools/clang/lib/StaticAnalyzer/Checkers

   2. Create a cpp file,

        vi ACMChecker20.cpp

   3. Add the file name in the CMakeLists.txt (in the same dir)

        vi CMakeLists.txt

      For reference, you can search the file name `DeadStoresChecker.cpp` and add your file just below it.

   4. Edit the `Checkers.td` file,

        vi $LLVM/llvm/tools/clang/include/clang/StaticAnalyzer/Checkers/Checkers.td

   5. Goto the build directory,

        cd \$LLVM/build

   6. Build the project,

        ninja

### Edit-compile-run your checker
Assuming $LLVM refers the to directory housing the build/llvm folders,

   1. Goto the checker directory,
    
        cd $LLVM/llvm/tools/clang/lib/StaticAnalyzer/Checkers

   2. Edit a cpp file,

        vi ACMChecker20.cpp

   3. Goto the build directory,

        cd \$LLVM/build

   4. Build the project,

        ninja

   5. Now run the checker,

        clang -c --analyze -Xanalyzer -analyzer-checker=debug.checker20 test.c


Notes <a name="notes"></a>
-------------------
* These notes will be updated periodically with more details.



<div class="footer">
<br/>
&copy; Anshuman Dhuliya, Uday Kehdker
<br/>
</div>

