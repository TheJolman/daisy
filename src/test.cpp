#include <iostream>

#include "llvm/IR/LLVMContext.h"

#include "test.hpp"

namespace test {

void test_libs() {
  llvm::LLVMContext context;
  std::cout << "LLVMContext created successfully!" << std::endl;
}
} // namespace test
