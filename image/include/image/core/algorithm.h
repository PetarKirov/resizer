#ifndef IMAGE_CORE_ALGORITHM_H
#define IMAGE_CORE_ALGORITHM_H

#include <cstring>
#include "image/core/slice.h"

namespace image
{
namespace core
{
    template <class T>
    void copy(const Slice<T>& src, Slice<T>& dst)
    {
        ASSERT(src.length() == dst.length(),
                "Copying one slice to another is allowed only when the lengths "
                "of both slices are equal");
        std::memcpy(dst.begin(), src.begin(), src.length() * sizeof(T));
    }
}
}

#endif /* IMAGE_CORE_ALGORITHM_H */
