#ifndef IMAGE_CORE_TYPE_TRAITS_H
#define IMAGE_CORE_TYPE_TRAITS_H

namespace image
{
namespace core
{
    template<bool B, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> { typedef T type; };

    template<class T, class U>
    struct is_same { enum { value = 0 }; };

    template<class T>
    struct is_same<T, T> { enum { value = 1 }; };

    template<class T> struct remove_const          { typedef T type; };
    template<class T> struct remove_const<const T> { typedef T type; };

    template <class From, class To>
    struct copy_const { typedef To type; };

    template <class From, class To>
    struct copy_const<const From, To> { typedef const To type; };
}
}

#endif /* IMAGE_CORE_TYPE_TRAITS_H */
