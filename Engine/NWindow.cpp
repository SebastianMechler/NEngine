#include "NWindow.h"

namespace Nully
{
  bool NWindow::Initialize(const NWindowDesc& a_windowDesc, const WNDPROC& a_wndProc, void* a_application)
  {
    this->m_windowDesc = a_windowDesc;

    WNDCLASS wndClass = {};

    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // load cursor 
    wndClass.hIcon = LoadIcon(NULL, IDI_INFORMATION); // load icon 
    wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH)); // background color 
    wndClass.lpfnWndProc = a_wndProc; // message handler 
    wndClass.lpszClassName = a_windowDesc.className; // window class name 
    wndClass.lpszMenuName = NULL; // no menu 
    wndClass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW; // window behaviour 
    wndClass.cbWndExtra = sizeof(a_application);


    if (FAILED(RegisterClass(&wndClass)))
    {
      return false;
    }

    const int windowStyle = WS_OVERLAPPEDWINDOW;//WS_OVERLAPPEDWINDOW;// WS_CAPTION | WS_SYSMENU |  WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

    int screenX = GetSystemMetrics(SM_CXSCREEN);
    int screenY = GetSystemMetrics(SM_CYSCREEN);

    RECT windowRect = { 0, 0, 0, 0 };

    if (a_windowDesc.isFullScreen)
    {
      windowRect.left = 0;
      windowRect.right = 0;
      windowRect.right = screenX;
      windowRect.bottom = screenY;
    }
    else
    {
      windowRect.right = a_windowDesc.width;
      windowRect.bottom = a_windowDesc.height;

      AdjustWindowRect(&windowRect, windowStyle, false);

      //windowRect.right = a_windowDescription.width - windowRect.left;
      //windowRect.bottom = a_windowDescription.height - windowRect.top;

      /*
      switch (a_windowDescription.windowAlignment)
      {
      case EWindowAlignment::TopLeft:
      windowRect.left = 0;
      windowRect.top = 0;
      break;

      case EWindowAlignment::TopRight:
      windowRect.left = screenX - windowRect.right;
      windowRect.top = 0;
      break;

      case EWindowAlignment::BottomLeft:
      windowRect.left = 0;
      windowRect.top = screenY - windowRect.bottom;
      break;

      case EWindowAlignment::BottomRight:
      windowRect.left = screenX - windowRect.right;
      windowRect.top = screenY - windowRect.bottom;
      break;

      case EWindowAlignment::Top:
      windowRect.left = screenX / 2 - windowRect.right / 2;
      windowRect.top = 0;
      break;

      case EWindowAlignment::Bottom:
      windowRect.left = screenX / 2 - windowRect.right / 2;
      windowRect.top = screenY - windowRect.bottom;
      break;

      case EWindowAlignment::Left:
      windowRect.left = 0;
      windowRect.top = screenY / 2 - windowRect.bottom / 2;
      break;

      case EWindowAlignment::Right:
      windowRect.left = screenX - windowRect.right;
      windowRect.top = screenY / 2 - windowRect.bottom / 2;
      break;

      case EWindowAlignment::Center:
      windowRect.left = screenX / 2 - windowRect.right / 2;
      windowRect.top = screenY / 2 - windowRect.bottom / 2;
      break;

      default:
      break;
      }
      */
    }

    //m_hwnd = CreateWindow(a_windowDesc.className, a_windowDesc.name, windowStyle, 0, 0, windowRect.right + abs(windowRect.left), windowRect.bottom + abs(windowRect.top), nullptr, nullptr, GetModuleHandle(NULL), nullptr);
    m_hwnd = CreateWindowEx(0, a_windowDesc.className, a_windowDesc.name, windowStyle, 0, 0, windowRect.right + abs(windowRect.left), windowRect.bottom + abs(windowRect.top), nullptr, nullptr, GetModuleHandle(NULL), a_application);
    if (m_hwnd != NULL)
    {
      SetFocus(m_hwnd);
      SetForegroundWindow(m_hwnd);
      ShowWindow(m_hwnd, SW_SHOW);

      return true;
    }


    return false;
  }

  HWND NWindow::GetWindowHandle() const
  {
    return this->m_hwnd;
  }

  NWindowDesc& NWindow::GetWindowDesc()
  {
    return this->m_windowDesc;
  }
}
