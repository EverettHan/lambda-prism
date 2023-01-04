#ifndef CATSURLIMITSUTILITIES_H
#define CATSURLIMITSUTILITIES_H

//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 2007
//
// CATSurLimits utilities
//
//=============================================================================
//
// History
//
// 08/08/07 NLD Creation.
// 14/11/07 PTO Chgt ExportedBy pour eviter cycle entre CATGeometricObjects.dll
//              et CATCGMGeoMath.dll (utilisation CATGetTolerance)
// 24/01/08 NLD Ajout IsContainingForSurLimits()
// 28/04/21 Q48 Make SurLimits etc const for ease of use in SurSurGen
//=============================================================================

#include "YP00IMPL.h"
#include "CATSurLimits.h"
#include "CATSurface.h"

// using IsEqualUForSurLimits/IsEqualVForSurLimits avoids using IsEqualU/IsEqualV tests non XScale compliants in CATSurLimits
extern "C" CATLONG32 ExportedByYP00IMPL IsEqualUForSurLimits(const CATSurLimits& iLimits1,
                                                             const CATSurLimits& iLimits2,
                                                             const CATSurface* iSurface) ;
extern "C" CATLONG32 ExportedByYP00IMPL IsEqualVForSurLimits(const CATSurLimits& iLimits1,
                                                             const CATSurLimits& iLimits2,
                                                             const CATSurface* iSurface) ;
extern "C" CATLONG32 ExportedByYP00IMPL IsContainingForSurLimits(
                  const CATSurLimits            & iBox1,
                  const CATSurLimits            & iBox2,
                  CATSurface*                     iSurface,
                  CATMathTransformation2D & ioTransfo2D,
                  double                    iPeriodU,
                  double                    iPeriodV,
                  double                    iTol       );

#endif
