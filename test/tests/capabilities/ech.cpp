#include "test/test_includes.h"

using namespace vt_test;

TEST(CapabilityEch, ClearFromEnd) {
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

TEST(CapabilityEch, ClearMultipleFromMidLine) {
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

TEST(CapabilityEch, AdjustZeroParameterToOne) {
  TestVtWrapper vt(80, 3);

  write_string(vt, "Hello, world");
  write_cursor_move(vt, CursorMoveDir::Left, 5);

  vt.set_clean();

  // Cursor is now underneath 'w' of 'world'
  write_csi(vt);
  write_string(vt, "0X");

  // should have cleared the letters 'wor'

  EXPECT_EQ("Hello,  orld", vt.get_line_text(0));
  EXPECT_EQ("", vt.get_line_text(1));

  EXPECT_TRUE(vt.is_line_dirty(0));
  EXPECT_FALSE(vt.is_line_dirty(1));
  EXPECT_FALSE(vt.is_line_dirty(2));
}

TEST(CapabilityEch, NoParameterClearsOneChar) {
  TestVtWrapper vt(80, 3);

  write_string(vt, "Hello, world");
  write_cursor_move(vt, CursorMoveDir::Left, 5);

  vt.set_clean();

  // Cursor is now underneath 'w' of 'world'
  write_csi(vt);
  write_string(vt, "X");

  // should have cleared the letters 'wor'

  EXPECT_EQ("Hello,  orld", vt.get_line_text(0));
  EXPECT_EQ("", vt.get_line_text(1));

  EXPECT_TRUE(vt.is_line_dirty(0));
  EXPECT_FALSE(vt.is_line_dirty(1));
  EXPECT_FALSE(vt.is_line_dirty(2));
}

TEST(CapabilityEch, DoesntClearBeyondEndOfLine) {
  TestVtWrapper vt(10, 3);

  write_string(vt, "11111111112222222222");
  write_cursor_move(vt, CursorMoveDir::Up, 2);
  write_cursor_move(vt, CursorMoveDir::Right, 5);

  vt.set_clean();

  write_csi(vt);
  write_string(vt, "10X");

  EXPECT_EQ("11111", vt.get_line_text(0));
  EXPECT_EQ("2222222222", vt.get_line_text(1));

  EXPECT_TRUE(vt.is_line_dirty(0));
  EXPECT_FALSE(vt.is_line_dirty(1));
  EXPECT_FALSE(vt.is_line_dirty(2));
}
