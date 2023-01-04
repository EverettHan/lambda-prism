// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATMathSystem3x3s:
//  Class derived from CATMathSystem used to Solve a SEPARATE system 3x3 of
//  the form :
//    FX(u,v) - GX(w) = 0
//    FY(u,v) - GY(w) = 0
//    FZ(u,v) - GZ(w) = 0
//
//
//=============================================================================
//
// Usage Notes:
//
// Two pure virtual methods must be overloaded in derived classes :
//
//    double EvalEquationF(const CATLONG32 iEquationIndex ,
//                         const double u, const double v);
//    double EvalEquationG(const CATLONG32 iEquationIndex ,
//                         const double w);
//
//  For much better performance, overload the other evaluators concerning F and G
//  (EvalEquationF, EvalEquationG, EvalF, EvalG, ...)
//
//  The evaluators of CATMathSystem do not need to be overloaded (Eval, ...)
//
//=============================================================================
// 03/06/16 NLD Mise au propre
//              - detabulation
//              - smart indent
//              - mise en conformite d'ecriture avec la classe mere CATMathSystem
//              - suppression de la valeur par defaut de l'argument iTolObject du constructeur
//              - recensement des derivations / non derivations par rapport a la classe mere
//              Preparation versionning
//              - ajout nouveau constructeur avec configuration et arguments reordonnes
//                (l'ancien ayant vocation a disparaitre tres rapidement)
//              - ajout du destructeur
// 06/06/16 NLD Ajout _h1 et _h2;
//              Ajout Init()
// 01/07/16 NLD Changement de notations:
//              - iEquationIndex  remplace iEquationNumber
//              - iVariableIndex  remplace iVariableNumber
//              - iVariableIndex1 remplace iVariableNumber1
//              - iVariableIndex2 remplace iVariableNumber2
//=============================================================================


#ifndef CATMathSystem3x3s_H
#define CATMathSystem3x3s_H

#include "YN000FUN.h"

#include "CATMathSystem.h"
#include "CATMathDef.h"
#include "CATMathDiagnostic.h"
#include "CATMathInterval.h"

class CATMathIntervalND;
class CATMathNxNFullMatrix;
class CATSoftwareConfiguration;

// Migration sur nouveau constructeur complete pour GeometricOperators, reste CVMGeometry. NLD070616
   #define CATMathSystem3x3s_KeepOldConstructor "transitoire NLD270516 avant migration complete. ATTENTION a CVMGeometry"

//-----------------------------------------------------------------------------
class ExportedByYN000FUN CATMathSystem3x3s : public CATMathSystem
{
 private:
    // Copy-Constructor (FORBIDDEN. NLD030616)
    //                                  CATMathSystem3x3s           (const CATMathSystem3x3s         & iSystemToCopy     );

 public:  

  virtual                              ~CATMathSystem3x3s           ();

  //--------------------------------------------------------------------------
  //  Constructor
  //--------------------------------------------------------------------------
                                        CATMathSystem3x3s           (      CATSoftwareConfiguration *  iConfig           ,
                                                                     const CATTolerance              & iTolObject        );
#ifdef CATMathSystem3x3s_KeepOldConstructor
// DEPRECATED. Old constructor to remove
                                        CATMathSystem3x3s           (const CATTolerance              & iTolObject        );
 //                                                                                    // NLD030616  = CATGetDefaultTolerance());
#endif

  //--------------------------------------------------------------------------
  // Information methods
  //--------------------------------------------------------------------------

  virtual CATBoolean                    IsOption                    (const CATMathOption               iOption           ) const;

  //--------------------------------------------------------------------------
  // Solver
  //--------------------------------------------------------------------------
  
  //--------------------------------------------------------------------------
  // Evaluators on points in RN
  // These evaluators do not need to be overloaded in derived classes
  //--------------------------------------------------------------------------

   //
   // Evaluators: iX is a point in RN.
   //  . oFX = F(iX) is the image of iX by F. oFX is in R(N-1) and is already allocated. 
   //  . oJacobianFX is the jacobian of F at iX and is in R(N*(N-1)) 
   //    and is already allocated.
   //  . oTX is the tangent at iX and is in RN and is already allocated.
   //
          void                          Eval                        (const double                   *  iX                ,
                                                                           double                   *  oFX               );

          void                          EvalJacobian                (const double                   *  iX                ,
                                                                           CATMathNxNFullMatrix     *  oJacobianFX       ); 

          void                          Eval                        (const double                   *  iX                ,
                                                                           double                   *  oFX               ,
                                                                           CATMathNxNFullMatrix     *  oJacobianFX       );

 protected:

  virtual CATLONG32                     FSolve                      (const CATMathIntervalND         & iDomain           ,
                                                                     const CATLONG32                *  Sampling          );

  //--------------------------------------------------------------------------
  // Evaluators on a point of equations of SubFunctions F and G
  //--------------------------------------------------------------------------
  // (not in mother class CATMathSystem) 
  virtual double                        EvalEquationF               (const CATLONG32                   iEquationIndex    ,
                                                                     const double                      u                 ,
                                                                     const double                      v                 ) = 0;

  virtual double                        EvalFirstDerivUEquationF    (const CATLONG32                   iEquationIndex    ,
                                                                     const double                      u                 ,
                                                                     const double                      v                 );

  virtual double                        EvalFirstDerivVEquationF    (const CATLONG32                   iEquationIndex    ,
                                                                     const double                      u                 ,
                                                                     const double                      v                 );

  virtual double                        EvalSecondDerivU2EquationF  (const CATLONG32                   iEquationIndex    ,
                                                                     const double                      u                 ,
                                                                     const double                      v                 );

  virtual double                        EvalSecondDerivUVEquationF  (const CATLONG32                   iEquationIndex    ,
                                                                     const double                      u                 ,
                                                                     const double                      v                 );

  virtual double                        EvalSecondDerivV2EquationF  (const CATLONG32                   iEquationIndex    ,
                                                                     const double                      u                 ,
                                                                     const double                      v                 );

  virtual double                        EvalEquationG               (const CATLONG32                   iEquationIndex    ,
                                                                     const double                      w                 ) = 0;

  virtual double                        EvalFirstDerivEquationG     (const CATLONG32                   iEquationIndex    ,
                                                                     const double                      w                 );

  virtual double                        EvalSecondDerivEquationG    (const CATLONG32                   iEquationIndex    ,
                                                                     const double                      w                 );
  
  //--------------------------------------------------------------------------
  // Evaluators on a grid of equations of SubFunctions F and G
  //--------------------------------------------------------------------------

  virtual void                          EvalEquationF               (const CATLONG32                   iEquationIndex    ,
                                                                     const CATMathIntervalND         & iDomain           ,
                                                                     const CATLONG32                *  NbPoints          ,
                                                                           double                   *  f                 );

  virtual void                          EvalEquationF               (const CATLONG32                   iEquationIndex    ,
                                                                     const CATMathIntervalND         & iDomain           ,
                                                                     const CATLONG32                *  NbPoints          ,
                                                                           double                   *  f                 ,
                                                                           double                   *  fu                ,
                                                                           double                   *  fv                );

  virtual void                          EvalEquationG               (const CATLONG32                   iEquationIndex    ,
                                                                     const CATMathInterval           & W                 ,
                                                                     const CATLONG32                   NbPoints          ,
                                                                           double                   *  G                 );

  virtual void                          EvalEquationG               (const CATLONG32                   iEquationIndex    ,
                                                                     const CATMathInterval           & W                 ,
                                                                     const CATLONG32                   NbPoints          ,
                                                                           double                   *  G                 ,
                                                                           double                   *  Gw                );

  //--------------------------------------------------------------------------
  // MultiDeriv evaluators on a point of all equations of SubFunctions F and G
  //--------------------------------------------------------------------------
  // (not in mother class CATMathSystem) 

  //  EvalF :
  // Depending in iOption, fill arrays F, Fu, Fv, Fu2, Fuv, Fv2 containing 3 doubles with :
  //   F[0] = FX(u,v)
  //   F[1] = FY(u,v)
  //   F[2] = FZ(u,v)
  //
  //   Fu[0] = FXu(u,v)
  //   ....
  //   ....
  //   Fv2[2] = FZv2(u,v)
  //
  virtual void                          EvalF                       (const double                      u                 ,
                                                                     const double                      v                 ,
                                                                     const CATMathOption               iOption           ,
                                                                           double                   *  F                 ,
                                                                           double                   *  Fu                = 0,
                                                                           double                   *  Fv                = 0,
                                                                           double                   *  Fu2               = 0,
                                                                           double                   *  Fuv               = 0,
                                                                           double                   *  Fv2               = 0);

  //  EvalG :
  // Depending in iOption, fill arrays G, Gw, Gw2 containing 3 doubles with :
  //   G[0] = GX(w)
  //   G[1] = GY(w)
  //   G[2] = GZ(w)
  //
  //   Gw[0] = GXw(w)
  //   ....
  //   ....
  //   Gw2[2] = GZw2(w)
  //
  virtual void                          EvalG                       (const double                      w                 ,
                                                                     const CATMathOption               iOption           ,
                                                                           double                   *  G                 ,
                                                                           double                   *  Gw                = 0,
                                                                           double                   *  Gw2               = 0);

  //--------------------------------------------------------------------------
  // Evaluators on intervals of equations of SubFunctions F and G
  //--------------------------------------------------------------------------
  // (not in mother class CATMathSystem) 
  virtual CATMathInterval               EvalEquationF               (const CATLONG32                   iEquationIndex    ,
                                                                     const CATMathInterval           & U                 ,
                                                                     const CATMathInterval           & V                 );

  virtual CATMathInterval               EvalEquationG               (const CATLONG32                   iEquationIndex    ,
                                                                     const CATMathInterval           & W                 );
  
  //-----------------------------------------------------------------------
  // Specialized evaluators on points in RN for Parmeval Solver.
  // These evaluators do not need to be overloaded in derived classes
  //-----------------------------------------------------------------------
  // (all derived from mother class CATMathSystem) 
          double                        EvalEquation                (const CATLONG32                   iEquationIndex    ,
                                                                     const double                   *  iX                );

          double                        EvalFirstDerivEquation      (const CATLONG32                   iEquationIndex    ,
                                                                     const CATLONG32                   iVariableIndex    ,
                                                                     const double                   *  iX                );

          double                        EvalSecondDerivEquation     (const CATLONG32                   iEquationIndex    , 
                                                                     const CATLONG32                   iVariableIndex1   ,
                                                                     const CATLONG32                   iVariableIndex2   ,
                                                                     const double                   *  iX                );



  // The following methods appear in fact not to be used if all the others are overloaded
  //
  //   void EvalFirstDerivEquation(const CATLONG32 iEquationIndex ,
  //                               const double  * iX,
  //                                     double  * oDFX);
  //
  //   void EvalEquation          (const CATLONG32 iEquationIndex ,
  //                               const double  * iX, 
  //                                     double  & oFX,
  //                                     double  * oDFX);

          void                          EvalEquation                (const CATLONG32                   iEquationIndex    ,
                                                                     const CATMathIntervalND         & iDomain           ,
                                                                     const CATLONG32                *  iSampling         ,
                                                                           double                   *  oFX               ,
                                                                           double                   *  oDFX              );

          void                          EvalEquation                (const CATLONG32                   iEquationIndex    ,
                                                                     const CATMathIntervalND         & iDomain           ,
                                                                     const CATLONG32                *  iSampling         ,
                                                                           double                   *  oFX               );
   


  // Specialized evaluator
  virtual CATBoolean                    FindRootNearSingularity     (const CATMathIntervalND         & iDomain           );

          void                          EvalForDoubleRoot           (const double                   *  iX                ,
                                                                           double                   *  oFX               ,
                                                                           CATMathNxNFullMatrix     *  oJacobianFX       );



  // return 1 if the system can be ill conditionned
  virtual CATBoolean                    TryMarching                 (      double                   *  iInit             );

 private:
  // (not in mother class CATMathSystem) 
          void                          Init                        ();

          CATBoolean                    LocalTryNonIntersection     (      double                      umin              ,
                                                                           double                      umax              ,
                                                                           double                      vmin              ,
                                                                           double                      vmax              ,
                                                                           double                      wmin              ,
                                                                           double                      wmax              );

          CATBoolean                    ProjectionOnPatch           (      double                    & u                  ,
                                                                           double                    & v                  ,
                                                                     const double                      w                  ,
                                                                           double                    & alpha              ,
                                                                           double                    & beta               );

          CATBoolean                    LagrangeNearSingularity     (const CATMathIntervalND         & iDomain            ,
                                                                           double                      alpha0             ,
                                                                           double                      alpha1             ,
                                                                           double                      u                  ,
                                                                           double                      v                  ,
                                                                           double                      w                  );
   
          void                          EvalEquationF               (const CATLONG32                   iEquationIndex     ,
                                                                     const CATBoolean                  iDeriv             ,
                                                                     const CATMathIntervalND         & iDomain            ,
                                                                     const CATLONG32                *  NbPoints           ,
                                                                           double                   *  f                  ,
                                                                           double                   *  fu                 ,
                                                                           double                   *  fv                 );

          void                          EvalEquationG               (const CATLONG32                   iEquationIndex     ,
                                                                     const CATBoolean                  iDeriv             ,
                                                                     const CATMathInterval           & W                  ,
                                                                     const CATLONG32                   NbPoints           ,
                                                                           double                   *  G                  ,
                                                                           double                   *  Gw                 );

protected:
// Donnees:
        double                    _h1;
        double                    _h2;

};  
#endif  

