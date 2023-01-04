// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyPointConstVisitor.h
//
//===================================================================
// December 2009  Creation: NDO
//===================================================================
#ifndef CATPolyPointConstVisitor_H
#define CATPolyPointConstVisitor_H

#include "PolyhedralModel.h"
#include "CATIPolyPoint.h"

class CATIPolyCurvePoint;
class CATIPolyMeshPoint;
class CATIPolyCurveVertex;
class CATIPolySurfaceVertex;

// Forward-declare concrete types (derived from CATIPolyPoint.)
class CATPolyPoint;
class CATPolyCurvePoint;
class CATPolyMeshPoint;
class CATPolyCurveVertex;
class CATPolySurfaceVertex;

// Other concrete types (PolyhedralVisualization)
class CATPolyPointMeshVertex;  // PolyhedralVisualization
class CATPolyPoint3DPointRep;
class CATPolyPointGPMarker;
class CATPolyPointVizMarker;
class CATPolyPointEVizEdge;
class CATPolyPointEVizLine;
class CATPolyPointGPEdge;
class CATPolyPointGPLine;
class CATPolyPointVizEdge;
class CATPolyPointVizLine;
class CATPolyPointEVizUVFace;
class CATPolyPointVizAdapter;

// Other concrete types (Tessellation)
class CATTessPolyPoint;
class CATTessPolyMeshVertex;
class CATTessPolyVertex;


/*
* Base class for visitors of CATIPolyPoint's.
*/
class ExportedByPolyhedralModel CATPolyPointConstVisitor
{

public:

  virtual ~CATPolyPointConstVisitor () {}

public:

  /**
   * Inline method that forwards the request to the point implementation.
   * If it accepts visitors, the point implementation calls back the visit methods 
   * with the concrete types or the default method.
   */
  inline HRESULT Visit (const CATIPolyPoint& iPoint);

public:

  // Calls back the generic implementation of the visitor 
  // (when the concrete type is not supported.)
  virtual HRESULT VisitDefault (const CATIPolyPoint& iPoint) = 0 ;
  //virtual HRESULT VisitDefault (const CATIPolyCurvePoint& iPoint) = 0 ;
  //virtual HRESULT VisitDefault (const CATIPolyMeshPoint& iPoint) = 0 ;
  //virtual HRESULT VisitDefault (const CATIPolyCurveVertex& iPoint) = 0 ;
  //virtual HRESULT VisitDefault (const CATIPolySurfaceVertex& iPoint) = 0 ;

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

  virtual HRESULT VisitConcrete (const CATIPolyPoint& iPoint, const CATPolyPoint&);
  virtual HRESULT VisitConcrete (const CATIPolyCurvePoint& iPoint, const CATPolyCurvePoint&);
  virtual HRESULT VisitConcrete (const CATIPolyMeshPoint& iPoint, const CATPolyMeshPoint&);
  virtual HRESULT VisitConcrete (const CATIPolyCurveVertex& iPCV, const CATPolyCurveVertex&);
  virtual HRESULT VisitConcrete (const CATIPolySurfaceVertex& iPSV, const CATPolySurfaceVertex&);

/** @} */

public:

/** @name Concrete types specific to PolyhedralVisualization framework.
    @{ */

  // TO DO: move to PolyhedralVisualization framework.

  virtual HRESULT VisitConcrete (const CATIPolyPoint& iPoint, const CATPolyPointMeshVertex&);  // PolyhedralVisualization type.

  virtual HRESULT VisitConcrete (const CATIPolyPoint& iPoint, const CATPolyPoint3DPointRep&);
  virtual HRESULT VisitConcrete (const CATIPolyPoint& iPoint, const CATPolyPointGPMarker&);
  virtual HRESULT VisitConcrete (const CATIPolyPoint& iPoint, const CATPolyPointVizMarker&);

  virtual HRESULT VisitConcrete (const CATIPolyPoint& iPoint, const CATPolyPointEVizEdge&);
  virtual HRESULT VisitConcrete (const CATIPolyPoint& iPoint, const CATPolyPointEVizLine&);
  virtual HRESULT VisitConcrete (const CATIPolyPoint& iPoint, const CATPolyPointGPEdge&);
  virtual HRESULT VisitConcrete (const CATIPolyPoint& iPoint, const CATPolyPointGPLine&);
  virtual HRESULT VisitConcrete (const CATIPolyPoint& iPoint, const CATPolyPointVizEdge&);
  virtual HRESULT VisitConcrete (const CATIPolyPoint& iPoint, const CATPolyPointVizLine&);

  virtual HRESULT VisitConcrete (const CATIPolyPoint& iPoint, const CATPolyPointEVizUVFace&);
  virtual HRESULT VisitConcrete (const CATIPolyPoint& iPoint, const CATPolyPointVizAdapter&);

/** @} */

public:

/** @name Concrete types specific to Tessellation framework.
    @{ */

  // TO DO: move to Tessellation framework.

  virtual HRESULT VisitConcrete (const CATIPolyPoint& iPoint, const CATTessPolyPoint&);
  virtual HRESULT VisitConcrete (const CATIPolyPoint& iPoint, const CATTessPolyMeshVertex&);
  virtual HRESULT VisitConcrete (const CATIPolyPoint& iPoint, const CATTessPolyVertex&);

/** @} */

};


inline HRESULT CATPolyPointConstVisitor::Visit (const CATIPolyPoint& iPoint)
{
  return iPoint.Accept (iPoint, *this);
}

#endif // !CATPolyPointConstVisitor_H
