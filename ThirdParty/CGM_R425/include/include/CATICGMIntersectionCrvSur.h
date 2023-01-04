#ifndef CATICGMIntersectionCrvSur_h_
#define CATICGMIntersectionCrvSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMGeoOperator.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATIntersectionSign.h"

class CATCartesianPoint;
class CATCurve;
class CATEdgeCurve;
class CATGeoFactory;
class CATMathBox;
class CATMathSetOfPointsND;
class CATPCurve;
//class CATPipeData;
class CATPointOnCurve;
class CATPointOnSurface;
class CATSurLimits;
class CATSurface;
class CATSurParam;
class CATCrvParam;
class CATCrvLimits;

extern ExportedByCATGMModelInterfaces IID IID_CATICGMIntersectionCrvSur;

//#endif
/**
 * Class defining the operator of the intersection of a curve and a surface.
 *<br>The operator outputs the isolated solutions (points) and the
 * overlapping solutions (curves).
 *<ul>
 *<li>The CATICGMIntersectionCrvSur operator is created with the <tt>CATCGMCreateIntersection</tt> method and 
 * directly released with the <tt>Release</tt> method.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. The advanced mode also allows you to
 * run the same operator with different curves or surfaces.
 *<li>In both cases, the result is accessed with two specific interators, one for the solution points,
 * the other for the solution curves.
 *</ul>
 */
class ExportedByCATGMModelInterfaces CATICGMIntersectionCrvSur: public CATICGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATICGMIntersectionCrvSur();

  //
  //  Getting the isolated intersections between the curve and the surface
  //
  /**
 * Returns the number of isolated solution points of <tt>this</tt> CATICGMIntersectionCrvSur operator.
 * @return
 * The number of isolated solution points.
 */
  virtual CATLONG32 GetNumberOfPoints() const = 0;

  /**
 * Initializes the iterator of the resulting points.
 *<br>By default, the initialization is performed once the operator runs, 
 * and this is therefore only used to read the solutions again.
 */
  virtual void BeginningPoint() = 0;

  /**
 * Skips to the next solution point of <tt>this</tt> CATICGMIntersectionCrvSur operator.
 *<br>After <tt>BeginningPoint</tt>, it skips to the first point. 
 * @return
 * The existence of the next solution.
 * <br><b>Legal values</b>:
 *<dl><dt><tt>TRUE</tt> <dd>if there is a solution point
 *    <dt><tt>FALSE</tt> <dd>no more solution point.</dl>
 */
  virtual CATBoolean NextPoint() = 0;

  /**
 * Createss the next solution point of <tt>this</tt> CATICGMIntersectionCrvSur operator.
 * @return
 * The pointer to the created point. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
  virtual CATCartesianPoint *GetCartesianPoint() = 0;

  /**
 * Creates the next solution point on curve of <tt>this</tt> CATICGMIntersectionCrvSur operator.
 * @return
 * The pointer to the created point on curve. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
  virtual CATPointOnCurve *GetPointOnCurve() = 0;

  /**
 * Returns the parameter on the curve of the next solution point of <tt>this</tt> CATICGMIntersectionCrvSur operator.
 * @return
 * The parameter.
 */
  virtual CATCrvParam GetCurveParam() const = 0;

  /**
 * Returns the next solution point on surface of <tt>this</tt> CATICGMIntersectionCrvSur operator.
 * @return
 * The pointer to the created point on surface. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
  virtual CATPointOnSurface *GetPointOnSurface() = 0;

  /**
 * Returns the parameter on the surface of the next solution point of <tt>this</tt> CATICGMIntersectionCrvSur operator.
 * @return
 * The parameter.
 */
  virtual CATSurParam GetSurfaceParam() const = 0;

  /**
 * Returns the relative orientation of the curve tangent and the surface normal at the intersection point.
 * <dl><dt><tt>CATIntersectionSignNegative</tt><dd> The scalar product between the curve tangent at the intersection point, 
 * and the surface normal at the intersection point is negative. 
 *    <dt><tt>CATIntersectionSignPositive</tt><dd> The scalar product between the curve tangent at the intersection point, 
 * and the surface normal at the intersection point is positive. 
 * </dl>
 */
  virtual CATIntersectionSign GetSignatureOn() const = 0;

  //
  //  Getting the confusion solution
  //
  /**
 * Returns the number of solution curves of <tt>this</tt> CATICGMIntersectionCrvSur operator.
 * @return
 * The number of solution curves.
 */
  virtual CATLONG32 GetNumberOfCurves() const = 0;

  /**
 * Initializes the iterator of the solution curves of <tt>this</tt> 
 * CATICGMIntersectionCrvSur operator.
 * <br>By default, the initialization is performed once the operator runs, 
 * and this is therefore only used to read the solutions again.
 */
  virtual void BeginningCurve() = 0;

  /**
 * Skips to the next solution curve of <tt>this</tt> CATICGMIntersectionCrvSur operator.
 * <br>After <tt>BeginningCurve</tt>, it skips to the first curve. 
 * @return
 * The existence of the next solution.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>TRUE</tt> <dd>if there is a solution curve
 *    <dt><tt>FALSE</tt> <dd>no more solution curve.</dl>
 */
  virtual CATBoolean NextCurve() = 0;

  /**
 * Creates the next solution curve of <tt>this</tt> CATICGMIntersectionCrvSur operator.
 * @return
 * The pointer to the created curve on surface. A new curve is created each time this method is called.
 * If you do not want to keep the created curve, use the @href CATICGMContainer#Remove method.
 */
  virtual CATPCurve *GetPCurve() = 0;

  /**
 * Creates the next solution curve as an edge curve.
 * @return
 * The pointer to the created edge curve, composed of a part of the initial curve, and the corresponding
 * part as a curve on the surface. 
 * A new curve is created each time this method is called.
 * If you do not want to keep the created curve, use the @href CATICGMContainer#Remove method.
 */
  virtual CATEdgeCurve *GetEdgeCurve() = 0;

  /**
 * Returns the domain of the next resulting curve of <tt>this</tt>
 * CATICGMIntersectionCrvSur operator.
 * @return
 * The corresponding limitations.
 */
  virtual CATCrvLimits GetCurveBoundaries() const = 0;

  /**
 * Modifies the curve domain to take into account for <tt>this</tt> CATICGMIntersectionCrvSur
 * operator (<tt>ADVANCED</tt> mode).
 * <br> It does not change the current curve 
 * limitations.  
 * @param iNewLimits
 * The new limitations of the curve.
 */
  virtual void SetLimits(const CATCrvLimits &iNewLimits) = 0;

  /**
 * Modifies the surface domain to take into account for <tt>this</tt> CATICGMIntersectionCrvSur
 * operator (<tt>ADVANCED</tt> mode).
 * <br> It does not change the current surface 
 * limitations. 
 * @param iNewLimits
 * The new limitations of the surface.
 */
  virtual void SetLimits(const CATSurLimits &iNewLimits) = 0;

  /**
 * Defines the intersection with another curve (<tt>ADVANCED</tt> mode).
 * @param iNewCurve
 * The pointer to the new curve.
 */
  virtual void SetCurve(const CATCurve *iNewCurve) = 0;

  /**
 * Defines the intersection with another second surface (<tt>ADVANCED</tt> mode).
 * @param iNewSurface
 * The pointer to the new surface.
 */
  virtual void SetSurface(const CATSurface *iNewSurface) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMIntersectionCrvSur(); // -> delete can't be called
};

#endif /* CATICGMIntersectionCrvSur_h_ */
