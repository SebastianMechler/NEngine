#include "NApplication.h"

#include <iostream>

#include "NTools.h"
#include "NDirectX11.h"

// Managers
#include "NShaderManager.h"
#include "NMeshManager.h"
#include "NObjectManager.h"
#include "NTextureManager.h"

#include "NGlobalData.h"
#include "NFrameTimer.h"
#include "NTime.h"

namespace Nully
{
  NApplication::NApplication()
    : m_renderer(nullptr)
    , m_scene(nullptr)
  {
  }

  NApplication::~NApplication()
  {
    if (m_renderer)
    {
      m_renderer->Shutdown();
      delete m_renderer;
      m_renderer = nullptr;
    }

    NShaderManager::GetInstance().Shutdown();
    NMeshManager::GetInstance().Shutdown();
    NObjectManager::GetInstance().Shutdown();
    NTextureManager::GetInstance().Shutdown();

    if (m_scene)
    {
      m_scene->Shutdown();
    }
  }

  bool NApplication::Initialize(const NApplicationDesc& a_applicationDesc, const NRenderer a_rendererType, IScene* a_scene)
  {
    // initialize window
    if (!m_window.Initialize(a_applicationDesc.windowDesc, NApplication::MessageHandling, this))
    {
      return false;
    }

    // set hwnd to graphicsDesc
    m_applicationDesc = a_applicationDesc;
    m_applicationDesc.graphicsDesc.hwnd = m_window.GetWindowHandle();

    if (!SetRenderer(a_rendererType))
    {
      return false;
    }

    // Load shaders
    NShaderManager::GetInstance().Load(m_renderer, NPATH_SHADER_DEFAULT);
    NShaderManager::GetInstance().Load(m_renderer, NPATH_SHADER_TERRAIN);
	NShaderManager::GetInstance().Load(m_renderer, NPATH_SHADER_WATER);

    // Load Primitives
    NMeshManager& meshManager = NMeshManager::GetInstance();
    meshManager.Load(m_renderer, NPATH_MESH_CUBE);
    meshManager.Load(m_renderer, NPATH_MESH_CONE);
    meshManager.Load(m_renderer, NPATH_MESH_IKOSADER);
    meshManager.Load(m_renderer, NPATH_MESH_PLANE);
    meshManager.Load(m_renderer, NPATH_MESH_SPHERE);
    meshManager.Load(m_renderer, NPATH_MESH_TORUS);

    // create terrain
    meshManager.CreateTerrain(m_renderer, NTERRAIN_NAME_DEFAULT, 80.0f, 80.0f, 64, 64);

	// create water plane
	meshManager.CreateTerrain(m_renderer, NWATER_NAME_DEFAULT, 80.0f, 80.0f, 128, 128);

    // load textures
    NTextureManager::GetInstance().Load(m_renderer, NPATH_TEXTURE_DEFAULT);
    NTextureManager::GetInstance().Load(m_renderer, NPATH_TEXTURE_DEFAULT1);
    NTextureManager::GetInstance().Load(m_renderer, NPATH_TEXTURE_DEFAULT2);
    NTextureManager::GetInstance().Load(m_renderer, NPATH_TEXTURE_TERRAIN);
    NTextureManager::GetInstance().Load(m_renderer, NPATH_TEXTURE_TERRAIN_HEIGHTMAP);
	NTextureManager::GetInstance().Load(m_renderer, NPATH_TEXTURE_WATER);
    
    // Set scene
    SetScene(a_scene);

    return true;
  }
  void NApplication::Run()
  {
    MSG message = {};

	NFrameTimer frameTimer;
	frameTimer.Initialize(120); // set frame cap

    while (m_quit != true)
    {
      while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
      {
        TranslateMessage(&message);
        DispatchMessage(&message);
      }

      // Update
      NInput::GetInstance().Update();
      m_scene->Update(NTime::GetInstance().DeltaTime());

      // Draw
      m_renderer->Begin();
      m_renderer->Clear();

      m_scene->Draw(m_renderer);

      m_renderer->End();

	  // Frame-Timer which is responsible for deltaTime
	  frameTimer.Update();
    }
  }
  LRESULT NApplication::MessageHandling(HWND a_hwnd, UINT a_message, WPARAM a_wparam, LPARAM a_lparam)
  {
    NApplication* application = reinterpret_cast<NApplication*>(GetWindowLongPtr(a_hwnd, 0));

    switch (a_message)
    {
    case WM_DESTROY:
    case WM_QUIT:
    case WM_CLOSE:
      PostQuitMessage(0);
      NApplication::m_quit = true;
      break;

    case WM_MOUSEMOVE:
      //NInput::GetInstance().SetMousePositon(GET_X_LPARAM(a_lparam), GET_Y_LPARAM(a_lparam));
      break;

    case WM_NCCREATE:
      SetWindowLongPtr(a_hwnd, 0, reinterpret_cast<LONG_PTR>((reinterpret_cast<CREATESTRUCT*>(a_lparam))->lpCreateParams));
      break;

    case WM_KEYDOWN:
      if (!NTools::IsBitSet(a_lparam, 31)) // Bit 31	The previous key state. The value is 1 if the key is down before the message is sent, or it is zero if the key is up.
      {
        NInput::GetInstance().SetKeyDown(static_cast<NKey>(a_wparam));
        std::cout << "DOWN" << std::endl;
      }
      break;


    case WM_KEYUP:
      if (NTools::IsBitSet(a_lparam, 31)) // bit 31 is set if it is repeating message
      {
        NInput::GetInstance().SetKeyUp(static_cast<NKey>(a_wparam));
        std::cout << "UP" << std::endl;
      }
      break;
   
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
      //NInput::GetInstance().SetMouseButtonState(a_message);
      break;

    case WM_SIZE:
    {
      if (application)
      {
        application->OnResize();
      }
    }
      break;

    }


    return DefWindowProc(a_hwnd, a_message, a_wparam, a_lparam);
  }

  HWND NApplication::GetWindowHandle() const
  {
    return m_window.GetWindowHandle();
  }

  bool NApplication::SetRenderer(const NRenderer a_renderer)
  {
    if (m_renderer)
    {
      m_renderer->Shutdown();
      delete m_renderer;
      m_renderer = nullptr;
    }

    switch (a_renderer)
    {
      case NRenderer::DirectX11:
        m_renderer = new NDirectX11();
        if (!m_renderer->Initialize(m_applicationDesc.graphicsDesc))
        {
          // ERROR....
          return false;
        }
        break;
    }

    return true;
  }

  void NApplication::SetScene(IScene * a_scene)
  {
    if (m_scene)
    {
      m_scene->Shutdown();
    }

    m_scene = a_scene;
    m_scene->Initialize();
  }

  void NApplication::OnResize()
  {
    RECT r{};
    GetClientRect(this->GetWindowHandle(), &r);
    
    auto windowDesc = m_window.GetWindowDesc();
    windowDesc.width = r.right;
    windowDesc.height = r.bottom;

    if (m_renderer)
    {
      m_renderer->OnResize(windowDesc.width, windowDesc.height);
    }

    // Update all cameras
    // ObjectMgr->UpdateMainCamera(windowDesc.width, windowDesc.height);
  }

  bool NApplication::m_quit = false;
  NApplicationDesc NApplication::m_applicationDesc {};
}

