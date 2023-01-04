#ifndef CATCreateLayDownCrvSur_H
#define CATCreateLayDownCrvSur_H

// COPYRIGHT DASSAULT SYSTEMES  2000


#include "Y300IINT.h"

#include "CATSkillValue.h"
#include "CATListOfCATCurves.h"
#include "CATCrvLimits.h"
#include "CATSurLimits.h"
#include "CreateLayDownCrvSur.h"

class CATLayDownCrvSur;
class CATMultiSurface;
class CATGeoFactory;
class CATSurface;
class CATCurve;
class CATSoftwareConfiguration;

/**
 * @nodoc
 * Cree un operateur permettant le posage d'une liste de Curves 
 * sur un reseau de surfaces.
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation.
 *     <dt><tt>ADVANCED</tt> <dd>Use the <tt>Run</tt> method to compute the operation.</dl>
 * @return
 * The pointer to the created operator.
 */
ExportedByY300IINT CATLayDownCrvSur * CATCreateLayDownCrvSur(CATGeoFactory * iWhere,
                                                             CATSoftwareConfiguration *Config,
                                                             CATLISTP(CATCurve) * iCurveList, 
                                                             CATMultiSurface * iMultiSurface,
                                                             CATSkillValue iMode=BASIC);

ExportedByY300IINT CATLayDownCrvSur * CATCreateLayDownCrvSur(CATGeoFactory * iFactory, 
                                                             CATSoftwareConfiguration *Config,
                                                             CATCurve * iCurve,
                                                             CATCrvLimits & iCrvLimits,
                                                             CATSurface * iSurface,
                                                             CATSurLimits & iSurLimits,
                                                             CATSkillValue iMode=BASIC);


#endif
