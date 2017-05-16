#include "NDirectX11.h"

#include <D3Dcompiler.h>

#include "NDirectXHelper.h"
#include "NFile.h"
#include "NMemory.h"
#include "NShaderDirectX11.h"
#include "NMeshDirectX11.h"
#include "NWorldViewProjectionDirectX.h"
#include "NObjectManager.h"
#include "NCameraDirectX.h"
#include "NShaderManager.h"
#include "NMeshManager.h"
#include "NMeshRenderer.h"
#include "NTransform.h"
#include "NTextureDirectX11.h"
#include "NTextureManager.h"
#include "NTime.h"

namespace Nully
{
  NDirectX11::NDirectX11()
    : m_adapter(nullptr)
    , m_swapchain(nullptr)
    , m_device(nullptr)
    , m_deviceContext(nullptr)
    , m_renderTargetView(nullptr)
    , m_textureDepthBuffer(nullptr)
    , m_depthStencilState(nullptr)
    , m_depthStencilView(nullptr)
    , m_constantBuffer(nullptr)
    , m_blendState(nullptr)
    , m_rasterizerState(nullptr)
    , m_samplerState(nullptr)
  {
  }
  NDirectX11::~NDirectX11()
  {
    NSafeRelease(m_adapter);
    NSafeRelease(m_swapchain);
    NSafeRelease(m_device);
    NSafeRelease(m_deviceContext);
    NSafeRelease(m_renderTargetView);
    NSafeRelease(m_textureDepthBuffer);
    NSafeRelease(m_depthStencilState);
    NSafeRelease(m_depthStencilView);
    NSafeRelease(m_constantBuffer);
    NSafeRelease(m_blendState);
    NSafeRelease(m_rasterizerState);
    NSafeRelease(m_samplerState);
  }
  bool NDirectX11::Initialize(const NGraphicsDesc & a_graphicsDesc)
  {
    
    DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
    swapChainDesc.BufferDesc.Height = a_graphicsDesc.height;
    swapChainDesc.BufferDesc.Width = a_graphicsDesc.width;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;

    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 1;

    swapChainDesc.OutputWindow = a_graphicsDesc.hwnd; // HWND
    swapChainDesc.Windowed = TRUE;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapChainDesc.Flags = 0;

    if (NDirectXFailed(D3D11CreateDeviceAndSwapChain(m_adapter, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG, nullptr,
      0, D3D11_SDK_VERSION, &swapChainDesc, &m_swapchain, &m_device, nullptr, &m_deviceContext)))
    {
      return false;
    }

    // resize window
    this->OnResize(a_graphicsDesc.width, a_graphicsDesc.height);
    
    m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    //m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    // Alpha Blending
    D3D11_BLEND_DESC blendDesc = CD3D11_BLEND_DESC(CD3D11_DEFAULT());

    blendDesc.RenderTarget[0].BlendEnable = TRUE;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

    if (NDirectXFailed(m_device->CreateBlendState(&blendDesc, &m_blendState)))
    {
      return false;
    }


    m_deviceContext->OMSetBlendState(m_blendState, nullptr, 0xffffffff);


    this->CreateShaderBuffer();

    //
    // RasterizerState
    //
    D3D11_RASTERIZER_DESC rsDesc = {};
    rsDesc.FillMode = D3D11_FILL_SOLID;
    rsDesc.CullMode = D3D11_CULL_NONE;//D3D11_CULL_BACK;
    rsDesc.FrontCounterClockwise = false;
    rsDesc.DepthBias = 0;
    rsDesc.DepthBiasClamp = 0;
    rsDesc.SlopeScaledDepthBias = 0.0f;
    rsDesc.DepthClipEnable = false;
    rsDesc.ScissorEnable = false;
    rsDesc.AntialiasedLineEnable = false;
    rsDesc.MultisampleEnable = false;

    if (NDirectXFailed(m_device->CreateRasterizerState(&rsDesc, &m_rasterizerState)))
    {
      return false;
    }
    m_deviceContext->RSSetState(m_rasterizerState);

    //
    // SamplerState
    //
    D3D11_SAMPLER_DESC samplerDesc{};
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MipLODBias = 0.0f;
    samplerDesc.MaxAnisotropy = 1;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    samplerDesc.BorderColor[0] = 0;
    samplerDesc.BorderColor[1] = 0;
    samplerDesc.BorderColor[2] = 0;
    samplerDesc.BorderColor[3] = 0;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    if (NDirectXFailed(m_device->CreateSamplerState(&samplerDesc, &m_samplerState)))
    {
      return false;
    }

    m_deviceContext->PSSetSamplers(0, 1, &m_samplerState);
    m_deviceContext->VSSetSamplers(0, 1, &m_samplerState);

    return true;
  }
  void NDirectX11::Shutdown()
  {
  }
  void NDirectX11::Begin()
  {

  }
  void NDirectX11::End()
  {
    m_swapchain->Present(0, 0);
  }
  void NDirectX11::SetPrimitiveTopology(const NPrimitiveTopology a_primitiveTopology)
  {
    D3D_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    switch (a_primitiveTopology)
    {
    case NPrimitiveTopology::PointList:
      topology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
      break;

    case NPrimitiveTopology::TriangleList:
      topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
      break;

    case NPrimitiveTopology::TriangleStrip:
      topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
      break;

    case NPrimitiveTopology::LineList:
      topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
      break;

    case NPrimitiveTopology::LineStrip:
      topology = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
      break;

    default:
      topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
      break;
    }

    m_deviceContext->IASetPrimitiveTopology(topology);
  }
  void NDirectX11::Clear()
  {
    if (m_depthStencilView)
      m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    float color[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
    m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);
  }
  void NDirectX11::SetFillMode(const NFillMode a_fillMode)
  {
    D3D11_RASTERIZER_DESC rsDesc = {};
    m_rasterizerState->GetDesc(&rsDesc);

    switch (a_fillMode)
    {
    default:
    case NFillMode::Solid:
      rsDesc.FillMode = D3D11_FILL_SOLID;
      break;
    case NFillMode::Wireframe:
      rsDesc.FillMode = D3D11_FILL_WIREFRAME;
      break;
    }

    NSafeRelease(m_rasterizerState);

    if (NDirectXFailed(m_device->CreateRasterizerState(&rsDesc, &m_rasterizerState)))
    {
      return;
    }

    m_deviceContext->RSSetState(m_rasterizerState);
  }
  bool NDirectX11::OnResize(uint32_t a_width, uint32_t a_height)
  {
    // no render targets for now
    m_deviceContext->OMSetRenderTargets(0, 0, 0);

    // release old renderTargetView
    NSafeRelease(m_renderTargetView);

    // use old format and old buffercount
    if (NDirectXFailed(m_swapchain->ResizeBuffers(0, a_width, a_height, DXGI_FORMAT_UNKNOWN, 0)))
    {
      return false;
    }

    ID3D11Texture2D* backBuffer = nullptr;
    if (NDirectXFailed(m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer))))
    {
      return false;
    }

    // create new renderTargetView
    if (NDirectXFailed(m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView)))
    {
      return false;
    }

    NSafeRelease(backBuffer);

    // set viewport
    D3D11_VIEWPORT viewPort = { 0 };
    viewPort.Width = static_cast<FLOAT>(a_width);
    viewPort.Height = static_cast<FLOAT>(a_height);
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    m_deviceContext->RSSetViewports(1, &viewPort);


    //
    // Depth-Buffer
    //
    NSafeRelease(m_textureDepthBuffer);

    D3D11_TEXTURE2D_DESC textureDesc = { 0 };
    textureDesc.Width = a_width;
    textureDesc.Height = a_height;
    textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    textureDesc.MipLevels = 1;
    textureDesc.Format = DXGI_FORMAT_D32_FLOAT;//DXGI_FORMAT_D24_UNORM_S8_UINT;//DXGI_FORMAT_D32_FLOAT;
    textureDesc.Usage = D3D11_USAGE_DEFAULT;
    textureDesc.ArraySize = 1;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;

    if (NDirectXFailed(m_device->CreateTexture2D(&textureDesc, nullptr, &m_textureDepthBuffer)))
    {
      return false;
    }

    // Release and create new DepthStencil
    NSafeRelease(m_depthStencilState);
    NSafeRelease(m_depthStencilView);
    
    // depthStencilState
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc = CD3D11_DEPTH_STENCIL_DESC(CD3D11_DEFAULT());
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

    if (NDirectXFailed(m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState)))
    {
      return false;
    }

    // depthStencilView
    if (NDirectXFailed(m_device->CreateDepthStencilView(m_textureDepthBuffer, nullptr, &m_depthStencilView)))
    {
      return false;
    }

    // set depthStencilState
    this->m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

    // set render target
    m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	// inform camera about new resolution
	auto cameraObject = NObjectManager::GetInstance().GetCamera();

	if (cameraObject)
	{
		auto cameraComponent = dynamic_cast<ICamera*>(cameraObject->GetComponent<NCameraDirectX>());

		if (cameraComponent)
		{
			cameraComponent->OnResize(a_width, a_height);
		}
	}
	


    return true;
  }
  IShader* NDirectX11::LoadShader(const char * a_path)
  {
    if (m_device == nullptr)
    {
      return nullptr;
    }

    NFile file;
    if (file.Open(a_path, NFileMode::Read) != NResult::Success)
    {
      return nullptr;
    }

    auto size = file.GetFileSize(a_path);

    if (size == 0)
    {
      return nullptr;
    }

    NSmartArrayPtr<char> shaderBuffer = new char[size];

    file.Read(shaderBuffer.Get(), size);

    // VertexShader
    NComPtr<ID3D10Blob> vsError;
    NComPtr<ID3D10Blob> vsCode;

    // shaderBuffer.Get()
    if (NDirectXFailed(D3DCompile(shaderBuffer.Get(), size, nullptr, nullptr, nullptr, "VS_Main", "vs_5_0", 0, 0, &vsCode, &vsError)))
    {
      if (vsError.Get())
      {
        // print error
        std::cout << "Failed to load Shader: " << a_path << std::endl;
        std::cout << "With error: " << reinterpret_cast<char*>(vsError->GetBufferPointer()) << std::endl;
      }

      return nullptr;
    }

    // PixelShader
    NComPtr<ID3D10Blob> psError;
    NComPtr<ID3D10Blob> psCode;

    if (NDirectXFailed(D3DCompile(shaderBuffer.Get(), size, nullptr, nullptr, nullptr, "PS_Main", "ps_5_0", 0, 0, &psCode, &psError)))
    {
      if (psError.Get())
      {
        // print error
        std::cout << "Failed to load Shader: " << a_path << std::endl;
        std::cout << "With error: " << reinterpret_cast<char*>(vsError->GetBufferPointer()) << std::endl;
      }

      return nullptr;
    }

    // Create Vertex- & Pixelshader
    ID3D11VertexShader* vertexShader = nullptr;
    if (NDirectXFailed(m_device->CreateVertexShader(vsCode.Get()->GetBufferPointer(), vsCode.Get()->GetBufferSize(), nullptr, &vertexShader)))
    {
      return nullptr;
    }

    ID3D11PixelShader* pixelShader = nullptr;
    if (NDirectXFailed(m_device->CreatePixelShader(psCode.Get()->GetBufferPointer(), psCode.Get()->GetBufferSize(), nullptr, &pixelShader)))
    {
      return nullptr;
    }

    // create the input layout
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
      { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
      { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
      { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
      { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    ID3D11InputLayout* inputLayout = nullptr;
    if (NDirectXFailed(m_device->CreateInputLayout(ied, sizeof(ied) / sizeof(D3D11_INPUT_ELEMENT_DESC), vsCode->GetBufferPointer(), vsCode->GetBufferSize(), &inputLayout)))
    {
      return nullptr;
    }

    // everything worked fine ==> return the new created shader
    NShaderDirectX11* shader = new NShaderDirectX11();
    shader->SetPixelShader(pixelShader);
    shader->SetVertexShader(vertexShader);
    shader->SetInputLayout(inputLayout);

    return shader;
  }
  void NDirectX11::SetShader(IShader* a_shader)
  {
    if (!a_shader)
    {
      return;
    }

    NShaderDirectX11* shader = reinterpret_cast<NShaderDirectX11*>(a_shader);

    m_deviceContext->VSSetShader(shader->GetVertexShader(), 0, 0);
    m_deviceContext->PSSetShader(shader->GetPixelShader(), 0, 0);
    m_deviceContext->IASetInputLayout(shader->GetInputLayout());
  }
  IMesh* NDirectX11::LoadMesh(NObj& a_obj) const
  {
    return NMeshDirectX11::Load(m_device, a_obj);
  }
  void NDirectX11::SetMesh(IMesh* a_mesh) const
  {
    if (!a_mesh)
    {
      return;
    }

    NMeshDirectX11* mesh = reinterpret_cast<NMeshDirectX11*>(a_mesh);
    mesh->Set(m_deviceContext);
  }
  IMesh* NDirectX11::LoadTerrain(float a_width, float a_height, uint32_t a_sizeX, uint32_t a_sizeY)
  {
    return NMeshDirectX11::LoadTerrain(m_device, a_width, a_height, a_sizeX, a_sizeY);
  }
  void NDirectX11::SetTerrain(IMesh* a_terrain)
  {
    SetMesh(a_terrain);
  }
  void NDirectX11::DrawGameobject(IGameObject* a_gameObject)
  {
    if (!a_gameObject)
    {
      return;
    }
   
    //// Select the correct type for calling the equal_range function
    //decltype(objects.equal_range("")) range;

    //// iterate through multimap's elements (by key)
    //for (auto i = objects.begin(); i != objects.end(); i = range.second)
    //{
    //  // Get the range of the current key
    //  range = objects.equal_range(i->first);

    //  // Now print out that whole range
    //  for (auto d = range.first; d != range.second; ++d)
    //  {
    //    // create instance buffer from objects
    //    std::cout << d->first << '\n';
    //  }
    //}

    //return;

    //auto end = objects.end();
    //for (auto it = objects.begin(); it != end; it++)
    //{
    //  
    //}

    auto meshRenderer = a_gameObject->GetComponent<NMeshRenderer>();
    if (!meshRenderer)
    {
      // no meshRenderer component, object will not be drawn
      return;
    }
      
    auto shader = NShaderManager::GetInstance().GetShader(meshRenderer->GetShader());
    if (!shader)
    {
      return;
    }
    shader->Set(m_deviceContext);
      
    auto mesh = reinterpret_cast<NMeshDirectX11*>(NMeshManager::GetInstance().GetMesh(meshRenderer->GetMesh()));
    if (!mesh)
    {
      return;
    }
    mesh->Set(m_deviceContext);
    SetPrimitiveTopology(mesh->GetTopology());

    // obtain textures and set them to the shader
    auto textures = meshRenderer->GetTexture();
    uint32_t texIndex = 0;
    for (auto& element : textures)
    {
      auto texture = reinterpret_cast<NTextureDirectX11*>(NTextureManager::GetInstance().GetTexture(element));
      if (texture)
      {
        texture->Bind(m_deviceContext, texIndex);
      }
      texIndex++;
    }
      
    auto transform = a_gameObject->GetComponent<NTransform>();
    if (!transform)
    {
      return;
    }
      
    auto world = transform->GetWorld();
    this->UpdateWVP(world);
      
    // Draw call // TODO: sort by MESH => SHADER, to be able to draw instanced...
    if (mesh->m_indexBuffer.GetCount() > 0)
    {
      // draw indexed
      m_deviceContext->DrawIndexed(mesh->m_indexBuffer.GetCount(), 0, 0);
    }
    else
    {
      // draw normally
      m_deviceContext->Draw(mesh->m_vertexBuffer.GetVertexCount(), 0);
    }    
  }

  ITexture* NDirectX11::LoadTextureTGA(const char* a_file)
  {
    NTextureDirectX11* texture = new NTextureDirectX11();
    if (!texture->Load(a_file))
    {
      NSafeDelete(texture);
      return nullptr;
    }

    if (!texture->CreateTexture(m_device))
    {
      NSafeDelete(texture);
      return nullptr;
    }

    return texture;
  }
  void NDirectX11::SetTexture(ITexture* a_texture)
  {
    if (!a_texture)
    {
      return;
    }

    NTextureDirectX11* dxTexture = reinterpret_cast<NTextureDirectX11*>(a_texture);
    dxTexture->Bind(m_deviceContext);
  }
  bool NDirectX11::CreateShaderBuffer()
  {
    NWorldViewProjectionDirectX constBuffer = {};
    constBuffer.world = {};
    constBuffer.view = {};
    constBuffer.projection = {};
	constBuffer.totalTime = 0.0f;

    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.ByteWidth = (sizeof(NWorldViewProjectionDirectX) + 15) / 16 * 16;;
    bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    bufferDesc.MiscFlags = 0;
    bufferDesc.StructureByteStride = 0;
    bufferDesc.Usage = D3D11_USAGE_DYNAMIC;

    D3D11_SUBRESOURCE_DATA subData = {};
    subData.pSysMem = &bufferDesc;
    subData.SysMemPitch = 0;
    subData.SysMemSlicePitch = 0;

    if (NDirectXFailed(m_device->CreateBuffer(&bufferDesc, &subData, &m_constantBuffer)))
    {
      return false;
    }

    m_deviceContext->VSSetConstantBuffers(0, 1, &m_constantBuffer);

    return true;
  }
  void NDirectX11::UpdateWVP(const DirectX::XMFLOAT4X4& a_world)
  {
    // Update DynamicBuffer
    // map
    D3D11_MAPPED_SUBRESOURCE subresource = {};
    if (NDirectXFailed(m_deviceContext->Map(m_constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subresource)))
    {
      return;
    }

    auto camObj = NObjectManager::GetInstance().GetCamera();
    NCameraDirectX* componentCamera = nullptr;
    if (camObj)
    {
      componentCamera = camObj->GetComponent<NCameraDirectX>();
      componentCamera->GetProjection();
      componentCamera->GetView();
    }

    auto bufferPtr = reinterpret_cast<NWorldViewProjectionDirectX*>(subresource.pData);
    bufferPtr->view = componentCamera->GetView();
    bufferPtr->projection = componentCamera->GetProjection();
    bufferPtr->world = a_world;
	bufferPtr->totalTime = NTime::GetInstance().TotalTime();

    // unmap
    m_deviceContext->Unmap(m_constantBuffer, 0);
  }
}
