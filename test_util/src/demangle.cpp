#include "test_util/demangle.h"

#ifdef __GNUG__

#include <cstdlib>
#include <cxxabi.h>

// See https://gcc.gnu.org/onlinedocs/libstdc++/manual/ext_demangling.html
std::string test_util::demangle(const char* name)
{
    std::string res;
    int status = -1;
    char *str = abi::__cxa_demangle(name, NULL, NULL, &status);
    if (status == 0) res = str;
    if (str) free(str);
    return res;
}

#else /* not __GNUG__ */

// Fallback for non-glibc platforms
std::string test_util::demangle(const char* name)
{
    return name;
}

#endif /* __GNUG__ */
