#pragma once

#include "tools/idx/code_index_writer_buffer.h"
#include "tools/idx/post_entry.h"
#include "tools/idx/sparse_set.h"
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <string>
#include <sys/fcntl.h>
#include <unistd.h>

namespace tools::idx {

const int kMaxFileLen = 1 << 30;
const int kMaxLineLen = 1 << 10;
const int kMaxPost = 64 << 20 / 8; // 64MB

class IndexWriter {
public:
  IndexWriter() = delete;
  ~IndexWriter() = default;
  IndexWriter(const IndexWriter &) = delete;
  IndexWriter &operator=(const IndexWriter &) = delete;
  explicit IndexWriter(const std::string &indexFile)
      : indexFile_{indexFile}, trigram_{new SparseSet()},
        nameData_{new IndexWriterBuffer("codeverse_name_data")},
        nameIndex_{new IndexWriterBuffer("codeverse_name_index")} {}

  void addFile(const std::string &name);
  void updateFile(const std::string &name);
  void flush();

  // addFileNameToIndex
  // @return: file id
  int addFileNameToIndex(const std::string &name);

  void flushPost();

private:
  // addFileWithName:
  //  will read the file's content, and converts it
  //  to trigram, add trigram to the sparse set.
  void addFileWithName(const std::string &name, std::ifstream fstream);
  uint32_t addName(const std::string &name);
  void copy(IndexWriterBuffer *dst, IndexWriterBuffer *src);

  std::string indexFile_;
  SparseSet *trigram_;

  std::vector<std::string> paths_;

  IndexWriterBuffer *nameData_;
  uint32_t nameLen_; // number of bytes written to nameData_;

  IndexWriterBuffer *nameIndex_;
  uint32_t nameNum_; // number of names written
  int64_t totalBytes_;

  std::vector<PostEntry> post;
  std::vector<int> postFile_;

  char inbuf_[16384];
  IndexWriterBuffer *main_;
};

} // namespace tools::idx