/* -*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1999
//==========================================================================
//
// CATCurveAffineSupport:
// Abstract class of the affine support of a curve.
/**
 * Interface representing the operator to known if a curve is planar (or linear)
 * and which return the corresponding plane (or line).
 *<ul>
 *<li>The CATCurveAffineSupport operator is designed to be open to external 
 * implementations.
 *<li>It is created with the <tt>CreateCurveAffineSupport</tt> method within a 
 *<tt>CATGeoFactory</tt>, but is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed. 
 *<li>In case of <tt>ADVANCED</tt>
 * mode, the user may precise options with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method . 
 *<tt>SetLimits</tt> method.
 *<li> The operator is removed from the memory with the <tt>Remove</tt> method.
 *</ul>
 */
//
//==========================================================================
//
// Usage notes:
//  The tolerance used is by default the factory resolution. It corresponds to 
//  the max distance between the curve and its approximate affine space. If
//  this tolerance is overpassed, the AffineSupport dimension is increased.
//  The default tolerance can be changed thanks to the SetTolerance method.
//
//========================================================================== 

#ifndef CATCurveAffineSupport_H
#define CATCurveAffineSupport_H

#include "CATCreateCurveAffineSupport.h"
#include "CreateCurveAffineSupport.h"

#include "CATMathDef.h"
#include "Y30A3HGG.h"
#include "CATGeoOperator.h"
#include "CATCurveAffineSupport_AffineSpace.h"

class CATGeoFactory;
class CATCurve;
class CATPointOnSurface;
class CATCrvLimits;
class CATMathPoint;
class CATMathLine;
class CATMathPlane;

//-----------------------------------------------------------------------------
/**
* @nodoc
* Class defining the operator to retrieve the affine support of a curve or a wire.
* <ul>
* <li>A CATCurveAffineSupport operator is created with the <tt>CATCreateCurveAffineSupport</tt> global function:
* It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
* <li>The result is accessed with the <tt>GetMathPoint</tt>, <tt>GetMathLine</tt> or <tt>GetMathPlane</tt> method. 
* <li>Using the <tt>Setxxx</tt> method(s) requires to create the operator in ADVANCED mode and start the computation with the
* <tt>Run</tt> method.
* </ul>
*/
class ExportedByY30A3HGG CATCurveAffineSupport  : public CATGeoOperator {
  CATCGMVirtualDeclareClass(CATCurveAffineSupport);
public:
  /**
 * Destructor.
 */ 
  virtual ~CATCurveAffineSupport();
  // Constructor.
  CATCurveAffineSupport(CATGeoFactory * iFactory) ;


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
 * Used with the GetAffineSpace method.
 */
  enum AffineSpace { POINT = CATCurveAffineSupport_POINT, LINE = CATCurveAffineSupport_LINE, PLANE = CATCurveAffineSupport_PLANE, SPACE = CATCurveAffineSupport_SPACE};
 /**
 * Returns the space dimension type of the curve.
 * @return
 * The affine space.
 */
  virtual CATCurveAffineSupport::AffineSpace GetAffineSpace() const = 0;

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

};
#endif
