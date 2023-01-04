#ifndef CATCGMCreateGeodesicLinePtPt_h_
#define CATCGMCreateGeodesicLinePtPt_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"

class CATBody;
class CATGeoFactory;
class CATTopData;
class CATICGMTopGeodesicPtPt;

/**
 * Constructs the CATICGMTopGeodesicPtPt operator. The CATICGMTopGeodesicPtPt operator
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
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMTopGeodesicPtPt *CATCGMCreateGeodesicLinePtPt(
  CATGeoFactory *iFacto,
  CATTopData *iData,
  CATBody *iPtOrig,
  CATBody *iPtFin,
  CATBody *iShellSupport);

#endif /* CATCGMCreateGeodesicLinePtPt_h_ */
