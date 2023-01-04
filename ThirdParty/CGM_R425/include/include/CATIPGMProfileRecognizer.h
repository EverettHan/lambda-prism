#ifndef CATIPGMProfileRecognizer_h_
#define CATIPGMProfileRecognizer_h_

// COPYRIGHT DASSAULT SYSTEMES 2020

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include <CATListPV.h>
class CATCurve;
class CATLISTP(CATCurve);
class CATCrvLimits;
class CATLISTP(CATCrvLimits);
class CATMathSetOfPointsND;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMProfileRecognizer;

// ============================================================================================================================= //
//                                                           OPERATOR                                                            //
// ============================================================================================================================= //
class ExportedByCATGMModelInterfaces CATIPGMProfileRecognizer: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMProfileRecognizer();

  /**
  * tolerance used to associate points with input curve
  */
  virtual void SetUserTolerance(double iTol) = 0;

  /**
  * set the curves set to be identified within the user tolerance among the list of points
  * curves informations are the curve and thier limits
  */
  virtual void SetInputCurvesData(
    const CATLISTP(CATCurve) &iListOfCurves,
    const CATLISTP(CATCrvLimits) &iListCrvLimits) = 0;

  /**
  *Get result: the set of curves dientified, their limits and orientation regarding the set of point order
  */
  virtual void GetCurveResults(
    CATLISTP(CATCurve) &ioListOfCurves,
    CATLISTP(CATCrvLimits) &ioCrvLimits,
    CATListOfInt &ioOrientations) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMProfileRecognizer(); // -> delete can't be called
};

// ============================================================================================================================= //
//                                                        CREATE OPERATOR                                                        //
// ============================================================================================================================= //
/**
* Create an operator which identifies the set of curves from a set of points 3D. 
*/
ExportedByCATGMModelInterfaces CATIPGMProfileRecognizer *CATPGMCreateProfileRecognizer(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATMathSetOfPointsND *iPoints);

#endif /* CATIPGMProfileRecognizer_h_ */
