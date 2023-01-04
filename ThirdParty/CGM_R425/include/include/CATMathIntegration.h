//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATMathIntegration :
// Abstract class used to compute integral of functions from R to R^n :
//
//  t  -->  F(t) =  ( F_0(t), F_1(t), ..., F_{n-1}(t) )
//
//
//=============================================================================
// Usage notes:
//
// The algorithm used is the so-called CCR subdivision method from 
// O'Hara and Francis J. Smith (1968)  "The evaluation of definite integrals
// by interval subdivision", Computing Journal.
// This method uses a subdivision process, combining the 9-point
// Romberg quadrature, two 5-point Newton-Cotes formula (2x Bode's rule) using
// the same abcissa, and a further two 7-point Clenshaw-Curtis quadrature.
// This techniques permits to performs efficient subdivision to compute the
// integral by controling the error, and minimising the number of evaluation 
// since at least 70% of abcissas are re-used during the subdivision process.
// 
// Moreover, the subdivision technique permits to concentrate the abcissas near
// the region of greatest irregularity in the integrand, thus well suited to 
// piecewise regular functions.
//
// Note : Clenshaw-Curtis method could also be used, with error estimation from
// O'Hara and Francis J. Smith (1968) "Error estimation in the Clenshaw-Curtis 
// quadrature formula", Computing Journal, 11, 213-219
//=============================================================================

#ifndef CATMathIntegration_H
#define CATMathIntegration_H

#include "YN000FUN.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATMathInline.h"

class CATMathFunctionX;
class CATMathSetOfPointsND;
class CATMathConstraint;
class CATSoftwareConfiguration;


//-----------------------------------------------------------------------------
class ExportedByYN000FUN CATMathIntegration : public CATCGMVirtual
{
   // public methods
public:
   //-----------------------------------------------------------------
   // Objects management
   //-----------------------------------------------------------------
   CATMathIntegration(      CATSoftwareConfiguration * iSoftwareConfiguration,
                      const CATLONG32                  iDimension            ); // The number of function of one variable
   virtual ~CATMathIntegration();

   //-----------------------------------------------------------------
   // Eval
   //-----------------------------------------------------------------
   virtual void Eval(const double t, double * oFX) = 0;

   //-----------------------------------------------------------------
   // Interface (Set)
   //-----------------------------------------------------------------
   // method used to change the maximum depth in the CCR-subdivision method.
   // The default maximum depth is 6
   INLINE void SetMaxDepth(const CATLONG32 iMaxDepth)
   {
      _MaxCCRDepth = iMaxDepth;
   };

   // The default minimum depth is 0
   INLINE void SetMinDepth(const CATLONG32 iMinDepth)
   {
      _MinCCRDepth = iMinDepth;
   };

   //-----------------------------------------------------------------
   // Methods
   //-----------------------------------------------------------------
   // Main method to have the of the integral :
   //
   // * The intergral is computed in the interval [tMin,tMax]
   // * ErrMax is an input array (of size Dimension) 
   //   of maximum absolute error required for the integral
   // * oResult is an array passed by the caller (of size Dimension), its output 
   //   value contains the integral
   // * oOutputErr is an optional array passed by the caller to have the estimated
   //   computed error (which is usually lower than iErrMax)
   void Integration(const double   tMin        ,
                    const double   tMax        ,
                    const double * iErrMax     ,
                          double * oResult     ,
                          double * oOutputErr=0);

   void Lagrange3(const double   tMin   ,
                  const double   tMax   ,
                        double * oResult);


protected : // ZIB: Why isn't this private? (and why are those methods virtual?)
   //
   // CCR-Subdivision algorithm (with limited depth) 
   // to compute the value of the integral on [a,b]
   //
   // If iFX is not null, it contains the already computed values of the functions
   // at the 5 abcissas a+i/4*(b-a), i=0,1,2,3,4 :
   //
   //   iFX[i*_Dimension+j] = F_j(x_i),  with x_i = a+i/4*(b-a)
   //
   virtual void CCRSubdivision(const double a, const double b, 
      const double * iFX,
      const double * iMaxErr, double * oResult, double * oOutputErr, CATLONG32 iDepth=0, CATBoolean iPrevOK=FALSE);

   //  Compute the 9-point Romberg quadrature on [a,b]
   // 
   // iFX contains already computed values of F :
   //
   //  iFX[i*_Dimension+j] = F_j(x_i)   with   x_i = a+i/8*(b-a) (i=0..8)
   //
   virtual void Romberg9(const double a, const double b, const double * iFX, double * oResult);

   // Compute two 5-point Newton-Cotes formulas (Bode's rule) on [a,b]
   //
   // iFX contains already computed values of F :
   //
   //  iFX[i*_Dimension+j] = F_j(x_i)   with   x_i = a+i/8*(b-a) (i=0..8)
   //
   virtual void TwoNewtonCotes5(const double a, const double b, const double * iFX, double * oResult);

   // Compute two 7-point Clenshaw-Curtis formulas on [a,b], using some already
   // computed values of F in iFX :
   //
   //  iFX[i*_Dimension+j] = F_j(x_i)   with   x_i = a+i/8*(b-a) (i=0..8)
   //
   // (4 other evaluations will be needed, but these 9 are reused).
   //
   // oOutputErr contains the absolute error estimate for the Clenshaw-Curtis method
   virtual void TwoClenshawCurtis7(const double a, const double b, const double * iFX, double * oResult,
      double * oOutputErr);

   // Additionnal test called when the error seems valid.
   // Default check does nothing.
   virtual CATBoolean CheckError(const CATLONG32 & iIdCoord,
                                 const double    * iError  ,
                                 const double    * iValue  ,
                                 const CATLONG32 & iDepth  );

   // Protected data
protected:




   // Dimension en dessous de laquelle on ne fait pas d'allocation dynamique
#define CATMathIntegration_Opt_Dim 11
   double _OptTmpArray[2*CATMathIntegration_Opt_Dim];
   double * _TmpResult, * _TmpErr;
   CATLONG32 _Dimension, _MaxCCRDepth, _MinCCRDepth;
   CATSoftwareConfiguration * _SoftwareConfiguration;
   CATBoolean _RequireConvergence;
   CATBoolean _BugTwoClenshawCurtis7;
};

#endif
