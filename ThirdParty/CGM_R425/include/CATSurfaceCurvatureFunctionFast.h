// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATSurfaceCurvatureFunctionFast :
//    The same as CATSurfaceCurvatureFunction, with an additionnal evaluator
//    for point, tangent and 2nd derivative simultaneously.
// 
//=============================================================================
// Usage notes:
//
//=============================================================================
//=============================================================================

#ifndef CATSurfaceCurvatureFunctionFast_H
#define CATSurfaceCurvatureFunctionFast_H

#include "CATSurfaceCurvatureFunction.h"
#include "CATMathFunctionXY.h"
#include "CATMathVector.h"
#include "CATMathInterval.h"
//DG
#include "Y30C3XGG.h"
#include "CATTolerance.h"


//-----------------------------------------------------------------------------
class ExportedByY30C3XGG CATSurfaceCurvatureFunctionFast : public CATSurfaceCurvatureFunction
{
 public:
  //-----------------------------------------------------------------
  // Object management
  //-----------------------------------------------------------------
  // copy-constructor  
  CATSurfaceCurvatureFunctionFast(const CATSurfaceCurvatureFunctionFast & iF);

  // constructor
  CATSurfaceCurvatureFunctionFast(const CATMathFunctionXY * iFX,
                                  const CATMathFunctionXY * iFY,
                                  const CATMathFunctionXY * iFZ,
                                  const CATCurvatureType itype = GaussianCurvature,
                                  const CATTolerance & iTolObject = CATGetDefaultTolerance());

  ~CATSurfaceCurvatureFunctionFast();

  CATMathFunctionXY * Duplicate() const;

  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------

  CATMathClassId IsA() const;
  CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
  CATBoolean IsOption(const CATMathOption iOption) const;
   
  //-----------------------------------------------------------------
  // Evaluators on doubles
  //-----------------------------------------------------------------
   
  //
  // Evaluator of function and derivatives at the same time :
  // (performance are increased if redefined in derived classes)
  // iOption is a command which contains which derivatives are requested
  // (usually, iOption = OptionEval + OptionEvalFirstDeriv)
  //
  void Eval(const double u, const double v, 
            const CATMathOption iOptions,
            double * f,
            double * fx =0, double * fy=0,
            double * fx2=0, double *fxy=0, double *fy2=0) const;

  /*
  // Multi-evaluation of function and derivatives on a regular 
  // grid of Nu x Nv points delimited by  [uStart,uEnd] x [vStart,vEnd]
  // If NbPoints[0]=1 and/or NbPoints[1]=1 then the evaluations
  // are made on the smallest corresponding coordinate in iDomain
  // WARNING : the pointers must be previously allocated if the
  // corresponding evaluations are needed.
  // The value f[Nv*i+j] contains Eval(x_i,y_j) ...
  //
  void Eval(const CATMathIntervalND & iDomain, const CATLONG32 * NbPoints,
	    const CATMathOption iOptions,
	    double * f,
	    double * fx =0, double * fy=0,
	    double * fx2=0, double *fxy=0, double *fy2=0) const;
  */

};

ExportedByY30C3XGG CATSurfaceCurvatureFunctionFast * CreateSurfaceCurvatureFunctionFast(const CATMathFunctionXY * iFX,
                                                                                        const CATMathFunctionXY * iFY,
                                                                                        const CATMathFunctionXY * iFZ,
                                                                                        const CATTolerance      & iTolObject = CATGetDefaultTolerance(),
                                                                                        const CATCurvatureType    itype      = GaussianCurvature); 

#endif
