#pragma once

#include "IGameObject.h"
#include "NVector.h"
#include "NUnorderedMultimap.h"
#include "NString.h"

namespace Nully
{
  typedef NVector<IGameObject*> NObjectList;

  typedef NUnorderedMultimap<NString, IGameObject*> NObjectListDrawable;

  class NObjectManager
  {
  public:
    static NObjectManager& GetInstance();
    void Add(IGameObject* a_object);
    void SetCamera(IGameObject* a_camera);
    IGameObject* GetCamera() const;
    void Update(float a_deltaTime);
    void Shutdown();
    NObjectList& GetObjects();

    const NObjectListDrawable& GetDrawableObjects();

  private:
    NObjectManager();
    NObjectManager(const NObjectManager&);
    IGameObject* m_mainCamera = nullptr;
    NObjectList m_objects;
    NObjectListDrawable m_objectsDrawable;
  };
}

/*
#pragma once

#include "IGameObject.h"
#include "NVector.h"

namespace Nully
{
typedef NVector<IGameObject*> NObjectList;

class NObjectManager
{
public:
static NObjectManager& GetInstance();
void Add(IGameObject* a_object);
void SetCamera(IGameObject* a_camera);
IGameObject* GetCamera() const;
void Update(float a_deltaTime);
void Shutdown();
NObjectList& GetObjects();

private:
NObjectManager();
NObjectManager(const NObjectManager&);
IGameObject* m_mainCamera = nullptr;
NObjectList m_objects;

};
}













#include "NObjectManager.h"

#include "NMemory.h"

namespace Nully
{
NObjectManager& NObjectManager::GetInstance()
{
static NObjectManager objectManager;
return objectManager;
}
void NObjectManager::Add(IGameObject* a_object)
{
m_objects.push_back(a_object);
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
for (auto e : m_objects)
{
e->Update(a_deltaTime);
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
}

NVector<IGameObject*>& NObjectManager::GetObjects()
{
return m_objects;
}

NObjectManager::NObjectManager()
{

}
}





*/