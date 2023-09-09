#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_string(q, "", "the content to query");
DEFINE_string(path, "", "where do we search from");

// z is a code search tool.
// e.g.:
//   z -q "hello" -in main.cc
//   z -q "int main" -in .
//   z -q "int main
int main(int argc, char **argv) {
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);
  FLAGS_logtostderr = 1;
  LOG(INFO) << "q = " << FLAGS_q;
  LOG(INFO) << "path = " << FLAGS_path;
  return 0;
}