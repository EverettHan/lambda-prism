#ifndef CATMathSquareDistXYs_H
#define CATMathSquareDistXYs_H
// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathSquareDistXYs:
//  class of function for the distance min of two N (<=3) dimensional curves :
//  (u,v) ->  (F_0(u) - G_0(v))^2 + ... + (F_{N-1}(u) - G_{N-1}(v))^2
//
//===================================================================
//
// Usage notes:
//
//  Used for intersection and distance min of 2D and 3D curves
//  
//
//===================================================================
// 30/01/09 NLD Interface R20 (CATSoftwareConfiguration)
//              pour Minimize()
//              Le constructeur prend une SoftwareConfiguration
//              Ajout de _Config;
// 13/04/11 NLD Deflaggage CATMathFunctionXYR20Interface
//=============================================================================
#include "CATIACGMLevel.h"

#include "CATMathDef.h"
#include "CATMathFunctionX.h"
#include "CATMathFoundationXY.h"
#include "CATMathInterval.h"

class CATSoftwareConfiguration ;
//-------------------------------------------------------------------

#include "YN000FUN.h"

class CATMathSquareDistXYsDel;

class ExportedByYN000FUN CATMathSquareDistXYs : public CATMathFoundationXY
{
 private:

  CATLONG32 _N; // Dimension, <= 3
  const CATMathFunctionX * _F[3], * _G[3];
  friend class CATMathSquareDistXYsDel;
  CATSoftwareConfiguration* _Config;

 public:
   
  CATMathSquareDistXYs(const CATLONG32 iN,  
             const CATMathFunctionX ** iF,
             const CATMathFunctionX ** iG,
                   CATSoftwareConfiguration* iConfig
                      );
  
  virtual ~CATMathSquareDistXYs();
  CATCGMNewClassArrayDeclare;

  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------
   
   virtual CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
#ifdef CATIACGMV5R21
   virtual CATBoolean IsATypeOf(const CATMathFunctionXYTypeId iType) const;
#endif
   virtual CATBoolean IsOption(const CATMathOption iOption) const;
   virtual CATMathClassId IsA() const;
   /** @nodoc */
   int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
   /** @nodoc  Not Published  */
   CATMathFunctionXY * Duplicate() const;
   /** @nodoc  Not Published  */
   CATMathFunctionXY * DeepDuplicate() const ;
#if defined ( CATIACGMR216CAA )
   /** @nodoc  Not Published  */
   CATMathFunctionXY * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
#endif
   //-----------------------------------------------------------------
   // Evaluators on doubles
   //-----------------------------------------------------------------
   
   // pure virtual evaluator
   virtual double Eval(const double & u, const double & v) const; /*=0*/
   
   virtual double EvalFirstDerivX(const double & u, const double & v) const;
   virtual double EvalFirstDerivY(const double & u, const double & v) const;
   
   virtual double EvalSecondDerivX2(const double & u, const double & v) const;
   virtual double EvalSecondDerivXY(const double & u, const double & v) const;
   virtual double EvalSecondDerivY2(const double & u, const double & v) const;
   
   virtual double EvalThirdDerivX3(const double & u, const double & v) const;
   virtual double EvalThirdDerivX2Y(const double & u, const double & v) const;
   virtual double EvalThirdDerivXY2(const double & u, const double & v) const;
   virtual double EvalThirdDerivY3(const double & u, const double & v) const;
   virtual void EvalAllThirdDerivs(const double iX, const double iY,
                                   double & oFx3, double & oFx2y, double & oFxy2, double & oFy3)
                                   const;
   virtual void EvalUpToThirdDeriv(const double iX, const double iY,
                                   double & oF, double & oFx,  double & oFy,
                                   double & oFx2, double & oFxy, double & oFy2,
                                   double & oFx3, double & oFx2y, double & oFxy2, double & oFy3
                                  )const;
   // Evaluation of function and derivatives at the same time on params
   virtual void Eval(const double u, const double v, 
                     const CATMathOption iOptions,
                     double * f,
                     double * fx =0, double * fy=0,
                     double * fx2=0, double *fxy=0, double *fy2=0 ) const;

   // Compute the fxy evaluation from fx and fy evaluations
//-------------------------------------------------------------------
   void Evalf(double fu[3], double du[3],
                     double d2u[3], double fv[3], double dv[3], double d2v[3],
                     const  CATMathOption iOption,
                     double *f, double *fx, double *fy,
           double * fx2, double *fxy, double *fy2) const;
  
//-------------------------------------------------------------------
   // Multi-evaluation of function and derivatives on a regular 
   // grid of Nu x Nv points delimited by  [uStart,uEnd] x [vStart,vEnd]
   // If NbPoints[0]=1 and/or NbPoints[1]=1 then the evaluations
   // are made on the smallest corresponding coordinate in iDomain
   // WARNING : the pointers must be previously allocated if the
   // corresponding evaluations are needed.
   // The value f[Nv*i+j] contains Eval(x_i,y_j) ...
   //
   virtual void Eval(const CATMathIntervalND & iDomain, const CATLONG32 * NbPoints,
                     const CATMathOption iOptions,
                     double * f,
                     double * fx =0, double * fy=0,
                     double * fx2=0, double *fxy=0, double *fy2=0) const;
   
   //-----------------------------------------------------------------
   // Evaluators on intervals
   //-----------------------------------------------------------------

   virtual CATMathInterval Eval(const CATMathInterval & Du,
    const CATMathInterval & Dv, const CATTolerance & iTolObject=CATGetDefaultTolerance()) const;
   virtual CATMathInterval EvalFirstDerivX(const CATMathInterval & Du,
                                           const CATMathInterval & Dv) const;
   virtual CATMathInterval EvalFirstDerivY(const CATMathInterval & Du,
                                           const CATMathInterval & Dv) const;
   
   virtual CATMathInterval EvalSecondDerivX2(const CATMathInterval & Du,
                                             const CATMathInterval & Dv) const;
   virtual CATMathInterval EvalSecondDerivXY(const CATMathInterval & Du,
                                             const CATMathInterval & Dv) const;
   virtual CATMathInterval EvalSecondDerivY2(const CATMathInterval & Du,
                                             const CATMathInterval & Dv) const;

   virtual void Eval(const CATMathInterval & Du, const CATMathInterval & Dv,
                     const CATMathOption iOptions, CATMathInterval * f,
                     CATMathInterval * fx =0, CATMathInterval * fy=0,
                     CATMathInterval * fx2=0, CATMathInterval *fxy=0, 
                     CATMathInterval *fy2=0, const CATTolerance & iTolObject=CATGetDefaultTolerance()) const;

   virtual CATMathDiagnostic Minimize(const CATMathInterval2D & D,
                                      CATMathSetOfPointsND & roots,
                                      const CATMathAttrList * attributes,
                                      CATSoftwareConfiguration* iConfig=NULL
                                     ) const;

};

#endif
