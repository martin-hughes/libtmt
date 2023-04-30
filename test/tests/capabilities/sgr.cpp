// Test the 'sgr' capability (and related ones such as 'invis' that also issue the same command)
//
// There's a fair amount of intro code in this file, the test fixtures are at the end.

#include "../../test_includes.h"

#include <vector>

using namespace vt_test;

class SgrTestFixture {
public:

  using ModesContainerType = std::vector<unsigned int>;
  using AttributeUpdateType = std::function<TMTATTRS(TMTATTRS test_attrs)>;

  SgrTestFixture(std::string name, ModesContainerType modes, AttributeUpdateType attribute_update_fn) :
      name{std::move(name)}, modes{std::move(modes)}, update_with_expectation{std::move(attribute_update_fn)} {};

  const std::string name;
  const std::vector<unsigned int> modes;
  const std::function<TMTATTRS(TMTATTRS test_attrs)> update_with_expectation;
};

class CapabilitySgr : public testing::TestWithParam<SgrTestFixture> {

};

// Rely on default initialisation setting everything else to false.
const TMTATTRS default_attrs{
    .fg = TMT_COLOR_DEFAULT,
    .bg = TMT_COLOR_DEFAULT
};

constexpr bool operator==(const TMTATTRS &a, const TMTATTRS &b) {
  return
      (a.bold == b.bold) &&
      (a.dim == b.dim) &&
      (a.underline == b.underline) &&
      (a.blink == b.blink) &&
      (a.reverse == b.reverse) &&
      (a.invisible == b.invisible) &&
      (a.fg == b.fg) &&
      (a.bg == b.bg);
}

const std::vector<unsigned int> all_modes{34, 44, 1, 2, 4, 5, 7, 8};
constexpr TMTATTRS all_modes_attrs{
    .bold = true,
    .dim = true,
    .underline = true,
    .blink = true,
    .reverse = true,
    .invisible = true,
    .fg = TMT_COLOR_BLUE,
    .bg = TMT_COLOR_BLUE,
};

TEST_P(CapabilitySgr, MapsModesCorrectlyFromDefaultAttrs) {
  auto fixture = GetParam();

  TestVtWrapper vt(10, 5);

  write_string(vt, "  ");
  write_sgr(vt, fixture.modes);
  write_string(vt, "t"); // 't' for 'test character'

  const auto before_char = vt.get_character(0, 1);
  const auto after_char = vt.get_character(0, 3);
  const auto test_char = vt.get_character(0, 2);

  EXPECT_EQ(default_attrs, before_char.a);
  EXPECT_EQ(fixture.update_with_expectation(default_attrs), test_char.a);
  EXPECT_EQ(default_attrs, after_char.a);
}

TEST_P(CapabilitySgr, MapsModesCorrectlyFromAllAttrs) {
  auto fixture = GetParam();

  TestVtWrapper vt(10, 5);

  write_sgr(vt, all_modes);
  write_string(vt, "  ");
  write_string(vt, "t "); // 't' for 'test character'

  write_cursor_move(vt, CursorMoveDir::Left, 2);
  write_sgr(vt, fixture.modes);
  write_string(vt, "t");

  const auto before_char = vt.get_character(0, 1);
  const auto after_char = vt.get_character(0, 3);
  const auto test_char = vt.get_character(0, 2);

  EXPECT_EQ(all_modes_attrs, before_char.a);
  const auto expectation = fixture.update_with_expectation(all_modes_attrs);
  EXPECT_EQ(expectation, test_char.a);
  EXPECT_EQ(all_modes_attrs, after_char.a);
}

INSTANTIATE_TEST_SUITE_P(
    MainSet,
    CapabilitySgr,
    testing::Values(
        SgrTestFixture{
            "SetAllModesToDefault",
            {0},
            [](auto a) { return default_attrs; }},
        SgrTestFixture{
            "SetBold",
            {1},
            [](auto a) {
              a.bold = true;
              return a;
            }},
        SgrTestFixture{
            "UnsetBold",
            {22},
            [](auto a) {
              a.bold = false;
              return a;
            }},
        SgrTestFixture{
            "SetDim",
            {2},
            [](auto a) {
              a.dim = true;
              return a;
            }},
        // TODO: Check this value - I think maybe it should be 22. But 'dim' isn't an ansi mode anyway.
        SgrTestFixture{
            "UnsetDim",
            {23},
            [](auto a) {
              a.dim = false;
              return a;
            }},
        SgrTestFixture{
            "SetUnderline",
            {4},
            [](auto a) {
              a.underline = true;
              return a;
            }},
        SgrTestFixture{
            "UnsetUnderline",
            {24},
            [](auto a) {
              a.underline = false;
              return a;
            }},
        SgrTestFixture{
            "SetBlink",
            {5},
            [](auto a) {
              a.blink = true;
              return a;
            }},
        SgrTestFixture{
            "UnsetBlink",
            {25},
            [](auto a) {
              a.blink = false;
              return a;
            }},
        SgrTestFixture{
            "SetReverse",
            {7},
            [](auto a) {
              a.reverse = true;
              return a;
            }},
        SgrTestFixture{
            "UnsetReverse",
            {27},
            [](auto a) {
              a.reverse = false;
              return a;
            }},
        SgrTestFixture{
            "SetInvisible",
            {8},
            [](auto a) {
              a.invisible = true;
              return a;
            }},
        SgrTestFixture{
            "UnsetInvisible",
            {28},
            [](auto a) {
              a.invisible = false;
              return a;
            }},
        SgrTestFixture{
            "SetForegroundBlack",
            {30},
            [](auto a) {
              a.fg = TMT_COLOR_BLACK;
              return a;
            }},
        SgrTestFixture{
            "SetForegroundRed",
            {31},
            [](auto a) {
              a.fg = TMT_COLOR_RED;
              return a;
            }},
        SgrTestFixture{
            "SetForegroundGreen",
            {32},
            [](auto a) {
              a.fg = TMT_COLOR_GREEN;
              return a;
            }},
        SgrTestFixture{
            "SetForegroundYellow",
            {33},
            [](auto a) {
              a.fg = TMT_COLOR_YELLOW;
              return a;
            }},
        SgrTestFixture{
            "SetForegroundBlue",
            {34},
            [](auto a) {
              a.fg = TMT_COLOR_BLUE;
              return a;
            }},
        SgrTestFixture{
            "SetForegroundMagenta",
            {35},
            [](auto a) {
              a.fg = TMT_COLOR_MAGENTA;
              return a;
            }},
        SgrTestFixture{
            "SetForegroundCyan",
            {36},
            [](auto a) {
              a.fg = TMT_COLOR_CYAN;
              return a;
            }},
        SgrTestFixture{
            "SetForegroundWhite",
            {37},
            [](auto a) {
              a.fg = TMT_COLOR_WHITE;
              return a;
            }},
        SgrTestFixture{
            "SetForegroundDefault",
            {39},
            [](auto a) {
              a.fg = TMT_COLOR_DEFAULT;
              return a;
            }},
        SgrTestFixture{
            "SetBackgroundBlack",
            {40},
            [](auto a) {
              a.bg = TMT_COLOR_BLACK;
              return a;
            }},
        SgrTestFixture{
            "SetBackgroundRed",
            {41},
            [](auto a) {
              a.bg = TMT_COLOR_RED;
              return a;
            }},
        SgrTestFixture{
            "SetBackgroundGreen",
            {42},
            [](auto a) {
              a.bg = TMT_COLOR_GREEN;
              return a;
            }},
        SgrTestFixture{
            "SetBackgroundYellow",
            {43},
            [](auto a) {
              a.bg = TMT_COLOR_YELLOW;
              return a;
            }},
        SgrTestFixture{
            "SetBackgroundBlue",
            {44},
            [](auto a) {
              a.bg = TMT_COLOR_BLUE;
              return a;
            }},
        SgrTestFixture{
            "SetBackgroundMagenta",
            {45},
            [](auto a) {
              a.bg = TMT_COLOR_MAGENTA;
              return a;
            }},
        SgrTestFixture{
            "SetBackgroundCyan",
            {46},
            [](auto a) {
              a.bg = TMT_COLOR_CYAN;
              return a;
            }},
        SgrTestFixture{
            "SetBackgroundWhite",
            {47},
            [](auto a) {
              a.bg = TMT_COLOR_WHITE;
              return a;
            }},
        SgrTestFixture{
            "SetBackgroundDefault",
            {49},
            [](auto a) {
              a.bg = TMT_COLOR_DEFAULT;
              return a;
            }},
        SgrTestFixture{
            "SetBackgroundAndForeground",
            {32, 43},
            [](auto a) {
              a.fg = TMT_COLOR_GREEN;
              a.bg = TMT_COLOR_YELLOW;
              return a;
            }},
        SgrTestFixture{
            "SetAndUnsetSomeModes",
            {1, 22, 4, 24},
            [](auto a) {
              a.bold = false;
              a.underline = false;
              return a;
            }},
        SgrTestFixture{
            "EighthParamIncluded",
            {1, 1, 1, 1, 1, 1, 1, 22},
            [](auto a) {
              a.bold = false;
              return a;
            }},
        SgrTestFixture{
            "NinthParamIgnored",
            {1, 1, 1, 1, 1, 1, 1, 1, 22},
            [](auto a) {
              a.bold = true;
              return a;
            }}
    ),
    [](const auto &info) {
      // Can use info.param here to generate the test suffix
      return info.param.name;
    }
);