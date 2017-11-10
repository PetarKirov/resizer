#ifndef IMAGE_CORE_IMAGE_H
#define IMAGE_CORE_IMAGE_H

#include <cstddef>
#include "image/config/assert.h"
#include "image/core/type_traits.h"
#include "image/core/slice.h"

namespace image
{
namespace core
{
    template <class T>
    struct Image
    {
        T*        const data;
        size_t    const w;
        size_t    const h;
        ptrdiff_t const strideInBytes;

        typedef typename copy_const<T, uint8_t>::type byte;

        Image(Slice<T> pixels,
                size_t width, size_t height,
                bool flipScanLines = false)
            : data(!flipScanLines? pixels.begin() : pixels.end() - width),
              w(width), h(height),
              strideInBytes((flipScanLines? -1 : 1) * w * sizeof(T))
        {
            invariant();
        }

        Image(Slice<typename copy_const<T, uint8_t>::type> pixels,
                size_t width, size_t height,
                ptrdiff_t stride)
            : data((T*)(stride > 0 ? pixels.begin() : pixels.end() + stride)),
              w(width), h(height),
              strideInBytes(stride)
        {
            invariant();
        }

        template <typename U>
        Image(
            Image<U> o,
            typename enable_if<
                !is_same<T, typename remove_const<U>::type>::value,
                int
            >::type _ = 0
        )
            : data(o.data), w(o.w), h(o.h), strideInBytes(o.strideInBytes)
        {
            (void)_;
        }

    private:
        static size_t abs(ptrdiff_t x) { return x < 0? -x : x; }

        void invariant() const
        {
            ASSERT(data, "image data must be non-null");
            ASSERT(h > 0, "image height must be positive");
            ASSERT(w > 0, "image width must be positive");
            ASSERT(w <= abs(strideInBytes / sizeof(T)),
                    "image stride must be at least as large as each image row");
        }

        T* scanLineImpl(size_t y)
        {
            return (T*)((char*)data + y * strideInBytes);
        }

        const T* scanLineImpl(size_t y) const
        {
            return (const T*)((char*)data + y * strideInBytes);
        }

    public:

        T& operator()(size_t x, size_t y)
        {
            ASSERT(y < h, "row index `y` out of range");
            ASSERT(x < w, "column index `x` out of range");
            return *(scanLineImpl(y) + x);
        }

        const T& operator()(size_t x, size_t y) const
        {
            ASSERT(y < h, "row index `y` out of range");
            ASSERT(x < w, "column index `x` out of range");
            return *(scanLineImpl(y) + x);
        }

        Slice<T> scanLine(size_t y)
        {
            ASSERT(y < h, "row index `y` out of range");
            return Slice<T>(w, scanLineImpl(y));
        }

        Slice<const T> scanLine(size_t y) const
        {
            ASSERT(y < h, "row index `y` out of range");
            return Slice<const T>(w, scanLineImpl(y));
        }

        Slice<T>       operator[](size_t y)       { return scanLine(y); }
        Slice<const T> operator[](size_t y) const { return scanLine(y); }

        Slice<T>       front()
        { invariant(); return slice(w, scanLineImpl(0)); }

        Slice<const T> front() const
        { invariant(); return slice(w, scanLineImpl(0)); }

        Slice<T>       back()
        { invariant(); return slice(w, scanLineImpl(h - 1)); }

        Slice<const T> back() const
        { invariant(); return slice(w, scanLineImpl(h - 1)); }

        Slice<byte> rawMemory()
        {
            invariant();
            return Slice<byte>(
                abs(strideInBytes) * h,
                (byte*)(strideInBytes > 0? front() : back()).begin());
        }

        Slice<const byte> rawMemory() const
        {
            invariant();
            return Slice<const byte>(
                abs(strideInBytes) * h,
                (const byte*)(strideInBytes > 0? front() : back()).begin());
        }
    };

    template<class T>
    Image<T> makeImage(Slice<T> slice, size_t width, size_t height, bool flipRows)
    {
        return Image<T>(slice, width, height, flipRows);
    }

} /* namespace core */
} /* namespace image */

#endif /* IMAGE_CORE_IMAGE_H */
