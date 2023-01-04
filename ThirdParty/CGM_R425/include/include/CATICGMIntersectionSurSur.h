#ifndef CATICGMIntersectionSurSur_h_
#define CATICGMIntersectionSurSur_h_

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
#include "CATCollec.h"
#include "CATIntersectionOrientation.h"

class CATCGMAttribute;
class CATCartesianPoint;
class CATCurve;
class CATEdgeCurve;
class CATGeometry;
class CATMathBox;
class CATPCurve;
class CATPlane;
class CATPointOnSurface;
class CATSetOfCrvParams;
class CATSurLimits;
class CATSurParam;
class CATSurface;
class CATPointOnEdgeCurve;
class CATLISTP(CATEdgeCurve);
class CATLISTP(CATPCurve);

extern ExportedByCATGMModelInterfaces IID IID_CATICGMIntersectionSurSur;

/**
 * Class defining the operator of the intersection of two surfaces.
 *<br>The operator outputs the isolated solutions (points, curves) and the
 * overlapping solutions (surfaces).
 *<ul>
 *<li>The CATICGMIntersectionSurSur operator is created with the <tt>CATCGMCreateIntersection</tt> method and 
 * directly released with the <tt>Release</tt> method.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. 
 *<li>In both cases, the result is accessed with specific interators, one for the solution points,
 * another for the solution curves and a last one for the solution surfaces.
 *</ul>
 */
class ExportedByCATGMModelInterfaces CATICGMIntersectionSurSur: public CATICGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATICGMIntersectionSurSur();

  /**
 * Returns the number of solution points.
 * @return
 * The number of solutions.
 */
  virtual CATLONG32 GetNumberOfPoints() const = 0;

  /**
 * Returns the number of solution curves.
 * @return
 * The number of solutions.
 */
  virtual CATLONG32 GetNumberOfCurves() const = 0;

  /**
 * Returns the number of solution surfaces.
 * @return
 * The number of solutions.
 */
  virtual CATLONG32 GetNumberOfSurfaces() const = 0;

  /**
 * Initializes the iterator of the resulting points.
 *<br>By default, the initialization is performed once the operator runs,
 * and this is therefore only used to read the solutions again.
 */
  virtual void BeginningPoint() = 0;

  /**
 * Skips to the next solution point of <tt>this</tt> CATICGMIntersectionSurSur operator.
 *<br>After <tt>BeginningPoint</tt>, it skips to the first point. 
 * @return
 * The existence of the next solution.
 * <br><b>Legal values</b>:
 *<dl><dt><tt>TRUE</tt> <dd>if there is a solution point
 *    <dt><tt>FALSE</tt> <dd>no more solution point.</dl>
 */
  virtual CATBoolean NextPoint() = 0;

  /**
 * Retrieves the parameters on each surface of the next solution point of <tt>this</tt> CATICGMIntersectionSurSur operator.
 * @param ioSurParam1
 * The parameter on the first surface.
 * @param ioSurParam2
 * The parameter on the second surface.
 */
  virtual void GetSurParam(CATSurParam &ioSurParam1, CATSurParam &ioSurParam2) = 0;

  /**
 * Creates the next solution point on a surface of <tt>this</tt> CATICGMIntersectionSurSur operator.
 * @param iSurface
 * The pointer to one of the intersecting surface.
 * @return
 * The pointer to the created point on surface. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
  virtual CATPointOnSurface *GetPointOnSurface(CATSurface *iSurface) = 0;

  /**
 * Creates the next solution point of <tt>this</tt> CATICGMIntersectionSurSur operator.
 * @return
 * The pointer to the created point. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
  virtual CATCartesianPoint *GetCartesianPoint() = 0;

  /**
 * Initializes the iterator of the solution curves of <tt>this</tt> 
 * CATICGMIntersectionSurSur operator.
 *<br>By default, the initialization is performed once the operator runs, 
 * and this is therefore only used to read the solutions again.
 */
  virtual void BeginningCurve() = 0;

  /**
 * Skips to the next solution curve of <tt>this</tt> CATICGMIntersectionSurSur operator.
 *<br>After <tt>BeginningCurve</tt>, it skips to the first curve. 
 * @return
 * The existence of the next solution.
 * <br><b>Legal values</b>:
 *<dl><dt><tt>TRUE</tt> <dd>if there is a solution curve
 *    <dt><tt>FALSE</tt> <dd>no more solution curve.</dl>
 */
  virtual CATBoolean NextCurve() = 0;

  /**
 * Creates the next solution curve of <tt>this</tt> CATICGMIntersectionSurSur operator.
 * @param iSurface
 * The pointer to the surface on which the curve is created.
 * @return
 * The pointer to the created curve on surface. A new curve is created each time this method is called.
 * If you do not want to keep the created curve, use the @href CATICGMContainer#Remove method.
 */
  virtual CATPCurve *GetPCurve(CATSurface *iSurface) = 0;

  /**
 * Creates the next solution curve 
 * as a CATPCurve pointer.
 *<br>Creates the object if necessary.
 * @param iIndexOperand
 * <dl><dt><tt>0</tt><dd> on the first surface operand
 *    <dt><tt>1</tt><dd> on the second surface operand</dl>
 */
  virtual CATPCurve *GetPCurve(CATLONG32 iIndexOperand) = 0;

  /**
 * Creates the next solution curve of <tt>this</tt> CATICGMIntersectionSurSur operator.
 * @return
 * The pointer to the created curve. A new curve is created each time this method is called.
 * If you do not want to keep the created curve, use the @href CATICGMContainer#Remove method.
 */
  virtual CATCurve *GetCurve() = 0;

  /**
 * Creates the next solution curve as an edge curve.
 * @return
 * The pointer to the created edge curve, composed of a part of the two curves lying on each surface. 
 * A new curve is created each time this method is called.
 * If you do not want to keep the created curve, use the @href CATICGMContainer#Remove method.
 */
  virtual CATEdgeCurve *GetEdgeCurve() = 0;

  /**
 * Creates the next solution curve as an edge curve.
 * @param oP1
 * The pointer to the created point representing the first extremity of the solution curve.
 * A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 * @param oP2
 * The pointer to the created point representing the last extremity of the solution curve.
 * A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 * @return
 * The pointer to the created edge curve, composed of a part of the two curves lying on each surface. 
 * A new curve is created each time this method is called.
 * If you do not want to keep the created curve, use the @href CATICGMContainer#Remove method.
 */
  virtual CATEdgeCurve *GetEdgeCurve(
    CATPointOnEdgeCurve *&oP1,
    CATPointOnEdgeCurve *&oP2) = 0;

  /**
 * Returns the signature of the intersection edge with regards to the surface normals.
 * @param iSurface
 * The pointer to the surface (first or second operand) for which the signature
 * is returned.
 * @return
 * The signature on <tt>iSurface</tt> such that:
 * Let the natural way of the intersection edge at the starting point being
 * such that the tangent at this point has the same direction as the
 * vector product of the normals of each surface. 
 *<br>Consider that the surface normal represents the outside of the matter
 * delimited by a surface. A positive signature implies that the resulting 
 * matter of the intersection is on the edge left.
 * <dl><dt><tt>CATIntersectionSignPositive</tt><dd>The resulting 
 * matter of the intersection is on the edge left.
 *     <dt><tt>CATIntersectionSignNegative</tt><dd>The resulting 
 * matter of the intersection is on the edge right.
 * </dl> 
 */
  virtual CATIntersectionSign GetSignatureOn(CATSurface *iSurface) = 0;

  /**
 * Initializes the iterator of the solution surfaces.
 *<br>By default, the initialization is performed once the operator runs,
 * and this is therefore only used to read the solutions again.
 */
  virtual void BeginningSurface() = 0;

  /**
 * Skips to the next solution surface of <tt>this</tt> CATICGMIntersectionSurSur operator.
 *<br>After <tt>BeginningSurface</tt>, it skips to the first surface. 
 * @return
 * The existence of the next solution.
 * <br><b>Legal values</b>:
 *<dl><dt><tt>TRUE</tt> <dd>if there is a solution surface
 *    <dt><tt>FALSE</tt> <dd>no more solution surface.</dl>
 */
  virtual CATBoolean NextSurface() = 0;

  /**
 * Returns the boundaries of the next solution surface.
 * <br>The boundaries are given on one input surface.
 * @param iSurface
 * The pointer to the surface on which the curves are defined.
 * @param oListOfPCurvesOrientation
 * The array of pointers to the relative orientation of each PCurve with respect to the loop.
 * If <tt>NULL</tt>, this is not output. This array is allocated by the method, you
 * have to <tt>delete</tt> it after use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATIntersectionOrientationOpposite</tt>
 * <dd>The orientation of the curve and the loop are opposite.
 *     <dt><tt>CATIntersectionOrientationSame</tt><dd>The loop and the curve have the same orientation.</dl> 
 * @param oContourOrientation
 * The relative orientation of the loop generated by the CATPCurves and <tt>iSurface</tt>. 
 * If <tt>NULL</tt>, this is not output.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATIntersectionOrientationOpposite</tt>
 * <dd>The orientation of <tt>iSurface</tt> and the loop are opposite.
 *     <dt><tt>CATIntersectionOrientationSame</tt><dd><tt>iSurface</tt> and the loop have the same orientation.</dl> 
 * @return 
 * The list of the curves defining the boundary on <tt>iSurface</tt>.
 */
  virtual CATLISTP(CATPCurve) GetSurfaceBoundaries(
    CATSurface *iSurface,
    CATIntersectionOrientation **oListOfPCurvesOrientation = NULL,
    CATIntersectionOrientation *oContourOrientation = NULL) = 0;

  /**
 * Returns the boundaries of the next solution surface.
 * <br>The boundaries are given on both input surfaces.
 * @param oListOfPCurvesOrientation
 * The array of pointers to the relative orientation of each PCurve (on the first input surface,
 * then on the second input surface) with respect to the loop. 
 * If <tt>NULL</tt>, this is not output. This array is allocated by the method, you
 * have to <tt>delete</tt> it after use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATIntersectionOrientationOpposite</tt>
 * <dd>The orientation of the curve and the loop are opposite.
 *     <dt><tt>CATIntersectionOrientationSame</tt><dd>The loop and the curve have the same orientation.</dl> 
 * @param oContourOrientation1
 * The relative orientation of the loop generated by the CATPCurves and the first input surface. 
 * If <tt>NULL</tt>, this is not output.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATIntersectionOrientationOpposite</tt>
 * <dd>The orientation of the first input surface and the loop are opposite.
 *     <dt><tt>CATIntersectionOrientationSame</tt><dd>The first input surface and the loop have the same orientation.</dl> 
 * @param oContourOrientation2
 * The relative orientation of the loop generated by the CATPCurves and the second input surface. 
 * If <tt>NULL</tt>, this is not output.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATIntersectionOrientationOpposite</tt>
 * <dd>The orientation of the second input surface and the loop are opposite.
 *     <dt><tt>CATIntersectionOrientationSame</tt><dd>The second input surface and the loop have the same orientation.</dl> 
 * @return 
 * The list of the edge curves defining the boundary, 
 * each edge curve representing the PCurves on each input surface. 
 */
  virtual CATLISTP(CATEdgeCurve) GetSurfaceBoundaries(
    CATIntersectionOrientation **oListOfPCurvesOrientation,
    CATIntersectionOrientation *oContourOrientation1,
    CATIntersectionOrientation *oContourOrientation2) = 0;

  /**
 * Modifies the surface domains to take into account for <tt>this</tt>
 * CATICGMIntersectionSurSur operator (<tt>ADVANCED</tt> mode).
 *<br> It does not change the current surface limitations.
 * @param iNewLimitsForSurface1
 * The pointer to the new domain of the first surface. If <tt>NULL</tt>, the current limitation of the first
 * curve is used.
 * @param iNewLimitsForSurface2
 * The pointer to the new domain of the second surface. If <tt>NULL</tt>, the current limitation of the second
 * curve is used.
 */
  virtual void SetLimits(
    CATSurLimits *iNewLimitsForSurface1,
    CATSurLimits *iNewLimitsForSurface2) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMIntersectionSurSur(); // -> delete can't be called
};

#endif /* CATICGMIntersectionSurSur_h_ */
