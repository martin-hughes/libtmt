#include "TestVtWrapper.h"
#include "tmt.h"

#include <stdexcept>

using namespace vt_test;

TestVtWrapper::TestVtWrapper(size_t cols, size_t rows) : TestVtWrapper(cols, rows, nullptr) {}

TestVtWrapper::TestVtWrapper(size_t cols, size_t rows, TmtCallbackType callback) :
    cols{cols}, lines{rows}, callback{std::move(callback)} {

  TMTCALLBACK cb{nullptr};
  void *p{nullptr};
  if (this->callback) {
    cb = static_callback;
    p = this;
  }

  this->vt = tmt_open(rows, cols, cb, p, nullptr);
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

TMTCHAR TestVtWrapper::get_character(size_t row, size_t col) {
  if ((row > lines) || (col > cols)) {
    throw std::invalid_argument("row and col must be within the terminal");
  }
  return tmt_screen(vt)->lines[row]->chars[col];
}

TMTPOINT TestVtWrapper::get_cursor_pos() {
  return *tmt_cursor(this->vt);
}

void TestVtWrapper::static_callback(tmt_msg_t msg, TMT *vt, const void *a, void *p) {
  auto cp = static_cast<TestVtWrapper *>(p);

  if (cp) {
    cp->callback(msg, vt, a, p);
  }
}
