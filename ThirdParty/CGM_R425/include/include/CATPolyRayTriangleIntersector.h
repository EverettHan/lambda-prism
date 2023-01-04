//=============================================================================
// COPYRIGHT Dassault Systemes 2005, 2007
//=============================================================================
//
// CATPolyRayTriangleIntersector.h
//
// Compute the intersection between a 3D ray and a triangle define by three 3D
// points.
//
//=============================================================================
// 2007-07-02   BPG: New.
//=============================================================================
#ifndef CATPolyRayTriangleIntersector_H
#define CATPolyRayTriangleIntersector_H

#include "CATErrorDef.h"
#include "CATBoolean.h"

//
class CATMathPoint;
class CATMathVector;

#ifndef NULL
#define NULL 0
#endif

//
#include "PolyMathRay.h"

class ExportedByPolyMathRay CATPolyRayTriangleIntersector
{
public:
  class Result
  {
  public:
    inline Result();
    inline Result(double Length,
                  double W0, double W1, double W2);

    inline Result &operator=(const Result &iRHS);

  public:
    inline double GetLength() const;

  public:
    inline double GetW0() const;
    inline double GetW1() const;
    inline double GetW2() const;

  protected:
    double _Length;

  protected:
    double _W0;
    double _W1;
    double _W2;
  };

public:
  /**
   *
   * @param iResolutionForLengthTest
   * the value below which a geometrical distance is said to be 0
   */
  inline CATPolyRayTriangleIntersector(double iEpsilonForLengthTest);

public:
  /**
     @param iOrigin ray's origin

     @param iDirection ray's direction. WARNING: this vector shall have been normalized.

     @param oRayParallelToTrianglePlane On S_FALSE, if oParallel is not NULL, it tells whether ray is parallel to triangle plane

     @return S_OK on success, E_FAIL on failure
   */
  HRESULT Run(const CATMathPoint &iOrigin, const CATMathVector &iDirection,
              const CATMathPoint &iV0, const CATMathPoint &iV1, const CATMathPoint &iV2,
              Result &oResult, CATBoolean* oIsRayParallelToTrianglePlane = NULL) const;

protected:
  const double _EpsilonForLengthTest;
};

// ----------------------------------------------------------------------------

inline
CATPolyRayTriangleIntersector::CATPolyRayTriangleIntersector(double iEpsilonForLengthTest):
  _EpsilonForLengthTest(iEpsilonForLengthTest)
{}

//
inline
CATPolyRayTriangleIntersector::Result::Result():
  _Length(0.0), _W0(2), _W1(2), _W2(2)
{}

inline
CATPolyRayTriangleIntersector::Result::Result(double iLength, double W0, double W1, double W2):
  _Length(iLength),
  _W0(W0), _W1(W1), _W2(W2)
{}

inline CATPolyRayTriangleIntersector::Result &
CATPolyRayTriangleIntersector::Result::operator=(const CATPolyRayTriangleIntersector::Result &iRHS)
{
  _Length = iRHS._Length;
  _W0 = iRHS._W0;
  _W1 = iRHS._W1;
  _W2 = iRHS._W2;
  return *this;
}

//

inline double
CATPolyRayTriangleIntersector::Result::GetLength() const
{
  return _Length;
}

inline double
CATPolyRayTriangleIntersector::Result::GetW0() const
{
 return _W0;
}

inline double
CATPolyRayTriangleIntersector::Result::GetW1() const
{
 return _W1;
}

inline double
CATPolyRayTriangleIntersector::Result::GetW2() const
{
 return _W2;
}

#endif // !CATPolyRayTriangleIntersector_H
