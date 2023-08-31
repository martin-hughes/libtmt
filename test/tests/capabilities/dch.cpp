#include "../../test_includes.h"

using namespace vt_test;

namespace {
  void write_dch(TestVtWrapper &vt, std::optional<const unsigned int> num) {
    write_csi(vt);

    if (num) {
      write_string(vt, std::to_string(num.value()));
    }
    write_string(vt, "P");
  }
}

TEST(CapabilityDch, DeletesToTheRight) {
  TestVtWrapper vt{10, 3};
  write_string(vt, "0123456789");
  EXPECT_EQ(0, vt.get_cursor_pos().c);
  EXPECT_EQ(1, vt.get_cursor_pos().r);

  set_cursor_pos(vt, {.r = 1, .c = 5});
  vt.set_clean();
  write_dch(vt, 2);

  EXPECT_EQ("01236789", vt.get_line_text(0));
  EXPECT_TRUE(vt.is_line_dirty(0));
  EXPECT_FALSE(vt.is_line_dirty(1));
  EXPECT_FALSE(vt.is_line_dirty(2));
}

TEST(CapabilityDch, DeletesTruncatedToRightColumn) {
  TestVtWrapper vt{10, 3};
  write_string(vt, "0123456789abcdefghij");
  EXPECT_EQ(0, vt.get_cursor_pos().c);
  EXPECT_EQ(2, vt.get_cursor_pos().r);

  set_cursor_pos(vt, {.r = 1, .c = 5});
  vt.set_clean();
  write_dch(vt, 100);

  EXPECT_EQ("0123", vt.get_line_text(0));
  EXPECT_TRUE(vt.is_line_dirty(0));

  EXPECT_EQ("abcdefghij", vt.get_line_text(1));
  EXPECT_FALSE(vt.is_line_dirty(1));

  EXPECT_FALSE(vt.is_line_dirty(2));
}

TEST(CapabilityDch, TreatsMissingParamAsOneChar) {
  TestVtWrapper vt{10, 3};
  write_string(vt, "0123456789");
  EXPECT_EQ(0, vt.get_cursor_pos().c);
  EXPECT_EQ(1, vt.get_cursor_pos().r);

  set_cursor_pos(vt, {.r = 1, .c = 5});
  vt.set_clean();
  write_dch(vt, std::nullopt);

  EXPECT_EQ("012356789", vt.get_line_text(0));
  EXPECT_TRUE(vt.is_line_dirty(0));
  EXPECT_FALSE(vt.is_line_dirty(1));
  EXPECT_FALSE(vt.is_line_dirty(2));
}


TEST(CapabilityDch, TreatsZeroParamAsOneChar) {
  TestVtWrapper vt{10, 3};
  write_string(vt, "0123456789");
  EXPECT_EQ(0, vt.get_cursor_pos().c);
  EXPECT_EQ(1, vt.get_cursor_pos().r);

  set_cursor_pos(vt, {.r = 1, .c = 5});
  vt.set_clean();
  write_dch(vt, 0);

  EXPECT_EQ("012356789", vt.get_line_text(0));
  EXPECT_TRUE(vt.is_line_dirty(0));
  EXPECT_FALSE(vt.is_line_dirty(1));
  EXPECT_FALSE(vt.is_line_dirty(2));
}

TEST(CapabilityDch, DeletesLastChar) {
  TestVtWrapper vt{10, 3};
  write_string(vt, "0123456789abcdefghij");
  EXPECT_EQ(0, vt.get_cursor_pos().c);
  EXPECT_EQ(2, vt.get_cursor_pos().r);

  set_cursor_pos(vt, {.r = 1, .c = 10});
  vt.set_clean();
  write_dch(vt, 2);

  EXPECT_EQ("012345678", vt.get_line_text(0));
  EXPECT_TRUE(vt.is_line_dirty(0));

  EXPECT_EQ("abcdefghij", vt.get_line_text(1));
  EXPECT_FALSE(vt.is_line_dirty(1));

  EXPECT_FALSE(vt.is_line_dirty(2));
}

TEST(CapabilityDch, SetsDefaultAttrsForEmptyChars) {
  TestVtWrapper vt{10, 3};
  write_sgr(vt, {36, 47, 5}); // Chosen attributes are arbitrary.
  write_string(vt, "0123456789");
  EXPECT_EQ(0, vt.get_cursor_pos().c);
  EXPECT_EQ(1, vt.get_cursor_pos().r);

  set_cursor_pos(vt, {.r = 1, .c = 5});
  vt.set_clean();
  write_dch(vt, 2);

  EXPECT_EQ("01236789", vt.get_line_text(0));
  EXPECT_NE(default_attrs, vt.get_character(0, 7).a);
  EXPECT_EQ(default_attrs, vt.get_character(0, 8).a);
  EXPECT_EQ(default_attrs, vt.get_character(0, 9).a);

  EXPECT_TRUE(vt.is_line_dirty(0));
  EXPECT_FALSE(vt.is_line_dirty(1));
  EXPECT_FALSE(vt.is_line_dirty(2));
}
