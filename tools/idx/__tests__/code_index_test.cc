#include "tools/idx/code_index.h"
#include <gtest/gtest.h>

TEST(CodeIndex, IndexFile) {
  auto actual = tools::idx::CodeIndex::IndexFile();
  EXPECT_TRUE(actual == "/Users/binhe/.codeverse.idx") << "actual = " << actual;
  EXPECT_EQ(1, 1);
}