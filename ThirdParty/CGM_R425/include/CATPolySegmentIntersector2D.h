// COPYRIGHT DASSAULT SYSTEMES 2004, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySegmentIntersector2D.h
//
//===================================================================
// November 2004  NDO
//===================================================================
#ifndef CATPolySegmentIntersector2D_H
#define CATPolySegmentIntersector2D_H

#include "PolyMathIntersectors.h"
#include "CATPolyIntersection.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

class CATMathPoint2D;
class CATPolyExactArithmetic;
class CATPolyIntersectionPointConstructor2D;


/**
 * Intersector of two segments defined by pairs of points.
 * If the two segments intersect, the main method returns the symbolic type of the intersection.
 * If there is a point intersection between the two segments, it computes the intersection with the
 * CATPolyIntersectionPointConstructor2D passed as an argument to the constructor.
 * If the intersection between the two segments is a point then it constructs it.
 */
class ExportedByPolyMathIntersectors CATPolySegmentIntersector2D
{

public:

  /**
   * Constructor with the exact arithmetic.
   */
  CATPolySegmentIntersector2D (const CATPolyExactArithmetic& iExactArithmetic);

  /**
   * Constructor with the exact arithmetic and a custom instance of an intersection point constructor.
   * If using gridded exact arithmetic, the constructor of the intersection point should grid the constructed points.
   */
  CATPolySegmentIntersector2D (const CATPolyExactArithmetic& iExactArithmetic, 
                               const CATPolyIntersectionPointConstructor2D& iConstructor);

  ~CATPolySegmentIntersector2D ();

  /**
   * Returns the intersection-point constructor if any has been set.
   * (see constructor.)
   */
  inline const CATPolyIntersectionPointConstructor2D* GetIntersectionPointConstructor () const;

public:

  /**
   * Tests whether two segments, each defined by a pair of points, intersect or not.
   * The method returns an enum that describes the type of the intersection.
   * If there is an intersection between the two segments, a symbolic description of the intersection
   * can be obtained using the GetEntityType () method.
   * @param A
   *   The start point of Segment 0.
   * @param B
   *   The end point of Segment 0.
   * @param C
   *   The start point of Segment 1.
   * @param D
   *   The end point of Segment 1.
   * @return
   *   An integer describing the type of the intersection between the segments.
   *   See CATPolySegmentIntersector2D::IntersectionType.
   */
  int Intersect (const CATMathPoint2D& A, const CATMathPoint2D& B,
                 const CATMathPoint2D& C, const CATMathPoint2D& D);

  /**
   * Tests whether two segments, each defined by a pair of points, intersect or not.
   * The method returns an enum that describes the type of the intersection.
   * It also returns the symbolic type of the intersection and an error code.
   * @param A
   *   The start point of Segment 0.
   * @param B
   *   The end point of Segment 0.
   * @param C
   *   The start point of Segment 1.
   * @param D
   *   The end point of Segment 1.
   * @return
   *   An integer describing the type of the intersection between the segments.
   *   See CATPolySegmentIntersector2D::IntersectionType.
   */
  int Intersect (const CATMathPoint2D& A, const CATMathPoint2D& B,
                 const CATMathPoint2D& C, const CATMathPoint2D& D,
                 CATPolyIntersection::Type& oIntersectionType, CATPolyIntersection::Error& oError);

  /** 
   * Constructs a normalized intersection between Segments AB and CD, in the case of a point intersection.
   * This method should be called only after a call to the Intersect method, with the same points in the same order.
   * When the segments are not colinear, the intersection point is computed by the intersection point
   * constructor fed into the class or otherwise by a default method.
   */
  HRESULT ConstructIntersection (const CATMathPoint2D& A, const CATMathPoint2D& B,
                                 const CATMathPoint2D& C, const CATMathPoint2D& D,
                                 CATMathPoint2D& oIntersectionPoint);

  /**
   * Constructs the barycentric coordinates of the intersection w.r.t. both Segments AB and CD, in the case of a point intersection.
   * This method should be called only after a call to the Intersect method, with the same points in the same order.
   * The computation method relies on extendable significand floating-point arithmetic for increased precision and can be expansive.
   */
  HRESULT ConstructBarycentricCoordinates (const CATMathPoint2D& A, const CATMathPoint2D& B,
                                           const CATMathPoint2D& C, const CATMathPoint2D& D,
                                           double uvAB[2], double uvCD[2]);

  /**
   * Finds the closest extremity from one segment to the next.
   * This method should be use only after calling the Intersect method.
   * The output argument is set to 1 for A, 2 for B, 3 for C or 4 for D.
   */
  HRESULT GetClosestExtremity (const CATMathPoint2D& A, const CATMathPoint2D& B,
                               const CATMathPoint2D& C, const CATMathPoint2D& D,
                               int& oExtremity);

  /**
   * Returns the type of the intersection point on a segment in the case of a point intersection.
   * If this method is called when the intersection between the two segments is not a point
   * (no intersection or intersection is a line segment), then the method returns CATPoly::eUndefined.
   * @param iSegment
   *   0 or 1, respectively for the first or second segment.
   * @return 
   *   CATPoly::eVertex if the intersection point is an end-point of the segment.
   *   CATPoly::eBar if the intersection point is any other point of the segment.
   *   CATPoly::eUndefined if the intersection between the two segments is not a point intersection.
   */
  inline int GetEntityType (const int iSegment) const;

  /**
   * Returns TRUE if the segments are colinear and FALSE otherwise after running the Intersect () method.
   * @return
   *   TRUE if the segments are colinear and FALSE otherwise.
   */
  inline CATBoolean AreSegmentsColinear () const;

private:

  // Check whether two colinear segments intersect or not.
  // The four points, A, B, C and D are distinct and the segments are not degenerate.
  int IntersectColinearSegments (const CATMathPoint2D& A, const CATMathPoint2D& B,
                                 const CATMathPoint2D& C, const CATMathPoint2D& D) const;

  // Determine how the segments [A,B] and [B,C] intersect.
  // The segments are not degenerate.
  int IntersectJoinSegments (const CATMathPoint2D& A, 
                             const CATMathPoint2D& B, const CATMathPoint2D& C);

  const CATPolyExactArithmetic& _ExactArithmetic;
  const CATPolyIntersectionPointConstructor2D* _Constructor;

  CATBoolean _Colinear;

  int _IntersectionType; // Type of the intersection between the two segments.
  int _EntityType[2];    // Type of the intersection point, respectively on Segments 0 and 1.
  int _VertexIndex[2];   // The index of the vertex (0 or 1) when the intersection is an end point
                         // for the two segments.

public:

  /**
   * @nodoc
   * @deprecated
   */
  CATPolySegmentIntersector2D (const CATPolyExactArithmetic* iExactArithmetic);

  /**
   * @nodoc
   * @deprecated
   */
  enum IntersectionType
  {
    eDegenerateSegment   = CATPolyIntersection::eDegenerateSegment,
    eColinearSegments    = CATPolyIntersection::eColinearOperands,
    eFatalError          = CATPolyIntersection::eFatalError,
    eUndetermined        = CATPolyIntersection::eUndetermined,
    eNoIntersection      = CATPolyIntersection::eNoIntersection,
    ePointIntersection   = CATPolyIntersection::ePointIntersection,
    eSegmentIntersection = CATPolyIntersection::eSegmentIntersection
  };

};

inline const CATPolyIntersectionPointConstructor2D* CATPolySegmentIntersector2D::GetIntersectionPointConstructor () const
{
  return _Constructor;
}

inline int CATPolySegmentIntersector2D::GetEntityType (const int iSegment) const
{
  return _EntityType[iSegment];
}

inline CATBoolean CATPolySegmentIntersector2D::AreSegmentsColinear () const
{
  return _Colinear;
}

#endif

