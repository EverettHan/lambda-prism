#ifndef CATCreateCrvLength_H
#define CATCreateCrvLength_H

#include "Y300IINT.h"
#include "CATMathDef.h"
#include "CATMathLimits.h"
//BigScale Mod. #SKA
#include "CATTolerance.h"

class CATCrvLength;
class CATCrvParam;
class CATPointOnCurve;
class CATCGMVirtual;
class CATSoftwareConfiguration;
class CATCurve;

ExportedByY300IINT
CATCrvLength * CATCreateCrvLength(CATSoftwareConfiguration * iConfig,
               const CATPointOnCurve *point1, 
               const CATPointOnCurve *point2, 
               //const double tol=CATEpsg);
               const double tol=CATGetDefaultTolerance().EpsgForLengthTest());//@Use Scaled value of Epsg
               

ExportedByY300IINT
CATCrvLength * CATCreateCrvLength(CATSoftwareConfiguration * iConfig,
               const CATCurve * crv,
               const CATCrvParam & param1, const CATCrvParam & param2,
               //const double tol=CATEpsg);
               const double tol=CATGetDefaultTolerance().EpsgForLengthTest());//@Use Scaled value of Epsg

#endif




