#include "test/test_includes.h"

using namespace vt_test;

TEST(CapabilityHome, MovesHomeFromAway) {
  TestVtWrapper vt(20, 5);
  write_string(vt, "Hello\r\n world");

  {
    const auto pos = vt.get_cursor_pos();
    EXPECT_EQ(6, pos.c);
    EXPECT_EQ(1, pos.r);
  }

  write_csi(vt);
  write_string(vt, "H");

  {
    const auto pos = vt.get_cursor_pos();
    EXPECT_EQ(0, pos.c);
    EXPECT_EQ(0, pos.r);
  }
}

TEST(CapabilityHome, DoesntMoveIfAlreadyHome) {
  TestVtWrapper vt(20, 5);

  {
    const auto pos = vt.get_cursor_pos();
    EXPECT_EQ(0, pos.c);
    EXPECT_EQ(0, pos.r);
  }

  write_csi(vt);
  write_string(vt, "H");

  {
    const auto pos = vt.get_cursor_pos();
    EXPECT_EQ(0, pos.c);
    EXPECT_EQ(0, pos.r);
  }
}
