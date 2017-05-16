#pragma once

namespace Nully
{
  template <typename T>
  class NComPtr
  {
  public:
    NComPtr();
    NComPtr(T* a_ptr);
    ~NComPtr();

    T* Get() const;

    T& operator*() const;
    T* operator->() const;
    T** operator&();

  private:
    T* m_ptr;
  };

  
  

  template<typename T>
  NComPtr<T>::NComPtr()
    : m_ptr(nullptr)
  {
  }

  template<typename T>
  NComPtr<T>::NComPtr(T* a_ptr)
    : m_ptr(a_ptr)
  {

  }

  template<typename T>
  NComPtr<T>::~NComPtr()
  {
    if (m_ptr)
    {
      m_ptr->Release();
      m_ptr = nullptr;
    }
  }

  template<typename T>
  T* NComPtr<T>::Get() const
  {
    return m_ptr;
  }

  template<typename T>
  T& NComPtr<T>::operator*() const
  {
    return m_ptr;
  }

  template<typename T>
  T* NComPtr<T>::operator->() const
  {
    return m_ptr;
  }

  template<typename T>
  T** NComPtr<T>::operator&()
  {
    return &m_ptr;
  }
}