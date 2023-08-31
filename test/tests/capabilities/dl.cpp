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

  SceneData expected
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

  SceneData expected
      {{
           {false, "11111"},
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""}
       }};

  check_scene(vt, expected);
}
