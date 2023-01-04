#ifndef CATPGMCreateLocalComparison2D_h_
#define CATPGMCreateLocalComparison2D_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "CATGMModelInterfaces.h"

class CATIPGMLocalAnalysis2D;
class CATIPGMLocalComparison2D;
class CATMathDirection2D;
class CATSoftwareConfiguration;
class CATSurParam;
class CATSurface;

/**
 * Creates a local Comparison between two points of 2 CATSurfaces.
 * @param iConfig
 * The level of code.
 * @param iSurface
 * The surface on which the analysis is done.
 * @param iPointToAnalyze
 * The parameter on <tt>iSurface</tt> of the point to analyze.
 * @return [out, IUnknown#Release]
 * The created CATIPGMLocalAnalysis2D operator.
 */
ExportedByCATGMModelInterfaces CATIPGMLocalComparison2D *CATPGMCreateLocalComparison2D(
  CATSoftwareConfiguration *iConfig,
  const CATSurface *iRedSurface,
  const CATSurface *iSurface,
  const CATSurParam &iPointToAnalyze);

#endif /* CATPGMCreateLocalComparison2D_h_ */
