#include <algorithm>

#include "image/core/slice.h"
#include "image/core/algorithm.h"
#include "test_util/assert.h"

using namespace image::core;

void testBasics();
void testRangePrimitives();
void testConst();
void testObjSlice();

int main()
{
    testBasics();
    testRangePrimitives();
    testConst();
    testObjSlice();
}

struct Sum
{
    Sum(): sum(0) { }
    void operator()(int n) { sum += n; }
    int sum;
};

void testBasics()
{
    Slice<short> x = Slice<short>::init();
    ASSERT_EQ(x.length(), 0);
    ASSERT_EQ(!!x.begin(), false);
    ASSERT_EQ(x.empty(), true);

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

    ASSERT_EQ(sl1.skipTake(0, 5), sl1);
    ASSERT_EQ(sl1.skipTake(1, 4), sl2);
    ASSERT_EQ(sl1.skipTake(0, 4), sl3);

    int elementsToSkip = 2;
    int elementsNeeded = 1;
    Slice<const int> res1 = sl1.skipTake(elementsToSkip, elementsNeeded);
    Slice<const int> res2 = sl1.slice(elementsToSkip, elementsToSkip + elementsNeeded);
    ASSERT_EQ(res1, res2);
}

struct Pow2
{
    void operator()(int& x) { x *= x; }
};

void testConst()
{
    int arr[] = {1, 2, 3, 4, 5};
    Slice<int> sl = slice(arr);

    // Test implicit construction
    Slice<const int> csl1 = sl;

    // Test slicing
    const Slice<const int> csl2 = csl1.slice(1, 3);

    // test operator==
    ASSERT_EQ(sl, csl1);
    ASSERT_NEQ(sl, csl2);

    // test getters: length(), bytes(), begin(), end(), operator[], empty()
    ASSERT_EQ(csl2.length(), 2);
    ASSERT_EQ(csl2.bytes(), 8);

    const int* beg = csl2.begin();
    const int* end = csl2.end();
    ASSERT_EQ(beg, &arr[1]);
    ASSERT_EQ(end, &arr[3]);

    const int& x = csl2[0];
    ASSERT_EQ(x, 2);

    const Slice<const int> csl3 = csl1.slice(2, 2);
    ASSERT_EQ(csl3.empty(), true);

    // test drop*()
    const Slice<const int> csl4 = csl1.drop().drop().dropBack().dropBack().dropBack();
    ASSERT_EQ(csl3, csl4);

    ASSERT_NEQ(csl3, csl1.drop().drop().drop().dropBack().dropBack());

    Slice<int> sl5 = sl.slice(2, 4);
    ASSERT_EQ(sl5, sl.drop().drop().dropBack());
    ASSERT_EQ(sl5.length(), 2);

    // test copying:
    int dst[5];
    Slice<int> res = slice(dst);

    copy(csl1, res);
    ASSERT_EQ(dst[0], 1);
    ASSERT_EQ(dst[1], 2);
    ASSERT_EQ(dst[2], 3);
    ASSERT_EQ(dst[3], 4);
    ASSERT_EQ(dst[4], 5);

    std::for_each(sl.begin(), sl.end(), Pow2());
    copy(slice(arr), slice(dst));
    ASSERT_EQ(dst[0], 1);
    ASSERT_EQ(dst[1], 4);
    ASSERT_EQ(dst[2], 9);
    ASSERT_EQ(dst[3], 16);
    ASSERT_EQ(dst[4], 25);

    // test bitcast
    Slice<const uint8_t> csl6 = csl1.bitcast<uint8_t>();
    ASSERT_EQ(csl6[0] + csl6[1] + csl6[2] + csl6[3], 1);
}

struct MyFancyObj
{
    uint8_t field1;
    uint8_t field2;
    uint8_t field3;
    uint8_t field4;

    MyFancyObj(uint8_t f1, uint8_t f2, uint8_t f3, uint8_t f4)
        : field1(f1), field2(f2), field3(f3), field4(f4)
    { }
};

void testObjSlice()
{
    MyFancyObj obj(7, 21, 42, 84);

    STATIC_ASSERT(sizeof(MyFancyObj) == 4);

    Slice<uint8_t> sl1 = sliceIntoBytes(obj);
    ASSERT_EQ(sl1.length(), 4);
    ASSERT_EQ(sl1.begin(), (uint8_t*)&obj);
    ASSERT_EQ(sl1[0], 7);
    ASSERT_EQ(sl1[1], 21);
    ASSERT_EQ(sl1[2], 42);
    ASSERT_EQ(sl1[3], 84);

    sl1[0] = 255;
    sl1[1] = 254;
    sl1[2] = 253;
    sl1[3] = 252;

    ASSERT_EQ(obj.field1, 255);
    ASSERT_EQ(obj.field2, 254);
    ASSERT_EQ(obj.field3, 253);
    ASSERT_EQ(obj.field4, 252);
}
