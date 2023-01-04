#ifndef CATCreateEdgeCurveSharpnessCut_H
#define CATCreateEdgeCurveSharpnessCut_H

#include "Y30UIUTI.h"

class CATEdgeCurveSharpnessCut;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATPCurve;
class CATSurface;
class CATPCurve;
class CATSurface;

ExportedByY30UIUTI
CATEdgeCurveSharpnessCut * CATCreateEdgeSharpnessCut(CATGeoFactory * iFactory,
                           CATSoftwareConfiguration *iConfig,
                           CATEdgeCurve * ECrv,
                           CATPointOnEdgeCurve * Start,
                           CATPointOnEdgeCurve * End,
                           const short SideOnFace1,
                           CATPCurve * PCrv1,
                           CATSurface * Surf1, 
                           const short OrnFaceVsSurf1,
                           CATPCurve * PCrv2,
                           CATSurface * Surf2,
                           const short OrnFaceVsSurf2);




#endif


