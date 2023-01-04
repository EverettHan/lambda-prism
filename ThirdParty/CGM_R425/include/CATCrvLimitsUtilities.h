#ifndef CATCrvLimitsUtilities_H
#define CATCrvLimitsUtilities_H

// COPYRIGHT DASSAULT SYSTEMES 1998

#include "ExportedByCATCGMGeoMath.h"
#include "CATCrvLimits.h"

//Method for boolean substraction between two CrvLimits: should be migrated to CATCrvLimits.h, one day...
// iCrvLim1 - iCrvLim2 = ioCrvLimOutLeft && ioCrvLimOutRight.
//Example: [1, 6]-[2, 4] = [1, 2] && [4, 6]. NB: ioCrvLimOutLeft and ioCrvLimOutRight can be empty.
void ExportedByCATCGMGeoMath BooleanSubstraction(CATCrvLimits &iCrvLim1, CATCrvLimits &iCrvLim2,
                                                 CATCrvLimits &ioCrvLimOutLeft, CATCrvLimits &ioCrvLimOutRight);



#endif


