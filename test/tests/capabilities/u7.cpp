// For libtmt, u7 is treated as though it's dsr(6) even though that's not (AFAICT) specified anywhere - \E[6n could do
// anything, but libtmt follows the convention of most terminals to return the cursor position.

#include "../../test_includes.h"

using namespace vt_test;

bool operator==(const TMTPOINT a, const TMTPOINT b) {
  return (a.c == b.c) && (a.r == b.r);
}

TEST(CapabilityU7, SimpleTest) {
  GMockCallbacks cbs;

  // Remember that libtmt uses zero-indexed cursor position internally.
  const TMTPOINT a{.r = 0, .c = 2};

  EXPECT_CALL(cbs.update_callback, Call).Times(testing::AtLeast(1));
  EXPECT_CALL(cbs.cursor_moved_callback, Call(a)).Times(1);
  EXPECT_CALL(cbs.answer_callback, Call("\033[1;3R")).Times(1);

  TestVtWrapper vt(10, 3, make_callback_for_gmocks(cbs), false);

  write_string(vt, "ab");

  write_csi(vt);
  write_string(vt, "6n");
}
