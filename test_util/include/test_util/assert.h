#ifndef TESTING_H
#define TESTING_H

#include <iostream>
#include <cstdlib>
#include "test_util/to_str.h"

#if defined(__GNUC__)
#   define FUNCTION __PRETTY_FUNCTION__
#elif defined(WIN32)
#   define FUNCTION __FUNCTION__
#else
#   define FUNCTION __func__
#endif

#define STRINGIFY(x) #x

#define ASSERT_EQ(actual, expected) \
do \
{ \
    if (!((expected) == (actual))) \
    { \
        using test_util::operator<<; \
        std::cout << __FILE__ << ":" << __LINE__ << ": Error:" \
            << std::boolalpha \
            << " `" \
            << (actual) << "` (`" STRINGIFY(actual) "`)" \
            << " different from expected `" \
            << (expected) << "` (`" STRINGIFY(expected) "`)\n" \
            << "In function: " << FUNCTION << "\n"; \
      exit(42); \
    } \
} while (0)

#define ASSERT_NEQ(a, b) \
do \
{ \
    if ((b) == (a)) \
    { \
        using test_util::operator<<; \
        std::cout << __FILE__ << ":" << __LINE__ << ": Error:" \
            << std::boolalpha \
            << " expected `" << (a) << "` (`" STRINGIFY(a) "`)" \
            << " to differ from `" << (b) << "` (`" STRINGIFY(b) "`)" \
            << "In function: " << FUNCTION << "\n"; \
      exit(42); \
    } \
} while (0)

#endif
