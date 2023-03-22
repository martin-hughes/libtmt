#include "test_helpers.h"

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

    std::string command = std::to_string(places) + std::to_string(static_cast<unsigned char>(dir));

    write_string(vt, command);
  }
}
