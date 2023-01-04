// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathCurveThicknessOper.h
// Header definition of CATPolyMathCurveThicknessOper
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// July 2007  Creation: ndo
//===================================================================
#ifndef CATPolyMathCurveThicknessOper_H
#define CATPolyMathCurveThicknessOper_H

#include "PolyMathCurves.h"
#include "CATPolyMathCurveConstVisitor.h"
#include "CATErrorDef.h"  // HRESULT definition.

class CATPolyMathCurve;
class CATPolyMathCubicBezierCurve;


class ExportedByPolyMathCurves CATPolyMathCurveThicknessOper : public CATPolyMathCurveConstVisitor
{

public:

  CATPolyMathCurveThicknessOper () {}
  ~CATPolyMathCurveThicknessOper () {}

public:

  // Compute an upper bound to the thickness of a curve.
  // The thickness is defined as the diameter of the cylinder of axis, the line defined by the 
  // end points of the curve, and that contain the curve.
  inline HRESULT Run (const CATPolyMathCurve& iCurve);

  inline double GetUpperBoundToThickness () const;

public:

  HRESULT VisitConcrete (const CATPolyMathCubicBezierCurve& iCurve);
  HRESULT VisitConcrete (const CATPolyMathCubicBSplineSurfaceIsopar& iCurve);

protected:

  double _UpperBoundThickness;

};


inline HRESULT CATPolyMathCurveThicknessOper::Run (const CATPolyMathCurve& iCurve)
{
  return Visit (iCurve);
}


inline double CATPolyMathCurveThicknessOper::GetUpperBoundToThickness () const
{
  return _UpperBoundThickness;
}

#endif
