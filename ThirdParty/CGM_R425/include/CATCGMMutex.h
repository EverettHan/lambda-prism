#ifndef CATCGMMutex_h
#define CATCGMMutex_h
/* -*-C++-*-*/
//==========================================================================
//
// COPYRIGHT DASSAULT SYSTEMES 1999
//
//==========================================================================
//
// Interface defining class used for mutex (locks for multi thread usage).
//
//==========================================================================
// 22/09/08 NLD Ajout _protected_threadmode pour perfos
// 17/03/21 NLD Revue des macros
//              - Dans version historique,
//                Ajout volatile pour compatibilité exceptions
//              - dans version active avec _protected_threadmode,
//                recalcul à chaque Lock() pour compatibilité avec utilisation
//                d'un mutex statique
//==========================================================================

#include "ExportedByCATMathStream.h"
#include "CATMutex.h"
#include "CATCGMThreadManager.h"
#include "CATErrorMacros.h"

// #define CATCGMMutex_BeforeOptimNLD "essai de restauration ancien code; NLD110321"

//==========================================================================
class ExportedByCATMathStream CATCGMMutex
{
public :
  CATCGMMutex();
  virtual      ~CATCGMMutex();

  // Acquiring a lock on the mutex
           void Lock();

  // Releasing a lock on the mutex
           void Unlock();

private :
  CATMutex      _mutex;
  CATThreadsId  _thread_id;
  CATULONG32    _locked;
public :
  int           _protected_threadmode ; // do NOT use directly outside class or outside following macros
};

//==========================================================================
// N.B history for macros
// V0 inquire for GetMode() at each use, definition of local variable ThreadMode
//    in calling code
// V1 switch to _protected_threadmode
//    global _protected_threadmode: query only at creation
// V2 because of some CATCGMMutex static instances,
//    (in CATCGMGeometry for subscribe, CATSurfaceCGM for equations lock, ...)
//    it is safer
//    to re-do a GetMode() query at each Lock
//==========================================================================

#ifdef CATCGMMutex_BeforeOptimNLD

// Standard code
#define CATCGMLock(MUTEX)                                    \
int volatile ThreadMode = CATCGMThreadManager::GetMode();    \
if (ThreadMode)                                              \
   MUTEX.Lock()

#define CATCGMUnlock(MUTEX)                                  \
if (ThreadMode)                                              \
   MUTEX.Unlock()

#else

// Optimized code
#define CATCGMLock(MUTEX)                                    \
MUTEX._protected_threadmode = CATCGMThreadManager::GetMode();\
if (MUTEX._protected_threadmode)                             \
   MUTEX.Lock()

#define CATCGMUnlock(MUTEX)                                  \
if (MUTEX._protected_threadmode)                             \
   MUTEX.Unlock()
#endif


#ifdef CATCGMMutex_BeforeOptimNLD

// Standard code
#define CATCGMLockThrowSafe(MUTEX)                           \
int volatile ThreadMode = CATCGMThreadManager::GetMode();    \
if (ThreadMode)                                              \
   MUTEX.Lock();                                             \
CATTry                                                       \
{

#define CATCGMUnlockThrowSafe(MUTEX)                         \
}                                                            \
CATCatchOthers                                               \
{                                                            \
   if (ThreadMode)                                           \
      MUTEX.Unlock();                                        \
   CATRethrow;                                               \
}                                                            \
CATEndTry;                                                   \
if (ThreadMode)                                              \
   MUTEX.Unlock();

#else

// Optimized code
#define CATCGMLockThrowSafe(MUTEX)                           \
MUTEX._protected_threadmode = CATCGMThreadManager::GetMode();\
if (MUTEX._protected_threadmode)                             \
   MUTEX.Lock();                                             \
CATTry                                                       \
{


#define CATCGMUnlockThrowSafe(MUTEX)                         \
}                                                            \
CATCatchOthers                                               \
{                                                            \
   if (MUTEX._protected_threadmode)                          \
      MUTEX.Unlock();                                        \
   CATRethrow;                                               \
}                                                            \
CATEndTry;                                                   \
if (MUTEX._protected_threadmode)                             \
   MUTEX.Unlock();
#endif


#endif

