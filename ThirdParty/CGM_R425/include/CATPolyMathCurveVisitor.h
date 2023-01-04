// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathCurveVisitor.h
// Header definition of CATPolyMathCurveVisitor
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// June 2007  Creation: ndo
//===================================================================
#ifndef CATPolyMathCurveVisitor_H
#define CATPolyMathCurveVisitor_H

#include "PolyMathCurves.h"
#include "CATErrorDef.h"
#include "CATPolyMathCurve.h"

class CATPolyMathCubicBezierCurve;
class CATPolyMathCubicBSplineSurfaceIsopar;


/**
 * Describe your class here.
 */
class ExportedByPolyMathCurves CATPolyMathCurveVisitor
{

public:

  CATPolyMathCurveVisitor () {}
  virtual ~CATPolyMathCurveVisitor () {}

public:

  inline HRESULT Visit (CATPolyMathCurve& iCurve);

public:

  virtual HRESULT VisitConcrete (CATPolyMathCubicBezierCurve& iCurve) = 0;
  virtual HRESULT VisitConcrete (CATPolyMathCubicBSplineSurfaceIsopar& iCurve) = 0;

};


inline HRESULT CATPolyMathCurveVisitor::Visit (CATPolyMathCurve& iCurve)
{
  return iCurve.Accept (*this);
}

#endif
