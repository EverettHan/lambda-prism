#ifndef CATCreateLocalComparison2D_H
#define CATCreateLocalComparison2D_H

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "Y30UIUTI.h"
#include "Y300IINT.h"

class CATSurface;
class CATMathDirection2D;
#include "CATSurParam.h"
#include "CATMathVector.h"

#include "CATCGMVirtual.h"

class CATSoftwareConfiguration;
class CATSurParam;
class CATLocalComparison2D;
class CATLocalAnalysis2D;

  /**
 * Creates a local Comparison between two points of 2 CATSurfaces.
 * @param iConfig
 * The level of code.
 * @param iSurface
 * The surface on which the analysis is done.
 * @param iPointToAnalyze
 * The parameter on <tt>iSurface</tt> of the point to analyze.
 * @return 
 * The created CATLocalAnalysis2D operator.
 */  

ExportedByY300IINT
CATLocalComparison2D * CATCreateLocalComparison2D(CATSoftwareConfiguration * iConfig,
                        const CATSurface *iRedSurface,
                        const CATSurface *iSurface,
                        const CATSurParam &iPointToAnalyze);

#endif 
