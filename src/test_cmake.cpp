#include <iostream>
#include "config/config.h"

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
    cout << "Library name: " << LIB_NAME << endl;
    cout << "Library version: " << LIB_VERSION << endl;
    cout << "Library description: " << LIB_DESCRIPTION << endl;
}
