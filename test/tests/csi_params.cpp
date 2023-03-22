#include "../test_includes.h"

using namespace vt_test;

TEST(BasicTests, CSIParams) {
  TestVtWrapper vt(80, 25);

  std::string text = "\u001b[1m\u001b[30mh\u001b[31;1me\u001b[0mllo";
  vt.write_string(text);

  const auto line = tmt_screen(vt.get_vt())->lines[0];

  ASSERT_EQ(line->chars[0].a.fg, TMT_COLOR_BLACK);
  ASSERT_EQ(line->chars[0].a.bold, 1);
  ASSERT_EQ(line->chars[1].a.fg, TMT_COLOR_RED);
  ASSERT_EQ(line->chars[1].a.bold, 1);
  ASSERT_EQ(line->chars[2].a.fg, TMT_COLOR_DEFAULT);
  ASSERT_EQ(line->chars[2].a.bold, 0);
}
