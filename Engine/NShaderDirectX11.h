#pragma once

#include <d3d11.h>

#include "IShader.h"

namespace Nully
{
  class NShaderDirectX11 : public IShader
  {
  public:
    // IShader Interface
    void Set(void* a_deviceContext) override;

    NShaderDirectX11();
    ~NShaderDirectX11();

    void SetVertexShader(ID3D11VertexShader* a_shader);
    void SetPixelShader(ID3D11PixelShader* a_shader);
    void SetInputLayout(ID3D11InputLayout* a_inputLayout);

    ID3D11VertexShader* GetVertexShader() const;
    ID3D11PixelShader* GetPixelShader() const;
    ID3D11InputLayout* GetInputLayout() const;

  private:
    ID3D11VertexShader* m_vertexShader;
    ID3D11PixelShader* m_pixelShader;
    ID3D11InputLayout* m_inputLayout;
  };
}