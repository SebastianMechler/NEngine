#pragma once

#include "NUnorderedMap.h"
#include "IGraphics.h"
#include "IShader.h"
#include "NString.h"

namespace Nully
{
  typedef NUnorderedMap<NString, IShader*> NShaderMap;

  class NShaderManager
  {
  public:
    bool Load(IGraphics* a_graphics, const NString& a_path);
    void Shutdown();
    static NShaderManager& GetInstance();
    IShader* GetShader(const NString& a_path);

  private:
    NShaderManager();
    NShaderMap m_shaderMap;
  };
}
