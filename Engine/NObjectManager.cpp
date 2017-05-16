#include "NObjectManager.h"

#include "NMemory.h"
#include "NMeshRenderer.h"

namespace Nully
{
  NObjectManager& NObjectManager::GetInstance()
  {
    static NObjectManager objectManager;
    return objectManager;
  }
  void NObjectManager::Add(IGameObject* a_object)
  {
    auto meshRenderer = a_object->GetComponent<NMeshRenderer>();

    if (meshRenderer)
    {
      m_objectsDrawable.insert(std::make_pair(meshRenderer->GetMesh(), a_object));     
    }
    else
    {
      m_objects.push_back(a_object);
    }
  }
  void NObjectManager::SetCamera(IGameObject* a_camera)
  {
    m_mainCamera = a_camera;
  }
  IGameObject* NObjectManager::GetCamera() const
  {
    return m_mainCamera;
  }
  void NObjectManager::Update(float a_deltaTime)
  {
    // update all objects
    for (auto e : m_objects)
    {
      e->Update(a_deltaTime);
    }

    // update all drawableObjects
    for (auto e : m_objectsDrawable)
    {
      e.second->Update(a_deltaTime);
    }

    // update main camera
    if (m_mainCamera)
    {
      m_mainCamera->Update(a_deltaTime);
    }
  }

  void NObjectManager::Shutdown()
  {
    for (auto& e : m_objects)
    {
      NSafeDelete(e);
    }
    m_objects.clear();

    for (auto& e : m_objectsDrawable)
    {
      NSafeDelete(e.second);
    }
    m_objects.clear();
  }

  NVector<IGameObject*>& NObjectManager::GetObjects()
  {
    return m_objects;
  }

  const NObjectListDrawable& NObjectManager::GetDrawableObjects()
  {
    return m_objectsDrawable;
  }

  NObjectManager::NObjectManager()
  {

  }
}

