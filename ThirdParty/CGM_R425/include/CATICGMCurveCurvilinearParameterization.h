#ifndef CATICGMCurveCurvilinearParameterization_h_
#define CATICGMCurveCurvilinearParameterization_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
* @CAA2Level L1
* @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMGeoOperator.h"

class CATCrvLimits;
class CATCurve;
class CATGeoFactory;
class CATSoftwareConfiguration;

extern ExportedByCATGMModelInterfaces IID IID_CATICGMCurveCurvilinearParameterization;

/**
* Class defining the operator to parameterize a curve in curvilinear parameterization.
 * <p> Let the inputs be:
 * <br>C(t): the curve to reparameterize
 * <br>[t0, t1]: the limits specified by the user
 * <br>Tol: the tolerance 
*
* Let L(t) be the 3D curvilinear length of the curve C between t0 and t.
* Then the result curve D(s) will be such that
* for all t in [t0, t1], we have |C(t) - D(L(t))| < Tol
*
* Remark:
 * This property is valid only on the limits [t0, t1] on C
* which correspond to the limits [L(t0), L(t1)] on D: 
* outside these limits this relation will not be verified.
*/
class ExportedByCATGMModelInterfaces CATICGMCurveCurvilinearParameterization: public CATICGMGeoOperator
{
public:
	/**
	* Constructor
	*/
	CATICGMCurveCurvilinearParameterization();

	/**
 * Retrieves the curve limits.
	* @param oLimits
	* The limits on the result curve that correspond to the limits on the input
 * curve in curvilinear parameterization.
	* @return
	* The result curve
	*/
	virtual CATCurve *GetResult(CATCrvLimits &oLimits) = 0;

protected:
	/**
	* Destructor
	*/
	virtual ~CATICGMCurveCurvilinearParameterization(); // -> delete can't be called
};

/**
 * Creates a CATICGMCurveCurvilinearParameterization operator.
* @param iFactory
* The factory where the result curve is created.
* @param iSoftwareConfiguration
 * The software configuration.
* @param iCurve
 * The input curve to be reparameterized.
* @param iLimits
* The limits on which the input curve will be reparameterized.
 * @param iTolerance
* The tolerance for curvilinear reparameterization.
*  @return [out, IUnknown#Release]
 * The created CATICGMCurveCurvilinearParameterization operator.
*/
ExportedByCATGMModelInterfaces CATICGMCurveCurvilinearParameterization *CATCGMCreateCurveCurvilinearParameterization(
	CATGeoFactory *iFactory,
	CATSoftwareConfiguration *iSoftwareConfiguration,
	const CATCurve *iCurve,
	const CATCrvLimits &iLimits,
	double iTolerance);

#endif /* CATICGMCurveCurvilinearParameterization_h_ */
