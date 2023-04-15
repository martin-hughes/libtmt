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
    GMockBellCallback bellCallback;
    GMockUpdateCallback updateCallback;
    GMockAnswerCallback answerCallback;
    GMockCursorMovedCallback cursorMovedCallback;
    GMockCursorVisibleCallback cursorVisibleCallback;
  };

  TmtCallbackType makeCallbackForGMocks(GMockCallbacks &callbacks);
}
