#pragma once

#include <functional>
#include <string>

struct TMTSCREEN;
struct TMTPOINT;
struct TMT;

namespace vt_test {

  using TmtCallbackType = std::function<void(int, TMT *, const void *, void *)>;

  using BellCallback = std::function<void()>;
  using UpdateCallback = std::function<void(const TMTSCREEN &screen)>;
  using AnswerCallback = std::function<void(const std::string &answer)>;
  using CursorMovedCallback = std::function<void(const TMTPOINT &position)>;
  using CursorVisibleCallback = std::function<void(bool visible)>;

  struct VtCallbacks {
    BellCallback bell;
    UpdateCallback update;
    AnswerCallback answer;
    CursorMovedCallback cursor_moved;
    CursorVisibleCallback cursor_visible;
  };

  TmtCallbackType create_callback_function(const VtCallbacks &callbacks);
}
