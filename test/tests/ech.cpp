#include "../test_includes.h"

using namespace vt_test;

TEST(EchTests, ClearFromEnd) {
  TestVtWrapper vt(80, 3);

  write_string(vt, "Hello, world");

  vt.set_clean();

  write_csi(vt);
  write_string(vt, "3X");

  EXPECT_EQ("Hello, world", vt.get_line_text(0));
  EXPECT_EQ("", vt.get_line_text(1));

  EXPECT_TRUE(vt.is_line_dirty(0));
  EXPECT_FALSE(vt.is_line_dirty(1));
  EXPECT_FALSE(vt.is_line_dirty(2));
}

TEST(EchTests, ClearMultipleFromMidLine) {
  TestVtWrapper vt(80, 3);

  write_string(vt, "Hello, world");
  write_cursor_move(vt, CursorMoveDir::Left, 5);

  vt.set_clean();

  // Cursor is now underneath 'w' of 'world'
  write_csi(vt);
  write_string(vt, "3X");

  // should have cleared the letters 'wor'

  EXPECT_EQ("Hello,    ld", vt.get_line_text(0));
  EXPECT_EQ("", vt.get_line_text(1));

  EXPECT_TRUE(vt.is_line_dirty(0));
  EXPECT_FALSE(vt.is_line_dirty(1));
  EXPECT_FALSE(vt.is_line_dirty(2));
}
