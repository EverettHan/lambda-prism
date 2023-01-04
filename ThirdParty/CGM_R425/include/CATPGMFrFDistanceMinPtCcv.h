#ifndef CATPGMFrFDistanceMinPtCcv_h_
#define CATPGMFrFDistanceMinPtCcv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATCGMVirtual.h"
#include "CATSkillValue.h"
#include "CATDataType.h"

class CATFrFCCvParam;
class CATMathPoint;
class CATGeoFactory;
class CATFrFCompositeCurve;
class CATCrvParam;

//
//
//-------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATPGMFrFDistanceMinPtCcv: public CATCGMVirtual
{
public:
  /**
   * Constructor
   */
  CATPGMFrFDistanceMinPtCcv();

  /**
   * Destructor
   */
  virtual ~CATPGMFrFDistanceMinPtCcv();

  virtual void Run() = 0;

  /**
 * Returns the minimum distance between a CATCurve and a CATPoint.
 */
  virtual double GetDistance() const = 0;

  /**
 * Returns the global parameter of a point on curve realizing the minimum
 * distance.
 *<br>Note that only one point is proposed, even multiple solutions exist.
 */
  virtual CATFrFCCvParam GetCCvParam() const = 0;

  /**
 * Returns all the global parameters of points on curve equivalent to input point,
 * if any.
 *<br>Note that only one point is proposed on each curve, even if multiple solutions exist.
 */
  virtual void GetAllCCvParamsEqualToPoint(
    CATLONG32 &oNbPoints,
    CATFrFCCvParam *&oPoints) const = 0;

  /**
 * Set the point from which the min distance with the curve will be done.
 */
  virtual void SetPoint(const CATMathPoint &iPoint) = 0;
};

// We compute just ONE result: the first result (No Next() result)
// Result can be out of the Block Limitation of the CompositeCurve...
ExportedByCATGMOperatorsInterfaces void CATPGMComputeDistanceMinPtCcv(
  CATGeoFactory *iFactory,
  CATFrFCompositeCurve *iCcv,
  const CATMathPoint &iPoint,
  CATLONG32 &oCrvIndex,
  CATCrvParam &oCrvParam);

ExportedByCATGMOperatorsInterfaces CATPGMFrFDistanceMinPtCcv *CATPGMCreateDistanceMin(
  CATGeoFactory *iWhere,
  const CATMathPoint &iPt,
  CATFrFCompositeCurve *iCcv,
  CATSkillValue iMode = BASIC);

ExportedByCATGMOperatorsInterfaces CATPGMFrFDistanceMinPtCcv *CATPGMCreateFrFDistanceMinPtCcv(
  CATGeoFactory *iFactory,
  CATFrFCompositeCurve *iCcv,
  const CATMathPoint &iPoint);

#endif /* CATPGMFrFDistanceMinPtCcv_h_ */
