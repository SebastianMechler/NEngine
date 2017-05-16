#pragma once

#include <d3d11.h>

#include "IMesh.h"
#include "NVertexBuffer.h"
#include "NIndexBuffer.h"

namespace Nully
{
  class NMeshDirectX11 : public IMesh
  {
  public:
    // Interface IMesh
    NPrimitiveTopology GetTopology() override;
    void SetTopology(const NPrimitiveTopology a_topology) override;

    static NMeshDirectX11* Load(ID3D11Device* a_device, NObj& a_obj);
    static NMeshDirectX11* LoadTerrain(ID3D11Device* a_device, float a_width, float a_depth, uint32_t a_m, uint32_t a_n);

    void Set(ID3D11DeviceContext* a_deviceContext);

    NMeshDirectX11();
    ~NMeshDirectX11();

    NVertexBuffer m_vertexBuffer;
    NIndexBuffer m_indexBuffer;

  private:
    NPrimitiveTopology m_primitiveTopology;
  };
}
