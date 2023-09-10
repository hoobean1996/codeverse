#pragma once

#include <filesystem>
#include <string>
namespace tools::idx {
struct Options {
  Options(std::string path) : path{path} {}
  bool validate() { return path != ""; }
  std::string path;
  std::string absPath() const {
    return std::filesystem::absolute(path).string();
  }
};
} // namespace tools::idx