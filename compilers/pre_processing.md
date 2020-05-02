Pre-Processor
=============

Refer to: [C Pre Processor](https://gcc.gnu.org/onlinedocs/gcc-2.95.3/cpp_1.html),
to learn how pre-processing works.

TODO: see how-to build and use PCH (pre compiled header)


## Some useful `clang` options.

    -I <dir>                Add directory to include search path
    -C                      Include comments in preprocessed output
    -c                      Only run preprocess, compile, and assemble steps
    -dD                     Print macro definitions in -E mode in addition to normal output
    -dependency-dot <value> Filename to write DOT-formatted header dependencies to
    -dependency-file <value>
                            Filename (or -) to write dependency output to
    -dI                     Print include directives in -E mode in addition to normal output
    -dM                     Print macro definitions in -E mode instead of normal output
    -D <macro>=<value>      Define <macro> to <value> (or 1 if <value> omitted)
    -H                      Show header includes and nesting depth
    -I-                     Restrict all prior -I flags to double-quoted inclusion and remove 
                            current directory from include path

    -P, --no-line-commands  Disable linemarker output in -E mode

    -U <macro>, --undefine-macro <arg>, --undefine-macro=<arg>
                            Undefine macro <macro>

    -Xpreprocessor <arg>    Pass <arg> to the preprocessor

Note: 
1. Unable to use `-dependency-dot` and `-dependency-file` option above.  No file is generated.
2. What is `-I-` used for?


## Input program for the rest of the article

Input program `test.cc`,

    // test.cc
    int main(int argc, char** argv) {
      int a = VAL + DAL;
      return a+argc;
    }


### How to give a value to a macro via command line?

    clang -D VAL=20 -D DAL=30 -E test.cc   



