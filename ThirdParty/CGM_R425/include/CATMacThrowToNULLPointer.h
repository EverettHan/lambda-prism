/* -*-c++-*- */
#ifndef CATMacThrowToNULLPointer_H
#define CATMacThrowToNULLPointer_H
// COPYRIGHT DASSAULT SYSTEMES 2007
//=============================================================================
//
// Macro to catch & flush any thrown error and replace it by a NULL Pointer
//
//=============================================================================
//
// Usage sample:
/*
CATClass* Class::Method()
//-----------------------------------------------------------------------------
{
  CATMacThrowToNULLPointerBegin();

  code without return at end;

  CATMacThrowToNULLPointerEnd(oPointer);
}
*/
//=============================================================================
// Oct. 07   Creation                                               R. Rorato  
//-----------------------------------------------------------------------------
//=============================================================================

#include "IUnknown.h"

#define CATMacThrowToNULLPointerBegin() \
CATTry {

#define CATMacThrowToNULLPointerEnd(oPointer) \
return oPointer; \
} CATCatch(CATError, AnyErrorToNULLPointer) { Flush(AnyErrorToNULLPointer); }; CATEndTry; \
  return NULL;

#endif
