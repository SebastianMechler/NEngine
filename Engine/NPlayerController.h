#pragma once

#include "IComponent.h"
#include "NVector3.h"

namespace Nully
{
  class NPlayerController : public IComponent
  {
  public:
    // IComponent Interface
    void Start() override;
    void Update(float a_deltaTime) override;
    bool AddRequiredComponents(IComponentManager* a_componentManager) override;

    NPlayerController();

    float m_speed = 25.0f;
	float m_rotationSpeed = 2.5f;
    float m_rotationY = 0.0f;
  private:
    IComponentManager* m_componentManager;
  };
}