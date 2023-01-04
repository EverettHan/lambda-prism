#ifndef CATCurveUserParameterization_H
#define CATCurveUserParameterization_H

// COPYRIGHT DASSAULT SYSTEMES  2008

/**
 * @level Protected
 * @usage U1
 */ 

#include "CATGeoOperator.h"
#include "Y30UIUTI.h"

class CATGeoFactory;
class CATCrvLimits;
class CATSoftwareConfiguration;
class CATMathFunctionX;
class CATCurve;

/**
 * Class defining the operator to parameterize a curve with a general parameterization.
 * <p> Let the inputs be:
 * <br>C(t): the curve to reparameterize
 * <br>[t0, t1]: the limits specified by the user
 * <br>[t0, t1]: the limits specified by the user
 * <br>Tol: the tolerance 
 * <br> F(t) the reparameterization function given by the user
 * Let L(t) be the 3D curvilinear length of the curve C between t0 and t.
 * Then the result curve D(s) will be such that
 * for all t in [t0, t1], we have |C(t) - D(F(t))| < Tol
 *
 * Remark:
 * This property is valid only on the limits [t0, t1] on C
 * which correspond to the limits [F(t0), F(t1)] on D: 
 * outside these limits this relation will not be verified.
 */
class ExportedByY30UIUTI CATCurveUserParameterization : public CATGeoOperator
{    
  CATCGMVirtualDeclareClass(CATCurveUserParameterization);
  public:
/**
 * Destructor.
 */
    virtual ~CATCurveUserParameterization();

/**
 * Retrieves the curve limits.
 * @param oLimits
 * The limits on the result curve that correspond to the limits on the input
 * curve in the new parameterization.
 * @return
 * The result curve
 */
    virtual CATCurve * GetResult(CATCrvLimits & oLimits) = 0;

  protected:

    CATCurveUserParameterization(CATGeoFactory * iFactory);

  private:

    CATCurveUserParameterization();
    CATCurveUserParameterization(const CATCurveUserParameterization &);
    void operator = (const CATCurveUserParameterization &);
};

/**
 * Creates a CATCurveUserParameterization operator.
 * @param iFactory
 * The factory where the result curve is created.
 * @param iSoftwareConfiguration
 * The software configuration.
 * @param iCurve
 * The input curve to be reparameterized.
 * @param iLimits
 * The limits on which the input curve will be reparameterized.
 * @param iTolerance
 * The function wich defines the new parameterization of the curve
 * @param iReparametrizationFunction
 * The tolerance for user reparameterization.
 * @return 
 * The created CATCurveUserParameterization operator.
 */
ExportedByY30UIUTI CATCurveUserParameterization * 
CATCreateCurveUserParameterization(CATGeoFactory * iFactory, 
                                          CATSoftwareConfiguration * iSoftwareConfiguration,
                                          const CATCurve * iCurve, 
                                          const CATCrvLimits & iLimits,
                                          CATMathFunctionX * iReparametrizationFunction,
                                          double iTolerance); 

#endif
