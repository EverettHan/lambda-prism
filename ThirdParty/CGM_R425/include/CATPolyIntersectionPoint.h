// COPYRIGHT DASSAULT SYSTEMES 2004, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyIntersectionPoint.h
// Header definition of CATPolyIntersectionPoint
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// June 2004 Creation: ndo
//===================================================================
#ifndef CATPolyIntersectionPoint_H
#define CATPolyIntersectionPoint_H

#include "PolyMathIntersectors.h"
#include "CATPoly.h"

class CATCGMOutput;


/**
 * Symbolic description of an intersection point between two entities (vertex, bar or triangle).
 *
 * The symbolic definition of an intersection point is for instance: 
 * <ul>
 *   <li> a vertex from Triangle 0 on a bar from Triangle 1; 
 *   <li> Triangle 0 intersecting with a bar from Triangle 1;
 *   <li> a bar from Triangle 0 intersecting with a bar from Triangle 1; or
 *   <li> Triangle 0 intersecting with a bar defined as its own entity (for example free bar.)
 * </ul>
 *
 * When the intersection is on a bar, it excludes the vertices from this bar; otherwise, it would
 * be on a vertex.  When the intersection is on a triangle, it excludes the bars and vertices from
 * this triangle; otherwise, it would be on a bar or a vertex.
 *
 * The index 0, 1 or 2 identifies the vertex or the bar of the triangle.
 * The index 0 or 1 identifies the vertex of the bar.
 * Given a triangle (A, B, C), the indices of the vertices A, B, C are 0, 1 and 2 respectively and
 * the indices of the bars AB, BC, CA are 0, 1 and 2 respectively.
 */
class ExportedByPolyMathIntersectors CATPolyIntersectionPoint
{

public :

  CATPolyIntersectionPoint ();
  CATPolyIntersectionPoint (const CATPolyIntersectionPoint& iIntersectionPoint);

  ~CATPolyIntersectionPoint () {}

public:

  /**
   * Sets the two entity (triangle) indices (arbitrary integers that are recorded for reference purposes).
   */
  inline void SetEntities (const int iEntity0, const int iEntity1);

  /** 
   * Gets one of the two entity index. 
   * @param iZeroOrOne
   *   <br>
   *     <li> 0 for the first entity (triangle).
   *     <li> 1 for the second entity (triangle).
   *   </br>
   * @return
   *   The entity (triangle) index.
   */
  inline int GetEntity (const int iZeroOrOne) const;

public:

  inline void SetUndefinedIntersection ();

  /**
   * Sets a vertex intersection for one of the two entities (triangles).
   * @param iZeroOrOne
   *   <br>
   *     <li> 0 for the first entity (triangle).
   *     <li> 1 for the second entity (triangle).
   *   </br>
   * @param iVertex
   *   Index of the vertex: 0, 1 or 2.
   */
  inline void SetVertexIntersection (const int iZeroOrOne, const int iVertex);

  /**
   * Sets a bar intersection for one of the two entities (triangles).
   * @param iZeroOrOne
   *   <br>
   *     <li> 0 for the first entity (triangle).
   *     <li> 1 for the second entity (triangle).
   *   </br>
   * @param iBar
   *   Index of the bar: 0, 1 or 2.
   */
  inline void SetBarIntersection (const int iZeroOrOne, const int iBar);

  /**
   * Sets a triangle intersection for one of the two entities (triangles).
   * @param iZeroOrOne
   *   <br>
   *     <li> 0 for the first entity (triangle).
   *     <li> 1 for the second entity (triangle).
   *   </br>
   */
  inline void SetTriangleIntersection (const int iZeroOrOne);

  /**
   * Sets a bar intersection for one of the two entities (triangles).
   * @param iZeroOrOne
   *   <br>
   *     <li> 0 for the first entity (triangle).
   *     <li> 1 for the second entity (triangle).
   *   </br>
   * @param iBar
   *   Index of the bar: 0, 1 or 2.
   */
  inline void SetBarycentricCoordinates(const int iZeroOrOne, const double iU, const double iV, const double iW);

  /**
   * Returns the intersecting entity type for one of the two entities (triangles).
   * @param iZeroOrOne
   *   <br>
   *     <li> 0 for the first entity (triangle).
   *     <li> 1 for the second entity (triangle).
   *   </br>
   * @return
   *   The entity type.
   *    @see CATPoly
   */
  inline int GetEntityType (const int iZeroOrOne) const;

  /**
   * Returns the intersecting vertex index for one of the two entities (triangles).
   * @param iZeroOrOne
   *   <br>
   *     <li> 0 for the first entity (triangle).
   *     <li> 1 for the second entity (triangle).
   *   </br>
   * @return
   *   The vertex index: 0, 1 or 2.
   */
  inline int GetVertexIndex (const int iZeroOrOne) const;

  /**
   * Returns the intersecting bar index for one of the two entities (triangles).
   * @param iZeroOrOne
   *   <br>
   *     <li> 0 for the first entity (triangle).
   *     <li> 1 for the second entity (triangle).
   *   </br>
   * @return
   *   The bar index: 0, 1 or 2.
   */
  inline int GetBarIndex (const int iZeroOrOne) const;

  /**
   * Returns the barycentric coordinates of the intersection point for one of the two entities (triangles).
   * @param iZeroOrOne
   *   <br>
   *     <li> 0 for the first entity (triangle).
   *     <li> 1 for the second entity (triangle).
   *   </br>
   * @return
   *   The bar index: 0, 1 or 2.
   */
  inline const double* GetBarycentricCoordinates(const int iZeroOrOne) const;

public:

  CATPolyIntersectionPoint& operator = (const CATPolyIntersectionPoint& iIntersectionPoint);

  int operator == (const CATPolyIntersectionPoint& iIntersectionPoint) const;

  int operator != (const CATPolyIntersectionPoint& iIntersectionPoint) const;

  // For debugging purposes...
  void Print (CATCGMOutput& stream) const;

protected :

  int _Entity[2];        // The indices of the two intersecting entities.
  int _EntityType[2];    // The types of the intersecting entities (vertex, bar or triangle) for the two triangles.
  int _EntityIndex[2];   // The indices of the entities in the two triangles (0, 1 or 2 for vertices or bars.)
  double _BarycentricCoords[2][3]; // The barycentric coordinates of the intersection point with regard to both triangles;

};


inline void CATPolyIntersectionPoint::SetEntities (const int iEntity0, const int iEntity1)
{
  _Entity[0] = iEntity0;
  _Entity[1] = iEntity1;
}

inline int CATPolyIntersectionPoint::GetEntity (const int iZeroOrOne) const
{
  return _Entity[iZeroOrOne];
}

inline void CATPolyIntersectionPoint::SetUndefinedIntersection ()
{
  _EntityType[0] = CATPoly::eUndefined;
  _EntityType[1] = CATPoly::eUndefined;
  _EntityIndex[0] = 0;
  _EntityIndex[1] = 0;
}

inline void CATPolyIntersectionPoint::SetVertexIntersection (const int iZeroOrOne, const int iVertex)
{
  _EntityType[iZeroOrOne] = CATPoly::eVertex;
  _EntityIndex[iZeroOrOne] = iVertex;
}

inline void CATPolyIntersectionPoint::SetBarIntersection (const int iZeroOrOne, const int iBar)
{
  _EntityType[iZeroOrOne] = CATPoly::eBar;
  _EntityIndex[iZeroOrOne] = iBar;
}

inline void CATPolyIntersectionPoint::SetTriangleIntersection (const int iZeroOrOne)
{
  _EntityType[iZeroOrOne] = CATPoly::eTriangle;
  _EntityIndex[iZeroOrOne] = 0;
}

inline void CATPolyIntersectionPoint::SetBarycentricCoordinates(const int iZeroOrOne, const double iU, const double iV, const double iW)
{
  _BarycentricCoords[iZeroOrOne][0] = iU;
  _BarycentricCoords[iZeroOrOne][1] = iV;
  _BarycentricCoords[iZeroOrOne][2] = iW;
}

inline int CATPolyIntersectionPoint::GetEntityType (const int iZeroOrOne) const
{
  return _EntityType[iZeroOrOne];
}

inline int CATPolyIntersectionPoint::GetVertexIndex (const int iZeroOrOne) const
{
  return (_EntityType[iZeroOrOne] == CATPoly::eVertex) ? _EntityIndex[iZeroOrOne] : -1;
}

inline int CATPolyIntersectionPoint::GetBarIndex (const int iZeroOrOne) const
{
  return (_EntityType[iZeroOrOne] == CATPoly::eBar) ? _EntityIndex[iZeroOrOne] : -1;
}

inline const double* CATPolyIntersectionPoint::GetBarycentricCoordinates(const int iZeroOrOne) const
{
  return _BarycentricCoords[iZeroOrOne];
}

inline int CATPolyIntersectionPoint::operator != (const CATPolyIntersectionPoint& iIntersectionPoint) const
{
  return !operator == (iIntersectionPoint);
}

#endif
