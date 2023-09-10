#pragma once

#include "tools/idx/code_index_writer.h"
#include "tools/idx/options.h"
#include <filesystem>
#include <glog/logging.h>
#include <string>

namespace tools::idx {

const std::string kMagicHeader = "codeverse_start\n";
const std::string kMagicTailer = "codeverse_end\n";
const std::string kIndexFileName = ".codeverse.idx";

class CodeIndex {
public:
  // IndexFile is the index file path.
  // It relys on HOME environment vairable,
  // in the test, we need to add mock env to make it passed.
  static std::string IndexFile() {
    const char *home = std::getenv("HOME");
    std::filesystem::path clean_path =
        std::filesystem::path(home).lexically_normal();

    return clean_path.string() + "/" + kIndexFileName;
  }

  static IndexWriter *GetWriter() {
    return new IndexWriter(CodeIndex::IndexFile());
  }

  static void BuildIncrementalIndex(const Options &opts) {
    LOG(INFO) << "BuildIncrementalIndex path = " << opts.absPath();
    try {
      auto indexWriter = GetWriter();
      walk(opts, [&indexWriter](const std::string &filename) {
        indexWriter->AddFile(filename);
      });
    } catch (std::runtime_error &e) {
      LOG(INFO) << "BuildIncrementalIndex exception = " << e.what();
    }
  }

  static void BuildNewIndex(const Options &opts) {
    LOG(INFO) << "BuildNewIndex path = " << opts.absPath();
    try {
      auto indexWriter = GetWriter();
      walk(opts, [&indexWriter](const std::string &filename) {
        indexWriter->UpdateFile(filename);
      });
    } catch (std::runtime_error &e) {
      LOG(ERROR) << "BuildNewIndex exception = " << e.what();
    }
  }

private:
  static void walk(const Options &opts,
                   std::function<void(const std::string &filemame)> onFile) {
    LOG(INFO) << "walk start";
    std::function<void(const std::string &)> walkRec =
        [&walkRec, &onFile](const std::string &path) {
          for (const auto &entry : std::filesystem::directory_iterator(path)) {
            const auto filenameStr = entry.path().filename().string();
            if (entry.is_directory()) {
              walkRec(entry.path());
            } else if (entry.is_regular_file()) {
              if (entry.path().extension() == ".cc") {
                LOG(INFO) << "entry = " << entry.path() << ", type = cc";
                onFile(entry.path().string());
              }
            } else {
            }
          }
        };
    auto directory = opts.absPath();
    walkRec(opts.absPath());
    LOG(INFO) << "walk end";
  }

  static CodeIndex index_;
};

} // namespace tools::idx