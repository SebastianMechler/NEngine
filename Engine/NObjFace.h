#pragma once

#include "NTypes.h"

namespace Nully
{
  // triangulated faces.
  struct NFace
  {
    uint32_t v1;
    uint32_t v2;
    uint32_t v3;

    uint32_t uv1;
    uint32_t uv2;
    uint32_t uv3;

    uint32_t normalIndex;
  };
}
