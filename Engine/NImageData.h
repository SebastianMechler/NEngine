#pragma once

#include "NTypes.h"

namespace Nully
{
  struct NImageData
  {
    uint32_t width;
    uint32_t height;
    uint8_t bitsPerPixel;
    void* data;
  };
}
