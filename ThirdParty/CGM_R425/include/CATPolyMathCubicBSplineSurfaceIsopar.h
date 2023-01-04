// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathCubicBSplineSurfaceIsopar.h
// Header definition of CATPolyMathCubicBSplineSurfaceIsopar
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// July 2009  Creation: tpg
//===================================================================
#ifndef CATPolyMathCubicBSplineSurfaceIsopar_H
#define CATPolyMathCubicBSplineSurfaceIsopar_H

#include "PolyMathCurves.h"
#include "CATPolyMathCurve.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"

class CATPolyMathCubicBSplineSurface;
class CATPolyMathCurveConstVisitor;
class CATPolyMathCurveVisitor;


/**
 * Describe your class here.
 */
//
//
class ExportedByPolyMathCurves CATPolyMathCubicBSplineSurfaceIsopar : public CATPolyMathCurve
{

public:

  // iIsoDir : 0 IsoU
  //           1 IsoV
  // iPointingSurface : 0 iSurface is duplicated
  //                    1 iSurface is pointed, not duplicated, so it should not be deleted during CATPolyMathCubicBSplineSurfaceIsopar life cycle
  CATPolyMathCubicBSplineSurfaceIsopar (const CATPolyMathCubicBSplineSurface * iSurface, int iIsoDir, double iIsoParam, int iPointingSurface = 0);

  virtual ~CATPolyMathCubicBSplineSurfaceIsopar ();

public:
  virtual const CATPolyMathCubicBSplineSurfaceIsopar* CastAsCubicBSplineIsopar()const;
  virtual CATPolyMathCubicBSplineSurfaceIsopar* CastAsCubicBSplineIsopar();
  virtual Type GetType () const; 
  virtual CATPolyMathCurve * Clone () const;  

public:

  // Return the position of an end vertex of the curve (start or end vertex).
  // @param vertex
  //   Valid values: 1, or 2.
  // @param oPoint
  //   The position of the vertex.
  void GetPoint (const unsigned int vertex, CATMathPoint& oPoint) const;

public:

  void Evaluate (const double t, CATMathPoint& oPoint) const;

  void EvaluateDerivative (const double t, double odPdt[]) const;
  void EvaluateSecondDerivative(const double t, double odDdt[])const;

  double GetMaxSecondDerivative()const;


public:

  /**
   * Access the concrete type through a const visitor
   * @return
   *   The status of the application of the visitor
   */
  HRESULT Accept (CATPolyMathCurveConstVisitor &iV) const;

  /**
   * Access the concrete type through a non-const visitor
   * @return
   *   The status of the application of the visitor
   */
  HRESULT Accept (CATPolyMathCurveVisitor &iV);

private:

  const CATPolyMathCubicBSplineSurface * _Surface;
  int _PointingSurface;
  int _IsoDir;
  double _IsoParam;

};

#endif
