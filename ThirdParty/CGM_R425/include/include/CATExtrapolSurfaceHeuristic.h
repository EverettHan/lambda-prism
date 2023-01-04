// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATExtrapolSurfaceHeuristic :
//
//=============================================================================
// Usage notes:
//
//
//=============================================================================
// Apr 00  Creation                          X. Gourdon
//=============================================================================

#ifndef CATExtrapolSurfaceHeuristic_H
#define CATExtrapolSurfaceHeuristic_H 

#include "Y30UIUTI.h"
#include "CATMathDef.h"

class CATSurface;
class CATCurve;
class CATSurLimits;
class CATCrvLimits;
class CATSurParam;
class CATSoftwareConfiguration;

CATBoolean ExportedByY30UIUTI GetExtrapolSurfaceHeuristicRatio(const CATSurface * iSurface,
                                                               CATSurLimits & iSurLim,
                                                               CATCurve * iCurve,
                                                               CATCrvLimits * iCrvLim,
                                                               CATSurParam & iSurParam,
                                                               CATSurParam & ioEstimatedSurParam,
                                                               double      & oRatio,
                                                               CATSoftwareConfiguration * iConfig=0);


#endif
























