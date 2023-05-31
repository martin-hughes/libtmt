#include "TestVtWrapper.h"
#include "tmt.h"

#include <stdexcept>

using namespace vt_test;

TestVtWrapper::TestVtWrapper(size_t cols, size_t rows) : TestVtWrapper(cols, rows, nullptr) {}

TestVtWrapper::TestVtWrapper(size_t cols, size_t rows, TmtCallbackType callback, const bool receive_startup_msgs) :
    cols{cols}, lines{rows}, callback{nullptr} {

  if (receive_startup_msgs) {
    this->callback = std::move(callback);
  }

  this->vt = tmt_open(rows, cols, static_callback, this, nullptr);

  if (!receive_startup_msgs) {
    this->callback = std::move(callback);
  }

  tmt_clean(this->vt);
}

TestVtWrapper::~TestVtWrapper() {
  tmt_close(this->vt);
}

TMT *TestVtWrapper::get_vt() const {
  return this->vt;
}

void TestVtWrapper::write_string(const std::string &string) {
  tmt_write(this->vt, string.c_str(), string.length());
}

void TestVtWrapper::set_clean() {
  tmt_clean(this->vt);
}

std::string TestVtWrapper::get_line_text(size_t line, bool strip_trailing_spaces) const {
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

bool TestVtWrapper::is_line_dirty(size_t line) const {
  if (line > lines) {
    throw std::invalid_argument("line must be within the terminal");
  }

  return tmt_screen(vt)->lines[line]->dirty;
}

TMTCHAR TestVtWrapper::get_character(size_t row, size_t col) const {
  if ((row > lines) || (col > cols)) {
    throw std::invalid_argument("row and col must be within the terminal");
  }
  return tmt_screen(vt)->lines[row]->chars[col];
}

TMTPOINT TestVtWrapper::get_cursor_pos() const {
  return *tmt_cursor(this->vt);
}

void TestVtWrapper::static_callback(tmt_msg_t msg, TMT *vt, const void *a, void *p) {
  auto cp = static_cast<TestVtWrapper *>(p);

  if (cp && cp->callback) {
    cp->callback(msg, vt, a, p);
  }
}
