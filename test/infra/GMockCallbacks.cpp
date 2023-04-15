#include "GMockCallbacks.h"

using namespace vt_test;

TmtCallbackType vt_test::makeCallbackForGMocks(GMockCallbacks &callbacks) {
  VtCallbacks cb{
      .bell = callbacks.bellCallback.AsStdFunction(),
      .update = callbacks.updateCallback.AsStdFunction(),
      .answer = callbacks.answerCallback.AsStdFunction(),
      .cursor_moved = callbacks.cursorMovedCallback.AsStdFunction(),
      .cursor_visible = callbacks.cursorVisibleCallback.AsStdFunction()
  };

  return createCallbackFunction(cb);
}
