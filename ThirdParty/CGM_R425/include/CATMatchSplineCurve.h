/*-*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATCrvQuinticInterpolation :
// Interface class of the CATCrvQuinticInterpolationCx2.
//
//=============================================================================
// Usage notes:
// sample of use :
//
//=============================================================================
// Sep   99 NDN Creation                                                    NDN
// 05/07/16 NLD Suppression du vieux Create sans configuration
// 06/07/16 NLD Ajout CATCreateMatchSplineCurve() avec iTolObject, pour XScale,
//              et sans iMode (en desuetude)
// 18/07/16 NLD Suppression definitive de l'ancien createur inactif
//=============================================================================
#ifndef CATMatchSplineCurve_H 
#define CATMatchSplineCurve_H

#include "CATSkillValue.h"
#include "YN000FUN.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"
#include "CATTolerance.h"
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;

//-----------------------------------------------------------------------------
class ExportedByYN000FUN CATMatchSplineCurve : public CATCGMVirtual
{
  public :
  
  virtual                   ~CATMatchSplineCurve() {};
   
  virtual void              Run() =0;

  virtual void              SetExactNorm       (CATLONG32   StartTg = 1,
                                                CATLONG32   EndTg   = 1,
                                                CATLONG32   StartDs = 1,
                                                CATLONG32   EndDs   = 1) =0;

  virtual void              SetStartTargetPoint(double    * PtStart ,
                                                double    * TgStart = 0,
                                                double    * DsStart = 0,
                                                CATLONG32 * EndIndexForStartDeformation = 0) =0;

  virtual void              SetEndTargetPoint  (double    * PtEnd   ,
                                                double    * TgEnd   = 0,
                                                double    * DsEnd   = 0,
                                                CATLONG32 * StartIndexForEndDeformation = 0) =0;

  // TabOfImpositions of size ioparameter, represent the kind of imposition for each param.
  // value is 0 -> No imposition , 1 -> Impose point , 2 -> Impose Tg , 4 -> Impose Ds.
  // For example : 5 i.e. imposition of point and second derivative. Dimension for the CATMathSetOfPointsND
  // is the same than ioparameter.
  // ExactNorm don't need to be allocated, default is imposition of norm of vectors. Else for each index you can set
  // ExactNorm=1 if you want to impose the exact norm, 0 if you want the operator to estimate the norm.
  // Warning : Don't try to impose twice the same point, using previous methods and this one, it could lead
  // to unwanted result...
  virtual void              SetImpositions(CATLONG32            * TabOfImpositions,
                                           CATMathSetOfPointsND * ImposedPoints,
                                           CATMathSetOfPointsND * ImposedTg = 0, CATLONG32 * ExactNormTg = 0,
                                           CATMathSetOfPointsND * ImposedDs = 0, CATLONG32 * ExactNormDs = 0) = 0;

  // If you set tolerance, the operator will try to converge toward the solution within the tolerance allowed.
  // Warning : Chech if your tolerance is smaller than the max gap you give through your impositions. Else
  // the max gap will be chosen instead of the input tolerance.
  virtual void              SetTolerance(double iTolerance) =0;

  // If you want to impose a Least Square constraint, eg minimize the distance toward a point with an associated
  // parameter that doesn't correspond to any imposed parameter.
  // Warning : This point may not be reach.
  // virtual void SetLeastSquareConstraint(double * iParam,CATMathSetOfPointsND * iLSPoints) =0;
};

//=============================================================================
ExportedByYN000FUN CATMatchSplineCurve * CATCreateMatchSplineCurve(const CATTolerance             & iTolObject         ,
                                                                         CATSoftwareConfiguration * iConfig            ,
                                                                         CATMathSetOfPointsND     * ioparameter        ,
                                                                         CATMathSetOfPointsND     * ioPoints           ,
                                                                         CATMathSetOfPointsND     * ioFirstDerivatives ,
                                                                         CATMathSetOfPointsND     * ioSecondDerivatives
                                                                  );

ExportedByYN000FUN void Remove(CATMatchSplineCurve *&iMove);


//Tools to work on ND Splines.
ExportedByYN000FUN void KnotInsertion(      CATLONG32              iPosition ,
                                            double                 iParam    ,
                                            CATMathSetOfPointsND & ioParam   ,
                                            CATMathSetOfPointsND & ioPt      ,
                                            CATMathSetOfPointsND & ioFirstDer,
                                            CATMathSetOfPointsND & ioSecDer  );

ExportedByYN000FUN void EvalQuintic  (      CATLONG32              arc       ,
                                            double                 locparam  ,
                                            double                 Delta     ,
                                      const CATMathSetOfPointsND & Pt        ,
                                      const CATMathSetOfPointsND & Tg        ,
                                      const CATMathSetOfPointsND & Ds        ,
                                            double               * ResultPt  ,
                                            double               * ResultFirstDer,
                                            double               * ResultSecDer);
#endif
