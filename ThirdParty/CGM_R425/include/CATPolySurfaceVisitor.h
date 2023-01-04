// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceVisitor.h
//
//===================================================================
// December 2009  Creation: NDO
//===================================================================
#ifndef CATPolySurfaceVisitor_H
#define CATPolySurfaceVisitor_H

#include "PolyhedralModel.h"
#include "CATIPolySurface.h"

class CATIPolyMesh;
class CATIPolyTriQuadMesh;

// Forward-declare concrete types (derived from CATIPolyMesh/CATIPolySurface.)
class CATPolyMeshImpl;
class CATPolyCompactMesh;
class CATPolyEditableMesh;

// Other concrete types.
class CATCldPolyMeshCGM;  // Get rid of me.


/*
* Base class for visitors of CATIPolySurface's.
*/
class ExportedByPolyhedralModel CATPolySurfaceVisitor
{

public:

  virtual ~CATPolySurfaceVisitor () {}

public:

  // Inline method that forwards the request to the surface implementation.
  // If it accepts visitors, the surface implementation calls back the visit methods 
  // with the concrete types or the default method.
  inline HRESULT Visit (CATIPolySurface& iSurface);

public:

  // Calls back the generic implementation of the visitor 
  // (when the concrete type is not supported.)
  virtual HRESULT VisitDefault (CATIPolySurface& iSurface);
  virtual HRESULT VisitDefault (CATIPolyMesh& iMesh);
  virtual HRESULT VisitDefault (CATIPolyTriQuadMesh& iMesh);

public:

/** @name Concrete types specific to PolyhedralObjects framework.
    @{ */

  virtual HRESULT VisitConcrete (CATIPolyMesh& iMesh, CATPolyMeshImpl&);
  virtual HRESULT VisitConcrete (CATIPolyMesh& iMesh, CATPolyCompactMesh&);
  virtual HRESULT VisitConcrete (CATIPolyMesh& iMesh, CATPolyEditableMesh&);

/** @} */

public:

/** @name Concrete types specific to GeometricObjectsCGM framework.
    @{ */

  // TO DO: move to GeometricObjectsCGM framework.
  virtual HRESULT VisitConcrete (CATIPolyMesh& iMesh, CATCldPolyMeshCGM &);

/** @} */

};

inline HRESULT CATPolySurfaceVisitor::Visit (CATIPolySurface& iSurface)
{
  return iSurface.Accept (iSurface, *this);
}

#endif // !CATPolySurfaceVisitor_H
