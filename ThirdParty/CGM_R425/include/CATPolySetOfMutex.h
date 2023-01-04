// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySetOfMutex
//
//===================================================================
// 2010-03-26   JXO
//      * New
//===================================================================
#ifndef CATPolySetOfMutex_H
#define CATPolySetOfMutex_H

// Poly
#include "PolyMultiThreading.h"
#define POLYNBMUTEXMAX 16
#include "CATPolyMutex.h"

// Poly Math
#define POLYMUTEXUSEHASHTABLE
#ifdef POLYMUTEXUSEHASHTABLE
#include "CATMapOfPtrToPtr.h"
#endif
#define POLYMUTEXCATMUTEX

// System
#include "CATMutex.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

class ExportedByPolyMultiThreading CountedMutex
{
public:
  CountedMutex(){_n=0;_p=NULL;}
  ~CountedMutex(){}
  int RemRef(){if(_n<=1){_p=NULL;} return --_n;}
  void AddRef(const void * ptr){++_n;_p=ptr;}
public:
  CATMutex _mut;
  const void * _p;
  int _n;
};

#include "CATThreadSafeStack.h"

/**
 * With this magic class, 
 */
class ExportedByPolyMultiThreading CATPolySetOfMutex
{
public:
  /**
   * Basic constructor and destructor
   */
  CATPolySetOfMutex ():_nbfree(POLYNBMUTEXMAX),m_freemutex(FALSE, 64){}
#ifndef POLYMUTEXUSEHASHTABLE
  ~CATPolySetOfMutex (){}
#else
  ~CATPolySetOfMutex ();
#endif

  /**
   * Locks a mutex dedicated to this void *
   */
  void Lock(const void * ID);

  /**
   * Unlocks dedicated mutex
   */
  void Unlock(const void * ID);


private:
#ifdef POLYMUTEXCATMUTEX
  CATMutex             _spinMap;
#else
  CATPolySpinLockMutex _spinMap;
#endif
  CountedMutex _muts[POLYNBMUTEXMAX];
#ifdef POLYMUTEXUSEHASHTABLE
  CATMapOfPtrToPtr m_mapofmuts;
  CATThreadSafeStack<CountedMutex*> m_freemutex;
#endif
  CATMutex _mutInCaseOfEmergency;
  CATLONG32 _nbfree;
};

#endif
