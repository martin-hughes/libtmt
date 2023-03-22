extern "C"
{
#include "tmt.h"
};

#include "../test_helpers.h"
#include "gtest/gtest.h"

TEST(EchTests, ClearFromEnd) {
  TMT *vt = tmt_open(80, 25, normal_callback, nullptr, nullptr);
  TMT &vt_r = *vt;

  write_string(vt_r, "Hello, world");
  write_csi(vt_r);
  write_string(vt_r, "3X");

  EXPECT_TRUE(line_is_equal_to(*vt, 0, "Hello, world"));
  EXPECT_TRUE(line_is_equal_to(*vt, 1, ""));

  tmt_close(vt);
}

TEST(EchTests, ClearMultipleFromMidLine) {
  TMT *vt = tmt_open(80, 25, normal_callback, nullptr, nullptr);
  TMT &vt_r = *vt;

  write_string(vt_r, "Hello, world");
  write_cursor_move(vt_r, CursorMoveDir::Left, 5);

  // Cursor is now underneath 'w' of 'world'
  write_csi(vt_r);
  write_string(vt_r, "3X");

  // should have cleared the letters 'wor'

  EXPECT_TRUE(line_is_equal_to(*vt, 0, "Hello,    ld"));
  EXPECT_TRUE(line_is_equal_to(*vt, 1, ""));

  tmt_close(vt);
}
