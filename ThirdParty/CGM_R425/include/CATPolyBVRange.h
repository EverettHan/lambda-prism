// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBVRange.h
//
//===================================================================
//
// May 2009  Creation: NDO
//===================================================================
#ifndef CATPolyBVRange_H
#define CATPolyBVRange_H

#include "PolyMathBV.h"
#include "CATErrorDef.h"

#include "CATPolyBVConstVisitor.h"

class CATPolyBoundingVolume;
class CATMathTransformation;
class CATPolyBoundingSphere;
class CATPolyBoundingPlane;
class CATPolyAABB;
class CATPolyOBB;
class CATPolyBoundingCylinder;


/**
 * This operator computes the range of a bounding volume with an arbitrary positions.
 * The range is defined as the minimum and maximum coordinates of any point in the bounding volume.
 */
class ExportedByPolyMathBV CATPolyBVRange : private CATPolyBVConstVisitor
{

public:

  CATPolyBVRange (const CATPolyBoundingVolume& iBV, const CATMathTransformation* iBVPosition = 0);

  ~CATPolyBVRange () {}

public:

  inline double MinLimit () const;
  inline double MaxLimit () const;

private:

  const CATPolyBoundingVolume& _BV;
  const CATMathTransformation* _BVPosition;

  double _MinLimit;
  double _MaxLimit;

private:

  HRESULT VisitConcrete (const CATPolyBoundingSphere& iBV);
  HRESULT VisitConcrete (const CATPolyBoundingPlane& iPlane);
  HRESULT VisitConcrete (const CATPolyAABB& iBV);
  HRESULT VisitConcrete (const CATPolyOBB& iBV);
  HRESULT VisitConcrete (const CATPolyBoundingCylinder& iBV);

};

inline double CATPolyBVRange::MinLimit () const
{
  return _MinLimit;
}

inline double CATPolyBVRange::MaxLimit () const
{
  return _MaxLimit;
}

#endif // !CATPolyBVRange_H
