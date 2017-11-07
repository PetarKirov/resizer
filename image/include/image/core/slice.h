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
            ASSERT(!empty(), "Indexing an empty slice");
            ASSERT(idx < _length, "Index out of range");
            return _ptr[idx];
        }

        const T& operator[](size_t idx) const
        {
            ASSERT(!empty(), "Indexing an empty slice");
            ASSERT(idx < _length, "Index out of range");
            return _ptr[idx];
        }

        Slice<T> slice(size_t start, size_t end)
        {
            ASSERT(start <= end, "`start` must be <= `end`");
            ASSERT(end <= _length, "`end` must be <= `length()`");
            return Slice<T>(end - start, _ptr + start);
        }

        Slice<const T> slice(size_t start, size_t end) const
        {
            ASSERT(start <= end, "`start` must be <= `end`");
            ASSERT(end <= _length, "`end` must be <= `length()`");
            return Slice<T>(end - start, _ptr + start);
        }

        bool empty() const { return !_length || !_ptr; }

        T& front()
        {
            ASSERT(!empty(), "`front()` called on empty slice");
            return _ptr[0];
        }

        const T& front() const
        {
            ASSERT(!empty(), "`front()` called on empty slice");
            return _ptr[0];
        }

        T& back()
        {
            ASSERT(!empty(), "`back()` called on empty slice");
            return _ptr[_length - 1];
        }

        const T& back() const
        {
            ASSERT(!empty(), "`back()` called on empty slice");
            return _ptr[_length - 1];
        }

        Slice<T>       drop()       { return this->slice(1, _length); }
        Slice<const T> drop() const { return this->slice(1, _length); }

        Slice<T>       dropBack()       { return this->slice(0, _length - 1); }
        Slice<const T> dropBack() const { return this->slice(0, _length - 1); }

    }; /* struct Slice<T> */

    template <class T, size_t N>
    Slice<T> slice(T (&arr)[N])
    {
        return Slice<T>(N, &arr[0]);
    }

    template <class T>
    Slice<T> slice(size_t length, T* ptr)
    {
        return Slice<T>(length, ptr);
    }
} /* namespace core */
} /* namespace image */

#endif /* IMAGE_CORE_SLICE_H */
