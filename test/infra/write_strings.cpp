#include "test_helpers.h"

#include <numeric>

namespace vt_test {
  void write_string(TestVtWrapper &vt, const std::string &string) {
    vt.write_string(string);
  }

  void write_escape(TestVtWrapper &vt) {
    write_string(vt, "\u001b");
  }

  void write_csi(TestVtWrapper &vt) {
    write_string(vt, "\u001b[");
  }

  void write_cursor_move(TestVtWrapper &vt, CursorMoveDir dir, size_t places) {
    write_csi(vt);

    std::string command = std::to_string(places) + static_cast<std::string::value_type>(dir);

    write_string(vt, command);
  }

  void write_sgr(TestVtWrapper &vt, const std::vector<unsigned int> &values) {
    write_csi(vt);

    auto command = std::accumulate(
        values.begin() + 1,
        values.end(),
        std::to_string(values[0]),
        [](const std::string &x, unsigned int y) {
          return x + ";" + std::to_string(y);
        }) + "m";

    write_string(vt, command);
  }
}
