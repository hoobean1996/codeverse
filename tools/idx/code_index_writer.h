#pragma once

#include "tools/idx/post_entry.h"
#include "tools/idx/sparse_set.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <sys/fcntl.h>
#include <unistd.h>

namespace tools::idx {

class IndexWriterBuffer;

const int kMaxFileLen = 1 << 30;
const int kMaxLineLen = 1 << 10;

class IndexWriter {
public:
  IndexWriter() = delete;
  IndexWriter(const IndexWriter &) = delete;
  IndexWriter &operator=(const IndexWriter &) = delete;
  explicit IndexWriter(const std::string &indexFile) : indexFile_{indexFile} {}

  void AddFile(const std::string &name);
  void UpdateFile(const std::string &name);

private:
  void addFileWithName(const std::string &name, std::ifstream fstream);

  std::string indexFile_;
  SparseSet *trigram;

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