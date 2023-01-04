/* COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATFunctionIntersectionLnCrv:
//  class of function for the intersection of a Line and a 3D Curves
//
//===================================================================
//
// Usage notes:
//
//  Internal use inside CATIntersection operator
//  
//
//===================================================================
// Nov. 97    Creation                         N. Barrier
// Juin 2004 Versionning Interne        EAB
//===================================================================
*/
 
#ifndef CATFUNCTIONSQUAREDISTLNCRV_H
#define CATFUNCTIONSQUAREDISTLNCRV_H

#include "Y30C3XGG.h"
#include "CATMathDef.h"
#include "CATMathFunctionX.h"
#include "CATMathPoint.h"
#include "CATMathDirection.h"
#include "CATMathBasisFunctionX.h"
#include "CATTolerance.h"

class CATMathInterval;
class CATSoftwareConfiguration;

//-------------------------------------------------------------------
class ExportedByY30C3XGG CATFunctionSquareDistLnCrv : public CATMathBasisFunctionX
{
   const CATMathFunctionX *_Function[3];
   CATMathPoint _origin;
   CATMathDirection _direction;
   CATSoftwareConfiguration * _Config;
  
// Compute the fxy evaluation from fx and fy evaluations
//-------------------------------------------------------------------
   void Evalf(double &fu0, double &fu1, double &fu2,
                     double &du0, double &du1, double &du2,
                     double &d2u0, double &d2u1, double &d2u2,
                     const  CATMathOption iOption,
                     double *f, double *fx, double * fx2) const;
  
 public:
   CATFunctionSquareDistLnCrv(CATSoftwareConfiguration * iConfig,
                              const CATMathFunctionX *const iFunctionCrv[3],
                              const CATMathPoint & iO, const CATMathDirection & iu,
                              const CATTolerance & iTolObject = CATGetDefaultTolerance());  
   ~CATFunctionSquareDistLnCrv();

   CATMathFunctionX * Duplicate() const;
  
   //-----------------------------------------------------------------
   // Information methods
   //-----------------------------------------------------------------
   
   virtual CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
   virtual CATBoolean IsOption(const CATMathOption iOption) const;
   virtual CATMathClassId IsA() const; /*=0*/
   
   //-----------------------------------------------------------------
   // Evaluators on doubles
   //-----------------------------------------------------------------
   
   // pure virtual evaluator
   virtual double Eval(const double & u) const; /*=0*/
   virtual double EvalFirstDeriv(const double & u) const;
   virtual double EvalSecondDeriv(const double & u) const;
/*
   virtual double EvalThirdDeriv(const double & u) const;
*/   
   // Evaluation of function and derivatives at the same time on params
   virtual void Eval(const double u, 
                     const CATMathOption iOptions,
                     double * f,
                     double * fu =0,
                     double * fu2=0 ) const;
/*
//-------------------------------------------------------------------
   // Multi-evaluation of function and derivatives
   //
   virtual void Eval(const CATMathInterval & iDomain, const CATLONG32 NbPoints,
                     const CATMathOption iOptions,
                     double * f,
                     double * fx =0,
                     double * fx2=0 ) const;
*/   
   //-----------------------------------------------------------------
   // Evaluators on intervals
   //-----------------------------------------------------------------

   virtual CATMathInterval Eval(const CATMathInterval & Du) const;
   
   virtual CATMathInterval EvalFirstDeriv(const CATMathInterval & Du) const;
   
/*   virtual CATMathInterval EvalSecondDeriv(const CATMathInterval & Du) const;
*/
};

#endif
