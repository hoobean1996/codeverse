#pragma once

#include <string>

namespace core::io {
class FileWriter final {
public:
  FileWriter(const std::string &path, bool append = true);
  ~FileWriter();
  int append(const char *data, int32_t len, bool flush = false);
  int flush();
  void sync();
  void close();

private:
  int persist(const char *data, int32_t len);
  bool isBufferFull();
  static constexpr int32_t bufferSize_ = 65536;
  int32_t bufferOffset_ = 0;
  char buffer_[bufferSize_];
  int32_t fd_;
};
} // namespace core::io
