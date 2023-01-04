#ifndef CATCGMInterrupt_H
#define CATCGMInterrupt_H
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2011
//==========================================================================
//
// interruption management (dedicated error)
//
//==========================================================================
// 03/07/20 NLD R424 nouveau protocole de CATCGMInterrupt_Throw()
//              (sans renommage en CATCGMInterrupt_OnBeforeThrow())
//              (IK8/NLD)
//==========================================================================
#include <stdlib.h>
#include <stddef.h>

#include "CATMathematics.h"
#include "CATErrorMacros.h"
#include "CATBoolean.h"

#include "CATCGMThrow.h"
#include "CATCGMInputError.h"

/*
  CATCGMIsInterruptError)  Check is error is an Interrupt Error
  CATCGMInterruptError)    Throw an interrupt error
  CATCGMInterruptCreation) Create an interruption error
*/
  
ExportedByCATMathematics CATError * CATCGMInterruptCreation();

ExportedByCATMathematics CATBoolean CATCGMIsInterruptError(CATError *iError); 

#define CATCGMInterruptError() CATCGMThrow( CATCGMInterruptCreation() )

// Internals
class CATInputError;

// CAUTION:
//          - RESTRICTED USE
//          - according to system implementation, CATCGMInterrupt_OnBeforeThrow()/CATCGMInterrupt_Throw()
//            may NOT raise iError, and must be, in this case, considered only as
//            a tooling and breakpoint help
//            Hence, please add a Throw in sequence, in calling code
//            NLD030720 (IK8 + NLD new implementation)
//            NLD080720 no more ptr_to_delete argument (unification R424 and other levels)
void CATCGMInterrupt_Throw        (CATInputError *iError, const char *loc, int line);

#endif

