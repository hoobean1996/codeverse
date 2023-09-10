#pragma once

#include <_types/_uint32_t.h>
#include <vector>
namespace tools::idx {
class SparseSet {
public:
  SparseSet();
  explicit SparseSet(uint32_t max);
  ~SparseSet() = default;
  void init(uint32_t max);
  void reset();
  void add(uint32_t x);
  bool has(uint32_t x);
  std::vector<uint32_t> getDense();
  std::vector<uint32_t> getSparse();
  int size();

private:
  std::vector<uint32_t> dense_;
  std::vector<uint32_t> sparse_;
};
} // namespace tools::idx