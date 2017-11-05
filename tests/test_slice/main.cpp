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

    Slice<int> sl1(arr);
    ASSERT_EQ(sl1.length(), 5);
    ASSERT_EQ(&sl1[0], &arr[0]);
    ASSERT_EQ(&sl1[4], &arr[4]);

    Slice<int> sl2 = sl1.slice(1, 3);
    ASSERT_EQ(sl2.length(), 2);
    ASSERT_EQ(sl2[0], 2);
    ASSERT_EQ(sl2[1], 3);
    ASSERT_EQ(&sl2[0], &sl1[1]);
    ASSERT_EQ(&sl2[1], &sl1[2]);

    Slice<int> sl3 = sl1.slice(1, 3);
    ASSERT_EQ(sl2, sl3);
    ASSERT_NEQ(sl2, sl1);
    ASSERT_NEQ(sl3, sl1);

    Sum s = std::for_each(sl1.begin(), sl1.end(), Sum());
    ASSERT_EQ(s.sum, 15);
}
