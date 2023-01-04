// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathCircleCurve.h
//
//===================================================================
// Nov 2009  Creation: zfi
//===================================================================
#ifndef CATPolyMathCircleCurve_H
#define CATPolyMathCircleCurve_H

#include "PolyMathCurves.h"
#include "CATPolyMathCurve.h"

#include "CATErrorDef.h"
#include "CATPolyMathObject.h"

#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMathLimits.h"

class CATPolyMathCurveConstVisitor;
class CATPolyMathCurveVisitor;


/**
 * Describe your class here.
 */
class ExportedByPolyMathCurves CATPolyMathCircleCurve : public CATPolyMathCurve
{

public:

  CATPolyMathCircleCurve ();
  CATPolyMathCircleCurve (const CATMathPoint& iOrigin, const CATMathVector& iAxis, const double iRadius);
  virtual ~CATPolyMathCircleCurve ();

public:
  //SPECIFIC
  inline const CATMathPoint& GetOrigin () const;
  inline const CATMathVector& GetAxis () const;
  inline double GetRadius () const;

  //Axis
  inline void SetBaseAxis(const CATMathVector& iU,
                          const CATMathVector& iV);

  /**
   * Returns true if the base axis were set.
   */
  inline bool AreBaseAxisSet () const;

  inline const CATMathVector& GetU()const;
  inline const CATMathVector& GetV()const;
  inline const CATMathVector& GetW()const;

  //INHERITED
public:
  Type GetType () const; 
  const CATPolyMathCircleCurve* CastAsCircle()const;
  CATPolyMathCircleCurve* CastAsCircle();
  CATPolyMathCurve * Clone () const;  
  void GetLimits(double &tmin,double &tmax) const;

public:
  void GetPoint (const unsigned int vertex, CATMathPoint& oPoint) const;

public:
  void Evaluate (const double t, CATMathPoint& oPoint) const;
  void EvaluateDerivative (const double t, double odPdt[]) const;
  void EvaluateSecondDerivative(const double t, double odDdt[])const;
  
  double GetMaxSecondDerivative()const;

public:
  HRESULT Accept (CATPolyMathCurveConstVisitor &iV) const;
  HRESULT Accept (CATPolyMathCurveVisitor &iV);

private:
  CATMathPoint _Origin;
  CATMathVector _U,_V,_W;
  double _Radius;
};

//INLINE
inline const CATMathPoint& CATPolyMathCircleCurve::GetOrigin () const
{
  return _Origin;
}

inline const CATMathVector& CATPolyMathCircleCurve::GetAxis () const
{
  return _W;
}

inline double CATPolyMathCircleCurve::GetRadius () const
{
  return _Radius;
}

inline void CATPolyMathCircleCurve::SetBaseAxis(const CATMathVector& iU,
                                                const CATMathVector& iV)
{
  _U=iU;
  _V=iV;
}

inline bool CATPolyMathCircleCurve::AreBaseAxisSet () const
{
  return _U.GetZ () != CATdoubleMax;
}

inline const CATMathVector& CATPolyMathCircleCurve::GetU()const
{
  return _U;
}

inline const CATMathVector& CATPolyMathCircleCurve::GetV()const
{
  return _V;
}

inline const CATMathVector& CATPolyMathCircleCurve::GetW()const
{
  return _W;
}
#endif
