// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathCurve.h
//
//===================================================================
// May 2007  Creation: ndo
// Nov 2009 zfi : add casts, gettype
//===================================================================
#ifndef CATPolyMathCurve_H
#define CATPolyMathCurve_H

#include "PolyMathCurves.h"

#include "CATErrorDef.h"
#include "CATPolyMathObject.h"

class CATMathPoint;
class CATPolyMathCurveConstVisitor;
class CATPolyMathCurveVisitor;

class CATPolyMathLineCurve;
class CATPolyMathPolyLineCurve;
class CATPolyMathCircleCurve;
class CATPolyMathCubicBezierCurve;
class CATPolyMathCubicBSplineCurve;
class CATPolyMathCubicBSplineSurfaceIsopar;
class CATPolyMathInQuadCurve;
class CATPolyMathTriangleSideCurve;


/**
 * Describe your class here.
 */
class ExportedByPolyMathCurves CATPolyMathCurve : public CATPolyMathObject
{

public:

  CATPolyMathCurve () {}
  virtual ~CATPolyMathCurve () {}

  /**
   * Returns a clone of this instance.
   */
  virtual CATPolyMathCurve* Clone () const = 0;

public:

  // Casts
  const CATPolyMathCurve* CastAsCurve () const;
  CATPolyMathCurve* CastAsCurve ();

  virtual const CATPolyMathLineCurve* CastAsLine()const;
  virtual const CATPolyMathPolyLineCurve* CastAsPolyLine()const;
  virtual const CATPolyMathCircleCurve* CastAsCircle()const;
  virtual const CATPolyMathCubicBezierCurve* CastAsCubicBezier()const;
  virtual const CATPolyMathCubicBSplineCurve* CastAsCubicBSpline()const;
  virtual const CATPolyMathCubicBSplineSurfaceIsopar* CastAsCubicBSplineIsopar()const;
  virtual const CATPolyMathInQuadCurve* CastAsInQuad()const;
  virtual const CATPolyMathTriangleSideCurve* CastAsTriangleSide()const;

  virtual CATPolyMathLineCurve* CastAsLine();
  virtual CATPolyMathPolyLineCurve* CastAsPolyLine();
  virtual CATPolyMathCircleCurve* CastAsCircle();
  virtual CATPolyMathCubicBezierCurve* CastAsCubicBezier();
  virtual CATPolyMathCubicBSplineCurve* CastAsCubicBSpline();
  virtual CATPolyMathCubicBSplineSurfaceIsopar* CastAsCubicBSplineIsopar();
  virtual CATPolyMathInQuadCurve* CastAsInQuad();
  virtual CATPolyMathTriangleSideCurve* CastAsTriangleSide();

public:

  virtual int ComputeLevel () const;

  // Return the position of an end vertex of the curve (start or end vertex).
  // @param vertex
  //   Valid values: 1, or 2.
  // @param oPoint
  //   The position of the vertex.
  virtual void GetPoint (const unsigned int vertex, CATMathPoint& oPoint) const = 0;

public:

  virtual void Evaluate (const double t, CATMathPoint& oPoint) const = 0;

  virtual void EvaluateDerivative (const double t, double odPdt[]) const = 0;
  virtual void EvaluateSecondDerivative(const double t, double odDdt[])const=0;

  virtual double GetMaxSecondDerivative()const=0;
  virtual void GetLimits(double &tmin,double &tmax) const;

public:

  /**
   * Access the concrete type through a const visitor
   * @return
   *   The status of the application of the visitor
   */
  virtual HRESULT Accept (CATPolyMathCurveConstVisitor &iV) const = 0;

  /**
   * Access the concrete type through a non-const visitor
   * @return
   *   The status of the application of the visitor
   */
  virtual HRESULT Accept (CATPolyMathCurveVisitor &iV) = 0;

};

#endif
