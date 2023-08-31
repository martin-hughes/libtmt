#include "../../test_includes.h"

using namespace vt_test;

namespace {
  void write_vpa(TestVtWrapper &vt, const unsigned int row) {
    write_csi(vt);
    write_string(vt, std::to_string(row));
    write_string(vt, "d");
  }
}

TEST(CapabilityVpa, MovesToRow) {
  TestVtWrapper vt{10, 5};

  write_vpa(vt, 3);

  EXPECT_EQ(0, vt.get_cursor_pos().c);
  EXPECT_EQ(2, vt.get_cursor_pos().r);
}

TEST(CapabilityVpa, DoesntMoveIfNotNeeded) {
  TestVtWrapper vt{10, 5};

  write_vpa(vt, 3);
  write_vpa(vt, 3);

  EXPECT_EQ(0, vt.get_cursor_pos().c);
  EXPECT_EQ(2, vt.get_cursor_pos().r);
}

TEST(CapabilityVpa, TruncatesToBottomRow) {
  TestVtWrapper vt{10, 3};

  write_vpa(vt, 500);

  EXPECT_EQ(0, vt.get_cursor_pos().c);
  EXPECT_EQ(2, vt.get_cursor_pos().r);
}

TEST(CapabilityVpa, DoesntChangeColumn) {
  TestVtWrapper vt{10, 5};
  set_cursor_pos(vt, {.r = 2, .c = 8});

  write_vpa(vt, 4);

  EXPECT_EQ(7, vt.get_cursor_pos().c);
  EXPECT_EQ(3, vt.get_cursor_pos().r);
}

TEST(CapabilityVpa, InterpretsZeroAsFirstRow) {
  TestVtWrapper vt{10, 3};

  write_vpa(vt, 0);

  EXPECT_EQ(0, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);
}

TEST(CapabilityVpa, InterpretsMissingParamAsFirstRow) {
  TestVtWrapper vt{10, 3};

  write_csi(vt);
  write_string(vt, "d");

  EXPECT_EQ(0, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);
}
