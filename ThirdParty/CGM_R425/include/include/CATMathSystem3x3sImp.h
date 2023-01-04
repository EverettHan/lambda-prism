// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATMathSystem3x3sImp:
//  Class derived from CATMathSystem3x3s used to Solve a SEPARATE system 3x3 of
//  the form :
//    FX(u,v) - GX(w) = 0
//    FY(u,v) - GY(w) = 0
//    FZ(u,v) - GZ(w) = 0
//
//  where FX,FY,FZ are CATMathFunctionXY and GX,GY,GZ are CATMathFunctionX.
//
//=============================================================================
// 03/06/16 NLD Mise au propre
//              - detabulation
//              - smart indent
//              - mise en conformite d'ecriture avec la classe mere CATMathSystem3x3s
//              - suppression de la valeur par defaut de l'argument iTolObject du constructeur
//              Preparation versionning
//              - ajout nouveau constructeur avec configuration et arguments reordonnes
//                (l'ancien ayant vocation a disparaitre tres rapidement)
// 10/06/16 NLD Suppression definitive de l'ancien constructeur sans configuration
// 01/07/16 NLD Changement de notations:
//              - iEquationIndex  remplace iEquationNumber
//=============================================================================

#ifndef CATMathSystem3x3sImp_H
#define CATMathSystem3x3sImp_H

#include "YN000FUN.h"

#include "CATMathSystem3x3s.h"
#include "CATMathDef.h"
#include "CATMathDiagnostic.h"

class CATMathFunctionX;
class CATMathFunctionXY;
class CATMathIntervalND;
class CATMathNxNFullMatrix;
class CATSoftwareConfiguration;

//-----------------------------------------------------------------------------
class ExportedByYN000FUN CATMathSystem3x3sImp : public CATMathSystem3x3s
{ 
 public:  

  //--------------------------------------------------------------------------
  //  Constructor
  //--------------------------------------------------------------------------
                                        CATMathSystem3x3sImp        (      CATSoftwareConfiguration *  iConfig           ,
                                                                     const CATTolerance              & iTol              ,
                                                                     const CATMathFunctionXY        *  FX                ,
                                                                     const CATMathFunctionXY        *  FY                ,
                                                                     const CATMathFunctionXY        *  FZ                ,
                                                                     const CATMathFunctionX         *  GX                ,
                                                                     const CATMathFunctionX         *  GY                ,
                                                                     const CATMathFunctionX         *  GZ                );
  
  //--------------------------------------------------------------------------
  // Information methods
  //--------------------------------------------------------------------------
  
          CATBoolean                    IsOption                    (const CATMathOption               iOption           ) const;

  //--------------------------------------------------------------------------
  // Solver
  //--------------------------------------------------------------------------
  
  //--------------------------------------------------------------------------
  // Evaluators on points in RN : already defined in CATMathSystem3x3s
  //--------------------------------------------------------------------------
  
 protected:

  //--------------------------------------------------------------------------
  // Evaluators on a point of equations of SubFunctions F and G
  //--------------------------------------------------------------------------
  // (derived from CATMathSystem3x3s, not in mother class CATMathSystem) 
          double                        EvalEquationF               (const CATLONG32                   iEquationIndex    ,
                                                                     const double                      u                 ,
                                                                     const double                      v                 );

          double                        EvalFirstDerivUEquationF    (const CATLONG32                   iEquationIndex    ,
                                                                     const double                      u                 ,
                                                                     const double                      v                 );

          double                        EvalFirstDerivVEquationF    (const CATLONG32                   iEquationIndex    ,
                                                                     const double                      u                 ,
                                                                     const double                      v                 );

          double                        EvalSecondDerivU2EquationF  (const CATLONG32                   iEquationIndex    ,
                                                                     const double                      u                 ,
                                                                     const double                      v                 );

          double                        EvalSecondDerivUVEquationF  (const CATLONG32                   iEquationIndex    ,
                                                                     const double                      u                 ,
                                                                     const double                      v                 );

          double                        EvalSecondDerivV2EquationF  (const CATLONG32                   iEquationIndex    ,
                                                                     const double                      u                 ,
                                                                     const double                      v                 );

          double                        EvalEquationG               (const CATLONG32                   iEquationIndex    ,
                                                                     const double                      w                 );

          double                        EvalFirstDerivEquationG     (const CATLONG32                   iEquationIndex    ,
                                                                     const double                      w                 );

          double                        EvalSecondDerivEquationG    (const CATLONG32                   iEquationIndex    ,
                                                                     const double                      w                 );

  //--------------------------------------------------------------------------
  // Evaluators on a grid of equations of SubFunctions F and G
  //--------------------------------------------------------------------------
          void                          EvalEquationF               (const CATLONG32                   iEquationIndex    ,
                                                                     const CATMathIntervalND         & iDomain           ,
                                                                     const CATLONG32                *  NbPoints          ,
                                                                           double                   *  f                 );

          void                          EvalEquationF               (const CATLONG32                   iEquationIndex    ,
                                                                     const CATMathIntervalND         & iDomain           ,
                                                                     const CATLONG32                *  NbPoints          ,
                                                                           double                   *  f                 ,
                                                                           double                   *  fu                ,
                                                                           double                   *  fv                );

          void                          EvalEquationG               (const CATLONG32                   iEquationIndex    ,
                                                                     const CATMathInterval           & W                 ,
                                                                     const CATLONG32                   NbPoints          ,
                                                                           double                   *  G                 );

          void                          EvalEquationG               (const CATLONG32                   iEquationIndex    ,
                                                                     const CATMathInterval           & W                 ,
                                                                     const CATLONG32                   NbPoints          ,
                                                                           double                   *  G                 ,
                                                                           double                   *  Gw                );

  //--------------------------------------------------------------------------
  // MultiDeriv evaluators on a point of all equations of SubFunctions F and G
  //--------------------------------------------------------------------------

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
          void                          EvalF                       (const double                      u                 ,
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
          void                          EvalG                       (const double                      w                 ,
                                                                     const CATMathOption               iOption           ,
                                                                           double                   *  G                 ,
                                                                           double                   *  Gw                = 0,
                                                                           double                   *  Gw2               = 0);
  

  //--------------------------------------------------------------------------
  // Evaluators on intervals of equations of SubFunctions F and G
  //--------------------------------------------------------------------------
          CATMathInterval               EvalEquationF               (const CATLONG32                   iEquationIndex    ,
                                                                     const CATMathInterval           & U                 ,
                                                                     const CATMathInterval           & V                 );

          CATMathInterval               EvalEquationG               (const CATLONG32                   iEquationIndex    ,
                                                                     const CATMathInterval           & W                 );
  
protected:
  const CATMathFunctionXY * _F[3];
  const CATMathFunctionX  * _G[3];

};
#endif  

