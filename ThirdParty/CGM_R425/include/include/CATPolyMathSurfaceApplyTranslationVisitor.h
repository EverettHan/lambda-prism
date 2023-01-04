// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathSurfaceApplyTranslationVisitor.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// 2010-10-04  XXC:Creation
//===================================================================
#ifndef CATPolyMathSurfaceApplyTranslationVisitor_H
#define CATPolyMathSurfaceApplyTranslationVisitor_H

#include "PolyMathSurfaces.h"
#include "CATPolyMathSurfaceVisitor.h"
#include "CATErrorDef.h"
#include "CATPolyMathSurface.h"
#include "CATBoolean.h"

class CATMathVector;

class CATPolyMathPNTriangleSurface;
class CATPolyMathTriangleSurfaceWithSupport;

class CATPolyMathCGMSurface;
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
class ExportedByPolyMathSurfaces CATPolyMathSurfaceApplyTranslationVisitor : public CATPolyMathSurfaceVisitor
{

public:

  CATPolyMathSurfaceApplyTranslationVisitor (const CATMathVector & iTranslation);
  ~CATPolyMathSurfaceApplyTranslationVisitor ();

public:

  /** Apply a transformation to the given surface. The surface is
   *  modified and is the transformed surface after the call to the
   *  method.
   */
  HRESULT ApplyToItself(CATPolyMathSurface & iSurface);

  /** Make a copy of the constant surface then apply the
   *  transformation to the copy only. The copied surface is allocated
   *  inside this method and must be deleted by the caller.
   */
  HRESULT ApplyToACopy(const CATPolyMathSurface & iSurface, CATPolyMathSurface *& ioSurface);

public:
  
  HRESULT VisitConcrete (CATPolyMathConeSurface& ioSurface);
  HRESULT VisitConcrete (CATPolyMathCylinderSurface& ioSurface);
  HRESULT VisitConcrete (CATPolyMathPlaneSurface& ioSurface);
  HRESULT VisitConcrete (CATPolyMathSphereSurface& ioSurface);
  HRESULT VisitConcrete (CATPolyMathTorusSurface& ioSurface);

private:

  const CATMathVector & _ToApply;

  CATPolyMathSurface * _ToReturn;
  CATBoolean _MakeACopy;
};

#endif
