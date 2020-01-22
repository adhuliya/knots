SPARC V8 and (related) LLVM Notes
====================
Scalable Processor ARChitecture Version 8

* [`isa.txt`](isa.txt)
* [`llvm related notes`](#llvm)
* [SparcV8 Manual](../../mydata/git/ws/sparcv8-ajit-git/misc/references/sparcv8.pdf)
* [My Reference Material](../../mydata/git/ws/sparcv8-ajit-git/misc/references/)

Processor Overview
------------------

* **Principal Data Types**: SPARC is an instruction set architecture (ISA) with 32-bit integer and 32-, 64- and 128-bit IEEE Standard 754 floating-point as its principal data types.
* **Instructions**: 72 basic instruction operations, all encoded in 32-bit wide instruction formats (3 basic formats). The load/store instructions address a linear, 2^32-byte address space.
* **Memory Addressing Modes**: register + register or register + immediate
* **Modes**: user or supervisor. In supervisor mode, the processor can execute any instruction, including the privileged (supervisor-only) instructions. In user mode, an attempt to execute a privileged instruction will cause a trap to supervisor software. "User application" programs are programs that execute while the processor is in user mode.
* **Memory Model**: Total Store Order (TSO) with optional Partial Store Order (PSO). Machines that implement Strong Consistency (also called Strong Ordering) automatically support both TSO and PSO. See [Memory Consitency](https://homes.cs.washington.edu/~bornholt/post/memory-models.html).
* **Trap and Interrupt**: A trap is a vectored transfer of control to the operating system through a special trap table that contains the first 4 instruction of each trap handler (the base of the table is stored in Integer Unit's, trap base register (TBR)). 256 entries can fit into a trap table. A trap may be cause by an interrupt request.

<a name="llvm"></a>
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

Resources
-------------------

* [SparcV8 Manual](../../mydata/git/ws/sparcv8-ajit-git/misc/references/sparcv8.pdf)
* [My Reference Material](../../mydata/git/ws/sparcv8-ajit-git/misc/references/)


