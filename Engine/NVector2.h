#pragma once

namespace Nully
{
  class NVector2
  {
  public:
    NVector2();
    NVector2(float a_x, float a_y);

    float x, y;

    bool IsNull();

    bool operator==(const NVector2& other);
  };
}