#ifndef __CATSysIsPointerNull
#define __CATSysIsPointerNull
// COPYRIGHT DASSAULT SYSTEMES 2016
/**
* Macro used to test a pointer regardless system version
*/

#include "CATIAV5Level.h"
#ifdef CATIAR419
#include "DSYSysIsPointerNull.h"
#define CATSysIsPointerNull(pPtrToTest) ::DSYSysIsPointerNull((void*)pPtrToTest) 
#else
#define CATSysIsPointerNull(pPtrToTest) (!pPtrToTest)
#endif

#endif
