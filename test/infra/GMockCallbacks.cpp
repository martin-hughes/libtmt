#include "GMockCallbacks.h"

using namespace vt_test;

TmtCallbackType vt_test::make_callback_for_gmocks(GMockCallbacks &callbacks) {
  VtCallbacks cb{
      .bell = callbacks.bell_callback.AsStdFunction(),
      .update = callbacks.update_callback.AsStdFunction(),
      .answer = callbacks.answer_callback.AsStdFunction(),
      .cursor_moved = callbacks.cursor_moved_callback.AsStdFunction(),
      .cursor_visible = callbacks.cursor_visible_callback.AsStdFunction()
  };

  return create_callback_function(cb);
}
