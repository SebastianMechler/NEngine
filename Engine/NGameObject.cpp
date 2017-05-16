#include "NGameObject.h"

#include "NObjectManager.h"
#include "NGlobalData.h"

namespace Nully
{
  void NGameObject::Start()
  {
    AddComponent<NTransform>();
  }
  void NGameObject::Update(float a_deltaTime)
  {
    UpdateComponents(a_deltaTime);
  }

  NGameObject::NGameObject()
  {
    Start();
  }
  NGameObject::~NGameObject()
  {
  }
}
