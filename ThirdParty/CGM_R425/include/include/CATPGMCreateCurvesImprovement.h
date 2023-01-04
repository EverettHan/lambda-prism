#ifndef CATPGMCreateCurvesImprovement_h_
#define CATPGMCreateCurvesImprovement_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATCollec.h"

class CATCurvesImprovement;
class CATGeoFactory;
class CATLocalizer2DFrom3D;
class CATMathSetOfPoints;
class CATSoftwareConfiguration;
class CATLISTP(CATCrvLimits);
class CATLISTP(CATCurve);

//
// To create an instance of the operator :
// ---------------------------------------
// List of CATCurves must be G0 connected.
// All are : 3D curves or Pcurves on a same shell. No combination is allowed.
//
//---------------------------------------
//       WARNING
//---------------------------------------
//if iSoftwareConfiguration == NULL, then you will use an older version of CurvesImprovement
//
ExportedByCATGMOperatorsInterfaces CATCurvesImprovement *CATPGMCreateCurvesImprovement(
  CATSoftwareConfiguration *iSoftwareConfiguration,
  CATGeoFactory *iFactory,
  const CATLISTP(CATCurve) *iCurvesToImprove,
  const CATLISTP(CATCrvLimits) *iListOfLimits = 0,
  const CATListOfInt *iListOfOrientations = 0);

//
// OBSOLETE CONSTRUCTOR :
//
ExportedByCATGMOperatorsInterfaces CATCurvesImprovement *CATPGMCreateCurvesImprovement(
  CATGeoFactory *iFactory,
  const CATLISTP(CATCurve) *iCurvesToImprove,
  const CATLISTP(CATCrvLimits) *iListOfLimits = 0,
  const CATListOfInt *iListOfOrientations = 0);

#endif /* CATPGMCreateCurvesImprovement_h_ */
