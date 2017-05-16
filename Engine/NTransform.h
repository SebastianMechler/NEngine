#pragma once

#include "IComponent.h"
#include "NVector3.h"

// TODO: write custom math library to get rid of DirectXMath...
#include <DirectXMath.h>

namespace Nully
{
  class NTransform : public IComponent
  {
  public:
    // IComponent Interface
    void Start() override;
    void Update(float a_deltaTime) override;
    bool AddRequiredComponents(IComponentManager* a_componentManager) override;

    NTransform();
    NTransform(const DirectX::XMFLOAT3& a_position, const DirectX::XMFLOAT3& a_rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), const DirectX::XMFLOAT3& a_scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    const DirectX::XMFLOAT3 GetPosition();
    const DirectX::XMFLOAT3 GetRotation();
    const DirectX::XMFLOAT3 GetScale();

    void SetRotation(float a_x, float a_y, float a_z);
    void SetPosition(float a_x, float a_y, float a_z);
    void SetScale(float a_x, float a_y, float a_z);

    DirectX::XMFLOAT4X4& GetWorld();
    const DirectX::XMFLOAT3& GetForward();
    const DirectX::XMFLOAT3& GetSide();
    const DirectX::XMFLOAT3& GetUp();

  private:

    void UpdateForwardSideUp();

    DirectX::XMFLOAT3 m_position;
    DirectX::XMFLOAT3 m_rotation;
    DirectX::XMFLOAT3 m_scale;

    DirectX::XMFLOAT3 m_forward;
    DirectX::XMFLOAT3 m_side;
    DirectX::XMFLOAT3 m_up;

    DirectX::XMFLOAT4X4 m_world;
  };
}
