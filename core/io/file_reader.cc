#include "core/io/file_reader.h"
#include <cassert>
#include <fcntl.h>
#include <filesystem>
#include <stdexcept>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <unistd.h>

namespace core::io {
FileReader::FileReader(const std::string &path) {
  if (!std::filesystem::exists(path)) {
    throw std::runtime_error("the file does not exist, path = " + path);
  }
  fd_ = open(path.c_str(), O_RDONLY);
  assert(fd_ >= 0);
}

FileReader::~FileReader() {
  if (fd_ != -1) {
    close(fd_);
    fd_ = -1;
  }
}

int FileReader::read(void *buf, int32_t count, int32_t offset) const {
  if (buf == nullptr) {
    throw std::runtime_error("the input buffer for read can't be nullptr");
  }
  if (fd_ == -1) {
    throw std::runtime_error("the fd is invalid");
  }
  int cnt = pread(fd_, buf, count, offset);
  if (cnt != count) {
  }
  return cnt;
}

} // namespace core::io