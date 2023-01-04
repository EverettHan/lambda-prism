#ifndef CATGetTolerance_H
#define CATGetTolerance_H
//=============================================================================
// COPYRIGHT Dassault Systemes 2005
//=============================================================================
//
// CATGetTolerance.h
// Extract tolerance from CATICGMUnknown
//
/** @CAA2Required */
/**
 * @deprecated V5R21 CATGetTolerance
 */
/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/
#include "CATTolerance.h"
#include "CATICGMUnknown.h"
#include "CATMathInline.h"

#include "CATGeoFactory.h" // to avoid compilation errors

INLINE const CATTolerance & CATGetTolerance(const CATICGMUnknown* iCGMItf)
{ return (iCGMItf) ? iCGMItf->GetToleranceObject() : (::CATGetDefaultTolerance()) ; }
 

#endif // !CATGetTolerance_H
