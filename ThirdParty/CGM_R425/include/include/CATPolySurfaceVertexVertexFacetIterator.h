// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceVertexVertexFacetIterator.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
// 2010-01-11   NDO: New
//===================================================================
#ifndef CATPolySurfaceVertexVertexFacetIterator_H
#define CATPolySurfaceVertexVertexFacetIterator_H

#include "PolyMeshImpl.h"
#include "CATBoolean.h"
#include "CATPolySurfaceVertexFacetIterator.h"

class CATIPolySurface;
class CATIPolySurfaceVertexFacetNeighborhood;
class CATIPolyMeshTriangleIterator;

/**
 * Iterator that cycles through all the facets adjacent to a bar (defined as a pair of vertices.)
 */
class ExportedByPolyMeshImpl CATPolySurfaceVertexVertexFacetIterator
{

public:

  CATPolySurfaceVertexVertexFacetIterator (const CATIPolySurface& iSurface, CATIPolySurfaceVertexFacetNeighborhood& iVertexFacetNeighborhood);
  ~CATPolySurfaceVertexVertexFacetIterator () {}

public:

  CATPolySurfaceVertexVertexFacetIterator& Begin (const int iVertex0, const int iVertex1);
  CATPolySurfaceVertexVertexFacetIterator& Begin ();

  inline CATBoolean End () const;


  CATPolySurfaceVertexVertexFacetIterator& operator++ ();

public:

  inline int Get ();
  inline int operator* ();
  inline int operator-> ();

private:

  CATPolySurfaceVertexFacetIterator _FacetIterator;
  const CATIPolySurface& _Surface;
  int _Vertex0;

};

inline CATBoolean CATPolySurfaceVertexVertexFacetIterator::End () const
{
  return _FacetIterator.End ();
}

inline int CATPolySurfaceVertexVertexFacetIterator::Get ()
{
  return _FacetIterator.Get ();
}

inline int CATPolySurfaceVertexVertexFacetIterator::operator* ()
{
  return *_FacetIterator;
}

inline int CATPolySurfaceVertexVertexFacetIterator::operator-> ()
{
  return _FacetIterator.operator-> ();
}

#endif
