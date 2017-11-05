#ifndef IMAGE_CORE_SLICE_H
#define IMAGE_CORE_SLICE_H

#include <stdint.h>
#include "image/config/assert.h"

namespace image
{
namespace core
{
    template <class T> struct Slice
    {
    private:
        size_t _length;
        T* _ptr;

#if __cplusplus >= 201103L
    public:
        Slice() = delete;
        Slice(const Slice& other) = default;
        Slice& operator=(const Slice& other) = default;
#else
    private:
        Slice() { }
#endif

    public:
        Slice(size_t size, T *ptr) : _length(size), _ptr(ptr) { }

    public:
        template <size_t N>
        Slice(T (&arr)[N])
            : _length(N), _ptr(arr)
        { }

        friend bool operator==(const Slice<T>& a, const Slice<T>& b)
        {
            return a._length == b._length && a._ptr == b._ptr;
        }

        friend bool operator!=(const Slice<T>& a, const Slice<T>& b)
        {
            return !(a == b);
        }

        size_t length() const { return _length; }

        T* begin() { return _ptr; }
        const T* begin() const { return _ptr; }

        T* end() { return _ptr + _length; }
        const T* end() const { return _ptr + _length; }

        T& operator[](size_t idx)
        {
            ASSERT(idx < _length, "Index out of range");
            return _ptr[idx];
        }

        const T& operator[](size_t idx) const
        {
            ASSERT(idx < _length, "Index out of range");
            return _ptr[idx];
        }

        Slice<T> slice(size_t start, size_t end)
        {
            ASSERT(start <= _length, "`start` must be less or equal to `end`");
            ASSERT(end < _length, "`end` must be less than `length()`");
            return Slice<T>(end - start, _ptr + start);
        }

        Slice<const T> slice(size_t start, size_t end) const
        {
            ASSERT(start <= _length, "`start` must be less or equal to `end`");
            ASSERT(end < _length, "`end` must be less than `length()`");
            return Slice<T>(end - start, _ptr + start);
        }
    }; /* struct Slice<T> */

    template <class T, size_t N>
    Slice<const T> slice(const T (&arr)[N])
    {
        return Slice<const T>(N, &arr[0]);
    }

    template <class T, size_t N>
    Slice<T> slice(T (&arr)[N])
    {
        return Slice<T>(N, &arr[0]);
    }
} /* namespace core */
} /* namespace image */

#endif /* IMAGE_CORE_SLICE_H */
