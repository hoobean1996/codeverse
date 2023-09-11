#include "core/io/file_reader.h"
#include <cstdlib>
#include <filesystem>
#include <gtest/gtest.h>

TEST(IO, FileReader) {
  auto dir = std::getenv("TEST_SRCDIR");
  auto workspace = std::getenv("TEST_WORKSPACE");
  auto dataFile =
      std::string(dir) + "/" + workspace + "/core/io/__tests__/data.txt";
  auto reader = core::io::FileReader(dataFile);
  char data[1024];

  {
    int n = reader.read(data, 1024);
    auto content = std::string(data, n);
    EXPECT_TRUE(n > 0) << "dir = " << dir << ", workspace = " << workspace
                       << ", n = " << n << ", data = " << content;
  }

  {
    int n = reader.read(data, 1024, 5);
    auto content = std::string(data, n);
    EXPECT_TRUE(content == " world");
  }
}