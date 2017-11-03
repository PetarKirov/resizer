#include "test_util/assert.h"
#include "image/bmp/defs.h"

using namespace image::bmp;

void verify_struct_def_sizes();

int main()
{
    verify_struct_def_sizes();
}

void verify_struct_def_sizes()
{
    ASSERT_EQ(sizeof(BmpFileHeader), 14);
    ASSERT_EQ(sizeof(DIBHeaderV0), (size_t)DIBVersion::BITMAPCOREHEADER);
    STATIC_ASSERT(sizeof(BmpFileHeader) == 14);
    STATIC_ASSERT(sizeof(DIBHeaderV0) == (size_t)DIBVersion::BITMAPCOREHEADER);
    STATIC_ASSERT(sizeof(DIBHeaderV1) == (size_t)DIBVersion::BITMAPINFOHEADER);
    STATIC_ASSERT(sizeof(DIBHeaderV2) == (size_t)DIBVersion::BITMAPV2INFOHEADER);
    STATIC_ASSERT(sizeof(DIBHeaderV3) == (size_t)DIBVersion::BITMAPV3INFOHEADER);
    STATIC_ASSERT(sizeof(DIBHeaderV4) == (size_t)DIBVersion::BITMAPV4INFOHEADER);
    STATIC_ASSERT(sizeof(DIBHeaderV5) == (size_t)DIBVersion::BITMAPV5INFOHEADER);
}
