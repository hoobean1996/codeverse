#pragma once

// UnifiedLog
//  - LocalLog
//  - LogcalLog
//    - LogSegment
//    - LogSegment
//      - FileRecord
//      - FileRecord

namespace tools::unified {
template <class Header> class Record {
public:
private:
  Header header_;
  char *bytes_;
};
} // namespace tools::unified