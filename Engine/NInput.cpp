#include "NInput.h"

namespace Nully
{
  bool NInput::Initialize()
  {
    return true;
  }
  void NInput::Shutdown()
  {

  }
  void NInput::SetKeyUp(const NKey a_key)
  {
    m_keyMap[a_key] = NKeyState::Up;
    m_keyPressedMap[a_key] = false;
  }
  void NInput::SetKeyDown(const NKey a_key)
  {
    m_keyMap[a_key] = NKeyState::Down;
    m_keyPressedMap[a_key] = true;
  }
  bool NInput::GetKeyDown(const NKey a_key)
  {
    return (m_keyMap[a_key] == NKeyState::Down);
  }
  bool NInput::GetKeyUp(const NKey a_key)
  {
    return (m_keyMap[a_key] == NKeyState::Up);
  }
  bool NInput::GetKey(const NKey a_key)
  {
    return m_keyPressedMap[a_key];
  }
  void NInput::Update()
  {
    for (auto& e : m_keyMap)
    {
      e.second = NKeyState::None;
    }
  }
  
  NInput::NInput()
  {

  }

  NInput& NInput::GetInstance()
  {
    static NInput g_input;
    return g_input;
  }
}
