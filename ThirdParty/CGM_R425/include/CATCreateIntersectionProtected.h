#ifndef CATCreateIntersectionProtected_H 
#define CATCreateIntersectionProtected_H 

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CATIntersectionPCrvPCrv.h"
#include "CreateIntersectionProtected.h"

class CATSoftwareConfiguration;

ExportedByY30C1XMM CATIntersectionPCrvPCrv* CATCreateIntersectionNoCheck (
			CATGeoFactory *Factory,
      CATSoftwareConfiguration *iConfig,
			const CATPointOnCurve * Poc1On1,
			const CATPointOnCurve * Poc2On1,
			const CATPointOnCurve * Poc1On2,
			const CATPointOnCurve * Poc2On2,
			const CATSkillValue skill = BASIC);

#endif


