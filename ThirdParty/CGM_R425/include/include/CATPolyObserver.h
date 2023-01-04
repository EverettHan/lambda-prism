// COPYRIGHT DASSAULT SYSTEMES 2014, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyObserver.h
//
//===================================================================
// 04/14 JXO : Creation
// 02/19 F1Z : Add React methods (not on AIX)
// MM/YY
//===================================================================
#ifndef CATPolyObserver_H
#define CATPolyObserver_H

// Poly math
#include "CATRefCounted.h"

// Math
#include "CATMathInline.h"

// System
#include "CATListPV.h"
#include "CATBoolean.h"

#ifdef _AIX_SOURCE
#undef throw
#undef catch
#undef try
#else
#include <utility>
#endif  //_AIX_SOURCE
#include <vector>

template<class T>
class CATPolyObserverObserver;

/**
 * Base class for chained observers mechanism in Polyhedral components.
 * Here is an example of code. First of all, operators or objects have to
 * expose a virtual observer.
 * @code
 * class MyObserverDefinition : public CATPolyObserver<MyObserverDefinition>
 * {
 * public:
 *   virtual int myfirstmethod(int i) = 0;
 *   virtual int mysecondmethod(int i, int j) = 0;
 * protected:
 *   MyObserverDefinition(){}
 *   ~MyObserverDefinition(){}
 * };
 * @endcode
 * Note that <code>MyObserverDefinition</code> is used as the template declaration.<br/>
 * Then in the observed class:
 * @code
 * class MyObservedClass
 * {
 *   // ...
 *   MyObserverDefinition * m_obs;
 *   ~MyObservedClass()
 *   {
 *     if(m_obs)
 *       m_obs->Release();
 *     m_obs = 0;
 *   }
 *   // ...
 *   void RegisterObserver(MyObserverDefinition * obs)
 *   {
 *     MyObserverDefinition::Register(m_obs, obs);
 *   }
 *   // ...
 *   void ObservedMethod(int i)
 *   {
 *     MyObserverDefinition * current = m_obs;
 *     while(current) {
 *       current->myfirstmethod(i);
 *       current = current->Next();
 *     }
 *     // ...
 *   }
 * };
 * @endcode
 * This way any client code can implement <code>MyObserverDefinition</code> and register 
 * observers on <code>MyObservedClass</code>.<br/>
 * Important note: this observer mechanism uses linked lists to store several obervers on a
 * single observed instance. That means you CANNOT put a single observer instance on multiple
 * observed instances.<br/>
 * There are macro helpers to ease the loops for calling the observers in the observed code.
 * The above loop can be replaced by:
 * @code
 *   CATPolyObserverFORWARDLOOP(MyObserverDefinition, m_obs, myfirstmethod(i));
 * @endcode
 * You can also do backward loops (<code>CATPolyObserverBACKWARDLOOP</code>), or update some 
 * <code>int</code> values returned by the observer method. For example:
 * @code
 *   int ObserverReturnValue = 0;
 *   CATPolyObserverFORWARDORLOOP(MyObserverDefinition, m_obs, mysecondmethod(i, j));
 * @endcode
 * Here each returned value of mysecondmethod is added to ObserverReturnValue with the 
 * bitwise | operator.<br/>
 * All of the loops have their safe equivalents:
 * @code
 *   SAFECATPolyObserverFORWARDLOOP(MyObserverDefinition, m_obs, myfirstmethod(i));
 *   SAFECATPolyObserverBACKWARDLOOP(MyObserverDefinition, m_obs, myfirstmethod(i));
 *   int ObserverReturnValue = 0;
 *   SAFECATPolyObserverFORWARDORLOOP(MyObserverDefinition, m_obs, myfirstmethod(i));
 *   int ObserverReturnValue = -1;
 *   SAFECATPolyObserverBACKWARDANDLOOP(MyObserverDefinition, m_obs, myfirstmethod(i));
 * @endcode
 * That means that even inside the implementation of myfirstmethod, an observer implementation 
 * can remove itself from the chain of observers attached to the operator. The loop will 
 * continue as needed.<br/>
 * The performances will be impacted in this case due to the use of a temporary list of observers 
 * to manage the stability of the chain.
 */

template<class T>
class CATPolyObserver : public CATRefCounted
{
public:

  /**
   * Registers an observer at the end of the chain
   * @param chain
   *        input chain (could be null pointer, in this case it will point to obs)
   * @param obs
   *        An addref is done on obs, it will be released in chain's destructor.
   * @return S_OK everything went fine.
   *         Error if obs is already registered.
   */
  static HRESULT Register(T*& chain, T*obs);
  /**
   * Removes the observer from the chain
   * @param chain
   *        input/output chain
   * @param obs
   *        Release will be called on obs
   */
  static void Unregister(T*& chain, T*obs);
  /** Returns the next observer in the chain */
  T * Next(){return m_next;}
  /** Returns the previous observer in the chain */
  T * Prev(){return m_prev;}

  /** Returns TRUE if o is already in the chain */
  CATBoolean IsAlreadyRegistered(const CATPolyObserver * o);

#ifndef _AIX
  /**
   * Propagate the method to all the observers chained to this one
   * with a HRESULT result
   */
  template<typename TObs, typename ...Params, typename ...Args>
  HRESULT React(HRESULT (TObs::*iF)(Params...), Args&&... args)
  {
    HRESULT hr = S_OK;
    static_assert(std::is_base_of<TObs, T>::value, "Template T doesn't deriv from TObs");
    T * obs = (T*)this;
    while(obs && SUCCEEDED(hr))
    {
      hr |= (((TObs*)obs)->*iF)(std::forward<Args>(args)...);
      obs = obs->Next();
    }
    return hr;
  };

  /**
   * Propagate the method to all the observers chained to this one
   * with a void result
   */
  template<typename TObs, typename ...Params, typename ...Args>
  void React(void (TObs::*iF)(Params...), Args&&... args)
  {
    static_assert(std::is_base_of<TObs, T>::value, "Template T doesn't deriv from TObs");
    T * obs = this;
    while(obs)
    {
      (((TObs*)obs)->*iF)(std::forward<Args>(args)...);
      obs = obs->Next();
    }
  };
#endif
  

protected:
  /** Constructor */
  INLINE CATPolyObserver();
  /** Destructor */
  virtual ~CATPolyObserver();

protected:
  friend class CATPolyObserverObserver<T>;
  T * m_prev;
  T * m_next;
  CATPolyObserverObserver<T> * m_o;
};

template<class T>
class CATPolyObserverObserver
{
public:
  CATPolyObserverObserver(T * o = 0):m_o(0)
  {
    SetO(o);
  }
  CATPolyObserverObserver(const CATPolyObserverObserver<T> & other):m_o(0)
  {
    SetO(other.m_o);
  }
  ~CATPolyObserverObserver()
  {
    if(m_o)
      m_o->m_o = 0;
    m_o = 0;
  }
  T * GetO()
  {
    return m_o;
  }
  void SetO(T * o)
  {
    if(m_o && m_o != o)
      m_o->m_o = 0;
    if(o)
    {
      CATPolyObserverObserver<T> * other = o->m_o;
      if(other)
        other->m_o = 0;
      o->m_o = this;
    }
    m_o = o;
  }
  CATPolyObserverObserver<T> & operator = (const CATPolyObserverObserver<T> & other)
  {
    SetO(other.m_o);
    return *this;
  }
private:
  T * m_o;
};

template<class T>
CATPolyObserver<T>::CATPolyObserver():
  m_prev(0),
  m_next(0),
  m_o(0)
{
}

template<class T>
CATPolyObserver<T>::~CATPolyObserver()
{
  m_prev = 0;
  if(m_next)
    m_next->Release();
  m_next = 0;
  if(m_o)
    m_o->SetO(0);
  m_o = 0;
}

template<class T>
HRESULT CATPolyObserver<T>::Register(T*& chain, T*obs)
{
  if(!obs)
    return E_INVALIDARG;
  if(!chain)
  {
    obs->AddRef();
    chain = obs;
    return S_OK;
  }
  else if(chain == obs)
  {
    return E_INVALIDARG;
  }
  else if(chain->m_next)
    return Register(chain->m_next, obs);
  else
  {
    obs->AddRef();
    chain->m_next = obs;
    obs->m_prev = chain;
    return S_OK;
  }
}

template<class T>
void CATPolyObserver<T>::Unregister(T*& chain, T*obs)
{
  if(!obs || !chain)
    return;
  Unregister(chain->m_next, obs);
  if(chain == obs)
  {
    T * prev = chain->m_prev;
    T * next = chain->m_next;
    chain->m_next = 0;
    chain->Release();
    chain = next;
    if(prev)
      prev->m_next = chain;
    if(chain)
      chain->m_prev = prev;
  }
}

template<class T>
CATBoolean CATPolyObserver<T>::IsAlreadyRegistered(const CATPolyObserver * o)
{
  if(this == o)
    return TRUE;
  if(m_next)
    return m_next->IsAlreadyRegistered(o);
  else
    return FALSE;
}

#define CATPolyObserverFORWARDLOOP(TYPE, PointerToChain, methodwithargs)                                      \
{                                                                                                             \
  TYPE * currentObserver = PointerToChain;                                                                    \
  while(currentObserver){                                                                                     \
    currentObserver->methodwithargs;                                                                          \
    currentObserver = currentObserver->Next();                                                                \
  }                                                                                                           \
}

#define CATPolyObserverBACKWARDLOOP(TYPE, PointerToChain, methodwithargs)                                     \
{                                                                                                             \
  TYPE * currentObserver = PointerToChain;                                                                    \
  TYPE * nextObserver = PointerToChain;                                                                       \
  while(currentObserver){                                                                                     \
    nextObserver = currentObserver;                                                                           \
    currentObserver = currentObserver->Next();                                                                \
  }                                                                                                           \
  while(nextObserver){                                                                                        \
    nextObserver->methodwithargs;                                                                             \
    nextObserver = nextObserver->Prev();                                                                      \
  }                                                                                                           \
}

// Needs an intialized int ObserverReturnValue to 0
#define CATPolyObserverFORWARDORLOOP(TYPE, PointerToChain, methodwithargs)                                    \
{                                                                                                             \
  TYPE * currentObserver = PointerToChain;                                                                    \
  while(currentObserver){                                                                                     \
    ObserverReturnValue |= currentObserver->methodwithargs;                                                   \
    currentObserver = currentObserver->Next();                                                                \
  }                                                                                                           \
}

// Needs an intialized int ObserverReturnValue to -1
#define CATPolyObserverBACKWARDANDLOOP(TYPE, PointerToChain, methodwithargs)                                  \
{                                                                                                             \
  TYPE * currentObserver = PointerToChain;                                                                    \
  TYPE * nextObserver = PointerToChain;                                                                       \
  while(currentObserver){                                                                                     \
    nextObserver = currentObserver;                                                                           \
    currentObserver = currentObserver->Next();                                                                \
  }                                                                                                           \
  while(nextObserver){                                                                                        \
    ObserverReturnValue &= nextObserver->methodwithargs;                                                      \
    nextObserver = nextObserver->Prev();                                                                      \
  }                                                                                                           \
}

#define SAFECATPolyObserverFORWARDLOOP(TYPE, PointerToChain, methodwithargs)                                  \
{                                                                                                             \
  TYPE * current = PointerToChain;                                                                            \
  TYPE * prev = PointerToChain;                                                                               \
  while(prev){                                                                                                \
    current = prev;                                                                                           \
    prev = prev->Prev();                                                                                      \
  }                                                                                                           \
  if(current)                                                                                                 \
  {                                                                                                           \
    std::vector<CATPolyObserverObserver<TYPE> > vvv; /* Needed to be safe if observers are added or removed */\
    while(current){                                                                                           \
      vvv.push_back(CATPolyObserverObserver<TYPE>(current));                                                  \
      current = current->Next();                                                                              \
    }                                                                                                         \
    size_t iObserver = 0;                                                                                     \
    while(iObserver < vvv.size())                                                                             \
      if(prev = (TYPE*)vvv[iObserver++].GetO())                                                               \
        prev->methodwithargs;                                                                                 \
  }                                                                                                           \
}

#define SAFECATPolyObserverBACKWARDLOOP(TYPE, PointerToChain, methodwithargs)                                 \
{                                                                                                             \
  TYPE * current = PointerToChain;                                                                            \
  TYPE * next = PointerToChain;                                                                               \
  while(current){                                                                                             \
    next = current;                                                                                           \
    current = current->Next();                                                                                \
  }                                                                                                           \
  if(next)                                                                                                    \
  {                                                                                                           \
    std::vector<CATPolyObserverObserver<TYPE> > vvv; /* Needed to be safe if observers are added or removed */\
    while(next){                                                                                              \
      vvv.push_back(CATPolyObserverObserver<TYPE>(next));                                                     \
      next = next->Prev();                                                                                    \
    }                                                                                                         \
    size_t iObserver = vvv.size();                                                                            \
    while(iObserver > 0)                                                                                      \
      if(next = (TYPE*)vvv[--iObserver].GetO())                                                               \
        next->methodwithargs;                                                                                 \
  }                                                                                                           \
}

// Needs an intialized int ObserverReturnValue to -1
#define SAFECATPolyObserverBACKWARDANDLOOP(TYPE, PointerToChain, methodwithargs)                              \
{                                                                                                             \
  TYPE * current = PointerToChain;                                                                            \
  TYPE * next = PointerToChain;                                                                               \
  while(current){                                                                                             \
    next = current;                                                                                           \
    current = current->Next();                                                                                \
  }                                                                                                           \
  if(next)                                                                                                    \
  {                                                                                                           \
    std::vector<CATPolyObserverObserver<TYPE> > vvv; /* Needed to be safe if observers are added or removed */\
    while(next){                                                                                              \
      vvv.push_back(CATPolyObserverObserver<TYPE>(next));                                                     \
      next = next->Prev();                                                                                    \
    }                                                                                                         \
    size_t iObserver = vvv.size();                                                                            \
    while(iObserver > 0)                                                                                      \
      if(next = (TYPE*)vvv[--iObserver].GetO())                                                               \
        ObserverReturnValue &= next->methodwithargs;                                                          \
  }                                                                                                           \
}

// Needs an intialized int ObserverReturnValue to 0
#define SAFECATPolyObserverFORWARDORLOOP(TYPE, PointerToChain, methodwithargs)                                \
{                                                                                                             \
  TYPE * current = PointerToChain;                                                                            \
  TYPE * prev = PointerToChain;                                                                               \
  while(prev){                                                                                                \
    current = prev;                                                                                           \
    prev = prev->Prev();                                                                                      \
  }                                                                                                           \
  if(current)                                                                                                 \
  {                                                                                                           \
    std::vector<CATPolyObserverObserver<TYPE> > vvv; /* Needed to be safe if observers are added or removed */\
    while(current){                                                                                           \
      vvv.push_back(CATPolyObserverObserver<TYPE>(current));                                                  \
      current = current->Next();                                                                              \
    }                                                                                                         \
    size_t iObserver = 0;                                                                                     \
    while(iObserver < vvv.size())                                                                             \
      if(prev = (TYPE*)vvv[iObserver++].GetO())                                                               \
        ObserverReturnValue |= prev->methodwithargs;                                                          \
  }                                                                                                           \
}


#endif
