// COPYRIGHT DASSAULT SYSTEMES 2016, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyCellPoint.h
//
//===================================================================
// November 2016  Creation NDO
//===================================================================
#ifndef CATPolyCellPoint_H
#define CATPolyCellPoint_H

#include "PolyMODEL.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATMathPoint.h"
#include "CATPoly.h"

class CATPolyCell;


/**
 * Definition of a point lying on an element (triangle, bar or vertex) of a CATPolyCell.
 * 
 * A cell-point is defined by:
 *  - One, two or three surface-vertices associated to one, two or three barycentric coordinates, respectively; or,
 *  - One or two curve-vertices associated to one or two barycentric coordinates, respectively; or,
 *  - A reference to a CATPolyVertex.
 *
 * The sum of the barycentric coordinates is equal to 1 (within the numerical accuracy.)
 * <ul>
 *   <li> If the element is a vertex (curve-vertex or surface-vertex), the cell-point 
 *        just refers to the vertex.  (Its barycentric coordinate is equal to 1 in this case.)
 *   <li> If the element is a bar (curve-bar or surface-bar), the cell-point refers to the
 *        two cell-vertices defining the bar and two barycentric coordinates defining the position
 *        of the point on the bar.
 *   <li> If the element is a triangle, the cell-point refers to the three vertices of the triangle
 *        and three barycentric coordinates defining the position of the point on the triangle.
 * </ul>
 */
class ExportedByPolyMODEL CATPolyCellPoint 
{

public:

  /**
   * Enumerator defining the type of an entity: vertex, bar or triangle.
   * @see CATPoly.h
   */
  typedef CATPoly::EntityType ElementType;

public:

  inline CATPolyCellPoint ();

  /**
   * Copy constructor.
   */
  inline CATPolyCellPoint (const CATPolyCellPoint& rhs);

  inline ~CATPolyCellPoint ();

  inline void Clear ();

public:

  /**
   * Assignment operator.
   */
  inline CATPolyCellPoint& operator = (const CATPolyCellPoint& rhs);

public:

  /**
   * Sets the CATPolyCell on which the point is defined.
   */
  inline void Set (CATPolyCell* cell);

  /**
   * Defines a cell-point as a cell-vertex.
   */
  inline void Set (int v);

  /**
   * Defines a cell-point as point lying on a bar.
   * @param v0, v1
   *   The vertices of the tips of the bar.
   * @param u, v
   *   The barycentric coordinates for each vertex, respectively, defining 
   *   the position on the bar.
   */
  inline void Set (int v0, int v1, double u, double v);

  /**
   * Defines a cell-point as a point lying on a triangle.
   * @param v0, v1, v2
   *   The vertices of the corners of the triangle.
   * @param u, v, w
   *   The barycentric coordinates for each vertex, respectively, defining 
   *   the position on the triangle.
   */
  inline void Set (int v0, int v1, int v2, double u, double v, double w);

public:

  /**
   * Returns the type of the cell-point.
   * @return
   * <ul>
   *   <li> CATPoly::eVertex for a cell-point on a vertex.
   *   <li> CATPoly::eBar for a cell-point on a bar.
   *   <li> CATPoly::eTriangle for a cell-point on a triangle.
   * </ul>
   */
  inline ElementType GetType () const;

  /**
   * Returns the CATPolyCell on which the point is defined.
   */
  inline CATPolyCell* GetPolyCell () const;

  /**
   * Returns the three surface-vertices defining the cell-point.
   * The second and third coordinates are equal to 0 for a cell-point on a vertex.
   * The third coordinate is equal to 0 for a cell-point on a bar.
   */
  inline void GetVertices (int& v0, int& v1, int& v2) const;

  /**
   * Returns a surface-vertex given an index: 0, 1, or 2.
   */
  inline int GetVertex (unsigned int k) const;

  /**
   * Returns the barycentric coordinates associated to the vertices.
   */
  inline void GetBarycentricCoordinates (double& u, double& v, double& w) const;

  /**
   * Returns a barycentric coordinate given an index: 0, 1, or 2.
   */
  inline double GetBarycentricCoordinate (unsigned int k) const;

public:

  /**
   * Sets the triangle referred to by a cell-point.
   */
  inline void SetTriangle (int t);

  /**
   * Returns the triangle referred to by a cell-point.
   * The index 0 is an invalid triangle index. 
   */
  inline int GetTriangle () const;

public:

  /**
   * Returns 0 if p0 and p1 have the same definition.
   */
  //static int Compare (const CATPolyCellPoint& p0, const CATPolyCellPoint& p1);

  /**
   * Returns the hash number of the cell-point.
   */
  inline unsigned int Hash () const; 

private:

  CATPolyCell* _Cell;

  int _V[3];
  int _T;           // Triangle index. (Optional.)

  double _UVW[3];  // Barycentric Coordinates.  The sum of the three coordinates is equal to 1.

};

inline CATPolyCellPoint::CATPolyCellPoint ()
{
  _Cell = 0;
  _V[0] = 0;
  _V[1] = 0;
  _V[2] = 0;
  _T = 0;
  _UVW[0] = 0;
  _UVW[1] = 0;
  _UVW[2] = 0;
}

inline CATPolyCellPoint::CATPolyCellPoint (const CATPolyCellPoint& rhs)
{
  _Cell = rhs._Cell;
  _V[0] = rhs._V[0];
  _V[1] = rhs._V[1];
  _V[2] = rhs._V[2];
  _T = rhs._T;
  _UVW[0] = rhs._UVW[0];
  _UVW[1] = rhs._UVW[1];
  _UVW[2] = rhs._UVW[2];
}

inline CATPolyCellPoint::~CATPolyCellPoint ()
{
  _Cell = 0;
}

inline void CATPolyCellPoint::Clear ()
{
  _Cell = 0;
  _V[0] = 0;
  _V[1] = 0;
  _V[2] = 0;
  _T = 0;
  _UVW[0] = 0;
  _UVW[1] = 0;
  _UVW[2] = 0;
}

inline CATPolyCellPoint& CATPolyCellPoint::operator = (const CATPolyCellPoint& rhs)
{
  _Cell = rhs._Cell;
  _V[0] = rhs._V[0];
  _V[1] = rhs._V[1];
  _V[2] = rhs._V[2];
  _T = rhs._T;
  _UVW[0] = rhs._UVW[0];
  _UVW[1] = rhs._UVW[1];
  _UVW[2] = rhs._UVW[2];
  return *this;
}

inline void CATPolyCellPoint::Set (CATPolyCell* cell)
{
  _Cell = cell;
}

inline void CATPolyCellPoint::Set (int v)
{
  _V[0] = v;
  _V[1] = 0;
  _V[2] = 0;
  _UVW[0] = 1;
  _UVW[1] = 0;
  _UVW[2] = 0;
}

inline void CATPolyCellPoint::Set (int v0, int v1, double u, double v)
{
  if (v0 < v1)
  {
    _V[0] = v0;
    _V[1] = v1;
    _UVW[0] = u;
    _UVW[1] = v;
  }
  else
  {
    _V[0] = v1;
    _V[1] = v0;
    _UVW[0] = v;
    _UVW[1] = u;
  }
  _V[2] = 0;
  _UVW[2] = 0;
}

inline void CATPolyCellPoint::Set (int v0, int v1, int v2, double u, double v, double w)
{
  _V[0] = v0;
  _V[1] = v1;
  _V[2] = v2;
  _UVW[0] = u;
  _UVW[1] = v;
  _UVW[2] = w;
}

inline CATPolyCell* CATPolyCellPoint::GetPolyCell () const
{
  return _Cell;
}

inline CATPolyCellPoint::ElementType CATPolyCellPoint::GetType () const
{
  if (_V[2] != 0)
    return CATPoly::eTriangle;
  else if (_V[1] != 0)
    return CATPoly::eBar;
  else if (_V[0] != 0)
    return CATPoly::eVertex;
  else
    return CATPoly::eUndefined;
}

inline void CATPolyCellPoint::GetVertices (int& v0, int& v1, int& v2) const
{
  v0 = _V[0];
  v1 = _V[1];
  v2 = _V[2];
}

inline int CATPolyCellPoint::GetVertex (unsigned int k) const
{
  return _V[k];
}

inline void CATPolyCellPoint::GetBarycentricCoordinates (double& u, double& v, double& w) const
{
  u = _UVW[0];
  v = _UVW[1];
  w = _UVW[2];
}

inline double CATPolyCellPoint::GetBarycentricCoordinate (unsigned int k) const
{
  return _UVW[k];
}

inline void CATPolyCellPoint::SetTriangle (int t)
{
  _T = t;
}

inline int CATPolyCellPoint::GetTriangle () const
{
  return _T;
}

inline unsigned int CATPolyCellPoint::Hash () const
{
  return _V[0];
}

#endif
