// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceVertexFacetIterator.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
// 2010-01-08   NDO: New
//===================================================================
#ifndef CATPolySurfaceVertexFacetIterator_H
#define CATPolySurfaceVertexFacetIterator_H

#include "CATPolyMeshImpl.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATListOfInt.h"

class CATIPolySurfaceVertexFacetNeighborhood;


/**
 * Iterator that cycles through all the facets adjacent to a given vertex.
 */
class ExportedByPolyMeshImpl CATPolySurfaceVertexFacetIterator
{

public:

  CATPolySurfaceVertexFacetIterator (CATIPolySurfaceVertexFacetNeighborhood& iVertexFacetNeighborhood);
  ~CATPolySurfaceVertexFacetIterator ();

public:

  CATPolySurfaceVertexFacetIterator& Begin (const int iVertex);
  inline CATPolySurfaceVertexFacetIterator& Begin () {_Index = 1; return* this;}

  inline CATBoolean End () const {return _Index > _Facets.Size ();}

  inline CATPolySurfaceVertexFacetIterator& operator++ () {++_Index; return *this;}

public:

  inline int Get () {return _Facets[_Index];}
  inline int operator* () {return _Facets[_Index];}
  inline int operator-> () {return _Facets[_Index];}

private:

  // The parent class that knows how to associate the facet neighborhood to a vertex.
  CATIPolySurfaceVertexFacetNeighborhood& _VertexFacetNeighborhood;

  CATListOfInt _Facets;
  int _Index;

};

#endif
