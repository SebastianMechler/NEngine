#include "NTextureDirectX11.h"

#include "NImageLoader.h"
#include "NMemory.h"
#include "NDirectXHelper.h"

namespace Nully
{
  bool NTextureDirectX11::Load(const char* a_path)
  {
    NImageData imgData{};
    if (!NImageLoader::LoadTGA(a_path, imgData))
    {
      return false;
    }
   
    // image loaded succesfully
    m_width = imgData.width;
    m_height = imgData.height;
    m_bitsPerPixel = imgData.bitsPerPixel;
    m_data = imgData.data;

    return true;
  }
  uint32_t NTextureDirectX11::GetWidth()
  {
    return m_width;
  }
  uint32_t NTextureDirectX11::GetHeight()
  {
    return m_height;
  }
  uint8_t NTextureDirectX11::GetBitsPerPixel()
  {
    return m_bitsPerPixel;
  }
  NTextureDirectX11::NTextureDirectX11()
    : m_width(0)
    , m_height(0)
    , m_bitsPerPixel(0)
    , m_data(nullptr)
    , m_texture(nullptr)
    , m_resourceView(nullptr)
  {
  }
  NTextureDirectX11::~NTextureDirectX11()
  {
    NSafeDeleteArray(m_data);
    NSafeRelease(m_texture);
    NSafeRelease(m_resourceView);
  }
  bool NTextureDirectX11::CreateTexture(ID3D11Device * a_device)
  {
    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = m_width;
    desc.Height = m_height;
    desc.MipLevels = desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;//D3D11_USAGE_DYNAMIC;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;//D3D11_CPU_ACCESS_WRITE;
    desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA textureData = {};
    textureData.pSysMem = m_data;
    textureData.SysMemPitch = m_width * 4;

    HRESULT hr = a_device->CreateTexture2D(&desc, &textureData, &m_texture);
    if (NDirectXFailed(hr))
    {
      return false;
    }

    // create ShaderResourceView
    hr = a_device->CreateShaderResourceView(m_texture, nullptr, &m_resourceView);
    if (NDirectXFailed(hr))
    {
      return false;
    }

    return true;
  }
  ID3D11Resource* NTextureDirectX11::GetTexture() const
  {
    return m_texture;
  }
  void NTextureDirectX11::Bind(ID3D11DeviceContext* a_deviceContext, uint32_t a_slot)
  {
    if (!a_deviceContext)
    {
      return;
    }

    a_deviceContext->PSSetShaderResources(a_slot, 1, &m_resourceView);
    a_deviceContext->VSSetShaderResources(a_slot, 1, &m_resourceView);
  }
}
