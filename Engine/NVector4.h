#pragma once

#include "NVector3.h"

class NVector3;

namespace Nully
{
  class NVector4
  {
  public:
    float x, y, z, w;

    NVector4();
    NVector4(float a_x, float a_y, float a_z, float a_w);
    void operator=(const NVector3& a_vector);
  };
}