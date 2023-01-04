// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathSurfaceVisitor.h
// Header definition of CATPolyMathSurfaceVisitor
//
//===================================================================
//
// Usage notes:
//
//===================================================================
// June 2007  Creation: ndo
//===================================================================
#ifndef CATPolyMathSurfaceVisitor_H
#define CATPolyMathSurfaceVisitor_H

#include "PolyMathSurfaces.h"
#include "CATErrorDef.h"
#include "CATPolyMathSurface.h"

class CATPolyMathPNTriangleSurface;
class CATPolyMathTriangleSurfaceWithSupport;

class CATPolyMathConeSurface;
class CATPolyMathCubicBSplineSurface;
class CATPolyMathCylinderSurface;
class CATPolyMathPlaneSurface;
class CATPolyMathSolidOfRevolutionSurface;
class CATPolyMathSphereSurface;
class CATPolyMathTorusSurface;

/**
 * Describe your class here.
 */
class ExportedByPolyMathSurfaces CATPolyMathSurfaceVisitor
{

public:

  CATPolyMathSurfaceVisitor () {}
  virtual ~CATPolyMathSurfaceVisitor () {}

public:

  inline HRESULT Visit (CATPolyMathSurface& iSurface);

public:

  virtual HRESULT VisitConcrete (CATPolyMathPNTriangleSurface& iSurface);
  virtual HRESULT VisitConcrete (CATPolyMathTriangleSurfaceWithSupport& iSurface);

  virtual HRESULT VisitConcrete (CATPolyMathConeSurface& iSurface);
  virtual HRESULT VisitConcrete (CATPolyMathCubicBSplineSurface& iSurface);
  virtual HRESULT VisitConcrete (CATPolyMathCylinderSurface& iSurface);
  virtual HRESULT VisitConcrete (CATPolyMathPlaneSurface& iSurface);
  virtual HRESULT VisitConcrete (CATPolyMathSolidOfRevolutionSurface& iSurface);
  virtual HRESULT VisitConcrete (CATPolyMathSphereSurface& iSurface);
  virtual HRESULT VisitConcrete (CATPolyMathTorusSurface& iSurface);

public:

  virtual HRESULT VisitDefault(CATPolyMathSurface& iSurface);

};


inline HRESULT CATPolyMathSurfaceVisitor::Visit (CATPolyMathSurface& iSurface)
{
  return iSurface.Accept (*this);
}

#endif
