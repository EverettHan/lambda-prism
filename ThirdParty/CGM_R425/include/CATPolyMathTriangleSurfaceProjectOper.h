// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathTriangleProjectOper.h
// Header definition of CATPolyMathTriangleProjectOper
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// May 2007  Creation: ndo
//===================================================================
#ifndef CATPolyMathTriangleProjectOper_H
#define CATPolyMathTriangleProjectOper_H

#include "PolyMathSurfaces.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATDataType.h"

class CATPolyMathTriangleSurface;
class CATMathPoint;
class CATMathVector;


class ExportedByPolyMathSurfaces CATPolyMathTriangleSurfaceProjectOper
{

public:

  CATPolyMathTriangleSurfaceProjectOper (const CATPolyMathTriangleSurface& iPatch);

  ~CATPolyMathTriangleSurfaceProjectOper();   

public: 

  // Project the point iPoint onto the PN-Triangle.  The result is the point oProjectedPoint.
  // Initially, the parameters u, v, and w are seed parameters for finding the projection.
  // At the end, they are the parameters of the projected point.
  HRESULT Project (const CATMathPoint& iPoint, CATMathPoint& oProjectedPoint,
                   double& u, double& v, double& w) const;

public:

  // Return the distance of a point to an axis.
  // It can be used to check the validity of a projected point.
  static double GetDistanceToAxis (const CATMathPoint& iPoint, 
                                   const CATMathPoint& iAxisPoint, const CATMathVector& iAxisDir);

protected:

  // Evaluation of the functions, F and G, for Newton's method.
  void EvalFandG (const CATMathPoint& iPoint, const double u, const double v, 
                  double& f, double& g) const;

  // Evaluation of the functions, F and G and their partial derivatives for Newton's method.
  void EvalFandG (const CATMathPoint& iPoint, const double u, const double v,
                  double& f, double& fx, double& fy,
                  double& g, double& gx, double& gy) const;

  //
  //  IsNull is a method to determine if (F(u),G(u)) = (f,g) can be considered as null 
  //  at (x,y) and oNorm is any norm of (F(u),G(u)). jac is a pointer containing the 4 values
  //  of the derivatives of F and G at (x,y). jac can be null.
  //  This method can be rederived for precision problems.
  //  
  //  This default method tests if |f|+|g| < CATEpsSol * (1+|fx|+|fy|+|gx|+|gy|) if jac!=0,
  //  otherwise it tests if |f|+|g| < CATEpsSol.
  //
  CATBoolean IsNull (const double x, const double y, 
                     const double f, const double g, double & oNorm,
                     const double * jac = 0) const;

  // Safe Newton's Method to find a root.
  // try to stay in the current rectangle in the iterations, using (x,y) as an init.
  // Return;
  //   1: Success
  //   2: Success but with critical point
  //   0: Failure
  //  -1: Failure with critical point
  //  -2: Failure because of unsafe Newton step
  // In successful cases, (x, y) are updated with the solution.
  //
  CATLONG32 SafeNewton (const CATMathPoint& iPoint, double & x, double & y) const;

private:

  const CATPolyMathTriangleSurface& _TrianglePatch;

  // Tolerances
  double _EpsSol;
  double _EpsSing;

  // Step size for first derivative evaluation.
  double _h1;

};

#endif
