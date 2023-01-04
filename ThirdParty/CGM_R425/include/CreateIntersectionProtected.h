#ifndef CreateIntersectionProtected_H 
#define CreateIntersectionProtected_H 
// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CATIntersectionPCrvPCrv.h"

//Do not use, use CATCreateIntersectionNoCheck
ExportedByY30C1XMM CATIntersectionPCrvPCrv* CreateIntersectionNoCheck (
			CATGeoFactory *Factory,
			const CATPointOnCurve * Poc1On1,
			const CATPointOnCurve * Poc2On1,
			const CATPointOnCurve * Poc1On2,
			const CATPointOnCurve * Poc2On2,
			const CATSkillValue skill = BASIC);

#endif


