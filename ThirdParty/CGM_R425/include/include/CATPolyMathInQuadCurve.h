// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathInQuadCurve.h
// Header definition of CATPolyMathInQuadCurve
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// June 2009  Creation: zfi
//===================================================================

#ifndef CATPolyMathInQuadCurve_H
#define CATPolyMathInQuadCurve_H

#include "PolyMathCurves.h"
#include "CATPolyMathCurve.h"

#include "CATMathPoint.h"
#include "CATMathPoint2D.h"

class CATPolyMathCurveConstVisitor;
class CATPolyMathCurveVisitor;
class CATPolyMathQuadSurface;

class ExportedByPolyMathCurves CATPolyMathInQuadCurve : public CATPolyMathCurve
{

public:

  CATPolyMathInQuadCurve (const CATPolyMathQuadSurface& iSurface,  
                          const double iU1, const double iV1,
                          const double iU2, const double iV2);

  virtual ~CATPolyMathInQuadCurve () {}

public:
  virtual const CATPolyMathInQuadCurve* CastAsInQuad()const;
  virtual CATPolyMathInQuadCurve* CastAsInQuad();
  virtual Type GetType () const; 
  virtual CATPolyMathCurve * Clone () const; 

public:
  const CATPolyMathQuadSurface& GetSurface()const{return _QuadSurface;}
  HRESULT GetLocalCoords(double& oU1, double& oV1, double& oU2, double& oV2)const{oU1=_U1;oU2=_U2;oV1=_V1;oV2=_V2;return S_OK;}

public:

  // Return the position of an end vertex of the curve (start or end vertex).
  // @param vertex
  //   Valid values: 1, or 2.
  // @param oPoint
  //   The position of the vertex.
  void GetPoint (const unsigned int vertex, CATMathPoint& oPoint) const;

public:

  void Evaluate (const double t, CATMathPoint& oPoint) const;

  void Evaluate (const double t,CATMathPoint& oPoint,CATMathVector& oNormal) const;

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

protected:

  const CATPolyMathQuadSurface& _QuadSurface;
  double _U1,_V1, _U2, _V2;

};

#endif
