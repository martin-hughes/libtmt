extern "C"
{
#include "tmt.h"
};

#include "../test_helpers.h"
#include "gtest/gtest.h"

TEST(BasicTests, DefaultValues)
{
  TMT* vt = tmt_open(80, 25, normal_callback, nullptr, nullptr);
  //tmt_reset(vt);

  tmt_write(vt, "hello", 5);

  ASSERT_EQ(tmt_screen(vt)->lines[0]->chars[0].a.fg, TMT_COLOR_DEFAULT);

  tmt_close(vt);
}
