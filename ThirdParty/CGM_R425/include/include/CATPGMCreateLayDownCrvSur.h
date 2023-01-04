#ifndef CATPGMCreateLayDownCrvSur_h_
#define CATPGMCreateLayDownCrvSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATSkillValue.h"
#include "CATCollec.h"

class CATCurve;
class CATGeoFactory;
class CATIPGMLayDownCrvSur;
class CATMultiSurface;
class CATSurface;
class CATCrvLimits;
class CATSurLimits;
class CATSoftwareConfiguration;
class CATLISTP(CATCurve);

/**
 * @nodoc
 * Cree un operateur permettant le posage d'une liste de Curves 
 * sur un reseau de surfaces.
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation.
 *     <dt><tt>ADVANCED</tt> <dd>Use the <tt>Run</tt> method to compute the operation.</dl>
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMModelInterfaces CATIPGMLayDownCrvSur *CATPGMCreateLayDownCrvSur(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *Config,
  CATLISTP(CATCurve) *iCurveList,
  CATMultiSurface *iMultiSurface,
  CATSkillValue iMode = BASIC);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMLayDownCrvSur *CATPGMCreateLayDownCrvSur(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *Config,
  CATCurve *iCurve,
  CATCrvLimits &iCrvLimits,
  CATSurface *iSurface,
  CATSurLimits &iSurLimits,
  CATSkillValue iMode = BASIC);

/**
* @deprecated V5R13 CATPGMCreateLayDownCrvSur
* @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATIPGMLayDownCrvSur *CATPGMCreateLayDownCrvSur(
  CATGeoFactory *iFactory,
  CATCurve *iCurve,
  CATCrvLimits &iCrvLimits,
  CATSurface *iSurface,
  CATSurLimits &iSurLimits,
  CATSkillValue iMode = BASIC);

/**
* @deprecated V5R13 CATPGMCreateLayDownCrvSur
* @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATIPGMLayDownCrvSur *CATPGMCreateLayDownCrvSur(
  CATGeoFactory *iWhere,
  CATLISTP(CATCurve) *iCurveList,
  CATMultiSurface *iMultiSurface,
  CATSkillValue iMode = BASIC);

#endif /* CATPGMCreateLayDownCrvSur_h_ */
