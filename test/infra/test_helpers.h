#pragma once

extern "C"
{
#include "tmt.h"
}

#include "test/infra/TestVtWrapper.h"

#include <string>

enum class CursorMoveDir : char {
  Up = 'A',
  Down = 'B',
  Right = 'C',
  Left = 'D',
};

namespace vt_test {
  void write_string(TestVtWrapper &vt, const std::string &string);
  void write_escape(TestVtWrapper &vt);
  void write_csi(TestVtWrapper &vt);
  void write_cursor_move(TestVtWrapper &vt, CursorMoveDir dir, size_t places);
  void write_sgr(TestVtWrapper &vt, const std::vector<unsigned int> &values);

  void set_cursor_pos(TestVtWrapper &vt, const TMTPOINT &position);
}
