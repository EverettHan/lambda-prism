#ifndef CATPGMFrFUtiMonopar_h_
#define CATPGMFrFUtiMonopar_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"

class CATCrvLimits;
class CATCurve;
class CATFrFCCvLimits;
class CATFrFCompositeCurve;
class CATFrFNurbsMultiForm;
class CATGeoFactory;
class CATMathDirection;
class CATMathPoint;
class CATPLine;
class CATSoftwareConfiguration;


//-----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATFrFNurbsMultiForm *CATPGMMakeNurbsCurveClamped(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATLONG32 iOrder,
  const CATLONG32 iKnotSize,
  double *iExtendedKnotVector,
  const CATLONG32 iDim,
  const CATLONG32 iIsRational,
  const CATLONG32 IsPeriodic,
  const CATLONG32 iNumberOfForm,
  const CATLONG32 iNumberOfPole,
  double *iPole,
  double *iWeight,
  const double iTolEqualKnots);

// DEPRECATED, not XScale compliant, will soon disappear, use API with factory and software configuration, above
ExportedByCATGMOperatorsInterfaces CATFrFNurbsMultiForm *CATPGMMakeNurbsCurveClamped(
  const CATLONG32 iOrder,
  const CATLONG32 iKnotSize,
  double *iExtendedKnotVector,
  const CATLONG32 iDim,
  const CATLONG32 iIsRational,
  const CATLONG32 IsPeriodic,
  const CATLONG32 iNumberOfForm,
  const CATLONG32 iNumberOfPole,
  double *iPole,
  double *iWeight,
  const double iTolEqualKnots);


#endif /* CATPGMFrFUtiMonopar_h_ */
