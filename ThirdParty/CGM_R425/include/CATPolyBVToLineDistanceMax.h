// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBVToLineDistanceMax.h
//   Finds max distance of a BV from a given line
//===================================================================
//
// August 2013  Creation: MPX
//===================================================================
#ifndef CATPolyBVToLineDistanceMax_H
#define CATPolyBVToLineDistanceMax_H

#include "PolyMathBV.h"
#include "CATPolyBVConstVisitor.h"
#include "CATMathLine.h"

class CATPolyBoundingSphere;
class CATPolyAABB;
class CATPolyOBB;
class CATMathBox;

class ExportedByPolyMathBV CATPolyBVToLineDistanceMax: public CATPolyBVConstVisitor
{
public:
  inline CATPolyBVToLineDistanceMax();
  
  // returns the max square distance of the given BV from the given line
  HRESULT GetMaxSquareDistance(const CATPolyBoundingVolume& iBV, const CATMathLine& iLine, double& oMaxSquareDistance);

private:
  HRESULT VisitConcrete (const CATPolyBoundingSphere& iBV);
  HRESULT VisitConcrete (const CATPolyAABB& iBV);
  HRESULT VisitConcrete (const CATPolyOBB& iBV);

  // not implemented
  HRESULT VisitConcrete (const CATPolyBoundingPlane& iBV);
  HRESULT VisitConcrete (const CATPolyBoundingCylinder& iBV);

private:
  const CATMathLine* _Line;
  double _MaxSquareDistance;
};

inline CATPolyBVToLineDistanceMax::CATPolyBVToLineDistanceMax()
: _Line(0), _MaxSquareDistance(0.0) 
{
}

#endif // !CATPolyBVToLineDistanceMax_H
