#include "NTransform.h"

using namespace DirectX;

namespace Nully
{
  NTransform::NTransform()
    : m_position(0.0f, 0.0f, 0.0f)
    , m_rotation(0.0f, 0.0f, 0.0f)
    , m_scale(1.0f, 1.0f, 1.0f)
    , m_forward(0.0f, 0.0f, 0.0f)
    , m_up(0.0f, 0.0f, 0.0f)
    , m_side(0.0f, 0.0f, 0.0f)
  {
    XMStoreFloat4x4(&m_world, XMMatrixIdentity());
    UpdateForwardSideUp();
  }

  NTransform::NTransform(const DirectX::XMFLOAT3 & a_position, const DirectX::XMFLOAT3 & a_rotation, const DirectX::XMFLOAT3 & a_scale)
    : m_position(a_position)
    , m_rotation(a_rotation)
    , m_scale(a_scale)
    , m_forward(0.0f, 0.0f, 0.0f)
    , m_up(0.0f, 0.0f, 0.0f)
    , m_side(0.0f, 0.0f, 0.0f)
  {
    XMStoreFloat4x4(&m_world, XMMatrixIdentity());
    UpdateForwardSideUp();
  }

  const DirectX::XMFLOAT3 NTransform::GetPosition()
  {
    return m_position;
  }

  const DirectX::XMFLOAT3 NTransform::GetRotation()
  {
    return m_rotation;
  }

  const DirectX::XMFLOAT3 NTransform::GetScale()
  {
    return m_scale;
  }

  void NTransform::SetRotation(float a_x, float a_y, float a_z)
  {
    m_rotation.x = a_x;
    m_rotation.y = a_y;
    m_rotation.z = a_z;

    UpdateForwardSideUp();
  }

  void NTransform::SetPosition(float a_x, float a_y, float a_z)
  {
    m_position.x = a_x;
    m_position.y = a_y;
    m_position.z = a_z;
  }

  void NTransform::SetScale(float a_x, float a_y, float a_z)
  {
    m_scale.x = a_x;
    m_scale.y = a_y;
    m_scale.z = a_z;
  }

  DirectX::XMFLOAT4X4& NTransform::GetWorld()
  {
    // translation
    auto T = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
    // rotation
    auto R = XMMatrixRotationX(m_rotation.x) * XMMatrixRotationY(m_rotation.y) * XMMatrixRotationZ(m_rotation.z);
    // scaling
    auto S = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);

    XMStoreFloat4x4(&m_world, DirectX::XMMatrixTranspose(R * S * T));

    return m_world;
  }

  const DirectX::XMFLOAT3& NTransform::GetForward()
  {
    return m_forward;
  }

  const DirectX::XMFLOAT3& NTransform::GetSide()
  {
    return m_side;
  }

  const DirectX::XMFLOAT3& NTransform::GetUp()
  {
    return m_up;
  }

  void NTransform::UpdateForwardSideUp()
  {
    // rotation
    auto R = XMMatrixRotationX(m_rotation.x) * XMMatrixRotationY(m_rotation.y) * XMMatrixRotationZ(m_rotation.z);

    // update look/up/side
    XMFLOAT4X4 rotation;
    XMStoreFloat4x4(&rotation, R);

    // extract look from rotation matrix
    m_forward.x = rotation.m[2][0];
    m_forward.y = rotation.m[2][1];
    m_forward.z = rotation.m[2][2];

    // extract up from rotation matrix
    m_up.x = rotation.m[1][0];
    m_up.y = rotation.m[1][1];
    m_up.z = rotation.m[1][2];

    // calculate side
    XMStoreFloat3(&m_side, XMVector3Cross(XMLoadFloat3(&m_forward), XMLoadFloat3(&m_up)));
  }

  void NTransform::Start()
  {
  }

  void NTransform::Update(float a_deltaTime)
  {
    GetWorld();
  }

  bool NTransform::AddRequiredComponents(IComponentManager* a_componentManager)
  {
    // a_componentManager->AddComponent<...>();

    return true;
  }
}