// Tests cu[p1](b|d|f|u) and kbs - cursor movement in the 4 directions, and backspace

#include "../../test_includes.h"

using namespace vt_test;

class CuxTestFixture {
public:
  CuxTestFixture(
      const std::string_view name,
      TMTPOINT start,
      const std::string_view command,
      TMTPOINT end,
      bool send_csi = true) :
      name{name}, start{start}, command{command}, end{end}, send_csi{send_csi} {};

  const std::string_view name;
  TMTPOINT start;
  const std::string_view command;
  TMTPOINT end;
  bool send_csi;
};

class CapabilityCux : public testing::TestWithParam<CuxTestFixture> {

};

TEST_P(CapabilityCux, StandardTest) {
  const auto fixture = GetParam();

  TestVtWrapper vt{10, 10};
  set_cursor_pos(vt, fixture.start);

  if (fixture.send_csi) {
    write_csi(vt);
  }
  write_string(vt, fixture.command);

  const auto result = vt.get_cursor_pos();

  // Remember that tmt returns cursor positions zero-indexed, but setting position is one-indexed.
  EXPECT_EQ(result.c + 1, fixture.end.c);
  EXPECT_EQ(result.r + 1, fixture.end.r);
}

INSTANTIATE_TEST_SUITE_P(
    MainSet,
    CapabilityCux,
    testing::Values(
        // LEFT
        CuxTestFixture{
            "LeftNoParamMovesOnePlace",
            {5, 5},
            "D",
            {5, 4}
        },
        CuxTestFixture{
            "LeftWithParam",
            {5, 5},
            "2D",
            {5, 3}
        },
        CuxTestFixture{
            "LeftZeroParmChangedToOne",
            {5, 5},
            "0D",
            {5, 4}
        },
        CuxTestFixture{
            "LeftDoesNotExceedBoundary",
            {5, 5},
            "100D",
            {5, 1}
        },
        CuxTestFixture{
            "LeftFromLeftNoChange",
            {5, 1},
            "D",
            {5, 1}
        },
        CuxTestFixture{
            "LeftFromRightWorks",
            {5, 10},
            "9D",
            {5, 1}
        },

        // RIGHT
        CuxTestFixture{
            "RightNoParamMovesOnePlace",
            {5, 5},
            "C",
            {5, 6}
        },
        CuxTestFixture{
            "RightWithParam",
            {5, 5},
            "2C",
            {5, 7}
        },
        CuxTestFixture{
            "RightZeroParmChangedToOne",
            {5, 5},
            "0C",
            {5, 6}
        },
        CuxTestFixture{
            "RightDoesNotExceedBoundary",
            {5, 5},
            "100C",
            {5, 10}
        },
        CuxTestFixture{
            "RightFromRightNoChange",
            {5, 10},
            "C",
            {5, 10}
        },

        // UP
        CuxTestFixture{
            "UpNoParamMovesOnePlace",
            {5, 5},
            "A",
            {4, 5}
        },
        CuxTestFixture{
            "UpWithParam",
            {5, 5},
            "2A",
            {3, 5}
        },
        CuxTestFixture{
            "UpZeroParmChangedToOne",
            {5, 5},
            "0A",
            {4, 5}
        },
        CuxTestFixture{
            "UpDoesNotExceedBoundary",
            {5, 5},
            "100A",
            {1, 5}
        },
        CuxTestFixture{
            "UpFromTopNoChange",
            {1, 5},
            "A",
            {1, 5}
        },
        CuxTestFixture{
            "UpFromBottomWorks",
            {10, 5},
            "9A",
            {1, 5}
        },

        // DOWN
        CuxTestFixture{
            "DownNoParamMovesOnePlace",
            {5, 5},
            "B",
            {6, 5}
        },
        CuxTestFixture{
            "DownWithParam",
            {5, 5},
            "2B",
            {7, 5}
        },
        CuxTestFixture{
            "DownZeroParmChangedToOne",
            {5, 5},
            "0B",
            {6, 5}
        },
        CuxTestFixture{
            "DownDoesNotExceedBoundary",
            {5, 5},
            "100B",
            {10, 5}
        },
        CuxTestFixture{
            "DownFromBottomNoChange",
            {10, 5},
            "B",
            {10, 5}
        },

        // BACKSPACE
        CuxTestFixture{
            "BackspaceMovesOnePlace",
            {5, 5},
            "\x08",
            {5, 4},
            false
        },
        CuxTestFixture{
            "BackspaceFromLeftNoChange",
            {5, 1},
            "\x08",
            {5, 1},
            false
        }
    ),
    [](const auto &info) {
      // Can use info.param here to generate the test suffix
      return std::string{info.param.name};
    }
);
