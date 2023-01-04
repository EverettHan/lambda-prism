// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATMathMinimizeRN:
//  Class used to minimize functions of N variables
//
//=============================================================================
// Usage notes:
//
// XScaleRules:                                                                                 (NLD030714)
// 1) standard behaviour
//  - domains         must behave like power 1 of factory scale
//  - parameters      must behave like power 1 of factory scale
//  - function        must behave like power 2 of factory scale
//  - steps  computed must behave like power 1 of factory scale
// 2) other behaviours forbidden
//  - standard behaviour is mandatory: no CATMathAttrScaleOption attribute taken into account for now

//=============================================================================
// 17/10/11 NLD Ajout _Config et _CGMLevel, ajout iConfig dans constructeur
//              L'argument iTolObject devient obligatoire
// 03/07/14 NLD Ajout XScaleRules
//              Smart indent
//=============================================================================
#ifndef CATMathMinimizeRN_H
#define CATMathMinimizeRN_H

#include "YN000FUN.h"

#include "CATMathIntervalND.h"
#include "CATMathDef.h"
#include "CATMathDiagnostic.h"
#include "CATCGMVirtual.h"
#include "CATTolerance.h"

class CATMathSetOfPointsND;
class CATMathAttrList;
class CATMathFunctionRN;
class CATSoftwareConfiguration;

#include <string.h>


//-------------------------------------------------------------------
class ExportedByYN000FUN CATMathMinimizeRN : public CATCGMVirtual
 {
// public methods
 public: 
  //-----------------------------------------------------------------
  // Object management
  //-----------------------------------------------------------------

           CATMathMinimizeRN               (const CATMathFunctionRN       *  iF         ,
                                            const CATTolerance             & iTolObject ,
                                                  CATSoftwareConfiguration*  iConfig
                                           );

  virtual ~CATMathMinimizeRN();
  //
  //-----------------------------------------------------------------
  // Minimize
  // Min F(x) where x is in the given Domain.
  // The minimization takes the bounds of the Domain in account.
  //-----------------------------------------------------------------
  //
  virtual CATMathDiagnostic Minimize       (const CATMathIntervalND        & iD         ,
                                                  CATMathSetOfPointsND     & ioRoots    ,
                                            const CATMathAttrList         *  attributes = 0) const;
  //
  //--------------------------------------------------------------------
  // Convergence on nul gradient
  //
  // Use the newton iteration on the gradient to find a solution
  // 0 is returned if no solution where found
  // 1 is returned if a solution was found, the solution is X
  //----------------------------------------------------------------------
  //
  virtual CATBoolean        MinimizeNewton (      double                  *  ioX        ,
                                            const CATMathIntervalND        & iD         ) const;
  //
  //--------------------------------------------------------------------
  // Convergence on nul gradient
  //
  // Use the BFGS iteration to find a solution
  // 0 is returned if no solution where found
  // 1 is returned if a solution was found, the solution is x
  //----------------------------------------------------------------------
  //
  virtual CATBoolean        MinimizeBFGS   (      double                  *  ioX        ,
                                            const CATMathIntervalND        & iD         ) const;

protected:
  //
  // Univariable minimization : Min _F (iX + Mu*iDir) (Mu is the parameter)
  // The "minimum" is at point of parameter ioMuOpt and verifies the
  // Wolfe-Powell conditions.
  //
          void              UniMin         (const double                     iNormX2    ,
                                            const double                     iNormGX2   ,
                                                  CATLONG32                & info       ,
                                            const double                  *  iX         ,
                                                  double                   & iofX       ,
                                                  double                  *  iogfX      ,
                                            const double                  *  iDomain    ,
                                                  double                  *  iDir       ,
                                                  double                   & ioMuOpt    ,
                                                  double                  *  ioMem      ) const ;
  //
  // The BFGS update formula (update of the inverse of an approximation
  // of the inverse of the hessian ioH. (idx = variation of X, idg variation
  // of the gradient)
  //
          void              UpdateH        (      double                     iNormX2    ,
                                                  double                     iNormGX2   ,
                                                  double                  *  idX        ,
                                                  double                  *  idg        ,
                                                  double                  *  ioH        ,
                                                  double                  *  ioMem      ) const;

  //
  // Data
  //
  const CATMathFunctionRN        *   _F;
        CATLONG32                    _N;

  const CATTolerance              &  _Tol;
        CATSoftwareConfiguration *   _Config;
        int                          _CGMLevel;
};

#endif
