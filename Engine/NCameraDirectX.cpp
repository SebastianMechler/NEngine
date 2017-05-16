#include "NCameraDirectX.h"

using namespace DirectX;

namespace Nully
{
  bool NCameraDirectX::Initialize(const NCameraDesc& a_cameraDesc)
  {
    assert(m_componentMgr);

    auto transform = m_componentMgr->GetComponent<NTransform>();
    assert(transform);

    m_camerDesc = a_cameraDesc;

    m_target = XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_up = XMFLOAT3(0.0f, 1.0f, 0.0f);

    // init view matrix
    auto matLookAt = XMMatrixLookAtLH(XMLoadFloat3(&transform->GetPosition()), XMLoadFloat3(&m_target), XMLoadFloat3(&m_up));
    XMStoreFloat4x4(&m_view, XMMatrixTranspose(matLookAt));

    // init projection matrix
	this->OnResize(a_cameraDesc.screenWidth, a_cameraDesc.screenHeight);

    return true;
  }
  void NCameraDirectX::OnResize(uint32_t a_width, uint32_t a_height)
  {
	  m_camerDesc.screenWidth = a_width;
	  m_camerDesc.screenHeight = a_height;

	  auto proj = XMMatrixTranspose
	  (
		  XMMatrixPerspectiveFovLH
		  (
			  m_camerDesc.fieldOfView,
			  static_cast<float>(m_camerDesc.screenWidth) / static_cast<float>(m_camerDesc.screenHeight),
			  m_camerDesc.nearPlane,
			  m_camerDesc.farPlane
		  )
	  );

	  DirectX::XMStoreFloat4x4(&m_proj, proj);
  }
  DirectX::XMFLOAT4X4& NCameraDirectX::GetView()
  {
    return m_view;
  }
  DirectX::XMFLOAT4X4& NCameraDirectX::GetProjection()
  {
    return m_proj;
  }
  void NCameraDirectX::Start()
  {
    NCameraDesc camDesc{};
    camDesc.screenWidth = NApplication::m_applicationDesc.windowDesc.width;
    camDesc.screenHeight = NApplication::m_applicationDesc.windowDesc.height;
    camDesc.farPlane = 100.0f;
    camDesc.nearPlane = 0.01f;
    camDesc.fieldOfView = 3.1415f * 0.35f;

    this->Initialize(camDesc);
  }
  void NCameraDirectX::Update(float a_deltaTime)
  {
    auto transform = m_componentMgr->GetComponent<NTransform>();

    auto position = transform->GetPosition(); // back
    auto forward = transform->GetForward();

    m_target.x = position.x + forward.x * 10.0f;
    m_target.y = position.y + forward.y * 10.0f;
    m_target.z = position.z + forward.z * 10.0f;

    auto matLookAt = XMMatrixLookAtLH(XMLoadFloat3(&transform->GetPosition()), XMLoadFloat3(&m_target), XMLoadFloat3(&m_up));
    XMStoreFloat4x4(&m_view, XMMatrixTranspose(matLookAt));
  }
  bool NCameraDirectX::AddRequiredComponents(IComponentManager* a_componentManager)
  {
    // access to other components is required, store component mgr
    m_componentMgr = a_componentManager;

    return true;
  }
  NCameraDirectX::NCameraDirectX()
    : m_componentMgr(nullptr)
    , m_camerDesc()
  {
  }
  NCameraDirectX::~NCameraDirectX()
  {
  }
}

