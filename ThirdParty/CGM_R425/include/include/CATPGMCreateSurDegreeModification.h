#ifndef CATPGMCreateSurDegreeModification_h_
#define CATPGMCreateSurDegreeModification_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"
#include "CATSkillValue.h"

class CATGeoFactory;
class CATNurbsSurface;
class CATIPGMSurDegreeModification;

/**
 * Creates the geometric operator that decreases the degree of a Nurbs curve.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iNurbsCurve
 * The pointer to the curve to be converted.
 * @param iTargetDegreeU
 * The degree along U to be achieved.
 * @param iTargetDegreeV
 * The degree along V to be achieved.
 * @param iTolerance
 * The specified tolerance.
 * @param iMode
 * The mode of use.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. 
 * To be released with the <tt>Release</tt> method afer use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMSurDegreeModification *CATPGMCreateSurDegreeModification(
  CATGeoFactory *ifactory,
  CATNurbsSurface *iNurbsSurface,
  const CATLONG32 &iTargetDegreeU,
  const CATLONG32 &iTargetDegreeV,
  const double iTolerance,
  CATSkillValue iMode = BASIC);

/**
 * Creates the geometric operator increases the degree of a Nurbs surface.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iNurbsCurve
 * The pointer to the surface to be converted.
 * @param iNewDegreeU
 * The new degree along U.
 * @param iNewDegreeV
 * The new degree along V.
 * @param iMode
 * The mode of use.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. 
 * To be released with the <tt>Release</tt> method afer use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMSurDegreeModification *CATPGMCreateSurDegreeModification(
  CATGeoFactory *iFactory,
  CATNurbsSurface *iNurbsSurface,
  const CATLONG32 &iNewDegreeU,
  const CATLONG32 &iNewDegreeV,
  CATSkillValue iMode = BASIC);

#endif /* CATPGMCreateSurDegreeModification_h_ */
