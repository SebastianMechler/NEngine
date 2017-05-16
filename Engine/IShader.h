#pragma once

namespace Nully
{
  class IShader
  {
  public:
    virtual void Set(void* a_deviceContext) = 0;

    virtual ~IShader() {};
  };
}
