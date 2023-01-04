// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBVClone.h
//
//===================================================================
//
// Dec 2009  Creation: JXO
//===================================================================
#ifndef CATPolyBVClone_H
#define CATPolyBVClone_H

#include "CATErrorDef.h"  // Definition of HRESULT.
#include "CATPolyBoundingVolume.h"
#include "PolyMathBV.h"
#include "CATPolyBVConstVisitor.h"


// Supported concrete types.
class CATPolyBoundingSphere;
class CATPolyAABB;
class CATPolyOBB;
class CATPolyBoundingPlane;
class CATPolyBoundingCylinder;

/*
  Clone a CATPolyBoundingVolume if you don't know input one.
 */
class ExportedByPolyMathBV CATPolyBVClone : public CATPolyBVConstVisitor
{
public:
  static CATPolyBoundingVolume * Clone(const CATPolyBoundingVolume * iBV);


protected:
  CATPolyBVClone():_pBV(NULL){}
  ~CATPolyBVClone(){_pBV=NULL;}

public:
  virtual HRESULT VisitConcrete (const CATPolyBoundingSphere& iBV);
  virtual HRESULT VisitConcrete (const CATPolyAABB& iBV);
  virtual HRESULT VisitConcrete (const CATPolyOBB& iBV);
  virtual HRESULT VisitConcrete (const CATPolyBoundingPlane& iBV);
  virtual HRESULT VisitConcrete (const CATPolyBoundingCylinder& iBV);

private:
  CATPolyBoundingVolume * _pBV;
};

#endif // !CATPolyBVClone_H
