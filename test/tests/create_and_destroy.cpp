#include "../test_includes.h"

using namespace vt_test;

TEST(BasicTests, CreateAndDestroy) {
  // This test is only really useful in two cases:
  // 1- There is a crass bug in tmt_open or tmt_close that trigger a crash
  // 2- The tests are being run with valgrind (or similar)

  GMockCallbacks cbs;
  EXPECT_CALL(cbs.update_callback, Call).Times(1);
  EXPECT_CALL(cbs.cursor_moved_callback, Call).Times(1);

  TestVtWrapper vt(10, 3, make_callback_for_gmocks(cbs));
}
