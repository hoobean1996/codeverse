#include "tools/idx/code_index.h"
#include "tools/idx/options.h"
#include <chrono>
#include <filesystem>
#include <future>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <memory>
#include <thread>

DEFINE_string(path, "", "where do we search from");

// idx is code index tool.
int main(int argc, char **argv) {
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);
  FLAGS_logtostderr = 1;
  auto opts = tools::idx::Options{FLAGS_path};
  auto action = opts.getAction();
  switch (action) {
  case tools::idx::Options::Action::Build: {
    tools::idx::CodeIndex::buildIndex(opts);
    break;
  }
  case tools::idx::Options::Action::Rebuild: {
    tools::idx::CodeIndex::rebuildIndex(opts);
    break;
  }
  }
  std::this_thread::sleep_for(std::chrono::minutes(10));
  return 0;
}