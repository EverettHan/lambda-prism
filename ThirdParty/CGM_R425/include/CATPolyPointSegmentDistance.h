//=============================================================================
// COPYRIGHT Dassault Systemes 2006, 2007
//=============================================================================
//
// CATPolyPointSegmentDistance.h
//
// Compute the distance between a 3D point and a segment define by two 3D
// points.
//
//=============================================================================
// 2007-06-15 BPG: Rename from CATDistanceVertexSegment. Introduce Result.
//
// 2006-07-31 CHU: New. Integrate in vertex/triangle to handle degenerated
// triangles.
// =============================================================================
#ifndef CATPolyPointSegmentDistance_H
#define CATPolyPointSegmentDistance_H

#include "PolyMathIntersectors.h"

#include "CATErrorDef.h"
#include "CATBoolean.h"

class CATMathPoint;

class ExportedByPolyMathIntersectors CATPolyPointSegmentDistance
{
public:
  class Result
  {
  public:
    enum Location
      {
        Inside,

        Vertex0,
        Vertex1,

        Invalid
      };

  public:
    inline Result();

  public:
    inline double GetSquareDistance() const;

    inline Location GetLocation() const;

    inline double GetLambda() const;

    inline CATBoolean DegeneratedSegmentP() const;

  protected:
    friend class CATPolyPointSegmentDistance;

  protected:
    double _Lambda;
    double _SquareDistance;
    Location _Location;
    CATBoolean _DegeneratedSegmentP;
  };

public:
  inline CATPolyPointSegmentDistance(double iResolutionForLengthTest);

  // if the segment is degenerated (length < resolution), the closest point is
  // set equal to the first point, and the degeneracy information is given in
  // output. oLambda is such that AH = oLambda AB if H is the solution
public:
  HRESULT Run(const CATMathPoint &iM,
              const CATMathPoint &iA, const CATMathPoint &iB,
              Result &oResult) const;

protected:
  const double _SquareResolutionForLengthTest;
};

// ----------------------------------------------------------------------------

inline
CATPolyPointSegmentDistance::CATPolyPointSegmentDistance(double iResolutionForLengthTest):
  _SquareResolutionForLengthTest(iResolutionForLengthTest * iResolutionForLengthTest)
{}

inline
CATPolyPointSegmentDistance::Result::Result():
  _SquareDistance(-1.0),
  _Location(Invalid),
  _Lambda(2.0)
{}

inline double
CATPolyPointSegmentDistance::Result::GetSquareDistance() const
{
  return _SquareDistance;
}

inline CATPolyPointSegmentDistance::Result::Location
CATPolyPointSegmentDistance::Result::GetLocation() const
{
  return _Location;
}

inline double
CATPolyPointSegmentDistance::Result::GetLambda() const
{
  return _Lambda;
}

inline CATBoolean
CATPolyPointSegmentDistance::Result::DegeneratedSegmentP() const
{
  return _DegeneratedSegmentP;
}

#endif // !CATPolyPointSegmentDistance_H
