#pragma once

#include <unordered_map>

#include "IInput.h"
#include "NKeyState.h"


namespace Nully
{
  class NInput : public IInput
  {
  public:
    bool Initialize() override;
    void Shutdown() override;

    void SetKeyUp(const NKey a_key) override;
    void SetKeyDown(const NKey a_key) override;

    bool GetKeyDown(const NKey a_key) override;
    bool GetKeyUp(const NKey a_key) override;
    bool GetKey(const NKey a_key) override;

    void Update() override;

    static NInput& GetInstance();

  private:
    NInput();
    NInput(const NInput&) = delete;

    std::unordered_map<NKey, NKeyState> m_keyMap; // true = down, false = up
    std::unordered_map<NKey, bool> m_keyPressedMap; // down = true, up = false
  };
}
