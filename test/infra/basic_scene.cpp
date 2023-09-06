#include "basic_scene.h"
#include "test_helpers.h"

#include "gtest/gtest.h"

using namespace vt_test;

namespace vt_test::basic_scene {
  void set_scene(TestVtWrapper &vt) {
    write_string(vt, "111112222233333444445555");
    vt.set_clean();
  }

  void check_scene_row(const TestVtWrapper &vt, const LineState &row, size_t row_num) {
    EXPECT_EQ(row.is_dirty, vt.is_line_dirty(row_num));
    EXPECT_EQ(row.contents, vt.get_line_text(row_num));
  }

  const DefaultSizeSceneData default_scene_data
      {{
           {false, "11111"},
           {false, "22222"},
           {false, "33333"},
           {false, "44444"},
           {false, "5555"}
       }};
}
