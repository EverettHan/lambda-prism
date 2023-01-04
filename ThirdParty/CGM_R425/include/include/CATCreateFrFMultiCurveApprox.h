#ifndef CATCreateFrFMultiCurveApprox_H 
#define CATCreateFrFMultiCurveApprox_H 

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATListOfCATCurves.h"
#include "CATListOfCATCrvLimits.h"
#include "CATListOfCATMathCurveFunction.h"

class CATFrFMultiCurveApprox;
class CATGeoFactory;
class CATFrFNurbsMultiForm;
class CATCurve;
class CATCrvLimits;
class CATMathInterval;
class CATMathFunctionX;
class CATCrvParam;
class CATSoftwareConfiguration;

/**
 * Creates the operator from two sets of curves: one list of CATCurve and one list of CATMathCurveFunction.
 * One and only one of these lists can be empty.
 *
 * @param iFactory
 * The pointer to the geometry factory.
 *
 *@param iSoftwareConfiguration
 *The pointer to the software configuration
 *
 * @param iTolerance
 * The tolerance of approximation.
 *
 * @param iListOfCATCurves
 * The list of CATCurve.
 *
 * @param iListOfCATCrvLimits
 * The list of CATCrvLimits to take into account for the CATCurve contained in iListOfCATCurves.
 *
 * @param iListOfCATMathCurveFunctions
 * The list of CATMathCurveFunction.
 *
 * @param iListOfLimits
 * The list of limits to take into account for the CATCurve contained in iListOfCATMathCurveFunctions.
 * Size: 2 * size of iListOfCATMathCurveFunctions.
 * Ordered: { start for curve 1, end for curve 1, start for curve 2, ... }.
 *
 * @param iMode
 * The mode of use.
 *
 * @return
 * The pointer to the created operator. To delete with the usual C++ <tt>delete</tt> operator afer use.
 */
ExportedByY300IINT 
CATFrFMultiCurveApprox * CATCreateMultiCurveApprox (CATGeoFactory *iFactory,
																                    CATSoftwareConfiguration * iSoftwareConfiguration,
							                                      double iTolerance, 
							                                      const CATLISTP(CATCurve) & iListOfCATCurves,
							                                      const CATLISTP(CATCrvLimits) & iListOfCATCrvLimits,
							                                      const CATLISTP(CATMathCurveFunction) & iListOfCATMathCurveFunctions,
							                                      const CATListOfDouble & iListOfLimits,
							                                      CATSkillValue iMode=BASIC);

/**
 * @nodoc
 * Deprecated.

ExportedByY30Approx CATFrFMultiCurveApprox * CATCreateMultiCurveApprox (CATGeoFactory *iFactory,
							double iTolerance, 
							const CATLISTP(CATCurve) & iListOfCATCurves,
							const CATLISTP(CATCrvLimits) & iListOfCATCrvLimits,
							const CATLISTP(CATMathCurveFunction) & iListOfCATMathCurveFunctions,
							const CATListOfDouble & iListOfLimits,
							CATSkillValue iMode=BASIC);
*/
#endif

