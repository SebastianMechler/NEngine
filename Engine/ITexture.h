#pragma once

#include "NTypes.h"

namespace Nully
{
  class ITexture
  {
  public:
    virtual bool Load(const char* a_path) = 0;
    virtual uint32_t GetWidth() = 0;
    virtual uint32_t GetHeight() = 0;
    virtual uint8_t GetBitsPerPixel() = 0;

    virtual ~ITexture() {}
  };
}