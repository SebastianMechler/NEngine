#pragma once

namespace Nully
{
  template <typename T>
  class NSmartPtr
  {
  public:
    NSmartPtr();
    NSmartPtr(T* a_ptr);
    ~NSmartPtr();

    T* Get() const;

    T& operator*() const;
    T* operator->() const;
    T** operator&();

  private:
    T* m_ptr;
  };



  template<typename T>
  inline NSmartPtr<T>::NSmartPtr()
    : m_ptr(nullptr)
  {
  }

  template<typename T>
  inline NSmartPtr<T>::NSmartPtr(T* a_ptr)
    : m_ptr(a_ptr)
  {
  }

  template<typename T>
  inline NSmartPtr<T>::~NSmartPtr()
  {
    if (m_ptr)
    {
      delete m_ptr;
      m_ptr = nullptr;
    }
  }

  template<typename T>
  inline T* NSmartPtr<T>::Get() const
  {
    return m_ptr;
  }

  template<typename T>
  inline T& NSmartPtr<T>::operator*() const
  {
    return *m_ptr;
  }

  template<typename T>
  inline T* NSmartPtr<T>::operator->() const
  {
    return *m_ptr;
  }

  template<typename T>
  inline T** NSmartPtr<T>::operator&()
  {
    return &m_ptr;
  }

}
