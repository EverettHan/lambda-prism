//=============================================================================
// COPYRIGHT Dassault Systemes 2009
//=============================================================================
//
// CATPolyRayAABBIntersector.h
//
// Compute the intersection between a 3D ray and a AABB define by CATMathBox
//
//=============================================================================
// 2009-03-12   MPX: New.
//=============================================================================
#ifndef CATPolyRayAABBIntersector_H
#define CATPolyRayAABBIntersector_H

#include "CATErrorDef.h"
#include "CATBoolean.h"

//
class CATMathPoint;
class CATMathDirection;
class CATMathBox;

#include "PolyMathRay.h"

class ExportedByPolyMathRay CATPolyRayAABBIntersector
{
public:
  class Result
  {
  public:
    inline Result();
    inline Result(
              CATBoolean iIsIntersecting,
              double iDistanceFromRayOrigin);

    inline Result &operator=(const Result &iRHS);

  public:
    inline CATBoolean IsIntersecting() const;

    // Returns the distance at which the ray enters the box.
    // Returns zero if the ray starts from inside the box.
    inline double GetDistanceFromRayOrigin() const;

  protected:
    CATBoolean _IsIntersecting;
    double _DistanceFromRayOrigin;

    friend class CATPolyRayAABBIntersector;
  };

public:
  /**
   *
   * @param iEpsilonForLengthTest
   * the value below which a geometrical distance is said to be 0
   */
  inline CATPolyRayAABBIntersector(double iEpsilonForLengthTest, double iModelSize);

public:
  /**
     @param iOrigin ray's origin
     @param iDirection ray's direction. WARNING: this vector shall have been normalized.
     @return S_OK on success, E_FAIL on failure
   */
  HRESULT Run(const CATMathPoint &iOrigin, 
              const CATMathDirection &iDirection,
              const CATMathBox &iBox,
              Result &oResult) const;

protected:
  const double _EpsilonForLengthTest;
  const double _ModelSize;
  const double _EpsilonForDerivativeTest;
};

// ----------------------------------------------------------------------------

inline
CATPolyRayAABBIntersector::CATPolyRayAABBIntersector(double iEpsilonForLengthTest, double iModelSize):
  _EpsilonForLengthTest(iEpsilonForLengthTest), _ModelSize(iModelSize), 
  _EpsilonForDerivativeTest(iModelSize > iEpsilonForLengthTest ? (iEpsilonForLengthTest/iModelSize) : iEpsilonForLengthTest)
{
}

//
inline
CATPolyRayAABBIntersector::Result::Result():
  _IsIntersecting(0),
  _DistanceFromRayOrigin(-1.0)
{}

inline
CATPolyRayAABBIntersector::Result::Result(
              CATBoolean iIsIntersecting,
              double iDistanceFromRayOrigin):
  _IsIntersecting(iIsIntersecting),
  _DistanceFromRayOrigin(iDistanceFromRayOrigin)
{}

inline CATPolyRayAABBIntersector::Result &
CATPolyRayAABBIntersector::Result::operator=(const CATPolyRayAABBIntersector::Result &iRHS)
{
  _IsIntersecting = iRHS._IsIntersecting;
  _DistanceFromRayOrigin = iRHS._DistanceFromRayOrigin;
  return *this;
}

//

inline CATBoolean
CATPolyRayAABBIntersector::Result::IsIntersecting() const
{
  return _IsIntersecting;
}

inline double
CATPolyRayAABBIntersector::Result::GetDistanceFromRayOrigin() const
{
 return _DistanceFromRayOrigin;
}

#endif // !CATPolyRayAABBIntersector_H
