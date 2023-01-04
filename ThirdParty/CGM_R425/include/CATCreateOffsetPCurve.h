
// COPYRIGHT DASSAULT SYSTEMES 2005

#include "CATSkillValue.h"
#include "CATOffsetPCurve.h"
#include "Y300IINT.h"
#include "CATSoftwareConfiguration.h"

ExportedByY300IINT CATOffsetPCurve * CATCreateOffsetPCurve(CATGeoFactory * iFactory,
                                                           CATSoftwareConfiguration * iConfig,
                                                           CATPCurve * iPCurve,
                                                           const CATCrvLimits & iLimits,
                                                           CATSurface * iTargetOffsetSupport,
                                                           CATSkillValue iMode = BASIC);





