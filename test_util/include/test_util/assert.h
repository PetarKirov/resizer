#ifndef TESTING_H
#define TESTING_H

#include <iostream>
#include <cstdlib>
#include "test_util/to_str.h"

#define STRINGIFY(x) #x

#define ASSERT_EQ(actual, expected) \
do \
{ \
    if (!((expected) == (actual))) \
    { \
        using test_util::operator<<; \
        std::cout << __FILE__ << ":" << __LINE__ << ": Error:" \
            << " expected: `" << (expected) << "` (" STRINGIFY(expected) ")" \
            << " to equal actual: `" \
            << (actual) << "` (" STRINGIFY(actual) ")\n"; \
      exit(42); \
    } \
} while (0)

#define ASSERT_NEQ(actual, expected) \
do \
{ \
    if ((expected) == (actual)) \
    { \
        using test_util::operator<<; \
        std::cout << __FILE__ << ":" << __LINE__ << ": Error:" \
            << " expected: `" << (expected) << "` (" STRINGIFY(expected) ")" \
            << " to not equal actual: `" \
            << (actual) << "` (" STRINGIFY(actual) ")\n"; \
      exit(42); \
    } \
} while (0)

#endif
