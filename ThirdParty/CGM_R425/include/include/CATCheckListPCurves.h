// COPYRIGHT DASSAULT SYSTEMES 1998
//============================================================================
//
// Check in a list of CATPCurves (iPCrv1 on surface 1 and iPCrv2 on surface 2)
// if there are two identical PCurves
//
//============================================================================
// Oct. 98    Creation                         F. Bezard
// Octobre 2004 - Versionning interne EAB
//============================================================================

#include "Y30C3XGG.h"

class CATPCurve;
class CATSoftwareConfiguration;
		                            
ExportedByY30C3XGG void CATCheckListPCurves (CATSoftwareConfiguration * iConfig,
                                             CATPCurve ** iPCrv1, CATPCurve ** iPCrv2, CATLONG32 iNbCrv);







