SPAN
====================
Synergistic Program Analysis setup and use.

SPAN is a program analysis framework.
It combines different analyses synergistically
to enable mutually beneficial interactions.
It is currently targeted at C language (specifically C99).

To use SPAN entirely, there are broadly the following requirements,

1. [The build of SPAN (its tarball)](#span-build)
2. [Linux (preferably Ubuntu)](#linux)
3. [Python 3.6.7](#python) (the only version tested, it may work with >=3.6 as well) 
4. [Local build of Clang/LLVM 8.0.1](#clangsetup) (the recent official release)
5. [SLANG Checkers for Clang/LLVM 8.0.1](#slang)
6. [The `xdot` program to view CFG and other information](#xdot)

# How to use?
Please make sure that all the requirements are met before
proceeding with the use.

1. Untar SPAN distribution tarball named `span-tool.tgz`,

        tar -xzf span-tool.tgz

2. Run automated tests,

        cd span-tool
        cd tests/automated
        ../../main.py test all

  All the test cases should pass. Currently these tests give a 46%
  code coverage and test some essential SPAN setup conditions as well.

3. If tests run okay, now one can use `span-tool/main.py` driver script
   to invoke SPAN. Type `./main.py help` to see the commands and their
   purpose supported by SPAN.

<a name="span-build"></a>
## The build of SPAN (its tarball)
Currently we are sharing the implementation selectively as the project
is under active development and not ready for a release.

<a name="linux"></a>
## Linux (preferably Ubuntu)
The whole development of SPAN has taken place on
`Ubuntu 18.04.2 x86_64-linux-gnu`.
Although we don't use any exclusive features of the system,
if SPAN crashes on your system, this information could be a good clue.
That said, the system should run on any decent Linux distribution
with target triple `x86_64-linux-gnu`.

<a name="python"></a>
## Python 3.6.7
The current version has been developed in Python 3.6.7 and it
definitely cannot run on version 3.5 or lower.
In the SPAN distribution tarball we compile some
modules specifically `span.sys.*` to their respective `.so`
files using `Cython 0.29.13` on a `x86_64-linux-gnu` machine.

<a name="clangsetup"></a>
## Local build of Clang/LLVM 8.0.1
This [step-by-step guide][1] shows how to build Clang/LLVM.

<a name="slang"></a>
## SLANG Checkers for Clang/LLVM 8.0.1
Slang Checkers convert Clang AST to SPAN IR and
Span bug reports to Clang bug reports.
[Slang github repo][2] contains the checker sources and
has a [README.md][3] that details how to add SLANG to
LLVM/Clang build.

<a name="xdot"></a>
## The `xdot` program to view CFG and other information
The `xdot` program is used to render graphviz dot files.
It is used to show CFG of functions
with statements as SPAN IR. It is also used for other
pictorial details of the system.

[1]: http://adhuliya.pythonanywhere.com/compilers/llvm/get_started.html
[2]: https://github.com/adhuliya/SLANG
[3]: https://github.com/adhuliya/SLANG/blob/master/README.md

<div class="footer"> <br/> &copy; Anshuman Dhuliya <br/> </div>

