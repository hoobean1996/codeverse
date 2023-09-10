#pragma once

#include <_types/_uint32_t.h>
#include <_types/_uint64_t.h>

namespace tools::idx {
struct PostEntry {
  uint64_t value;

  uint32_t trigram() { return value >> 32; }

  uint32_t filedid() { return uint32_t(value); }

  PostEntry(uint32_t trigram, uint32_t fileid)
      : value{uint64_t(trigram) << 32 | fileid} {}
};
} // namespace tools::idx