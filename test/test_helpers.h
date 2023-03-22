#pragma once

extern "C"
{
#include "tmt.h"
}

#include "TestVtWrapper.h"

#include <string>

enum class CursorMoveDir : unsigned char {
  Up = 'A',
  Down = 'B',
  Right = 'C',
  Left = 'D',
};

void normal_callback(tmt_msg_t m, TMT *vt, const void *a, void *p);

namespace vt_test {
  void write_string(TestVtWrapper &vt, const std::string &string);
  void write_escape(TestVtWrapper &vt);
  void write_csi(TestVtWrapper &vt);
  void write_cursor_move(TestVtWrapper &vt, CursorMoveDir dir, size_t places);
}
