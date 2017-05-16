#pragma once

#include "IGraphics.h"
#include "IMesh.h"
#include "NString.h"
#include "NUnorderedMap.h"

namespace Nully
{
  typedef NUnorderedMap<NString, IMesh*> NMeshMap;

  class NMeshManager
  {
  public:
    bool Load(IGraphics* a_graphics, const NString& a_path);
    bool CreateTerrain(IGraphics* a_graphics, const NString& a_terrainName, float a_width, float a_height, uint32_t a_sizeX, uint32_t a_sizeY);
    void Shutdown();
    static NMeshManager& GetInstance();

    IMesh* GetMesh(const NString& a_path);

  private:
    NMeshManager();
    NMeshMap m_meshMap;
  };
}
