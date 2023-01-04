// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathTriangleSideCurve.h
// Header definition of CATPolyMathTriangleSideCurve
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// June 2007  Creation: ndo
// 2009 zfi add normal
//===================================================================
#ifndef CATPolyMathTriangleSideCurve_H
#define CATPolyMathTriangleSideCurve_H

#include "PolyMathCurves.h"
#include "CATPolyMathCurve.h"
#include "CATMathPoint.h"
#include "CATPolyMathTriangleSurface.h"
#include "CATPolyMathPNTriangleSurface.h"

//class CATPolyMathTriangleSurface;
class CATPolyMathCurveConstVisitor;
class CATPolyMathCurveVisitor;


/**
 * Curve representing the side of a triangle surface.
 */
class ExportedByPolyMathCurves CATPolyMathTriangleSideCurve : public CATPolyMathCurve
{

public:

  CATPolyMathTriangleSideCurve (const CATPolyMathTriangleSurface& iSurface, const unsigned int iSide);

  virtual ~CATPolyMathTriangleSideCurve () {}

public:
  virtual const CATPolyMathTriangleSideCurve* CastAsTriangleSide()const;
  virtual CATPolyMathTriangleSideCurve* CastAsTriangleSide();
  virtual Type GetType () const; 
  virtual CATPolyMathCurve * Clone () const; 

public:

  // Return the position of an end vertex of the curve (start or end vertex).
  // @param vertex
  //   Valid values: 1, or 2.
  // @param oPoint
  //   The position of the vertex.
  void GetPoint (const unsigned int vertex, CATMathPoint& oPoint) const;
  void GetPointAndNormal (const unsigned int vertex, CATMathPoint& oPoint, CATMathVector& oNormal) const;


public:

  void Evaluate (const double t, CATMathPoint& oPoint) const;
  void Evaluate (const double t,CATMathPoint& oPoint,CATMathVector& oNormal) const;
  void EvaluateDerivative (const double t, double odPdt[]) const;
  void EvaluateSecondDerivative(const double t, double odSdt[])const;
  
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

protected:

  const CATPolyMathTriangleSurface& _TriangleSurface;
  const unsigned int _Side;

};

#endif
