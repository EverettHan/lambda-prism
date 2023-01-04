//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATPolyMeshHoleVertexIterator
//
//=============================================================================
// 2008-05-23   BPG: New
//=============================================================================
#ifndef CATPolyMeshHoleVertexIterator_H
#define CATPolyMeshHoleVertexIterator_H

#include "PolyMeshImpl.h"
#include "CATIPolySurfaceVertexIterator.h"

class CATIPolyMesh;
class CATIPolySurfaceVertexFacetNeighborhood;


class ExportedByPolyMeshImpl CATPolyMeshHoleVertexIterator : public CATIPolySurfaceVertexIterator
{

public:

  CATPolyMeshHoleVertexIterator (const CATIPolyMesh &Mesh);
  CATPolyMeshHoleVertexIterator (const CATIPolyMesh &Mesh, CATIPolySurfaceVertexIterator &It);

  virtual ~CATPolyMeshHoleVertexIterator();

public:

  CATIPolyIndexIterator& Begin ();
  CATBoolean End () const;
  CATIPolyIndexIterator& operator++ ();

  int Get () const;
  int operator* ();

protected:

  CATIPolySurfaceVertexFacetNeighborhood* _Neighborhood;
  CATIPolySurfaceVertexIterator* _It;

};

#endif // CATPolyMeshHoleVertexIterator_H
