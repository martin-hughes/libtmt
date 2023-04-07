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

TEST(EchTests, ClearMultipleFromMidLine) {
  TestVtWrapper vt(80, 25);

  write_string(vt, "Hello, world");
  write_cursor_move(vt, CursorMoveDir::Left, 5);

  // Cursor is now underneath 'w' of 'world'
  write_csi(vt);
  write_string(vt, "3X");

  // should have cleared the letters 'wor'

  EXPECT_EQ("Hello,    ld", vt.get_line_text(0));
  EXPECT_EQ("", vt.get_line_text(1));
}
