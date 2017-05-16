#pragma once

#include <D3D11.h>

#include "NTypes.h"
#include "NDirectxHelper.h"
#include "NVector2.h"
#include "NVector4.h"
#include "NVector3.h"

namespace Nully
{
  struct NVertexDefault
  {
    NVector3 position;
    NVector4 color;
    NVector3 normal;
    NVector2 uv;
  };

  class NVertexBuffer
  {
  public:
    NVertexBuffer();
    ~NVertexBuffer();

    bool Load(ID3D11Device* a_device, NVertexDefault* a_vertexData, uint32_t a_vertexCount);
    void SetBuffer(ID3D11DeviceContext* a_deviceContext);

    ID3D11Buffer* GetBuffer() const;
    uint32_t GetStride() const; // TODO: make this better...
    uint32_t GetVertexCount() const;

  private:
    ID3D11Buffer* m_vertexBuffer;
    uint32_t m_vertexCount;
    uint32_t m_stride;
  };
}