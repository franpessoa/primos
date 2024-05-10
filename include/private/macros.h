#pragma once

#include <fmt/color.h>
#include <fmt/core.h>

#define FORMAT_BOLD(s) fmt::format(fmt::emphasis::bold, s)
#define PRINT_BOLD(s) fmt::println(FORMAT_BOLD(s))
#define FORMAT_BOLD_COLOR(s, c) fmt::format(fmt::emphasis::bold | fg(c), s)
#define PRINT_BOLD_COLOR(s, c) fmt::println(FORMAT_BOLD_COLOR(s, c))
#define FORMAT_VECTOR(s) fmt::join(s, ", ")