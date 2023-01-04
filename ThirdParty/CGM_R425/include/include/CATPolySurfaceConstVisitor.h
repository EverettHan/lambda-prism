// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceConstVisitor.h
//
//===================================================================
// 2006-10-12   BPG     * New
// 2009-12-04   NDO     * Renamed from CATPolyMeshConstVisitor
// 2015-08-17   JXO     * CATPolyProxyMesh
//===================================================================
#ifndef CATPolySurfaceConstVisitor_H
#define CATPolySurfaceConstVisitor_H

#include "PolyhedralModel.h"
#include "CATIPolySurface.h"

class CATIPolyMesh;
class CATIPolyTriQuadMesh;

// Forward-declare concrete types (derived from CATIPolyMesh/CATIPolySurface.)
class CATPolyMeshImpl;
class CATPolyCompactMesh;
class CATPolyCompactMeshConst;
class CATPolySubMesh;
class CATPolyProxyMesh;
class CATPolyEditableMesh;
class CATPolyDeltaMeshConst;
class CATPolyDeltaMeshKeep;
class CATPolyDeltaMeshRemove;

// Other concrete types.
class CATTessPolyMesh;
class CATCldPolyMeshCGM;


/*
* Base class for visitors of CATIPolySurface's.
*/
class ExportedByPolyhedralModel CATPolySurfaceConstVisitor
{

public:

  virtual ~CATPolySurfaceConstVisitor() {}

public:

  /**
  * Inline method that forwards the request to the surface implementation.
  * If it accepts visitors, the surface implementation calls back the visit methods
  * with the concrete types or the default method.
  */
  inline HRESULT Visit(const CATIPolySurface& iSurface);

public:

  // Calls back the generic implementation of the visitor 
  // (when the concrete type is not supported.)
  virtual HRESULT VisitDefault(const CATIPolySurface& iSurface);
  virtual HRESULT VisitDefault(const CATIPolyMesh& iMesh);
  virtual HRESULT VisitDefault(const CATIPolyTriQuadMesh& iMesh);

public:

  /** @name For casting methods.
  @{ */

  typedef void* TOOLSID;

  /**
  * Returns 0 if the two tools ID are the same.
  */
  static inline int CompareToolsID(const TOOLSID& id1, const TOOLSID& id2);

  /**
  * Returns the tools ID for identification of the base visitor class
  * making callbacks to the concrete surface types.
  * (The base visitor class is implemented in the same framework as the
  * concrete types.)
  */
  virtual TOOLSID GetToolsID() const;

  /** @} */

public:

  /** @name Concrete types specific to PolyhedralObjects framework.
  @{ */

  virtual HRESULT VisitConcrete(const CATIPolyMesh& iMesh, const CATPolyMeshImpl&);
  virtual HRESULT VisitConcrete(const CATIPolyMesh& iMesh, const CATPolyCompactMesh&);
  virtual HRESULT VisitConcrete(const CATIPolyMesh& iMesh, const CATPolyCompactMeshConst&);
  virtual HRESULT VisitConcrete(const CATIPolyMesh& iMesh, const CATPolySubMesh&);
  virtual HRESULT VisitConcrete(const CATIPolyMesh& iMesh, const CATPolyProxyMesh&);
  virtual HRESULT VisitConcrete(const CATIPolyMesh& iMesh, const CATPolyEditableMesh&);
  virtual HRESULT VisitConcrete(const CATIPolyMesh& iMesh, const CATPolyDeltaMeshConst&);
  virtual HRESULT VisitConcrete(const CATIPolyMesh& iMesh, const CATPolyDeltaMeshKeep&);
  virtual HRESULT VisitConcrete(const CATIPolyMesh& iMesh, const CATPolyDeltaMeshRemove&);

  /** @} */

public:

  /** @name Concrete types specific to Tessellation framework.
  @{ */

  // TO DO: move to Tessellation framework.
  virtual HRESULT VisitConcrete(const CATIPolyMesh& iMesh, const CATTessPolyMesh &);

  /** @} */

public:

  /** @name Concrete types specific to GeometricObjectsCGM framework.
  @{ */

  // TO DO: move to GeometricObjectsCGM framework.
  virtual HRESULT VisitConcrete(const CATIPolyMesh& iMesh, const CATCldPolyMeshCGM &);

  /** @} */

};

inline HRESULT CATPolySurfaceConstVisitor::Visit(const CATIPolySurface& iSurface)
{
  return iSurface.Accept(iSurface, *this);
}

int CATPolySurfaceConstVisitor::CompareToolsID(const TOOLSID& id1, const TOOLSID& id2)
{
  return id1 == id2;
}

#endif // !CATPolySurfaceConstVisitor_H
