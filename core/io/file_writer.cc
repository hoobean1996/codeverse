
#include <cassert>
#include <cstring>
#include <filesystem>
#include <sys/fcntl.h>
#include <unistd.h>

#include "core/io/file_writer.h"

namespace core::io {
FileWriter::FileWriter(const std::string &path, bool append) {
  int mode = O_CREAT | O_WRONLY;
  if (append) {
    mode |= O_APPEND;
  } else {
    mode |= O_TRUNC;
  }
  if (access(path.c_str(), F_OK) != F_OK) {
    int idx = (int)path.rfind("/");
    auto dir = path.substr(0, idx);
    std::filesystem::create_directories(dir.c_str());
  }
  fd_ = open(path.c_str(), mode, 0644);
  assert(access(path.c_str(), F_OK) == F_OK);
}

FileWriter::~FileWriter() { sync(); }

int FileWriter::append(const char *data, int32_t len, bool flush) {
  int32_t dataOffset = 0;
  assert(data != nullptr);
  if (len == 0) {
    return 0;
  }
  int remainBufferSize = bufferSize_ - bufferOffset_;
  if (len < remainBufferSize) {
    memcpy(buffer_ + bufferOffset_, data + dataOffset, len);
    bufferOffset_ += len;
    dataOffset += len;
  } else {
    memcpy(buffer_, data, remainBufferSize);
    len -= remainBufferSize;
    bufferOffset_ += remainBufferSize;
    dataOffset += remainBufferSize;
    persist(buffer_, bufferSize_);

    while (len > 0) {
      if (isBufferFull()) {
        persist(buffer_, bufferSize_);
      }
      int needCopy = std::min(len, bufferSize_ - bufferOffset_);
      memcpy(buffer_ + bufferOffset_, data + dataOffset, needCopy);
      dataOffset += needCopy;
      len -= needCopy;
      bufferOffset_ += needCopy;
      if (len == 0) {
        break;
      }
    }
  }

  if (flush) {
    persist(buffer_, bufferOffset_);
  }
  return 0;
}

int FileWriter::flush() {
  if (bufferOffset_ > 0) {
    persist(buffer_, bufferOffset_);
  }
  return 0;
}

void FileWriter::sync() {
  flush();
  fsync(fd_);
}

void FileWriter::close() {
  flush();
  ::close(fd_);
  fd_ = -1;
}

int FileWriter::persist(const char *data, int32_t len) {
  auto ret = write(fd_, data, len);
  assert(ret == len);
  bufferOffset_ = 0;
  return 0;
}

bool FileWriter::isBufferFull() { return bufferOffset_ == bufferSize_; }
} // namespace core::io