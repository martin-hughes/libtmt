#include "test/test_includes.h"

using namespace vt_test;;
using namespace vt_test::basic_scene;

namespace {
  void write_rep(TestVtWrapper &vt, std::optional<int> reps = std::nullopt) {
    write_csi(vt);

    if (reps) {
      write_string(vt, std::to_string(*reps));
    }

    write_string(vt, "b");
  }
}

TEST(CapabilityRep, RepeatsPreviousPrintableCharacter) {
  TestVtWrapper vt{10, 3};

  write_string(vt, "a");
  write_rep(vt, 12);

  const SceneData<3> expected
      {{
           {true, "aaaaaaaaaa"},
           {true, "aaa"},
           {false, ""}
       }};

  check_scene(vt, expected);

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(3, pos.c);
  EXPECT_EQ(1, pos.r);
}

TEST(CapabilityRep, RepeatsAfterImplicitNewline) {
  TestVtWrapper vt{10, 3};

  write_string(vt, "aaaaaaaaab");
  vt.set_clean();
  write_rep(vt, 3);

  const SceneData<3> expected
      {{
           {false, "aaaaaaaaab"},
           {true, "bbb"},
           {false, ""}
       }};

  check_scene(vt, expected);

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(3, pos.c);
  EXPECT_EQ(1, pos.r);
}

TEST(CapabilityRep, DoesntRepeatTwice) {
  TestVtWrapper vt{10, 3};

  write_string(vt, "a");
  write_rep(vt, 3);
  write_rep(vt, 5);

  const SceneData<3> expected
      {{
           {true, "aaaa"},
           {false, ""},
           {false, ""}
       }};

  check_scene(vt, expected);

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(4, pos.c);
  EXPECT_EQ(0, pos.r);
}

TEST(CapabilityRep, DoesntRepeatIfNothingPrinted) {
  TestVtWrapper vt{10, 3};
  vt.set_clean();

  write_rep(vt, 3);

  const SceneData<3> expected
      {{
           {false, ""},
           {false, ""},
           {false, ""}
       }};

  check_scene(vt, expected);

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(0, pos.c);
  EXPECT_EQ(0, pos.r);
}

TEST(CapabilityRep, DoesntRepeatAfterReset) {
  TestVtWrapper vt{10, 3};
  vt.set_clean();

  write_string(vt, "this will disappear");
  vt.set_clean();

  tmt_reset(vt.get_vt());

  write_rep(vt, 3);

  // The dirty flags are set as a result of the reset.
  const SceneData<3> expected
      {{
           {true, ""},
           {true, ""},
           {true, ""}
       }};

  check_scene(vt, expected);

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(0, pos.c);
  EXPECT_EQ(0, pos.r);
}

TEST(CapabilityRep, DoesntRepeatAfterOtherControlSequence) {
  TestVtWrapper vt{10, 3};

  write_string(vt, "a");
  write_sgr(vt, {5});
  write_rep(vt, 12);

  const SceneData<3> expected
      {{
           {true, "a"},
           {false, ""},
           {false, ""}
       }};

  check_scene(vt, expected);

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(1, pos.c);
  EXPECT_EQ(0, pos.r);
}

TEST(CapabilityRep, DoesntRepeatAfterNonPrintableChar) {
  TestVtWrapper vt{10, 3};

  write_string(vt, "a\31");
  write_rep(vt, 12);

  const SceneData<3> expected
      {{
           {true, "a\31"},
           {false, ""},
           {false, ""}
       }};

  check_scene(vt, expected);

  const auto pos = vt.get_cursor_pos();
  EXPECT_EQ(2, pos.c);
  EXPECT_EQ(0, pos.r);
}
