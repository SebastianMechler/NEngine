#include "IComponentManager.h"

#include "NMemory.h"

namespace Nully
{
  IComponentManager::IComponentManager()
  {
    for (auto& e : m_components)
    {
      e.second->Start();
    }
  }
  void IComponentManager::RemoveComponent(IComponent* a_component)
  {
    //auto it = std::find(m_components.begin(), m_components.end(), a_component);
    //    
    //if (it != m_components.end())
    //{
    //  //std::swap(*it, m_components.back());
    //  //m_components.pop_back();
    //  m_components.erase(it);
    //  delete a_component;
    //  a_component = nullptr;
    //}
  }
  void IComponentManager::UpdateComponents(float a_deltaTime)
  {
    for (auto& e : m_components)
    {
      e.second->Update(a_deltaTime);
    }
  }
  IComponentManager::~IComponentManager()
  {
    // cleanup all components
    for (auto& e : m_components)
    {
      if (e.second)
      {
        NSafeDelete(e.second);
      }
    }
  }
}
