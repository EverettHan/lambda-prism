// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMeshPointDef.h
//
//===================================================================
// May 2015  Creation NDO
//===================================================================
#ifndef CATPolyMeshPointDef_H
#define CATPolyMeshPointDef_H

#include "PolyhedralModel.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATMathPoint.h"
//#include "CATPoly.h"


/**
 * Definition of a mesh-point.
 * 
 * A mesh-point lies on a CATIPolyMesh.  It refers to a sub-element of the mesh and can lie
 * on a vertex (surface-vertex), a bar (surface-bar) or a triangle of the mesh. 
 *
 * More specifically, a mesh-point is defined by one, two or three surface-vertices
 * associated to one, two or three barycentric coordinates, respectively.
 * <ul>
 *   <li> The mesh-point just refers to a surface-vertex with the first barycentric coordinate
 *        set to one in the case of a mesh-point on a vertex.
 *   <li> The mesh-point refers to two surface-vertices and two barycentric coordinates in the
 *        case of a mesh-point on a bar.
 *   <li> The mesh-point refers to three surface-vertices and three barycentric coordinates in the
 *        case of a mesh-point on a triangle.
 * </ul>
 *
 * The sum of the barycentric coordinates is equal to 1.
 */
class ExportedByPolyhedralModel CATPolyMeshPointDef 
{

public:

  /**
   * Enumerator defining the type of an entity: vertex, bar or triangle.
   * @see CATPoly.h
   */
  enum EntityType
  {
    /** Undefined type. */   eUndefined = 0,
    /** Vertex type. */      eVertex    = 1,
    /** Bar type. */         eBar       = 2,
    /** Triangle type. */    eTriangle  = 3
  };  

public:

  inline CATPolyMeshPointDef ();

  // Copy constructor.
  inline CATPolyMeshPointDef (const CATPolyMeshPointDef& rhs);

  ~CATPolyMeshPointDef () {}

public:

  /**
   * Assignment operator.
   */
  inline CATPolyMeshPointDef& operator = (const CATPolyMeshPointDef& rhs);

public:

  /**
   * Defines a mesh-point on a vertex.
   */
  inline void Set (int v);

  /**
   * Defines a mesh-point on a bar.
   */
  inline void Set (int v0, int v1, double u, double v);

  /**
   * Defines a mesh-point on a triangle.
   */
  inline void Set (int v0, int v1, int v2, double u, double v, double w);

public:

  /**
   * Returns the type of the mesh point.
   * @return
   * <ul>
   *   <li> CATPoly::eVertex for a mesh-point on a vertex.
   *   <li> CATPoly::eBar for a mesh-point on a bar.
   *   <li> CATPoly::eTriangle for a mesh-point on a triangle.
   * </ul>
   */
  inline EntityType GetType () const;

  /**
   * Returns the three surface-vertices defining the mesh-point.
   * The second and third coordinates are equal to 0 for a mesh-point on a vertex.
   * The third coordinate is equal to 0 for a mesh-point on a bar.
   */
  inline void GetVertices (int& v0, int& v1, int& v2) const;

  /**
   * Returns a surface-vertex given its index: 0, 1, or 2.
   */
  inline int GetVertex (unsigned int index) const;

  /**
   * Returns the barycentric coordinates associated to the vertices.
   */
  inline void GetBarycentricCoordinates (double& u, double& v, double& w) const;

  /**
   * Returns a barycentric coordinate given its index: 0, 1, or 2.
   */
  inline double GetBarycentricCoordinate (unsigned int index) const;

public:

  /**
   * Sets the triangle referred to by a mesh-point.
   */
  inline void SetTriangle (int t);

  inline int GetTriangle () const;

public:

  /**
   * Returns 0 if p0 and p1 have the same definition.
   */
  //static int Compare (const CATPolyMeshPointDef& p0, const CATPolyMeshPointDef& p1);

  /**
   * Returns the hash number of the mesh-point.
   */
  inline unsigned int Hash () const; 

private:

  int _V[3];
  int _T;           // Triangle index. (Optional.)

  double _UVW[3];  // Barycentric Coordinates.  The sum of the three coordinates is equal to 1.

};

inline CATPolyMeshPointDef::CATPolyMeshPointDef ()
{
  _V[0] = 0;
  _V[1] = 0;
  _V[2] = 0;
  _T = 0;
  _UVW[0] = 0;
  _UVW[1] = 0;
  _UVW[2] = 0;
}

inline CATPolyMeshPointDef::CATPolyMeshPointDef (const CATPolyMeshPointDef& rhs)
{
  _V[0] = rhs._V[0];
  _V[1] = rhs._V[1];
  _V[2] = rhs._V[2];
  _T = rhs._T;
  _UVW[0] = rhs._UVW[0];
  _UVW[1] = rhs._UVW[1];
  _UVW[2] = rhs._UVW[2];
}

inline CATPolyMeshPointDef& CATPolyMeshPointDef::operator = (const CATPolyMeshPointDef& rhs)
{
  _V[0] = rhs._V[0];
  _V[1] = rhs._V[1];
  _V[2] = rhs._V[2];
  _T = rhs._T;
  _UVW[0] = rhs._UVW[0];
  _UVW[1] = rhs._UVW[1];
  _UVW[2] = rhs._UVW[2];
  return *this;
}

inline void CATPolyMeshPointDef::Set (int v)
{
  _V[0] = v;
  _V[1] = 0;
  _V[2] = 0;
  _UVW[0] = 1;
  _UVW[1] = 0;
  _UVW[2] = 0;
}

inline void CATPolyMeshPointDef::Set (int v0, int v1, double u, double v)
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

inline void CATPolyMeshPointDef::Set (int v0, int v1, int v2, double u, double v, double w)
{
  _V[0] = v0;
  _V[1] = v1;
  _V[2] = v2;
  _UVW[0] = u;
  _UVW[1] = v;
  _UVW[2] = w;
}

inline CATPolyMeshPointDef::EntityType CATPolyMeshPointDef::GetType () const
{
  if (_V[2] != 0)
    return eTriangle;
  else if (_V[1] != 0)
    return eBar;
  else if (_V[0] != 0)
    return eVertex;
  else
    return eUndefined;
}

inline void CATPolyMeshPointDef::GetVertices (int& v0, int& v1, int& v2) const
{
  v0 = _V[0];
  v1 = _V[1];
  v2 = _V[2];
}

inline int CATPolyMeshPointDef::GetVertex (unsigned int index) const
{
  return _V[index];
}

inline void CATPolyMeshPointDef::GetBarycentricCoordinates (double& u, double& v, double& w) const
{
  u = _UVW[0];
  v = _UVW[1];
  w = _UVW[2];
}

inline double CATPolyMeshPointDef::GetBarycentricCoordinate (unsigned int index) const
{
  return _UVW[index];
}

inline void CATPolyMeshPointDef::SetTriangle (int t)
{
  _T = t;
}

inline int CATPolyMeshPointDef::GetTriangle () const
{
  return _T;
}

inline unsigned int CATPolyMeshPointDef::Hash () const
{
  return _V[0];
}

#endif
