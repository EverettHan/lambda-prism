#ifndef CATCGMCreateTopGeodesicDistanceTool_h_
#define CATCGMCreateTopGeodesicDistanceTool_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATIACGMLevel.h"

#include "CATGMOperatorsInterfaces.h"
#include "CATMathDef.h"
#include "CATTopDefine.h"
#include "CATCompositeLaw.h"

class CATICGMDistanceTool;
class CATGeoFactory;
class CATTopData;

/**
 * Constructs the object for the geodesic computation.
 * @param iGeoFactory
 * The pointer to geometry factory.
 * @param iData
 * The pointer to the CATTopData.
 * @param iOrientation
 * The side on which the parallel is computed.
 * The cross product between the shell normal and the wire tangent define the
 * left side.
 * <br><b>Legal values </b>: <tt>CATOrientationPositive</tt> for the left side,
 * <tt>CATOrientationNegative</tt> for the right side.
 * @param iDistance
 * The pointer to the law defining the parallel offset.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method afer use.
 */
#ifndef CATIACGMR214CAA
ExportedByCATGMOperatorsInterfaces CATICGMDistanceTool *CATCGMCreateTopGeodesicDistanceTool(
  CATGeoFactory *iGeoFactory,
  CATTopData *iData,
  CATOrientation iOrientation,
  CATCompositeLaw *iDistance);
#else
ExportedByCATGMOperatorsInterfaces CATICGMDistanceTool *CATCGMCreateTopGeodesicDistanceTool(
  CATGeoFactory *iGeoFactory,
  CATTopData *iData,
  CATOrientation iOrientation,
  CATLaw *iDistance);
#endif

#endif /* CATCGMCreateTopGeodesicDistanceTool_h_ */
