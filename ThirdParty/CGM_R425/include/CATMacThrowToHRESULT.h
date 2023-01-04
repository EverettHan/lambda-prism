/* -*-c++-*- */
#ifndef CATMacThrowToHRESULT_H
#define CATMacThrowToHRESULT_H
// COPYRIGHT DASSAULT SYSTEMES 2007
//=============================================================================
//
// Macro to catch & flush any thrown error and replace it by a HRESULT
//
//=============================================================================
//
// Usage sample:
/*
HRESULT Class::Method()
//-----------------------------------------------------------------------------
{
  CATMacThrowToHRESULTBegin();

  code without return at end;

  CATMacThrowToHRESULTEnd(S_OK, E_FAIL);
             or
  CATMacThrowButInterruptedToHRESULTEnd(S_OK, E_FAIL);
}
*/
//=============================================================================
// Sep. 07   Creation                                               R. Rorato  
//-----------------------------------------------------------------------------
//=============================================================================

#include "IUnknown.h"
#include "CATErrorMacros.h"
#include "CATCGMInputError.h"

#define CATMacThrowToHRESULTBegin() \
CATTry {

#define CATMacThrowToHRESULTEnd(oHRESULT_S,oHRESULT_E) \
return oHRESULT_S; \
} CATCatch(CATError, AnyErrorToHRESULT) { Flush(AnyErrorToHRESULT); }; CATEndTry; \
  return oHRESULT_E;

#define CATMacThrowButInterruptedToHRESULTEnd(oHRESULT_S,oHRESULT_E) \
return oHRESULT_S; \
} CATCatch(CATError, AnyErrorToHRESULT) { if ( AnyErrorToHRESULT->IsAKindOf(CATCGMInputError::ClassName()) && AnyErrorToHRESULT->GetId()==110 ) CATRethrow; else Flush(AnyErrorToHRESULT); }; CATEndTry; \
  return oHRESULT_E;

#define IsInterruptError(ErrorToCheck) \
  (ErrorToCheck && ErrorToCheck->IsAKindOf(CATCGMInputError::ClassName()) && ErrorToCheck->GetId()==110)


#endif
