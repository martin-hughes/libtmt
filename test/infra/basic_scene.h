#pragma once

#include "TestVtWrapper.h"

#include <array>

namespace vt_test::basic_scene {
  constexpr size_t test_rows = 5;
  struct LineState {
    bool is_dirty;
    std::string contents;
  };

  template <size_t n>
  using SceneData = std::array<LineState, n>;

  using DefaultSizeSceneData = std::array<LineState, test_rows>;

  void set_scene(TestVtWrapper &vt);

  void check_scene_row(const TestVtWrapper &vt, const LineState &row, size_t row_num);

  template<size_t n>
  void check_scene(const TestVtWrapper &vt, const SceneData<n> &contents) {
    // Can't use range-based for loop as we need the index for the member calls on vt.
    for (size_t i = 0; i < n; i++) {
      check_scene_row(vt, contents[i], i);
    }
  }

  extern const DefaultSizeSceneData default_scene_data;
}
