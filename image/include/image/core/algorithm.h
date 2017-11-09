#ifndef IMAGE_CORE_ALGORITHM_H
#define IMAGE_CORE_ALGORITHM_H

#include <cstring>
#include "image/core/slice.h"
#include "image/core/image.h"

namespace image
{
namespace core
{
    template <class T>
    void copy(Slice<const T> src, Slice<T> dst)
    {
        ASSERT(src.length() == dst.length(),
                "Copying one slice to another is allowed only when the lengths "
                "of both slices are equal");
        std::memcpy(dst.begin(), src.begin(), dst.bytes());
    }

    template <class T>
    void copy(Slice<T> src, Slice<T> dst)
    {
        copy(Slice<const T>(src), dst);
    }

    template <class T>
    void copy(Image<const T> src, Image<T> dst)
    {
        ASSERT(src.w == dst.w && src.h == dst.h,
                "Copying one image to another is allowed only when the "
                "widths and heights of both images are equal");

        ASSERT(src.strideInBytes && dst.strideInBytes,
                "Images should have non-zero strides");

        if (src.strideInBytes == dst.strideInBytes)
            copy(src.rawMemory(), dst.rawMemory());

        else
            for (size_t i = 0; i < src.h; i++)
                copy(src.scanLine(i), dst.scanLine(i));
    }

    template <class T>
    void copy(Image<T> src, Image<T> dst)
    {
        copy<T>(Image<const T>(src), dst);
    }
}
}

#endif /* IMAGE_CORE_ALGORITHM_H */
