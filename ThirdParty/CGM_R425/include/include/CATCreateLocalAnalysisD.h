#ifndef CATCreateLocalAnalysis_H
#define CATCreateLocalAnalysis_H
// COPYRIGHT DASSAULT SYSTEMES  2002
/**
 * @level Protected
 * @usage U1
 */ 

#include "Y300IINT.h"

class CATSurface;
class CATCurve;
class CATSurParam;
class CATCrvParam;
class CATSoftwareConfiguration;
class CATLocalAnalysis1D;
class CATLocalAnalysis2D;

/**
 * Creates a local analyzer on a point of a CATCurve.
 * @param iConfig
 * The level of code (Versionning).
 * @param iSupport
 * The curve on which the analysis is done.
 * @param iPointToAnalyze
 * The parameter on <tt>iSupport</tt> of the point to analyze.
 * @return 
 * The created CATLocalAnalysis1D operator.
 */ 
ExportedByY300IINT
CATLocalAnalysis1D * CATCreateLocalAnalysis(CATSoftwareConfiguration * iConfig,
                        const CATCurve *iSupport,
                        const CATCrvParam &iPointToAnalyze);

/**
 * Creates a local analyzer by copy.
 * @param iAnalysisToCopy
 * The operator to be copied. 
 * @return 
 * The created CATLocalAnalysis1D operator.
 */
ExportedByY300IINT
CATLocalAnalysis1D* CATCreateLocalAnalysis(const CATLocalAnalysis1D * iAnalysisToCopy ) ;

  /**
 * Creates a local analyzer on a point of a CATSurface.
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
CATLocalAnalysis2D * CATCreateLocalAnalysis(CATSoftwareConfiguration * iConfig,
                        const CATSurface *iSurface,
                        const CATSurParam &iPointToAnalyze);

/**
 * Creates a local analyzer by copy.
 * @param iAnalysisToCopy
 * The operator to be copied. 
 * @return 
 * The created CATLocalAnalysis2D operator.
 */
ExportedByY300IINT
CATLocalAnalysis2D* CATCreateLocalAnalysis(const CATLocalAnalysis2D * iAnalysisToCopy ) ;


#endif





