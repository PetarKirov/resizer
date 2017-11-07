#include "image/core/image.h"
#include "test_util/assert.h"

using namespace image::core;

void testBasics1();
void testBasics2();
void testStride();

int main()
{
    testBasics1();
    testBasics2();
    testStride();
}

void testBasics1()
{
    int arr1[] =
    {
        1, 2, 3,
        4, 5, 6
    };

    Slice<int> sl1 = slice(arr1);
    Image<int> img1(slice(arr1), 3, 2);
    ASSERT_EQ(img1.w, 3);
    ASSERT_EQ(img1.h, 2);
    ASSERT_EQ(img1.strideInBytes, 3 * sizeof(arr1[0]));

    ASSERT_EQ(img1.scanLine(0)[0], 1);
    ASSERT_EQ(img1.scanLine(0).length(), 3);
    ASSERT_EQ(img1.scanLine(0).begin(), &arr1[0]);
    ASSERT_EQ(img1.scanLine(0).end(), &arr1[3]);

    ASSERT_EQ(img1.scanLine(1)[0], 4);
    ASSERT_EQ(img1.scanLine(1).length(), 3);
    ASSERT_EQ(img1.scanLine(1).begin(), &arr1[3]);
    ASSERT_EQ(img1.scanLine(1).end(), &arr1[6]);

    ASSERT_EQ(img1.front().back(), 3);
    ASSERT_EQ(img1.back().back(), 6);

    ASSERT_EQ(img1(0, 0), 1);
    ASSERT_EQ(img1(1, 0), 2);
    ASSERT_EQ(img1(2, 0), 3);
    ASSERT_EQ(img1(0, 1), 4);
    ASSERT_EQ(img1(1, 1), 5);
    ASSERT_EQ(img1(2, 1), 6);

    ASSERT_EQ(img1[0][0], 1);
    ASSERT_EQ(img1[0][1], 2);
    ASSERT_EQ(img1[0][2], 3);
    ASSERT_EQ(img1[1][0], 4);
    ASSERT_EQ(img1[1][1], 5);
    ASSERT_EQ(img1[1][2], 6);

    Slice<uint8_t> mem1 = img1.rawMemory();
    ASSERT_EQ((void*)mem1.begin(), (void*)&arr1[0]);
    ASSERT_EQ((void*)mem1.end(), (void*)&arr1[6]);

    Slice<uint8_t> mem2 = sl1.bitcast<uint8_t>();
    ASSERT_EQ(mem1.length(), mem2.length());
    ASSERT_EQ(mem2, mem2);
}

void testBasics2()
{
    int arr1[] =
    {
        4, 5, 6,
        1, 2, 3
    };

    Slice<int> sl1 = slice(arr1);
    Image<int> img1(sl1, 3, 2, true);
    ASSERT_EQ(img1.w, 3);
    ASSERT_EQ(img1.h, 2);
    ASSERT_EQ(img1.strideInBytes, -3 * ptrdiff_t(sizeof(arr1[0])));

    ASSERT_EQ(img1.scanLine(0)[0], 1);
    ASSERT_EQ(img1.scanLine(0).length(), 3);
    ASSERT_EQ(img1.scanLine(0).begin(), &arr1[3]);
    ASSERT_EQ(img1.scanLine(0).end(), &arr1[6]);

    ASSERT_EQ(img1.scanLine(1)[0], 4);
    ASSERT_EQ(img1.scanLine(1).length(), 3);
    ASSERT_EQ(img1.scanLine(1).begin(), &arr1[0]);
    ASSERT_EQ(img1.scanLine(1).end(), &arr1[3]);

    ASSERT_EQ(img1.front().back(), 3);
    ASSERT_EQ(img1.back().back(), 6);

    ASSERT_EQ(img1(0, 0), 1);
    ASSERT_EQ(img1(1, 0), 2);
    ASSERT_EQ(img1(2, 0), 3);
    ASSERT_EQ(img1(0, 1), 4);
    ASSERT_EQ(img1(1, 1), 5);
    ASSERT_EQ(img1(2, 1), 6);

    ASSERT_EQ(img1[0][0], 1);
    ASSERT_EQ(img1[0][1], 2);
    ASSERT_EQ(img1[0][2], 3);
    ASSERT_EQ(img1[1][0], 4);
    ASSERT_EQ(img1[1][1], 5);
    ASSERT_EQ(img1[1][2], 6);

    Slice<uint8_t> mem1 = img1.rawMemory();
    ASSERT_EQ((void*)mem1.begin(), (void*)&arr1[0]);
    ASSERT_EQ((void*)mem1.end(), (void*)&arr1[6]);

    Slice<uint8_t> mem2 = sl1.bitcast<uint8_t>();
    ASSERT_EQ(mem1.length(), mem2.length());
    ASSERT_EQ(mem2, mem2);
}

struct Rgb { uint8_t r, g, b; };

void testStride()
{
    uint8_t arr[] =
    {
        51, 52, 53, 61, 62, 63, 254, 255,
        31, 32, 33, 41, 42, 43, 252, 253,
        11, 12, 13, 21, 22, 23, 250, 251
    };

    Slice<uint8_t> sl = slice(arr);

    Image<Rgb> img(sl, 2, 3, -8);

    ASSERT_EQ(img(0, 0).r, 11);
    ASSERT_EQ(img(0, 0).g, 12);
    ASSERT_EQ(img(0, 0).b, 13);

    ASSERT_EQ(img(1, 0).r, 21);
    ASSERT_EQ(img(1, 0).g, 22);
    ASSERT_EQ(img(1, 0).b, 23);

    ASSERT_EQ(img(0, 1).r, 31);
    ASSERT_EQ(img(0, 1).g, 32);
    ASSERT_EQ(img(0, 1).b, 33);

    ASSERT_EQ(img(1, 1).r, 41);
    ASSERT_EQ(img(1, 1).g, 42);
    ASSERT_EQ(img(1, 1).b, 43);

    ASSERT_EQ(img(0, 2).r, 51);
    ASSERT_EQ(img(0, 2).g, 52);
    ASSERT_EQ(img(0, 2).b, 53);

    ASSERT_EQ(img(1, 2).r, 61);
    ASSERT_EQ(img(1, 2).g, 62);
    ASSERT_EQ(img(1, 2).b, 63);

    ASSERT_EQ(img.front().front().r, 11);
    ASSERT_EQ(img.front().back().b, 23);

    ASSERT_EQ(img.back().front().r, 51);
    ASSERT_EQ(img.back().back().b, 63);
}
