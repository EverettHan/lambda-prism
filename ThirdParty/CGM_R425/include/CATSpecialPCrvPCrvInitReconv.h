#ifndef CATSpecialPCrvPCrvInitReconv_h
#define CATSpecialPCrvPCrvInitReconv_h

// ---------------------------------------------------------------------------------
// Please do not use this function. Use the CATSpecialPCrvPCrvInitReconvOp operator.
// ---------------------------------------------------------------------------------

// The following function is a simple utility dedicated to finding a stable init for
// the SurSurTg operator in a smooth area in the context of fillet ribbon hermetization.
// In more concrete words, it is similar to PCurve/PCurve intersection with the differences
// that it is dedicated to tangent and nearly tangent configurations, it requires inits
// on the PCurves, a single point solution is always returned (no tolerance, no 
// confusion area, no multiple solutions) and stability is emphasized possibly at the
// expense of accuracy.

#include "Y30C3XGG.h"
#include "CATDataType.h"

class CATPCurve;
class CATCrvLimits;
class CATCrvParam;
class CATSoftwareConfiguration;

// return value:
// 0 : ok
// 1 : failed
ExportedByY30C3XGG CATLONG32 CATSpecialPCrvPCrvInitReconv
  (CATSoftwareConfiguration * iConfig,
   CATPCurve * iPCurve0, CATPCurve * iPCurve1,
   const CATCrvLimits & iCrvLimits0, const CATCrvLimits & iCrvLimits1,
   CATCrvParam & ioPar0, CATCrvParam & ioPar1);

#endif
