// COPYRIGHT DASSAULT SYSTEMES 2007
#ifndef CATPGMCreateBreakSurface_H 
#define CATPGMCreateBreakSurface_H 
//
#include "CATGMOperatorsInterfaces.h"
#include "CATSkillValue.h"
#include "CATIsoParameter.h"
#include "CATCollec.h"

class CATGeoFactory;
class CATPCurve;
class CATPointOnSurface;
class CATBreakSurface;
class CATNurbsSurface;
class CATSoftwareConfiguration;
class CATLISTP(CATPCurve);

ExportedByCATGMOperatorsInterfaces
CATBreakSurface * CATPGMCreateBreakSurface( CATGeoFactory  *iFactory, CATSoftwareConfiguration * iSoftwareConfiguration,
				      CATPCurve *iCurve,
                                      CATSkillValue iMode = BASIC);

ExportedByCATGMOperatorsInterfaces
CATBreakSurface * CATPGMCreateBreakSurface( CATGeoFactory  *iFactory, CATSoftwareConfiguration * iSoftwareConfiguration, 
				      CATPointOnSurface *iPtBreak,
                                      CATSkillValue iMode = BASIC);
ExportedByCATGMOperatorsInterfaces
CATBreakSurface * CATPGMCreateBreakSurface( CATGeoFactory  *iFactory, CATSoftwareConfiguration * iSoftwareConfiguration,
				     CATLISTP(CATPCurve ) &iListe,
                                      CATSkillValue iMode = BASIC);

/* TO BE MOVED HERE ONCE CreateBreakSurface.h is removed
ExportedByCATGMOperatorsInterfaces
void Remove( CATBreakSurface *&ioBreakSurface );
*/

#endif
