#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

namespace {
struct MyLegacyPass : public ModulePass {
  static char ID;
  MyLegacyPass() : ModulePass(ID) {}

  bool doInitialization(Module &M) override {
    errs() << "[MyLegacyPass] Doing nothing for initalization" << "\n";
    return false;
  }

  bool runOnModule(Module &M) override {
    errs() << "[MyLegacyPass] Runing on Module" << M.getName() << "\n";

    for (Function &F : M) {

      if (F.isDeclaration())
        continue;

      errs() << "[MyLegacyPass] Visiting Function: " << F.getName() << "\n";
    }

    // not modify the module
    return false;
  }

  void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.setPreservesAll();
  }
};
} // namespace

// register pass ID
char MyLegacyPass::ID = 0;

// register pass to opt
static RegisterPass<MyLegacyPass>
    X("my-legacy-pass", "My Legacy FunctionPass (LLVM 10 legacy PM)",
      /*only looks at CFG=*/false,
      /*is analysis=*/false);

// register pass to clang
static MyLegacyPass *_PassMaker = NULL;
static RegisterStandardPasses
    _RegPass1(PassManagerBuilder::EP_OptimizerLast,
              [](const PassManagerBuilder &, legacy::PassManagerBase &PM) {
                if (!_PassMaker) {
                  PM.add(_PassMaker = new MyLegacyPass());
                }
              }); // ** for -Ox
static RegisterStandardPasses
    _RegPass2(PassManagerBuilder::EP_EnabledOnOptLevel0,
              [](const PassManagerBuilder &, legacy::PassManagerBase &PM) {
                if (!_PassMaker) {
                  PM.add(_PassMaker = new MyLegacyPass());
                }
              }); // ** for -O0
