#include "../test_includes.h"

using namespace vt_test;

TEST(ScrollingTests, BasicOverflowScroll) {
  TestVtWrapper vt(10, 3);

  vt.write_string("Row 1\r\n");
  vt.write_string("Row 2\r\n");
  vt.write_string("Row 3\r\n");
  vt.write_string("Row 4\r\n");
  vt.write_string("Row 5\r\n");

  EXPECT_EQ(vt.get_line_text(0), "Row 4");
  EXPECT_EQ(vt.get_line_text(1), "Row 5");
  EXPECT_EQ(vt.get_line_text(2), "");
}

// After a line is full the cursor automatically moves to the next line, which is why line 3 is blank in this test.
TEST(ScrollingTests, LongLineScrolling) {
  TestVtWrapper vt(10, 3);

  vt.write_string("1111111111222222222233333333334444444444");

  EXPECT_EQ(vt.get_line_text(0), "3333333333");
  EXPECT_EQ(vt.get_line_text(1), "4444444444");
  EXPECT_EQ(vt.get_line_text(2), "");
}
