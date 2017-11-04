#include "image/bmp/io.h"

#include <cstring>

namespace image
{
namespace bmp
{

bool loadHeader(core::Slice<const uint8_t> data, BmpV5File* result)
{
#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
#   error "Image loading on big endian targets is not yet implemented"
#endif

    const int genericHeaderSize = sizeof(BmpGenericHeader);

    if (data.length() < sizeof(genericHeaderSize))
        return false;

    const BmpGenericHeader* base = (const BmpGenericHeader*)&data[0];

    if (base->signature != 0x4D42)
        return false;

    if (base->fileSize != data.length())
        return false;

    if (base->version != DIBVersion::BITMAPCOREHEADER &&
        base->version != DIBVersion::BITMAPINFOHEADER &&
        base->version != DIBVersion::BITMAPV2INFOHEADER &&
        base->version != DIBVersion::BITMAPV3INFOHEADER &&
        base->version != DIBVersion::BITMAPV4INFOHEADER &&
        base->version != DIBVersion::BITMAPV5INFOHEADER)
        return false;

    std::memcpy((void*)result, base, genericHeaderSize);

    if (base->version == DIBVersion::BITMAPCOREHEADER)
    {

        return true;
    }
    else if (base->version == DIBVersion::BITMAPINFOHEADER)
    {
        const BmpV1File* base = (const BmpV1File*)&data[0];
        std::memcpy((void*)result, base, sizeof(BmpV1File));
        return true;
    }
    else
        return false;
}

} /* namespace bmp */
} /* namespace image */
