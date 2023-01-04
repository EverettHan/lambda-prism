// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathCurveConstVisitor.h
// Header definition of CATPolyMathCurveConstVisitor
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// July 2007  Creation: ndo
//===================================================================
#ifndef CATPolyMathCurveConstVisitor_H
#define CATPolyMathCurveConstVisitor_H

#include "PolyMathCurves.h"
#include "CATErrorDef.h"
#include "CATPolyMathCurve.h"

class CATPolyMathCubicBezierCurve;
class CATPolyMathCubicBSplineSurfaceIsopar;


/**
 * Describe your class here.
 */
class ExportedByPolyMathCurves CATPolyMathCurveConstVisitor
{

public:

  CATPolyMathCurveConstVisitor () {}
  virtual ~CATPolyMathCurveConstVisitor () {}

public:

  inline HRESULT Visit (const CATPolyMathCurve& iCurve);

public:

  virtual HRESULT VisitConcrete (const CATPolyMathCubicBezierCurve& iCurve) = 0;
  virtual HRESULT VisitConcrete (const CATPolyMathCubicBSplineSurfaceIsopar& iCurve) = 0;

};


inline HRESULT CATPolyMathCurveConstVisitor::Visit (const CATPolyMathCurve& iCurve)
{
  return iCurve.Accept (*this);
}

#endif
