#ifndef CATCGMClonePtr_H
#define CATCGMClonePtr_H

#if !defined(_AIX_SOURCE)
#define CATCGMCLONEPTR_CPP11
#endif

#ifdef CATCGMCLONEPTR_CPP11
#define CATCGMCLONEPTR_NOEXCEPT noexcept

#include <utility>
#else
#define CATCGMCLONEPTR_NOEXCEPT
#endif

// Utility class similar to std::unique_ptr except than copy and assignment are implement through pointed type copy and assignment
// Basic use :
// {
//   CATCGMClonePtr<Foo> pFoo(new Foo());
//   pFoo->BigComputation();
// } // pFoo goes out of scope, destructor is automatically called

// Class member :
// class Foo
// {
//   SetBar(CATCGMClonePtr<Bar> ipBar) { _pBar = ipBar; } // Automatically create a new bar which is copied from ipBar
//   ~Foo();                                              // Destructor automatically called on _pBar
//  
//   CATCGMClonePtr<Bar> _pBar;
// };

// CATCGMClonePtr can also be used within a container class like std::vector
// Method(CATCGMClonePtr<Foo> ipFoo1)
// {
//   std::vector<CATCGMClonePtr<Foo>> myVector(1);
//   myVector[0] = ipFoo; // A copy is done from the element pointed by ipFoo
// } // The vector is destroyed : the container is cleared so a destructor is called on each of its elements.

template<class T>
class CATCGMClonePtr
{
public:
  explicit CATCGMClonePtr(T* iPtr);
  CATCGMClonePtr(CATCGMClonePtr const& iPtr);
  CATCGMClonePtr& operator=(CATCGMClonePtr const& iPtr);
  ~CATCGMClonePtr();

#if defined(CATCGMCLONEPTR_CPP11)
  CATCGMClonePtr() noexcept = default;

  CATCGMClonePtr(CATCGMClonePtr&& iPtr) noexcept;
  CATCGMClonePtr& operator=(CATCGMClonePtr&& iPtr) noexcept;

  CATCGMClonePtr(std::nullptr_t) noexcept;
  CATCGMClonePtr& operator=(std::nullptr_t);
#else
  CATCGMClonePtr();
#endif

  bool operator == (CATCGMClonePtr const& iPtr) const CATCGMCLONEPTR_NOEXCEPT;
  bool operator != (CATCGMClonePtr const& iPtr) const CATCGMCLONEPTR_NOEXCEPT;
  bool operator <  (CATCGMClonePtr const& iPtr) const CATCGMCLONEPTR_NOEXCEPT;
  bool operator <= (CATCGMClonePtr const& iPtr) const CATCGMCLONEPTR_NOEXCEPT;
  bool operator >  (CATCGMClonePtr const& iPtr) const CATCGMCLONEPTR_NOEXCEPT;
  bool operator >= (CATCGMClonePtr const& iPtr) const CATCGMCLONEPTR_NOEXCEPT;

#if defined(CATCGMCLONEPTR_CPP11)
  bool operator == (std::nullptr_t) const noexcept;
  bool operator != (std::nullptr_t) const noexcept;
#endif

  T& operator*() const CATCGMCLONEPTR_NOEXCEPT;
  T* operator->() const CATCGMCLONEPTR_NOEXCEPT;

  T* get() const CATCGMCLONEPTR_NOEXCEPT;

  T* release() CATCGMCLONEPTR_NOEXCEPT;

#if defined(CATCGMCLONEPTR_CPP11)
  explicit operator bool() const noexcept;
#else
  operator bool() const;
#endif

private:
#if defined(CATCGMCLONEPTR_CPP11)
  T* _ptr = nullptr;
#else
  T* _ptr;
#endif
};

template<class T>
CATCGMClonePtr<T>::CATCGMClonePtr(T* iPtr) 
  : _ptr(iPtr)
{
}

template<class T>
CATCGMClonePtr<T>::CATCGMClonePtr(CATCGMClonePtr const& iPtr)
  : _ptr(iPtr._ptr ? new T(*iPtr._ptr) : nullptr)
{
}

template<class T>
CATCGMClonePtr<T>& CATCGMClonePtr<T>::operator=(CATCGMClonePtr const& iPtr)
{
  if (_ptr != iPtr._ptr)
  {
    if (iPtr._ptr)
    {
      if (_ptr)
      {
        *_ptr = *iPtr._ptr;
      }
      else
      {
        _ptr = new T(*iPtr._ptr);
      }
    }
    else
    {
      delete _ptr;
      _ptr = nullptr;
    }
  }
  return *this;
}

template<class T>
CATCGMClonePtr<T>::~CATCGMClonePtr()
{
  delete _ptr;
}

#if defined(CATCGMCLONEPTR_CPP11)
template<class T>
CATCGMClonePtr<T>::CATCGMClonePtr(CATCGMClonePtr&& iPtr) noexcept
  : _ptr(iPtr._ptr)
{
  iPtr._ptr = nullptr;
}

template<class T>
CATCGMClonePtr<T>& CATCGMClonePtr<T>::operator=(CATCGMClonePtr&& iPtr) noexcept
{
  std::swap(_ptr, iPtr._ptr);
  return *this;
}

template<class T>
CATCGMClonePtr<T>::CATCGMClonePtr(std::nullptr_t) noexcept
  : _ptr(nullptr)
{
}

template<class T>
CATCGMClonePtr<T>& CATCGMClonePtr<T>::operator=(std::nullptr_t)
{
  if (_ptr)
  {
    delete _ptr;
    _ptr = nullptr;
  }
  return *this;
}
#else
template<class T>
CATCGMClonePtr<T>::CATCGMClonePtr()
  : _ptr(0)
{}
#endif

template<class T>
bool CATCGMClonePtr<T>::operator==(CATCGMClonePtr const& iPtr) const CATCGMCLONEPTR_NOEXCEPT
{
  return _ptr == iPtr._ptr;
}

template<class T>
bool CATCGMClonePtr<T>::operator!=(CATCGMClonePtr const& iPtr) const CATCGMCLONEPTR_NOEXCEPT
{
  return _ptr != iPtr._ptr;
}

template<class T>
bool CATCGMClonePtr<T>::operator<(CATCGMClonePtr const& iPtr) const CATCGMCLONEPTR_NOEXCEPT
{
  return _ptr < iPtr._ptr;
}

template<class T>
bool CATCGMClonePtr<T>::operator<=(CATCGMClonePtr const& iPtr) const CATCGMCLONEPTR_NOEXCEPT
{
  return _ptr <= iPtr._ptr;
}

template<class T>
bool CATCGMClonePtr<T>::operator>(CATCGMClonePtr const& iPtr) const CATCGMCLONEPTR_NOEXCEPT
{
  return _ptr > iPtr._ptr;
}

template<class T>
bool CATCGMClonePtr<T>::operator>=(CATCGMClonePtr const& iPtr) const CATCGMCLONEPTR_NOEXCEPT
{
  return _ptr >= iPtr._ptr;
}

#if defined(CATCGMCLONEPTR_CPP11)
template<class T>
bool CATCGMClonePtr<T>::operator==(std::nullptr_t) const noexcept
{
  return _ptr == nullptr;
}

template<class T>
bool CATCGMClonePtr<T>::operator!=(std::nullptr_t) const noexcept
{
  return _ptr != nullptr;
}
#endif

template<class T>
T& CATCGMClonePtr<T>::operator*() const CATCGMCLONEPTR_NOEXCEPT
{
  return *_ptr;
}

template<class T>
T* CATCGMClonePtr<T>::operator->() const CATCGMCLONEPTR_NOEXCEPT
{
  return _ptr;
}

template<class T>
T* CATCGMClonePtr<T>::get() const CATCGMCLONEPTR_NOEXCEPT
{
  return _ptr;
}

template<class T>
T* CATCGMClonePtr<T>::release() CATCGMCLONEPTR_NOEXCEPT
{
  T* ptr = _ptr;
  _ptr = 0;
  return ptr;
}

template<class T>
CATCGMClonePtr<T>::operator bool() const CATCGMCLONEPTR_NOEXCEPT
{
  return !!_ptr;
}

#endif
