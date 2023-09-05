#include "test/test_includes.h"

using namespace vt_test;
using namespace vt_test::basic_scene;

namespace {

  void set_ich_scene(TestVtWrapper &vt) {
    write_string(vt, "12345abcde67890ABCDEfghi");
    vt.set_clean();
  }

  const SceneData default_ich_scene_data
      {{
           {false, "12345"},
           {false, "abcde"},
           {false, "67890"},
           {false, "ABCDE"},
           {false, "fghi"}
       }};

  void write_ich(TestVtWrapper &vt, std::optional<int> num_characters = std::nullopt) {
    write_csi(vt);
    if (num_characters) {
      write_string(vt, std::to_string(*num_characters));
    }

    write_string(vt, "@");
  }
}

TEST(CapabilityEl, InsertsOneCharByDefault) {
  TestVtWrapper vt(5, 5);
  set_ich_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 3});

  write_ich(vt);

  SceneData expected = default_ich_scene_data;
  expected[1] = {true, "ab cd"};

  check_scene(vt, expected);

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(2, pos.c);
  EXPECT_EQ(1, pos.r);
}

TEST(CapabilityEl, InsertsSmallNumber) {
  TestVtWrapper vt(5, 5);
  set_ich_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 3});

  write_ich(vt, 2);

  SceneData expected = default_ich_scene_data;
  expected[1] = {true, "ab  c"};

  check_scene(vt, expected);

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(2, pos.c);
  EXPECT_EQ(1, pos.r);
}

TEST(CapabilityEl, TruncatesInsertOfTooLargeNumber) {
  TestVtWrapper vt(5, 5);
  set_ich_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 3});

  write_ich(vt, 20);

  SceneData expected = default_ich_scene_data;
  expected[1] = {true, "ab"};

  check_scene(vt, expected);

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(2, pos.c);
  EXPECT_EQ(1, pos.r);
}

TEST(CapabilityEl, InsertsFromFirstCol) {
  TestVtWrapper vt(5, 5);
  set_ich_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 1});

  write_ich(vt, 3);

  SceneData expected = default_ich_scene_data;
  expected[1] = {true, "   ab"};

  check_scene(vt, expected);

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(0, pos.c);
  EXPECT_EQ(1, pos.r);
}

TEST(CapabilityEl, InsertsAcrossWholeRowIfNeeded) {
  TestVtWrapper vt(5, 5);
  set_ich_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 1});

  write_ich(vt, 10);

  SceneData expected = default_ich_scene_data;
  expected[1] = {true, ""};

  check_scene(vt, expected);

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(0, pos.c);
  EXPECT_EQ(1, pos.r);
}

TEST(CapabilityEl, InsertsOkInLastColumn) {
  TestVtWrapper vt(5, 5);
  set_ich_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 5});

  write_ich(vt, 2);

  SceneData expected = default_ich_scene_data;
  expected[1] = {true, "abcd"};

  check_scene(vt, expected);

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(4, pos.c);
  EXPECT_EQ(1, pos.r);
}
