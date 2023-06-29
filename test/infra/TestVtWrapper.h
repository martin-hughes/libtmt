#pragma once

extern "C"
{
#include "tmt.h"
}

#include "VtStdCallbacks.h"

#include <string_view>

namespace vt_test {
  class TestVtWrapper {
  public:
    TestVtWrapper(size_t cols, size_t rows);
    TestVtWrapper(size_t cols, size_t rows, TmtCallbackType callback, bool receive_startup_msgs = true);
    ~TestVtWrapper();

    [[nodiscard]] TMT *get_vt() const;
    void write_string(const std::string_view &string);
    void set_clean();

    [[nodiscard]] std::string get_line_text(size_t line, bool strip_trailing_spaces = true) const;
    [[nodiscard]] bool is_line_dirty(size_t line) const;

    [[nodiscard]] TMTCHAR get_character(size_t row, size_t col) const;
    [[nodiscard]] TMTPOINT get_cursor_pos() const;

  private:
    TMT *vt;

    size_t cols;
    size_t lines;
    TmtCallbackType callback;

    static void static_callback(tmt_msg_t msg, TMT *vt, const void *a, void *p);
  };
}
