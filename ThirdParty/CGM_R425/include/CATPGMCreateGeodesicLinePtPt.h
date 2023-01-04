#ifndef CATPGMCreateGeodesicLinePtPt_h_
#define CATPGMCreateGeodesicLinePtPt_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"

class CATBody;
class CATGeoFactory;
class CATTopData;
class CATIPGMTopGeodesicPtPt;

//
/*
 * Constructs the CATIPGMTopGeodesicPtPt operator. 
 * The CATIPGMTopGeodesicPtPt operator
 * creates a geodesic line between two points.
 * @param iFacto
 * A pointer to the factory of the resulting body.
 * @param iData
 * A pointer to the topological data.
 * @param iPtOrig
 * A pointer to start point.
 * @param iPtFin
 * A pointer to end point. 
 * @param iShellSupport
 * A pointer to the support. 
 * @return [out, IUnknown#Release]
 */
//
ExportedByCATGMOperatorsInterfaces CATIPGMTopGeodesicPtPt *CATPGMCreateGeodesicLinePtPt(
  CATGeoFactory *iFacto,
  CATTopData *iData,
  CATBody *iPtOrig,
  CATBody *iPtFin,
  CATBody *iShellSupport);

#endif /* CATPGMCreateGeodesicLinePtPt_h_ */
