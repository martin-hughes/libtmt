#include "../test_includes.h"

using namespace vt_test;

TEST(CursorTests, BasicCursorLeft) {
  TestVtWrapper vt(80, 25);

  write_string(vt, "aaaaaaaaa");
  write_cursor_move(vt, CursorMoveDir::Left, 6);
  write_string(vt, "bbb");

  EXPECT_EQ(vt.get_line_text(0), "aaabbbaaa");
  EXPECT_EQ(vt.get_line_text(4), "");
}

TEST(CursorTests, BasicCursorRight) {
  TestVtWrapper vt(80, 25);

  write_string(vt, "aaa");
  write_cursor_move(vt, CursorMoveDir::Right, 3);
  write_string(vt, "bbb");

  EXPECT_EQ(vt.get_line_text(0), "aaa   bbb");
  EXPECT_EQ(vt.get_line_text(4), "");
}

TEST(CursorTests, BasicCursorDown) {
  TestVtWrapper vt(80, 5);

  write_string(vt, "aaa");
  write_cursor_move(vt, CursorMoveDir::Down, 3);
  write_string(vt, "bbb");

  EXPECT_EQ(vt.get_line_text(0), "aaa");
  EXPECT_EQ(vt.get_line_text(1), "");
  EXPECT_EQ(vt.get_line_text(2), "");
  EXPECT_EQ(vt.get_line_text(3), "   bbb");

  EXPECT_TRUE(vt.is_line_dirty(0));
  EXPECT_FALSE(vt.is_line_dirty(1));
  EXPECT_FALSE(vt.is_line_dirty(2));
  EXPECT_TRUE(vt.is_line_dirty(3));
  EXPECT_FALSE(vt.is_line_dirty(4));
}

TEST(CursorTests, BasicCursorUp) {
  TestVtWrapper vt(80, 5);

  write_string(vt, "\n\n\naaa");
  write_cursor_move(vt, CursorMoveDir::Up, 3);
  write_string(vt, "bbb");

  EXPECT_EQ(vt.get_line_text(0), "   bbb");
  EXPECT_EQ(vt.get_line_text(1), "");
  EXPECT_EQ(vt.get_line_text(2), "");
  EXPECT_EQ(vt.get_line_text(3), "aaa");

  EXPECT_TRUE(vt.is_line_dirty(0));
  EXPECT_FALSE(vt.is_line_dirty(1));
  EXPECT_FALSE(vt.is_line_dirty(2));
  EXPECT_TRUE(vt.is_line_dirty(3));
  EXPECT_FALSE(vt.is_line_dirty(4));
}
