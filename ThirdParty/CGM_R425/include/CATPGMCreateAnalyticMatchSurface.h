#ifndef CATPGMCreateAnalyticMatchSurface_h_
#define CATPGMCreateAnalyticMatchSurface_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATSkillValue.h"

class CATAnalyticMatchSurface;
class CATCrvLimits;
class CATCurve;
class CATGeoFactory;
class CATLaw;
class CATPLine;
class CATPlane;
class CATSoftwareConfiguration;

/**
 * Creates the geometric operator to analytically deform a NURBS surface such that a boundary
 *  of this surface becomes another curve.
 * <br> The parameterization of reference curve or surface (the surface or the curve which 
 * becomes the boundary of the original surface) is kept on the deformed surface.
 * @param iFactory
 * The pointer to the geometry factory.
 * @param iBoundaryToMatch
 * The pointer to the surface boundary to match. The surface must be a NURBS surface.
 * @param iCrvRef
 * The pointer to the curve on which <tt>iCrvMat</tt> is matched.
 * @param iCrvLimRef
 * The limits on <tt>iCrvRef</tt> to take into account.
 * @param iMode
 * The mode of use.
 * @return
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATAnalyticMatchSurface *CATPGMCreateAnalyticMatchSurface(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATPLine *iBoundaryToMatch,
  CATCurve *iCrvRef,
  const CATCrvLimits &iCrvLimRef,
  CATSkillValue iMode = BASIC);

/**
 * Ascending compatibility for client frameworks. This inline function must be deleted once clients call
 * CATPGMCreateAnalyticMatchSurface.
 */
inline CATAnalyticMatchSurface *CreateAnalyticMatchSurface(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATPLine *iBoundaryToMatch,
  CATCurve *iCrvRef,
  const CATCrvLimits &iCrvLimRef,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateAnalyticMatchSurface(iFactory, iConfig, iBoundaryToMatch, iCrvRef, iCrvLimRef, iMode);
}


/**
 * Creates the geometric operator to analytically deform a NURBS surface to make a given 
 * angle with a plane.
 * <br> The orthogonal projection on the plane of the initial NURBS surface boundary must
 * not be self-intersecting.
 * @param iFactory
 * The pointer to the geometry factory.
 * @param iBoundaryToMatch
 * The pointer to the surface boundary to match. The surface must be a NURBS surface.
 * @param iPlane
 * The pointer to the plane.
 * @param iAngularLawMirror
 * The law angle between the surface and the plane. If NULL, the surface arrives normally
 * to the plane.
 * @param iMode
 * The mode of use.
 * @return
 * The pointer to the created operator.
 */
//////////JSX 040407
//////////Pas de config mais 5 ODTs !
//////////Pourqoui ne pas le migrer en meme temps que les autres 
//////////
//////////CATClassAUI.tst TestCases CATClaFeatureTest003
//////////CATClassAUI.tst TestCases CATClaPlaneMatchingTest001
//////////CATClassAUI.tst TestCases TestWkBInit
//////////CGMSurfacicTests.tst TestCases CGMTest_SurfacicMatchMirror_Task1063_N1
//////////FreeStyleShapeUI.tst TestCases FSSSurfaceMatchingOnPlane
//////////
//////////
//////////
ExportedByCATGMOperatorsInterfaces CATAnalyticMatchSurface *CATPGMCreateAnalyticMirrorMatch(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATPLine *iBoundaryToMatch,
  CATPlane *iPlane,
  const CATLaw *iAngularLawMirror,
  CATSkillValue iMode);

/**
 * Ascending compatibility for client frameworks. This inline function must be deleted once clients call
 * CATPGMCreateAnalyticMirrorMatch.
 */
inline CATAnalyticMatchSurface *CATCreateAnalyticMirrorMatch(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATPLine *iBoundaryToMatch,
  CATPlane *iPlane,
  const CATLaw *iAngularLawMirror,
  CATSkillValue iMode)
{
  return CATPGMCreateAnalyticMirrorMatch(iFactory, iConfig, iBoundaryToMatch, iPlane, iAngularLawMirror, iMode);
}

ExportedByCATGMOperatorsInterfaces CATAnalyticMatchSurface *CATPGMCreateAnalyticMirrorMatch(
  CATGeoFactory *iFactory,
  CATPLine *iBoundaryToMatch,
  CATPlane *iPlane,
  const CATLaw *iAngularLawMirror,
  CATSkillValue iMode);

/**
 * Ascending compatibility for client frameworks. This inline function must be deleted once clients call
 * CATPGMCreateAnalyticMirrorMatch.
 */
inline CATAnalyticMatchSurface *CATCreateAnalyticMirrorMatch(
  CATGeoFactory *iFactory,
  CATPLine *iBoundaryToMatch,
  CATPlane *iPlane,
  const CATLaw *iAngularLawMirror,
  CATSkillValue iMode)
{
  return CATPGMCreateAnalyticMirrorMatch(iFactory, iBoundaryToMatch, iPlane, iAngularLawMirror, iMode);
}

/** @nodoc */
ExportedByCATGMOperatorsInterfaces
void Remove( CATAnalyticMatchSurface *&ioAnalyticMatchSurface );

#endif /* CATPGMCreateAnalyticMatchSurface_h_ */
