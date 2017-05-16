#pragma once

#include "IGameObject.h"
#include "NTransform.h"

namespace Nully
{
  class NGameObject : public IGameObject
  {
  public:
    // IGameObject Interface
    void Start() override;
    void Update(float a_deltaTime) override;

    template <typename T>
    static IGameObject* Instantiate(bool a_addToObjectManager = true);

    NGameObject();
    virtual ~NGameObject();
  };







  template <typename T>
  IGameObject* NGameObject::Instantiate(bool a_addToObjectManager)
  {
    IGameObject* newObj = new T();

    if (a_addToObjectManager)
    {
      NObjectManager::GetInstance().Add(newObj);
    }

    return newObj;
  }
}