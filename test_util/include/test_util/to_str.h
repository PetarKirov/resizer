#ifndef TO_STR_H
#define TO_STR_H

#include <iostream>
#include <typeinfo>

#include "test_util/demangle.h"

#if __cplusplus >= 201103L

#include <type_traits>

#else

namespace std
{
    template<bool B, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> { typedef T type; };
}

#endif /* __cplusplus >= 201103L */


namespace test_util
{
    /// Adds ostream formatting operator << for types
    /// that don't define one.

    namespace has_insertion_operator_impl
    {
        typedef char no;
        typedef char yes[2];

        struct any_t { template<typename T> any_t(T const&); };

        no operator<<(std::ostream const&, any_t const&);

        yes& test(std::ostream&);
        no test(no);

        template<typename T>
        struct has_insertion_operator
        {
            static std::ostream &s;
            static T const &t;
            static bool const value = sizeof(test(s << t)) == sizeof(yes);
        };
    }

    template<typename T>
    struct has_insertion_operator
        : has_insertion_operator_impl::has_insertion_operator<T>
    { };

    template<typename T> inline
    typename std::enable_if<!has_insertion_operator<T>::value, std::ostream&>::type
    operator<<(std::ostream& os, T const &t)
    {
        return os << demangle(typeid(t).name()) <<
            " [at 0x" << static_cast<const void*>(&t) << ']';
    }
}

#endif
