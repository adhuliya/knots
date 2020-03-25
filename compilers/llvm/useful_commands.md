Useful clang/llvm commands
===================

Useful Clang/LLVM commands and use cases.

1. [`clang (llvm frontend)`](#clang)
1. [`opt (llvm optimizer)`](#opt)
1. [`llc (llvm backend)`](#llc)

<a name="clang"></a>
## Clang (the LLVM frontend)

### Emit .ll (and .bc) files

    clang -S -emit-llvm test.c -o test.ll

Without `-S` this generates `.bc` file.

### Dump clang AST

    # Clang by default is a frontend for many tools; -Xclang is used to pass
    # options directly to the C++ frontend.
    clang -Xclang -ast-dump -fsyntax-only test.cc

### Run Slang on a C program `test.c`

    clang --analyze -Xanalyzer -analyzer-checker=debug.SlangGenAst test.c

### View the dot graph of the program's cfg

    clang --analyze -Xanalyzer -analyzer-checker=debug.SlangGenAst test.c

<a name="llvm-backend"></a>
## LLVM Notes

### Command to use to build LLVM minimally for Sparc/Ajit

    > $ CC=cc CXX=g++ \
       cmake -G Ninja \
         -DCMAKE_EXPORT_COMPILE_COMMANDS=On \
         -DBUILD_SHARED_LIBS=On \
         -DLLVM_ENABLE_ASSERTIONS=On \
         -DLLVM_TARGETS_TO_BUILD="X86;Sparc" \
         -DLLVM_ENABLE_SPHINX=Off \
         -DLLVM_ENABLE_THREADS=On \
         -DLLVM_INSTALL_UTILS=On \
         -DCMAKE_BUILD_TYPE=Debug \
         ../llvm-ajit-git/llvm-ajit

### Verify that the sparc target is indeed supported using `llc` command.

Look for the "Registered Targets" in the output of `llc --version`.


    > $ llc --version
    LLVM (http://llvm.org/):
      LLVM version 9.0.0
      DEBUG build with assertions.
      Default target: x86_64-unknown-linux-gnu
      Host CPU: skylake

      Registered Targets:
        sparc   - Sparc
        sparcel - Sparc LE
        sparcv9 - Sparc V9
        x86     - 32-bit X86: Pentium-Pro and above
        x86-64  - 64-bit X86: EM64T and AMD64

### How to compile a c file to sparc assembly?

    clang -emit-llvm -S -c sum.c -o sum.ll;
    llc sum.ll --march=sparc;

### How to view the DAG graphs?

REF: <https://llvm.org/docs/CodeGenerator.html#selectiondag-instruction-selection-process>

    llc --help-hidden | grep view-dag

    clang -emit-llvm -S -c sum.c -o sum.ll
    llc -fast-isel=false -view-dag-combine1-dags sum.ll

### How to generate sparc assembly code?

    clang -target sparc-unknown-linux-gnu -S test.c

### How to build a backend?

View IR generated at each step:

    clang -emit-llvm -S -c hello.c -o hello.ll
    llc hello.ll -print-after-all 2>&1 &> hello.log   

### How to view the list of instructions and registers?

    # cd to the lib/Target/Sparc directory containing Sparc.td file
    llvm-tblgen -I ../../../include Sparc.td -print-enums -class=Instruction  # for instructions
    llvm-tblgen -I ../../../include Sparc.td -print-enums -class=Register     # for registers

### How to see if the instruction matches a valid node is the DAG?

    # cd to the lib/Target/Sparc directory containing Sparc.td file
    llvm-tblgen -I ../../../include Sparc.td -gen-dag-isel -instrument-coverage | less
    # now search for any instruction and see SelectionDAG -> Instruction mapping.

