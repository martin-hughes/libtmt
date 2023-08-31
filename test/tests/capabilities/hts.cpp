#include "../../test_includes.h"

using namespace vt_test;

// These tests assume that the tab character and tab command sequence `\E[I` operate identically, so only test using the
// tab character.

TEST(CapabilityHts, DoesntMoveCursor) {
  TestVtWrapper vt{20, 3};

  set_cursor_pos(vt, {.r = 1, .c = 4});

  write_hts(vt);

  EXPECT_EQ(0, vt.get_cursor_pos().r);
  EXPECT_EQ(3, vt.get_cursor_pos().c);
}

TEST(CapabilityHts, WorksOnUnsetColumn) {
  TestVtWrapper vt{20, 3};

  set_cursor_pos(vt, {.r = 1, .c = 4});
  write_hts(vt);
  set_cursor_pos(vt, {.r = 1, .c = 2});

  write_string(vt, "\t");
  EXPECT_EQ(3, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);

  write_string(vt, "\t");
  EXPECT_EQ(8, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);
}

TEST(CapabilityHts, CatchesBacktabs) {
  TestVtWrapper vt{20, 3};

  set_cursor_pos(vt, {.r = 1, .c = 4});
  write_hts(vt);
  set_cursor_pos(vt, {.r = 1, .c = 6});

  write_backtab(vt);
  EXPECT_EQ(3, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);

  write_backtab(vt);
  EXPECT_EQ(0, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);
}

TEST(CapabilityHts, SetsAllLines) {
  const size_t rows = 3;
  TestVtWrapper vt{20, rows};

  set_cursor_pos(vt, {.r = 1, .c = 4});
  write_hts(vt);

  for (size_t i = 0; i < rows; i++) {
    set_cursor_pos(vt, {.r = i + 1, .c = 2});

    write_string(vt, "\t");
    EXPECT_EQ(3, vt.get_cursor_pos().c);
    EXPECT_EQ(i, vt.get_cursor_pos().r);

    write_string(vt, "\t");
    EXPECT_EQ(8, vt.get_cursor_pos().c);
    EXPECT_EQ(i, vt.get_cursor_pos().r);
  }
}

TEST(CapabilityHts, IgnoresDuplicateSets) {
  TestVtWrapper vt{20, 3};

  set_cursor_pos(vt, {.r = 1, .c = 4});
  write_hts(vt);
  write_hts(vt);
  set_cursor_pos(vt, {.r = 1, .c = 2});

  write_string(vt, "\t");
  EXPECT_EQ(3, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);

  write_string(vt, "\t");
  EXPECT_EQ(8, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);
}

TEST(CapabilityHts, DoesntAffectPresetTab) {
  TestVtWrapper vt{20, 3};

  set_cursor_pos(vt, {.r = 1, .c = 9});
  write_hts(vt);
  set_cursor_pos(vt, {.r = 1, .c = 2});

  write_string(vt, "\t");
  EXPECT_EQ(8, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);

  write_string(vt, "\t");
  EXPECT_EQ(16, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);
}

TEST(CapabilityHts, DoesntAffectFirstColumn) {
  TestVtWrapper vt{20, 3};

  set_cursor_pos(vt, {.r = 1, .c = 1});
  write_hts(vt);
  set_cursor_pos(vt, {.r = 1, .c = 2});

  write_backtab(vt);
  EXPECT_EQ(0, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);

  write_backtab(vt);
  EXPECT_EQ(0, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);
}

TEST(CapabilityHts, DoesntAffectLastColumn) {
  TestVtWrapper vt{20, 3};

  set_cursor_pos(vt, {.r = 1, .c = 20});
  write_hts(vt);
  set_cursor_pos(vt, {.r = 1, .c = 18});

  write_string(vt, "\t");
  EXPECT_EQ(19, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);

  write_string(vt, "\t");
  EXPECT_EQ(19, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);
}
