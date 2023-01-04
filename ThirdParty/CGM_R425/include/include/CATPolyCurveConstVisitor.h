// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyCurveConstVisitor.h
//
//===================================================================
// September 2009  Creation: NDO
//===================================================================
#ifndef CATPolyCurveConstVisitor_H
#define CATPolyCurveConstVisitor_H

#include "PolyhedralModel.h"
#include "CATIPolyCurve.h"

class CATIPolySurfaceVertexLine;

// Forward-declare concrete types (derived from CATIPolyCurve.)
class CATPolyLine;
class CATPolyLineConst;
class CATPolyEditableCurve;
class CATPolyMeshCurve;
class CATPolyMeshCurveConst;
class CATPolySurfaceVertexLine;
class CATPolyCompactSurfaceVertexLine;
class CATPolyCompactSurfaceVertexLineConst;
class CATPolyEditableSurfaceVertexLine;

// Other concrete types (PolyhedralVisualization)
class CATPolyLineGPEdge;
class CATPolyLineGPLine;
class CATPolyLineVizEdge;
class CATPolyLineVizLine;
class CATPolyLineEVizEdge;
class CATPolyLineEVizLine;
class CATPolyMeshVertexLineGPEdge;
class CATPolyMeshVertexLineVizEdge;
class CATPolyMeshVertexLineEVizUVEdge;

// Other concrete types (Tessellation)
class CATTessPolyLine;
class CATTessPolyMeshVertexLine;


/*
 * Base class for visitors of CATIPolyCurve's.
 */
class ExportedByPolyhedralModel CATPolyCurveConstVisitor
{

public:

  virtual ~CATPolyCurveConstVisitor () {}

public:

  /**
   * Inline method that forwards the request to the curve implementation.
   * If it accepts visitors, the curve implementation calls back the visit methods 
   * with the concrete types or the default method.
   */
  inline HRESULT Visit (const CATIPolyCurve &iCurve);

public:

  // Calls back the generic implementation of the visitor 
  // (when the concrete type is not supported.)
  virtual HRESULT VisitDefault (const CATIPolyCurve& iCurve) = 0 ;
  virtual HRESULT VisitDefault (const CATIPolySurfaceVertexLine& iSVL) ;

public:

/** @name For casting methods.
    @{ */

  // TO DO.
  // See CATPolySurfaceConstVisitor.

  typedef void* TOOLSID;

/** @} */

public:

/** @name Concrete types specific to PolyhedralObjects framework.
    @{ */

  virtual HRESULT VisitConcrete (const CATIPolyCurve& iCurve, const CATPolyLine&);
  virtual HRESULT VisitConcrete (const CATIPolyCurve& iCurve, const CATPolyLineConst&);
  virtual HRESULT VisitConcrete (const CATIPolyCurve& iCurve, const CATPolyEditableCurve&);
  virtual HRESULT VisitConcrete (const CATIPolyMeshCurve& iMC, const CATPolyMeshCurve&);
  virtual HRESULT VisitConcrete (const CATIPolyMeshCurve& iMC, const CATPolyMeshCurveConst&);
  virtual HRESULT VisitConcrete (const CATIPolySurfaceVertexLine& iSVL, const CATPolySurfaceVertexLine&);
  virtual HRESULT VisitConcrete (const CATIPolySurfaceVertexLine& iSVL, const CATPolyCompactSurfaceVertexLine&);
  virtual HRESULT VisitConcrete (const CATIPolySurfaceVertexLine& iSVL, const CATPolyCompactSurfaceVertexLineConst&);
  virtual HRESULT VisitConcrete (const CATIPolySurfaceVertexLine& iSVL, const CATPolyEditableSurfaceVertexLine&);

/** @} */

public:

/** @name Concrete types specific to PolyhedralVisualization framework.
    @{ */

  // TO DO: move to PolyhedralVisualization framework.

  // Wire curves.
  virtual HRESULT VisitConcrete (const CATIPolyCurve& iCurve, const CATPolyLineGPEdge&);
  virtual HRESULT VisitConcrete (const CATIPolyCurve& iCurve, const CATPolyLineGPLine&);
  virtual HRESULT VisitConcrete (const CATIPolyCurve& iCurve, const CATPolyLineVizEdge&);
  virtual HRESULT VisitConcrete (const CATIPolyCurve& iCurve, const CATPolyLineEVizEdge&);
  virtual HRESULT VisitConcrete (const CATIPolyCurve& iCurve, const CATPolyLineVizLine&);
  virtual HRESULT VisitConcrete (const CATIPolyCurve& iCurve, const CATPolyLineEVizLine&);

  // Surface vertex lines.
  virtual HRESULT VisitConcrete (const CATIPolySurfaceVertexLine& iSVL, const CATPolyMeshVertexLineGPEdge&);
  virtual HRESULT VisitConcrete (const CATIPolySurfaceVertexLine& iSVL, const CATPolyMeshVertexLineVizEdge&);
  virtual HRESULT VisitConcrete (const CATIPolySurfaceVertexLine& iSVL, const CATPolyMeshVertexLineEVizUVEdge&);

/** @} */

public:

/** @name Concrete types specific to Tessellation framework.
    @{ */

  // TO DO: move to Tessellation framework.

  // Wire curves.
  virtual HRESULT VisitConcrete (const CATIPolyCurve& iCurve, const CATTessPolyLine&);

  // Surface vertex lines.
  virtual HRESULT VisitConcrete (const CATIPolySurfaceVertexLine& iSVL, const CATTessPolyMeshVertexLine&);

/** @} */

};

inline HRESULT CATPolyCurveConstVisitor::Visit (const CATIPolyCurve& iCurve)
{
  return iCurve.Accept (iCurve, *this);
}

#endif // !CATPolyCurveConstVisitor_H
