#pragma once

#include "tools/idx/code_index.h"
namespace tools::idx {

class IndexReader {
public:
  IndexReader() = delete;
  ~IndexReader() = default;
  IndexReader(const IndexReader &) = delete;
  IndexReader &operator=(const IndexReader &) = delete;
  // IndexReader: Create a IndexReader from a CodeIndexer.
  explicit IndexReader(CodeIndex *indexer) : indexer_{indexer} {}
  // Open: open the underlying file, and ready to read.
  void Open();

  char Slice(int offset, int size);
  uint32_t Uint32(int offset);

private:
  bool verbose_;
  uint32_t path_data_;
  uint32_t name_data_;
  uint32_t post_data_;
  uint32_t name_index_;
  uint32_t post_index_;
  size_t num_name_;
  size_t num_post_;

  CodeIndex *indexer_;
  int fd_;
};
} // namespace tools::idx