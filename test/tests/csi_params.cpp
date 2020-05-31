extern "C"
{
#include "tmt.h"
};

#include "../test_helpers.h"
#include "gtest/gtest.h"

TEST(BasicTests, CSIParams)
{
  TMT* vt = tmt_open(80, 25, normal_callback, nullptr, nullptr);
  //tmt_reset(vt);

  const char *str = "\u001b[1m\u001b[30mh\u001b[31;1me\u001b[0mllo";
  tmt_write(vt, str, strlen(str));

  ASSERT_EQ(tmt_screen(vt)->lines[0]->chars[0].a.fg, TMT_COLOR_BLACK);
  ASSERT_EQ(tmt_screen(vt)->lines[0]->chars[0].a.bold, 1);
  ASSERT_EQ(tmt_screen(vt)->lines[0]->chars[1].a.fg, TMT_COLOR_RED);
  ASSERT_EQ(tmt_screen(vt)->lines[0]->chars[1].a.bold, 1);
  ASSERT_EQ(tmt_screen(vt)->lines[0]->chars[2].a.fg, TMT_COLOR_DEFAULT);
  ASSERT_EQ(tmt_screen(vt)->lines[0]->chars[2].a.bold, 0);

  tmt_close(vt);
}
