#pragma once

#include "IComponentManager.h"
#include "NString.h"

namespace Nully
{
  class IGameObject : public IComponentManager
  {
  public:
    virtual void Start() = 0;
    virtual void Update(float a_deltaTime) = 0;
    //virtual void LateUpdate(float a_deltaTime) = 0;
    //virtual void FixedUpdate(float a_deltaTime) = 0;
    // void SetParent(Gameobject& a_gameobject);
    // void SetParent(Transform& a_transform);

    virtual ~IGameObject() {}
  };
}