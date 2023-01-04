#ifndef CATCreateExtrapol_H
#define CATCreateExtrapol_H 

#include "Y300IINT.h"

class CATExtrapolSurfaces;
class CATGeoFactory;
class CATSurface;
class CATSurLimits;
class CATExtrapolNurbsSurface;
class CATNurbsSurface;
class CATMathVector2D;
class CATSoftwareConfiguration;
class CATSurParam;

ExportedByY300IINT
CATExtrapolSurfaces * CATCreateExtrapolSurfaces (CATGeoFactory * iFactory,
                        CATSoftwareConfiguration * iConfig,
                        CATSurface * iSurface0, CATSurLimits * iLimits0,
                        CATSurface * iSurface1, CATSurLimits * iLimits1);

ExportedByY300IINT
CATExtrapolNurbsSurface * CATCreateExtrapolSurfaces (CATGeoFactory *iFactory,
         CATSoftwareConfiguration * iConfig,
			   CATNurbsSurface * ioSur,
			   const CATMathVector2D & iDirection,
			   const CATSurParam & iParamOnSur);


#endif



