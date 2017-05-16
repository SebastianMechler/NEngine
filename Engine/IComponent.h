#pragma once

#include "IComponentManager.h"

namespace Nully
{
  class IComponentManager;

  class IComponent
  {
  public:
    virtual void Start() = 0;
    virtual void Update(float a_deltaTime) = 0;
    virtual bool AddRequiredComponents(IComponentManager* a_componentManager) = 0;
    virtual ~IComponent() {};
  };
}

