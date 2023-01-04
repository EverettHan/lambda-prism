#ifndef CATCGMCreateInterproxSur_h_
#define CATCGMCreateInterproxSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATCollec.h"
#include "CATSkillValue.h"

class CATFrFCompositeSurface;
class CATGeoFactory;
class CATICGMInterproxSur;
class CATMathDirection;
class CATMathSetOfPointsND;
class CATMathSetOfVectors;
class CATNurbsSurface;
class CATSoftwareConfiguration;
class CATLISTP(CATSurface);

#ifndef NULL
#define NULL 0
#endif

/**
 * Creates the operator that deforms surfaces on a set of points.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iConfig
 * The pointer to configuration defining the level of code to replay.
 * @param iListe
 * The list of pointers to the surfaces to deform.
 * @param iPoints
 * The pointer to the set of points (of dimension 3) on which the curves are deformed.
 * @param iVectors
 * To keep to <tt>0</tt>.
 * @param iTension
 * The tension.
 * @param iSmoothness
 * The smoothness.
 * @param iTolapp
 * Always keep to the factory resolution.
 * @param iImposition
 * The array [4*Nbsur] defining the type of constraints at each extremities of the deformed surface.
 * The array is filled as follows, for the input surfaces from <tt>0 <= i < Nbsur</tt>:
 * <ul>
 * <li><tt>iImposition[0+4*i]</tt> for the iso-parametric boundary <tt>v=0</tt> of the <tt>i-</tt>th surface.
 * <li><tt>iImposition[1+4*i]</tt> for the iso-parametric boundary <tt>u=0</tt> of the <tt>i-</tt>th surface.
 * <li><tt>iImposition[2+4*i]</tt> for the iso-parametric boundary <tt>v=vmax</tt> of the <tt>i-</tt>th surface.
 * <li><tt>iImposition[3+4*i]</tt> for the iso-parametric boundary <tt>u=umax</tt> of the <tt>i-</tt>th surface.
 * </ul>
 * <br><b>Legal values</b>: <tt>0</tt> for a free boundary,
 * <tt>1</tt> for a C0 continuity with the input surface, 
 * <tt>2</tt> for a C1 continuity, <tt>3</tt> for a C2 continuity.
 * @param iVect
 * The direction of the projection of the points on the surfaces. 
 * @param iMode
 * The mode of use.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 * @see CATICGMInterproxSur
 */
ExportedByCATGMOperatorsInterfaces CATICGMInterproxSur *CATCGMCreateInterproxSur(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATLISTP(CATSurface) &iListe,
  const CATMathSetOfPointsND *iPoints,
  const CATMathSetOfVectors *iVectors,
  double &iTension,
  double &iSmoothness,
  double &tolapp,
  const int *iImposition,
  const CATMathDirection *iVect = NULL,
  CATSkillValue iMode = BASIC);

#endif /* CATCGMCreateInterproxSur_h_ */
