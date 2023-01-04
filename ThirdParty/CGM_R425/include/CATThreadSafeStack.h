//=============================================================================
// COPYRIGHT Dassault Systemes 2009
//=============================================================================
//
// Template stack of T_Element
// First in, first out
// Instantiate objects for you so you don't have to worry about memory
//
//=============================================================================
// 2009-09-02   XXC: New from JXO CATPolyBVHNodePairStack
// 2013-05-23   JXO: Add event frequency for better performances
// 2013-09-03   JXO: Monosource for V5
//=============================================================================
#ifndef CATThreadSafeStack_H
#define CATThreadSafeStack_H

#include "CATMathInline.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATDataType.h"
#include "CATMutex.h"
#include "CATIAV5Level.h"
#ifdef CATIAR214
#define USECATEVENTS
#endif
#ifdef USECATEVENTS
#include "CATEvent.h"
#else
#include "CATWaitingPoint.h"
#endif
#include <string.h>

#include "PolyMultiThreading.h"
#include "CATPolyAtomicOperations.h"


// #define DEBUGSTACK
#ifdef DEBUGSTACK
#include <iostream.h>
using namespace std;
#endif

/**
 * Thread safe template class to manage stacks (FIFO) of elements
 * possibly from multiple threads (one or many threads push and/or pop
 * elements in/from the stack). The type of element in the stack is
 * defined through the template mechanism.
 * Note: In order to avoid numerous memory allocations, the push
 * method allocates big chunks of memory. Added elements are copied
 * thanks to the "=" operator so be sure your template element
 * implements = operator.
 * Note that you can choose to always lock the stack with the Pop and 
 * Push methods, or choose to push several objects and lock only once.
 * Same for Pop.
 */

/** How to implement a specific stack ? Example with a stack of int.
 * class CATStackOfInt : public CATThreadSafeStack<int>
 * {
 * public:
 *   CATStackOfInt(const CATBoolean iWaitForPop = TRUE):CATThreadSafeStack<int>(iWaitForPop)
 *   ~CATStackOfInt(){}
 * };
 * It's done!
 * You can now use it in a multi thread context:
 * CATStackOfInt MyStack;
 * MyStack.Push(42);
 * MyStack.SetFinish();
 * int i;
 * while(SUCCEEDED(MyStack.Pop(i)))
 * {
 *   // do something with i
 * }
 */

template <class T_Element> class CATThreadSafeStack
{
public:
  INLINE CATThreadSafeStack(const CATBoolean iWaitForPop = TRUE, int PoolSize = 256);
  INLINE virtual ~CATThreadSafeStack();
  INLINE CATThreadSafeStack(const CATThreadSafeStack & iCopy);
  INLINE CATThreadSafeStack & operator = (const CATThreadSafeStack & iCopy);

  /**
   * Returns the total Size of the stack.
   */
  INLINE int FullSize();
  /**
   * Return the number of non popped out elements. 0 if everything has
   * been popped out.
   */
  INLINE int QueueSize();

  /**
   * Returns
   *     0 if filling is not over
   *     1 if filling is over.
   * Note that filler has to set it when filling is over with
   * SetFinish method.
   */
  INLINE CATBoolean GetFinish();
  /**
   * To be called when the filling process is over.
   * Note that an 'add' event is sent in order to wake-up every listening threads.
   */
  INLINE void SetFinish(CATBoolean finish = TRUE);

  /**
   * Reset the stack at the beginning, in order to pop again every
   * pushed element. Works only if the fill of the stack is finished
   * (after a call of SetFinish()) and every elements has already been
   * popped out.
   */
  INLINE void Reset();

  /**
   * Releases memory and empties the stack.
   */
  INLINE void Empty();

  /**
   * Empties the stack without releasing memory for later reuse.
   */
  INLINE void EmptyWithoutRelease();

  /**
   * Pushes a new element (usually already allocated) in the stack.
   * The = operator is called on oElement.
   * Note: The principle allows to avoid element allocations at every
   * call to the push method. But this necessitate to keep the mutex
   * locked during the element initialization.
   */
  HRESULT Push(const T_Element & oElement);

  /**
   * Pops a previously added element (first in, first out.)
   *@param oElement: oElement is filled through the = operator
   *@return
   *     S_OK: Valid element is popped.
   *     S_FALSE: Their is no more elements in the stack, but some will
   *       possibly be pushed later (only if parameter iWaitForPop is
   *       set to FALSE in the constructor).
   *     E_FAIL: Empty stack, nothing is done.
   */
  HRESULT Pop(T_Element & oElement);

  /**
   * Multiple Pushes: Mutex can be locked only once for a lot of pushed elements
   * Call BeginPush, then n FastPush and EndPush at the end.
   */
  INLINE void BeginPush();
  /**
   * Multiple Pushes: Note that in mono thread context you can use this method 
   *                  without BeginPush and EndPush
   */
  INLINE HRESULT FastPush(const T_Element & oElement);
  /**
   * Multiple Pushes: Mutex can be locked only once for a lot of pushed elements
   * Call BeginPush, then n FastPush and EndPush at the end.
   */
  INLINE void EndPush();

  /**
   * Multiple Pops: Mutex can be locked only once for a lot of popped elements
   * Call BeginPop, then n FastPop and EndPop at the end. To be used when pops
   * and pushes happen together during the same transaction.
   */
  INLINE void BeginPop();
  /**
   * Mono-thread: Note that in mono thread context you can use this method 
   *              without BeginPop and EndPop
   * Multi-thread: In an ONLY POPS context (say if stack has been filled before
   *               and is now emptied by several threads), you can use this Pop
   *               method safely.
   */
  INLINE HRESULT FastPop(T_Element & oElement);
  /**
   * Multiple Pops: Mutex can be locked only once for a lot of popped elements
   * Call BeginPop, then n FastPop and EndPop at the end.
   */
  INLINE void EndPop();
  
  /**
   * Pops a previously added element (first in, first out)
   * and gives you a pointer to it for you to edit it.
   * Element can be modified in place. You can then
   * reset the stack and when going through it again you
   * will have access to the modified element.
   * Important note: Pop is thread safe but edit of the
   * element might NOT be.
   *@return
   *     S_OK: Valid element is popped.
   *     S_FALSE: Their is no more elements in the stack, but some will
   *       possibly be pushed later (only if parameter iWaitForPop is
   *       set to FALSE in the constructor).
   *     E_FAIL: Empty stack, nothing is done.
   */
  INLINE HRESULT PopAndEdit(T_Element *& oElement);

  /**
   * Sends the add event only every nth Push call. Better for performances, provided
   * - Push events happen really regularly (so the waiting thread does not wait too much)
   * - SetFinish is called at the end of the filling (this is mandatory)
   * @param iFrequency default is to always send the add event.
   */
  INLINE void SetAddEventFrequency(int iFrequency = -1){m_AddEventFrequency = iFrequency;}

  /**
   * Returns the add event, sent whenever a push transaction ends.
   */
#ifdef USECATEVENTS
  INLINE CATEvent * GetAddEvent();
#else
  INLINE CATWaitingPoint & GetAddEvent();
#endif

protected:
  /**
   * Copy an input stack into this one.
   * Previous stack is LOST. It uses memcpy so use it at your own risks.
   */
  INLINE CATThreadSafeStack<T_Element> & Copy(const CATThreadSafeStack<T_Element> & iCopy);

  void DestroyPools();

private:
  CATBoolean _WaitForPop;

  int _PoolSize; // size of one pool
  int _SizePoolsBuf; // size of the buffers which contains the pools

  T_Element ** _PoolsBuf; // pools buffer
  T_Element * _CurrentPushPool; // current pools buffer
  int _CurrentIndexInCurrentPushPool;
  int _CurrentPushPoolIndex;
  int _NbPools; // Number of pools allocated in the pools buffer
  int _NbElements; // Total number of elements pushed in the stack

  int _CurrentElement; // Next element to iterate on
  int m_AddEventFrequency;

  // Thread safe stack
  CATBoolean _finish;
  CATMutex _mutex;

#ifdef USECATEVENTS
  CATEvent * m_event;
#else
  CATWaitingPoint _add;
#endif
};

template <class T_Element>
INLINE CATThreadSafeStack<T_Element>::CATThreadSafeStack(const CATBoolean iWaitForPop, int PoolSize)
  : _WaitForPop(iWaitForPop),
#ifdef USECATEVENTS
  m_event(CreateCATEvent(0)),
#else
  _add(0, 1),
#endif
  _finish(FALSE)
{
  _PoolSize = PoolSize;
  _SizePoolsBuf = 512;

  _PoolsBuf = NULL;
  _CurrentPushPool = NULL;
  _CurrentIndexInCurrentPushPool = -1;
  _CurrentPushPoolIndex = 0;
  _NbPools = 0;
  _NbElements = 0;

  _CurrentElement = 0;

  m_AddEventFrequency = -1;
}

template <class T_Element>
INLINE CATThreadSafeStack<T_Element>::~CATThreadSafeStack()
{
  DestroyPools();
  _PoolsBuf = NULL;
  _CurrentPushPool = NULL;
  _CurrentIndexInCurrentPushPool = -1;
  _CurrentPushPoolIndex = 0;
  _NbPools = 0;
  _NbElements = 0;
#ifdef USECATEVENTS
  delete m_event;
  m_event = 0;
#endif
}

template <class T_Element>
void CATThreadSafeStack<T_Element>::BeginPush()
{
  CATMutexFastLock(&_mutex);
}

template <class T_Element>
HRESULT CATThreadSafeStack<T_Element>::Push(const T_Element & oElement)
{
  BeginPush();
  HRESULT ret = FastPush(oElement);
  EndPush();
  return ret;
}

template <class T_Element>
HRESULT CATThreadSafeStack<T_Element>::FastPush(const T_Element & oElement)
{
  _CurrentIndexInCurrentPushPool++;
  _NbElements++; // _CurrentPushPoolIndex * _PoolSize + _CurrentIndexInCurrentPushPool + 1
  if(_CurrentIndexInCurrentPushPool < _PoolSize)
  {
    if(NULL == _CurrentPushPool)
    {
      // Current pool is NULL, we create a new pool
      if (NULL == _PoolsBuf) {
        _PoolsBuf = new T_Element * [_SizePoolsBuf];
        memset(_PoolsBuf, NULL, _SizePoolsBuf * sizeof(T_Element *));
      }
      _CurrentPushPoolIndex = _NbPools;
      _PoolsBuf[_CurrentPushPoolIndex] = _CurrentPushPool = new T_Element[_PoolSize];

      /**
      * Reallocation in case...
      */
      _NbPools++;
      if (_NbPools >= _SizePoolsBuf) {
        int newnbofpools = _SizePoolsBuf * 2;
        T_Element ** tmppool = new T_Element * [newnbofpools];
        memcpy(tmppool, _PoolsBuf, _SizePoolsBuf * sizeof(T_Element *));
        delete [] _PoolsBuf;
        _PoolsBuf = tmppool;
        tmppool = NULL;
        _SizePoolsBuf = newnbofpools;
      }
    }

    // Perfect
    // Most of the time we should go there with only 2 tests and 2 ++
    _CurrentPushPool[_CurrentIndexInCurrentPushPool] = oElement;
    return S_OK;
  }
  else
  {
    // Next pool !
    _CurrentPushPoolIndex++;
    _CurrentIndexInCurrentPushPool = 0;
    if (NULL == _PoolsBuf)
    {
      _PoolsBuf = new T_Element * [_SizePoolsBuf];
      memset(_PoolsBuf, NULL, _SizePoolsBuf * sizeof(T_Element *));
    }
    if(_CurrentPushPoolIndex < _SizePoolsBuf)
    {
      _CurrentPushPool = _PoolsBuf[_CurrentPushPoolIndex];
      if(NULL == _CurrentPushPool)
      {
        _NbPools++;
        _PoolsBuf[_CurrentPushPoolIndex] = _CurrentPushPool = new T_Element[_PoolSize];
      }
    }
    else
    {
      _NbPools++;
      int newnbofpools = _SizePoolsBuf * 2;
      T_Element ** tmppool = new T_Element * [newnbofpools];
      memcpy(tmppool, _PoolsBuf, _SizePoolsBuf * sizeof(T_Element *));
      memset(tmppool+_SizePoolsBuf, NULL, _SizePoolsBuf * sizeof(T_Element *));
      delete [] _PoolsBuf;
      _PoolsBuf = tmppool;
      tmppool = NULL;
      _SizePoolsBuf = newnbofpools;

      _PoolsBuf[_CurrentPushPoolIndex] = _CurrentPushPool = new T_Element[_PoolSize];
    }

    _CurrentPushPool[_CurrentIndexInCurrentPushPool] = oElement;
    return S_OK;
  }
}

template <class T_Element>
INLINE void CATThreadSafeStack<T_Element>::EndPush()
{
  CATMutexFastUnlock(&_mutex);
  if(m_AddEventFrequency < 0 || (0 == (_NbElements%m_AddEventFrequency)))
#ifdef USECATEVENTS
    if(m_event)
      m_event->SetEvent();
#else
    _add.Broadcast();
#endif
}

template <class T_Element>
void CATThreadSafeStack<T_Element>::BeginPop()
{
  CATMutexFastLock(&_mutex);
  if (_WaitForPop)
    while(_CurrentElement == _NbElements && _finish == FALSE) {
      CATMutexFastUnlock(&_mutex);
#ifdef USECATEVENTS
      WaitForSingleEvent(m_event, 100);
#else
      _add.Wait();
#endif
      CATMutexFastLock(&_mutex);
      if(_CurrentElement < _NbElements || _finish)
        break;
#ifdef DEBUGSTACK
      else
        cout << "@";
#endif
    }
}
template <class T_Element>
void CATThreadSafeStack<T_Element>::EndPop()
{
  if(_CurrentElement == _NbElements)
#ifdef USECATEVENTS
    if(m_event)
      m_event->ResetEvent();
#else
    _add.Reset();
#endif
  CATMutexFastUnlock(&_mutex);
}
template <class T_Element>
HRESULT CATThreadSafeStack<T_Element>::Pop(T_Element & oElement)
{
  BeginPop();
  HRESULT ret = FastPop(oElement);
  EndPop();
  return ret;
}

template <class T_Element>
HRESULT CATThreadSafeStack<T_Element>::FastPop(T_Element & oElement)
{
  if (_CurrentElement >= _NbElements && _finish == FALSE) {
    return S_FALSE;
  }
  if (_PoolsBuf) {
    int curelem = CATPolyAtomicOperations::Increment(&_CurrentElement) - 1;

    if (curelem < _NbElements) {
      int currentpoolindex = curelem/_PoolSize;
      int indexincurrentpool = curelem - currentpoolindex * _PoolSize;
      T_Element * _curPool = _PoolsBuf[currentpoolindex];
      if (NULL != _curPool) {
        oElement = _curPool[indexincurrentpool];
        return S_OK;
      }
    }
    else
    {
      CATPolyAtomicOperations::Decrement(&_CurrentElement);
    }
  }
  return E_FAIL;
}

template <class T_Element>
HRESULT CATThreadSafeStack<T_Element>::PopAndEdit(T_Element *& oElement)
{
  BeginPop();
  HRESULT HR = E_FAIL;
  if (_CurrentElement >= _NbElements && _finish == FALSE) {
    HR = S_FALSE;
  }
  else if (_PoolsBuf) {
    int curelem = (++_CurrentElement) - 1;
    if (curelem < _NbElements) {
      int currentpoolindex = curelem/_PoolSize;
      int indexincurrentpool = curelem - currentpoolindex * _PoolSize;
      T_Element * _curPool = _PoolsBuf[currentpoolindex];
      if (NULL != _curPool) {
        oElement = _curPool+indexincurrentpool;
        HR = S_OK;
      }
    }
    else
    {
      --_CurrentElement;
    }
  }
  EndPop();
  return HR;
}

template <class T_Element>
INLINE int CATThreadSafeStack<T_Element>::FullSize()
{
#ifdef _WINDOWS_SOURCE
  return _NbElements;
#else
  CATMutexFastLock(&_mutex);
  int nbelems = _NbElements;
  CATMutexFastUnlock(&_mutex);
  return nbelems;
#endif
}

template <class T_Element>
INLINE int CATThreadSafeStack<T_Element>::QueueSize()
{
#ifdef _WINDOWS_SOURCE
  return _NbElements - _CurrentElement;
#else
  CATMutexFastLock(&_mutex);
  int nbelems = _NbElements - _CurrentElement;
  CATMutexFastUnlock(&_mutex);
  return nbelems;
#endif
}

template <class T_Element>
INLINE void CATThreadSafeStack<T_Element>::Empty()
{
  CATMutexFastLock(&_mutex);
  DestroyPools();
  _CurrentPushPool = NULL;
  _CurrentIndexInCurrentPushPool = -1;
  _CurrentPushPoolIndex = 0;
  _PoolsBuf = NULL;
  _NbPools = 0;
  _NbElements = 0;
  _CurrentElement = 0;
  _finish = FALSE;
  CATMutexFastUnlock(&_mutex);
}
template <class T_Element>
INLINE void CATThreadSafeStack<T_Element>::EmptyWithoutRelease()
{
  CATMutexFastLock(&_mutex);
  _CurrentIndexInCurrentPushPool = -1;
  _CurrentPushPoolIndex = 0;
  _NbElements = 0;
  _CurrentElement = 0;
  _CurrentPushPool = NULL;
  if(NULL != _PoolsBuf)
    _CurrentPushPool = _PoolsBuf[0];
  _finish = FALSE;
  CATMutexFastUnlock(&_mutex);
}

template <class T_Element>
INLINE void CATThreadSafeStack<T_Element>::Reset()
{
  CATMutexFastLock(&_mutex);
  if (_finish && _CurrentElement >= _NbElements) {
    _CurrentElement = 0;
  }
  CATMutexFastUnlock(&_mutex);
}

template <class T_Element>
void CATThreadSafeStack<T_Element>::DestroyPools()
{
  if (NULL != _PoolsBuf) {
    int i = 0;
    for (i = 0; i < _NbPools; i++) {
      T_Element * pool = _PoolsBuf[i];
      if(NULL != pool)
        delete [] pool;
    }
    delete [] _PoolsBuf;
  }
  _CurrentPushPool = NULL;
  _CurrentIndexInCurrentPushPool = -1;
  _CurrentPushPoolIndex = 0;
  _PoolsBuf = NULL;
  _NbPools = 0;
  _NbElements = 0;
}

template <class T_Element>
INLINE void CATThreadSafeStack<T_Element>::SetFinish(CATBoolean finish)
{
  CATMutexFastLock(&_mutex);
  _finish = finish;
  CATMutexFastUnlock(&_mutex);
#ifdef USECATEVENTS
  if(m_event)
    m_event->SetEvent();
#else
  _add.Broadcast();
#endif
}

template <class T_Element>
INLINE CATBoolean CATThreadSafeStack<T_Element>::GetFinish()
{
  return _finish;
}

template <class T_Element>
#ifdef USECATEVENTS
INLINE CATEvent * CATThreadSafeStack<T_Element>::GetAddEvent()
{
  return m_event;
}
#else
INLINE CATWaitingPoint & CATThreadSafeStack<T_Element>::GetAddEvent()
{
  return _add;
}
#endif

template <class T_Element>
INLINE CATThreadSafeStack<T_Element> & CATThreadSafeStack<T_Element>::Copy(const CATThreadSafeStack<T_Element> & iCopy)
{
  CATMutexFastLock(&_mutex);
  DestroyPools();
  
  _WaitForPop = iCopy._WaitForPop;
  _finish = TRUE;

  _PoolSize = iCopy._PoolSize;
  _SizePoolsBuf = iCopy._SizePoolsBuf;
  _CurrentElement = iCopy._CurrentElement;
  _NbPools = iCopy._NbPools;
  _NbElements = iCopy._NbElements;

  /**
   * Optimization in case we copy a very small stack
   * (Note that in this case the Push method could suffer some performances pbs if
   * Size becomes very large.)
   */
  if(1 <= _NbElements && _NbElements < _PoolSize && 1 == _NbPools)
  {
    _PoolSize = _NbElements;
  }

  /**
   * Pool copy...
   */
  _PoolsBuf = NULL;
  if(NULL != iCopy._PoolsBuf)
  {
    _PoolsBuf = new T_Element * [_SizePoolsBuf];
    memset(_PoolsBuf, 0, _SizePoolsBuf * sizeof(T_Element *));
    int i = 0;
    for(i = 0; i < _NbPools; i++)
    {
      if(NULL != iCopy._PoolsBuf[i])
      {
        _PoolsBuf[i] = new T_Element[_PoolSize];
        memcpy(_PoolsBuf[i], iCopy._PoolsBuf[i], _PoolSize * sizeof(T_Element));
        if(i == _NbPools - 1)
        {
          _CurrentPushPool = _PoolsBuf[i];
          _CurrentPushPoolIndex = i;
          _CurrentIndexInCurrentPushPool = _NbElements - _CurrentPushPoolIndex * _PoolSize - 1;
        }
      }
    }
  }
  /**
   * Mutex is NOT copied
   */
  CATMutexFastUnlock(&_mutex);
  return *this;
}

template <class T_Element>
INLINE CATThreadSafeStack<T_Element>::CATThreadSafeStack(const CATThreadSafeStack<T_Element> & iCopy):
_WaitForPop(FALSE),
#ifdef USECATEVENTS
  m_event(CreateCATEvent(0)),
#else
  _add(0, 1),
#endif
  _finish(FALSE)
{
  _PoolSize = 0;
  _SizePoolsBuf = 512;

  _PoolsBuf = NULL;
  _CurrentPushPool = NULL;
  _CurrentIndexInCurrentPushPool = -1;
  _CurrentPushPoolIndex = 0;
  _NbPools = 0;
  _NbElements = 0;

  _CurrentElement = 0;
  m_AddEventFrequency = -1;
  Copy(iCopy);
}
template <class T_Element>
INLINE CATThreadSafeStack<T_Element> & CATThreadSafeStack<T_Element>::operator = (const CATThreadSafeStack<T_Element> & iCopy)
{
  Copy(iCopy);
  return *this;
}


#endif // !CATThreadSafeStack_H
