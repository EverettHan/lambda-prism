/**
 * @fullReview JXO NDO 09:12:11
 */

// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyPool
//
//=============================================================================
// 2009-12-11: JXO, new
//=============================================================================
#ifndef CATPolyPool_H
#define CATPolyPool_H

#define NBPOLYPOOLS 16
#define NB2POLYPOOLS 32

#define USE_TBB_MALLOC
#ifdef USE_TBB_MALLOC

#define CATPolyDeclarePooledNew

#else

// Poly
#include "PolyMultiThreading.h"
#include "CATMapOfPtrToPtr.h"
#include "CATThreadSafeStack.h"

// System
#include "CATErrorDef.h"
#include "CATSysAllocator.h"
#include "CATMutex.h"



class CATPolyThreads;

class ExportedByPolyMultiThreading PoolMap
{
public:
  PoolMap(){int i = 0; for(; i < NB2POLYPOOLS; ++i)_p[i] = NULL;}
  ~PoolMap(){int i = 0; for(; i < NB2POLYPOOLS; ++i) _p[i] = NULL;}
public:
  void * _p[NB2POLYPOOLS];
};

class ExportedByPolyMultiThreading CATPolyPool
{
friend class CATPolyThreads;
private:
  CATPolyPool();
  ~CATPolyPool(); 

public:
  static void * GetDefaultPool();
  static void * AllocateObjectInDefaultPool(size_t iSize);
  static void * AllocateObjectInTSPool(size_t iSize);
  static void FreeObjectFromPool(void * iObject);

protected:
  // (this is actually called in CATPolyThreads::CATPolyThreads() so
  // you should not worry calling this function)
  static void RegisterTSPool(void * pTId = NULL);
  // you can call this function at the end of a thread
  // This tells the pool manager that current thread won't allocate
  // anymore. (Usefull to keep the map between Threads and Pools in
  // a decent state)
  // Called in CATPolyThreads::~CATPolyThreads()
  static void ReleaseTSPool(void * pTId = NULL);

private:
  static PoolMap _PtrToPools;
};

#define CATPolyDeclarePooledNew \
public:                                                   \
void *operator new(  size_t iSize)                        \
{                                                         \
  return CATPolyPool::AllocateObjectInTSPool(iSize); \
}                                                         \
void operator delete(void *iAddr)                         \
{                                                         \
  CATPolyPool::FreeObjectFromPool(iAddr);          \
}

#endif

#endif
