// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATMathCheapInterpol:
//   Base class for quintic polynomial C2 interpolation of an object
//   after a discretisation algorithm, with reconvergence on the parameters to 
//   have the best possible interpolation. Compared to CATMathExplicitInterpol,
//   this interpolation rely only on the point evaluation and requires less
//   evaluation (on the other hand, it is less reliable).
//
//=============================================================================
// Usage notes:
//
//  This base class works for interpolation of a N-dimensional curve defined 
//  by an explicit equation. The method EvalPoint must be overloaded.
//
//  The number of subelements generated tries to be as small as possible, with 
//  the constraint on the tolerance for the Quality evaluator.
//
//  *** NOT TO USE                       ***  NLD290416
//  *** CAUTION: no test coverage at all ***  NLD290416
//
//=============================================================================
// 11/04/08 PKC Versionning
// 25/06/08 NLD XScale. Suppression des valeurs par defaut du constructeur
// 29/04/16 NLD Mise au propre
//              - detabulation
//              - smart indent
//              - mise en conformite de presentation et d'ordre avec les classes meres
//              - deplacement des declarations de variables
// 18/04/17 NLD Equipement pour migration sur la signature standard de ComputeDataAtMiddle()
//=============================================================================


#ifndef CATMathCheapInterpol_h
#define CATMathCheapInterpol_h


// #define CATMathCheapInterpol_UseStandardComputeDataAtMiddleSignature "Etude NLD180417"

#include "YN000FUN.h"

#include "CATMathDef.h"
#include "CATMathExplicitInterpol.h"

class CATSoftwareConfiguration;
class CATMathSetOfPointsND;

class ExportedByYN000FUN CATMathCheapInterpol : public CATMathExplicitInterpol
{
public:
                     CATMathCheapInterpol      (      CATSoftwareConfiguration *  iConfig              ,
                                                      CATLONG32                   iN                   ,
                                                      double                      iTolerance           ,
                                                const CATTolerance              & iTolObject
                                               );
   
  virtual           ~CATMathCheapInterpol();
   
   //
   // From iInitialParams, which contains parameters of a discretisation
   // compute optimal nodal vector, points, tangents and secondderivatives in oResult
   // such that the interpolating Hermite quintics  have a precision at most iTolerance.
   //
   // More precisely, oParameters, oPoints, oTangents and oSecondDerivatives contain
   // a certain number K of values in R^N (in R for oParameters)
   // (usually significantly less than the number of points in iSet)
   // such that for (i>=1) :
   // * The Hermite polynomial Pi of degree 5 defined by
   //
   //   Pi (0)              = oPoints           [i-1],
   //   Pi'(0)              = oTangents         [i-1],
   //   Pi"(0)              = oSecondDerivatives[i-1],
   //
   //   Pi (oParameters[i]) = oPoints           [i],
   //   Pi'(oParameters[i]) = oTangents         [i],
   //   Pi"(oParameters[i]) = oSecondDerivatives[i],
   //
   //   verify the property : Quality(Pi(t)) < iTolerance    for t in [0,oParameters[i]]
   //
   // * P(0) and P'(0) corresponds to the starting point and tangent of iSet
   // * P(K-1) and P'(K-1) corresponds the ending point and tangent of iSet
   //
   // Comments :
   //   * Usually, oPoints[i] are point of iSet. In some rare case, some 
   //     new points are added if the required precision could not be reached.
   //   * oSecondDerivatives[i] are computed thanks to an approximation from close normed tangents.
   //   * The resulting piecewise curve defined with P0,P1,P2,... is of class C2.
   //
  virtual void       Run                       (      CATMathSetOfPointsND     & iInitialParams        ,
                                                      CATMathSetOfPointsND     & iInitialPoints        ,
                                                      CATMathSetOfPointsND     & oParameters           ,
                                                      CATMathSetOfPointsND     & oPoints               ,
                                                      CATMathSetOfPointsND     & oTangents             ,
                                                      CATMathSetOfPointsND     & oSecondDerivatives    ,
                                                      CATMathSetOfPointsND    *  oCorrespondingInitialParams = 0);
   
          CATBoolean GetErrorDiag              ();
          CATLONG32  GetTwistIndex             ();
          double     GetTwistParam             ();
   
protected:
   // 
   
  virtual CATBoolean EvalPoint                 (      double                     iParam                ,
                                                      double                  *  ioP                   ) = 0;
   
  virtual void       EstimateTangentAndSecondDeriv
                                               (const double                  *  P0                    ,
                                                const double                  *  P1                    ,
                                                      int                        Position1             ,
                                                const double                  *  P2                    ,
                                                      int                        Position2             ,
                                                      double                  *  ioT                   ,
                                                      double                  *  ioC                   );
   
  virtual void       ComputeDataAtPosition     (      CATLONG32                  InitialSetIndex       ,
                                                      double                  *  ioP                   ,
                                                      double                  *  ioT                   ,
                                                      double                  *  ioC                   );
   
// -----------------------------------------------------------------------
//  Insertion Management
// -----------------------------------------------------------------------
/**
 * Compute a new point inside the arc, and do some various controls.
 * The point is chosen at the middle in case of an implicit interpol,
 * or at parameter oParam in case of an explicit interpol.
 * The return value is 0 in case of success, -2 or another value < -2
 * corresponding to a failure diagnostic otherwise.
 */
 // ATTENTION signature differente de celle de CATMathExplicitInterpol/CATMathInterpol. NLD290416
 //           (premier parametre      const double iParam     au lieu de     double & oParam)
 //           mais la derivation CATGeodesicParallelCheapInterpol reprend la signature de CATMathExplicitInterpol/CATMathInterpol
 //
 //           en pratique:
 //             filiere de derivation 1
 //               CATMathInterpol                  declare         double & oParam mais ne fournit pas d'implementation
 //               CATMathExplicitInterpol          declare         double & oParam et prend et rend le point milieu
 // AVANT         CATMathCheapInterpol             declarait const double   iParam et utilisait la valeur recue
 // (a activer?)  CATMathCheapInterpol             declarerait     double & oParam MAIS utiliserait la valeur recue
 //               CATGeodesicParallelCheapInterpol declare         double & oParam et prend et rend le point milieu
 //             filiere de derivation 2
 //               CATMathInterpol                  declare         double & oParam mais ne fournit pas d'implementation
 //               CATMathCleverInterpol            declare         double & oParam mais n'utilise ni ne remplit oParam (ni iParam1 ni iParam2)
 //                                                                                (calcule le point milieu grace au systeme)
 //            a noter a propos des appels effectifs:
 //               CATMathInterpol fait un appel depuis AddPointAndInterpol() supposant implicitement que le parametre est une sortie
 //                                                et seulement une sortie
 //               CATGeodesicParallelCheapInterpol fait un appel avec le parametre milieu mais sa derivation
 //                                                s'empresse de recalculer en interne ce parametre milieu  
  virtual enum ConvergenceInfo ComputeDataAtMiddle (
#ifdef CATMathCheapInterpol_UseStandardComputeDataAtMiddleSignature
                                                      double                   & oParam                ,
#else
                                                const double                     iParam                ,
#endif
                                                const double                     iParam0               ,
                                                const double                     iParam1               ,
                                                const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                const double                  *  iC1                   ,
                                                      double                     iMinLength            ,
                                                      double                  *  ioPHalf               ,
                                                      double                  *  ioTHalf               ,
                                                      double                  *  ioCHalf               );
/**
 * Compute the default value for the delta parameter (before reconvergence).
 */
  virtual double     InitializeDeltaParam      (const double                     iParam0               ,
                                                const double                     iParam1               ,
                                                const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                const double                  *  iC1                   );

  virtual double     BestCheapInterpol         (      CATLONG32                  Index0                ,
                                                      CATLONG32                  Index1                ,
                                                const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                const double                  *  iC1                   ,
                                                      double                   & oDeltaParam           ,
                                                const CATLONG32                  NbSample              ,
                                                const CATBoolean                 iEasyInterpol         = 0);
   
  virtual double     QualityExplicit           (const double                     iLambda               ,
                                                const double                     iParam0               ,
                                                const double                     iParam1               ,
                                                const double                     iDeltaParam           );
   
/**
 * Return the discretization number to use to compute the deviation of the arcs
 * when splitting an arc. Default is 3 (unlike mother class CATMAthExplicitInterpol).
 */
  virtual CATLONG32  GetNbSampleInAddPoint     ();
   
private:
          CATLONG32  GetNextPoint                    (CATMathSetOfPointsND     & iInitialParams        ,
                                                      CATMathSetOfPointsND     & iInitialPoints        ,
                                                      CATLONG32                  iCurrentPoint         ,
                                                      double                     iCosMin               ,
                                                      double                  *  iOldT                 ,
                                                      CATLONG32                & oMinPoint             ,
                                                      double                   & oParam                ,
                                                      double                  *  ioP                   ,
                                                      double                  *  ioT                   ,
                                                      double                  *  ioC                   );

          CATLONG32  GetNextPointOld                 (CATMathSetOfPointsND     & iInitialParams        ,
                                                      CATMathSetOfPointsND     & iInitialPoints        ,
                                                      CATLONG32                  iCurrentPoint         ,
                                                      double                     iCosMin               ,
                                                      double                  *  iOldT                 ,
                                                      double                   & oParam                ,
                                                      double                  *  ioP                   ,
                                                      double                  *  ioT                   ,
                                                      double                  *  ioC                   );

 // ATTENTION signature differente de celle de CATMathExplicitInterpol. NLD290416
          double     GetCosAngleBetweenTangents(      CATMathSetOfPointsND     & iInitialPoints        ,
                                                const double                  *  iT0                   ,
                                                      CATLONG32                  iCurrentPoint         ,
                                                      CATLONG32                  iPoint1               );
   

          double     InterpolateWithinTol      (      CATMathSetOfPointsND     & iInitialParams        ,
                                                      CATMathSetOfPointsND     & oParameters           ,
                                                      CATMathSetOfPointsND     & oPoints               ,
                                                      CATMathSetOfPointsND     & oTangents             ,
                                                      CATMathSetOfPointsND     & oSecondDerivatives    ,
                                                      CATMathSetOfPointsND    *  oCorrespondingInitialParams,
                                                      CATLONG32                  iCurrentPoint         ,
                                                      CATLONG32                  iMinPoint             ,
                                                      CATLONG32                & ioTargetNewPoint      ,
                                                      double                     iParam0               ,
                                                      double                   & ioParam1              , 
                                                const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                      double                  *  ioP1                  ,
                                                      double                  *  ioT1                  ,
                                                      double                  *  ioC1                  ,
                                                      CATBoolean               & oPointAdded           ,
                                                      double                   & oDeltaParam           );
   

protected:
  const CATMathSetOfPointsND      * _InitialSet;
        CATBoolean                  _ErrorDiag;
        CATLONG32                   _TwistIndex;
        double                      _TwistParam;

};


#endif

