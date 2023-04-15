#include "../test_includes.h"

TEST(BasicTests, CreateAndDestroy)
{
  // This test is only really useful in two cases:
  // 1- There is a crass bug in tmt_open or tmt_close that trigger a crash
  // 2- The tests are being run with valgrind (or similar)

  TMT* vt = tmt_open(80, 25, nullptr, nullptr, nullptr);

  tmt_close(vt);
}
