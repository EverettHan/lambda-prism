// COPYRIGHT DASSAULT SYSTEMES 1997

//===================================================================
//===================================================================
//
// CATMathSystemXYc
// Implementation class of 2x2 systems with coupled variables
// This class needs only two CATMathFunctionXY
//
//===================================================================


#ifndef CATMathSystemXYc_H
#define CATMathSystemXYc_H

#include "YN000FUN.h"
#include "CATMathDef.h"
#include "CATMathSystemXY.h"

class CATMathInterval;
class CATMathFunctionXY;
class CATSoftwareConfiguration;


class ExportedByYN000FUN CATMathSystemXYc : public CATMathSystemXY
{
 private:
   const CATMathFunctionXY * _F, * _G;

 public:
   //-----------------------------------------------------------------
   // Constructor
   //-----------------------------------------------------------------

   CATMathSystemXYc(CATSoftwareConfiguration * iConfig,
                    const CATMathFunctionXY * F,
                    const CATMathFunctionXY * G,
                    const CATTolerance & iTol = CATGetDefaultTolerance(),
                    const CATMathAttrList * iattr=NULL);
   
   //-----------------------------------------------------------------
   // Information methods
   //-----------------------------------------------------------------
   
   virtual CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
   virtual CATBoolean IsOption(const CATMathOption iOption) const;
   virtual CATMathClassId IsA() const;

   void Set(const CATMathFunctionXY * F,
            const CATMathFunctionXY * G);

   //-----------------------------------------------------------------
   // Evaluators
   //-----------------------------------------------------------------

   virtual double EvalF(const double & x, const double & y) const;
   virtual double EvalG(const double & x, const double & y) const;
   virtual double EvalFirstDerivFX(const double & x, const double & y) const;
   virtual double EvalFirstDerivFY(const double & x, const double & y) const;
   virtual double EvalFirstDerivGX(const double & x, const double & y) const;
   virtual double EvalFirstDerivGY(const double & x, const double & y) const;
   virtual double EvalSecondDerivFX2(const double & x, const double & y) const;
   virtual double EvalSecondDerivFXY(const double & x, const double & y) const;
   virtual double EvalSecondDerivFY2(const double & x, const double & y) const;
   virtual double EvalSecondDerivGX2(const double & x, const double & y) const;
   virtual double EvalSecondDerivGXY(const double & x, const double & y) const;
   virtual double EvalSecondDerivGY2(const double & x, const double & y) const;

   //
   // Evaluator of function and derivatives at the same time (see base class for details):
   //
   virtual void EvalF(const double u, const double v, 
                      const CATMathOption iOptions,
                      double * f,
                      double * fx =0, double * fy=0,
                      double * fx2=0, double *fxy=0, double *fy2=0) const;
   virtual void EvalG(const double u, const double v, 
                      const CATMathOption iOptions,
                      double * f,
                      double * fx =0, double * fy=0,
                      double * fx2=0, double *fxy=0, double *fy2=0) const;

   //
   // Multi-evaluation of function and derivatives on a regular 
   // grid of Nu x Nv points delimited by iDomain (see base class for details):
   //
   virtual void EvalF(const CATMathIntervalND & iDomain, const CATLONG32 * NbPoints,
                     const CATMathOption iOptions,
                     double * f,
                     double * fx =0, double * fy=0,
                     double * fx2=0, double *fxy=0, double *fy2=0) const;

   virtual void EvalG(const CATMathIntervalND & iDomain, const CATLONG32 * NbPoints,
                      const CATMathOption iOptions,
                      double * f,
                      double * fx =0, double * fy=0,
                      double * fx2=0, double *fxy=0, double *fy2=0) const;

   
};

#endif
