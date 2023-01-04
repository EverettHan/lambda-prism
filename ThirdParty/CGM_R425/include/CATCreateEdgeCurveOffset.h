
// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CATSkillValue.h"
#include "CATEdgeCurveOffset.h"
#include "Y300IINT.h"
#include "CATSoftwareConfiguration.h"

ExportedByY300IINT CATEdgeCurveOffset * CATCreateEdgeCurveOffset( CATGeoFactory *Factory,
                                                                 CATSoftwareConfiguration *Config,
                                                                 const CATEdgeCurve * EC,
                                                                 const CATOffsetSurface * OSur1,
                                                                 const CATOffsetSurface * OSur2,
                                                                 CATSkillValue iMode = BASIC);

ExportedByY300IINT CATEdgeCurveOffset * CATCreateEdgeCurveOffset( CATGeoFactory *Factory,
                                                                 CATSoftwareConfiguration *Config,
                                                                 const CATEdgeCurve * EC,
                                                                 const CATSurface * SurBase1,
                                                                 const CATSurface * SurBase2,
                                                                 const CATSurface * SurOff1,
                                                                 const CATSurface * SurOff2,
                                                                 CATSkillValue iMode = BASIC);


