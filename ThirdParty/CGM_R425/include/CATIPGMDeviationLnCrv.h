#ifndef CATIPGMDeviationLnCrv_h_
#define CATIPGMDeviationLnCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include "CATSkillValue.h"

class CATCrvLimits;
class CATCrvParam;
class CATCurve;
class CATGeoFactory;
class CATMathLine;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMDeviationLnCrv;

/**
 * Class defining the operator of maximum deviation between an infinite line
 * and a curve. It returning the maximum length between the curve and the line.
 */
class ExportedByCATGMModelInterfaces CATIPGMDeviationLnCrv: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMDeviationLnCrv();

  /**
 * Specify limits to work on
 */
  virtual void SetLimits(const CATCrvLimits &iLimits) = 0;

  /**
 * Returns the maximum distance between the CATCurve and the 
 * CATMathLine.
 * @return
 * The distance.
 */
  virtual double GetDistance() const = 0;

  /**
 * Returns a param on the Curve which realized the
 * maximum distance between the CATCurve and the CATMathLine.
 * @return
 * The curve parameter.
 */
  virtual void GetCrvParam(CATCrvParam &oParam) const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDeviationLnCrv(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMDeviationLnCrv *CATPGMCreateDeviationLnCrv(
  CATGeoFactory *iWhere,
  const CATMathLine &iLine,
  CATCurve *iCurve,
  CATSkillValue iMode = BASIC);

#endif /* CATIPGMDeviationLnCrv_h_ */
