#pragma once

#include <cstdlib>

#include <fmt/format.h>
#include <fmt/color.h>

#if defined(_WIN32) || defined(_WIN64)
    #define __PRETTY_FUNCTION__  __FUNCTION__
#endif

#if !defined(NDEBUG) || defined(_DEBUG)
    #define ENABLE_ASSERTIONS
#else
    #undef ENABLE_ASSERTIONS
#endif

#if defined(ENABLE_ASSERTIONS)

    /**
     * Print __MESSAGE and abort program execution if __EXPR evaluates to false
     * */
    #define ASSERT(__EXPR, __MESSAGE)                               \
    do {                                                            \
        if (!(__EXPR)) {                                            \
            fmt::print(fmt::fg(fmt::color::red), "MESSAGE: {}\n"    \
                                        "FUNCTION: {}\n"            \
                                        "SRC: {}\n"                 \
                                        "LINE: {}\n",               \
                    __MESSAGE, __PRETTY_FUNCTION__,                 \
                                      __FILE__, __LINE__);          \
            std::abort();                                           \
        }                                                           \
    } while (false)

#else
    #define ASSERT(__EXPR, __MESSAGE)
#endif