#include "test/test_includes.h"

using namespace vt_test;
using namespace vt_test::basic_scene;

namespace {
  void write_dl(TestVtWrapper &vt, std::optional<const unsigned int> rows) {
    write_csi(vt);

    if (rows.has_value()) {
      write_string(vt, std::to_string(rows.value()));
    }

    write_string(vt, "M");
  }
}

TEST(CapabilityDl, DeletesRows) {
  TestVtWrapper vt{5, 5};
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 3});

  write_dl(vt, 2);

  DefaultSizeSceneData expected
      {{
           {false, "11111"},
           {true, "44444"},
           {true, "5555"},
           {true, ""},
           {true, ""}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityDl, DeletesIsLimitedByNumberOfRows) {
  TestVtWrapper vt{5, 5};
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 3});

  write_dl(vt, 200);

  DefaultSizeSceneData expected
      {{
           {false, "11111"},
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityDl, TreatsNoParamAsOneRow) {
  TestVtWrapper vt{5, 5};
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 3});

  write_dl(vt, std::nullopt);

  DefaultSizeSceneData expected
      {{
           {false, "11111"},
           {true, "33333"},
           {true, "44444"},
           {true, "5555"},
           {true, ""}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityDl, TreatsZeroParamAsOneRow) {
  TestVtWrapper vt{5, 5};
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 3});

  write_dl(vt, 0);

  DefaultSizeSceneData expected
      {{
           {false, "11111"},
           {true, "33333"},
           {true, "44444"},
           {true, "5555"},
           {true, ""}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityDl, DeletesTopRow) {
  TestVtWrapper vt{5, 5};
  set_scene(vt);
  set_cursor_pos(vt, {.r = 1, .c = 3});

  write_dl(vt, 1);

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

TEST(CapabilityDl, DeletesBottomRow) {
  TestVtWrapper vt{5, 5};
  set_scene(vt);
  set_cursor_pos(vt, {.r = 5, .c = 3});

  write_dl(vt, 1);

  DefaultSizeSceneData expected
      {{
           {false, "11111"},
           {false, "22222"},
           {false, "33333"},
           {false, "44444"},
           {true, ""}
       }};

  check_scene(vt, expected);
}
