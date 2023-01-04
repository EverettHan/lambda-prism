//=============================================================================
// COPYRIGHT Dassault Systemes 2009
//=============================================================================
// CATPolyOBB.h
// OBB (Oriented Bounding Box) definition for the accelerated structure for 
// the clash operator.
//=============================================================================
// 2009-02-05   JXO/XXC: New
// 2010-03-23   JXO: CATMathOBBBase
//=============================================================================
#ifndef CATPolyOBB_H
#define CATPolyOBB_H

#include "PolyMathBV.h"
#include "CATPolyBoundingVolume.h"
#include "CATPolyPool.h"

#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMathTransformation.h"
#include "CATMathBox.h"
#include "CATMathOBBBase.h"
#include "CATMathVectorf.h"
#include "CATMathPointf.h"
#include "CATPolyBoxf.h"


class ExportedByPolyMathBV CATPolyOBB
  : public CATPolyBoundingVolume
{
  CATPolyDeclarePooledNew;

public:
  enum OBBOverlap
    {
      Separate,
      Overlap
    };

public:
  CATPolyOBB();
  ~CATPolyOBB();
/**
 * Copy constructor
 */
  inline CATPolyOBB (const CATPolyOBB & iOBBToCopy);
/**
 * Useful constructors
 */
  inline CATPolyOBB (const CATMathOBBBase & iBoxToCopy);
  inline CATPolyOBB (const CATMathBox & iBoxToCopy);
  inline CATPolyOBB (const CATPolyBoxf & iBoxToCopy);
  /**
   * @param Basis orthonormal basis representing the three directions of the OBB.
   * @param Diag half of the OBB diagonal in the Basis
   * @param C center of the OBB.
   */
  inline CATPolyOBB (CATMathVector Basis[3], CATMathVector & Diag, CATMathPoint & C);

  TypeID GetTypeID() const; 
  
  inline CATBoolean IsDefined() const;

  inline CATMathVector U() const;
  inline CATMathVector V() const;
  inline CATMathVector W() const;

  inline CATMathPoint Center() const;
  inline CATMathVector Diagonal() const;

  inline CATMathPoint UVWtoXYZ(const CATMathPoint & iLocalPoint) const;
  inline CATMathPoint XYZtoUVW(const CATMathPoint & iGlobalPoint) const;

  OBBOverlap Test(const CATPolyOBB & iOBB) const;
  double SquareDistanceMin(const CATMathPoint & iPoint) const;
  double SquareDistanceMax(const CATMathPoint & iPoint) const;
  CATBoolean SquareDistanceMinDir(const CATMathPoint & iCenter, const double iRadius,
                                  const CATMathVector & iDirection, double & oDistance) const;
  double SquareDistanceMin(const CATPolyOBB & iOBB) const;
  double SquareDistanceMax(const CATPolyOBB & iOBB) const;
  CATBoolean SquareDistanceMinDir(const CATPolyOBB & iOBB,
                                  const CATMathVector & iDirection, double & oDistance) const;

  inline CATBoolean IsContaining(const CATMathPoint & point) const;

  // Transformation
  inline friend CATPolyOBB operator * (const CATMathTransformation & iTransfo, const CATPolyOBB & iOBB);
  CATPolyOBB operator = (const CATPolyOBB & iOBBToCopy)
  {
    _obb = iOBBToCopy._obb;
    return (*this);
  }
  CATMathBox GetAABB() const;
  HRESULT ConvertToBoxAndTransformation(CATMathBox & obox, CATMathTransformation & otransfo) const;
  HRESULT Absorb (const CATPolyOBB & iobb);
  void Inflate(double iTol);

public:

  HRESULT Accept (CATPolyBVConstVisitor& iVisitor) const;

  inline CATMathOBBBase & GetBase() {return _obb;}
  inline const CATMathOBBBase & GetBase() const {return _obb;}

  virtual CATBoolean IsEmpty() const;


protected:
  CATMathOBBBase _obb;
};

// _____________________________________________________________________________
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// Inline methods implementation.
// _____________________________________________________________________________
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯

inline CATBoolean CATPolyOBB::IsDefined() const
{
  return _obb.IsDefined();
}

inline CATMathVector CATPolyOBB::U() const
{
#ifdef CATMATHOBBBASE_DOUBLEMIGRATION
   return _obb.UDir();
#else
  CATMathVectorf uu = _obb.U();
  return CATMathVector(uu.x, uu.y, uu.z);
#endif
}
inline CATMathVector CATPolyOBB::V() const
{
#ifdef CATMATHOBBBASE_DOUBLEMIGRATION
   return _obb.VDir();
#else
  CATMathVectorf vv = _obb.V();
  return CATMathVector(vv.x, vv.y, vv.z);
#endif
}
inline CATMathVector CATPolyOBB::W() const
{
#ifdef CATMATHOBBBASE_DOUBLEMIGRATION
   return _obb.WDir();
#else
  CATMathVectorf ww = _obb.W();
  return CATMathVector(ww.x, ww.y, ww.z);
#endif
}

inline CATMathPoint CATPolyOBB::Center() const
{
#ifdef CATMATHOBBBASE_DOUBLEMIGRATION
   return _obb.CenterPoint();
#else
  CATMathPointf ww = _obb.Center();
  return CATMathPoint(ww.x, ww.y, ww.z);
#endif
}

inline CATMathVector CATPolyOBB::Diagonal() const
{
#ifdef CATMATHOBBBASE_DOUBLEMIGRATION
   return _obb.BoxDiagonal();
#else
  CATMathVectorf ww = _obb.Diagonal();
  return CATMathVector(ww.x, ww.y, ww.z);
#endif
}

inline CATMathPoint CATPolyOBB::UVWtoXYZ(const CATMathPoint & iLocalPoint) const
{
  return _obb.UVWtoXYZ(iLocalPoint);
}

inline CATMathPoint CATPolyOBB::XYZtoUVW(const CATMathPoint & iGlobalPoint) const
{
  return _obb.XYZtoUVW(iGlobalPoint);
}

inline CATPolyOBB::CATPolyOBB(const CATPolyOBB & iOBBToCopy):
_obb(iOBBToCopy._obb)
{
}

inline CATPolyOBB::CATPolyOBB (const CATMathOBBBase & iBoxToCopy):
_obb(iBoxToCopy)
{
}
inline CATPolyOBB::CATPolyOBB (const CATMathBox & iBoxToCopy):
_obb(iBoxToCopy)
{
}
inline CATPolyOBB::CATPolyOBB (const CATPolyBoxf & iBoxToCopy):
_obb(iBoxToCopy.GetMathBox())
{
}
inline CATPolyOBB::CATPolyOBB(CATMathVector Basis[], CATMathVector & Diag, CATMathPoint & C):
_obb(Basis, Diag, C)
{  
}

inline CATBoolean CATPolyOBB::IsContaining(const CATMathPoint & point) const
{
  return (1 == _obb.IsContaining(point, 0.0));
}

// Transformation
inline CATPolyOBB operator * (const CATMathTransformation & iTransfo, const CATPolyOBB & iOBB)
{
  CATPolyOBB Box(iTransfo * iOBB._obb);
  return Box;
}

#endif // !CATPolyOBB_H
