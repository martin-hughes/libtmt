extern "C"
{
#include "tmt.h"
};

#include "../test_helpers.h"
#include "gtest/gtest.h"


TEST(BasicTests, WriteSimpleString)
{
TMT* vt = tmt_open(80, 25, normal_callback, nullptr, nullptr);

const char *str = "Hello, world";
tmt_write(vt, str, strlen(str));

EXPECT_TRUE(line_is_equal_to(*vt, 0, str));
EXPECT_TRUE(line_is_equal_to(*vt, 1, ""));

tmt_close(vt);
}

TEST(BasicTests, WriteStringWithNewline) {
  TMT* vt = tmt_open(80, 25, normal_callback, nullptr, nullptr);

  const char *str = "Hello,\nworld";
  tmt_write(vt, str, strlen(str));

  EXPECT_TRUE(line_is_equal_to(*vt, 0, "Hello,"));
  EXPECT_TRUE(line_is_equal_to(*vt, 1, "      world"));
  EXPECT_TRUE(line_is_equal_to(*vt, 2, ""));

  tmt_close(vt);
}

TEST(BasicTests, WriteStringWithReturn) {
  TMT* vt = tmt_open(80, 25, normal_callback, nullptr, nullptr);

  const char *str = "Hello, cruel\rworld";
  tmt_write(vt, str, strlen(str));

  EXPECT_TRUE(line_is_equal_to(*vt, 0, "world, cruel"));
  EXPECT_TRUE(line_is_equal_to(*vt, 1, ""));

  tmt_close(vt);
}

TEST(BasicTests, WriteMultilineString) {
  TMT* vt = tmt_open(80, 25, normal_callback, nullptr, nullptr);

  const char *str = "Hello, cruel\r\nworld";
  tmt_write(vt, str, strlen(str));

  EXPECT_TRUE(line_is_equal_to(*vt, 0, "Hello, cruel"));
  EXPECT_TRUE(line_is_equal_to(*vt, 1, "world"));
  EXPECT_TRUE(line_is_equal_to(*vt, 2, ""));

  tmt_close(vt);
}
