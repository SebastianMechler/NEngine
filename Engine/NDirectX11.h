#pragma once

#include <D3D11.h>
#include <DirectXMath.h>

#include "IGraphics.h"

namespace Nully
{
  class NDirectX11 : public IGraphics
  {
  public:
    NDirectX11();
    ~NDirectX11();

    // IGraphics Interface
    bool Initialize(const NGraphicsDesc& a_graphicsDesc) override;
    void Shutdown() override;
    void Begin() override;
    void End() override;
    void SetPrimitiveTopology(const NPrimitiveTopology a_primitiveTopology) override;
    void Clear() override;
    void SetFillMode(const NFillMode a_fillMode) override;
    bool OnResize(uint32_t a_width, uint32_t a_height) override;
    IShader* LoadShader(const char* a_path) override;
    void SetShader(IShader* a_shader) override;
    IMesh* LoadMesh(NObj& a_obj) const override;
    void SetMesh(IMesh* a_mesh) const override;
    IMesh* LoadTerrain(float a_width, float a_height, uint32_t a_sizeX, uint32_t a_sizeY) override;
    void SetTerrain(IMesh* a_terrain) override;
    ITexture* LoadTextureTGA(const char* a_file) override;
    void SetTexture(ITexture* a_texture) override;
    void DrawGameobject(IGameObject* a_gameObject) override;


	

  private:
	// Custom Methods
	bool CreateShaderBuffer();
	void UpdateWVP(const DirectX::XMFLOAT4X4& a_world);
	void DebugDrawCollider(IGameObject* a_gameObject);

    IDXGIAdapter* m_adapter;
    IDXGISwapChain* m_swapchain;
    ID3D11Device* m_device;
    ID3D11DeviceContext* m_deviceContext;
    ID3D11RenderTargetView* m_renderTargetView;
    ID3D11Texture2D* m_textureDepthBuffer;
    ID3D11DepthStencilState* m_depthStencilState;
    ID3D11DepthStencilView* m_depthStencilView;
    ID3D11Buffer* m_constantBuffer;
    ID3D11BlendState* m_blendState;
    ID3D11RasterizerState* m_rasterizerState;
    ID3D11SamplerState* m_samplerState;
  };
}