// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBarsExtractor.h
//
//===================================================================
//
// July 2009  Creation: NDO
//===================================================================
#ifndef CATPolyBarsExtractor_h
#define CATPolyBarsExtractor_h

#include "PolyMeshImpl.h"
#include "CATErrorDef.h"

class CATPolyBars;
class CATIPolyMesh;
class CATIPolyMeshTriangleVertexIterator;


class ExportedByPolyMeshImpl CATPolyBarsExtractor 
{

public:

  CATPolyBarsExtractor (void) {}

  ~CATPolyBarsExtractor (void) {}

public:

  // Extract all the bars from a CATIPolyMesh and add them to the CATPolyBars object.
  HRESULT Run (const CATIPolyMesh& iMesh, CATPolyBars& oBars) const;

  // Extract all the bars of the triangles of the CATIPolyMesh returned from the triangle iterator
  // and add them to the CATPolyBars object.
  HRESULT Run (const CATIPolyMesh& iMesh, CATIPolyMeshTriangleVertexIterator& iTriangleVertexIterator,
               CATPolyBars& oBars) const;

};

#endif
