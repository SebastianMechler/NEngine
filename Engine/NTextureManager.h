#pragma once

#include "IGraphics.h"
#include "ITexture.h"
#include "NString.h"
#include "NUnorderedMap.h"

namespace Nully
{
  typedef NUnorderedMap<NString, ITexture*> NTextureMap;

  class NTextureManager
  {
  public:
    bool Load(IGraphics* a_graphics, const NString& a_path);
    void Shutdown();
    static NTextureManager& GetInstance();

    ITexture* GetTexture(const NString& a_path);

  private:
    NTextureManager();
    NTextureMap m_textureMap;
  };
}
