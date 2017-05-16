#include "NMeshManager.h"

#include "NObj.h"

namespace Nully
{
  bool NMeshManager::Load(IGraphics* a_graphics, const NString& a_path)
  {
    if (m_meshMap.find(a_path) == m_meshMap.end())
    {
      NObj obj;
      if (!obj.Load(a_path.c_str()))
      {
        return false;
      }

      // if not in map
      IMesh* mesh = a_graphics->LoadMesh(obj);
      if (mesh)
      {
        // loaded successfully
        // add mesh to map..
        m_meshMap[a_path] = mesh;
        return true;
      }
      else
      {
        return false;
      }
    }

    // mesh is already in map
    return true;
  }
  bool NMeshManager::CreateTerrain(IGraphics* a_graphics, const NString& a_terrainName, float a_width, float a_height, uint32_t a_sizeX, uint32_t a_sizeY)
  {
    if (m_meshMap.find(a_terrainName) == m_meshMap.end())
    {
      // if not in map
      IMesh* mesh = a_graphics->LoadTerrain(a_width, a_height, a_sizeX, a_sizeY);
      if (mesh)
      {
        // loaded successfully
        // add mesh to map..
        m_meshMap[a_terrainName] = mesh;
        return true;
      }
      else
      {
        return false;
      }
    }

    // mesh is already in map
    return true;
  }
  void NMeshManager::Shutdown()
  {
    for (auto& e : m_meshMap)
    {
        NSafeDelete(e.second);
    }

    m_meshMap.clear();
  }

  NMeshManager::NMeshManager()
  {

  }

  NMeshManager& NMeshManager::GetInstance()
  {
    static NMeshManager g_meshManager;
    return g_meshManager;
  }
  IMesh* NMeshManager::GetMesh(const NString & a_path)
  {
    auto element = m_meshMap.find(a_path);
    if (element == m_meshMap.end())
    {
      // not in map
      return nullptr;
    }

    return element->second;
  }
}