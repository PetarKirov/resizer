#include <iostream>
#include "image/config/config.h"
#include "test_util/assert.h"

void printCppVer()
{
    using namespace std;
#if __cplusplus >= 201103L
    cout << "In C++11 mode!" << endl;
#else
    cout << "In C++98 mode!" << endl;
#endif
}

int main()
{
    using namespace std;
    printCppVer();
    string expected_version = "0.0.1";
    string actual_version = LIB_VERSION;

    ASSERT_EQ(actual_version, expected_version);
    ASSERT_NEQ(actual_version, string("0.0.0"));
}
