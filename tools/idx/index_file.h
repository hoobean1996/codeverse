#pragma once

#include <filesystem>
#include <string>

namespace tools::idx {
class CodeIndexer {
public:
  // File is the index file path.
  // It relys on HOME environment vairable,
  // in the test, we need to add mock env to make it passed.
  static std::string File() {
    const char *home = std::getenv("HOME");
    std::filesystem::path clean_path =
        std::filesystem::path(home).lexically_normal();
    return clean_path;
  }
};
} // namespace tools::idx