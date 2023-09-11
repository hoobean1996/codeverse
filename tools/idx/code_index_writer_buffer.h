#pragma once

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>

namespace tools::idx {

class IndexWriterBuffer {
  static const int kBufSize = 256 << 10;

public:
  IndexWriterBuffer() = delete;
  IndexWriterBuffer(const std::string &name);
  ~IndexWriterBuffer();
  void write(const char *x, int size);
  void flush();
  void writeByte(uint8_t x);
  void writeString(const std::string &);
  uint32_t offset();
  void writeTrigram(uint32_t t);
  void writeUint32(uint32_t x);

private:
  int left();

  std::string name_;
  std::fstream stream_;
  char buf_[kBufSize] = {0};
  int valid_;
  char tmp[8] = {0};
};
} // namespace tools::idx