//=============================================================================
// COPYRIGHT Dassault Systemes 2004, 2007
//=============================================================================
//
// CATIPolyMeshTriangleIterator.h
// Iterate over a set of triangles of a CATIPolyMesh
//
//=============================================================================
//
// This interface is used to iterate over triangles of a CATIPolyMesh.
// For example, one can write:
//
// CATIPolyMeshTriangleIterator *it = 0;
// if (SUCCEDED(Mesh.GetTriangleIterator(it) && it))
// {
//   for (it->Begin (); !it->End(); ++(*it))
//   {
//     int t = it->Get();  // Also: "int t = **it;"
//   }
//   it->Release();
//   it = 0;
// }
//
//
//=============================================================================
//
// 2008-02-13 NDO: Added standard iterator methods (Begin, End, operator++, Get, operator*).
//                 Deprecated obsolete methods (Next ()).
//
// 2007-06-08 BPG: Introduce Get() and End(). Remove default argument of
// Next(). Remove inheritance on CATBaseUnknown.
//
// 2007-04-26 BPG: Rename to CATIPolyMeshTriangleIterator.
//
// 2004-05-xx NDO: New.
//=============================================================================
#ifndef CATIPolyMeshTriangleIterator_H
#define CATIPolyMeshTriangleIterator_H

#include "PolyhedralModel.h"
#include "CATIPolySurfaceFacetIterator.h"

class CATMathPoint;


/**
* Interface to a mesh triangle iterator.
*/
class ExportedByPolyhedralModel CATIPolyMeshTriangleIterator : public CATIPolySurfaceFacetIterator
{
protected:

  CATIPolyMeshTriangleIterator();
  virtual ~CATIPolyMeshTriangleIterator();

};

#endif // CATIPolyMeshTriangleIterator_H
