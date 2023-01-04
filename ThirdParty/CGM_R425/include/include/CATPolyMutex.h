// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMutex
//
//===================================================================
// 2010-10-11   JXO
//      * New
//===================================================================
#ifndef CATPolyMutex_H
#define CATPolyMutex_H

#include "CATPolyPool.h"
#include "CATPolyAtomicOperations.h"

// System
#include "CATMutex.h"
#include <string.h>

// ExportedBy
#include "PolyMultiThreading.h"

/**
 * Implementation of tools for mutex management
 */

class ExportedByPolyMultiThreading CATPolySpinLockMutex
{
public:
  INLINE CATPolySpinLockMutex():_c(0)
  {
  }
  INLINE ~CATPolySpinLockMutex()
  {
  }
  INLINE void Lock()
  {
    while (1 == CATPolyAtomicOperations::CompareAndSwap(&_c, 1, 0));
  }
  INLINE void Unlock()
  {
    CATPolyAtomicOperations::CompareAndSwap(&_c, 0, 1);
  }
private:
  int _c;
};

class ExportedByPolyMultiThreading CATPolyScopedMutex
{
public:
 INLINE CATPolyScopedMutex(CATMutex & mut):_mut(&mut),_smut(0)
  {
    CATMutexFastLock(&mut);
  }
  INLINE CATPolyScopedMutex(CATPolySpinLockMutex & smut):_mut(0),_smut(&smut)
  {
    smut.Lock();
  }
  INLINE ~CATPolyScopedMutex()
  {
    if(_mut)CATMutexFastUnlock(_mut);
    if(_smut)_smut->Unlock();
  }
private:
  CATMutex * _mut;
  CATPolySpinLockMutex * _smut;
};


#endif
