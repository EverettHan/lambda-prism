#ifndef CATICGMCreateLocalAnalysisD_h_
#define CATICGMCreateLocalAnalysisD_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMModelInterfaces.h"

class CATCrvParam;
class CATCurve;
class CATICGMLocalAnalysis1D;
class CATICGMLocalAnalysis2D;
class CATSoftwareConfiguration;
class CATSurParam;
class CATSurface;

/**
 * Copy pointer
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATICGMLocalAnalysis2D *CATCGMCreateLocalAnalysis(
  const CATICGMLocalAnalysis2D *iAnalysisToCopy);

/**
 * Creates a local analyzer on a point of a CATSurface
 * @param iConfig
 * The level of code (Versionning).
 * @param iSupport
 * The surface on which the analysis is done.
 * @param iPointToAnalyze
 * The parameter on <tt>iSupport</tt> of the point to analyze.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATICGMLocalAnalysis2D *CATCGMCreateLocalAnalysis(
  CATSoftwareConfiguration *iConfig,
  const CATSurface *iSurface,
  const CATSurParam &iPointToAnalyze);

/**
 * Copy pointer
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATICGMLocalAnalysis1D *CATCGMCreateLocalAnalysis(
  const CATICGMLocalAnalysis1D *iAnalysisToCopy);

/**
 * Creates a local analyzer on a point of a CATCurve.
 * @param iConfig
 * The level of code (Versionning).
 * @param iSupport
 * The curve on which the analysis is done.
 * @param iPointToAnalyze
 * The parameter on <tt>iSupport</tt> of the point to analyze.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATICGMLocalAnalysis1D *CATCGMCreateLocalAnalysis(
  CATSoftwareConfiguration *iConfig,
  const CATCurve *iSupport,
  const CATCrvParam &iPointToAnalyze);

#endif /* CATICGMCreateLocalAnalysisD_h_ */
