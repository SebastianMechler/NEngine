#include "NVector2.h"

namespace Nully
{
  NVector2::NVector2()
    : x(0.0f)
    , y(0.0f)
  {
  }
  NVector2::NVector2(float a_x, float a_y)
    : x(a_x)
    , y(a_y)
  {
  }
  bool NVector2::IsNull()
  {
    return x == 0.0f && y == 0.0f;
  }
  bool NVector2::operator==(const NVector2 & other)
  {
    return (this->x == other.x && this->y == other.y);
  }
}

