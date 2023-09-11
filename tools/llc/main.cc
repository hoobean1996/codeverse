#include "llvm/IR/LLVMContext.h"
#include <iostream>
#include <iterator>
#include <memory>

int main(int argc, char **argv) {
  std::unique_ptr<llvm::LLVMContext> context =
      std::make_unique<llvm::LLVMContext>();

  std::cout << "hello llc" << std::endl;
  return 0;
}