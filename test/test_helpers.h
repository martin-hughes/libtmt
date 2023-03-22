#pragma once

extern "C"
{
#include "tmt.h"
}

#include <string>

void normal_callback(tmt_msg_t m, TMT* vt, const void* a, void* p);

bool line_is_equal_to(const TMT &vt, int line, const std::string expected);
