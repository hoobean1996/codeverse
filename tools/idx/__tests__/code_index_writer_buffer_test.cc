#include "tools/idx/code_index_writer_buffer.h"
#include <fstream>
#include <gtest/gtest.h>

TEST(CodeIndexWriter, WriterBufferWrite) {
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
  EXPECT_TRUE(indexWriterBuffer->offset() == expectBytes);
}

TEST(CodeIndexWriter, WriterBufferWriteString) {
  auto indexWriterBuffer = new tools::idx::IndexWriterBuffer("./test.cc");
  std::string message = "hello world";
  int expectBytes = message.size();
  indexWriterBuffer->writeString(message);
  indexWriterBuffer->flush();
  EXPECT_TRUE(std::filesystem::exists("./test.cc"));
  std::fstream f("./test.cc");
  EXPECT_TRUE(f.is_open());
  char buf[20] = {0};
  f.read(buf, expectBytes);
  auto actualBytes = f.gcount();
  EXPECT_TRUE(actualBytes == message.size()) << "actualBytes = " << actualBytes;
  EXPECT_TRUE(indexWriterBuffer->offset() == expectBytes);
}

TEST(CodeIndexWriter, WriterBufferWriteByte) {
  auto indexWriterBuffer = new tools::idx::IndexWriterBuffer("./test.cc");
  char c = '0';
  indexWriterBuffer->writeByte(c);
  indexWriterBuffer->flush();
  EXPECT_TRUE(std::filesystem::exists("./test.cc"));
  std::fstream f("./test.cc");
  EXPECT_TRUE(f.is_open());
  char buf[20] = {0};
  f.read(buf, 1);
  auto actualBytes = f.gcount();
  EXPECT_TRUE(actualBytes == 1) << "actualBytes = " << actualBytes;
  EXPECT_TRUE(indexWriterBuffer->offset() == 1);
}

TEST(CodeIndexWriter, WriterBufferWriteTrigram) {
  auto indexWriterBuffer = new tools::idx::IndexWriterBuffer("./test.cc");
  uint32_t t = 123456;
  indexWriterBuffer->writeTrigram(t);
  indexWriterBuffer->flush();
  EXPECT_TRUE(std::filesystem::exists("./test.cc"));
  std::fstream f("./test.cc");
  EXPECT_TRUE(f.is_open());
  char buf[20] = {0};
  f.read(buf, 3);
  auto actualBytes = f.gcount();
  EXPECT_TRUE(actualBytes == 3) << "actualBytes = " << actualBytes;
  EXPECT_TRUE(indexWriterBuffer->offset() == 3);
}