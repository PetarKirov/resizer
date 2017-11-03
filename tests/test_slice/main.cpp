#include <algorithm>

#include "image/core/slice.h"
#include "test_util/assert.h"

using namespace image::core;

struct Sum
{
    Sum(): sum(0) { }
    void operator()(int n) { sum += n; }
    int sum;
};

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    Slice<int> sl(arr);
    ASSERT_EQ(sl.length(), 5);

    Sum s = std::for_each(sl.begin(), sl.end(), Sum());
    ASSERT_EQ(s.sum, 15);
}
