// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathPolyLineCurve.h
// Header definition of CATPolyMathPolyLineCurve
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// Nov 2009  Creation: xcz
//===================================================================

#ifndef CATPolyMathPolyLineCurve_H
#define CATPolyMathPolyLineCurve_H

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
class ExportedByPolyMathCurves CATPolyMathPolyLineCurve : public CATPolyMathCurve
{

public:

  CATPolyMathPolyLineCurve (CATMathPoint *iPointsArray,int iNbPoints);
  virtual ~CATPolyMathPolyLineCurve ();

  //SPECIFIC
public:
  inline const HRESULT GetPointByInd(int indPoint,CATMathPoint &oPoint) const;
  inline int GetNbPoints() const;


  //INHERITED
public:
  virtual Type GetType () const; 
  virtual const CATPolyMathPolyLineCurve* CastAsPolyLine()const;
  virtual CATPolyMathPolyLineCurve* CastAsPolyLine();
  virtual CATPolyMathCurve * Clone () const;  
public:
  virtual void GetPoint (const unsigned int vertex, CATMathPoint& oPoint) const;
public:

  virtual void Evaluate (const double t, CATMathPoint& oPoint) const;
  virtual void EvaluateDerivative (const double t, double odPdt[]) const;
  virtual void EvaluateSecondDerivative(const double t, double odDdt[])const;
  virtual double GetMaxSecondDerivative()const;
public:
  virtual HRESULT Accept (CATPolyMathCurveConstVisitor &iV) const;
  virtual HRESULT Accept (CATPolyMathCurveVisitor &iV);

private:
  CATMathPoint *_PointsArray;
  int _nbPoints;
};


//INLINE
inline const HRESULT CATPolyMathPolyLineCurve::GetPointByInd (int indPoint,CATMathPoint &oPoint) const
{
  HRESULT hr = S_OK;
  if ((indPoint >= 0) && (indPoint < _nbPoints))
  {
    oPoint = _PointsArray[indPoint];
    hr = S_OK;
  }
  else
  {
    hr = E_FAIL;
  }
  return hr;
  
}

inline int CATPolyMathPolyLineCurve::GetNbPoints() const
{
  return _nbPoints;
}


#endif
