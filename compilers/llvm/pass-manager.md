LLVM Pass Manager
======================

All LLVM passes subclass the `Pass` class. The functionalities are
implemented by overriding virtual methods inherited from `Pass` class.
Depending on the kind of pass one is writing, one should inherit from the,

* ImmutablePass
* ModulePass
* CallGraphSCCPass
* FunctionPass
* LoopPass
* RegionPass
* BasicBlockPass
* MachineFunctionPass

Important Files
----------------------
* [`PassRegistry.def`](https://github.com/llvm-mirror/llvm/blob/master/lib/Passes/PassRegistry.def):
  Registers (and thus has list of) all the core passes that come with LLVM.
* [`PassBuilder.h`](https://llvm.org/doxygen/classllvm_1_1PassBuilder.html#details)
* [`PassManager.h`](https://github.com/llvm-mirror/llvm/blob/master/include/llvm/IR/PassManager.h)

Questions
----------------------
### Q1. A pass named `MyHello` is registered as follows,

    char MyHello::ID = 0;
    static RegisterPass<MyHello> X("myhello", "MyHello World Pass");

What mechanism goes into registering a pass using the syntax above?

Answer.
RegisterPass is a subclass of PassInfo that creates an instance of the pass (here `MyHello`)
and registers it in the PassRegistry database. It can be found in the file
`PassSupport.h` and its code is,

    template <typename PassName> Pass *callDefaultCtor() { return new PassName(); }
    
    //===---------------------------------------------------------------------------
    /// RegisterPass<t> template - This template class is used to notify the system
    /// that a Pass is available for use, and registers it into the internal
    /// database maintained by the PassManager.  Unless this template is used, opt,
    /// for example will not be able to see the pass and attempts to create the pass
    /// will fail. This template is used in the follow manner (at global scope, in
    /// your .cpp file):
    ///
    /// static RegisterPass<YourPassClassName> tmp("passopt", "My Pass Name");
    ///
    /// This statement will cause your pass to be created by calling the default
    /// constructor exposed by the pass.
    template <typename passName> struct RegisterPass : public PassInfo {
      // Register Pass using default constructor...
      RegisterPass(StringRef PassArg, StringRef Name, bool CFGOnly = false,
                   bool is_analysis = false)
          : PassInfo(Name, PassArg, &passName::ID,
                     PassInfo::NormalCtor_t(callDefaultCtor<passName>), CFGOnly,
                     is_analysis) {
        PassRegistry::getPassRegistry()->registerPass(*this);
      }
    };


References
----------------
1. [Pass Manager][1]
2. [LLVM Passes (list)][2]

[1]: http://llvm.org/docs/WritingAnLLVMPass.html#introduction-what-is-a-pass
[2]: https://llvm.org/docs/Passes.html
