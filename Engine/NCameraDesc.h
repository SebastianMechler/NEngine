#pragma once

#include "NVector3.h"
#include "NTypes.h"

namespace Nully
{
  struct NCameraDesc
  {
    float nearPlane; // usually 1.0f
    float farPlane; // usually 1000.0f
    float fieldOfView; // PI * 0.35f

    uint32_t screenWidth; // width of screen
    uint32_t screenHeight; // height of screen

    NCameraDesc()
      : nearPlane(0.0f)
      , farPlane(0.0f)
      , fieldOfView(0.0f)
      , screenWidth(0)
      , screenHeight(0)
    {

    }
  };
}
