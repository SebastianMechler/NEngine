#pragma once



#include "NWindow.h"
#include "NApplicationDesc.h"
#include "NInput.h"
#include "IGraphics.h"
#include "NRenderer.h"
#include "IScene.h"

#include <Windows.h>

namespace Nully
{
  class NApplication
  {
  public:
    NApplication();
    ~NApplication();
    bool Initialize(const NApplicationDesc& a_windowDesc, const NRenderer a_rendererType, IScene* a_scene);
    void Run();
    static LRESULT CALLBACK MessageHandling(HWND a_hwnd, UINT a_message, WPARAM a_wparam, LPARAM a_lparam);
    HWND GetWindowHandle() const;

    bool SetRenderer(const NRenderer a_renderer);
    void SetScene(IScene* a_scene);
    void OnResize();

    static NApplicationDesc m_applicationDesc;
  private:
    static bool m_quit;
    NWindow m_window;
    IGraphics* m_renderer;
    IScene* m_scene;
  };
}