#pragma once

#include <Windows.h>

#include "NTypes.h"

namespace Nully
{
  struct NGraphicsDesc
  {
    uint32_t width;
    uint32_t height;
    HWND hwnd;
  };
}