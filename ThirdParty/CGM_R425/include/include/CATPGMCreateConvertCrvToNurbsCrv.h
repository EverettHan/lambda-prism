#ifndef CATPGMCreateConvertCrvToNurbsCrv_h_
#define CATPGMCreateConvertCrvToNurbsCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATSkillValue.h"

class CATConvertCrvToNurbsCrv;
class CATCurve;
class CATGeoFactory;
class CATSoftwareConfiguration;

/**
 * @deprecated V5R10 CreateCrvFittingToNurbsCrv
 * Creates the geometric operator that computes the Nurbs representation of a CATCurve.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iCurve
 * The pointer to the curve to convert.
 * @param iMode
 * The mode of use.
 * @return
 * The pointer to the created operator. To <tt>delete</tt> with the usual C++ delete operator afer use.
 * @see CATConvertCrvToNurbsCrv
 */
ExportedByCATGMOperatorsInterfaces CATConvertCrvToNurbsCrv *CATPGMCreateConvertCrvToNurbsCrv(
  CATGeoFactory *iFactory,
  const CATCurve &iCurve,
  CATSkillValue iMode = BASIC);

ExportedByCATGMOperatorsInterfaces CATConvertCrvToNurbsCrv *CATPGMCreateConvertCrvToNurbsCrv(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATCurve &iCurve);

/**
 * Ascending compatibility for client frameworks. This inline function must be deleted once clients call
 * CATPGMCreateConvertCrvToNurbsCrv.
 */
inline CATConvertCrvToNurbsCrv *CreateConvertCrvToNurbsCrv(
  CATGeoFactory *iFactory,
  const CATCurve &iCurve,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateConvertCrvToNurbsCrv(iFactory, iCurve, iMode);
}

/**
 * @nodoc
 */
ExportedByCATGMOperatorsInterfaces
void Remove( CATConvertCrvToNurbsCrv *&iCATConvertCrvToNurbsCrv );

#endif /* CATPGMCreateConvertCrvToNurbsCrv_h_ */
