#ifndef CATIPGMCurveAffineSupport_h_
#define CATIPGMCurveAffineSupport_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include "CATCurveAffineSupport_AffineSpace.h"

/**
* @level Protected
* @usage U1
*/

class CATCrvLimits;
class CATCurve;
class CATGeoFactory;
class CATMathLine;
class CATMathPlane;
class CATMathPoint;
class CATPointOnSurface;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMCurveAffineSupport;

/**
* @nodoc
* Class defining the operator to retrieve the affine support of a curve or a wire.
* <ul>
* <li>A CATIPGMCurveAffineSupport operator is created with the <tt>CATPGMCreateCurveAffineSupport</tt> global function:
* It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
* <li>The result is accessed with the <tt>GetMathPoint</tt>, <tt>GetMathLine</tt> or <tt>GetMathPlane</tt> method. 
* <li>Using the <tt>Setxxx</tt> method(s) requires to create the operator in ADVANCED mode and start the computation with the
* <tt>Run</tt> method.
* </ul>
*/
class ExportedByCATGMModelInterfaces CATIPGMCurveAffineSupport: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMCurveAffineSupport();

  /**
 * Modifies the CATCurve to take into account.
 * It does not change the current CATCurve limitations. <br>
 * To be used in <tt>ADVANCED</tt> mode before calling the <tt>Run</tt> method.
 * @param iCurve
 * The new curve.
 */
  virtual void SetCurve(CATCurve *iCurve) = 0;

  /**
 * Modifies the family of CATCurves to take into account.
 * It does not change the current curves' limitations. <br>
 * To be used in <tt>ADVANCED</tt> mode before calling the <tt>Run</tt> method.
 * @param iCurves
 * The new list of curves.
 * @param iNbCurves
 * The number of new curves.
 */
  virtual void SetCurves(CATCurve **iCurves, const CATLONG32 iNbCurves) = 0;

  /**
 * Modifies the CATCurve limitation to take into account (in the case of only one curve
 * specified).
 * To be used in <tt>ADVANCED</tt> mode before calling the <tt>Run</tt> method.
 * @param iLimits
 * The new limits.
 */
  virtual void SetLimits(CATCrvLimits &iLimits) = 0;

  /**
 * Modifies the limitation to take into account for a given CATCurve of the family
 * (in the case of a family of curves specified).
 * <br> It does not change the other CATCurve limitations. 
 * To be used in <tt>ADVANCED</tt> mode before calling the <tt>Run</tt> method.
 * @param iCurve
 * The curve whose limits are to be modified.
 * @param iLimits
 * The new limits.
 */
  virtual void SetLimits(const CATCurve *iCurve, CATCrvLimits &iLimits) = 0;

  /**
 * Modifies the default tolerance (which is the resolution).
 * <br>NOT IMPLEMENTED.
 * @param iTolerance
 * The new tolerance.
 */
  virtual void SetTolerance(const double iTolerance) = 0;

  /**
 * Specifies that the plane orientation should be stable when the curves are planar.
 * An array of CurveOrientation (+1 or -1) containing the same number of
 * elements as the number of curves should also be specified
 * (the process used consists in computing the natural rotation side of the oriented curves)
 * @param iCurveOrientation
 * The array of curve orientations.
 */
  virtual void SetStabilizePlaneOrientation(short *iCurveOrientation) = 0;

 /**
 * Returns the space dimension type of the curve.
 * @return
 * The affine space.
 */
  virtual CATCurveAffineSupport_AffineSpace GetAffineSpace() const = 0;

  /**
  * When the affine space is a POINT, returns the CATMathPoint corresponding to that point.
  * @param oMathPoint
  * The mathematical point corresponding to the affine space.
  */
  virtual void GetMathPoint(CATMathPoint &oMathPoint) const = 0;

  /**
  * When the affine space is a LINE, returns the CATMathLine corresponding to that line.
  * @param oMathLine
  * The mathematical line corresponding to the affine space.
  */
  virtual void GetMathLine(CATMathLine &oMathLine) const = 0;

 /**
  * When the affine space is a PLANE, returns the CATMathPlane corresponding to that plane.
  * @param oMathPlane
  * The mathematical plane corresponding to the affine space.
  */
  virtual void GetMathPlane(CATMathPlane &oMathPlane) const = 0;

  /**
 * Returns the maximal distance from the returned affine space.
 * @return
 * The maximum distance.
 */
  virtual double GetDistance() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMCurveAffineSupport(); // -> delete can't be called
};

#endif /* CATIPGMCurveAffineSupport_h_ */
