#include <print>

#include "llvm/IR/LLVMContext.h"

#include "test.hpp"

namespace test {

void test_libs() {
  llvm::LLVMContext context;
  std::println("LLVMContext created successfully!");
}
} // namespace test
