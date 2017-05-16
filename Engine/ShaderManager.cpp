#include "NShaderManager.h"

#include "NMemory.h"

namespace Nully
{
  bool NShaderManager::Load(IGraphics* a_graphics, const NString& a_path)
  {
    if (m_shaderMap.find(a_path) == m_shaderMap.end())
    {
      // if not in map
      IShader* shader = a_graphics->LoadShader(a_path.c_str());
      if (shader)
      {
        // loaded successfully
        // add shader to map..
        m_shaderMap[a_path] = shader;
        return true;
      }
      else
      {
        return false;
      }
    }

    // shader is already in map
    return true;
  }

  void NShaderManager::Shutdown()
  {
    for (auto& e : m_shaderMap)
    {
      NSafeDelete(e.second);
    }

    m_shaderMap.clear();
  }

  NShaderManager& NShaderManager::GetInstance()
  {
    static NShaderManager g_shaderManager;
    return g_shaderManager;
  }

  IShader* NShaderManager::GetShader(const NString & a_path)
  {
    auto element = m_shaderMap.find(a_path);
    if (element == m_shaderMap.end())
    {
      // not in map
      return nullptr;
    }

    return element->second;
  }

  NShaderManager::NShaderManager()
  {

  }
}
