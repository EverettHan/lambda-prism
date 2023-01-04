// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathCurveProjectOper.h
// Header definition of CATPolyMathCurveProjectOper
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// May 2007  Creation: ndo
//===================================================================
#ifndef CATPolyMathCurveProjectOper_H
#define CATPolyMathCurveProjectOper_H

#include "PolyMathCurves.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATDataType.h"

class CATPolyMathCurve;
class CATMathPoint;
class CATMathVector;


class ExportedByPolyMathCurves CATPolyMathCurveProjectOper
{

public:

  CATPolyMathCurveProjectOper (const CATPolyMathCurve& iCurve);

  ~CATPolyMathCurveProjectOper();   

public: 

  // Project the point iPoint onto the curve.  The result is the point oProjectedPoint.
  // The parameter t is an initial seed parameter for finding the projection.
  // After the projection, it is the parameter of the projected point.
  HRESULT Project (const CATMathPoint& iPoint, CATMathPoint& oProjectedPoint,
                   double& t) const;

protected:

  // Evaluation of the function, F, for Newton's method.
  void EvalF (const CATMathPoint& iPoint, const double t, double& f) const;

  // Evaluation of the function, F and its derivative for Newton's method.
  void EvalF (const CATMathPoint& iPoint, const double t,
              double& f, double& fx) const;

  //
  //  IsNull is a method to determine if (F(u),G(u)) = (f,g) can be considered as null 
  //  at (x,y) and oNorm is any norm of (F(u),G(u)). jac is a pointer containing the 4 values
  //  of the derivatives of F and G at (x,y). jac can be null.
  //  This method can be rederived for precision problems.
  //  
  //  This default method tests if |f| < CATEpsSol * (1+|fp|) if jac!=0,
  //  otherwise it tests if |f| < CATEpsSol.
  //
  CATBoolean IsNull (const double t, 
                     const double f, double & oNorm,
                     const double fp) const;

  // Safe Newton's Method to find a root.
  // Try to stay in the current interval in the iterations, using t as an initial parameter.
  // Return;
  //   1: Success
  //   2: Success but with critical point
  //   0: Failure
  //  -1: Failure with critical point
  //  -2: Failure because of unsafe Newton step
  // In successful cases, (x, y) are updated with the solution.
  //
  CATLONG32 SafeNewton (const CATMathPoint& iPoint, double & t) const;

private:

  const CATPolyMathCurve& _Curve;

  // Tolerances
  double _EpsSol;
  double _EpsSing;

  // Step size for first derivative evaluation.
  double _h;

};

#endif
