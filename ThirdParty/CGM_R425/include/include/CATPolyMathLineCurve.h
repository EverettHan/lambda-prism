// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathLineCurve.h
//
//===================================================================
// Nov 2009  Creation: zfi
//===================================================================

#ifndef CATPolyMathLineCurve_H
#define CATPolyMathLineCurve_H

#include "PolyMathCurves.h"
#include "CATPolyMathCurve.h"

#include "CATErrorDef.h"
#include "CATPolyMathObject.h"

#include "CATMathPoint.h"
#include "CATMathVector.h"

class CATPolyMathCurveConstVisitor;
class CATPolyMathCurveVisitor;


/**
 * Describe your class here.
 */
class ExportedByPolyMathCurves CATPolyMathLineCurve : public CATPolyMathCurve
{

public:

  CATPolyMathLineCurve ();
  CATPolyMathLineCurve (const CATMathPoint& iPoint1, const CATMathPoint& iPoint2);
  CATPolyMathLineCurve (double iPoint1[3], double iPoint2[3]);
  virtual ~CATPolyMathLineCurve ();

  CATPolyMathLineCurve* Clone () const /*override*/;

  //SPECIFIC
public:
  inline const CATMathPoint& GetPoint1 () const;
  inline const CATMathPoint& GetPoint2 () const;

  //INHERITED
public:
  Type GetType () const; 
  const CATPolyMathLineCurve* CastAsLine()const;
  CATPolyMathLineCurve* CastAsLine();
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
  CATMathPoint _Point1, _Point2;
};


//INLINE
inline const CATMathPoint& CATPolyMathLineCurve::GetPoint1 () const
{
  return _Point1;
}

inline const CATMathPoint& CATPolyMathLineCurve::GetPoint2 () const
{
  return _Point2;
}

#endif
