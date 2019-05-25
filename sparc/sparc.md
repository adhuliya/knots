SPARC V8 Notes
====================
Scalable Processor ARChitecture Version 8

Processor Overview
------------------

* **Principal Data Types**: SPARC is an instruction set architecture (ISA) with 32-bit integer and 32-, 64- and 128-bit IEEE Standard 754 floating-point as its principal data types.
* **Instructions**: 72 basic instruction operations, all encoded in 32-bit wide instruction formats (3 basic formats). The load/store instructions address a linear, 2^32-byte address space.
* **Memory Addressing Modes**: register + register or register + immediate
* **Modes**: user or supervisor. In supervisor mode, the processor can execute any instruction, including the privileged (supervisor-only) instructions. In user mode, an attempt to execute a privileged instruction will cause a trap to supervisor software. "User application" programs are programs that execute while the processor is in user mode.
* **Memory Model**: Total Store Order (TSO) with optional Partial Store Order (PSO). Machines that implement Strong Consistency (also called Strong Ordering) automatically support both TSO and PSO. See [Memory Consitency](https://homes.cs.washington.edu/~bornholt/post/memory-models.html).
* **Trap and Interrupt**: A trap is a vectored transfer of control to the operating system through a special trap table that contains the first 4 instruction of each trap handler (the base of the table is stored in Integer Unit's, trap base register (TBR)). 256 entries can fit into a trap table. A trap may be cause by an interrupt request.

Resources
-------------------

* [SparcV8 Manual](../../mydata/git/ws/sparcv8-ajit-git/misc/references/sparcv8.pdf)
* [My Reference Material](../../mydata/git/ws/sparcv8-ajit-git/misc/references/)
