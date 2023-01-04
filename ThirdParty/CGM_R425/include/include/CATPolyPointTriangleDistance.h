//=============================================================================
// COPYRIGHT Dassault Systemes 2005, 2007
//=============================================================================
//
// CATPolyPointTriangleDistance.h
//
// Compute the distance between a 3D point and a triangle define by three 3D
// points.
//
//=============================================================================
// 2007-06-15   BPG: Rename from CATDistanceVertexTriangle.
// 2005-09-23   BPG: New.
//=============================================================================
#ifndef CATPolyPointTriangleDistance_H
#define CATPolyPointTriangleDistance_H

#include "CATErrorDef.h"

#include "PolyMathIntersectors.h"

class CATMathPoint;

class ExportedByPolyMathIntersectors CATPolyPointTriangleDistance
{
public:
  class Result
  {
  public:
    enum Location
      {
        Inside,

        Edge01,
        Edge12,
        Edge02,

        Vertex0,
        Vertex1,
        Vertex2,

        Invalid
      };

  public:
    inline Result();
    inline Result(double SquareDistance, Location L, double W0, double W1, double W2);

    inline Result &operator=(const Result &iRHS);

    inline void Invalidate ();

  public:
    inline double GetSquareDistance() const;

    inline Location GetLocation() const;

    inline double GetW0() const;
    inline double GetW1() const;
    inline double GetW2() const;

  protected:
    double _SquareDistance;

    Location _Location;

    double _W0;
    double _W1;
    double _W2;
  };

public:
  /**
   * @param iEpsilonForLengthTest
   * the value below which a dot product is said to be 0
   *
   * @param iResolutionForLengthTest
   * the value below which a geometrical distance is said to be 0
   */
  inline CATPolyPointTriangleDistance(double iResolutionForLengthTest, double iEpsilonForLengthTest);

public:
  /**
   * @return S_OK on success, E_FAIL on failure
   *
   * The result holds the barycentric coordinates of the nearest point P:
   * P = iV0 * oResult.GetW0() + iV1 * oResult.GetW1() + iV2 * oResult.GetW2())
   */
  HRESULT Run(const CATMathPoint &iM,
              const CATMathPoint &iV0, const CATMathPoint &iV1, const CATMathPoint &iV2,
              Result &oResult) const;

protected:
  HRESULT Run(const CATMathPoint &iM,
              const CATMathPoint &iV0, const CATMathPoint &iV1, const CATMathPoint &iV2,
              double &oW1, double &oW2, double &oSquareDistance, Result::Location &oLocation) const;

protected:
  const double _ResolutionForLengthTest;
  const double _EpsilonForLengthTest;
};

// ----------------------------------------------------------------------------

inline
CATPolyPointTriangleDistance::CATPolyPointTriangleDistance(double iResolutionForLengthTest, double iEpsilonForLengthTest):
  _ResolutionForLengthTest(iResolutionForLengthTest),
  _EpsilonForLengthTest(iEpsilonForLengthTest)
{}

//

inline
CATPolyPointTriangleDistance::Result::Result():
  _SquareDistance(-1.0), _Location(Invalid), _W0(2), _W1(2), _W2(2)
{}

inline void CATPolyPointTriangleDistance::Result::Invalidate ()
{
  _SquareDistance = -1.0;
  _Location = Invalid;
}

inline
CATPolyPointTriangleDistance::Result::Result(double SquareDistance, Location L, double W0, double W1, double W2):
  _SquareDistance(SquareDistance),
  _Location(L),
  _W0(W0), _W1(W1), _W2(W2)
{}

inline CATPolyPointTriangleDistance::Result &
CATPolyPointTriangleDistance::Result::operator=(const CATPolyPointTriangleDistance::Result &iRHS)
{
  _SquareDistance = iRHS._SquareDistance;
  _Location = iRHS._Location;
  _W0 = iRHS._W0;
  _W1 = iRHS._W1;
  _W2 = iRHS._W2;
  return *this;
}

//

inline double
CATPolyPointTriangleDistance::Result::GetSquareDistance() const
{
  return _SquareDistance;
}

inline CATPolyPointTriangleDistance::Result::Location
CATPolyPointTriangleDistance::Result::GetLocation() const
{
  return _Location;
}

inline double
CATPolyPointTriangleDistance::Result::GetW0() const
{
 return _W0;
}

inline double
CATPolyPointTriangleDistance::Result::GetW1() const
{
 return _W1;
}

inline double
CATPolyPointTriangleDistance::Result::GetW2() const
{
 return _W2;
}

#endif // !CATPolyPointTriangleDistance_H
