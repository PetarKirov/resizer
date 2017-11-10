#include "image/bmp/io.h"
#include "image/core/algorithm.h"

#include <cstring>

namespace image
{
namespace bmp
{

core::Slice<const uint8_t> loadBitmapImage(
    core::Slice<const uint8_t> bytes, BmpV5File& resultInfo)
{
#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
#   error "Image loading on big endian targets is not yet implemented"
#endif

    using namespace core;

    Slice<const uint8_t> error = Slice<const uint8_t>::init();

    if (bytes.length() < sizeof(BmpGenericHeader))
        return error;

    const BmpGenericHeader& header = *(const BmpGenericHeader*)&bytes[0];

    if (header.signature != 0x4D42)
        return error;

    if (header.fileSize != bytes.length())
        return error;

    if (header.version != DIBVersion::BITMAPCOREHEADER &&
        header.version != DIBVersion::BITMAPINFOHEADER &&
        header.version != DIBVersion::BITMAPV2INFOHEADER &&
        header.version != DIBVersion::BITMAPV3INFOHEADER &&
        header.version != DIBVersion::BITMAPV4INFOHEADER &&
        header.version != DIBVersion::BITMAPV5INFOHEADER)
        return error;

    const int fileHeader = sizeof(BmpFileHeader);
    const uint32_t dibHeader = (uint32_t)header.version;

    Slice<uint8_t> resultAsBytes = sliceIntoBytes(resultInfo);

    copy(
        bytes.slice(0, fileHeader),
        resultAsBytes.slice(0, fileHeader));

    if (header.version == DIBVersion::BITMAPCOREHEADER)
    {
        const BmpV0File& file = *(const BmpV0File*)&bytes[0];
        resultInfo.width = file.width;
        resultInfo.height = file.height;
        resultInfo.colorPlanesCount = file.colorPlanesCount;
        resultInfo.bpp = file.bpp;
    }
    else
    {
        copy(
            bytes.skipTake(fileHeader, dibHeader),
            resultAsBytes.skipTake(fileHeader, dibHeader));
    }

    return bytes.slice(header.offsetToPixelArray, bytes.length());
}

} /* namespace bmp */
} /* namespace image */
