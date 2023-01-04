#ifndef CATCreateExtrapolAndReconvergeSharpCrvSur_H
#define CATCreateExtrapolAndReconvergeSharpCrvSur_H


#include "Y300IINT.h"
class CATExtrapolAndReconvergeSharpCrvSur;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATSurface;
class CATMathLine;
class CATSurParam;

ExportedByY300IINT
CATExtrapolAndReconvergeSharpCrvSur* CATCreateExtrapolAndReconvergeSharpCrvSur(CATGeoFactory * iFactory,
                                   CATSoftwareConfiguration * iConfig,
                                   CATSurface * iSurface,
                                   CATSurParam & iSurParam,
                                   CATMathLine * iLine,
                                   double MinExtrapol = 0);

ExportedByY300IINT
CATExtrapolAndReconvergeSharpCrvSur* CATCreateExtrapolAndReconvergeSharpCrvSur(CATGeoFactory * iFactory,
                                   CATSoftwareConfiguration * iConfig,
                                   CATSurface * iSurface,
                                   CATSurParam *& iSurfParam,
                                   int iNbLine,
                                   CATMathLine ** iLine,
                                   double iDistMinExtrapol);

#endif


