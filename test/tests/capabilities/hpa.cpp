#include "../../test_includes.h"

using namespace vt_test;

namespace {
  void write_hpa(TestVtWrapper &vt, const unsigned int col) {
    write_csi(vt);
    write_string(vt, std::to_string(col));
    write_string(vt, "G");
  }
}

TEST(CapabilityHpa, MovesToColumn) {
  TestVtWrapper vt{10, 3};

  write_hpa(vt, 5);

  EXPECT_EQ(4, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);
}

TEST(CapabilityHpa, DoesntMoveIfNotNeeded) {
  TestVtWrapper vt{10, 3};

  write_hpa(vt, 5);
  write_hpa(vt, 5);

  EXPECT_EQ(4, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);
}

TEST(CapabilityHpa, TruncatesToRightHandColumn) {
  TestVtWrapper vt{10, 3};

  write_hpa(vt, 500);

  EXPECT_EQ(9, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);
}

TEST(CapabilityHpa, DoesntChangeRow) {
  TestVtWrapper vt{10, 3};
  set_cursor_pos(vt, {.r = 3, .c = 8});

  write_hpa(vt, 5);

  EXPECT_EQ(4, vt.get_cursor_pos().c);
  EXPECT_EQ(2, vt.get_cursor_pos().r);
}

TEST(CapabilityHpa, InterpretsZeroAsFirstCol) {
  TestVtWrapper vt{10, 3};

  write_hpa(vt, 0);

  EXPECT_EQ(0, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);
}

TEST(CapabilityHpa, InterpretsMissingParamAsFirstCol) {
  TestVtWrapper vt{10, 3};

  write_csi(vt);
  write_string(vt, "G");

  EXPECT_EQ(0, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);
}
