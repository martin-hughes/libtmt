// Test the 'rin' capability - scroll backwards 1 or n lines

#include "../../test_includes.h"

using namespace vt_test;

TEST(CapabilityRin, NoParameterScrollsOneLine) {
  TestVtWrapper vt(10, 3);

  vt.write_string("Row 1\r\n");
  vt.write_string("Row 2\r\n");
  vt.write_string("Row 3\r\n");
  vt.write_string("Row 4\r\n");
  vt.write_string("Row 5\r\n");

  vt.set_clean();

  write_csi(vt);
  write_string(vt, "T");

  EXPECT_EQ(vt.get_line_text(0), "");
  EXPECT_EQ(vt.get_line_text(1), "Row 4");
  EXPECT_EQ(vt.get_line_text(2), "Row 5");

  EXPECT_TRUE(vt.is_line_dirty(0));
  EXPECT_TRUE(vt.is_line_dirty(1));
  EXPECT_TRUE(vt.is_line_dirty(2));
}

TEST(CapabilityRin, ValidParameterScrollsAsExpected) {
  TestVtWrapper vt(10, 3);

  vt.write_string("Row 1\r\n");
  vt.write_string("Row 2\r\n");
  vt.write_string("Row 3");

  write_csi(vt);
  write_string(vt, "2T");

  EXPECT_EQ(vt.get_line_text(0), "");
  EXPECT_EQ(vt.get_line_text(1), "");
  EXPECT_EQ(vt.get_line_text(2), "Row 1");

  EXPECT_TRUE(vt.is_line_dirty(0));
  EXPECT_TRUE(vt.is_line_dirty(1));
  EXPECT_TRUE(vt.is_line_dirty(2));
}

TEST(CapabilityRin, ExcessiveParameterTruncated) {
  // libtmt stops scrolling when the last line reaches the bottom of the screen
  TestVtWrapper vt(10, 3);

  vt.write_string("Row 1\r\n");
  vt.write_string("Row 2\r\n");
  vt.write_string("Row 3");

  write_csi(vt);
  write_string(vt, "5T");

  EXPECT_EQ(vt.get_line_text(0), "");
  EXPECT_EQ(vt.get_line_text(1), "");
  EXPECT_EQ(vt.get_line_text(2), "Row 1");

  EXPECT_TRUE(vt.is_line_dirty(0));
  EXPECT_TRUE(vt.is_line_dirty(1));
  EXPECT_TRUE(vt.is_line_dirty(2));
}

TEST(CapabilityRin, ZeroParameterScrollsOneLine) {
  // Zero is an invalid parameter for `rin` - other terminals simply assume a
  // value of 1, it's reasonable for libtmt to do so as well.
  //
  // See https://terminalguide.namepad.de/seq/csi_ct_1param/

  GMockCallbacks cbs;

  // - Once on startup
  // - once for each call of write_string and write_csi (5 times total)
  EXPECT_CALL(cbs.update_callback, Call).Times(6);

  // - once for startup
  // - once for each call of write_string that causes "Row [x]" to be written (3 times)
  EXPECT_CALL(cbs.cursor_moved_callback, Call).Times(4);

  TestVtWrapper vt(10, 3, make_callback_for_gmocks(cbs));

  vt.write_string("Row 1\r\n");
  vt.write_string("Row 2\r\n");
  vt.write_string("Row 3");

  write_csi(vt);
  write_string(vt, "0T");

  EXPECT_EQ(vt.get_line_text(0), "");
  EXPECT_EQ(vt.get_line_text(1), "Row 1");
  EXPECT_EQ(vt.get_line_text(2), "Row 2");

  EXPECT_TRUE(vt.is_line_dirty(0));
  EXPECT_TRUE(vt.is_line_dirty(1));
  EXPECT_TRUE(vt.is_line_dirty(2));
}
