// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyPointVisitor.h
//
//===================================================================
// December 2009  Creation: NDO
//===================================================================
#ifndef CATPolyPointVisitor_H
#define CATPolyPointVisitor_H

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


/*
* Base class for visitors of CATIPolyPoint's.
*/
class ExportedByPolyhedralModel CATPolyPointVisitor
{

public:

  virtual ~CATPolyPointVisitor () {}

public:

  // Inline method that forwards the request to the point implementation.
  // If it accepts visitors, the point implementation calls back the visit methods with the concrete types or 
  // the default method.
  inline HRESULT Visit (CATIPolyPoint& iPoint);

public:

  // Calls back the generic implementation of the visitor 
  // (when the concrete type is not supported.)  
  virtual HRESULT VisitDefault (CATIPolyPoint& iPoint) = 0 ;
  //virtual HRESULT VisitDefault (CATIPolyCurveVertex& iPoint) = 0 ;
  //virtual HRESULT VisitDefault (CATIPolySurfaceVertex& iPoint) = 0 ;

public:

/** @name Concrete types specific to PolyhedralObjects framework.
    @{ */

  virtual HRESULT VisitConcrete (CATIPolyPoint& iPoint, CATPolyPoint&);
  virtual HRESULT VisitConcrete (CATIPolyCurvePoint& iCP, CATPolyCurvePoint&);
  virtual HRESULT VisitConcrete (CATIPolyMeshPoint& iMP, CATPolyMeshPoint&);
  virtual HRESULT VisitConcrete (CATIPolyCurveVertex& iCV, CATPolyCurveVertex&);
  virtual HRESULT VisitConcrete (CATIPolySurfaceVertex& iSV, CATPolySurfaceVertex&);

/** @} */

};

inline HRESULT CATPolyPointVisitor::Visit (CATIPolyPoint& iPoint)
{
  return iPoint.Accept (iPoint, *this);
}

#endif // !CATPolyPointVisitor_H
