#include "../../test_includes.h"

using namespace vt_test;
using namespace vt_test::basic_scene;

TEST(CapabilityIndn, NoParameterScrollsOneLine) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 3});

  write_csi(vt);
  write_string(vt, "S");

  DefaultSizeSceneData expected
      {{
           {true, "22222"},
           {true, "33333"},
           {true, "44444"},
           {true, "5555"},
           {true, ""}
       }};

  check_scene(vt, expected);

  // Check the cursor doesn't move.
  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(2, pos.c);
  EXPECT_EQ(1, pos.r);
}

TEST(CapabilityIndn, ValidParameterScrollsAsExpected) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);

  write_csi(vt);
  write_string(vt, "2S");

  DefaultSizeSceneData expected
      {{
           {true, "33333"},
           {true, "44444"},
           {true, "5555"},
           {true, ""},
           {true, ""}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityIndn, ExcessiveParameterTruncated) {
  // libtmt stops scrolling when the last line reaches the top of the screen
  TestVtWrapper vt(5, 5);
  set_scene(vt);

  write_csi(vt);
  write_string(vt, "100S");

  DefaultSizeSceneData expected
      {{
           {true, "5555"},
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityIndn, ZeroParameterScrollsOneLine) {
  // If zero is provided, it is incremented to one.
  //
  // See https://terminalguide.namepad.de/seq/csi_cs/

  TestVtWrapper vt(5, 5);
  set_scene(vt);

  write_csi(vt);
  write_string(vt, "0S");

  DefaultSizeSceneData expected
      {{
           {true, "22222"},
           {true, "33333"},
           {true, "44444"},
           {true, "5555"},
           {true, ""}
       }};

  check_scene(vt, expected);
}
