#pragma once

#include <cstdint>
#include <string>

namespace tools::idx {

class IndexReader {
public:
  IndexReader() = delete;
  ~IndexReader() = default;
  IndexReader(const IndexReader &) = delete;
  IndexReader &operator=(const IndexReader &) = delete;
  explicit IndexReader(const std::string &indexFile) : indexFile_{indexFile} {}

  void open();
  char *slice(int offset, int size);
  uint32_t uint32(int offset);

private:
  bool verbose_;
  uint32_t path_data_;
  uint32_t name_data_;
  uint32_t post_data_;
  uint32_t name_index_;
  uint32_t post_index_;
  size_t num_name_;
  size_t num_post_;

  std::string indexFile_;
  int fd_;
};
} // namespace tools::idx