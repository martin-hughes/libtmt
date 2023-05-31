// u8 and u9 are very similar, so test them together.

#include "../../test_includes.h"

using namespace vt_test;

TEST(CapabilityU9, SimpleTest) {
  GMockCallbacks cbs;
  EXPECT_CALL(cbs.answer_callback, Call("\033[?6c")).Times(1);

  TestVtWrapper vt(10, 3, make_callback_for_gmocks(cbs), false);

  write_csi(vt);
  write_string(vt, "c");
}

TEST(CapabilityU8, SimpleTest) {
  GMockCallbacks cbs;
  EXPECT_CALL(cbs.answer_callback, Call("\033[?6c")).Times(1);

  TestVtWrapper vt(10, 3, make_callback_for_gmocks(cbs), false);

  write_csi(vt);
  write_string(vt, "1c");
}

TEST(CapabilityU8, ZeroParameterAlsoOk) {
  GMockCallbacks cbs;
  EXPECT_CALL(cbs.answer_callback, Call("\033[?6c")).Times(1);

  TestVtWrapper vt(10, 3, make_callback_for_gmocks(cbs), false);

  write_csi(vt);
  write_string(vt, "0c");
}