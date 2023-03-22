extern "C"
{
#include "tmt.h"
};

#include "test_helpers.h"

#include <stdexcept>
#include <string>

bool line_is_equal_to(const TMT &vt, int line, const std::string expected) {
  const auto expected_length = expected.length();
  const auto line_length = tmt_screen(&vt)->ncol;
  if (expected_length > line_length) {
    throw std::invalid_argument("expected string must fit into VT size");
  }

  const auto vt_line = tmt_screen(&vt)->lines[line];

  int pos{0};
  for (const auto c: expected) {
    if (c != vt_line->chars[pos].c) {
      return false;
    }
    pos++;
  }

  while (pos < line_length) {
    if (vt_line->chars[pos].c != ' ') {
      return false;
    }
    pos++;
  }

  return true;
}
