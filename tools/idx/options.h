#pragma once

#include <filesystem>
#include <string>
#include <vector>
namespace tools::idx {
struct Options {
  enum class Action {
    Build,
    Rebuild,
  };
  Options(std::string path) : path{path} {}
  Action getAction() {
    return path != "" ? Options::Action::Build : Options::Action::Rebuild;
  }
  std::string path;
  std::string absPath() const {
    return std::filesystem::absolute(path).string();
  }
};
} // namespace tools::idx