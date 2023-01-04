/*-*-C++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATFrFUtiNurbs :
// Global Fonctions for NUPBS Curves and Surfaces for computing l2 and L2 square norms
//
// for a nupbs curve : C(u)  = sum_on_i (ControlPoint[i] * B[i](u))
// square l2 norm : mat(i,j) = sum_on_k (B[j] * B[k])(u[i])
// square L2 norm : mat(i,j) = sum_on_k { Integral{(B[j] * B[k])(u[i])} }
//
// for a nupbs surface : S(u,v) = sum_on_i(sum_on_j(ControlPoint[i,j] * BU[i](u) * BV[j](v)))
// square l2 or L2 norm : MAT(i,j) = outer_product(matV,matU)
//=============================================================================
// Usage notes:
// sample of use :
// to provide
//
//=============================================================================
//    01/98 NDN Creation                                                    NDN
// 21/05/14 NLD Reprise en main
//              - Detabulation
//              - Smart indent
//              - Les shunts sont pilotes par #ifdef
//              - Remise en etat de compilation de la classe CATMinimizeWithConstraints()
//                avec _TolObject et argument iTolObject au constructeur
//              - Suppression definitive des versions inactives sans argument de break
//                de ReductionMatrixForCrv()
//=============================================================================
#ifndef CATFrFUtiNurbs_H 
#define CATFrFUtiNurbs_H 

#include "YP00IMPL.h"
#include "CATKnotVector.h"
#include "CATMathMxNFullMatrix.h"
#include "CATMathNxNFullSymMatrix.h"
#include "CATMathNxNBandSymMatrix.h"
#include "CATMathPolynomX.h"
#include "CATTolerance.h"
#include <stdlib.h>

//=============================================================================
// Shunt des methodes non utilisees, non couvertes
   #define CATFrFUtiNurbs_ShuntNDNCoverage141205_L2NormForSurBandCase
   #define CATFrFUtiNurbs_ShuntNDNCoverage141205_CATMinimizeWithConstraints
   #define CATFrFUtiNurbs_ShuntNDNCoverage141205_L2NormForCrvForOneArc

//-----------------------------------------------------------------------------
// Eval Nubs Basis for an array of parameters for all arcs
//-----------------------------------------------------------------------------
ExportedByYP00IMPL
void                   BasisValuesForAllArcs(const CATKnotVector        *  Kv              ,
                                                   double               *  param           ,
                                                   CATMathMxNFullMatrix *  Eval            ,
                                                   CATMathMxNFullMatrix *  EvalFirstDeriv  = NULL,
                                                   CATMathMxNFullMatrix *  EvalSecondDeriv = NULL,
                                                   CATMathMxNFullMatrix *  EvalThirdDeriv  = NULL ,
                                             const CATTolerance          & iTolObject      = CATGetDefaultTolerance()
                                            );

ExportedByYP00IMPL
void                   BasisValuesForAllArcs(const CATKnotVector        *  KvU             ,
                                             const CATKnotVector        *  KvV             ,
                                                   CATLONG32               Nb_disc         ,
                                                   double               *  ParametersU     ,
                                                   double               *  ParametersV     ,
                                                   CATMathMxNFullMatrix *  Eval            ,
                                                   CATMathMxNFullMatrix *  EvalFirstDeriv  = NULL,
                                                   CATMathMxNFullMatrix *  EvalSecondDeriv = NULL,
                                                   CATMathMxNFullMatrix *  EvalThirdDeriv  = NULL,
                                             const CATTolerance  &   iTolObject      = CATGetDefaultTolerance()
                                            );

//-----------------------------------------------------------------------------
// Eval L2 norm for Nubs Basis, and derivatives :  Mat(n)(i,j) = Integral(Derivative(n)(Bi)*Derivative(n)(Bj))
// where Derivative(n)(Bi) means the n derivative of basis Bi.
//-----------------------------------------------------------------------------
ExportedByYP00IMPL
void                   L2NormForCrv         (const CATKnotVector           *  Kv              ,
                                                   CATMathNxNFullSymMatrix *  Eval            ,
                                                   CATMathNxNFullSymMatrix *  EvalFirstDeriv  = NULL,
                                                   CATMathNxNFullSymMatrix *  EvalSecondDeriv = NULL,
                                                   CATMathNxNFullSymMatrix *  EvalThirdDeriv  = NULL
                                            );

ExportedByYP00IMPL
void                   L2NormForSur         (const CATKnotVector           *  KvU             ,
                                             const CATKnotVector           *  KvV             ,
                                                   CATMathNxNFullSymMatrix *  Eval            ,
                                                   CATMathNxNFullSymMatrix *  EvalFirstDeriv  = NULL,
                                                   CATMathNxNFullSymMatrix *  EvalSecondDeriv = NULL,
                                                   CATMathNxNFullSymMatrix *  EvalThirdDeriv  = NULL
                                            );


//-----------------------------------------------------------------------------
// Same computation but output is a band matix. Band width is equal degree+1.
//-----------------------------------------------------------------------------
ExportedByYP00IMPL
void                   L2NormForCrv         (const CATKnotVector           *  Kv              ,
                                                   CATMathNxNBandSymMatrix *  Eval            ,
                                                   CATMathNxNBandSymMatrix *  EvalFirstDeriv  = NULL,
                                                   CATMathNxNBandSymMatrix *  EvalSecondDeriv = NULL,
                                                   CATMathNxNBandSymMatrix *  EvalThirdDeriv  = NULL
                          );
#ifndef CATFrFUtiNurbs_ShuntNDNCoverage141205_L2NormForCrvForOneArc
ExportedByYP00IMPL
void                   L2NormForCrvForOneArc(const CATKnotVector           *  Kv              ,
                                                   CATLONG32                  RankOfArc       ,
                                                   CATMathNxNFullSymMatrix *  Mat1            ,
                                                   CATMathNxNFullSymMatrix *  Mat2            ,
                                                   CATMathNxNFullSymMatrix *  Mat3            ,
                                                   CATMathNxNFullSymMatrix *  Mat4
                                            );
#endif

#ifndef CATFrFUtiNurbs_ShuntNDNCoverage141205_L2NormForSurBandCase
ExportedByYP00IMPL
void                   L2NormForSur         (const CATKnotVector           *  KvU             ,
                                             const CATKnotVector           *  KvV             ,
                                                   CATMathNxNBandSymMatrix *  Eval            ,
                                                   CATMathNxNBandSymMatrix *  EvalFirstDeriv  = NULL,
                                                   CATMathNxNBandSymMatrix *  EvalSecondDeriv = NULL,
                                                   CATMathNxNBandSymMatrix *  EvalThirdDeriv  = NULL
                                            );
#endif

// Reduce the freedom degree of a Nurbs Curve for knot removal from C0 to TargetContinuity
// TargetContinuity = 1 ou 2

// if you want to specify the knots C0 where you want TargetContinuity use break input data
ExportedByYP00IMPL
CATMathMxNFullMatrix * ReductionMatrixForCrv(const CATKnotVector           *  Kv              ,
                                                   CATLONG32                  TargetContinuity,
                                                   CATLONG32                  NbOfBreaksC0ToCi= 0,
                                             const CATLONG32               *  BreaksC0ToCi    = NULL);

// TargetContinuity = 1 ou 2
// if you don't specify NbBreaks nor Breaks, all knot C0 are to become TargetContinuity
ExportedByYP00IMPL
CATMathMxNFullMatrix * ReductionMatrixForSur(const CATKnotVector           *  KvU             ,
                                             const CATKnotVector           *  KvV             ,
                                                   CATLONG32                  TargetContinuity,
                                                   CATLONG32                  NbBreaksU       = 0,
                                             const CATLONG32               *  BreaksU         = NULL,
                                                   CATLONG32                  NbBreaksV       = 0,
                                             const CATLONG32               *  BreaksV         = NULL,
                                             const CATTolerance             & iTolObject      = CATGetDefaultTolerance()
                                            );

// Composition des 2 matrices elementaires de reduction (PRG-Loft)
ExportedByYP00IMPL
CATMathMxNFullMatrix * ReductionMatrixForSur(const CATMathMxNFullMatrix    *  SmallMatU       ,
                                             const CATMathMxNFullMatrix    *  SmallMatV       ,
                                             const CATTolerance             & iTolObject      = CATGetDefaultTolerance()
                                            );


////////////////////////////////////////////////////////////////////
///Class for minimizing quadratic systems with linear constraints///
////////////////////////////////////////////////////////////////////
#ifndef CATFrFUtiNurbs_ShuntNDNCoverage141205_CATMinimizeWithConstraints
class ExportedByYP00IMPL CATMinimizeWithConstraints
{
  public  :

  CATMinimizeWithConstraints                (const CATTolerance             & iTolObject      ,
                                             const CATMathNxNFullSymMatrix *  Minimizer       ,
                                             const double                  *  SecMemberMin    ,
                                             const CATMathMxNFullMatrix    *  Constraints     ,
                                             const double                  *  SecMemberConst  ,
                                                   CATLONG32                  Dimension       ,
                                                   double                  *  Solution
                                            );

  ~CATMinimizeWithConstraints() {};

  void SetMaxIterations(CATLONG32 MaxIter) //Default is 10
    {
     _MaxIter = (MaxIter > 0 && MaxIter < 100) ? MaxIter : _MaxIter;
    };

  void SetTolerance(double Tol) //Default is CATEpsg
    {
      _Tol = (Tol > 0) ? Tol : _Tol;
    };

  void SetEllipticity(double Ellipt) //Enhance operator
    {
     _Ellipt = (Ellipt > 0) ? Ellipt : _Ellipt;
    };

  void SetConstraintNorm(double NormC) //Enhance operator
    {
     _NormC = (NormC > 0) ? NormC : _NormC;
    };

  double GetError()
    {
     return _Erreur;
    };
  
  void   Run    (); //Mandatory!


  private :

  const CATTolerance             &_TolObject;
  const CATMathNxNFullSymMatrix * _OpeJ;
  const CATMathMxNFullMatrix    * _Const;
  const double                  * _SecJ;
  const double                  * _SecConst;
  double                        * _Sol;

  double                          _Tol;
  double                          _Erreur;
  double                          _Ellipt;
  double                          _NormC;
  CATLONG32                       _MaxIter;
  CATLONG32                       _Dim;
  CATLONG32                       _Taille;
  CATLONG32                       _NbConstraints;
};

#endif
#endif


