#include "tools/idx/code_index.h"
#include "tools/idx/options.h"
#include <filesystem>
#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_string(path, "", "where do we search from");

// idx is code index tool.
int main(int argc, char **argv) {
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);
  FLAGS_logtostderr = 1;
  auto opts = tools::idx::Options{FLAGS_path};
  if (!opts.validate()) {
    LOG(ERROR) << "the code path is required.";
    LOG(INFO) << "usage:\n\tcodeverse -path <path>";
    return 0;
  }
  if (std::filesystem::exists(tools::idx::CodeIndex::IndexFile())) {
    tools::idx::CodeIndex::BuildIncrementalIndex(opts);
  } else {
    tools::idx::CodeIndex::BuildNewIndex(opts);
  }
  return 0;
}