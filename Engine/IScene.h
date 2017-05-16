#pragma once

#include "IGraphics.h"

namespace Nully
{
  class IGraphics;

  class IScene
  {
  public:
    virtual bool Initialize() = 0;
    virtual void Update(float a_deltaTime) = 0;
    virtual void Draw(IGraphics* a_renderer) = 0;
    virtual void Shutdown() = 0;

    virtual ~IScene() {}
  };
}
