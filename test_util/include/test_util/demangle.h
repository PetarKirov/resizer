#ifndef DEMANGLE_H
#define DEMANGLE_H

#include <string>

namespace test_util
{
    /// Given the mangled name of a symbol, returns its demangled name.
    std::string demangle(const char* name);
}

#endif
