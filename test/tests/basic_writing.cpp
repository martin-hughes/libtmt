#include "../test_includes.h"

using namespace vt_test;

TEST(BasicTests, WriteSimpleString) {
  TestVtWrapper vt(80, 5);

  std::string text = "Hello, world";
  vt.write_string(text);

  EXPECT_EQ(vt.get_line_text(0), text);
  EXPECT_EQ(vt.get_line_text(1), "");

  EXPECT_TRUE(vt.is_line_dirty(0));
  EXPECT_FALSE(vt.is_line_dirty(1));
  EXPECT_FALSE(vt.is_line_dirty(2));
  EXPECT_FALSE(vt.is_line_dirty(3));
  EXPECT_FALSE(vt.is_line_dirty(4));
}

TEST(BasicTests, WriteStringWithNewline) {
  TestVtWrapper vt(80, 5);

  std::string text = "Hello,\nworld";
  vt.write_string(text);

  EXPECT_EQ("Hello,", vt.get_line_text(0));
  EXPECT_EQ("      world", vt.get_line_text(1));
  EXPECT_EQ("", vt.get_line_text(2));

  EXPECT_TRUE(vt.is_line_dirty(0));
  EXPECT_TRUE(vt.is_line_dirty(1));
  EXPECT_FALSE(vt.is_line_dirty(2));
  EXPECT_FALSE(vt.is_line_dirty(3));
  EXPECT_FALSE(vt.is_line_dirty(4));
}

TEST(BasicTests, WriteStringWithReturn) {
  TestVtWrapper vt(80, 5);

  std::string text = "Hello, cruel\rworld";
  vt.write_string(text);

  EXPECT_EQ("world, cruel", vt.get_line_text(0));
  EXPECT_EQ("", vt.get_line_text(1));

  EXPECT_TRUE(vt.is_line_dirty(0));
  EXPECT_FALSE(vt.is_line_dirty(1));
  EXPECT_FALSE(vt.is_line_dirty(2));
  EXPECT_FALSE(vt.is_line_dirty(3));
  EXPECT_FALSE(vt.is_line_dirty(4));
}

TEST(BasicTests, WriteMultilineString) {
  TestVtWrapper vt(25, 5);

  std::string text = "Hello, cruel\r\nworld";
  vt.write_string(text);

  EXPECT_EQ("Hello, cruel", vt.get_line_text(0));
  EXPECT_EQ("world", vt.get_line_text(1));
  EXPECT_EQ("", vt.get_line_text(2));

  EXPECT_TRUE(vt.is_line_dirty(0));
  EXPECT_TRUE(vt.is_line_dirty(1));
  EXPECT_FALSE(vt.is_line_dirty(2));
  EXPECT_FALSE(vt.is_line_dirty(3));
  EXPECT_FALSE(vt.is_line_dirty(4));
}
