#include "test/infra/TestVtWrapper.h"
#include "test/infra/test_helpers.h"
#include "test/test_includes.h"

using namespace vt_test;

// Throughout these tests, note that `set_cursor_pos` writes the relevant command.
// Also recall that the cursor position is 1-indexed, but the output from tmt is 0-indexed.

TEST(CapabilityCup, MovesWithinWindow) {
  TestVtWrapper vt{10, 5};

  set_cursor_pos(vt, {.r = 2, .c = 5});

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(1, pos.r);
  EXPECT_EQ(4, pos.c);
}

TEST(CapabilityCup, CantMoveBeyondWindow) {
  TestVtWrapper vt{10, 5};

  set_cursor_pos(vt, {.r = 5, .c = 15});

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(4, pos.r);
  EXPECT_EQ(9, pos.c);
}

TEST(CapabilityCup, MovesToTopLeftIfZeroSent) {
  TestVtWrapper vt{10, 5};

  set_cursor_pos(vt, {.r = 2, .c = 2});
  {
    const auto pos = vt.get_cursor_pos();
    EXPECT_EQ(1, pos.r);
    EXPECT_EQ(1, pos.c);
  }

  set_cursor_pos(vt, {.r = 0, .c = 0});
  {
    const auto pos = vt.get_cursor_pos();
    EXPECT_EQ(0, pos.r);
    EXPECT_EQ(0, pos.c);
  }
}

TEST(CapabilityCup, WritesAtNewCursorLoc) {
  TestVtWrapper vt{10, 5};

  vt.set_clean();

  set_cursor_pos(vt, {.r = 2, .c = 5});
  write_string(vt, "hi");

  EXPECT_EQ("", vt.get_line_text(0));
  EXPECT_EQ("    hi", vt.get_line_text(1));
  EXPECT_EQ("", vt.get_line_text(2));

  EXPECT_FALSE(vt.is_line_dirty(0));
  EXPECT_TRUE(vt.is_line_dirty(1));
  EXPECT_FALSE(vt.is_line_dirty(2));

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(1, pos.r);
  EXPECT_EQ(6, pos.c);
}
