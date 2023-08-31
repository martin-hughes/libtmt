#include "../../test_includes.h"

using namespace vt_test;

// Based on knowledge of the code, tabs and backtabs are both very likely to work - so generally only normal tabs are
// tested.

namespace {
  void write_tbc(TestVtWrapper &vt) {
    write_csi(vt);
    write_string(vt, "3g");
  }
}

TEST(CapabilityTbc, DoesntMoveCursor) {
  TestVtWrapper vt{20, 3};
  set_cursor_pos(vt, {.r = 1, .c = 4});

  write_tbc(vt);

  EXPECT_EQ(0, vt.get_cursor_pos().r);
  EXPECT_EQ(3, vt.get_cursor_pos().c);
}

TEST(CapabilityTbc, RemovesNormalTabstop) {
  TestVtWrapper vt{20, 3};

  set_cursor_pos(vt, {.r = 1, .c = 4});
  write_tbc(vt);
  write_string(vt, "\t");

  EXPECT_EQ(0, vt.get_cursor_pos().r);
  EXPECT_EQ(19, vt.get_cursor_pos().c);
}

TEST(CapabilityTbc, StillStopsBacktabsAtFirstRow) {
  TestVtWrapper vt{20, 3};

  set_cursor_pos(vt, {.r = 1, .c = 14});
  write_tbc(vt);
  write_backtab(vt);

  EXPECT_EQ(0, vt.get_cursor_pos().r);
  EXPECT_EQ(0, vt.get_cursor_pos().c);
}

TEST(CapabilityTbc, AffectsAllRows) {
  TestVtWrapper vt{20, 3};

  set_cursor_pos(vt, {.r = 1, .c = 4});
  write_tbc(vt);
  set_cursor_pos(vt, {.r = 2, .c = 5});
  write_string(vt, "\t");

  EXPECT_EQ(1, vt.get_cursor_pos().r);
  EXPECT_EQ(19, vt.get_cursor_pos().c);
}
