#include "test/test_includes.h"

using namespace vt_test;
using namespace vt_test::basic_scene;

TEST(CapabilityEd, DefaultClearsBelow) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 3});

  write_erase(vt);

  SceneData expected
      {{
           {false, "11111"},
           {true, "22"},
           {true, ""},
           {true, ""},
           {true, ""}
       }};

  check_scene(vt, expected);

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(2, pos.c);
  EXPECT_EQ(1, pos.r);
}

TEST(CapabilityEd, ClearsBelowWhenRequested) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 3});

  write_erase(vt, EraseDirection::Below);

  SceneData expected
      {{
           {false, "11111"},
           {true, "22"},
           {true, ""},
           {true, ""},
           {true, ""}
       }};

  check_scene(vt, expected);

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(2, pos.c);
  EXPECT_EQ(1, pos.r);
}

TEST(CapabilityEd, ClearBelowWorksAtBottom) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 5, .c = 3});

  write_erase(vt, EraseDirection::Below);

  SceneData expected
      {{
           {false, "11111"},
           {false, "22222"},
           {false, "33333"},
           {false, "44444"},
           {true, "55"}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityEd, ClearBelowWorksInLeftCol) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 1});

  write_erase(vt, EraseDirection::Below);

  SceneData expected
      {{
           {false, "11111"},
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""},
       }};

  check_scene(vt, expected);
}

TEST(CapabilityEd, ClearBelowWorksInRightCol) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c =5});

  write_erase(vt, EraseDirection::Below);

  SceneData expected
      {{
           {false, "11111"},
           {true, "2222"},
           {true, ""},
           {true, ""},
           {true, ""}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityEd, ClearBelowWorksAtTop) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 1, .c = 3});

  write_erase(vt, EraseDirection::Below);

  SceneData expected
      {{
           {true, "11"},
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""},
       }};

  check_scene(vt, expected);
}

TEST(CapabilityEd, ClearBelowWorksAtOrigin) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 1, .c = 1});

  write_erase(vt, EraseDirection::Below);

  SceneData expected
      {{
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""},
       }};

  check_scene(vt, expected);
}

TEST(CapabilityEd, ClearBelowWorksAtEnd) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 5, .c = 5});

  write_erase(vt, EraseDirection::Below);

  SceneData expected
      {{
           {false, "11111"},
           {false, "22222"},
           {false, "33333"},
           {false, "44444"},
           {true, "5555"}, // Even though no changes are made, dirty is still set.
       }};

  check_scene(vt, expected);
}

TEST(CapabilityEd, ClearsAboveWhenRequested) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 3});

  write_erase(vt, EraseDirection::Above);

  SceneData expected
      {{
           {true, ""},
           {true, "  222"},
           {false, "33333"},
           {false, "44444"},
           {false, "5555"}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityEd, ClearAboveWorksAtBottom) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 5, .c = 3});

  write_erase(vt, EraseDirection::Above);

  SceneData expected
      {{
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""},
           {true, "  55"}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityEd, ClearAboveWorksInLeftCol) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 1});

  write_erase(vt, EraseDirection::Above);

  SceneData expected
      {{
           {true, ""},
           {true, "22222"},
           {false, "33333"},
           {false, "44444"},
           {false, "5555"}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityEd, ClearAboveWorksInRightCol) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c =5});

  write_erase(vt, EraseDirection::Above);

  SceneData expected
      {{
           {true, ""},
           {true, "    2"},
           {false, "33333"},
           {false, "44444"},
           {false, "5555"}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityEd, ClearAboveWorksWhenAtTop) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 1, .c = 3});

  write_erase(vt, EraseDirection::Above);

  SceneData expected
      {{
           {true, "  111"},
           {false, "22222"},
           {false, "33333"},
           {false, "44444"},
           {false, "5555"}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityEd, ClearAboveWorksAtOrigin) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 1, .c = 1});

  write_erase(vt, EraseDirection::Above);

  SceneData expected
      {{
           {true, "11111"}, // Even though no changes are made, dirty is still set.
           {false, "22222"},
           {false, "33333"},
           {false, "44444"},
           {false, "5555"},
       }};

  check_scene(vt, expected);
}

TEST(CapabilityEd, ClearAboveWorksAtEnd) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 5, .c = 5});

  write_erase(vt, EraseDirection::Above);

  SceneData expected
      {{
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""},
       }};

  check_scene(vt, expected);
}

TEST(CapabilityEd, ClearsCompletelyWhenRequested) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 3});

  write_erase(vt, EraseDirection::Complete);

  SceneData expected
      {{
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityEd, ClearCompletelyWorksAtBottom) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 5, .c = 3});

  write_erase(vt, EraseDirection::Complete);

  SceneData expected
      {{
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityEd, ClearCompletelyWorksInLeftCol) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c = 1});

  write_erase(vt, EraseDirection::Complete);

  SceneData expected
      {{
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityEd, ClearCompletelyWorksInRightCol) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 2, .c =5});

  write_erase(vt, EraseDirection::Complete);

  SceneData expected
      {{
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityEd, ClearCompletelyWorksWhenAtTop) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 1, .c = 3});

  write_erase(vt, EraseDirection::Complete);

  SceneData expected
      {{
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityEd, ClearCompletelyWorksAtOrigin) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 1, .c = 1});

  write_erase(vt, EraseDirection::Complete);

  SceneData expected
      {{
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""}
       }};

  check_scene(vt, expected);
}

TEST(CapabilityEd, ClearCompletelyWorksAtEnd) {
  TestVtWrapper vt(5, 5);
  set_scene(vt);
  set_cursor_pos(vt, {.r = 5, .c = 5});

  write_erase(vt, EraseDirection::Complete);

  SceneData expected
      {{
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""},
           {true, ""},
       }};

  check_scene(vt, expected);
}
