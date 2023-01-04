// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBVConstVisitor.h
//
//===================================================================
//
// April 2009  Creation: NDO
//===================================================================
#ifndef CATPolyBVConstVisitor_H
#define CATPolyBVConstVisitor_H

#include "CATErrorDef.h"  // Definition of HRESULT.
#include "CATPolyBoundingVolume.h"
#include "PolyMathBV.h"

// Supported concrete types.
class CATPolyBoundingSphere;
class CATPolyAABB;
class CATPolyOBB;
class CATPolyBoundingPlane;
class CATPolyBoundingCylinder;
/*
Visitor for CATPolyBoundingVolume.
A class deriving from CATPolyBVConstVisitor can implement specific implementations for each of the 
supported concrete types.
An instance of this class will get a callback with an object of the concrete type.
*/
class ExportedByPolyMathBV CATPolyBVConstVisitor
{

public:

  virtual ~CATPolyBVConstVisitor () {}

public:

  inline HRESULT Visit (const CATPolyBoundingVolume& iBV);

public:

  virtual HRESULT VisitConcrete (const CATPolyBoundingSphere& iBV) = 0;
  virtual HRESULT VisitConcrete (const CATPolyAABB& iBV) = 0;
  virtual HRESULT VisitConcrete (const CATPolyOBB& iBV) = 0;
  virtual HRESULT VisitConcrete (const CATPolyBoundingPlane& iBV) = 0;
  virtual HRESULT VisitConcrete (const CATPolyBoundingCylinder& iBV) = 0;
};

inline HRESULT CATPolyBVConstVisitor::Visit (const CATPolyBoundingVolume& iBV)
{
  return iBV.Accept (*this);
}

#endif // !CATPolyBVConstVisitor_H
