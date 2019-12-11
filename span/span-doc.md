SPAN
====================
Synergistic Program Analyzer setup and use.

SPAN is a program analysis framework.
It combines different analyses synergistically
to enable mutually beneficial interactions.
It is currently targeted at C language (specifically C99).

To use SPAN's Python implementation,
there are broadly the following five requirements/steps,

1. [The `xdot` program to view CFG and other information](#xdot)
2. [Linux (preferably Ubuntu)](#linux)
3. [Python 3.6](#python) (the only version tested)
4. [The build of SPAN (its tarball)](#span-build)
5. [Test and use SPAN](#testspan)

In addition to the above steps, you can add SPAN support
to Clang/LLVM.
(This is an optional exercise, but this will give you the flexibility to
experiment more.) To add the support follow the following two steps,

1. [Build your own Clang/LLVM](../compilers/llvm/get_started.html)
2. Add SLANG checkers to the Clang/LLVM build.
   Slang Checkers convert Clang AST to SPAN IR and
   Span bug reports to Clang bug reports.
   [Slang github repo](https://github.com/adhuliya/SLANG) contains the checker sources and
   has a [README.md](https://github.com/adhuliya/SLANG/blob/master/README.md)
   that details how to add SLANG to LLVM/Clang build.

<a name="xdot"></a>
## The `xdot` program to view CFG and other information
The `xdot` program is used to render graphviz dot files.
It is used to show CFG of functions
with statements as SPAN IR. It is also used for other
pictorial details of the system.

<a name="linux"></a>
## Linux (preferably Ubuntu)
The whole development of SPAN has taken place on
`Ubuntu 18.04.2 x86_64-linux-gnu`.
Although we don't use any exclusive features of the system,
if SPAN crashes on your system, this information could be a good clue.
That said, the system should run on any decent Linux distribution
with target triple `x86_64-linux-gnu`.

<a name="python"></a>
## Python 3.6
The current version has been developed in Python 3.6.7 and it
definitely cannot run on version 3.5 or lower.
In the SPAN distribution tarball we compile some
modules specifically `span.sys.*` to their respective `.so`
files using `Cython 0.29.13` on a `x86_64-linux-gnu` machine.

**Therefore we recommend using Python 3.6 only.**
The sub-versions 3.6.7, 3.6.9 have been tested.

<a name="span-build"></a>
## The build of SPAN (its tarball)
Currently we are sharing the implementation selectively as the project
is under active development and not ready for a release.
Usually the file shared will be named `span-tool.tgz` or similar.
[Download here](https://drive.google.com/open?id=11EYDQnjP0bTsUSs4aip6wEh75yEnwScm)

<a name="testspan"></a>
## Test and use SPAN
Please make sure that all the requirements are met before
proceeding with the use.

1. Untar SPAN distribution tarball named `span-tool.tgz`,

        tar -xzf span-tool.tgz

   This creates a folder `span-tool` which contains SPAN's
   driver script `main.py` along with the rest of the implementation.
   Change into the directory,

        cd span-tool

2. Run a test. View the CFG of a program,
       
        python3.6 ./main.py view dot tests/automated/spanTest001.c.spanir

3. Run another test. Run an analysis,
       
        python3.6 ./main.py analyze /+PointsToA/ tests/automated/spanTest001.c.spanir

4. If the requirements have been met the tests should run okay.
   You can use `span-tool/main.py` driver script
   to invoke SPAN. Type `./main.py help` to see the commands and their
   purpose as supported by SPAN.

If you have successfully followed the instructions till this point,
you should be able to use SPAN's Python implementation.

[1]: http://adhuliya.pythonanywhere.com/compilers/llvm/get_started.html
[2]: https://github.com/adhuliya/SLANG
[3]: https://github.com/adhuliya/SLANG/blob/master/README.md

<div class="footer"> <br/> &copy; Anshuman Dhuliya <br/> </div>

