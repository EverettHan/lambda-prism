// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyQ4Solver.h
//
//===================================================================
// September 2011  Creation NDO
//===================================================================
#ifndef CATPolyQ4Solver_H
#define CATPolyQ4Solver_H

#include "PolyMathUtils.h"
#include "CATErrorDef.h"


/**
 * Solver minimizing the 4-dimensional quadric.
 * The solver tries to find the point v minimizing the quadratic expression Q(v).
 */
class ExportedByPolyMathUtils CATPolyQ4Solver 
{

public:

  CATPolyQ4Solver () {}

  ~CATPolyQ4Solver () {}

public:

  //inline double* GetCoefficients ();
  //inline const double* GetCoefficients () const;

public:

  //void SetCoefficients (const double q[]);
  void SetCoefficients (const double q0[], const double q1[]);

public:

  /**
   * Finds the 4D-point minimizing the quadric.
   */
  HRESULT Solve (double c[], double& t) const;

  /**
   * Computes the quadratic expression for the input 4D-point.
   */
  double Multiply (const double x, const double y, const double z, const double t) const;

private:

  static const unsigned int SizeQCoefficients;
  double _Q[15];  // Fifteen coefficients.

};

//inline double* CATPolyQ4Solver::GetCoefficients ()
//{
//  return _Q;
//}

//inline const double* CATPolyQ4Solver::GetCoefficients () const
//{
//  return _Q;
//}

//inline void CATPolyQ4Solver::SetCoefficients (const double q[])
//{
//  for (unsigned int i = 0; i < SizeQCoefficients; ++i)
//  {
//    _Q[i] = q[i];
//  }
//}

inline void CATPolyQ4Solver::SetCoefficients (const double q0[], const double q1[])
{
  for (unsigned int i = 0; i < SizeQCoefficients; ++i)
  {
    _Q[i] = q0[i] + q1[i];
  }
}

#endif
