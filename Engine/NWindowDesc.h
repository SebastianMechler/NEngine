#pragma once

#include "NTypes.h"

namespace Nully
{
  struct NWindowDesc
  {
    uint32_t width;
    uint32_t height;
    const char* name;
    const char* className;
    bool isFullScreen;
  };
}

