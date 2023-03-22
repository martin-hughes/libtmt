#pragma once

extern "C"
{
#include "tmt.h"
}

#include <string>

namespace vt_test {
  class TestVtWrapper {
  public:
    TestVtWrapper(int cols, int rows);
    ~TestVtWrapper();

    TMT *get_vt();
    void write_string(const std::string &string);

    std::string get_line_text(size_t line, bool strip_trailing_spaces = true);

  private:
    TMT *vt;
  };
}
