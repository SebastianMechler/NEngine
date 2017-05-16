#pragma once

#include <D3D11.h>

#include "NTypes.h"
#include "NMemory.h"
#include "NDirectxHelper.h"

namespace Nully
{
  class NIndexBuffer
  {
  public:
    NIndexBuffer();
    ~NIndexBuffer();

    bool Create(ID3D11Device* a_device, uint32_t* a_indices, const uint32_t a_indicesCount);
    void SetBuffer(ID3D11DeviceContext* a_deviceContext) const;
    ID3D11Buffer* GetBuffer() const;
    uint32_t GetCount() const;

  private:
    ID3D11Buffer* m_indexBuffer;
    uint32_t m_count;
  };
}