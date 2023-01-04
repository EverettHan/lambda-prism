// COPYRIGHT DASSAULT SYSTEMES 2003, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathGeoDistanceUtil.h
//
//===================================================================
//
// Usage notes: many distance methods between canonical polyhedral objects
//
//===================================================================
//
// 2009/09/28 XXC: New with distance min functions
// 2009/10    XXC: Add distance max functions
// 2009/11    XXC: Add directional distance min functions
// 2013/08    JXO: epsilons
//===================================================================

#ifndef CATPOLYMATHGEODISTANCEUTIL__H
#define CATPOLYMATHGEODISTANCEUTIL__H

class CATMathBox;
#include "PolyMathUtils.h"
#include "CATBoolean.h"
#include "CATMathConstant.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"

/** Distance measures between elementary linear objects.
 * Linear objects considered are:
 *   - lines,
 *   - halflines (or rays),
 *   - segments,
 *   - triangles,
 *   - planes.
 * Distance measures are:
 *   - minimum distance
 *   - maximum distance
 *   - minimum distance along a direction
 *   - maximum distance from 1 to 2 (maximum distance along normal
 *     directions to the first operand)
 *   - angles
 * Notes:
 * - lines, halflines and segments are given by two points. Halflines
 *   are considered to be extended by the second point/extremity.
 * - Planes are given by a normal vector and an offset. The normal
 *   vector does not have to be normalized and the offset is
 *   proportionally scaled by this norm. E.g. if N:(xn,yn,zn) is the
 *   normal vector and O the offset, a*xn + b*yn + c*zn - O = 0 is the
 *   plane equation and the set of points P:(a,b,c) that verify this
 *   equation defines the plane. In the same way, if P is a point onto
 *   the plane, we have the following (scalar product) equality P*N = O.
 * - Infinite linear elements (lines, halflines, planes) are only
 *   considered when it has a sens: minimum distance and minimum
 *   distance along a direction.
 * - By default, in the "maximal distance 1 to 2" functions, if a
 *   segment or a triangle is degenerate and seen as a point, the
 *   distance measure is not defined (return FALSE).
 * - For angle measures, finite element are always considered as
 *   infinite ones.
 */

class ExportedByPolyMathUtils CATPolyMathGeoDistanceUtil
{
public:

  // ____________________________________________________________________
  //|                         MINIMUM DISTANCE                           |
  // ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
  static void SqDistanceMin_PointLine (const CATMathPoint & iP, const CATMathPoint & iA1, const CATMathPoint & iA2,
                                       double & oDistance, CATMathPoint & oPA, const double eps2);
  static void SqDistanceMin_PointHalfLine (const CATMathPoint & iP, const CATMathPoint & iA1, const CATMathPoint & iA2,
                                           double & oDistance, CATMathPoint & oPA, const double eps2);
  static void SqDistanceMin_PointSegment (const CATMathPoint & iP, const CATMathPoint & iA1, const CATMathPoint & iA2,
                                          double & oDistance, CATMathPoint & oPA, const double eps2);
  /** Distance between a point and a triangle defined by its
   * vertices. Returns the distance and the point on the triangle that
   * minimize the distance.
   * Algorithm from http://geometrictools.com.
   * The triangle plane is split in 6 regions as below.
   *
   *            /t direction
   *      \ r2 /
   *       \  /
   *        \/
   *  r3    /\   r1
   *       /  \
   *      / r0 \
   *     /      \
   *----*--------\------- s direction
   * r4/ B0       \ r6
   *  /     r5     \
   */
  static void SqDistanceMin_PointTriangle (const CATMathPoint & iA, const CATMathPoint iB[3],
                                           double & oDistance, CATMathPoint & oB);
  static void SqDistanceMin_PointPlane (const CATMathPoint & iP, const CATMathVector & iNormal, const double iOffset,
                                        double & oDistance, CATMathPoint & oProj);
  static void SqDistanceMin_LineLine (const CATMathPoint & iA1, const CATMathPoint & iA2,
                                      const CATMathPoint & iB1, const CATMathPoint & iB2,
                                      double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps2);
  static void SqDistanceMin_LineLine (const CATMathPoint & iA1, const CATMathVector & dA,
                                      const CATMathPoint & iB1, const CATMathVector & dB,
                                      double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps2);
  static void SqDistanceMin_LineHalfLine (const CATMathPoint & iA1, const CATMathPoint & iA2,
                                          const CATMathPoint & iB1, const CATMathPoint & iB2,
                                          double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps2);
  static void SqDistanceMin_LineSegment (const CATMathPoint & iA1, const CATMathPoint & iA2,
                                         const CATMathPoint & iB1, const CATMathPoint & iB2,
                                         double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps2);
  static void SqDistanceMin_LineTriangle (const CATMathPoint & iA1, const CATMathPoint & iA2, const CATMathPoint iB[3],
                                          double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps2, const double eps3);
  static void SqDistanceMin_LinePlane (const CATMathPoint & iA1, const CATMathPoint & iA2,
                                       const CATMathVector & iNormalB, const double iOffsetB,
                                       double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps);
  static void SqDistanceMin_HalfLineHalfLine (const CATMathPoint & iA1, const CATMathPoint & iA2,
                                              const CATMathPoint & iB1, const CATMathPoint & iB2,
                                              double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps2);
  static void SqDistanceMin_HalfLineSegment (const CATMathPoint & iA1, const CATMathPoint & iA2,
                                             const CATMathPoint & iB1, const CATMathPoint & iB2,
                                             double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps2);
  static void SqDistanceMin_HalfLineTriangle (const CATMathPoint & iA1, const CATMathPoint & iA2, const CATMathPoint iB[3],
                                              double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps, const double eps2);
  static void SqDistanceMin_HalfLinePlane (const CATMathPoint & iA1, const CATMathPoint & iA2,
                                           const CATMathVector & iNormalB, const double iOffsetB,
                                           double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps);
  static void SqDistanceMin_SegmentSegment (const CATMathPoint & iA1, const CATMathPoint & iA2,
                                            const CATMathPoint & iB1, const CATMathPoint & iB2,
                                            double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps2);
  static void SqDistanceMin_SegmentTriangle (const CATMathPoint & iA1, const CATMathPoint & iA2, const CATMathPoint iB[3],
                                             double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps2, const double eps3);
  static void SqDistanceMin_SegmentPlane (const CATMathPoint & iA1, const CATMathPoint & iA2,
                                          const CATMathVector & iNormalB, const double iOffsetB,
                                          double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps);
  /** Computes the distance between two triangles A and B (the minimal
   *  distance between two points on the triangles), defined by their
   *  three vertices, and the points on each triangle that realize this
   *  distance.
   *@param iA: array of the three A triangle vertices.
   *@param iB: array of the three B triangle vertices.
   *@param oDistance: the distance between the two edges.
   *@param oA: the point on the triangle A realizing the minimal
   *distance with a point of B.
   *@param oB: the point on the triangle B realizing the minimal
   *distance with a point of A.
   */
  static void SqDistanceMin_TriangleTriangle (const CATMathPoint iA[3], const CATMathPoint iB[3],
                                              double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps2, const double eps3);
  static void SqDistanceMin_TrianglePlane (const CATMathPoint iA[3], const CATMathVector & iNormalB, const double iOffset,
                                           double & oDistance, CATMathPoint & oA, CATMathPoint & oB);
  static void SqDistanceMin_PlanePlane (const CATMathVector & iNormalA, const double & iOffsetA,
                                        const CATMathVector & iNormalB, const double & iOffsetB,
                                        double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps);


  /** This is a structure meant to precompute and store all information
   *  relative to a triangle which will be necessary to compute the
   *  distance from this triangle to a point.
   *  This is purely meant to make this computation faster in scenarios
   *  where we have to compute the distance from this triangle to many points.
   */
  struct ExportedByPolyMathUtils SqDistance_TriangleData
  {
    SqDistance_TriangleData ();
    SqDistance_TriangleData (const CATMathPoint iPoints[3]);

    void Set (const CATMathPoint iPoints[3]);

    CATMathVector GetNormal ();

    CATMathPoint _Origin;
    CATMathVector _FstEdge;
    CATMathVector _SndEdge;
    double _FstEdgeSqLength;
    double _SndEdgeSqLength;
    double _DoubleArea;
    double _Det;
  };

  /** This method uses the exact same algorithm as its overload above.
   *  It simply uses an intermediary class to precompute data relative
   *  to the triangle such that it can be reused.
   */
  static void SqDistanceMin_PointTriangle (const CATMathPoint & iA, const SqDistance_TriangleData& iTriangle,
                                           double & oDistance, CATMathPoint & oB);
  /** This version takes an additional char parameter to indicate where is the locus, on the triangle [A,B,C], where the distance is minimal.
   *  This locus is defined by:
   *  0: inside the triangle.
   *  1: vertex A
   *  2: vertex B
   *  4: vertex C
   *  3: edge [AB]
   *  5: edge [AC]
   *  6: edge [BC]
   */
  static void SqDistanceMin_PointTriangle (const CATMathPoint & iA, const SqDistance_TriangleData& iTriangle,
                                           double & oDistance, CATMathPoint & oB, char & oLocus);

  // ____________________________________________________________________
  //|                         MAXIMUM DISTANCE                           |
  // ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
  static double SqDistanceMax_PointBox (const CATMathPoint & iA, const CATMathBox & iB);
  static double SqDistanceMax_BoxBox (const CATMathBox & iA, const CATMathBox & iB);

  static void SqDistanceMax_PointSegment (const CATMathPoint & iA, const CATMathPoint & iB1, const CATMathPoint & iB2,
                                          double & oDistance, CATMathPoint & oB);
  static void SqDistanceMax_PointTriangle (const CATMathPoint & iA, const CATMathPoint iB[3],
                                           double & oDistance, CATMathPoint & oB);
  static void SqDistanceMax_SegmentSegment (const CATMathPoint & iA1, const CATMathPoint & iA2,
                                            const CATMathPoint & iB1, const CATMathPoint & iB2,
                                            double & oDistance, CATMathPoint & oA, CATMathPoint & oB);
  static void SqDistanceMax_SegmentTriangle (const CATMathPoint & iA1, const CATMathPoint & iA2, const CATMathPoint iB[3],
                                             double & oDistance, CATMathPoint & oA, CATMathPoint & oB);
  static void SqDistanceMax_TriangleTriangle (const CATMathPoint iA[3], const CATMathPoint iB[3],
                                              double & oDistance, CATMathPoint & oA, CATMathPoint & oB);

  // ____________________________________________________________________
  //|                MINIMUM DISTANCE ALONG A DIRECTION                  |
  // ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯

  static CATBoolean SqDistanceMinDir_PointBox (const CATMathVector & iDirection,
                                               const CATMathPoint & iA, const CATMathBox & iB,
                                               double & oDistance, const double eps1);
  static CATBoolean SqDistanceMinDir_BoxBox (const CATMathVector & iDirection,
                                             const CATMathBox & iA, const CATMathBox & iB,
                                             double & oDistance, const double eps1);

  static CATBoolean SqDistanceMinDir_PointLine (const CATMathVector & iDirection,
                                                const CATMathPoint & iP, const CATMathPoint & iA1, const CATMathPoint & iA2,
                                                double & oDistance, CATMathPoint & oPA, const double eps2);
  static CATBoolean SqDistanceMinDir_PointHalfLine (const CATMathVector & iDirection,
                                                    const CATMathPoint & iP, const CATMathPoint & iA1, const CATMathPoint & iA2,
                                                    double & oDistance, CATMathPoint & oPA, const double eps2);
  static CATBoolean SqDistanceMinDir_PointSegment (const CATMathVector & iDirection,
                                                   const CATMathPoint & iP, const CATMathPoint & iA1, const CATMathPoint & iA2,
                                                   double & oDistance, CATMathPoint & oPA, const double eps2);
  static CATBoolean SqDistanceMinDir_PointTriangle (const CATMathVector & iDirection,
                                                    const CATMathPoint & iA, const CATMathPoint iB[3],
                                                    double & oDistance, CATMathPoint & oB, const double eps2, const double eps3);
  static CATBoolean SqDistanceMinDir_PointPlane (const CATMathVector & iDirection,
                                                 const CATMathPoint & iP, const CATMathVector & iNormal, const double iOffset,
                                                 double & oDistance, CATMathPoint & oProj, const double eps, const double eps1);
  static CATBoolean SqDistanceMinDir_LineLine (const CATMathVector & iDirection,
                                               const CATMathPoint & iA1, const CATMathPoint & iA2,
                                               const CATMathPoint & iB1, const CATMathPoint & iB2,
                                               double & oDistance, CATMathPoint & oA, CATMathPoint & oB,
                                               const double eps, const double eps2, const double eps3);
  static CATBoolean SqDistanceMinDir_LineHalfLine (const CATMathVector & iDirection,
                                                   const CATMathPoint & iA1, const CATMathPoint & iA2,
                                                   const CATMathPoint & iB1, const CATMathPoint & iB2,
                                                   double & oDistance, CATMathPoint & oA, CATMathPoint & oB,
                                                   const double eps, const double eps2, const double eps3);
  static CATBoolean SqDistanceMinDir_LineSegment (const CATMathVector & iDirection,
                                                  const CATMathPoint & iA1, const CATMathPoint & iA2,
                                                  const CATMathPoint & iB1, const CATMathPoint & iB2,
                                                  double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps, const double eps2, const double eps3);
  static CATBoolean SqDistanceMinDir_LineTriangle (const CATMathVector & iDirection,
                                                   const CATMathPoint & iA1, const CATMathPoint & iA2, const CATMathPoint iB[3],
                                                   double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps, const double eps2, const double eps3);
  static CATBoolean SqDistanceMinDir_LinePlane (const CATMathVector & iDirection,
                                                const CATMathPoint & iA1, const CATMathPoint & iA2,
                                                const CATMathVector & iNormalB, const double iOffsetB,
                                                double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps, const double eps1);
  static CATBoolean SqDistanceMinDir_HalfLineHalfLine (const CATMathVector & iDirection,
                                                       const CATMathPoint & iA1, const CATMathPoint & iA2,
                                                       const CATMathPoint & iB1, const CATMathPoint & iB2,
                                                       double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps, const double eps2, const double eps3);
  static CATBoolean SqDistanceMinDir_HalfLineSegment (const CATMathVector & iDirection,
                                                      const CATMathPoint & iA1, const CATMathPoint & iA2,
                                                      const CATMathPoint & iB1, const CATMathPoint & iB2,
                                                      double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps, const double eps2, const double eps3);
  static CATBoolean SqDistanceMinDir_HalfLineTriangle (const CATMathVector & iDirection,
                                                       const CATMathPoint & iA1, const CATMathPoint & iA2, const CATMathPoint iB[3],
                                                       double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps, const double eps2, const double eps3);
  static CATBoolean SqDistanceMinDir_HalfLinePlane (const CATMathVector & iDirection,
                                                    const CATMathPoint & iA1, const CATMathPoint & iA2,
                                                    const CATMathVector & iNormalB, const double iOffsetB,
                                                    double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps, const double eps1);
  static CATBoolean SqDistanceMinDir_SegmentSegment (const CATMathVector & iDirection,
                                                     const CATMathPoint & iA1, const CATMathPoint & iA2,
                                                     const CATMathPoint & iB1, const CATMathPoint & iB2,
                                                     double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps, const double eps2, const double eps3);
  static CATBoolean SqDistanceMinDir_SegmentTriangle (const CATMathVector & iDirection,
                                                      const CATMathPoint & iA1, const CATMathPoint & iA2, const CATMathPoint iB[3],
                                                      double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps, const double eps2, const double eps3);
  static CATBoolean SqDistanceMinDir_SegmentPlane (const CATMathVector & iDirection,
                                                   const CATMathPoint & iA1, const CATMathPoint & iA2,
                                                   const CATMathVector & iNormalB, const double iOffsetB,
                                                   double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps, const double eps1);
  static CATBoolean SqDistanceMinDir_TriangleTriangle (const CATMathVector & iDirection,
                                                       const CATMathPoint iA[3], const CATMathPoint iB[3],
                                                       double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps, const double eps2, const double eps3);
  static CATBoolean SqDistanceMinDir_TrianglePlane (const CATMathVector & iDirection,
                                                    const CATMathPoint iA[3], const CATMathVector & iNormalB, const double iOffset,
                                                    double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps, const double eps1, const double eps2);
  static CATBoolean SqDistanceMinDir_PlanePlane (const CATMathVector & iDirection,
                                                 const CATMathVector & iNormalA, const double & iOffsetA,
                                                 const CATMathVector & iNormalB, const double & iOffsetB,
                                                 double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps);

  // ____________________________________________________________________
  //|                   MAXIMUM DISTANCE FROM 1 TO 2                     |
  // ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯

  // WARNING: By default, in the following functions, if a segment or a
  // triangle is degenerate and seen as a point, the distance measure is
  // not defined (return FALSE).

  static CATBoolean SqDistanceMax1To2_PointSegment (const CATMathPoint & iA,
                                                    const CATMathPoint & iB1, const CATMathPoint & iB2,
                                                    double & oDistance, CATMathPoint & oB);
  static CATBoolean SqDistanceMax1To2_PointTriangle (const CATMathPoint & iA, const CATMathPoint iB[3],
                                                     double & oDistance, CATMathPoint & oB);
  static CATBoolean SqDistanceMax1To2_SegmentPoint (const CATMathPoint & iA1, const CATMathPoint & iA2,
                                                    const CATMathPoint & iB,
                                                    double & oDistance, CATMathPoint & oA, const double eps2);
  static CATBoolean SqDistanceMax1To2_SegmentSegment (const CATMathPoint & iA1, const CATMathPoint & iA2,
                                                      const CATMathPoint & iB1, const CATMathPoint & iB2,
                                                      double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps2);
  static CATBoolean SqDistanceMax1To2_SegmentTriangle (const CATMathPoint & iA1, const CATMathPoint & iA2,
                                                       const CATMathPoint iB[3],
                                                       double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps2);
  static CATBoolean SqDistanceMax1To2_HalfLinePoint (const CATMathPoint & iA1, const CATMathPoint & iA2,
                                                     const CATMathPoint & iB,
                                                     double & oDistance, CATMathPoint & oA, const double eps2);
  static CATBoolean SqDistanceMax1To2_HalfLineSegment (const CATMathPoint & iA1, const CATMathPoint & iA2,
                                                       const CATMathPoint & iB1, const CATMathPoint & iB2,
                                                       double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps2);
  static CATBoolean SqDistanceMax1To2_HalfLineTriangle (const CATMathPoint & iA1, const CATMathPoint & iA2,
                                                        const CATMathPoint iB[3],
                                                        double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps2);
  static void SqDistanceMax1To2_LineSegment (const CATMathPoint & iA1, const CATMathPoint & iA2,
                                             const CATMathPoint & iB1, const CATMathPoint & iB2,
                                             double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps2);
  static void SqDistanceMax1To2_LineTriangle (const CATMathPoint & iA1, const CATMathPoint & iA2,
                                              const CATMathPoint iB[3],
                                              double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps2);
  static CATBoolean SqDistanceMax1To2_TrianglePoint (const CATMathPoint iA[3], const CATMathPoint & iB,
                                                     double & oDistance, CATMathPoint & oA);
  static CATBoolean SqDistanceMax1To2_TriangleSegment (const CATMathPoint iA[3],
                                                       const CATMathPoint & iB1, const CATMathPoint & iB2,
                                                       double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps, const double eps2, const double eps3);
  static CATBoolean SqDistanceMax1To2_TriangleTriangle (const CATMathPoint iA[3], const CATMathPoint iB[3],
                                                        double & oDistance, CATMathPoint & oA, CATMathPoint & oB, const double eps, const double eps2, const double eps3);
  static void SqDistanceMax1To2_PlaneSegment (const CATMathVector & iNormalA, const double & iOffsetA,
                                              const CATMathPoint & iB1, const CATMathPoint & iB2,
                                              double & oDistance, CATMathPoint & oA, CATMathPoint & oB);
  static void SqDistanceMax1To2_PlaneTriangle (const CATMathVector & iNormalA, const double & iOffsetA,
                                               const CATMathPoint iB[3],
                                               double & oDistance, CATMathPoint & oA, CATMathPoint & oB);

  // ____________________________________________________________________
  //|                              ANGLES                                |
  // ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
  static CATAngle Angle_LineLine (const CATMathPoint & P1, const CATMathVector & Dir1,
                                  const CATMathPoint & P2, const CATMathVector & Dir2,
                                  const double eps, const double eps1);
  static CATAngle Angle_LinePlane (const CATMathPoint & P1, const CATMathVector & Dir1,
                                   const CATMathPoint & P2, const CATMathVector & N2,
                                   const double eps, const double eps1);
  static CATAngle Angle_PlanePlane (const CATMathPoint & P1, const CATMathVector & N1,
                                    const CATMathPoint & P2, const CATMathVector & N2,
                                    const double eps, const double eps1);

};

#endif
