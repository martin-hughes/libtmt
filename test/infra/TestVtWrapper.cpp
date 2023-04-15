#include "TestVtWrapper.h"
#include "test_helpers.h"

#include <stdexcept>

using namespace vt_test;

TestVtWrapper::TestVtWrapper(size_t cols, size_t rows) : cols{cols}, lines{rows} {
  this->vt = tmt_open(rows, cols, nullptr, nullptr, nullptr);
  tmt_clean(this->vt);
}

TestVtWrapper::~TestVtWrapper() {
  tmt_close(this->vt);
}

TMT *TestVtWrapper::get_vt() {
  return this->vt;
}

void TestVtWrapper::write_string(const std::string &string) {
  tmt_write(this->vt, string.c_str(), string.length());
}

void TestVtWrapper::set_clean() {
  tmt_clean(this->vt);
}

std::string TestVtWrapper::get_line_text(size_t line, bool strip_trailing_spaces) {
  std::string result;

  const auto screen = tmt_screen(this->vt);

  if (line > screen->nline) {
    throw std::invalid_argument("`line` cannot be greater than lines in vt");
  }

  const auto vt_line = screen->lines[line];
  for (size_t i = 0; i < screen->ncol; i++) {
    result += static_cast<std::string::value_type>(vt_line->chars[i].c);
  }

  if (strip_trailing_spaces) {
    result.erase(result.find_last_not_of(' ') + 1, std::string::npos);
  }

  return result;
}

bool TestVtWrapper::is_line_dirty(size_t line) {
  if (line > lines) {
    throw std::invalid_argument("line must be within the terminal");
  }

  return tmt_screen(vt)->lines[line]->dirty;
}