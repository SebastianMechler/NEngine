#pragma once

#include "NCompiler.h"
#include "NTypes.h"

/*
#define TGA_DESC_ABITS 0x0f
#define TGA_DESC_HORIZONTAL 0x10
#define TGA_DESC_VERTICAL 0x20
*/

namespace Nully
{
  enum class NImageTGAType : int8_t
  {
    NO_DATA = 0,
    COLOR_MAPPED = 1,
    COLOR_UNMAPPED = 2,
    BLACK_AND_WHITE = 3,
    COLOR_MAPPED_RLE = 9,
    COLOR_RLE = 10,
    BLACK_AND_WHITE_RLE = 11
  };


#ifdef NCOMPILER_VISUAL_STUDIO
  #pragma pack(push, 1)
#endif

  struct NImageDescriptor
  {
    // alphaChannel
    //These bits specify the number of attribute bits per
    //pixel. In the case of the TrueVista, these bits indicate
    //the number of bits per pixel which are designated as
    //Alpha Channel bits.For the ICB and TARGA
    //products, these bits indicate the number of overlay
    //bits available per pixel.
    int8_t alphaChannel : 4; // 0-3 alphaChannel

    // imageOrigin defines the ordering
    // bit 4    bit 5   result
    // 0        0       bottomLeft
    // 0        1       bottomRight
    // 1        0       topLeft
    // 1        1       topRight

    // or in hexadecimal... (way better to read...)
    // 0x0 = bottomLeft
    // 0x1 = bottomRight
    // 0x2 = topLeft
    // 0x3 = topRight
    int8_t imageOrigin : 2; // 4-5 imageOrigin

    int8_t unused : 2; // 6-7 unused
  };

  struct NImageTGAHeader 
  {
    int8_t idLength;
    int8_t colorMapType;
    NImageTGAType imageType;
    int16_t colorMapOrigin;
    int16_t colorMapLength;
    int8_t colorMapDepth;
    int16_t xOrigin;
    int16_t yOrigin;
    int16_t width;
    int16_t height;
    int8_t bitsPerPixel;
    int8_t imageDescriptor;
  };

#ifdef NCOMPILER_VISUAL_STUDIO
  #pragma pack(pop)
#endif
}