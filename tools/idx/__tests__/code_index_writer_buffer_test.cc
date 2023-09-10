#include "tools/idx/code_index_writer_buffer.h"
#include <fstream>
#include <gtest/gtest.h>

TEST(CodeIndexWriter, WriterBuffer) {
  auto indexWriterBuffer = new tools::idx::IndexWriterBuffer("./test.cc");
  std::string message = "hello world";
  int expectBytes = message.size();
  indexWriterBuffer->write(message.c_str(), expectBytes);
  indexWriterBuffer->flush();

  EXPECT_TRUE(std::filesystem::exists("./test.cc"));

  std::fstream f("./test.cc");
  EXPECT_TRUE(f.is_open());
  char buf[20] = {0};
  f.read(buf, expectBytes);
  auto actualBytes = f.gcount();
  EXPECT_TRUE(actualBytes == message.size()) << "actualBytes = " << actualBytes;
}