#pragma once

#include "NMap.h"
#include "IComponent.h"

namespace Nully
{
  class IComponent;

	class IComponentManager
  {
  public:
    IComponentManager();
		
    template <typename T, typename ...Args>
    T* AddComponent(Args ... args);

    template <typename T>
    void RemoveComponent();

    void RemoveComponent(IComponent* a_component);

    template <typename T>
    T* GetComponent();

    virtual ~IComponentManager();

  protected:
    void UpdateComponents(float a_deltaTime);

    NMap<size_t, IComponent*> m_components; // key = hash, value = ptr
  };
}
#include "IComponentManager.hpp"

