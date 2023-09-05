#include "basic_scene.h"
#include "test_helpers.h"

#include "gtest/gtest.h"

using namespace vt_test;

namespace vt_test::basic_scene {
  void set_scene(TestVtWrapper &vt) {
    write_string(vt, "111112222233333444445555");
    vt.set_clean();
  }

  void check_scene(const TestVtWrapper &vt, const SceneData &contents) {
    for (size_t i = 0; i < test_rows; i++) {
      EXPECT_EQ(contents[i].is_dirty, vt.is_line_dirty(i));
      EXPECT_EQ(contents[i].contents, vt.get_line_text(i));
    }
  }

  const SceneData default_scene_data
      {{
           {false, "11111"},
           {false, "22222"},
           {false, "33333"},
           {false, "44444"},
           {false, "5555"}
       }};
}
