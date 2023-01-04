//=============================================================================
// COPYRIGHT Dassault Systemes 2006
//=============================================================================
//
// CATPolyPreAllocatedMeshVertexLine.h
//
//=============================================================================
// 2010-03-15   ZFI: New
// 2014-10-09   JXO: Observers
// 2014-12-03   NDO: Optimization, Surface Observer
// 2015-09-08   NDO: Replace float W layer by double W layer
// November 2015  NDO @see CATPolyCompactSurfaceVertexLine
//=============================================================================
#ifndef CATPolyPreAllocatedMeshVertexLine_H
#define CATPolyPreAllocatedMeshVertexLine_H

#include "PolyMeshImpl.h"
#include "CATPolyCompactSurfaceVertexLine.h"

class CATIPolyMesh;


/**
 * @see CATPolyCompactSurfaceVertexLine
 */
class ExportedByPolyMeshImpl CATPolyPreAllocatedMeshVertexLine : public CATPolyCompactSurfaceVertexLine
{

public:

/** @name Life Cycle
    @{ */

  static CATPolyPreAllocatedMeshVertexLine* New (CATIPolyMesh& iMesh, int NbVerticesToAllocate, 
                                                 CATBoolean iWithVertexWLayer, CATBoolean iWithVertexTangentLayer);

  virtual ~CATPolyPreAllocatedMeshVertexLine ();

/** @} */

public:

/** @name Methods specific to this implementation
    @{ */

  // To get rid of.
  CATIPolyMesh& GetMesh ();
  const CATIPolyMesh& GetMesh () const;

  // Deprecated.
  inline HRESULT AppendMeshVertex (int i, int &v);
  inline HRESULT InsertMeshVertex (int i, int j, int &v);

/** @} */

private:

  // Private constructor.
  CATPolyPreAllocatedMeshVertexLine (CATIPolyMesh& iMesh);

  friend class CATPolyCompactSurfaceVertexLine;

};

inline HRESULT CATPolyPreAllocatedMeshVertexLine::AppendMeshVertex (int sv, int &v)
{
  return CATPolyCompactSurfaceVertexLine::AppendSurfaceVertex (sv, v);
}

inline HRESULT CATPolyPreAllocatedMeshVertexLine::InsertMeshVertex (int sv, int vn, int &v)
{
  return CATPolyCompactSurfaceVertexLine::InsertSurfaceVertex (sv, vn, v);
}

#endif // !CATPolyPreAllocatedMeshVertexLine_H
