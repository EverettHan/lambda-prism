#ifndef CATCRVPARAMUTILITIES_H
#define CATCRVPARAMUTILITIES_H

//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 2007
//
// CATCrvParam utilities
//
//=============================================================================
//
// History
//
// 04/04/07 NLD Creation. IsEqualForCrvParam
// 14/11/07 PTO Chgt ExportedBy pour eviter cycle entre CATGeometricObjects.dll
//              et CATCGMGeoMath.dll (utilisation CATGetTolerance)
// 15/06/09 NLD Argument optionnel iTolObject a IsEqualForCrvParam()
// 20/11/19 Q48 Migration to use const
//=============================================================================

#include "YP00IMPL.h"
#include "CATCrvParam.h"
#include "CATCurve.h"
#include "CATTolerance.h"

// using IsEqualForCrvParam avoids using == or != tests non XScale compliants in CATCrvParam
// using iTolObject optional argument, if already known by caller,  may speed up computation by avoiding
// searching it under iCurve geometric container
// iCurve is not mandatory and may be null if iTolObject specified 
extern "C" const CATLONG32 ExportedByYP00IMPL IsEqualForCrvParam(const CATCrvParam& iParam1, const CATCrvParam& iParam2,
                                                                      const CATCurve* iCurve, const CATTolerance* iTolObject=NULL);

#endif
