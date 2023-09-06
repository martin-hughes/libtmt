#include "test/test_includes.h"

using namespace vt_test;
using namespace vt_test::basic_scene;

namespace {
  void write_el(TestVtWrapper &vt, std::optional<int> command = std::nullopt) {
    write_csi(vt);
    if (command) {
      write_string(vt, std::to_string(*command));
    }

    write_string(vt, "K");
  }
}

TEST(CapabilityEl, ClearsToEndByDefault) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 3});

  write_el(vt);

  DefaultSizeSceneData expected = default_scene_data;
  expected[1] = {true, "22"};

  check_scene(vt, expected);

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(2, pos.c);
  EXPECT_EQ(1, pos.r);
}

TEST(CapabilityEl, ClearsLastCharIfClearRightAtEbd) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 5});

  write_el(vt);

  DefaultSizeSceneData expected = default_scene_data;
  expected[1] = {true, "2222"};

  check_scene(vt, expected);
}

TEST(CapabilityEl, ClearsToEndWithZeroParam) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 3});

  write_el(vt, 0);

  DefaultSizeSceneData expected = default_scene_data;
  expected[1] = {true, "22"};

  check_scene(vt, expected);

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(2, pos.c);
  EXPECT_EQ(1, pos.r);
}

TEST(CapabilityEl, ClearsToStartWithOneParam) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 3});

  write_el(vt, 1);

  DefaultSizeSceneData expected = default_scene_data;
  expected[1] = {true, "   22"};

  check_scene(vt, expected);

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(2, pos.c);
  EXPECT_EQ(1, pos.r);
}

TEST(CapabilityEl, ClearsFirstCellInFirstCol) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 1});

  write_el(vt, 1);

  DefaultSizeSceneData expected = default_scene_data;
  expected[1] = {true, " 2222"};

  check_scene(vt, expected);
}

TEST(CapabilityEl, ClearsCompleteLineWithTwoParam) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 3});

  write_el(vt, 2);

  DefaultSizeSceneData expected = default_scene_data;
  expected[1] = {true, ""};

  check_scene(vt, expected);

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(2, pos.c);
  EXPECT_EQ(1, pos.r);
}

TEST(CapabilityEl, IgnoresInvalidParam) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 3});

  write_el(vt, 4);

  check_scene(vt, default_scene_data);

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(2, pos.c);
  EXPECT_EQ(1, pos.r);
}

