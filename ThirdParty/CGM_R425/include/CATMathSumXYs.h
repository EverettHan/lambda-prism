#ifndef CATMathSumXYs_H
#define CATMathSumXYs_H
// COPYRIGHT DASSAULT SYSTEMES 1997
//============================================================================
//
// CATMathSumXYs
// Class of real functions of two separated variables.
//
//============================================================================
// Usage notes:
//
//  This class is an function class for functions of two
//  separated variables.
//
//============================================================================

#include "CATIACGMLevel.h"

#include "YN000FUN.h"

#include "CATMathFoundationXY.h"
#include "CATMathDef.h"

class CATMathFunctionX;
class CATMathInterval;

class CATMathSumXYsDel;
class CATMathSumXYsDel2;

class ExportedByYN000FUN CATMathSumXYs : public CATMathFoundationXY
{
// public methods
 public:
  //-----------------------------------------------------------------
  // Constructors and destructor
  //-----------------------------------------------------------------
  CATMathSumXYs(const CATMathSumXYs & s);
  CATMathSumXYs(const CATMathFunctionX * fU,
		            const CATMathFunctionX * fV);
  virtual ~CATMathSumXYs();
  CATCGMNewClassArrayDeclare;

  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------

  CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
#ifdef CATIACGMV5R21
  CATBoolean IsATypeOf(const CATMathFunctionXYTypeId iType) const;
#endif
  CATBoolean IsOption(const CATMathOption iOption) const;
  CATMathClassId IsA() const;
	/** @nodoc */
  int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
  CATMathFunctionXY * Duplicate() const;
  CATMathFunctionXY * DeepDuplicate() const ;
#if defined ( CATIACGMR216CAA )
  /** @nodoc  Not Published  */
  CATMathFunctionXY * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
#endif

  //-----------------------------------------------------------------
  // Evaluators on doubles
  //-----------------------------------------------------------------

  double Eval(const double & u, const double & v) const;

  double EvalFirstDerivX(const double & u, const double & v) const;
  double EvalFirstDerivY(const double & u, const double & v) const;

  double EvalSecondDerivX2(const double & u, const double & v) const;
  double EvalSecondDerivXY(const double & u, const double & v) const;
  double EvalSecondDerivY2(const double & u, const double & v) const;

  double EvalThirdDerivX3(const double & u, const double & v) const;
  double EvalThirdDerivX2Y(const double & u, const double & v) const;
  double EvalThirdDerivXY2(const double & u, const double & v) const;
  double EvalThirdDerivY3(const double & u, const double & v) const;


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
  void Eval(const CATMathIntervalND & iDomain, const CATLONG32 * NbPoints,
            const CATMathOption iOptions,
            double * f,
            double * fx =0, double * fy=0,
            double * fx2=0, double *fxy=0, double *fy2=0) const;

  //-----------------------------------------------------------------
  // Evaluators on intervals
  //-----------------------------------------------------------------

  CATMathInterval Eval(const CATMathInterval & Du,
            const CATMathInterval & Dv, const CATTolerance & iTolObject=CATGetDefaultTolerance()) const;
  CATMathInterval EvalFirstDerivX(const CATMathInterval & Du,
				    const CATMathInterval & Dv) const;
  CATMathInterval EvalFirstDerivY(const CATMathInterval & Du,
				    const CATMathInterval & Dv) const;
  CATMathInterval EvalSecondDerivX2(const CATMathInterval & Du,
				    const CATMathInterval & Dv) const;
  CATMathInterval EvalSecondDerivXY(const CATMathInterval & Du,
				    const CATMathInterval & Dv) const;
  CATMathInterval EvalSecondDerivY2(const CATMathInterval & Du,
				    const CATMathInterval & Dv) const;
  void Eval(const CATMathInterval & Du, const CATMathInterval & Dv,
	          const CATMathOption iOptions,
	          CATMathInterval * f,
	          CATMathInterval * fx =0, CATMathInterval * fy=0,
	          CATMathInterval * fx2=0, CATMathInterval *fxy=0, 
	          CATMathInterval *fy2=0, const CATTolerance & iTolObject=CATGetDefaultTolerance()) const;



  /**
  * @nodoc
  *
  * MultiEvaluator of f and its derivative on a non regular grid :
  * Evaluation of 
  *                F[i*xNbPoints+j] = Eval(xPoints[i],yPoints[j]), ...
  */
  virtual void EvalGrid(CATLONG32 xNbPoints, const double * xPoints, CATLONG32 yNbPoints, const double * yPoints,
                        const CATMathOption iOptions,
                        double * ioF, 
                        double * ioFx=0, double * ioFy=0) const;
   

  //-----------------------------------------------------------------
  // Stream 
  //-----------------------------------------------------------------
#if defined ( CATIACGMV5R21 )
   virtual short GetStreamDomainType(char ioDomain[3]) const;
#else
   virtual short GetStreamType() const;
#endif
  void Stream( CATMathStream& Str, const char iLabelReserved[] = "" ) const;
  virtual size_t  GetStaticMemoryBytes() const;   
  virtual size_t  GetDynamicMemoryBytes() const;   
  virtual CATBoolean _IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;

  // protected methods
protected:
  virtual CATMathFunctionXY * FormalCombination(const CATLONG32 iN, 
						const CATMathFunctionXY ** iFunc,
						const double * iCoef, 
						const double iConstant) const;

private:
  const CATMathFunctionX *_fU, *_fV;
  friend class CATMathSumXYsDel;
  friend class CATMathSumXYsDel2;
};

#endif
