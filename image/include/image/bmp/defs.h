#ifndef IMAGE_BMP_DEFS_H
#define IMAGE_BMP_DEFS_H

#include <stdint.h>
#include "image/config/config.h"

namespace image
{
namespace bmp
{

// Represents the file header of at the start of all .bmp images.
#pragma pack(2)
struct BmpFileHeader
{
    uint16_t signature;
    uint32_t fileSize;
    uint16_t _reserved1;
    uint16_t _reserved2;
    uint32_t offsetToPixelArray;
};

// Enum (class) definitions for various fields:

ENUM_CLASS_BEGIN(DIBVersion, uint32_t)
    BITMAPCOREHEADER =      12,
    //OS22XBITMAPHEADER =   64, unsupported
    BITMAPINFOHEADER =      40,
    BITMAPV2INFOHEADER =    52,
    BITMAPV3INFOHEADER =    56,
    BITMAPV4INFOHEADER =    108,
    BITMAPV5INFOHEADER =    124
ENUM_CLASS_END

ENUM_CLASS_BEGIN(Compression, uint32_t)
    BI_RGB =            0,
    BI_RLE8 =           1,
    BI_RLE4 =           2,
    BI_BITFIELDS =      3,
    BI_JPEG =           4,
    BI_PNG =            5,
    BI_ALPHABITFIELDS = 6,
    BI_CMYK =           11,
    BI_CMYKRLE8 =       12,
    BI_CMYKTLE4 =       13
ENUM_CLASS_END

ENUM_CLASS_BEGIN(LogicalColorSpace, uint32_t)
    calibratedRGB = 0x00000000,
    sRGB = 0x73524742,
    windowsColorSpace = 0x57696E20
ENUM_CLASS_END

// Header definitions for DIBs (device-independent bitmaps):

struct DIBHeaderV0
{
    DIBVersion version;
    int16_t width;
    int16_t height;
    uint16_t colorPlanesCount;
    uint16_t bpp;
};

struct DIBHeaderV1
{
    DIBVersion version;
    int32_t width;
    int32_t height;
    uint16_t colorPlanesCount;
    uint16_t bpp;
    Compression compression;
    uint32_t sizeOfPixelArray;
    int32_t  pixelsPerMeterX;
    int32_t  pixelsPerMeterY;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
};

struct DIBHeaderV2 : DIBHeaderV1
{
    uint32_t redBitMask;
    uint32_t greenBitMask;
    uint32_t blueBitMask;
};

struct DIBHeaderV3 : DIBHeaderV2
{
    uint32_t alphaMask;
};

typedef uint32_t FXPT2DOT30;

struct CIE_XYZ
{
    FXPT2DOT30 x;
    FXPT2DOT30 y;
    FXPT2DOT30 z;
};

struct CIE_XYZ_Triple
{
    CIE_XYZ red;
    CIE_XYZ green;
    CIE_XYZ blue;
};

struct DIBHeaderV4 : DIBHeaderV3
{
    LogicalColorSpace logicalColorSpace;
    CIE_XYZ_Triple colorSpaceEndPoints;
    uint32_t gammaRed;
    uint32_t gammaGreen;
    uint32_t gammaBlue;
};

struct DIBHeaderV5 : DIBHeaderV4
{
    uint32_t intent;
    uint32_t profileData;
    uint32_t profileSize;
    uint32_t reserved;
};

} /* namespace bmp */
} /* namespace image */

#endif /* IMAGE_BMP_DEFS_H */
