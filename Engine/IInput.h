#pragma once

#include "NKey.h"

namespace Nully
{
  class IInput
  {
  public:
    virtual bool Initialize() = 0;
    virtual void Shutdown() = 0;

    virtual void SetKeyUp(const NKey a_key) = 0;
    virtual void SetKeyDown(const NKey a_key) = 0;

    virtual bool GetKeyDown(const NKey a_key) = 0;
    virtual bool GetKeyUp(const NKey a_key) = 0;
    virtual bool GetKey(const NKey a_key) = 0;
    
    virtual void Update() = 0;

    virtual ~IInput() {};
  };
}
