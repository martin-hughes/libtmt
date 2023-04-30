#pragma once

#include "VtStdCallbacks.h"

#include "gmock/gmock.h"

namespace vt_test {
  using GMockBellCallback = testing::MockFunction<BellCallback>;
  using GMockUpdateCallback = testing::MockFunction<UpdateCallback>;
  using GMockAnswerCallback = testing::MockFunction<AnswerCallback>;
  using GMockCursorMovedCallback = testing::MockFunction<CursorMovedCallback>;
  using GMockCursorVisibleCallback = testing::MockFunction<CursorVisibleCallback>;

  struct GMockCallbacks {
  public:
    GMockBellCallback bell_callback;
    GMockUpdateCallback update_callback;
    GMockAnswerCallback answer_callback;
    GMockCursorMovedCallback cursor_moved_callback;
    GMockCursorVisibleCallback cursor_visible_callback;
  };

  TmtCallbackType make_callback_for_gmocks(GMockCallbacks &callbacks);
}
