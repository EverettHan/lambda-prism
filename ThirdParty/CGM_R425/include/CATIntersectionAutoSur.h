#ifndef CATINTERSECTAUTOSUR_H
#define CATINTERSECTAUTOSUR_H

// Base class header
#include "CATGeoOperator.h"

// Module header
#include "Y30C3XGG.h"

#include "CATIntersectionSign.h"
#include "CATIntersectionOrientation.h"
#include "CATListOfCATEdgeCurves.h"

class CATSurLimit;
class CATSetOfSurParams;

class ExportedByY30C3XGG CATIntersectionAutoSur : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATIntersectionAutoSur);
public:

  //================================================
  //  Constructors / Destructors
  //================================================
  
  /**
  * @nodoc
  * Use the <tt>CreateIntersection</tt> global method.
  */
  CATIntersectionAutoSur(CATGeoFactory *);

  /**
  * Destructor.
  */
  virtual ~CATIntersectionAutoSur();


  //================================================
  //  Set inputs
  //================================================
  
  /**
  * @param iSurface    : The surface to intersect
  * @param iForceReset : Force the operator to reset data
  */
  virtual void SetSurface(      CATSurface * iSurface, 
                          const CATBoolean   iForceReset = FALSE) = 0;


  /**
  * @param iSurLimit : Limitation of surface
  */
  virtual void SetSurLimits(const CATSurLimits & iSurLimit) = 0;

  //-----------------------------------------------------------------------------------------------
  // This method is optional.
  // Note that the polyhedral check is available only in V6, this method should NOT be used in V5.
  //-----------------------------------------------------------------------------------------------
  /**
  * @param iUVParam : UV param of points
  */
  //virtual void SetSeedParams(const CATSetOfSurParams & iUVParam) = 0;


  //================================================
  //  Get results
  //================================================

  //  Points
  //========

  /**
  * Returns the number of solution points.
  * @return
  * The number of solutions.
  */
   virtual CATLONG32 GetNumberOfPoints() const = 0;


   /**
   * Initializes the iterator of the solution points.
   *<br>By default, the initialization is performed once the operator runs,
   * and this is therefore only used to read the solutions again.
   */
   virtual void BeginningPoint() = 0;

   /**
   * Moves the iterator to the next solution point of <tt>this</tt> operator.
   *<br>After <tt>BeginningPoint</tt>, it returns to the first point. 
   * @return
   * The existence of the next solution.
   * <br><b>Legal values</b>:
   *<dl><dt><tt>TRUE</tt> <dd>if there is a solution point
   *    <dt><tt>FALSE</tt> <dd>no more solution point.</dl>
   */
   virtual CATBoolean NextPoint() = 0;

   /**
   * Creates the next solution point on the surface of <tt>this</tt> operator.
   * @param iPointIndex
   * <dl><dt><tt>0</tt><dd> the first CATPointOnSurface
   *    <dt><tt>1</tt><dd> the second CATPointOnSurface </dl>
   * @return
   * The pointer to the created point on surface. A new point is created each time this method is called.
   * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
   */
   virtual CATPointOnSurface * GetPointOnSurface(const CATLONG32 iPointIndex) const = 0;

   /**
   * Retrieves the parameters on the surface of the current solution point of <tt>this</tt> operator.
   * @param oSurParam1
   * The first parameter on the surface.
   * @param oSurParam2
   * The second parameter on the surface.
   */
   virtual void GetSurParam(CATSurParam & oSurParam1,
                            CATSurParam & oSurParam2) const = 0;

   /**
   * Creates the 3D point of the current solution point <tt>this</tt> operator.
   * @return
   * The pointer to the created point. A new point is created each time this method is called.
   * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
   */
   virtual CATCartesianPoint* GetCartesianPoint() const = 0;

   //  Curves
   //========

   /**
   * Returns the number of solution curves.
   * @return
   * The number of solutions.
   */
   virtual CATLONG32 GetNumberOfCurves() const = 0;

   /**
   * Initializes the iterator of the solution curves of <tt>this</tt> 
   *<br>By default, the initialization is performed once the operator runs, 
   * and this is therefore only used to read the solutions again.
   */
   virtual void BeginningCurve() = 0;

   /**
   * Moves the iterator to the next solution curve of <tt>this</tt> operator.
   *<br>After <tt>BeginningCurve</tt>, it returns to the first curve. 
   * @return
   * The existence of the next solution.
   * <br><b>Legal values</b>:
   *<dl><dt><tt>TRUE</tt> <dd>if there is a solution curve
   *    <dt><tt>FALSE</tt> <dd>no more solution curve.</dl>
   */
   virtual CATBoolean NextCurve() = 0; 

//   /**
//   * Creates the next solution curve of <tt>this</tt>  operator.
//   * @return
//   * The pointer to the created curve on surface. A new curve is created each time this method is called.
//   * If you do not want to keep the created curve, use the @href CATICGMContainer#Remove method.
//   */
//   virtual CATPCurve * GetPCurve() = 0; 
//
///**
// * Creates the next solution curve of <tt>this</tt>  operator.
// * @return
// * The pointer to the created curve. A new curve is created each time this method is called.
// * If you do not want to keep the created curve, use the @href CATICGMContainer#Remove method.
// */
//   virtual CATCurve * GetCurve() = 0;

   /**
   * Creates the next solution curve as an edge curve.
   * @return
   * The pointer to the created edge curve, composed of a part of the two curves lying on this surface. 
   * A new curve is created each time this method is called.
   * If you do not want to keep the created curve, use the @href CATICGMContainer#Remove method.
   */
   virtual CATEdgeCurve * GetEdgeCurve() = 0;

///**
// * Creates the next solution curve as an edge curve.
// * @param oP1
// * The pointer to the created point representing the first extremity of the solution curve.
// * A new point is created each time this method is called.
// * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
// * @param oP2
// * The pointer to the created point representing the last extremity of the solution curve.
// * A new point is created each time this method is called.
// * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
// * @return
// * The pointer to the created edge curve, composed of a part of the two curves lying on each surface. 
// * A new curve is created each time this method is called.
// * If you do not want to keep the created curve, use the @href CATICGMContainer#Remove method.
// */
//   virtual CATEdgeCurve * GetEdgeCurve(CATPointOnEdgeCurve *&oP1, 
//				                               CATPointOnEdgeCurve *&oP2) = 0;
//

   /**
   * Returns the signature of the intersection edge with regards to the surface normals.
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
   virtual CATIntersectionSign GetSignatureOn(const short iSignatureIndex) = 0;

   /**
   * @nodoc
   * Returns the crossing of the intersection edge 
   * with regards to the surface normals.
   * <br>Especially designed when the 2 surfaces are tangents.
   * @param iCrossingIndex
   * <dl><dt><tt>0</tt><dd> the first CrossingOn
   *    <dt><tt>1</tt><dd> the second CrossingOn </dl>
   * @return
   *<br>Consider that the surface normal represents the outside of the matter
   * delimited by a surface.
   * The crossing on <tt>iSurface</tt> can be :
   * <dl><dt><tt>CATIntersectionCrossingTrue</tt><dd>When the intersection is frank.
   *     <dt><tt>CATIntersectionCrossingFalsePositive</tt><dd>
   *     <dt><tt>CATIntersectionCrossingFalseNegative</tt><dd>
   *     <dt><tt>CATIntersectionCrossingUnknown</tt><dd></dl>
   */
   virtual CATIntersectionCrossing GetCrossingOn(const short iCrossingIndex) = 0;

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
   virtual void GetStartingPointsIndex(CATLONG32 & oBegin, CATLONG32 & oEnd) = 0;

   // Surfaces
   //=========

   /**
   * Returns the number of solution surfaces.
   * @return
   * The number of solutions.
   */
   virtual CATLONG32 GetNumberOfSurfaces() const = 0;

   /**
   * Initializes the iterator of the solution surfaces.
   *<br>By default, the initialization is performed once the operator runs,
   * and this is therefore only used to read the solutions again.
   */
   virtual void BeginningSurface() = 0;

   /**
   * Moves the iterator to the next solution surface of <tt>this</tt> operator.
   *<br>After <tt>BeginningSurface</tt>, it returns to the first surface. 
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
   * @param oListOfPCurvesOrientation
   * The array of pointers to the relative orientation of each PCurve with respect to the loop.
   * If <tt>NULL</tt>, this is not output. This array is allocated by the method, you
   * have to <tt>delete</tt> it after use.
   * <br><b>Legal values</b>:
   * <dl><dt><tt>CATIntersectionOrientationOpposite</tt>
   * <dd>The orientation of the curve and the loop are opposite.
   *     <dt><tt>CATIntersectionOrientationSame</tt><dd>The loop and the curve have the same orientation.</dl> 
   * @param oContourOrientation
   * The relative orientation of the loop generated by the CATPCurves and surface. 
   * If <tt>NULL</tt>, this is not output.
   * <br><b>Legal values</b>:
   * <dl><dt><tt>CATIntersectionOrientationOpposite</tt>
   * <dd>The orientation of surface and the loop are opposite.
   *     <dt><tt>CATIntersectionOrientationSame</tt><dd> surface and the loop have the same orientation.</dl> 
   * @return 
   * The list of the curves defining the boundary on surface.
   */
   virtual CATLISTP(CATEdgeCurve) GetSurfaceBoundaries(CATIntersectionOrientation *& oListOfPCurvesOrientation,
                                                       CATIntersectionOrientation  & oContourOrientation1,
                                                       CATIntersectionOrientation  & oContourOrientation2,
                                                       CATLONG32                  *& oStartIndices,
                                                       CATLONG32                  *& oEndIndices) = 0;
};
#endif
