// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATMathMinimizeXY:
//  Class used to minimize functions of two variables
//
//
// XScaleRules:                                                                                 (NLD021213)
//  - there is no ScaleOption (of typeCATMathAttrScaleOption) describing the system to solve :
//    scale behaviour is imposed
//  - domains         must behave like power 1 of factory scale
//  - parameters      must behave like power 1 of factory scale
//  - function        must behave like power 2 of factory scale <--- WARNING
//  - steps  computed must behave like power 1 of factory scale
// (if function does not follow these rules, use CATMathFunctionXY::Minimize() method and provide a scale option attribute)
//
//=============================================================================
// 07/01/08 NLD Ajout _OKScaleReviewed et SetOKScaleReviewed() pour exclusion du controle des attributs deja certifies
// 02/04/08 NLD Ajout tactique ForceLocalMinBugCorrected()
// 02/04/08 NLD Ajout _ParallelDebugChecked, _NbUnReviewedAttributes
//              Ajout CATMathMinimizeXYParallelDebugCond()
// 28/01/09 NLD Ajout _Config, ajout SoftwareConfiguration en argument du constructeur
// 18/07/11 NLD Ajout LocalMinimizationStoreEval()
// 20/07/11 NLD Ajout CATMathMinimizeXYParams.h pour partage avec classes dérivées des code internes d'options
//              CATMathALLEXTREMA CATMathINTERIOREXT CATMathIMAGECOMPAREDEXT  CATMathINTERVALMETHOD CATMathRELENTLESSLY
//              autrefois définies dans l'implémentation (à renommer?)
//              et de la documentation des attributs du Minimize()
// 21/09/11 NLD Ajout MinimumOnCorners()
// 27/11/13 KJD/F1Z Addition of the AdvancedLocalMinimization() method and of the private methods called inside
// 02/12/13 NLD XScale rules
//              Smart indent
// 03/08/21 JSX _Tol to _Tol_SpecPts , mv _SpecPts from private to protected
//=============================================================================

#ifndef CATMathMinimizeXY_H
#define CATMathMinimizeXY_H

#include "YN000FUN.h"

#include "CATMathInterval.h"
#include "CATMathDef.h"
#include "CATMathDiagnostic.h"
#include "CATMathSetOfPointsND.h"
#include "CATCGMVirtual.h"

class CATMathInterval2D;
class CATMathAttrList;
class CATMathFunctionXY;
class CATSoftwareConfiguration;
class CATMathVector;

#include <string.h>
#include "CATTolerance.h"

#include "CATMathMinimizeXYParams.h" // documentation des attributs des minimiseurs XY et codage des options

// Additive option for minimizing (internal use: reserved for this class and its super classes)
//  See CATMathMinimizeXYParams.h

// Attributes available:
//  See CATMathMinimizeXYParams.h

//-------------------------------------------------------------------

//-------------------------------------------------------------------
class ExportedByYN000FUN CATMathMinimizeXY  : public CATCGMVirtual
{
  // public methods
public:

  //-----------------------------------------------------------------
  // Object management
  //-----------------------------------------------------------------

                               CATMathMinimizeXY         (const CATMathFunctionXY        *  iF        ,
                                                          const CATTolerance              & iTol      = CATGetDefaultTolerance(),
                                                                CATSoftwareConfiguration * iConfig    = NULL
                                                         );
    virtual                   ~CATMathMinimizeXY         ();


  //-----------------------------------------------------------------
  // Minimize
  // Min F(x, y) where x and y are in the given Domain.
  // The minimization takes the bounds of the Domain in account.
  // Different options are available (absolute minimum/all minima ,
  // interior minimum, minimum with image lower than K)
  // The default method is a discretization method, using a specific
  // argument an interval method is accessible (safer about 50% slower).
  //-----------------------------------------------------------------
  // Attributes available:
  //  See CATMathMinimizeXYParams.h

    virtual CATMathDiagnostic  Minimize                  (const CATMathInterval2D         & iDomain    ,
                                                                CATMathSetOfPointsND      & roots      ,
                                                          const CATMathAttrList          *  attributes = 0) const;


  //--------------------------------------------------------------------
  // Convergence on nul gradient
  //
  // Use the newton iteration on the gradient to find a solution
  // 0 is returned if no solution where found
  // 1 is returned if a solution was found, the solution is (x,y)
  //----------------------------------------------------------------------

    virtual CATBoolean         MinimizeNewton            (      double                    & x          , 
                                                                double                    & y          ,
                                                          const double                      xMin       ,
                                                          const double                      xMax       ,
                                                          const double                      yMin       ,
                                                          const double                      yMax       ) const;


    virtual CATMathDiagnostic LocalMinimization          (const double                      xmin       ,
                                                          const double                      xmax       ,
                                                          const double                      ymin       ,
                                                          const double                      ymax       ,
                                                                double                    & iox        ,
                                                                double                    & ioy        ) const;

    virtual void              SetOKScaleReviewed         () ;

    virtual void              ForceLocalMinBugCorrected  () ;

  // ------------------------
  // Minimization method
  // ------------------------
  // Launch a local minimization (Advanced Use)
  // In case of failure (CATMathMaxInteration), the hessian at the found point is evaluated. 
  // If it is negative, a new init is computed thanks to the privileged direction of the hessian matrix.
            CATMathDiagnostic AdvancedLocalMinimization  (const double                    & xmin       ,
                                                          const double                    & xmax       ,
                                                          const double                    & ymin       ,
                                                          const double                    & ymax       ,
                                                                double                    & iox        ,
                                                                double                    & ioy        );


  //protected methods

protected:

    virtual CATMathDiagnostic FMinimize                  (const CATMathInterval2D         & Domain     ,
                                                                CATMathSetOfPointsND      & roots      ,
                                                          const CATLONG32                   option     ,
                                                                double                    & LocalLimValue,
                                                          const CATLONG32                   sampleX     ,
                                                          const CATLONG32                   sampleY     ) const;

    virtual CATMathDiagnostic DMinimize                  (const CATMathInterval2D         & Domain     ,
                                                                CATMathSetOfPointsND      & roots      ,
                                                          const CATLONG32                   option     ,
                                                                double                    & LocalLimValue,
                                                          const CATLONG32                   sampleX     ,
                                                          const CATLONG32                   sampleY     ) const;

    virtual CATMathDiagnostic RBMinimize                 (const CATMathInterval2D         & Domain     ,
                                                                CATMathSetOfPointsND      & roots      ,
                                                          const CATLONG32                   option     ,
                                                                double                    & LocalLimValue,
                                                          const CATLONG32                   sampleX     ,
                                                          const CATLONG32                   sampleY     ) const;

    virtual CATMathDiagnostic R1Minimize                 (const CATMathInterval           & DX         ,
                                                          const CATMathInterval           & DY         ,
                                                                CATMathSetOfPointsND      & roots      ,
                                                          const CATLONG32                   option     ,
                                                                double                    & LocalLimValue,
                                                          const double MaxWidth                        ) const;
    virtual CATMathDiagnostic R2Minimize                 (const CATMathInterval           & DX         ,
                                                          const CATMathInterval           & DY         ,
                                                                CATMathSetOfPointsND      & roots      ,
                                                          const CATLONG32                   option     ,
                                                                double                    & LocalLimValue,
                                                          const double MaxWidth                        ) const;

    virtual CATLONG32         MinimizeIntervalNewton     (const CATMathInterval           & DX         ,
                                                          const CATMathInterval           & DY         ,
                                                                CATMathSetOfPointsND      & roots      ,
                                                          const CATLONG32                   option     ,
                                                                double                    & LocalLimValue) const;

            int               HasGoodSign                (const double                      t0         ,
                                                          const double                      t1         ,
                                                          const double                      df0        ,
                                                          const double                      df1        ,
                                                          const double                      d2f0       ,
                                                          const double                      d2f1       ,
                                                          const CATLONG32                   VARFIXED   ,
                                                          const double                      uFixed     ,
                                                          const CATLONG32                   VARDERIV   ,
                                                          const CATLONG32                   WantedSign ) const;



            void              MinimumBoundary            (const CATLONG32                   FRONTIERE  ,
                                                          const double                      uFixed     ,
                                                          const double                      tMin       ,
                                                          const double                      tMax       ,
                                                          const CATLONG32                   Sample     ,
                                                          const double                   *  F          ,
                                                          const double                   *  Ft         ,
                                                          const double                   *  Ft2        ,
                                                          const CATLONG32                   DeltaPtr   ,
                                                          const CATLONG32                   NormalDirection,
                                                                CATMathSetOfPointsND      & roots      ,
                                                          const CATLONG32                   option     ,
                                                                double                    & LocalLimValue) const;

    virtual void              AddMinimum                 (const double                      x          ,
                                                          const double                      y          ,
                                                          const CATLONG32                   option     ,
                                                                CATMathSetOfPointsND      & roots      ,
                                                                double                    & LocalLimValue) const;

    virtual void              FirstMinimumInDirection    (const double                    & xdep       ,
                                                          const double                    & ydep       ,
                                                          const double                    & nx         ,
                                                          const double                    & ny         ,
                                                          const double                    & Longueur   ,
                                                                double                    & xpoint     ,
                                                                double                    & ypoint     ) const;

            CATMathDiagnostic DMinimizeMonodimensional   (const double                       xmin      ,
                                                          const double                       xmax      ,
                                                          const double                       ymin      ,
                                                          const double                       ymax      ,
                                                          const double                       GradientX ,
                                                          const double                       GradientY ,
                                                                CATMathSetOfPointsND       & roots     ,
                                                          const CATLONG32                    option    , 
                                                                double                     & LocalLimValue,
                                                          const CATLONG32                    NX        ,
                                                          const CATLONG32                    NY        ) const;


    virtual CATMathDiagnostic GridGlobalMinimization     (const double                       xmin      ,
                                                          const double                       xmax      ,
                                                          const double                       ymin      ,
                                                          const double                       ymax      ,
                                                          const CATLONG32                    NX        ,
                                                          const CATLONG32                    NY        ,
                                                                double                       TolForCst ,
                                                                double                     & ox        ,
                                                                double                     & oy        ) const;

    virtual CATMathDiagnostic GridLocalMinimization      (const double                       xmin      ,
                                                          const double                       xmax      ,
                                                          const double                       ymin      ,
                                                          const double                       ymax      ,
                                                                CATMathSetOfPointsND       & roots     ,
                                                          const CATLONG32                    option    ,
                                                          const CATLONG32                    NX        ,
                                                          const CATLONG32                    NY        ,
                                                                double                       TolForCst ) const;

    virtual void       CATMathMinimizeXYParallelDebugCond(      double                       Xmin      ,
                                                                double                       Xmax      ,
                                                                double                       Ymin      ,
                                                                double                       Ymax      ,
                                                             // double                       iTolerance,
                                                                double                       iTolForCst,
                                                                double                       iLimitValue
                                                         )  ;

private:
  // Stockage du resultat d'evaluation de la minimisation locale
            void       LocalMinimizationStoreEval        (      double                       x         ,
                                                                double                       y         ,
                                                                double                       f         ,
                                                                double                       fx        ,
                                                                double                       fy        );


            void       MinimumOnCorners                  (const double                       xmin      ,
                                                          const double                       xmax      ,
                                                          const double                       ymin      ,
                                                          const double                       ymax      ,
                                                          const CATLONG32                    option    ,
                                                          const CATLONG32                    NX        ,
                                                          const CATLONG32                    NY        ,
                                                                double                    *  F         ,
                                                                double                    *  Fx        ,
                                                                double                    *  Fy        ,
                                                                double                    *  Fx2       ,
                                                                double                    *  Fxy       ,
                                                                double                    *  Fy2       ,
                                                                double                     & LocalLimValue,
                                                                CATMathSetOfPointsND       & roots
                                                                                                       ) const;


  //Methods devoted to the AdvancedLocalMinization computation :
  //CATMathDiagnostic AdvancedLocalMinimization(const double &xmin,  const double &xmax,
  //                                            const double &ymin,  const double &ymax,
  //                                            double       & iox, double       & ioy);
  // Method called in case of failure of a local minimization to compute a new init and to launch a new local minimization with it
  //(ixInit, iyInit)  is the initial point provided to AdvancedLocalMinimization
  //(iox, ioy) is the result of the first local minimization
            CATMathDiagnostic ImproveLocalMinimizationResult
                                                         (const double                     & xmin      ,
                                                          const double                     & xmax      ,
                                                          const double                     & ymin      ,
                                                          const double                     & ymax      ,
                                                                double                     & ixInit    ,
                                                                double                     & iyInit    ,
                                                                double                     & iox       ,
                                                                double                     & ioy       );
  // Method called in ImproveLocalMinimizationResult to compute the direction to find the new init
            CATBoolean        GetPrivilegedDirection     (const double                     & ix        ,
                                                          const double                     & iy        ,
                                                                CATMathVector              & ioMainDir ) const;
  // Method which computes the eigen properties of the hessian matrix
            int               GetHessianInfo             (const double                     & ix        ,
                                                          const double                     & iy        ,
                                                                double                     & osigne    ,
                                                                int                        & onbVal    ,
                                                                double                    *& ovalP     ,
                                                                CATMathVector             *& ovecP     ,
                                                                CATBoolean                 & oIsDiagonal) const;

  // Method called in ImproveLocalMinimizationResult to find a first point with a positive hessian
            CATBoolean        LookForAPositiveArea       (const double                     & xmin      ,
                                                          const double                     & xmax      ,
                                                          const double                     & ymin      ,
                                                          const double                     & ymax      ,
                                                          const CATMathVector              & iMainDirLocal,
                                                          const double                     & iStep     ,
                                                                double                     & iox       ,
                                                                double                     & ioy       ) const ;

  // Method called in ImproveLocalMinimizationResult to compute the new init from a first point with a positive hessian
            void              LookForABestPositiveArea   (const double                     & xmin      ,
                                                          const double                     & xmax      ,
                                                          const double                     & ymin      ,
                                                          const double                     & ymax      ,
                                                          const CATMathVector              & iMainDirLocal,
                                                          const double                     & iStep     ,
                                                                double                     & iox       ,
                                                                double                     & ioy       ) const ;

  // Method which computes the second derivative along a privileged direction
            double            EvalHessianAlongDir        (      double                     & ix        ,
                                                                double                     & iy        ,
                                                                double                     & iDirX     ,
                                                                double                     & iDirY     ) const;
  // Method which computes the distance to boundary
  // If the new point is outside of the domain, it is projected on the border
            double            GetDistanceToBoundary      (const double                     & xmin      ,
                                                          const double                     & xmax      ,
                                                          const double                     & ymin      ,
                                                          const double                     & ymax      ,
                                                          const double                     & ix        ,
                                                          const double                     & iy        ,
                                                          const double                     & iDirX     ,
                                                          const double                     & iDirY     ) const;

  // protected data
protected:
  const CATMathFunctionXY * _F;
  const CATTolerance & _TolObject;
  CATMathSetOfPointsND    * _SpecPts;

private:
  //                                                   // parametres et resultats de la derniere evaluation de LocalMinimization()
  double                    _ValX,
                            _ValY,
                            _ValF,
                            _ValFX,
                            _ValFY;

  double                    _Tol_SpecPts;

  CATBoolean                _LocalMin_BugCorrected;
  CATBoolean                _OKScaleReviewed ;
  CATBoolean                _ParallelDebugChecked ;
  int                       _NbUnReviewedAttributes ;

  CATSoftwareConfiguration* _Config ;
};

#endif
