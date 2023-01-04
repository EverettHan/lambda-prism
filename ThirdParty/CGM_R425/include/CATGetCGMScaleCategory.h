#ifndef CATGetCGMScaleCategory_H
#define CATGetCGMScaleCategory_H
//=============================================================================
// COPYRIGHT Dassault Systemes 2012
//=============================================================================
//
// CATGetCGMScaleCategory.h
// Return the scale category of a geofactory.
//
/** @CAA2Required */
/**
 * @deprecated V5R21 CATGetCGMScaleCategory
 */
/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/

//#include "YP00IMPL.h"

#include "CATCGMScaleCategoryDef.h"
#include "CATTolerance.h"
#include "CATICGMUnknown.h"
#include "CATMathInline.h"

#include "CATGeoFactory.h" // to avoid compilation errors
#include "CATGeometry.h" // to avoid compilation errors

INLINE const CATCGMScaleCategory CATGetCGMScaleCategory(const CATICGMUnknown * iCGMItf )
{ 
  const CATTolerance * obj = iCGMItf?(const CATTolerance*) & (iCGMItf->GetToleranceObject()):NULL; 
  return obj?obj->GetScaleCategory():ScaleNotSet;
}
 
#endif // !CATGetScaleCategory_H
