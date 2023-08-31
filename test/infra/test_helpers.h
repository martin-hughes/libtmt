#pragma once

extern "C"
{
#include "tmt.h"
}

#include "test/infra/TestVtWrapper.h"

#include <optional>
#include <string_view>

enum class CursorMoveDir : char {
  Up = 'A',
  Down = 'B',
  Right = 'C',
  Left = 'D',
};

enum class EraseDirection : unsigned int {
  Below = 0,
  Above = 1,
  Complete = 2
};

namespace vt_test {
  void write_string(TestVtWrapper &vt, const std::string_view &string);
  void write_escape(TestVtWrapper &vt);
  void write_csi(TestVtWrapper &vt);
  void write_cursor_move(TestVtWrapper &vt, CursorMoveDir dir, size_t places);
  void write_sgr(TestVtWrapper &vt, const std::vector<unsigned int> &values);
  void write_erase(TestVtWrapper &vt, std::optional<EraseDirection> dir = std::nullopt);
  void write_backtab(TestVtWrapper &vt);
  void write_hts(TestVtWrapper &vt);

  void set_cursor_pos(TestVtWrapper &vt, const TMTPOINT &position);
}
