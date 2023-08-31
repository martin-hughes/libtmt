#include "../../test_includes.h"

using namespace vt_test;

namespace {
  void write_backtab(TestVtWrapper &vt) {
    write_csi(vt);
    write_string(vt, "Z");
  }
}

TEST(CapabilitCbt, MovesBetweenTabs) {
  TestVtWrapper vt{20, 3};

  set_cursor_pos(vt, {.r = 1, .c = 18});

  write_backtab(vt);
  EXPECT_EQ(16, vt.get_cursor_pos().c);

  write_backtab(vt);
  EXPECT_EQ(8, vt.get_cursor_pos().c);

  write_backtab(vt);
  EXPECT_EQ(0, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);
}

TEST(CapabilityCbt, MovesToNextTabWhenInBetween) {
  TestVtWrapper vt{20, 3};

  set_cursor_pos(vt, {.r = 1, .c = 13});

  write_backtab(vt);
  EXPECT_EQ(8, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);
}

TEST(CapabilityCbt, DoesNotTabPastFirstColumn) {
  TestVtWrapper vt{20, 3};

  set_cursor_pos(vt, {.r = 1, .c = 3});

  write_backtab(vt);
  EXPECT_EQ(0, vt.get_cursor_pos().c);

  write_backtab(vt);
  EXPECT_EQ(0, vt.get_cursor_pos().c);

  EXPECT_EQ(0, vt.get_cursor_pos().r);
}

TEST(CapabilityCbt, TabsFromLastColumn) {
  TestVtWrapper vt{20, 3};

  set_cursor_pos(vt, {.r = 1, .c = 20});

  write_backtab(vt);
  EXPECT_EQ(16, vt.get_cursor_pos().c);
}
