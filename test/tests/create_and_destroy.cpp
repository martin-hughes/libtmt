#include "../test_includes.h"

TEST(BasicTests, CreateAndDestroy)
{
  TMT* vt = tmt_open(80, 25, normal_callback, nullptr, nullptr);

  tmt_close(vt);
}
