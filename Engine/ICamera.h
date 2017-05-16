#pragma once

#include "NCameraDesc.h"
#include <DirectXMath.h>

namespace Nully
{
  class ICamera
  {
  public:
    virtual bool Initialize(const NCameraDesc& a_cameraDesc) = 0;

    virtual DirectX::XMFLOAT4X4& GetView() = 0;
    virtual DirectX::XMFLOAT4X4& GetProjection() = 0;

    virtual ~ICamera() {};
  };
}
