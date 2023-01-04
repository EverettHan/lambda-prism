// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED
//===================================================================
//
// CATPolyMeshVertexVertexTriangleIterator.h
//
//===================================================================
// August 2008 Creation: NDO
//===================================================================
#ifndef CATPolyMeshVertexVertexTriangleIterator_H
#define CATPolyMeshVertexVertexTriangleIterator_H

#include "PolyMeshImpl.h"
#include "CATBoolean.h"
#include "CATListOfInt.h"

class CATIPolyMesh;
class CATIPolySurfaceVertexFacetNeighborhood;


/**
 * Iterate through the triangles referring to two given vertices from a CATIPolyMesh.
 */
class ExportedByPolyMeshImpl CATPolyMeshVertexVertexTriangleIterator
{

public:

  CATPolyMeshVertexVertexTriangleIterator (const CATIPolyMesh& iMesh);
  CATPolyMeshVertexVertexTriangleIterator (const CATIPolyMesh& iMesh, const CATIPolySurfaceVertexFacetNeighborhood* iNeighborhood);
  CATPolyMeshVertexVertexTriangleIterator (const CATIPolyMesh& iMesh, const int iVertex0, const int iVertex1);

  ~CATPolyMeshVertexVertexTriangleIterator () {_Neighborhood = 0;}

public:

  inline CATPolyMeshVertexVertexTriangleIterator& Begin ();
  CATPolyMeshVertexVertexTriangleIterator& Begin (const int iVertex0, const int iVertex1);
  inline CATBoolean End () const;

public:

  inline CATPolyMeshVertexVertexTriangleIterator& operator++ ();

public:

  inline int Get ();
  inline int operator* ();
  inline int operator-> ();

private:

  const CATIPolyMesh& _Mesh;
  const CATIPolySurfaceVertexFacetNeighborhood* _Neighborhood;

  CATListOfInt _Triangles;
  int _Index;

};


inline CATPolyMeshVertexVertexTriangleIterator& CATPolyMeshVertexVertexTriangleIterator::Begin ()
{
  _Index = 1;
  return *this;
}


inline CATBoolean CATPolyMeshVertexVertexTriangleIterator::End () const
{
  return _Index > _Triangles.Size ();
}


inline CATPolyMeshVertexVertexTriangleIterator& CATPolyMeshVertexVertexTriangleIterator::operator++ ()
{
  ++_Index;
  return *this;
}

inline int CATPolyMeshVertexVertexTriangleIterator::Get ()
{
  return _Triangles[_Index];
}

inline int CATPolyMeshVertexVertexTriangleIterator::operator* ()
{
  return _Triangles[_Index];
}

inline int CATPolyMeshVertexVertexTriangleIterator::operator-> ()
{
  return _Triangles[_Index];
}

#endif
