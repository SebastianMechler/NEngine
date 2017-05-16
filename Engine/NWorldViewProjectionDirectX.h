#pragma once

#include <DirectXMath.h>

namespace Nully
{
  struct NWorldViewProjectionDirectX
  {
    DirectX::XMFLOAT4X4 world;
    DirectX::XMFLOAT4X4 view;
    DirectX::XMFLOAT4X4 projection;
  };
}

