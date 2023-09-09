#include "tools/idx/index_file.h"
#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_string(path, "", "where do we search from");

// idx is code index tool.
int main(int argc, char **argv) {
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);
  FLAGS_logtostderr = 1;
  LOG(INFO) << "path = " << FLAGS_path;
  LOG(INFO) << "home = " << tools::idx::CodeIndexer::File();
  return 0;
}