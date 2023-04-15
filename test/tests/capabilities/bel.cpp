#include "test/test_includes.h"

using namespace vt_test;

TEST(CapabilityBel, CallbackSentForBell) {
  GMockCallbacks cbs;

  // Update and cursor moved are called as part of setup - see "create_and_destroy.cpp".
  // The bell callback is called as a result of writing the bell string to the terminal.
  EXPECT_CALL(cbs.updateCallback, Call).Times(1);
  EXPECT_CALL(cbs.bellCallback, Call).Times(1);
  EXPECT_CALL(cbs.cursorMovedCallback, Call).Times(1);

  TestVtWrapper vt(80, 3, makeCallbackForGMocks(cbs));

  vt.write_string("\x07");

  ASSERT_FALSE(vt.is_line_dirty(0));
}
