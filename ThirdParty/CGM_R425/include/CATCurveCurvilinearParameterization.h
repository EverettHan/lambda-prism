#ifndef CATCurveCurvilinearParameterization_H
#define CATCurveCurvilinearParameterization_H

// COPYRIGHT DASSAULT SYSTEMES  2004

/**
 * @level Protected
 * @usage U1
 */ 

#include "CATGeoOperator.h"
#include "Y30UIUTI.h"

class CATGeoFactory;
class CATCrvLimits;
class CATSoftwareConfiguration;
class CATCurve;

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
class ExportedByY30UIUTI CATCurveCurvilinearParameterization : public CATGeoOperator
{    
  CATCGMVirtualDeclareClass(CATCurveCurvilinearParameterization);
  public:
/**
 * Destructor.
 */
    virtual ~CATCurveCurvilinearParameterization();

/**
 * Retrieves the curve limits.
 * @param oLimits
 * The limits on the result curve that correspond to the limits on the input
 * curve in curvilinear parameterization.
 * @return
 * The result curve
 */
    virtual CATCurve * GetResult(CATCrvLimits & oLimits) = 0;

  protected:

    CATCurveCurvilinearParameterization(CATGeoFactory * iFactory);

  private:

    CATCurveCurvilinearParameterization();
    CATCurveCurvilinearParameterization(const CATCurveCurvilinearParameterization &);
    void operator = (const CATCurveCurvilinearParameterization &);
};

/**
 * Creates a CATCurveCurvilinearParameterization operator.
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
 * @return 
 * The created CATCurveCurvilinearParameterization operator.
 */
ExportedByY30UIUTI CATCurveCurvilinearParameterization * 
CATCreateCurveCurvilinearParameterization(CATGeoFactory * iFactory, 
                                          CATSoftwareConfiguration * iSoftwareConfiguration,
                                          const CATCurve * iCurve, 
                                          const CATCrvLimits & iLimits,
                                          double iTolerance);

#endif
