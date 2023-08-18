#include "../../test_includes.h"

using namespace vt_test;

class HtTestFixture {
public:
  const std::string_view command;
  const std::string_view name;
};

class CapabilityHt : public testing::TestWithParam<HtTestFixture> {

};

TEST_P(CapabilityHt, MovesBetweenTabs) {
  const auto command = GetParam().command;

  TestVtWrapper vt{20, 3};

  write_string(vt, command);
  EXPECT_EQ(8, vt.get_cursor_pos().c);

  write_string(vt, command);
  EXPECT_EQ(16, vt.get_cursor_pos().c);

  write_string(vt, command);
  EXPECT_EQ(19, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);
}

TEST_P(CapabilityHt, MovesToNextTabWhenInBetween) {
  const auto command = GetParam().command;

  TestVtWrapper vt{20, 3};

  set_cursor_pos(vt, {.r = 1, .c = 13});

  write_string(vt, command);
  EXPECT_EQ(16, vt.get_cursor_pos().c);
  EXPECT_EQ(0, vt.get_cursor_pos().r);
}

TEST_P(CapabilityHt, DoesNotTabPastEndColumn) {
  const auto command = GetParam().command;

  TestVtWrapper vt{20, 3};

  set_cursor_pos(vt, {.r = 1, .c = 17});

  write_string(vt, command);
  EXPECT_EQ(19, vt.get_cursor_pos().c);

  write_string(vt, command);
  EXPECT_EQ(19, vt.get_cursor_pos().c);

  EXPECT_EQ(0, vt.get_cursor_pos().r);
}

INSTANTIATE_TEST_SUITE_P(
    MainSet,
    CapabilityHt,
    testing::Values(
        HtTestFixture{
            "\t",
            "NormalTab"
        },
        HtTestFixture{
            "\x1b[I",
            "HtCommandSequence"
        }
    ),
    [](const auto &info) {
      // Can use info.param here to generate the test suffix
      return std::string{info.param.name};
    });
