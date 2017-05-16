#include "NTextureManager.h"

namespace Nully
{
  bool NTextureManager::Load(IGraphics* a_graphics, const NString& a_path)
  {
    if (m_textureMap.find(a_path) == m_textureMap.end())
    {
      ITexture* texture = a_graphics->LoadTextureTGA(a_path.c_str());

      if (!texture)
      {
        return false;
      }      
      
      // loaded successfully
      // add texture to map..
      m_textureMap[a_path] = texture;
    }

    // texture is already in map
    return true;
  }
  void NTextureManager::Shutdown()
  {
    for (auto& e : m_textureMap)
    {
      NSafeDelete(e.second);
    }

    m_textureMap.clear();
  }
  NTextureManager& NTextureManager::GetInstance()
  {
    static NTextureManager g_textureManager;
    return g_textureManager;
  }
  ITexture* NTextureManager::GetTexture(const NString & a_path)
  {
    auto element = m_textureMap.find(a_path);
    if (element == m_textureMap.end())
    {
      // not in map
      return nullptr;
    }

    return element->second;
  }

  NTextureManager::NTextureManager()
  {

  }
}
