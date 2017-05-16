#include "NIndexBuffer.h"

namespace Nully
{
  NIndexBuffer::NIndexBuffer()
    : m_indexBuffer(nullptr)
    , m_count(0)
  {
  }

  NIndexBuffer::~NIndexBuffer()
  {
    NSafeRelease(m_indexBuffer);
  }

  bool NIndexBuffer::Create(ID3D11Device* a_device, uint32_t * a_indices, const uint32_t a_indicesCount)
  {
    // Fill in a buffer description.
    D3D11_BUFFER_DESC bufferDesc;
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = (sizeof(uint32_t) * a_indicesCount + 15) / 16 * 16;
    bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0;
    bufferDesc.MiscFlags = 0;

    // Define the resource data.
    D3D11_SUBRESOURCE_DATA InitData;
    InitData.pSysMem = a_indices;
    InitData.SysMemPitch = 0;
    InitData.SysMemSlicePitch = 0;

    // Create the buffer with the device.
    if (NDirectXFailed(a_device->CreateBuffer(&bufferDesc, &InitData, &m_indexBuffer)))
    {
      return false;
    }

    m_count = a_indicesCount;

    return true;
  }

  void NIndexBuffer::SetBuffer(ID3D11DeviceContext * a_deviceContext) const
  {
    a_deviceContext->IASetIndexBuffer(GetBuffer(), DXGI_FORMAT_R32_UINT, 0);
  }

  ID3D11Buffer* NIndexBuffer::GetBuffer() const
  {
    return m_indexBuffer;
  }

  uint32_t NIndexBuffer::GetCount() const
  {
    return m_count;
  }
}

