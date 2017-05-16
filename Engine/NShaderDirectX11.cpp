#include "NShaderDirectX11.h"

#include "NMemory.h"

namespace Nully
{
  void NShaderDirectX11::Set(void* a_deviceContext)
  {
    if (!a_deviceContext)
    {
      return;
    }

    auto deviceContext = reinterpret_cast<ID3D11DeviceContext*>(a_deviceContext);

    deviceContext->VSSetShader(m_vertexShader, 0, 0);
    deviceContext->PSSetShader(m_pixelShader, 0, 0);
    deviceContext->IASetInputLayout(m_inputLayout);
  }
  NShaderDirectX11::NShaderDirectX11()
    : m_vertexShader(nullptr)
    , m_pixelShader(nullptr)
    , m_inputLayout(nullptr)
  {
  }
  NShaderDirectX11::~NShaderDirectX11()
  {
    NSafeRelease(m_pixelShader);
    NSafeRelease(m_vertexShader);
    NSafeRelease(m_inputLayout);
  }
  void NShaderDirectX11::SetVertexShader(ID3D11VertexShader* a_shader)
  {
    if (!m_vertexShader)
    {
      m_vertexShader = a_shader;
    }
  }
  void NShaderDirectX11::SetPixelShader(ID3D11PixelShader* a_shader)
  {
    if (!m_pixelShader)
    {
      m_pixelShader = a_shader;
    }
  }
  void NShaderDirectX11::SetInputLayout(ID3D11InputLayout* a_inputLayout)
  {
    if (!m_inputLayout)
      m_inputLayout = a_inputLayout;
  }
  ID3D11VertexShader* NShaderDirectX11::GetVertexShader() const
  {
    return m_vertexShader;
  }
  ID3D11PixelShader* NShaderDirectX11::GetPixelShader() const
  {
    return m_pixelShader;
  }
  ID3D11InputLayout* NShaderDirectX11::GetInputLayout() const
  {
    return m_inputLayout;
  }
}
