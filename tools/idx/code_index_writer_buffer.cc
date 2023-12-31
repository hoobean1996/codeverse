#include "tools/idx/code_index_writer_buffer.h"
#include <cstdint>
#include <fstream>
#include <glog/logging.h>
#include <stdint.h>

namespace tools::idx {
IndexWriterBuffer::IndexWriterBuffer(const std::string &name) : name_{name} {
  stream_ =
      std::fstream(name, std::ios::in | std::ios::out); // 尝试打开已存在的文件
  if (!stream_.is_open()) {
    LOG(ERROR) << "open stream failed, reason = " << strerror(errno);
    stream_.clear();
    stream_.open(name, std::ios::out); // 创建文件
    stream_.close();
    stream_.open(name, std::ios::in | std::ios::out); // 重新打开
  }
}

void IndexWriterBuffer::flush() {
  stream_.write(buf_, valid_);
  stream_.flush();
  valid_ = 0;
}

int IndexWriterBuffer::left() { return kBufSize - valid_; }

void IndexWriterBuffer::write(const char *x, int size) {
  int left = this->left();
  if (size > left) {
    flush();
    // if size > cap, write to the underlying file directly
    if (size > kBufSize) {
      stream_.write(x, size);
    }
  }
  memcpy(buf_ + valid_, x, size);
  valid_ += size;
}

void IndexWriterBuffer::writeByte(uint8_t x) {
  int left = this->left();
  if (left == 0) {
    flush();
  }
  buf_[valid_] = x;
  valid_++;
}

void IndexWriterBuffer::writeString(const std::string &message) {
  int left = this->left();
  if (left == 0) {
    flush();
    if (message.size() > kBufSize) {
      stream_.write(message.c_str(), message.size());
    }
  }
  memcpy(buf_ + valid_, message.c_str(), message.size());
  valid_ += message.size();
}

uint32_t IndexWriterBuffer::offset() {
  auto offset = stream_.tellp();
  // We should consider those data in the buffer before
  offset += valid_;
  if (offset > UINT32_MAX) {
    throw std::runtime_error("index is larger than 4GB");
  }
  return static_cast<uint32_t>(offset);
}

void IndexWriterBuffer::writeTrigram(uint32_t t) {
  int left = this->left();
  if (left < 3) {
    flush();
  }
  char tmp[3] = {static_cast<char>(t >> 16), static_cast<char>(t >> 8),
                 static_cast<char>(t)};
  memcpy(buf_ + valid_, tmp, 3);
  valid_ += 3;
}

void IndexWriterBuffer::writeUint32(uint32_t x) {
  int left = this->left();
  if (left < 4) {
    flush();
  }
  char tmp[4] = {static_cast<char>(x >> 24), static_cast<char>(x >> 16),
                 static_cast<char>(x >> 8), static_cast<char>(x)};
  memcpy(buf_ + valid_, tmp, 4);
  valid_ += 4;
}

IndexWriterBuffer::~IndexWriterBuffer() { flush(); }

} // namespace tools::idx