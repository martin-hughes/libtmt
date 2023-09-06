#include "test/test_includes.h"

using namespace vt_test;
using namespace vt_test::basic_scene;

namespace {
  void write_il(TestVtWrapper &vt, std::optional<const unsigned int> rows) {
    write_csi(vt);

    if (rows.has_value()) {
      write_string(vt, std::to_string(rows.value()));
    }

    write_string(vt, "L");
  }
}

TEST(CapabilityIl, InsertsRows) {
  TestVtWrapper vt{5, 5};
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 3});

  write_il(vt, 2);

  DefaultSizeSceneData expected
      {{
           {false, "11111"},
           {true, ""},
           {true, ""},
           {true, "22222"},
           {true, "33333"}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityIl, InsertsIsLimitedByNumberOfRows) {
  TestVtWrapper vt{5, 5};
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 3});

  write_il(vt, 200);

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

TEST(CapabilityIl, TreatsNoParamAsOneRow) {
  TestVtWrapper vt{5, 5};
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 3});

  write_il(vt, std::nullopt);

  DefaultSizeSceneData expected
      {{
           {false, "11111"},
           {true, ""},
           {true, "22222"},
           {true, "33333"},
           {true, "44444"}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityIl, TreatsZeroParamAsOneRow) {
  TestVtWrapper vt{5, 5};
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 3});

  write_il(vt, 0);

  DefaultSizeSceneData expected
      {{
           {false, "11111"},
           {true, ""},
           {true, "22222"},
           {true, "33333"},
           {true, "44444"}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityIl, InsertsAtTopRow) {
  TestVtWrapper vt{5, 5};
  set_scene(vt);
  set_cursor_pos(vt, {.r = 1, .c = 3});

  write_il(vt, 1);

  DefaultSizeSceneData expected
      {{
           {true, ""},
           {true, "11111"},
           {true, "22222"},
           {true, "33333"},
           {true, "44444"}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityIl, DeletesBottomRow) {
  TestVtWrapper vt{5, 5};
  set_scene(vt);
  set_cursor_pos(vt, {.r = 5, .c = 3});

  write_il(vt, 1);

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
