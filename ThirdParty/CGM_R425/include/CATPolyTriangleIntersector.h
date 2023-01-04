// COPYRIGHT DASSAULT SYSTEMES 2004, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyTriangleIntersector.h
//
//===================================================================
// Apr 2004  Creation: rxu/ndo
//===================================================================
#ifndef CATPolyTriangleIntersector_H
#define CATPolyTriangleIntersector_H

#include "PolyMathIntersectors.h"
#include "CATPolyIntersectionPoint.h"
#include "CATPolyIntersection.h"
#include "CATPolyTriangleIntersector2D.h"
#include "CATBoolean.h"

class CATMathPoint;
class CATPolyExactArithmetic;


/**
 * Operator that finds if two triangles intersect.
 * If the triangles intersect, it computes a symbolic description of the intersection
 * (point, segment or polygon.)
 */
class ExportedByPolyMathIntersectors CATPolyTriangleIntersector
{

public:

  /**
   * Enumerator defining the type of the intersection.
   * @see CATPolyIntersection
   */
  enum IntersectionType
  {
    /** Degenerate triangle (no further test). */  eDegenerateTriangle  = CATPolyIntersection::eDegenerateTriangle,
    /** Coplanar triangles; (no further test). */  eCoplanarTriangles   = CATPolyIntersection::eCoplanarOperands,
    /** Fatal error.*/                             eFatalError          = CATPolyIntersection::eFatalError,
    /** Undetermined. */                           eUndetermined        = CATPolyIntersection::eUndetermined,
    /** No intersection between the triangles. */  eNoIntersection      = CATPolyIntersection::eNoIntersection,
    /** Intersection is a point. */                ePointIntersection   = CATPolyIntersection::ePointIntersection,
    /** Intersection is a line segment. */         eSegmentIntersection = CATPolyIntersection::eSegmentIntersection,
    /** Intersection is a polygon. */              ePolygonIntersection = CATPolyIntersection::ePolygonIntersection
  };

public:

  CATPolyTriangleIntersector (const CATPolyExactArithmetic& iExactArithmetic);
  ~CATPolyTriangleIntersector ();

public:

/** @name Settings and Services
    @{ */

  /** 
  * Sets an option to ignore coplanar triangles.  With this option turned on, the method
  * Intersect () will not compute the intersection of coplanar triangles.  
  */
  void IgnoreCoplanarTriangles ();

  /**
  * Sets an option to compute an estimation of the barycentric coordinates of intersection points;
  */
  void ComputeBarycentricCoordinates();

  /**
   * Check if the coplanar are ignored or not
   */
  bool DoesIgnoreCoplanarTriangles() { return (_PlanarIntersector)? false : true; };

  /**
  * Check if barycentric coordinates are estimated or not.
  */
  bool DoesComputeBarycentricCoordinates() { return _ComputeBarycentricCoordinates; }

  /**
  * Returns the position of a point D with respect to a plane defined by three (non-colinear) points: A, B and C.
  *   @param A
  *      A first point of the plane.
  *   @param B
  *      A second point of the plane.
  *   @param C
  *      A third point of the plane.
  *   @param D
  *      The point being tested.
  *   @return
  *      +1: if the point is above.
  *       0: if the point is on the plane.
  *      -1: if the point is below.
  */
  int GetPosition (const CATMathPoint& A, const CATMathPoint& B, const CATMathPoint& C, const CATMathPoint& D) const;

/** @} */

public:

/** @name Intersect Methods
    @{ */

  /**
  * Tests whether two triangles defined by three points intersect or not.  The method returns an enum
  * that describes the type of the intersection (see CATPolyTriangleIntersector::IntersectionType.)
  * If there is an intersection between the two triangles, a symbolic description of the intersection
  * can be obtained with the GetIntersectionPoint () method.
  *   @param A
  *      The first point of Triangle 1.
  *   @param B
  *      The second point of Triangle 1.
  *   @param C
  *      The third point of Triangle 1.
  *   @param D
  *      The first point of Triangle 2.
  *   @param E
  *      The second point of Triangle 2.
  *   @param F
  *      The third point of Triangle 2.
  *   @return
  *      An integer describing the type of the intersection between the triangles.
  *      See CATPolyTriangleIntersector::IntersectionType.
  */
  int Intersect (const CATMathPoint& A, const CATMathPoint& B, const CATMathPoint& C,
                 const CATMathPoint& D, const CATMathPoint& E, const CATMathPoint& F);

  /**
  * Tests whether two triangles defined by three points intersect or not.  The method returns an enum
  * that describes the type of the intersection (see CATPolyTriangleIntersector::IntersectionType.)
  * If there is an intersection between the two triangles, a symbolic description of the intersection
  * can be obtained with the GetIntersectionPoint () method.
  *   @param P
  *      The three points defining the first triangle.
  *   @param Q
  *      The three points defining the second triangle.
  *   @return
  *      An integer describing the type of the intersection between the triangles.
  *      See CATPolyTriangleIntersector::IntersectionType.
  */
  int Intersect (const CATMathPoint P[3], const CATMathPoint Q[3]);

  /**
   * Tests whether two triangles (O, B, C) and (O, E, F) have a segment or polygon intersection.
   */
  int Intersect (const CATMathPoint& O, 
                 const CATMathPoint& B, const CATMathPoint& C,
                 const CATMathPoint& E, const CATMathPoint& F);

  /**
  * Tests whether two triangles (O, P, A) and (O, P, B) have a polygon intersection.
  */
  int Intersect(const CATMathPoint& O, const CATMathPoint& P,
                const CATMathPoint& A, const CATMathPoint& B);

/** @} */

public:

/** @name Results
    @{ */

  /**
  * Returns a description of the intersection between the two triangles after a call to the Intersect ()
  * method. The intersection is either a point, a line segment or a polygon which are defined respectively 
  * by one, two or more intersection points. If another call to Intersect () is made after calling this method,
  * the data become invalid.
  *
  * *** Orientation of a line segment intersection for non-planar triangles ***
  * The most common intersection between two triangles is a line segment.  When the triangles are non-planar,
  * the line segment is oriented in the direction of the vector product of their normals.
  * More specifically, let n1 be the normal of Triangle 1 and n2 the normal of Triangle 2.  Then
  * the line segment intersection is defined by two points, I and J, and its direction IJ is the same 
  * as n1 ^ n2.  The points I and J are respectively the first and the second point returned.
  *
  *   @param oNbPoints
  *      An output integer giving the number of points defining the intersection.
  *   @return
  *      A pointer to the intersection points defining the intersection.
  */
  inline const CATPolyIntersectionPoint* GetIntersectionPoints (int& oNbPoints) const;

  /**
  * Returns <tt>TRUE</tt> if the triangles are coplanar and <tt>FALSE</tt> otherwise.
  *   @return
  *     <tt>TRUE</tt> if the triangles are coplanar and <tt>FALSE</tt> otherwise.
  */
  inline CATBoolean AreTrianglesCoplanar () const;

  /** 
   * Returns <tt>TRUE</tt> if the orientation of the two coplanar triangles are the same.
   * This method applies only to coplanar triangles.
   */
  inline CATBoolean HaveSameOrientation () const;

  /**
   * @see HaveSameOrientation
   */
  inline CATBoolean IsOrientationOfTrianglesTheSame () const;

  /**
   * Returns <tt>TRUE</tt> the orientation computed with the three vertices of triangle (1 - t) and vertex v of triangle t
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *    
   * BE CAREFUL
   * If triangle are coplanar or if there is no intersection data may not be initialized for the second triangle.
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *    
   */
  int GetOrientation(int t, int v) const;

/** @} */

private:

  const CATPolyExactArithmetic& _ExactArithmetic;
  CATPolyTriangleIntersector2D* _PlanarIntersector;
  bool _ComputeBarycentricCoordinates;

  // Symbolic description of the intersection points.
  // An intersection point is defined symbolically by the intersection of two triangle entities
  // (a vertex, a bar or a triangle) from Triangle 1 and Triangle 2.
  // For instance, a vertex from Triangle 1 on a bar from Triangle 2; or an intersection point 
  // could be defined as the intersection between Triangle 1 and a bar of Triangle 2.  
  // When the intersection is on a bar, it excludes the vertices from this bar; otherwise, it would
  // be on a vertex.  When the intersection is on a triangle, it excludes the bars and vertices from
  // this triangle; otherwise, it would be on a bar or a vertex.
  // An index identifies the vertex or the bar of the triangle.
  // Given a triangle (A, B, C), the indices of the vertices A, B, C are 0, 1 and 2 respectively and
  // the indices of the bars AB, BC, CA are 0, 1 and 2 respectively.

  int _NbPoints;
  CATPolyIntersectionPoint _Point[2];

  int _PntOri[2][3]; // _PntOri[t][v] is the orientation computed with the three vertices of triangle (1 - t) and vertex v of triangle t;
  int _Ori[6]; // Orientation cache used to sort points along the line formed by the intersection of the triangles supporting planes.
  int _Idx[2][3]; // Permutation of vertices on both triangles.
  const CATMathPoint* _Pts[2][3]; // Cache of points.

private:

  int IntersectCoplanarTriangles (const CATMathPoint& A, const CATMathPoint& B, const CATMathPoint& C, const CATMathPoint& D, const CATMathPoint& E, const CATMathPoint& F) const;

  int GetTriangleDirection (const CATMathPoint& A, const CATMathPoint& B, const CATMathPoint& C) const;

  int ComputeIntersections ();

  void ComputeBarycentricCoordinates(CATPolyIntersectionPoint* iPoints, const int iNbPoints);

  void SetPointBuffer (const CATMathPoint& A, const CATMathPoint& B, const CATMathPoint& C, const CATMathPoint& D, const CATMathPoint& E, const CATMathPoint& F);

  void TestOppositeVertices (const int iTriangle);
  void UpdatePointDefinition (const int iTriangle);
  void PermutePointDefinition (const int iTriangle);
  void TransposeIntersectionPoints ();

public:

  CATPolyTriangleIntersector (const CATPolyExactArithmetic* iExactArithmetic);

};

inline const CATPolyIntersectionPoint* CATPolyTriangleIntersector::GetIntersectionPoints (int& oNbPoints) const
{
  if (_NbPoints > 0)
  {
    oNbPoints = _NbPoints;
    return _Point;
  }
  else if (_NbPoints == -1 && _PlanarIntersector)
    return _PlanarIntersector->GetIntersectionPoints (oNbPoints);
  else
  {
    oNbPoints = 0;
    return 0;
  }
}

inline CATBoolean CATPolyTriangleIntersector::AreTrianglesCoplanar () const
{
  return _NbPoints == -1 ? TRUE : FALSE;
}

inline CATBoolean CATPolyTriangleIntersector::HaveSameOrientation () const
{
  return _PlanarIntersector ? _PlanarIntersector->HaveSameOrientation () : FALSE;
}

inline CATBoolean CATPolyTriangleIntersector::IsOrientationOfTrianglesTheSame () const
{
  return HaveSameOrientation ();
}

inline int CATPolyTriangleIntersector::GetOrientation(int t, int v) const
{
  return _PntOri[t][v];
}

#endif
