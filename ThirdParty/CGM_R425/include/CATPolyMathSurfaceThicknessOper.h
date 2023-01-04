// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathSurfaceThicknessOper.h
// Header definition of CATPolyMathSurfaceThicknessOper
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// June 2007  Creation: ndo
//===================================================================
#ifndef CATPolyMathSurfaceThicknessOper_H
#define CATPolyMathSurfaceThicknessOper_H

#include "PolyMathSurfaces.h"
#include "CATPolyMathSurfaceConstVisitor.h"
#include "CATErrorDef.h"  // HRESULT definition.

class CATPolyMathSurface;
class CATPolyMathPNTriangleSurface;


class ExportedByPolyMathSurfaces CATPolyMathSurfaceThicknessOper : public CATPolyMathSurfaceConstVisitor
{

public:

  CATPolyMathSurfaceThicknessOper () {}
  ~CATPolyMathSurfaceThicknessOper () {}

public:

  // Compute positive and negative bounds to signed thicknesses of a surface (patch) w.r.t.
  // its principal plane.  A point on the patch is guaranteed to be at a signed distance of the 
  // plane within the interval [oMinHNeg, oMaxHPos].
  inline HRESULT Run (const CATPolyMathSurface& iSurface);

  inline double GetBoundToMinimumHeight () const;
  inline double GetBoundToMaximumHeight () const;

public:

  HRESULT VisitConcrete (const CATPolyMathPNTriangleSurface& iSurface);

protected:

  double _BoundMinimumHeight;
  double _BoundMaximumHeight;

};


inline HRESULT CATPolyMathSurfaceThicknessOper::Run (const CATPolyMathSurface& iSurface)
{
  return Visit (iSurface);
}


inline double CATPolyMathSurfaceThicknessOper::GetBoundToMinimumHeight () const
{
  return _BoundMinimumHeight;
}

inline double CATPolyMathSurfaceThicknessOper::GetBoundToMaximumHeight () const
{
  return _BoundMaximumHeight;
}

#endif
