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
  TestVtWrapper vt(80, 25);

  write_string(vt, "aaa");
  write_cursor_move(vt, CursorMoveDir::Down, 3);
  write_string(vt, "bbb");

  EXPECT_EQ(vt.get_line_text(0), "aaa");
  EXPECT_EQ(vt.get_line_text(1), "");
  EXPECT_EQ(vt.get_line_text(2), "");
  EXPECT_EQ(vt.get_line_text(3), "   bbb");
}

TEST(CursorTests, BasicCursorUp) {
  TestVtWrapper vt(80, 25);

  write_string(vt, "\n\n\naaa");
  write_cursor_move(vt, CursorMoveDir::Up, 3);
  write_string(vt, "bbb");

  EXPECT_EQ(vt.get_line_text(0), "   bbb");
  EXPECT_EQ(vt.get_line_text(1), "");
  EXPECT_EQ(vt.get_line_text(2), "");
  EXPECT_EQ(vt.get_line_text(3), "aaa");
}
