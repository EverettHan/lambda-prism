//=============================================================================
// COPYRIGHT Dassault Systemes 2009
//=============================================================================
// CATPolyBoundingPlane.h
// Bounding Plane definition for the accelerated structure for 
// the clash operator. Equicvalent to a plane with a thickness.
//=============================================================================
// 2010-01-29   XXC: New
//=============================================================================
#ifndef CATPolyBoundingPlane_H
#define CATPolyBoundingPlane_H

#include "PolyMathBV.h"
#include "CATPolyBoundingVolume.h"
#include "CATPolyPool.h"

#include "CATMathTransformation.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMath.h"

class ExportedByPolyMathBV CATPolyBoundingPlane
  : public CATPolyBoundingVolume
{
  CATPolyDeclarePooledNew;

public:
  /** Default constructor. By default, it is the plane xOy with a
   *  thickness equal to 0.01
   */
  CATPolyBoundingPlane();
  ~CATPolyBoundingPlane();
  CATPolyBoundingPlane (const CATPolyBoundingPlane & iBPToCopy);
  /**
   * @param iNormal: normal to the plane
   * @param iOrigin: Origin of the plane. Can be any point on the plane
   * @param iThickness: The plane thickness.
   */
  CATPolyBoundingPlane (const CATMathVector & iNormal, const CATMathPoint & iOrigin, const double iThickness = 0.01);

  inline TypeID GetTypeID() const {return /*CATPolyBoundingVolume::*/PlaneType;}
  
  inline const CATMathVector & GetNormal() const;
  inline void SetNormal(const CATMathVector & iNormal);

  inline const CATMathPoint & GetOrigin() const;
  inline void SetOrigin(const CATMathPoint & iOrigin);

  inline double GetThickness() const;
  inline void SetThickness(const double iThickness);

  inline CATBoolean IsInfinitelyThick() const;
  inline void SetInfinitelyThick(CATBoolean iInfinite);

  /** Plane equation such that a point (x,y,z) is in the plane if and
   *  ony if (ax + by + cz + d = 0)
   */
  inline void GetEquation(double & a, double & b, double & c, double & d);

  double SquareDistanceTo(const CATMathPoint & iPoint) const;
  double DistanceTo(const CATMathPoint & iPoint) const;

  // Transformation
  friend ExportedByPolyMathBV CATPolyBoundingPlane operator * (const CATMathTransformation & iTransfo, const CATPolyBoundingPlane & iOBB);
  inline const CATPolyBoundingPlane operator = (const CATPolyBoundingPlane & iOBBToCopy);

  inline void Inflate(double iTol);

public:

  HRESULT Accept (CATPolyBVConstVisitor& iVisitor) const;

  virtual CATBoolean IsEmpty() const;

protected:
  CATMathVector _Normal;
  CATMathPoint _Origin;
  double _Thickness;
  CATBoolean _InfiniteThickness;
};

// _____________________________________________________________________________
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// Inline methods implementation.
// _____________________________________________________________________________
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯

ExportedByPolyMathBV CATPolyBoundingPlane operator * (const CATMathTransformation & iTransfo, const CATPolyBoundingPlane & iPlane);

const CATPolyBoundingPlane CATPolyBoundingPlane::operator = (const CATPolyBoundingPlane & iOBBToCopy)
{
  _Origin = iOBBToCopy._Origin;
  _Normal = iOBBToCopy._Normal;
  _Thickness = iOBBToCopy._Thickness;
  _InfiniteThickness = iOBBToCopy._InfiniteThickness;
  return (*this);
}

inline const CATMathVector & CATPolyBoundingPlane::GetNormal() const
{
  return _Normal;
}

inline void CATPolyBoundingPlane::SetNormal(const CATMathVector & iNormal)
{
  _Normal = iNormal;
  _Normal.Normalize();
}

inline const CATMathPoint & CATPolyBoundingPlane::GetOrigin() const
{
  return _Origin;
}

inline void CATPolyBoundingPlane::SetOrigin(const CATMathPoint & iOrigin)
{
  _Origin = iOrigin;
}

inline double CATPolyBoundingPlane::GetThickness() const
{
  return _Thickness;
}

inline void CATPolyBoundingPlane::SetThickness(const double iThickness)
{
  _Thickness = CATFabs(iThickness);
}

inline CATBoolean CATPolyBoundingPlane::IsInfinitelyThick() const
{
  return _InfiniteThickness;
}

inline void CATPolyBoundingPlane::SetInfinitelyThick(CATBoolean iInfinite)
{
  _InfiniteThickness = iInfinite;
}

/** Plane equation such that a point (x,y,z) is in the plane if and
 *  ony if (ax + by + cz + d = 0)
 */
inline void CATPolyBoundingPlane::GetEquation(double & a, double & b, double & c, double & d)
{
  a = _Normal.GetX();
  b = _Normal.GetY();
  c = _Normal.GetZ();
  d = - (_Origin.GetX()*_Normal.GetX() +
         _Origin.GetY()*_Normal.GetY() +
         _Origin.GetZ()*_Normal.GetZ());
}

inline void CATPolyBoundingPlane::Inflate(double iTol)
{
  _Thickness += iTol;
  if (_Thickness < 0.0)
    _Thickness = 0.0;
}

#endif // !CATPolyBoundingPlane_H
