#pragma once

#include "IScene.h"

namespace Nully
{
  class NScene : public IScene
  {
  public:
    // IScene Interface
    bool Initialize() override;
    void Update(float a_deltaTime) override;
    void Draw(IGraphics* a_renderer) override;
    void Shutdown() override;

  private:
    IGameObject* m_rotatingObject = nullptr;
    float rotationY = 0.0f;
	float movementSpeed = 3.0f;
  };
}