//=============================================================================
// COPYRIGHT Dassault Systemes 2009
//=============================================================================
// CATPolyBoundingSphere.h
//
//=============================================================================
// 2009-01-05   JXO: New
//=============================================================================
#ifndef CATPolyBoundingSphere_H
#define CATPolyBoundingSphere_H

#include "PolyMathBV.h"
#include "CATPolyBoundingVolume.h"
#include "CATPolyPool.h"

#include "CATMathPoint.h"
#include "CATDataType.h"

class ExportedByPolyMathBV CATPolyBoundingSphere
  : public CATPolyBoundingVolume
{
  CATPolyDeclarePooledNew;

public:
  CATPolyBoundingSphere(const CATMathPoint &iCenter, double iRadius):
    _Center(iCenter),
    _Radius(iRadius)
  {}

  CATPolyBoundingSphere() {_Radius = 0.;}

  virtual ~CATPolyBoundingSphere () {}

  TypeID GetTypeID() const; 
  
public:
  inline const CATMathPoint &GetCenter() const { return _Center; }
  inline const double GetRadius() const { return _Radius; }

  inline void Set (const CATMathPoint & center, double radius)
  {
    _Center = center;
    _Radius = radius;
  }

public:

  HRESULT Accept (CATPolyBVConstVisitor& iVisitor) const;

  virtual CATBoolean IsEmpty() const;

protected:
  CATMathPoint _Center;
  double _Radius;

};


#endif // !CATPolyBoundingSphere_H
