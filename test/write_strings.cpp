extern "C"
{
#include "tmt.h"
};

#include "test_helpers.h"

void write_string(TMT &vt, const std::string &string) {
  tmt_write(&vt, string.c_str(), string.length());
}

void write_escape(TMT &vt) {
  tmt_write(&vt, "\u001b", 1);
}

void write_csi(TMT &vt) {
  tmt_write(&vt, "\u001b[", 2);
}

void write_cursor_move(TMT &vt, CursorMoveDir dir, size_t places) {
  write_csi(vt);

  std::string command = std::to_string(places) + std::to_string(static_cast<unsigned char>(dir));

  write_string(vt, command);
}
