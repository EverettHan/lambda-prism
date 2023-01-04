//=============================================================================
// COPYRIGHT Dassault Systemes 2006
//=============================================================================
//
// CATPolyMeshVertex.h
//
//=============================================================================
// 2006-11-15   BPG: New
//=============================================================================
#ifndef CATPolyMeshVertex_H
#define CATPolyMeshVertex_H

#include "CATPolySurfaceVertex.h"
#include "PolyMeshImpl.h"
#include "CATIPolyMesh.h"


class ExportedByPolyMeshImpl CATPolyMeshVertex : public CATPolySurfaceVertex
{

public:

  CATPolyMeshVertex (CATIPolyMesh& iMesh, int v) : CATPolySurfaceVertex (iMesh, v) {}
  virtual ~CATPolyMeshVertex () {}

public:

  inline CATIPolyMesh& GetMesh ();
  inline const CATIPolyMesh& GetMesh () const;

};

inline CATIPolyMesh& CATPolyMeshVertex::GetMesh ()
{
  return (CATIPolyMesh&) _PolySurface;
}

inline const CATIPolyMesh& CATPolyMeshVertex::GetMesh () const
{
  return (const CATIPolyMesh&) _PolySurface;
}

#endif // !CATPolyMeshVertex_H
