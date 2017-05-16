#pragma once

#include <Windows.h>

#include "NWindowDesc.h"

namespace Nully
{
  class NWindow
  {
  public:
    bool Initialize(const NWindowDesc& a_windowDesc, const WNDPROC& a_wndProc, void* a_application);
    HWND GetWindowHandle() const;
    NWindowDesc& GetWindowDesc();
   
  private:
    HWND m_hwnd;
    NWindowDesc m_windowDesc;
  };
}