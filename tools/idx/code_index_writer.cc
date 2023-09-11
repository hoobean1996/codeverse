#include "tools/idx/code_index_writer.h"
#include "tools/idx/code_index.h"
#include "tools/idx/code_index_writer_buffer.h"
#include "tools/idx/post_entry.h"

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <filesystem>
#include <fstream>
#include <glog/logging.h>
#include <stdexcept>
#include <unistd.h>

namespace tools::idx {
void IndexWriter::addFile(const std::string &path) {
  std::ifstream fstream(path);
  paths_.push_back(path);
  int pos = path.rfind("/");
  auto filename = path.substr(pos + 1);
  LOG(INFO) << "addFile, filpath = " << path;
  LOG(INFO) << "addFile, filename = " << filename;
  addFileWithName(path, std::move(fstream));
}
void IndexWriter::updateFile(const std::string &name) {
  LOG(INFO) << "updateFile, filename = " << name;
}
void IndexWriter::addFileWithName(const std::string &path,
                                  std::ifstream fstream) {
  auto filesize = std::filesystem::file_size(path);
  LOG(INFO) << "addFileWithName, filepath = " << path
            << ", filesize = " << filesize;
  trigram_->reset();
  constexpr int bufSize = 16384;
  uint8_t c = 0;
  char buf[bufSize] = {0};
  uint32_t trigramValue = 0;
  int n = 0;
  int lineLen = 0;
  int readedBufSize = 0;
  int i = 0;
  for (;;) {
    if (i >= readedBufSize) {
      LOG(INFO) << "process bytes reaches to readed bytes";
      if (!fstream.is_open()) {
        throw std::runtime_error("the file is not been opended, filename = " +
                                 path);
      }
      fstream.read(buf, bufSize);
      readedBufSize = fstream.gcount();
      LOG(INFO) << "read size: " << readedBufSize;
      if (n == 0) {
        break;
      }
      i = 0;
    }
    trigramValue = (trigramValue << 8) & ((1 << 24) - 1);
    for (int j = 0; j < readedBufSize; j++) {
      c = buf[j];
      i++;
      trigramValue |= uint32_t(c);
      if (++n >= 3) {
        trigram_->add(trigramValue);
      }
      if (n > kMaxFileLen) {
        LOG(ERROR) << "the file content exceeds the max file len";
      }
      if (++lineLen > kMaxLineLen) {
        LOG(ERROR) << "the line is too long, exceeds the max line length";
      }
      if (c == '\n') {
        lineLen = 0;
      }
    }
  }
  totalBytes_ += n;
  auto fileId = addFileNameToIndex(path);
  for (const auto &trigram : trigram_->getDense()) {
    if (post.size() >= kMaxPost) {
      flushPost();
    }
    post.push_back(PostEntry(trigram, fileId));
  }
  flushPost();
}
uint32_t IndexWriter::addName(const std::string &name) { return 0; }
void IndexWriter::flush() {
  addName("");
  uint32_t offset[5];
  main_->writeString(kMagicHeader);
  offset[0] = main_->offset();
  for (const auto &path : paths_) {
    main_->writeString(path);
    main_->writeString("\x00");
  }
  main_->writeString("\x00");
  offset[1] = main_->offset();
}

int IndexWriter::addFileNameToIndex(const std::string &name) {
  nameIndex_->writeUint32(nameData_->offset());
  nameData_->writeString(name);
  nameData_->writeByte(0);
  auto id = nameNum_;
  id++;
  return id;
}

void IndexWriter::flushPost() {
  char tmpl[] = "/tmp/codeverse/postindexXXXXXX";
  auto filename = ::mktemp(tmpl);
  LOG(INFO) << "flushPost, temporary file = " << filename;
  auto fd = open(filename, O_RDWR, 0644);
  std::sort(post.begin(), post.end(),
            [](const PostEntry &lhs, const PostEntry &rhs) {
              return lhs.value < rhs.value;
            });
  uint8_t *data = reinterpret_cast<uint8_t *>(post.data());
  write(fd, data, sizeof(PostEntry) * post.size());
  lseek(fd, 0, SEEK_SET);
  post.clear();
  postFile_.push_back(fd);
}

void IndexWriter::copy(IndexWriterBuffer *dst, IndexWriterBuffer *src) {}
} // namespace tools::idx