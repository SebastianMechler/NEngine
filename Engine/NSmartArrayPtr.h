#pragma once

namespace Nully
{
  template <typename T>
  class NSmartArrayPtr
  {
  public:
    NSmartArrayPtr();
    NSmartArrayPtr(T* a_ptr);
    ~NSmartArrayPtr();

    T* Get() const;

    T& operator*() const;
    T* operator->() const;
    T** operator&();
    
  private:
    T* m_ptr;
  };



  template<typename T>
  inline NSmartArrayPtr<T>::NSmartArrayPtr()
    : m_ptr(nullptr)
  {
  }

  template<typename T>
  inline NSmartArrayPtr<T>::NSmartArrayPtr(T* a_ptr)
    : m_ptr(a_ptr)
  {
  }

  template<typename T>
  inline NSmartArrayPtr<T>::~NSmartArrayPtr()
  {
    if (m_ptr)
    {
      delete[] m_ptr;
      m_ptr = nullptr;
    }
  }

  template<typename T>
  inline T* NSmartArrayPtr<T>::Get() const
  {
    return m_ptr;
  }

  template<typename T>
  inline T& NSmartArrayPtr<T>::operator*() const
  {
    return m_ptr;
  }

  template<typename T>
  inline T* NSmartArrayPtr<T>::operator->() const
  {
    return m_ptr;
  }

  template<typename T>
  inline T** NSmartArrayPtr<T>::operator&()
  {
    return &m_ptr;
  }

}
