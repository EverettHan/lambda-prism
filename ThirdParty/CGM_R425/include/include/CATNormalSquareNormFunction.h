// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
//
// CATNormalSquareNormFunction :
// Function of 2 variables, based on 3 functions of 2 variables _X[0..2],
// defined by ||DuF^DvF||^2.
// 
//=============================================================================
// Usage notes:
//
//=============================================================================
// Apr. 2001    Creation                                      S.Dauby
// 10/07/08 NLD Ajout SetActiveOptimizedGridEval() _ActiveOptimizedGridEval()
// 23/07/09 NLD Gestion du stream
//              - derivation de GetDirectComponents()
//              - derivation de _IsStreamable()
//              - derivation de GetStreamType()
//              - derivation de Steam()
//              - derivation de DeepDuplicate()
//              - ajout de UnStreamNormalSquareNormFunction()
//              - ajout de _DeleteFunctions
// 23/07/09 NLD Deplacement dans AdvancedMathematics pour UnStream centralise
//=============================================================================

#ifndef CATNormalSquareNormFunction_H
#define CATNormalSquareNormFunction_H

#include "CATMathFunctionXY.h"
#include "CATMathBasisFunctionXY.h"
#include "CATTolerance.h"
#include "YN000FUN.h"


/**
   * @nodoc   internal use. 
   * @nocgmitf
   */
class ExportedByYN000FUN CATNormalSquareNormFunction : public CATMathBasisFunctionXY
{
// public methods
 public:
  //-----------------------------------------------------------------
  // Object management
  //-----------------------------------------------------------------
  // copy-constructor  
  CATNormalSquareNormFunction(const CATNormalSquareNormFunction & iF);

  // constructor
  CATNormalSquareNormFunction(const CATMathFunctionXY * iFX,
                              const CATMathFunctionXY * iFY,
                              const CATMathFunctionXY * iFZ,
                              const CATTolerance & iTolObject);

  ~CATNormalSquareNormFunction();
  CATMathFunctionXY * Duplicate() const;
  /** @nodoc  Not Published  */
  CATMathFunctionXY * DeepDuplicate() const ;
#if defined ( CATIACGMR216CAA )
  /** @nodoc  Not Published  */
  CATMathFunctionXY * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
#endif
  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------

  CATMathClassId IsA() const;
  CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
  CATBoolean IsOption(const CATMathOption iOption) const;
  //-----------------------------------------------------------------
  // Stream management
  //-----------------------------------------------------------------
  virtual int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
  virtual CATBoolean _IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;
#if defined ( CATIACGMV5R21 )
   virtual short GetStreamDomainType(char ioDomain[3]) const;
#else
   virtual short GetStreamType() const;
#endif
   virtual void Stream( CATMathStream &Str, const char iLabelReserved[]) const ;

  //-----------------------------------------------------------------
  // Evaluators on doubles
  //-----------------------------------------------------------------
   
  double Eval(const double & u, const double & v) const;

  double EvalFirstDerivX(const double & u, const double & v) const;
  double EvalFirstDerivY(const double & u, const double & v) const;
 
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

  // Multi-evaluation of function and derivatives on a regular 
  // grid of Nu x Nv points delimited by  [uStart,uEnd] x [vStart,vEnd]
  // If NbPoints[0]=1 and/or NbPoints[1]=1 then the evaluations
  // are made on the smallest corresponding coordinate in iDomain
  // WARNING : the pointers must be previously allocated if the
  // corresponding evaluations are needed.
  // The value f[Nv*i+j] contains Eval(x_i,y_j) ...
  //
  // NLD10/07/08
  // - by default generic grid evaluation with double loop on simple Eval()
  // - optimized grid evaluation available only if SetActiveOptimizedGridEval() has been called
  void Eval(const CATMathIntervalND & iDomain, const CATLONG32 * NbPoints,
       const CATMathOption iOptions,
       double * f,
       double * fx =0, double * fy=0,
       double * fx2=0, double *fxy=0, double *fy2=0) const;

  // Optimized grid evaluation activation
  // CAUTION: depending on the way grid evaluations are implemented in received functions,
  //  results may be different with optimization.
  //  ==> call to SetActiveOptimizedGridEval() must be managed by SoftwareConfiguration
  void SetActiveOptimizedGridEval(int iActiveOptimizedGridEval=1) ;

  // Evaluators on intervals

private:
  const CATMathFunctionXY * _X[3];
  int _ActiveOptimizedGridEval ;
  int _DeleteFunctions ;
};

#endif
