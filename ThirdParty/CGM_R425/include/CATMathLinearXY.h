#ifndef CATMathLinearXY_H
#define CATMathLinearXY_H// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATMathLinearXY
// Class of linear function of two variables : (x,y) -> a*u+b*v+c
//
//=============================================================================
// Usage notes:
//  Useful for parameter equations of planes
//  Permits formal operations
//
//=============================================================================
#include "CATIACGMLevel.h"

#include "YN000FUN.h"

#include "CATMathFoundationXY.h"
#include "CATMathInterval.h"
#include "CATMathPolynomX.h"
#include "CATMathDef.h"

class CATMathIntervalND;


class ExportedByYN000FUN CATMathLinearXY : public CATMathFoundationXY
{
 public:

  //-----------------------------------------------------------------
  // Constructors
  //-----------------------------------------------------------------
  
  // Copy constructor
  CATMathLinearXY(const CATMathLinearXY & p);
  // Constructs a*u+b*v+c
  CATMathLinearXY(const double ia, const double ib, const double ic);

  //-----------------------------------------------------------------
  // Destructor
  //-----------------------------------------------------------------
  ~CATMathLinearXY();
  CATCGMNewClassArrayDeclare;

  //-----------------------------------------------------------------
  // Set Global
  //-----------------------------------------------------------------

  void SetCoefficients(const double ia, const double ib, const double ic);

  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------
  
  CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
#ifdef CATIACGMV5R21
  CATBoolean IsATypeOf(const CATMathFunctionXYTypeId iType) const;
#endif
  CATBoolean IsOption(const CATMathOption iOption) const;
  CATMathClassId IsA() const;
  int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
  CATMathFunctionXY * Duplicate() const;
  CATMathFunctionXY * DeepDuplicate() const ;
#if defined ( CATIACGMR216CAA )
  CATMathFunctionXY * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
#endif
  void GetCoefficients(double & oa, double & ob, double & oc) const;
  //-----------------------------------------------------------------
  // Stream 
  //-----------------------------------------------------------------
#if defined ( CATIACGMV5R21 )
   virtual short GetStreamDomainType(char ioDomain[3]) const;
#else
   virtual short GetStreamType() const;
#endif
  void Stream( CATMathStream& Str, const char iLabelReserved[] = "" ) const;
  virtual CATBoolean _IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;

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
   // iOption is a command which contains which derivatives are requested
   // (usually, iOption = OptionEval + OptionEvalFirstDeriv)
   //
  void Eval(const double u, const double v, 
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

  //
  // Multi-evaluation of interval  on a regular grid of
  // Nu x Nv sub-squares  delimited by  [uStart,uEnd] x [vStart,vEnd]
  // WARNING : the pointer Images  must be previously allocated
  // Images[Nv*i+j] contains Eval(X_i,Y_j)
  //
//  void Eval(const CATMathIntervalND & iDomain,
//                    const CATLONG32 * NbIntervals,
//                    CATMathInterval * Images) const;


  
  //---------------------------------------------------------------------
  // Composition creation  
  //
  // Create the FunctionX defined by : t-> Phi(F(t),G(t))
  // where Phi represents the FunctionXY "this", 
  // WARNING : The returned pointer must be deleted by the caller.
  //
  //---------------------------------------------------------------------

  CATMathFunctionX * CreateCompositionX(const CATMathFunctionX * iF,
                                        const CATMathFunctionX * iG) const;
  // overloading << 
friend ExportedByYN000FUN ostream & operator << (ostream& os, CATMathLinearXY & p);

  // protected methods
protected:
  CATMathFunctionXY * FormalCombination(const CATLONG32 iN, 
                                        const CATMathFunctionXY ** iFunc,
                                        const double * iCoef, 
                                        const double iConstant) const;

 private:
  double _a, _b, _c;
};

#endif
