#include "tools/idx/code_index_writer.h"

#include <fstream>
#include <glog/logging.h>
#include <stdexcept>
#include <unistd.h>

namespace tools::idx {
void IndexWriter::AddFile(const std::string &name) {
  LOG(INFO) << "AddFile filename = " << name;
  std::ifstream fstream(name);
  addFileWithName(name, std::move(fstream));
}
void IndexWriter::UpdateFile(const std::string &name) {
  LOG(INFO) << "UpdateFile filename = " << name;
}
void IndexWriter::addFileWithName(const std::string &name,
                                  std::ifstream fstream) {
  LOG(INFO) << "addFileWithName filename = " << name;
  constexpr int bufSize = 16384;
  uint8_t c = 0;
  int i = 0;
  char buf[bufSize] = {0};
  uint32_t trigramValue = 0;
  int n = 0;
  int lineLen = 0;
  int validBufSize = 0;
  for (;;) {
    trigramValue = (trigramValue << 8) & ((1 << 24) - 1);
    if (i >= validBufSize) {
      if (!fstream.is_open()) {
        throw std::runtime_error("the file is not been opended, filename = " +
                                 name);
      }
      fstream.read(buf, bufSize);
      validBufSize = fstream.gcount();
      LOG(INFO) << "read size: " << validBufSize << ", read content: \n"
                << std::string(buf);
      if (n == 0) {
        break;
      }
      i = 0;
    }

    for (int j = 0; j < validBufSize; j++) {
      c = buf[j];
      i++;
      trigramValue |= uint32_t(c);
      if (++n >= 3) {
        // trigram.Add(tv)
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
}
} // namespace tools::idx