#include "tools/idx/code_index_reader.h"
#include <cstdint>

namespace tools::idx {
void IndexReader::open() {}
char *IndexReader::slice(int offset, int size) { return {}; }
uint32_t IndexReader::uint32(int offset) { return 0; }
} // namespace tools::idx