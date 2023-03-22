#pragma once

extern "C"
{
#include "tmt.h"
}

#include <string>

enum class CursorMoveDir : unsigned char {
    Up = 'A',
    Down = 'B',
    Right = 'C',
    Left = 'D',
};

void normal_callback(tmt_msg_t m, TMT *vt, const void *a, void *p);

bool line_is_equal_to(const TMT &vt, int line, const std::string expected);

void write_string(TMT &vt, const std::string &string);
void write_escape(TMT &vt);
void write_csi(TMT &vt);
void write_cursor_move(TMT &vt, CursorMoveDir dir, size_t places);
