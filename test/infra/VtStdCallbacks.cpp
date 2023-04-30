#include "VtStdCallbacks.h"

#include "gmock/gmock.h"

#include "tmt.h"

// This avoids needing to include tmt.h in the header.
static_assert(std::is_convertible_v<tmt_msg_t, int>);

namespace {
  void default_callback(const vt_test::VtCallbacks &callbacks, int msg, TMT *vt, const void *a, const void *) {
    switch (msg) {
      case TMT_MSG_BELL:
        callbacks.bell ? callbacks.bell() : (void) 0;
        break;

      case TMT_MSG_UPDATE:
        callbacks.update ? callbacks.update(*static_cast<const TMTSCREEN *>(a)) : (void) 0;
        break;

      case TMT_MSG_ANSWER:
        callbacks.answer ? callbacks.answer(std::string{static_cast<const char *>(a)}) : (void) 0;
        break;

      case TMT_MSG_MOVED:
        callbacks.cursor_moved ? callbacks.cursor_moved(*static_cast<const TMTPOINT *>(a)) : (void) 0;
        break;

      case TMT_MSG_CURSOR: {
        auto c = static_cast <const char *>(a);
        bool visible;

        switch (c[0]) {
          case 't':
            visible = true;
            break;

          case 'f':
            visible = false;
            break;

          default:
            throw std::invalid_argument("cursor visibilty string is invalid");
        }

        callbacks.cursor_visible ? callbacks.cursor_visible(visible) : (void) 0;
        break;
      }

      default:
        throw std::invalid_argument("msg is not one of the expected messages");
    }
  }
}

namespace vt_test {
  TmtCallbackType create_callback_function(const VtCallbacks &callbacks) {
    return [callbacks](int msg, TMT *vt, const void *a, const void *p) { default_callback(callbacks, msg, vt, a, p); };
  }
}
