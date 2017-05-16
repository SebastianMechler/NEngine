#pragma once

#include "NGraphicsDesc.h"
#include "NFillMode.h"
#include "NPrimitiveTopology.h"
#include "IShader.h"
#include "NObj.h"
#include "IMesh.h"
#include "IGameObject.h"
#include "ITexture.h"

namespace Nully
{
  class IGraphics
  {
  public:
    virtual bool Initialize(const NGraphicsDesc& a_graphicsDesc) = 0;
    virtual void Shutdown() = 0;

    virtual void Begin() = 0;
    virtual void End() = 0;

    virtual void Clear() = 0;
    virtual void SetFillMode(const NFillMode a_fillMode) = 0;
    virtual void SetPrimitiveTopology(const NPrimitiveTopology a_primitiveTopology) = 0;

    virtual bool OnResize(uint32_t a_width, uint32_t a_height) = 0;

    virtual IShader* LoadShader(const char* a_path) = 0;
    virtual void SetShader(IShader* a_shader) = 0;

    virtual IMesh* LoadMesh(NObj& a_obj) const = 0;
    virtual void SetMesh(IMesh* a_mesh) const = 0;

    virtual IMesh* LoadTerrain(float a_width, float a_height, uint32_t a_sizeX, uint32_t a_sizeY) = 0;
    virtual void SetTerrain(IMesh* a_terrain) = 0;

    virtual ITexture* LoadTextureTGA(const char* a_file) = 0;
    virtual void SetTexture(ITexture* a_texture) = 0;

    virtual void DrawGameobject(IGameObject* a_gameObject) = 0; // will be deleted and changed by scene management later on

    virtual ~IGraphics() {}
  };
}
