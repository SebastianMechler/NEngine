#pragma once

#include "NComPtr.h"
#include "NSmartPtr.h"
#include "NSmartArrayPtr.h"

template<typename T> void NSafeRelease(T*& a_interface)
{
  if (a_interface != nullptr)
  {
    a_interface->Release();
    a_interface = nullptr;
  }
}

template<typename T> void NSafeDelete(T*& a_interface)
{
  if (a_interface != nullptr)
  {
    delete a_interface;
    a_interface = nullptr;
  }
}

template<typename T> void NSafeDeleteArray(T*& a_interface)
{
  if (a_interface != nullptr)
  {
    delete[] a_interface;
    a_interface = nullptr;
  }
}
