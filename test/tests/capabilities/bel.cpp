#include "test/test_includes.h"

using namespace vt_test;

TEST(CapabilityBel, CallbackSentForBell) {
  GMockCallbacks cbs;

  // Update and cursor moved are called as part of setup - see "create_and_destroy.cpp".
  // The bell callback is called as a result of writing the bell string to the terminal.
  EXPECT_CALL(cbs.update_callback, Call).Times(1);
  EXPECT_CALL(cbs.bell_callback, Call).Times(1);
  EXPECT_CALL(cbs.cursor_moved_callback, Call).Times(1);

  TestVtWrapper vt(80, 3, make_callback_for_gmocks(cbs));

  vt.write_string("\x07");

  ASSERT_FALSE(vt.is_line_dirty(0));
}
