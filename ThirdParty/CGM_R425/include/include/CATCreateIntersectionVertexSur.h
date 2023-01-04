#ifndef CATCreateIntersectionVertexSur_H 
#define CATCreateIntersectionVertexSur_H 

#include "Y300IINT.h"
#include "CATMathDef.h"

class CATIntersectionVertexSur;
class CATGeoFactory;
class CATEdgeCurve; 
class CATSurface;
class CATCurve;
class CATCrvLimits;
class CATSurParam;
class CATMathPoint;
class CATSoftwareConfiguration;

ExportedByY300IINT
CATIntersectionVertexSur * CATCreateIntersectionVertexSur(CATGeoFactory *iFactory,
         CATSoftwareConfiguration * iConfig,
			   CATLONG32 iNbSurface,
			   CATSurface **iListOfSurface,
			   CATSurParam *iListOfCoupleOfParamUV,
			   CATSurface *iSurface);

#endif



