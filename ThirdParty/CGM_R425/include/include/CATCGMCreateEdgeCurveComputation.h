#ifndef CATICGMCreateEdgeCurveComputation_h_
#define CATICGMCreateEdgeCurveComputation_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMModelInterfaces.h"

class CATCurve;
class CATICGMEdgeCurveComputation;
class CATGeoFactory;
class CATSoftwareConfiguration;

/**
 * Creates an operator to compute an edge curve.
 * @param iCurve1
 * The pointer to the first curve.
 * @param iCurve2
 * The pointer to the second curve.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMEdgeCurveComputation *CATCGMCreateEdgeCurveComputation(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  CATCurve *iCurve1,
  CATCurve *iCurve2);

#endif /* CATICGMCreateEdgeCurveComputation_h_ */
