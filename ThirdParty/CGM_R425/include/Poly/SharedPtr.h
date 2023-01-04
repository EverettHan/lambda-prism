#pragma once

// copy from CATCGMSharedPtr (not a prereq)

#if !defined(_AIX_SOURCE)
#define CATCGMSHAREDPTR_CPP11
#endif

#ifdef CATCGMSHAREDPTR_CPP11
#define CATCGMSHAREDPTR_NOEXCEPT noexcept

#include <utility>
#else
#define CATCGMSHAREDPTR_NOEXCEPT
#endif


namespace Poly {

  // Utility class for automatic management of ref counted objects with AddRef/Release methods
  // Basic use :
  // {
  //   SharedPtr<Foo> pFoo(new Foo());
  //   pFoo->BigComputation();
  // } // pFoo goes out of scope, Release is automatically called

  // Class member :
  // class Foo
  // {
  //   SetBar(SharedPtr<Bar> ipBar) { _pBar = ipBar; } // Copy automatically does an AddRef call on pointed bar object
  //   ~Foo();                                               // Destructor automatically calls Release on _pBar
  //  
  //   SharedPtr<Bar> _pBar;
  // };

  //
  // If you receive an object which was not previously manage by SharedPtr, 
  // you can switch to an automatic management with additional argument to constructor
  // Method(Foo* ipFoo)
  // {
  //   SharedPtr<Foo> pFoo(ipFoo, true); // true => an AddRef 
  //   ...
  // } // Out of scope : Release        

  // SharedPtr can also be used within a container class like std::vector
  // Method(SharedPtr<Foo> ipFoo1)
  // {
  //   std::vector<SharedPtr<Foo>> myVector(1);
  //   myVector[0] = ipFoo; // An Addref is done on the element pointed by ipFoo
  // } // The vector is destroyed : the container is cleared so a Release is called on each of its elements.

  template<class T>
  class SharedPtr
  {
  public:
    /**
    @param AddOneRef : call addref on the creation of this shared pointer  => consider itself as a new reference
    (typically if it was not managed by sharedptr it is necessary for example if it is an argument as pointer )
    */
    explicit SharedPtr(T* iPtr, bool AddMyRef = false);
    SharedPtr(SharedPtr const& iPtr);
    SharedPtr& operator=(SharedPtr const& iPtr);
    ~SharedPtr();

    template<class U>
    SharedPtr(SharedPtr<U> const& iPtr);

    template<class U>
    SharedPtr& operator=(SharedPtr<U> const& iPtr);

#if defined(CATCGMSHAREDPTR_CPP11)
    SharedPtr() noexcept = default;

    SharedPtr(SharedPtr&& iPtr) noexcept;
    SharedPtr& operator=(SharedPtr&& iPtr) noexcept;

    SharedPtr(std::nullptr_t) noexcept;
    SharedPtr& operator=(std::nullptr_t);

    template<class U>
    SharedPtr(SharedPtr<U>&& iPtr) noexcept;

    template<class U>
    SharedPtr& operator=(SharedPtr<U>&& iPtr);
#else
    SharedPtr();
#endif

    bool operator == (SharedPtr const& iPtr) const CATCGMSHAREDPTR_NOEXCEPT;
    bool operator != (SharedPtr const& iPtr) const CATCGMSHAREDPTR_NOEXCEPT;
    bool operator <  (SharedPtr const& iPtr) const CATCGMSHAREDPTR_NOEXCEPT;
    bool operator <= (SharedPtr const& iPtr) const CATCGMSHAREDPTR_NOEXCEPT;
    bool operator >  (SharedPtr const& iPtr) const CATCGMSHAREDPTR_NOEXCEPT;
    bool operator >= (SharedPtr const& iPtr) const CATCGMSHAREDPTR_NOEXCEPT;

#if defined(CATCGMSHAREDPTR_CPP11)
    bool operator == (std::nullptr_t) const noexcept;
    bool operator != (std::nullptr_t) const noexcept;
#endif

    template<class U>
    bool operator == (U* iPtr) const CATCGMSHAREDPTR_NOEXCEPT;
    template<class U>
    bool operator != (U* iPtr) const CATCGMSHAREDPTR_NOEXCEPT;

    T& operator*() const CATCGMSHAREDPTR_NOEXCEPT;
    T* operator->() const CATCGMSHAREDPTR_NOEXCEPT;

    T* get() const CATCGMSHAREDPTR_NOEXCEPT;

    T* release() CATCGMSHAREDPTR_NOEXCEPT;

    // Use carefully
    // Enable to interact with old interface which initializes a reference on a pointer which must be released
    // SharedPtr<Foo> foo;
    // ...->Get(foo.ref());
    T*& ref() CATCGMSHAREDPTR_NOEXCEPT;

#if defined(CATCGMSHAREDPTR_CPP11)
    template<class U>
    SharedPtr<U> Cast() const&;

    template<class U>
    SharedPtr<U> Cast() && noexcept;
#else
    template<class U>
    SharedPtr<U> Cast() const;
#endif

#if defined(CATCGMSHAREDPTR_CPP11)
    explicit operator bool() const noexcept;
#else
    operator bool() const;
#endif

  private:
    template<class U>
    friend class SharedPtr;

#if defined(CATCGMSHAREDPTR_CPP11)
    T* _ptr = nullptr;
#else
    T* _ptr;
#endif
  };

  template<class T>
  SharedPtr<T>::SharedPtr(T* iPtr, bool AddOneRef)
    : _ptr(iPtr)
  {
    if (_ptr && AddOneRef)
    {
      _ptr->AddRef();
    }
  }

  template<class T>
  SharedPtr<T>::SharedPtr(SharedPtr const& iPtr)
    : _ptr(iPtr._ptr)
  {
    if (_ptr)
    {
      _ptr->AddRef();
    }
  }

  template<class T>
  SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr const& iPtr)
  {
    if (_ptr != iPtr._ptr)
    {
      if (_ptr)
      {
        _ptr->Release();
      }
      _ptr = iPtr._ptr;
      if (_ptr)
      {
        _ptr->AddRef();
      }
    }
    return *this;
  }

  template<class T>
  SharedPtr<T>::~SharedPtr()
  {
    if (_ptr)
    {
      _ptr->Release();
    }
  }

  template<class T>
  template<class U>
  SharedPtr<T>::SharedPtr(SharedPtr<U> const& iPtr)
    : _ptr(iPtr.get())
  {
    if (_ptr)
      _ptr->AddRef();
  }

  template<class T>
  template<class U>
  SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<U> const& iPtr)
  {
    if (_ptr != iPtr.get())
    {
      if (_ptr)
        _ptr->Release();
      _ptr = iPtr.get();
      if (_ptr)
        _ptr->AddRef();
    }
    return *this;
  }

#if defined(CATCGMSHAREDPTR_CPP11)
  template<class T>
  SharedPtr<T>::SharedPtr(SharedPtr&& iPtr) noexcept
    : _ptr(iPtr._ptr)
  {
    iPtr._ptr = nullptr;
  }

  template<class T>
  SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& iPtr) noexcept
  {
    std::swap(_ptr, iPtr._ptr);
    return *this;
  }

  template<class T>
  SharedPtr<T>::SharedPtr(std::nullptr_t) noexcept
    : _ptr(nullptr)
  {
  }

  template<class T>
  SharedPtr<T>& SharedPtr<T>::operator=(std::nullptr_t)
  {
    if (_ptr)
    {
      _ptr->Release();
      _ptr = nullptr;
    }
    return *this;
  }

  template<class T>
  template<class U>
  SharedPtr<T>::SharedPtr(SharedPtr<U>&& iPtr) noexcept
    : _ptr(iPtr._ptr)
  {
    iPtr._ptr = nullptr;
  }

  template<class T>
  template<class U>
  SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<U>&& iPtr)
  {
    if (_ptr != iPtr.get())
    {
      if (_ptr)
        _ptr->Release();
      _ptr = iPtr._ptr;
      iPtr._ptr = nullptr;
    }
    return *this;
  }
#else
  template<class T>
  SharedPtr<T>::SharedPtr()
    : _ptr(0)
  {}
#endif

  template<class T>
  bool SharedPtr<T>::operator==(SharedPtr const& iPtr) const CATCGMSHAREDPTR_NOEXCEPT
  {
    return _ptr == iPtr._ptr;
  }

  template<class T>
  bool SharedPtr<T>::operator!=(SharedPtr const& iPtr) const CATCGMSHAREDPTR_NOEXCEPT
  {
    return _ptr != iPtr._ptr;
  }

  template<class T>
  template<class U>
  bool SharedPtr<T>::operator==(U* iPtr) const CATCGMSHAREDPTR_NOEXCEPT
  {
    return _ptr == iPtr;
  }

  template<class T>
  template<class U>
  bool SharedPtr<T>::operator!=(U* iPtr) const CATCGMSHAREDPTR_NOEXCEPT
  {
    return _ptr != iPtr;
  }

  template<class T, class U>
  bool operator==(T* iPtr1, SharedPtr<U> const& iPtr2) CATCGMSHAREDPTR_NOEXCEPT
  {
    return iPtr2 == iPtr1;
  }

  template<class T, class U>
  bool operator!=(T* iPtr1, SharedPtr<U> const& iPtr2) CATCGMSHAREDPTR_NOEXCEPT
  {
    return iPtr2 != iPtr1;
  }

  template<class T>
  bool SharedPtr<T>::operator<(SharedPtr const& iPtr) const CATCGMSHAREDPTR_NOEXCEPT
  {
    return _ptr < iPtr._ptr;
  }

  template<class T>
  bool SharedPtr<T>::operator<=(SharedPtr const& iPtr) const CATCGMSHAREDPTR_NOEXCEPT
  {
    return _ptr <= iPtr._ptr;
  }

  template<class T>
  bool SharedPtr<T>::operator>(SharedPtr const& iPtr) const CATCGMSHAREDPTR_NOEXCEPT
  {
    return _ptr > iPtr._ptr;
  }

  template<class T>
  bool SharedPtr<T>::operator>=(SharedPtr const& iPtr) const CATCGMSHAREDPTR_NOEXCEPT
  {
    return _ptr >= iPtr._ptr;
  }

#if defined(CATCGMSHAREDPTR_CPP11)
  template<class T>
  bool SharedPtr<T>::operator==(std::nullptr_t) const noexcept
  {
    return _ptr == nullptr;
  }

  template<class T>
  bool SharedPtr<T>::operator!=(std::nullptr_t) const noexcept
  {
    return _ptr != nullptr;
  }
#endif

  template<class T>
  T& SharedPtr<T>::operator*() const CATCGMSHAREDPTR_NOEXCEPT
  {
    return *_ptr;
  }

  template<class T>
  T* SharedPtr<T>::operator->() const CATCGMSHAREDPTR_NOEXCEPT
  {
    return _ptr;
  }

  template<class T>
  T* SharedPtr<T>::get() const CATCGMSHAREDPTR_NOEXCEPT
  {
    return _ptr;
  }

  template<class T>
  T* SharedPtr<T>::release() CATCGMSHAREDPTR_NOEXCEPT
  {
    T* ptr = _ptr;
    _ptr = 0;
    return ptr;
  }

  template<class T>
  T*& SharedPtr<T>::ref() CATCGMSHAREDPTR_NOEXCEPT
  {
    return _ptr;
  }

#if defined(CATCGMSHAREDPTR_CPP11)
  template<class T>
  template<class U>
  SharedPtr<U> SharedPtr<T>::Cast() const&
  {
    return SharedPtr<U>(static_cast<U*>(_ptr), true);
  }

  template<class T>
  template<class U>
  SharedPtr<U> SharedPtr<T>::Cast() && noexcept
  {
    auto ptr = _ptr;
    _ptr = nullptr;
    return SharedPtr<U>(static_cast<U*>(ptr));
  }
#else
  template<class T>
  template<class U>
  SharedPtr<U> SharedPtr<T>::Cast() const
  {
    return SharedPtr<U>(static_cast<U*>(_ptr), true);
  }
#endif

  template<class T>
  SharedPtr<T>::operator bool() const CATCGMSHAREDPTR_NOEXCEPT
  {
    return !!_ptr;
  }

#if defined(CATCGMSHAREDPTR_CPP11)
  template<class T, class... Args>
  SharedPtr<T> CreateSharedPtr(Args&&... iArgs)
  {
    return SharedPtr<T>(new T(std::forward<Args>(iArgs)...));
  }
#else
  template<class T>
  SharedPtr<T> CreateCGMSharedPtr()
  {
    return SharedPtr<T>(new T());
  }

  template<class T, class Arg1>
  SharedPtr<T> CreateCGMSharedPtr(Arg1& iArg1)
  {
    return SharedPtr<T>(new T(iArg1));
  }

  template<class T, class Arg1, class Arg2>
  SharedPtr<T> CreateCGMSharedPtr(Arg1& iArg1, Arg2& iArg2)
  {
    return SharedPtr<T>(new T(iArg1, iArg2));
  }

  template<class T, class Arg1, class Arg2, class Arg3>
  SharedPtr<T> CreateCGMSharedPtr(Arg1& iArg1, Arg2& iArg2, Arg3& iArg3)
  {
    return SharedPtr<T>(new T(iArg1, iArg2, iArg3));
  }

  template<class T, class Arg1, class Arg2, class Arg3, class Arg4>
  SharedPtr<T> CreateCGMSharedPtr(Arg1& iArg1, Arg2& iArg2, Arg3& iArg3, Arg4& iArg4)
  {
    return SharedPtr<T>(new T(iArg1, iArg2, iArg3, iArg4));
  }

  template<class T, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
  SharedPtr<T> CreateCGMSharedPtr(Arg1& iArg1, Arg2& iArg2, Arg3& iArg3, Arg4& iArg4, Arg5& iArg5)
  {
    return SharedPtr<T>(new T(iArg1, iArg2, iArg3, iArg4, iArg5));
  }

  template<class T, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
  SharedPtr<T> CreateCGMSharedPtr(Arg1& iArg1, Arg2& iArg2, Arg3& iArg3, Arg4& iArg4, Arg5& iArg5, Arg6& iArg6)
  {
    return SharedPtr<T>(new T(iArg1, iArg2, iArg3, iArg4, iArg5, iArg6));
  }

  template<class T, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
  SharedPtr<T> CreateCGMSharedPtr(Arg1& iArg1, Arg2& iArg2, Arg3& iArg3, Arg4& iArg4, Arg5& iArg5, Arg6& iArg6, Arg7& iArg7)
  {
    return SharedPtr<T>(new T(iArg1, iArg2, iArg3, iArg4, iArg5, iArg6, iArg7));
  }

  template<class T, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7, class Arg8>
  SharedPtr<T> CreateCGMSharedPtr(Arg1& iArg1, Arg2& iArg2, Arg3& iArg3, Arg4& iArg4, Arg5& iArg5, Arg6& iArg6, Arg7& iArg7, Arg8& iArg8)
  {
    return SharedPtr<T>(new T(iArg1, iArg2, iArg3, iArg4, iArg5, iArg6, iArg7, iArg8));
  }

  template<class T, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7, class Arg8, class Arg9>
  SharedPtr<T> CreateCGMSharedPtr(Arg1& iArg1, Arg2& iArg2, Arg3& iArg3, Arg4& iArg4, Arg5& iArg5, Arg6& iArg6, Arg7& iArg7, Arg8& iArg8, Arg9& iArg9)
  {
    return SharedPtr<T>(new T(iArg1, iArg2, iArg3, iArg4, iArg5, iArg6, iArg7, iArg8, iArg9));
  }
#endif
};

