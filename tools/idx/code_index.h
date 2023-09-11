#pragma once

#include "tools/idx/code_index_reader.h"
#include "tools/idx/code_index_writer.h"
#include "tools/idx/options.h"
#include <filesystem>
#include <functional>
#include <glog/logging.h>
#include <map>
#include <set>
#include <string>

namespace tools::idx {

const std::string kMagicHeader = "codeverse_start\n";
const std::string kMagicTailer = "codeverse_end\n";
const std::string kIndexFileName = ".codeverse.idx";

class CodeIndex {
public:
  // indexFile is the index file path.
  // It relys on HOME environment vairable,
  // in the test, we need to add mock env to make it passed.
  static std::string indexFile() {
    const char *home = std::getenv("HOME");
    std::filesystem::path clean_path =
        std::filesystem::path(home).lexically_normal();

    return clean_path.string() + "/" + kIndexFileName;
  }

  static IndexWriter *getWriter() {
    return new IndexWriter(CodeIndex::indexFile());
  }

  static IndexReader *getReader() {
    return new IndexReader(CodeIndex::indexFile());
  }

  static void rebuildIndex(const Options &opts) {
    LOG(INFO) << "rebuildIndex";
    try {
    } catch (std::runtime_error &e) {
      LOG(INFO) << "BuildIncrementalIndex exception = " << e.what();
    }
  }

  static void buildIndex(const Options &opts) {
    LOG(INFO) << "buildIndex, dir = " << opts.absPath();
    try {
      auto indexWriter = getWriter();
      walk(opts,
           {
               ".cc",
           },
           [&indexWriter](const std::string &filename) -> void {
             indexWriter->addFile(filename);
           });
    } catch (std::runtime_error &e) {
      LOG(ERROR) << "buildIndex, exception = " << e.what();
    }
  }

private:
  static void walk(const Options &opts, std::set<std::string> interestedFiles,
                   std::function<void(const std::string &filemame)> onFile) {
    std::function<void(const std::string &)> walkRec =
        [&walkRec, &onFile, &interestedFiles](const std::string &path) {
          for (const auto &entry : std::filesystem::directory_iterator(path)) {
            const auto filename = entry.path().filename().string();
            if (entry.is_directory()) {
              walkRec(entry.path());
            } else if (entry.is_regular_file()) {
              if (interestedFiles.contains(entry.path().extension())) {
                onFile(entry.path().string());
              }
            } else {
            }
          }
        };
    walkRec(opts.absPath());
  }

  static CodeIndex index_;
};

} // namespace tools::idx