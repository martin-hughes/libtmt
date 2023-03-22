#include "../test_includes.h"

using namespace vt_test;

TEST(EchTests, ClearFromEnd) {
  TestVtWrapper vt(80, 25);

  write_string(vt, "Hello, world");
  write_csi(vt);
  write_string(vt, "3X");

  EXPECT_EQ("Hello, world", vt.get_line_text(0));
  EXPECT_EQ("", vt.get_line_text(1));
}

#if 0
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
#endif
