// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathSurfaceConstVisitor.h
// Header definition of CATPolyMathSurfaceConstVisitor
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// June 2007  Creation: ndo
//===================================================================
#ifndef CATPolyMathSurfaceConstVisitor_H
#define CATPolyMathSurfaceConstVisitor_H

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
class ExportedByPolyMathSurfaces CATPolyMathSurfaceConstVisitor
{

public:

  CATPolyMathSurfaceConstVisitor () {}
  virtual ~CATPolyMathSurfaceConstVisitor () {}

public:

  inline HRESULT Visit (const CATPolyMathSurface& iSurface);

public:

  virtual HRESULT VisitConcrete (const CATPolyMathPNTriangleSurface& iSurface);
  virtual HRESULT VisitConcrete (const CATPolyMathTriangleSurfaceWithSupport& iSurface);

  virtual HRESULT VisitConcrete (const CATPolyMathConeSurface& iSurface);
  virtual HRESULT VisitConcrete (const CATPolyMathCubicBSplineSurface& iSurface);
  virtual HRESULT VisitConcrete (const CATPolyMathCylinderSurface& iSurface);
  virtual HRESULT VisitConcrete (const CATPolyMathPlaneSurface& iSurface);
  virtual HRESULT VisitConcrete (const CATPolyMathSolidOfRevolutionSurface& iSurface);
  virtual HRESULT VisitConcrete (const CATPolyMathSphereSurface& iSurface);
  virtual HRESULT VisitConcrete (const CATPolyMathTorusSurface& iSurface);

public:

  virtual HRESULT VisitDefault(const CATPolyMathSurface& iSurface);

};


inline HRESULT CATPolyMathSurfaceConstVisitor::Visit (const CATPolyMathSurface& iSurface)
{
  return iSurface.Accept (*this);
}

#endif
