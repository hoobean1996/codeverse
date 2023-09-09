#include "tools/idx/index_file.h"
#include <gtest/gtest.h>

TEST(CodeIndexer, IndexFile) {
  auto actual = tools::idx::CodeIndexer::File();
  EXPECT_TRUE(actual == "/Users/binhe");
  EXPECT_EQ(1, 1);
}