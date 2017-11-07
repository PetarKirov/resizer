#include <algorithm>

#include "image/core/slice.h"
#include "image/core/algorithm.h"
#include "test_util/assert.h"

using namespace image::core;

void testBasics();
void testRangePrimitives();

int main()
{
    testBasics();
    testRangePrimitives();
}

struct Sum
{
    Sum(): sum(0) { }
    void operator()(int n) { sum += n; }
    int sum;
};

void testBasics()
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

    int dstArr[5] = {};
    Slice<int> dst = slice(dstArr);
    copy<int>(sl1, dst);
    ASSERT_EQ(dstArr[0], 1);
    ASSERT_EQ(dstArr[1], 2);
    ASSERT_EQ(dstArr[2], 3);
    ASSERT_EQ(dstArr[3], 4);
    ASSERT_EQ(dstArr[4], 5);
}

void testRangePrimitives()
{
    const int arr[] = {1, 2, 3, 4, 5};
    Slice<const int> sl1 = slice(arr);

    ASSERT_EQ(sl1.empty(), false);
    ASSERT_EQ(sl1.front(), 1);
    ASSERT_EQ(sl1.back(), 5);

    Slice<const int> sl2 = sl1.drop();
    ASSERT_EQ(sl2.front(), 2);
    ASSERT_EQ(sl2.back(), 5);
    ASSERT_EQ(sl2.length(), 4);

    Slice<const int> sl3 = sl1.dropBack();
    ASSERT_EQ(sl3.front(), 1);
    ASSERT_EQ(sl3.back(), 4);
    ASSERT_EQ(sl3.length(), 4);
}
