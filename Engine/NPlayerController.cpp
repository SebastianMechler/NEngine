#include "NPlayerController.h"
#include "NInput.h"
#include "NTransform.h"

namespace Nully
{
  void NPlayerController::Start()
  {
  }
  void NPlayerController::Update(float a_deltaTime)
  {
    if (NInput::GetInstance().GetKey(NKey::K_W))
    {
      auto transform = m_componentManager->GetComponent<NTransform>();
      if (transform)
      {
        auto position = transform->GetPosition();
        auto forward = transform->GetForward();
        position.x += forward.x * m_speed * a_deltaTime;
        position.y += forward.y * m_speed * a_deltaTime;
        position.z += forward.z * m_speed * a_deltaTime;
        transform->SetPosition(position.x, position.y, position.z);
      }
    }

    if (NInput::GetInstance().GetKey(NKey::K_S))
    {
      auto transform = m_componentManager->GetComponent<NTransform>();
      if (transform)
      {
        auto position = transform->GetPosition();
        auto forward = transform->GetForward();
        position.x -= forward.x * m_speed * a_deltaTime;
        position.y -= forward.y * m_speed * a_deltaTime;
        position.z -= forward.z * m_speed * a_deltaTime;
        transform->SetPosition(position.x, position.y, position.z);
      }
    }

    if (NInput::GetInstance().GetKey(NKey::K_A))
    {
      auto transform = m_componentManager->GetComponent<NTransform>();
      if (transform)
      {
        auto position = transform->GetPosition();
        auto side = transform->GetSide();
        position.x += side.x * m_speed * a_deltaTime;
        position.y += side.y * m_speed * a_deltaTime;
        position.z += side.z * m_speed * a_deltaTime;
        transform->SetPosition(position.x, position.y, position.z);
      }
    }

    if (NInput::GetInstance().GetKey(NKey::K_D))
    {
      auto transform = m_componentManager->GetComponent<NTransform>();
      if (transform)
      {
        auto position = transform->GetPosition();
        auto side = transform->GetSide();
        position.x -= side.x * m_speed * a_deltaTime;
        position.y -= side.y * m_speed * a_deltaTime;
        position.z -= side.z * m_speed * a_deltaTime;
        transform->SetPosition(position.x, position.y, position.z);
      }
    }

    if (NInput::GetInstance().GetKey(NKey::K_UP))
    {
      auto transform = m_componentManager->GetComponent<NTransform>();
      if (transform)
      {
        auto position = transform->GetPosition();
        auto up = transform->GetUp();
        position.y += up.y * m_speed * a_deltaTime;
        transform->SetPosition(position.x, position.y, position.z);
      }
    }

    if (NInput::GetInstance().GetKey(NKey::K_DOWN))
    {
      auto transform = m_componentManager->GetComponent<NTransform>();
      if (transform)
      {
        auto position = transform->GetPosition();
        auto up = transform->GetUp();
        position.y -= up.y * m_speed * a_deltaTime;
        transform->SetPosition(position.x, position.y, position.z);
      }
    }

    if (NInput::GetInstance().GetKey(NKey::K_LEFT))
    {
      m_rotationY -= a_deltaTime * 0.1f;
      auto transform = m_componentManager->GetComponent<NTransform>();
      transform->SetRotation(0.0f, m_rotationY, 0.0f);
    }

    if (NInput::GetInstance().GetKey(NKey::K_RIGHT))
    {
      m_rotationY += a_deltaTime * 0.1f;
      auto transform = m_componentManager->GetComponent<NTransform>();
      transform->SetRotation(0.0f, m_rotationY, 0.0f);
    }
  }
  bool NPlayerController::AddRequiredComponents(IComponentManager* a_componentManager)
  {
    m_componentManager = a_componentManager;

    return true;
  }
  NPlayerController::NPlayerController()
    : m_componentManager(nullptr)
  {
  }
}
