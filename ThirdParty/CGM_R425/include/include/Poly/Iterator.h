// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//===================================================================
//
// Iterator.h
//
// Generic encapsulating class for iterator
// Useful to get rid of iterator class type constraint
// Drawback : need to use clone method for copy
//
//===================================================================
// Mar 2021 : F1Z : Creation
//===================================================================

// System&co
#include "DSYSysCommon.h"

// PolyhedralMathematics
#include "Poly/TemplateUtils.h"
#include "Poly/Vector.h"

// PolyhedralInterfaces
#include "CATPolyRefCounted.h"

// std
#ifndef _AIX
#include <initializer_list>
#endif

#pragma once

namespace Poly
{
  namespace Interface
  {
    // Interface for "basic" poly iterartor (Begin/End/++/operator*)
    template<typename T>
    class Iterator : public CATPolyRefCounted
    {
    public:
      typedef T value_type;
    public:
      Iterator(){};
      virtual ~Iterator(){};

    public:
      virtual Iterator<T> & Begin() = 0;
      virtual Iterator<T> & operator++() = 0;
      Iterator<T> & Next() { return operator++(); };
      virtual bool End() const = 0;

      virtual Iterator<T> * Clone() const = 0;
      virtual Iterator<T> * Move() const { return Clone(); };

      virtual T operator*() const = 0;
      T Get() const { return **this; };
      T operator->() const { return **this; };
    };

    // Interface for poly iterator with fast increment implementation (operator+=, Position, Size)
    template<typename T>
    class IteratorFastIncr : public Iterator<T>
    {
    public:
      typedef T value_type;
    public:
      IteratorFastIncr() {};
      virtual ~IteratorFastIncr() {};

    public:
      virtual IteratorFastIncr<T> & Begin() = 0;
      virtual IteratorFastIncr<T> & operator++() = 0;
      IteratorFastIncr<T> & Next() { return operator++(); };
      virtual bool End() const = 0;

      virtual IteratorFastIncr<T> * Clone() const = 0;
      virtual IteratorFastIncr<T> * Move() const { return Clone(); };

      virtual T operator*() const = 0;
      T Get() const { return **this; };
      T operator->() const { return **this; };

    public:
      virtual IteratorFastIncr<T> & operator+=(const unsigned int) = 0;
      virtual unsigned int Position() const = 0;
      virtual unsigned int NbElements() const = 0;
    };
  };

  // encapsulating class, no required if the impl inherit from Interface::Iterator interface
  template<typename IteratorImplType>
  class IteratorEncapsulator : public Poly::Interface::Iterator<typename IteratorImplType::value_type>
  {
  private:
    IteratorImplType _ite;

  public:
    IteratorEncapsulator(const IteratorImplType & iIte) : _ite(iIte){};
    ~IteratorEncapsulator(){};

  public:
    Poly::Interface::Iterator<typename IteratorImplType::value_type> & Begin() { _ite.Begin(); return *this; };
    Poly::Interface::Iterator<typename IteratorImplType::value_type> & operator++() { ++_ite; return *this; };
    bool End() const { return _ite.End(); };

    Poly::Interface::Iterator<typename IteratorImplType::value_type> * Clone() const { return new IteratorEncapsulator(_ite); };

    typename IteratorImplType::value_type operator*() const { return *_ite; };
  };

  // Specialization for pointer iterator
  template<typename IteratorImplType>
  class IteratorEncapsulator<IteratorImplType*> : public Poly::Interface::Iterator<typename IteratorImplType::value_type>
  {
  private:
    IteratorImplType *_ite;

  public:
    IteratorEncapsulator(IteratorImplType * iIte, bool iDuplicate=true)
    {
      _ite = iIte? iDuplicate? iIte->Clone() : iIte : NULL;
      if(!iDuplicate)
        _ite->AddRef();
    }

    ~IteratorEncapsulator()
    {
      CATSysReleasePtr(_ite);
    }

  public:
    Poly::Interface::Iterator<typename IteratorImplType::value_type> & Begin()
    {
      if(_ite)
        _ite->Begin();
      return *this;
    };

    Poly::Interface::Iterator<typename IteratorImplType::value_type> & operator++() { ++(*_ite); return *this; };
    bool End() const { return _ite? _ite->End() : true; };

    Poly::Interface::Iterator<typename IteratorImplType::value_type> * Clone() const { return new Poly::Interface::Iterator<typename IteratorImplType::value_type>(_ite); };

    typename IteratorImplType::value_type operator*() { return **_ite; };
  };

  // encapsulating class, no required if the impl inherit from Interface::Iterator interface
  template<typename IteratorImplType>
  class IteratorFastIncrEncapsulator : public Poly::Interface::IteratorFastIncr<typename IteratorImplType::value_type>
  {
  private:
    IteratorImplType _ite;

  public:
    IteratorFastIncrEncapsulator(const IteratorImplType & iIte) : _ite(iIte) {};
    ~IteratorFastIncrEncapsulator() {};

  public:
    Poly::Interface::IteratorFastIncr<typename IteratorImplType::value_type> & Begin() { _ite.Begin(); return *this; };
    Poly::Interface::IteratorFastIncr<typename IteratorImplType::value_type> & operator++() { ++_ite; return *this; };
    bool End() const { return _ite.End(); };

    Poly::Interface::IteratorFastIncr<typename IteratorImplType::value_type> & operator+=(const unsigned int increment) { _ite += increment; return *this; };
    unsigned int Position() const { return _ite.Position(); };
    unsigned int NbElements() const { return _ite.NbElements(); };

    Poly::Interface::IteratorFastIncr<typename IteratorImplType::value_type> * Clone() const { return new IteratorFastIncrEncapsulator(_ite); };

    typename IteratorImplType::value_type operator*() const { return *_ite; };
  };

  // Specialization for pointer iterator
  template<typename IteratorImplType>
  class IteratorFastIncrEncapsulator<IteratorImplType *> : public Poly::Interface::IteratorFastIncr<typename IteratorImplType::value_type>
  {
  private:
    IteratorImplType * _ite;

  public:
    IteratorFastIncrEncapsulator(IteratorImplType * iIte, bool iDuplicate = true)
    {
      _ite = iIte ? iDuplicate ? iIte->Clone() : iIte : NULL;
      if (!iDuplicate)
        _ite->AddRef();
    }

    ~IteratorFastIncrEncapsulator()
    {
      CATSysReleasePtr(_ite);
    }

  public:
    Poly::Interface::IteratorFastIncr<typename IteratorImplType::value_type> & Begin()
    {
      if (_ite)
        _ite->Begin();
      return *this;
    };

    Poly::Interface::IteratorFastIncr<typename IteratorImplType::value_type> & operator++() { ++(*_ite); return *this; };
    bool End() const { return _ite ? _ite->End() : true; };

    Poly::Interface::IteratorFastIncr<typename IteratorImplType::value_type> & operator+=(const unsigned int increment) { (*_ite) += increment; return *this; };
    unsigned int Position() const { return _ite ? _ite->Position() : 0; };
    unsigned int NbElements() const { return _ite ? _ite->NbElements() : 0; };

    Poly::Interface::IteratorFastIncr<typename IteratorImplType::value_type> * Clone() const { return new Poly::Interface::Iterator<typename IteratorImplType::value_type>(_ite); };

    typename IteratorImplType::value_type operator*() { return **_ite; };
  };


  // Iterator encapsulating an (or severals) iterator interface
  template<typename ValueType>
  class Iterator : public Poly::Interface::Iterator<ValueType>
  {
  private:
	typedef ValueType value_type;
    int _id;
    PolyVector<Poly::Interface::Iterator<ValueType>*> _iterators;

  public:
    Iterator(const Poly::Interface::Iterator<ValueType> & iIte)
    {
      _id = 0;
      _iterators.push_back(iIte.Clone());
      Begin();
    }

#ifndef _AIX
    Iterator(std::initializer_list < Poly::Interface::Iterator<ValueType>* > list, bool iDuplicate = true)
    {
      _id = 0;
      _iterators.reserve(list.size());
      for (auto elem : list)
      {
        _iterators.emplace_back(iDuplicate ? elem->Clone() : elem);
        if (!iDuplicate)
          elem->AddRef();
      }
      Begin();
    }

    Iterator(Poly::Interface::Iterator<ValueType> && iIte)
    {
      _id = 0;
      _iterators.emplace_back(iIte.Move());
      Begin();
    }
#endif

    Iterator(Poly::Interface::Iterator<ValueType> * iIte, bool iDuplicate = true)
    {
      _id = 0;
      _iterators.push_back(iIte ? iDuplicate ? iIte->Clone() : iIte : NULL);
      if(!iDuplicate)
        _iterators.back()->AddRef();
    }

    Iterator(const Iterator<ValueType> & iToCopy)
    {
      _id = iToCopy._id;
      for (int i = 0; i < iToCopy._iterators.size(); ++i)
        _iterators.push_back(iToCopy._iterators[i]->Clone());
    }

    ~Iterator()
    {
      for(typename PolyVector<Poly::Interface::Iterator<ValueType>* >::iterator ite = _iterators.begin(); ite!=_iterators.end(); ++ite)
        CATSysReleasePtr(*ite);
    }

    Iterator<ValueType>& operator=(const Iterator<ValueType> & iToCopy)
    {
      for (typename PolyVector<Poly::Interface::Iterator<ValueType>* >::iterator ite = _iterators.begin(); ite!=_iterators.end(); ++ite)
        CATSysReleasePtr(*ite);

      _id = iToCopy._id;
      for (int i = 0; i < iToCopy._iterators.size(); ++i)
        _iterators.emplace_back(iToCopy._iterators->Clone());
    }

  public:
    Poly::Interface::Iterator<value_type> & Begin()
    {
      _id = 0;
      if (_iterators.size() > 0 && _iterators[_id])
        _iterators[_id]->Begin();

      while (_id < _iterators.size() && _iterators[_id]->End()) /// move to next valid iterators
        ++_id;

      return *this;
    };

    Poly::Interface::Iterator<value_type> & operator++() 
    { 
      if (_id < _iterators.size())
      {
        if (_iterators[_id]->End())
        {
          ++_id; /// move to next iterator
        }
        else
          ++(*_iterators[_id]); /// move to next element in the current iterator

        while (_id < _iterators.size() && _iterators[_id]->End()) /// move to next valid iterators
          ++_id;
      }
      return *this; 
    };

    bool End() const { return _id == _iterators.size(); };

    Poly::Interface::Iterator<value_type> * Clone() const { return new Iterator(*this); };

    value_type operator*() const
    {
      Poly::Interface::Iterator<ValueType> * ite = _iterators[_id];
      return **ite;
    };
  };

#ifndef _AIX
  template<typename IteratorImpl>
  class PartialIterator : public Poly::Interface::Iterator<typename IteratorImpl::value_type>
  {
    typedef typename IteratorImpl::value_type value_type;
  private:
    IteratorImpl _ite;
    Poly::Condition<const value_type&> _isValid;
    void MoveToValid()
    {
      while(!End() && !_isValid(*_ite))
        ++_ite;
    }

  public:
    PartialIterator(const IteratorImpl & iIte, Poly::Condition<const value_type&> iIsValid) :
      _ite(iIte),
      _isValid(iIsValid)
    {
    };

    ~PartialIterator() {};

  public:
    Poly::Interface::Iterator<value_type> & Begin() { _ite.Begin(); MoveToValid(); return *this; };
    Poly::Interface::Iterator<value_type> & operator++() { ++_ite; MoveToValid(); return *this; };
    bool End() const { return _ite.End(); };

    Poly::Interface::Iterator<value_type> * Clone() const { return new PartialIterator(_ite, _isValid); };

    value_type operator*() const { return *_ite; };
  };

  /**
   * Iterator on std structure with Begin/End interface
   */
  template<template<class, class...> class C, typename T, typename ...Args>
  struct STDIteratorToBegEndIterator : public Poly::Interface::Iterator<T>
  {
    typedef T value_type;

    inline STDIteratorToBegEndIterator(const C<T, Args...> & iContainer) : _container(iContainer) { Begin(); };
    inline STDIteratorToBegEndIterator(const STDIteratorToBegEndIterator<C, T, Args...> & iToCopy) : _container(iToCopy._container), _ite(iToCopy._ite) {};
    inline ~STDIteratorToBegEndIterator() {};
    inline Poly::Interface::Iterator<T>& Begin() { _ite = _container.begin(); return *this; };
    inline bool End() const { return _ite == _container.end(); };
    inline T operator*() { return *_ite; }
    inline T operator*() const { return *_ite; }
    inline Poly::Interface::Iterator<T> & operator++ () { ++_ite; return *this; };
    Poly::Interface::Iterator<T>* Clone() const { return new STDIteratorToBegEndIterator(*this); };

    const C<T, Args...> & _container;
    typename C<T, Args...>::const_iterator _ite;
  };

  /**
   * Iterator on std structure with Begin/End interface
   */
  template<template<class, class...> class C, typename T, typename ...Args>
  struct STDIteratorToBegEndIteratorFastIncr : public Poly::Interface::IteratorFastIncr<T>
  {
    typedef T value_type;

    inline STDIteratorToBegEndIteratorFastIncr(const C<T, Args...> & iContainer) : _container(iContainer) { Begin(); };
    inline STDIteratorToBegEndIteratorFastIncr(const STDIteratorToBegEndIteratorFastIncr<C, T, Args...> & iToCopy) : _container(iToCopy._container), _ite(iToCopy._ite) {};
    inline ~STDIteratorToBegEndIteratorFastIncr() {};
    inline Poly::Interface::IteratorFastIncr<T> & Begin() { _ite = _container.begin(); return *this; };
    inline bool End() const { return _ite == _container.end(); };
    inline T operator*() { return *_ite; }
    inline T operator*() const { return *_ite; }
    inline Poly::Interface::IteratorFastIncr<T> & operator++ () { ++_ite; return *this; };
    inline Poly::Interface::IteratorFastIncr<T> & operator+=(const unsigned int increment)
    {
      int incr = increment;
      for (; _ite != _container.end() && incr > 0; ++_ite, --incr);
      return *this;
    }
    inline unsigned int Position() const { return std::distance(_container.begin(), _ite); };
    inline unsigned int NbElements() const { return _container.size(); };
    Poly::Interface::IteratorFastIncr<T> * Clone() const { return new STDIteratorToBegEndIteratorFastIncr(*this); };

    const C<T, Args...> & _container;
    typename C<T, Args...>::const_iterator _ite;
  };
#endif

  // Might be useful for basic iteration with direct incrementation
  // Ex: if need begin/end iterator on a range of integer...
  template<typename T>
  class DirectIncrementIterator : public Poly::Interface::Iterator<T>
  {
  private:
    T _first;
    T _last;
    T _current;

  public:
    DirectIncrementIterator(T iFirst, T iLast) :
      _first(iFirst),
      _last(iLast),
      _current(iFirst)
    {};

    DirectIncrementIterator(const DirectIncrementIterator & iToCopy) :
      _first(iToCopy._first),
      _last(iToCopy._last),
      _current(iToCopy._current)
    {};

    ~DirectIncrementIterator() {};

    Poly::Interface::Iterator<T>& Begin()
    {
      _current = _first;
      return *this;
    }

    T operator*() const
    {
      return _current;
    }

    Poly::Interface::Iterator<T> * Clone() const
    {
      return new DirectIncrementIterator(*this);
    }

    Poly::Interface::Iterator<T>& operator++()
    {
      ++_current;
      return *this;
    }

    bool End() const
    {
      return _current > _last;
    }
  };

  // useful in case of isolated element (to avoid creating structure containing it)
  template<typename T>
  class OneElementIterator : public Interface::Iterator<T>
  {
  public:
    OneElementIterator(T & iElement) : _element(iElement), _end(false) {};
    virtual ~OneElementIterator() {};

  public:
    virtual Iterator<T> & Begin() { _end = false; return *this; };
    virtual Iterator<T> & operator++() { _end = true; return *this; };
    Iterator<T> & Next() { return operator++(); };
    virtual bool End() const { return _end; };

    virtual Iterator<T> * Clone() const { return new OneElementIterator(_element); };
    virtual Iterator<T> * Move() const { return Clone(); };

    virtual T& operator*() const { return _element; };
    T& Get() const { return **this; };
    T& operator->() const { return **this; };

  private:
    T& _element;
    bool _end;
  };

  template<typename T>
  class OneElementIterator<T*> : public Interface::Iterator<T*>
  {
  public:
    OneElementIterator(T* iElement) : _element(iElement), _end(false) {};
    virtual ~OneElementIterator() { _element = 0; };

  public:
    virtual Iterator<T*> & Begin() { _end = false; return *this; };
    virtual Iterator<T*> & operator++() { _end = true; return *this; };
    Iterator<T*> & Next() { return operator++(); };
    virtual bool End() const { return _end; };

    virtual Iterator<T*> * Clone() const { return new OneElementIterator(_element); };
    virtual Iterator<T*> * Move() const { return Clone(); };

    virtual T* operator*() const { return _element; };
    T* Get() const { return **this; };
    T* operator->() const { return **this; };

  private:
    T* _element;
    bool _end;
  };
};
