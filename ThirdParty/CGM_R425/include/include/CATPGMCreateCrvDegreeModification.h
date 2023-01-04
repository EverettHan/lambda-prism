#ifndef CATPGMCreateCrvDegreeModification_h_
#define CATPGMCreateCrvDegreeModification_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"
#include "CATSkillValue.h"

class CATIPGMCrvDegreeModification;
class CATCurve;
class CATGeoFactory;

/**
 * Creates the geometric operator that decreases the degree of a Nurbs curve.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iNurbsCurve
 * The pointer to the curve to be converted.
 * @param iTargetDegree
 * The degree to be achieved.
 * @param iTolerance
 * The specified tolerance.
 * @param iMode
 * The mode of use.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. 
 * To be released with the <tt>Release</tt> method afer use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMCrvDegreeModification *CATPGMCreateCrvDegreeModification(
  CATGeoFactory *iFactory,
  CATCurve *iNurbsCurve,
  const CATLONG32 iTargetDegree,
  const double iTolerance,
  CATSkillValue iMode = BASIC);

/**
 * Creates the geometric operator increases the degree of a Nurbs curve.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iNurbsCurve
 * The pointer to the curve to be converted.
 * @param iNewDegree
 * The new degree.
 * @param iMode
 * The mode of use.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. 
 * To be released with the <tt>Release</tt> method afer use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMCrvDegreeModification *CATPGMCreateCrvDegreeModification(
  CATGeoFactory *iFactory,
  CATCurve *iNurbsCurve,
  const CATLONG32 &iNewDegree,
  CATSkillValue iMode = BASIC);

#endif /* CATPGMCreateCrvDegreeModification_h_ */
