#ifndef CATIPGMIntersectionSurSur_h_
#define CATIPGMIntersectionSurSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @level Protected
 * @usage U3
 */

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
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
class CATMathSetOfPointsNDTwoTangents;
class CATCrvParam;
class CATMathSetOfLongs;
class CATMathSetOfPointsND;
class CATPointOnEdgeCurve;
class CATSetOfSurParams;
class CATLISTP(CATEdgeCurve);
class CATLISTP(CATPCurve);

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMIntersectionSurSur;

/**
 * Class defining the operator of the intersection of two surfaces.
 *<br>The operator outputs the isolated solutions (points, curves) and the
 * overlapping solutions (surfaces).
 *<ul>
 *<li>The CATIPGMIntersectionSurSur operator is created with the <tt>CATPGMCreateIntersection</tt> method and 
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
class ExportedByCATGMModelInterfaces CATIPGMIntersectionSurSur: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMIntersectionSurSur();

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

  /** @nodoc 
  * Do not use.
  */
  virtual CATLONG32 GetNumberOfCurveSolutions() const = 0;

  /**
 * Returns the number of solution surfaces.
 * @return
 * The number of solutions.
 */
  virtual CATLONG32 GetNumberOfSurfaces() const = 0;

  /**
 * @nodoc
 * Retrieves the definition points of the resulting curve.
 * @param oSet
 * The set of points.
 */
  virtual void GetDefinitionPoints(CATMathSetOfPointsNDTwoTangents &oSet) const = 0;

  /** @nodoc 
  * Retrieves singular points on resulting Curve (<tt>ADVANCED</tt> mode).
  * <br> Init points must have been set before running operator (with method SetStartingPoints).
  * <br> Result Curve must already be created (GetCurve, GetPCurve, GetEdgeCurve).
  * @param oSetOfSingParams
  * The set of Curve parameters of singular points.
  * <br> To be deleted after use.
  */
  virtual void GetSingularPoints(CATSetOfCrvParams *&oSetOfSingParams) = 0;

  /** @nodoc
  * Retrieves exit points on resulting Curve (<tt>ADVANCED</tt> mode).
  * <br> Init points must have been set before running operator (with method SetStartingPoints).
  * <br> Result Curve must already be created (GetCurve, GetPCurve, GetEdgeCurve).
  * @param SetOfExitParams
  * The set of Curve parameters of init and exit points.
  * <br> To be deleted after use.
  */
  virtual void GetExitPoints(CATSetOfCrvParams *&SetOfExitParams) = 0;

  /** @nodoc 
  * Retrieves exit points on resulting Curve by index (<tt>ADVANCED</tt> mode).
  * <br> Init points must have been set before running operator (with method SetStartingPoints).
  * <br> Result Curve must already be created (GetCurve, GetPCurve, GetEdgeCurve).
  * @param ExitNumero
  * The index of point to retrieve.
  * @param ExitParam
  * The Curve parameter of the point.
  */
  virtual void GetExitPoint(CATLONG32 ExitNumero, CATCrvParam &ExitParam) = 0;

  /** @nodoc 
  * Retrieves the indexes of exit points on resulting Curve in order of parametrization (<tt>ADVANCED</tt> mode).
  * <br> Init points must have been set before running operator (with method SetStartingPoints).
  * @return
  * The set of indexes.
  */
  virtual CATMathSetOfLongs *GetExitNumero() = 0;

  /** @nodoc
  * Retrieves the Init points that were set.
  * (<tt>ADVANCED</tt> mode).
  * @return
  * The set of Init points.
  */
  virtual CATMathSetOfPointsND *GetInitPoints() = 0;

  /** @nodoc
  * Returns a diagnostic for TangentDesign of Surface boundaries, in the case of
  * Surface solution.
  * @param oCheckGap
  * Maximum gap of Curve compared to tolerance.
  * <br><b>Legal values</b>:
  * <dl><dt><tt>0</tt></dt><dd> gap is lower than 0.1*tolerance.</dl>
  *     <dt><tt>1</tt> </dt><dd> gap is greater than tolerance(10e-3)
  *     <dt><tt>2</tt></dt><dd> gap is greater than 0.1*tolerance(10e-4).</dl>
  * @return
  * <br><b>Legal values</b>:
  * <dl><dt><tt>1</tt> </dt><dd> is tangent.
  *     <dt><tt>0</tt></dt><dd> isn't tangent.</dl>
  */
  virtual int GetTangentDiagnostic(int *oCheckGap) = 0;

  /**
 * Initializes the iterator of the resulting points.
 *<br>By default, the initialization is performed once the operator runs,
 * and this is therefore only used to read the solutions again.
 */
  virtual void BeginningPoint() = 0;

  /**
 * Skips to the next solution point of <tt>this</tt> CATIPGMIntersectionSurSur operator.
 *<br>After <tt>BeginningPoint</tt>, it skips to the first point. 
 * @return
 * The existence of the next solution.
 * <br><b>Legal values</b>:
 *<dl><dt><tt>TRUE</tt> <dd>if there is a solution point
 *    <dt><tt>FALSE</tt> <dd>no more solution point.</dl>
 */
  virtual CATBoolean NextPoint() = 0;

  /**
 * Retrieves the parameters on each surface of the next solution point of <tt>this</tt> CATIPGMIntersectionSurSur operator.
 * @param ioSurParam1
 * The parameter on the first surface.
 * @param ioSurParam2
 * The parameter on the second surface.
 */
  virtual void GetSurParam(CATSurParam &ioSurParam1, CATSurParam &ioSurParam2) = 0;

  /**
 * Creates the next solution point on a surface of <tt>this</tt> CATIPGMIntersectionSurSur operator.
 * @param iSurface
 * The pointer to one of the intersecting surface.
 * @return
 * The pointer to the created point on surface. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
  virtual CATPointOnSurface *GetPointOnSurface(CATSurface *iSurface) = 0;

  /**
 * Creates the next solution point of <tt>this</tt> CATIPGMIntersectionSurSur operator.
 * @return
 * The pointer to the created point. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
  virtual CATCartesianPoint *GetCartesianPoint() = 0;

  /**
 * Initializes the iterator of the solution curves of <tt>this</tt> 
 * CATIPGMIntersectionSurSur operator.
 *<br>By default, the initialization is performed once the operator runs, 
 * and this is therefore only used to read the solutions again.
 */
  virtual void BeginningCurve() = 0;

  /**
 * Skips to the next solution curve of <tt>this</tt> CATIPGMIntersectionSurSur operator.
 *<br>After <tt>BeginningCurve</tt>, it skips to the first curve. 
 * @return
 * The existence of the next solution.
 * <br><b>Legal values</b>:
 *<dl><dt><tt>TRUE</tt> <dd>if there is a solution curve
 *    <dt><tt>FALSE</tt> <dd>no more solution curve.</dl>
 */
  virtual CATBoolean NextCurve() = 0;

  /**
 * Creates the next solution curve of <tt>this</tt> CATIPGMIntersectionSurSur operator.
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
 * Creates the next solution curve of <tt>this</tt> CATIPGMIntersectionSurSur operator.
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
 * @nodoc
 * Returns the crossing of the intersection edge 
 * with regards to the surface normals.
 * <br>Especially designed when the 2 surfaces are tangents.
 * @param iSurface
 * The pointer to the surface (first or second operand) for which the crossing
 * is returned.
 * @return
 *<br>Consider that the surface normal represents the outside of the matter
 * delimited by a surface.
 * The crossing on <tt>iSurface</tt> can be :
 * <dl><dt><tt>CATIntersectionCrossingTrue</tt><dd>When the intersection is frank.
 *     <dt><tt>CATIntersectionCrossingFalsePositive</tt><dd>
 *     <dt><tt>CATIntersectionCrossingFalseNegative</tt><dd>
 *     <dt><tt>CATIntersectionCrossingUnknown</tt><dd></dl>
 */
  virtual CATIntersectionCrossing GetCrossingOn(CATSurface *iSurface) = 0;

  /**
 * @nodoc
 * Retrieves the index of starting and ending points of the result curve.
 * The numerotation of the result curve extremities is done as follows:
 * The index of first result curve begins at <tt>0</tt>.
 * <br>If the curves dont share any extremity, the value of indexes are incremented:
 * (0,1), (2,3), ... (2*NbCurves-2, 2*NbCurves-1).
 * <br> If an extremity is common, the same value is assigned:
 * (0,1), (1,2) : the last point of the first curve is identical to the first point of
 * the second curve.
 * <br> If the curve is closed , result is (0, 0).
 */
  virtual void GetStartingPointsIndex(CATLONG32 &oBegin, CATLONG32 &oEnd) = 0;

  /**
 * Initializes the iterator of the solution surfaces.
 *<br>By default, the initialization is performed once the operator runs,
 * and this is therefore only used to read the solutions again.
 */
  virtual void BeginningSurface() = 0;

  /**
 * Skips to the next solution surface of <tt>this</tt> CATIPGMIntersectionSurSur operator.
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
 * @nodoc
 * Same as previous with Indexes of the curves of the loop.
 */
  virtual CATLISTP(CATEdgeCurve) GetSurfaceBoundaries(
    CATIntersectionOrientation **oListOfPCurvesOrientation,
    CATIntersectionOrientation *oContourOrientation1,
    CATIntersectionOrientation *oContourOrientation2,
    CATLONG32 *&oStartIndexes,
    CATLONG32 *&oEndIndexes) = 0;

  /**
 * @nodoc
 * Defines the intersection with another second surface (<tt>ADVANCED</tt> mode).
 * @param iNewSecondSurface
 * The pointer to the new second surface.
 */
  virtual void SetSurface(CATSurface *iNewSecondSurface) = 0;

  /**
 * @nodoc
 * Set a 3D Box in which the solutions have to be searched (<tt>ADVANCED</tt> mode).
 * One may calculate this box intersecting the 3D Boxes of the 2 limited surfaces.
 * @param i3DBox
 * The 3D box in which to search.
 */
  virtual void SearchInBox(const CATMathBox &i3DBox) = 0;

  /**
 * Modifies the surface domains to take into account for <tt>this</tt>
 * CATIPGMIntersectionSurSur operator (<tt>ADVANCED</tt> mode).
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

  /** @nodoc 
 * Same as precedent method SetLimits.
  */
  virtual void HoldDomain(
    CATSurLimits *iNewLimitsForSurface1,
    CATSurLimits *iNewLimitsForSurface2) = 0;

  /* Caution : the following method has priority on the previous above SetLimits */
  /* ie the solution can go out of the held domain                     */
  /* In the case of HoldDomain, an error is thrown and no solution is returned */
  /**
 * @nodoc
 * Extrapolates the CATIPGMIntersectionSurSur solution until one of the operands boundary.
 *<br>This method has priority on the <tt>HoldDomain</tt> method: the solution
 * can go outside the domain defined by <tt>HoldDomain</tt>.
 *<br> The <tt>Run</tt> method then should be called before reading solutions.
 */
  virtual void ReachBoundaryOf(CATSurface *iSurface) = 0;

  /** @nodoc 
   * Same method as above, with index of surface as input.
   * @param IndexOperand
   * Index of surface to extrapolate to.
   * <br><b>Legal values</b>:
   *<dl><dt><tt>0</tt> <dd> First surface defined at operator creation.
   *    <dt><tt>1</tt> <dd> Second surface defined at operator creation.</dl>
   */
  virtual void ReachBoundaryOf(CATLONG32 IndexOperand) = 0;

  /**
 * @nodoc
 * Do not use. For specific use only.
 * Authorize solutions close from a boundary to go out of the domain.
 */
  virtual void SetExtrapol(CATBoolean iBoolean) = 0;

  /**
 * @nodoc
 * Imposes initial and/or final points of the resulting surface of
 * a CATIPGMIntersectionSurSur operator. 
 *<br>In case of <tt>ADVANCED</tt> mode.
 * @param iSetOfInitParamsOnSurface1
 * The pointer to a CATSetOfSurParam containing initial and/or final
 * points of the solution on the first surface.
 * @param iSetOfInitParamsOnSurface2
 * The pointer to a CATSetOfSurParam containing initial and/or final
 * points of the solution on the second surface, they should be identical in
 * space with those of the previous CATSetOfSurparam.
 *<br> This argument and the following one give the 
 * definition of the pieces of the CATIPGMIntersectionSurSur.
 * @param iStartingSignatureOnFirstSurface
 * The driving direction of the intersection edge on the first surface
 * with regards to each surface
 * normals at each points of <tt>iSetOfInitPoints</tt>.
 * The natural way of the intersection edge at the starting point
 * is such that the tangent at this point has the same direction as the
 * vector product of the normals of each surface. 
 *<br>Consider that the surface normal represents the outside of the matter
 * delimited by a surface. A positive signature implies that the resulting 
 * matter of the intersection is on the edge left.
 * <dl><dt><tt>CATIntersectionSignPositive</tt><dd>The resulting 
 * matter of the intersection is on the edge left.
 *     <dt><tt>CATIntersectionSignNegative</tt><dd>The resulting 
 * matter of the intersection is on the edge right.
 *     <dt><tt>CATIntersectionSignSameDirection</tt><dd> 
 *     <dt><tt>CATIntersectionSignOppositeDirection</tt><dd>
 *     <dt><tt>CATIntersectionSignUnknown</tt><dd>
 *     <dt><tt>CATIntersectionSignUnset</tt><dd></dl> 
 * @param iTangents
 * When the signature is NonCrossing type, a dimension 3 vector 
 * has to be given to indicate the starting direction.
 * @param iLoopSearch
 * <dl><dt><tt>1</tt><dd>search of the scalop (loop) configurations
 *     <dt><tt>0</tt><dd>otherwise </dl> 
 *<br> The <tt>Run</tt> method then should be called before reading solutions.
 */
  virtual void SetStartingPoints(
    CATSetOfSurParams &iSetOfInitParamsOnSurface1,
    CATSetOfSurParams &iSetOfInitParamsOnSurface2,
    CATIntersectionSign *iStartingSignatureOnFirstSurface,
    double *iTangents = NULL,
    CATBoolean LoopSearch = 1) = 0;

  /**
 * @nodoc
 * When one the surfaces is a plane and only the PCurve on the plane is required, enable
 * canonic solution on the plane.
 */
  virtual void SetCanonicalPCurveOnPlane() = 0;

  /** @nodoc 
  * Do not use.
  */
  virtual void SetUnstableWarning() = 0;

  /** @nodoc 
  * Asks operator not to cut the result Curve when crossing the Init points.
  */
  virtual void SetNonCutting(CATBoolean iDoNotCut = 1) = 0;

  /** @nodoc 
  * Asks operator to keep result Curve in between Init points.
  */
  virtual void SetOnlyBetweenInits(CATBoolean iOnlyBetweenInits = 1) = 0;

  /** @nodoc 
  * Asks operator to reconverge Init points if necessary.
  */
  virtual void SetConvergeInit(CATBoolean iReconv = 1) = 0;

  /** @nodoc 
  * Asks operator to try for linear solutions.
  * <br> They are curves where the surfaces are tangent at each point.
  */
  virtual void SetTangentSol(CATBoolean iBoolean = 1) = 0;

  /** @nodoc
  * Do not use.
  */
  virtual void SetAttribute(CATSurface *iSurface, CATCGMAttribute *iAttribute) = 0;

  /** @nodoc 
  * Do not use.
  */
  virtual CATCGMAttribute *GetAttribute(CATSurface *iSurface) = 0;

  /** @nodoc
  * For performance optimization.
  */
  virtual void SetOptimizedAttribute() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMIntersectionSurSur(); // -> delete can't be called
};

/** @nodoc */
ExportedByCATGMModelInterfaces CATLONG32 CATPGMIntersectionIsNull(
  CATSurface *iSurface1,
  CATSurface *iSurface2,
  CATSurParam &iParam1,
  CATSurParam &iParam2,
  CATSoftwareConfiguration *iConfig = NULL);

#endif /* CATIPGMIntersectionSurSur_h_ */
