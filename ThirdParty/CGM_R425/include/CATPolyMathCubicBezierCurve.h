// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathCubicBezierCurve.h
// Header definition of CATPolyMathCubicBezierCurve
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// May 2007  Creation: ndo
//===================================================================
#ifndef CATPolyMathCubicBezierCurve_H
#define CATPolyMathCubicBezierCurve_H

#include "PolyMathCurves.h"
#include "CATPolyMathCurve.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"

class CATPolyMathCurveConstVisitor;
class CATPolyMathCurveVisitor;


/**
 * Describe your class here.
 */
//
// Cubic Bezier curve (with support for normals).
//
//   Points:           A ----------------------------B
//   Control Points:  B30 ----- B21 ----- B12 ----- B03
//   Control Normals: N20 ---------- N11 ---------- N02
//
//   Parameter: t 0->1 with P(t = 0) = A and P(t = 1) = B. 
//
//   Weights:
//      v weight of A, 1 -> 0, v = 1 - t
//      u weight of B, 0 -> 1, u = t
//
// Points :
// --------
//
//   P(t) = u^3 * B30 + 3 * u^2 * v * B21 + 3 * u * v^2 * B12 + v^3 * B03
//
// Normals (2 modes) : Quadratic, Linear
// -------------------
//
//   Quadratic :
//
//     N(t) = u^2 * N20 + u * v * N11 + v^2 * N02
//
//   Linear :
//
//     N(t) = u * N20 + v * N02
//
class ExportedByPolyMathCurves CATPolyMathCubicBezierCurve : public CATPolyMathCurve
{

public:

  CATPolyMathCubicBezierCurve ();

  //Constructor of a cubic Bezier curve given 4 Bezier Points 
  CATPolyMathCubicBezierCurve (const CATMathPoint iPoints[]);
  void FillFromPoints(const CATMathPoint iPoints[]);

  // Construction of a cubic Bezier curve given two points and the tangents at these points.
  CATPolyMathCubicBezierCurve (const CATMathPoint iPoints[], const CATMathVector iTangents[], int iOptimalTangents=0);

  // Construction of a cubic Bezier curve given two points and the tangents at these points.
  CATPolyMathCubicBezierCurve (const double iPoint1[3], const double iPoint2[3],
                               const double iTangent1[3], const double iTangent2[3] ,
                               int iOptimalTangents=0);

  virtual ~CATPolyMathCubicBezierCurve ();

  // Construction of a cubic bezier curve given two points and two normals and optionally
  // a pair of tangents to the curve at its extremities. 
  // If P0, P1 and P2 are the three corner vertices, then:
  //   - iTangents[0] and iTangents[1] refer to the tangents to the curve at P0 and P1, respectively. 
  // Set the corresponding pointer to 0 if the tangent is not defined.
  //CATPolyMathCubicBezierCurve (const CATMathPoint iPoints[], const CATMathVector iNormals[],
                               //const CATMathVector* iTangents); 

public:

  enum ControlPointIndex
  {
    eB30 = 0,  // P1
    eB21,
    eB12,
    eB03       // P2
  };
  
  // Construction of a cubic Bezier curve given two points and the tangents at these points.
  void Set(const double iPoint1[3], const double iPoint2[3],
           const double iTangent1[3], const double iTangent2[3], 
           int iOptimalTangents=0);

  // Methods to set and get the control points.
  inline void SetControlPoint (const ControlPointIndex index, const CATMathPoint& iPoint);
  inline void GetControlPoint (const ControlPointIndex index, CATMathPoint& oPoint) const;

public:
  virtual const CATPolyMathCubicBezierCurve* CastAsCubicBezier()const;
  virtual CATPolyMathCubicBezierCurve* CastAsCubicBezier();
  virtual Type GetType () const; 
  virtual CATPolyMathCurve * Clone () const;  

public:

  // Return the position of an end vertex of the curve (start or end vertex).
  // @param vertex
  //   Valid values: 1, or 2.
  // @param oPoint
  //   The position of the vertex.
  void GetPoint (const unsigned int vertex, CATMathPoint& oPoint) const;
  
  // Return the tangant of an end vertex of the curve (start or end vertex).
  // @param vertex
  //   Valid values: 1, or 2.
  // @param oTangent
  //   The tangent of the vertex.
  void GetTangent (const unsigned int vertex, CATMathVector& oTangent) const;

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

  double _ControlPoints[4][3];

private:

  void ComputeControlPoints (const CATMathPoint iPoints[], const CATMathVector iTangents[], int iOptimalTangents);
  void ComputeControlPoints (const CATMathVector iTangents[], int iOptimalTangents);

  void EvaluatePrivate (const double t, CATMathPoint& oPoint) const;

  friend class CATPolyMathPNTGen;

};


void CATPolyMathCubicBezierCurve::SetControlPoint (const ControlPointIndex index, const CATMathPoint& iPoint)
{
  iPoint.GetCoord (_ControlPoints[index]);
}


void CATPolyMathCubicBezierCurve::GetControlPoint (const ControlPointIndex index, CATMathPoint& oPoint) const
{
  oPoint.SetCoord (_ControlPoints[index]);
}


#endif
