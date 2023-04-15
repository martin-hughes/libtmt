#pragma once

extern "C"
{
#include "tmt.h"
}

#include <string>

namespace vt_test {
  class TestVtWrapper {
  public:
    TestVtWrapper(size_t cols, size_t rows);
    ~TestVtWrapper();

    TMT *get_vt();
    void write_string(const std::string &string);
    void set_clean();

    std::string get_line_text(size_t line, bool strip_trailing_spaces = true);
    bool is_line_dirty(size_t line);

  private:
    TMT *vt;

    size_t cols;
    size_t lines;
  };
}
