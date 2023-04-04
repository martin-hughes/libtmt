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

  write_csi(vt);
  write_string(vt, "T");

  EXPECT_EQ(vt.get_line_text(0), "");
  EXPECT_EQ(vt.get_line_text(1), "Row 4");
  EXPECT_EQ(vt.get_line_text(2), "Row 5");
}
