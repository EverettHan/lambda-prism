// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATMathSystemReturningPoints:
//  class used to find initialization points for surface surface intersection
//
//=============================================================================
//
// Usage Notes:
//
// This class is a system S : (u,v,r,s) -> R4  whose solutions S(u,v,r,s)=0
// give the returning points of the intersection of two surfaces F and G, 
// that is it gives the points (u,v,r,s) such that :
//   - F(u,v) = G(r,s)
//   - the trace on G of the intersection of F and G has a tangent at (r,s)
//     which is parallel to a given direction. In mathematical words :
//
//     N[0]*(alpha*Gr[0]+Gs[0]) + N[1]*(alpha*Gr[1]+Gs[1]) + N[2]*(alpha*Gr[2]+Gs[2]) = 0
//
//     where * N[i] are the coordinates of the normal of F at (u,v),
//           * Gr[i], Gs[i] are the partial derivatives of G at (r,s)
//           * alpha is such that the given direction to which parallel 
//             are looked for is (1,-alpha) in (r,s). alpha has been choosed to be
//             a transcendantal value to avoid ill conditionned systems.
//
//   - Sometimes, to go faster, only points such that the tangent has the same
//     sense as the given direction are returned. Im mathematical words, if
//
//     W = N[0]*(Gr[0]-alpha*Gs[0]) + N[1]*(Gr[1]-alpha*Gs[1]) + N[2]*(Gr[2]-alpha*Gs[2]) < 0
//
//     then we consider that the tangent has not the right direction and we decide not
//     to find the solution. The reason is that on a closed loop of the intersection of F
//     and G, at least two solutions of the system S exists, and give opposite sign for W.
//
// XScaleStatus/XScaleRules:                                                                    (NLD090616)
// 1) standard behaviour
//  - domains         must behave like power 1 of factory scale
//  - parameters      must behave like power 1 of factory scale
//  - function        must behave like power 1 of factory scale
//  - steps  computed must behave like power 1 of factory scale
//
// 2) for a system not following standard behaviour:
//  Scale behaviour may be defined by two means (from best way to worst)
//  - specify a CATMathAttrScaleOption attribute through attributes list at constructor call 
//  - use SetScaleOption()
//
//  CAUTION:
//  anyway: THIS system, when taking standard and homogeneous functions,
//  builds an internal system in which fourth function coordinates
//  has a different behaviour
//  see CATMultiThreadSurSurGen::LocalReturningPoint for example,
//  in which we have
//    CATLONG32 PowerScaleF[4] =  {1,1,1,0};
//    CATLONG32 PowerScaleX[4] =  {1,1,1,1};
//
//  CAUTION:
//  absolutely not guaranteed if any of the four parameters does not behave like power 1 of factory scale
//
//=============================================================================
// xx/xx/xx xgn Creation
// 26/05/16 NLD Mise au propre
//              - detabulation
//              - smart indent
//              - mise en conformite d'ecriture avec la classe mere CATMathSystem
//              - suppression de la valeur par defaut de l'argument iTolObject du constructeur
// 27/05/16 NLD Preparation versionning
//              - ajout _LocalConfig;
//              - ajout nouveau constructeur avec configuration et arguments reordonnes
//                (l'ancien ayant vocation a disparaitre tres rapidement)
//              - ajout du destructeur
// 03/06/16 NLD Debranchement du vieux constructeur
// 09/06/16 NLD Suppression de _LocalConfig (on utilise la donnee _SytemConfig dorenavant disponible dans la classe mere)
//              Ajout de classes amies pour besoins fins d'implementation
//              - ajout CATMathSystemSpecialPointsForReturningPointsAttributes
//              - ajout CATMathSystemSpecialPointsForReturningPoints
//              Ajout XScaleStatus/XScaleRules
// 10/06/16 NLD Suppression definitive de l'ancien constructeur sans configuration
// 01/07/16 NLD Renommage de _EquationNumberReached en _EquationIndexReached
//=============================================================================


#ifndef CATMathSystemReturningPoints_H
#define CATMathSystemReturningPoints_H

#include "CATMathDef.h"
#include "CATMathSystem.h"
#include "CATMathInterval.h"

class CATMathFunctionXY;
class CATMathNxNFullMatrix;
class CATMathIntervalND;
class CATSoftwareConfiguration;
class CATMathSystemSpecialPointsForReturningPoints;
class CATMathSystemSpecialPointsForReturningPointsAttributes;

//-----------------------------------------------------------------------------
#include "YN000FUN.h"
class ExportedByYN000FUN CATMathSystemReturningPoints : public CATMathSystem 
{
 friend class CATMathSystemSpecialPointsForReturningPoints;
 friend class CATMathSystemSpecialPointsForReturningPointsAttributes;
 public:

  virtual                              ~CATMathSystemReturningPoints();

// New constructor. NLD270516
                                        CATMathSystemReturningPoints(      CATSoftwareConfiguration *  iConfig           ,
                                                                     const CATTolerance              & iTolObject        ,
                                                                     const CATMathFunctionXY        *  iFunctionSur1[3]  ,
                                                                     const CATMathFunctionXY        *  iFunctionSur2[3]  ,
                                                                     const CATMathAttrList          *  attributes        = NULL);


   // Solve is derived to handle specific attributes
          CATMathDiagnostic             Solve                       (const CATMathIntervalND         & iUserDomain       , 
                                                                           CATMathSetOfPointsND      & oSolutions        ,
                                                                     const CATMathAttrList          *  iAttributes       = 0);

  /************************************************************************/
  /* Evaluators: iX is a point in R4.                                     */
  /*  . oFX = F(iX) is the image of iX by F. oFX is in R4 and is already  */
  /*    allocated.                                                        */
  /*  . oJacobianFX is the jacobian of F at iX and is a 4x4 Matrix already*/
  /*     allocated                                                        */
  /*                                                                      */
  /************************************************************************/

  virtual void                          Eval                        (const double                   *  iX                ,
                                                                           double                   *  oFX               );

  virtual void                          Eval                        (const double                   *  iX                ,
                                                                           double                   *  oFX               ,
                                                                           CATMathNxNFullMatrix     *  oJacobianFX       );
   
protected:

  virtual CATLONG32                     FSolve                      (const CATMathIntervalND         & iScaledDomain     ,
                                                                     const CATLONG32                *  Sampling          );

  // Classic Discretization solver
  virtual CATLONG32                     DSolve                      (const CATMathIntervalND         & iScaledDomain     ,
                                                                     const CATLONG32                *  Sampling          ,
                                                                     const char                     *  TestSubGrid       = 0);


  // specific (not in mother class CATMathSystem)
  virtual CATLONG32                     SolveOnIsopar               (const CATMathIntervalND         & iScaledDomain     ,
                                                                           double                   *  ioSolution        ,
                                                                     const CATLONG32                   iVariableIndexFixed);



private:

  virtual CATLONG32                     SubDSolve                   (const CATMathIntervalND         & iScaledDomain     ,
                                                                     const double                   *  F0u               ,
                                                                     const double                   *  F0v               ,
                                                                     const double                   *  G0r               ,
                                                                     const double                   *  G0s               ,
                                                                     const double                      mG0               ,
                                                                     const double                      MG0               ,
                                                                     const CATLONG32                   iGIndex           );

          void                          ComputeTangentField         (const double                   *  iX                ,
                                                                           double                   *  oTX               );

          int                           IsStandardScale             () ; //NLD220108 indique si on est au scale option standard attendu

          CATBoolean                    ProjectionOnPatch           (const CATMathFunctionXY       **  FF                ,
                                                                     const CATMathFunctionXY       **  GG                ,
                                                                           double                    & u                 ,
                                                                           double                    & v                 ,
                                                                     const double                      uMin              ,
                                                                     const double                      uMax              ,
                                                                     const double                      vMin              ,
                                                                     const double                      vMax              ,
                                                                     const double                      r                 ,
                                                                     const double                      s                 ,
                                                                           double                    & alpha             ,
                                                                           double                    & betaX             ,
                                                                           double                    & betaY             );

          CATBoolean                    TryWithPatch                (const CATMathIntervalND         & iScaledDomain     ,
                                                                     const double                      mG             [3],
                                                                     const double                      MG             [3],
                                                                     const CATLONG32                   iGIndex           );


          CATLONG32                     LagrangeNearSingularity     (const CATMathIntervalND         & iScaledDomain     ,
                                                                     const CATLONG32                   VarNbr            ,
                                                                     const CATMathFunctionXY       **  FF                ,
                                                                     const CATMathFunctionXY       **  GG                ,
                                                                           double                    & u                 ,
                                                                           double                    & v                 ,
                                                                     const double                      uMin              ,
                                                                     const double                      uMax              ,
                                                                     const double                      vMin              ,
                                                                     const double                      vMax              ,
                                                                     const double                      tFixed            ,
                                                                           double                      w0                ,
                                                                           double                      w1                ,
                                                                           double                    & w                 ,
                                                                           double                      alpha0            ,
                                                                           double                      alpha1            ,
                                                                           double                      Sol[4]            );

          void                          ReconvergeOnSpecialPoint    (      double                   *  ioSolution        );


protected:
        CATLONG32                 _Orientation;
  const CATMathFunctionXY       * _Function1[3];
  const CATMathFunctionXY       * _Function2[3];

private:
   CATLONG32                      _DSolveDepthMax;

  double                          _uMinLocal,
                                  _uMaxLocal,
                                  _vMinLocal,
                                  _vMaxLocal;
  CATLONG32                       _EquationIndexReached;
  double                          _Fu       [3][4],
                                  _Fv       [3][4];
  double                          _MinF     [3],
                                  _MaxF     [3];
  char                          * _TestG    [3];
  double                        * _Gr       [3][4],
                                * _Gs       [3][4];
  double                        * _MinG     [3],
                                * _MaxG     [3];

  CATBoolean                      _IsImageIsoparF[8];
  CATMathInterval                 _ImageIsoparF  [8][3];

};

#endif  
