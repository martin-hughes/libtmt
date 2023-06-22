#pragma once

#include "TestVtWrapper.h"

#include <array>

namespace vt_test::basic_scene {
  constexpr size_t test_rows = 5;
  struct LineState {
    bool is_dirty;
    std::string contents;
  };

  using SceneData = std::array<LineState, test_rows>;

  void set_scene(TestVtWrapper &vt);
  void check_scene(const TestVtWrapper &vt, const SceneData &contents);
}
