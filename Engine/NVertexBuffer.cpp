#include "NVertexBuffer.h"

#include "NMemory.h"

namespace Nully
{
  NVertexBuffer::NVertexBuffer()
    : m_vertexBuffer(nullptr)
    , m_stride(0)
    , m_vertexCount(0)
  {
  }
  NVertexBuffer::~NVertexBuffer()
  {
    NSafeRelease(m_vertexBuffer);
  }
  bool NVertexBuffer::Load(ID3D11Device* a_device, NVertexDefault* a_vertexData, uint32_t a_vertexCount)
  {
    if (a_vertexData == nullptr)
    {
      return false;
    }
	
    m_vertexCount = a_vertexCount;
    m_stride = sizeof(NVertexDefault);

    // Fill in a buffer description.
    D3D11_BUFFER_DESC bufferDesc;
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = (m_stride * m_vertexCount + 15) / 16 * 16;;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0;
    bufferDesc.MiscFlags = 0;

    // Fill in the subresource data.
    D3D11_SUBRESOURCE_DATA InitData;
    InitData.pSysMem = a_vertexData;
    InitData.SysMemPitch = 0;
    InitData.SysMemSlicePitch = 0;

    // Create the vertex buffer.
    if (NDirectXFailed(a_device->CreateBuffer(&bufferDesc, &InitData, &m_vertexBuffer)))
    {
      return false;
    }

    return true;
  }
  void NVertexBuffer::SetBuffer(ID3D11DeviceContext* a_deviceContext)
  {
    UINT offset = 0;
    a_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &m_stride, &offset);
  }
  ID3D11Buffer * NVertexBuffer::GetBuffer() const
  {
    return m_vertexBuffer;
  }
  uint32_t NVertexBuffer::GetStride() const
  {
    return m_stride;
  }
  uint32_t NVertexBuffer::GetVertexCount() const
  {
    return m_vertexCount;
  }
}
