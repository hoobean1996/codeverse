#include "tools/idx/sparse_set.h"

namespace tools::idx {
SparseSet::SparseSet() : dense_{{}}, sparse_{std::vector<uint32_t>(1 << 24)} {}

SparseSet::SparseSet(uint32_t max)
    : dense_{{}}, sparse_{std::vector<uint32_t>(max)} {}

void SparseSet::init(uint32_t max) { sparse_ = std::vector<uint32_t>(max); }

void SparseSet::reset() { dense_ = {}; }

void SparseSet::add(uint32_t x) {
  auto v = sparse_[x];
  if (v < uint32_t(dense_.size() && dense_[v] == x)) {
    return;
  }
  auto n = dense_.size();
  sparse_[x] = uint32_t(n);
  dense_.push_back(x);
}

bool SparseSet::has(uint32_t x) {
  auto v = sparse_[x];
  return v < uint32_t(dense_.size()) && dense_[v] == x;
}

std::vector<uint32_t> SparseSet::getDense() { return dense_; }

std::vector<uint32_t> SparseSet::getSparse() { return sparse_; }

int SparseSet::size() { return dense_.size(); }
} // namespace tools::idx