#ifndef IMAGE_CONFIG_ASSERT_H
#define IMAGE_CONFIG_ASSERT_H

#include "image/config/config.h"

#if ASSERT_EXIT

#include <cstdio>
#include <cstdlib>

#define ASSERT(expr, error_msg) \
do \
{ \
    if (!(expr)) \
    { \
        std::fprintf(stderr, "%s:%d Internal error: '%s'.", \
                __FILE__, __LINE__, (error_msg)); \
        std::exit(42); \
    } \
} while (0)

#elif ASSERT_THROW

#include <stdexcept>

#define ASSERT(expr, error_msg) \
do \
{ \
    if (!(expr)) \
    { \
        throw std::logic_error( (error_msg) ); \
    } \
} while (0)

#else /* not in debug mode */

#define ASSERT(expr, error_msg) do { } while(0)

#endif /* definition of ASSERT */

#endif /* IMAGE_CONFIG_ASSERT_H */
