LLVM Backend
====================

Important Files
--------------------
* `/home/codeman/itsoflife/mydata/local/packages-live/llvm-clang8.0.1/llvm/lib/Target/Sparc/SparcRegisterInfo.td` : Contains information on all registers.
* <https://llvm.org/devmtg/2014-04/PDFs/Talks/Building%20an%20LLVM%20backend.pdf>:
Good tutorial on creating a basic custom backend.

## Backend big picture
Pipeline structure of the backend:

    IR --> SelectionDAG --> MachineDAG --> MachineInstr --> MCInst

Transforms your program many times-Same program,
few different representations-Different instruction namespaces
Check it out (IR and MI only):

    llc foo.ll  -print-after-all 2>&1 > foo.log

References
-------------------
1. [Writing an LLVM Backend](https://llvm.org/docs/WritingAnLLVMBackend.html)
2. [The LLVM Target-Independent Code Generator](https://llvm.org/docs/CodeGenerator.html)
3. [TableGen](https://llvm.org/docs/TableGen/index.html)
