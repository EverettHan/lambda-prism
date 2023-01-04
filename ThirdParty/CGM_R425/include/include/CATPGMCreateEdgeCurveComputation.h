#ifndef CATIPGMCreateEdgeCurveComputation_h_
#define CATIPGMCreateEdgeCurveComputation_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"

class CATCurve;
class CATIPGMEdgeCurveComputation;
class CATGeoFactory;
class CATSoftwareConfiguration;

/**
 * @level Protected
 * @usage U1
 */

/**
 * Creates an operator to compute an edge curve.
 * @param iCurve1
 * The pointer to the first curve.
 * @param iCurve2
 * The pointer to the second curve.
 * @return
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMEdgeCurveComputation *CATPGMCreateEdgeCurveComputation(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  CATCurve *iCurve1,
  CATCurve *iCurve2);

#endif /* CATIPGMCreateEdgeCurveComputation_h_ */
