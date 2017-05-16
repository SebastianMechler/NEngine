#pragma once

#include "ICamera.h"
#include "IComponent.h"
#include "NApplication.h"
#include "NTransform.h"

#include <DirectXMath.h>

namespace Nully
{
  class NCameraDirectX : public IComponent, public ICamera
  {
  public:
    // ICamera Interface
    bool Initialize(const NCameraDesc& a_cameraDesc) override;
	void OnResize(uint32_t a_width, uint32_t a_height) override;
    DirectX::XMFLOAT4X4& GetView() override;
    DirectX::XMFLOAT4X4& GetProjection() override;

    // IComponent Interface
    void Start() override;
    void Update(float a_deltaTime) override;
    bool AddRequiredComponents(IComponentManager* a_componentManager) override;

    NCameraDirectX();
    ~NCameraDirectX();

  private:
    IComponentManager* m_componentMgr;
    DirectX::XMFLOAT4X4 m_view;
    DirectX::XMFLOAT4X4 m_proj;

    DirectX::XMFLOAT3 m_target;
    DirectX::XMFLOAT3 m_up;

    NCameraDesc m_camerDesc;
  };
}