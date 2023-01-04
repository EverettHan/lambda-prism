#ifndef CATCreateEdgeCurveComputation_H
#define CATCreateEdgeCurveComputation_H

// COPYRIGHT DASSAULT SYSTEMES 2003

/**
 * @level Protected
 * @usage U1
 */

#include "Y300IINT.h"

class CATEdgeCurveComputation;
class CATGeoFactory;
class CATCurve;
class CATSoftwareConfiguration;
/**
 * Creates an operator to compute an edge curve.
 * @param iCurve1
 * The pointer to the first curve.
 * @param iCurve2
 * The pointer to the second curve.
 * @return
 * The pointer to the created operator. To delete with the usual C++ delete operator after use.
 */
ExportedByY300IINT CATEdgeCurveComputation * 
CATCreateEdgeCurveComputation(CATGeoFactory * iWhere,
                              CATSoftwareConfiguration * iConfig,
                              CATCurve *iCurve1, 
                              CATCurve *iCurve2);

#endif

