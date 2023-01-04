#ifndef CATSysMTGlobalMutex_H
#define CATSysMTGlobalMutex_H

// COPYRIGHT DASSAULT SYSTEMES  2000
/**
 **   reserved for use to Vault and CORBARuntime services
 **/
#include "JS0MT.h"
#include "CATSysDataType.h"
#include "CATMutex.h"
#include "CATResourceLock.h"
#include <stdlib.h>

#define CATSysMTGMLock    0x1
#define CATSysMTGMUnlock  0x2

/***
 ** allows to obtain the central mutex for Vault and CORBARuntime
 ** reserved for use to Vault and CORBARuntime services
 **
 **  USAGE :
 **    CATSysMTGlobalMutex( CATSysMTGMLock );
 **    .. protected section .. 
 **    CATSysMTGlobalMutex( CATSysMTGMUnlock );
 **
 **  return 1 if locked 
 **  return 0 if unlocked
 **  return <0 if error occured
 **
 **/
ExportedByJS0MT  int CATSysMTGlobalMutex( int lMode,  const char *iId=NULL, int iKey=0);

#define THREAD_UNSAFE_CREATION 0x00000000
#define THREAD_SAFE_CREATION 0x00000001


/**
* @deprecated R421 Rather use C++11 atomic fence or even better: std::atomic/std::atomic_ref with explicit 'std::memory_order' parameters.
*	Declared here for compatibility reasons. 
**/
ExportedByJS0MT void DSYMemoryBarrier();

/**
* @deprecated R421 Use C++11 thread-safe static initialization or std::call_once...
*   => Not thread-safe, removed in R424
*	Create a CATMutex object if the provided pointer is null at creation time
*	This factory allows protected mutex creation as data member without worrying 
*   about locking the creation itself or making it static
*	The created mutex is not locked.
*/
//ExportedByJS0MT void DSYCreateMutex(CATMutex *& iopMutex, DWORD iMode=THREAD_SAFE_CREATION);

/**
* @deprecated R421 Use C++11 thread-safe static initialization or std::call_once...
*   => Not thread-safe, removed in R424 
*	Create a CATResourceLock object if the provided pointer is null at creation time
*	This factory allows protected mutex creation as data member without worrying 
*   about locking the creation itself or making it static
*	The created mutex is not locked.
*/
// ExportedByJS0MT void DSYCreateResourceLock(CATResourceLock *& iopMutex, DWORD iMode=THREAD_SAFE_CREATION);


#endif
