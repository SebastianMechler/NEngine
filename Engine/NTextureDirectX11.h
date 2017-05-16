#pragma once

#include <d3d11.h>

#include "ITexture.h"
#include "IGraphics.h"

namespace Nully
{
  class NTextureDirectX11 : public ITexture
  {
  public:
    // ITexture Interface
    bool Load(const char* a_path) override;
    uint32_t GetWidth() override;
    uint32_t GetHeight() override;
    uint8_t GetBitsPerPixel() override;

    NTextureDirectX11();
    ~NTextureDirectX11();

    bool CreateTexture(ID3D11Device* a_device);
    ID3D11Resource* GetTexture() const;
    void Bind(ID3D11DeviceContext* a_deviceContext, uint32_t a_slot = 0);

  private:
    uint32_t m_width;
    uint32_t m_height;
    uint8_t m_bitsPerPixel;
    void* m_data;

    ID3D11Texture2D* m_texture;
    ID3D11ShaderResourceView* m_resourceView;
  };
}
