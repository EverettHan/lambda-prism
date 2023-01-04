// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyCurveVisitor.h
//
//===================================================================
// September 2009  Creation: NDO
//===================================================================
#ifndef CATPolyCurveVisitor_H
#define CATPolyCurveVisitor_H

#include "PolyhedralModel.h"
#include "CATIPolyCurve.h"

class CATIPolyMeshCurve;
class CATIPolySurfaceVertexLine;

// Forward-declare concrete types (derived from CATIPolyCurve.)
class CATPolyLine;
class CATPolyEditableCurve;
class CATPolyMeshCurve;
class CATPolySurfaceVertexLine;
class CATPolyCompactSurfaceVertexLine;
class CATPolyEditableSurfaceVertexLine;


/*
* Base class for visitors of CATIPolyCurve's.
*/
class ExportedByPolyhedralModel CATPolyCurveVisitor
{

public:

  virtual ~CATPolyCurveVisitor () {}

public:

  /**
   * Inline method that forwards the request to the curve implementation.
   * If it accepts visitors, the curve implementation calls back the visit methods 
   * with the concrete types or the default method.
   */
  inline HRESULT Visit (CATIPolyCurve &iCurve);

public:

  // Calls back the generic implementation of the visitor 
  // (when the concrete type is not supported.)
  virtual HRESULT VisitDefault (CATIPolyCurve& iCurve);
  virtual HRESULT VisitDefault (CATIPolySurfaceVertexLine& iSVL);

public:

/** @name Concrete types specific to PolyhedralObjects framework.
    @{ */

  virtual HRESULT VisitConcrete (CATIPolyCurve& iCurve, CATPolyLine&);
  virtual HRESULT VisitConcrete (CATIPolyCurve& iCurve, CATPolyEditableCurve&);
  virtual HRESULT VisitConcrete (CATIPolyMeshCurve& iMC, CATPolyMeshCurve&);
  virtual HRESULT VisitConcrete (CATIPolySurfaceVertexLine& iSVL, CATPolySurfaceVertexLine&);
  virtual HRESULT VisitConcrete (CATIPolySurfaceVertexLine& iSVL, CATPolyCompactSurfaceVertexLine&);
  virtual HRESULT VisitConcrete (CATIPolySurfaceVertexLine& iSVL, CATPolyEditableSurfaceVertexLine&);

/** @} */

};

inline HRESULT CATPolyCurveVisitor::Visit (CATIPolyCurve& iCurve)
{
  return iCurve.Accept (iCurve, *this);
}

#endif // !CATPolyCurveVisitor_H
