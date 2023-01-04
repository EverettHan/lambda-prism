#ifndef CATCGMCreateInterproxCrv_h_
#define CATCGMCreateInterproxCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATCollec.h"
#include "CATSkillValue.h"

class CATCurve;
class CATGeoFactory;
class CATICGMInterproxCrv;
class CATMathSetOfPointsND;
class CATMathSetOfVectors;
class CATSoftwareConfiguration;
class CATLISTP(CATCurve);

/**
 * Creates the operator that deforms curves on a set of points.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iConfig
 * The pointer to configuration defining the level of code to replay.
 * @param iListe
 * The list of pointers to the curves to deform.
 * @param iPoints
 * The pointer to the set of points on which the curves are deformed.
 * @param iVectors
 * To keep to <tt>0</tt>.
 * @param iTension
 * The tension.
 * @param iSmoothness
 * The smoothness.
 * @param iTolapp
 * Always keep to the factory resolution.
 * @param iImposition
 * The array [2] defining the type of constraints at each extremities of the deformed curve.
 * <br><b>Legal values</b>: <tt>0</tt> if a G0 continuity with the input curve is required, 
 * <tt>1</tt> for a G1 continuity, <tt>2</tt> for a G1 continuity.
 * @param iMode
 * The mode of use.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 * @see CATInterproxCrv
 */
ExportedByCATGMOperatorsInterfaces CATICGMInterproxCrv *CATCGMCreateInterproxCrv(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATLISTP(CATCurve) &iListe,
  const CATMathSetOfPointsND *iPoints,
  const CATMathSetOfVectors *iVectors,
  double &iTension,
  double &iSmoothness,
  double &iTolapp,
  const int iImposition[2],
  CATSkillValue iMode = BASIC);

#endif /* CATCGMCreateInterproxCrv_h_ */
