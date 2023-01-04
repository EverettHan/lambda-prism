//   #define ShuntSetTolerance "NLD120718 pour voir appelants: AUCUN appelant au 120718; SI: Y3TstSurNormal001"
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
// CATSurNormal:
//   This operator compute the normal to a CAT - surface 
//
//=============================================================================
// Usage notes:
//=============================================================================
// (post-historique corrective NLD100718)
// 1) historique de CATMathNormal
//    ---------------------------
//   /01/98 SRO Jan 98   Creation                                 S. Royer
//          PKC Modif                                             P. Catel
//   /03/00 D.J Modif                                             D. Johansson
//              (nous devons certainement à D.J la mécanique des calculs de derivées manquante;
//               FiniteMethodHighDerivatives(), et tout le code qui,
//               dans CATMathNormal, echouera dans les ComputeMissingInputs*() NLD030718)
// 2) historique de CATSurNormal
//    --------------------------
// 09/08/00 DJ  Creation par copie/modification de CATMathNormal
//              - derivation de CATCGMOperator (en l'etat, sans grand interet; NLD100718)
//              - ajout de TrustedParameter(), CaseSelection, CreateCATSurNormal()
// 10/07/18 NLD Mise au propre
//              - Detabulation
//              - Smart indent
//              Ajout Init()
//              Ajout constructeur avec configuration
//              Deplacement du destructeur dans implémentation
//              Ajout _Config
//              Ajout CATCreateCATSurNormal() avec configuration
// 12/07/18 NLD XScale: Acces interdit à SetTolerance() (jamais appelé) en attendant eclaircissement
// 03/08/18 NLD Suppression effective du dernier createur et du dernier constructeur sans configuration après migration
//              des dernieres familles d'appelants (par flag deprécompilation)
//=============================================================================
#ifndef CATSurNormal_H
#define CATSurNormal_H

// Pour activer ces shunts on attend la collecte complete du 030818 de mes modifications dans le tree CGMSTYLE
   #define CATSurNormal_ShuntOldConstructor "EN ATTENTE, finir la migration; reste CATCltG3EvalOp   dans CATClassATopoOperators; OKNLD010818"
   #define CATSurNormal_ShuntOldCreator     "EN ATTENTE, finir la migration; reste CATFDFFunctionXY dans SurfacicTopoOperators;  OKNLD010818"


#include "Y30UIUTI.h"
#include "CATCGMOperator.h"
#include "CATSurface.h"
#include "CATSurNormal.h"
#include "CATCGMOperator.h"
class CATSoftwareConfiguration;

//=============================================================================
class ExportedByY30UIUTI  CATSurNormal : public CATCGMOperator 
{
 public:
  //---------------------------------------------------------------------------
  // Object Management.
  //---------------------------------------------------------------------------    
#ifndef CATSurNormal_ShuntOldConstructor
                            CATSurNormal(      CATGeoFactory            * iFactory ,
                                               CATSurface               * iSurf    ) ;
#endif

                            CATSurNormal(      CATGeoFactory            * iFactory ,
                                               CATSoftwareConfiguration * iConfig  ,
                                               CATSurface               * iSurf    ) ;

    virtual                ~CATSurNormal();

                 void       SetSurface  (      CATSurface               * iNewSurf ) ;

     // Tolerance: Suppose d1 is a short derivative of one parameter and d2, of the other 
     // parameter, is substantially longer, the environment is considered degenerated if
     // |d1 x d2|/|d2| < iNewTol.
     // Default value is the resolution of the iFactory.

     // CAUTION: Inconsistent XScale definition
     // - cannot depend on factory resolution because |d1 x d2|/|d2| is  scale independant
     // - but coded as so
     // TO BE FIXED; NLD120718
#ifdef ShuntSetTolerance
private:
#endif
                 void       SetTolerance(const double                     iNewTol  ) ;
#ifdef ShuntSetTolerance
public:
#endif

                 int        Run         ()
                {return _OK ; } ;
  //---------------------------------------------------------------------------
  // Normal evaluator.
  //   * ioNormal is the normalized normal output. It is an array of 3 doubles.
  //   * iU and iV are the parameters where the normal is to be computed.
  //   * iDU, iDV and iDUV are optional pointers. The partial derivative
  //     can be given as arguments when available, for optimisation.
  //     When given, they are arrays of three doubles.
  //        iDU is the first derivative of the first variable iU.
  //        iDV is the first derivative of the second variable iV.
  //        iDUV is the second derivative of both variables iU and iV.

                 CATBoolean EvalNormal  (      double        * ioNormal ,
                                         const double          iU       ,
                                         const double          iV       ,
                                         const double        * iDU      = NULL,
                                         const double        * iDV      = NULL,
                                         const double        * iDUV     = NULL) ;

  //---------------------------------------------------------------------------
  // Normal and normal derivatives evaluator.
  //   * ioNormal is the normalized normal output. It is an array of 3 doubles.
  //   * ioDerivU and ioDerivV are the output for the first derivative of
  //     the normalized normal. They are arrays of 3 doubles.
  //   * iU and iV are the parameters where the normal is to be computed.
  //   * iDU, iDV, iDUV, iDU2 and iDV2 are optional pointers.
  //     The partial derivative can be given as arguments when available,
  //     for optimisarion.
  //     When given, they are arrays of three doubles.
  //        iDU is the first derivative of the first variable iU.

  //        iDV is the first derivative of the second variable iV.
  //        iDUV is the second derivative of both variables iU and iV.
  //        iDU2 is the second derivative of the fisrt variable iU.
  //        iDUV is the second derivative of the second variable iV.

                 CATBoolean EvalUpToFirstDeriv(double        * ioNormal ,
                                               double        * ioDerivU ,
                                               double        * ioDerivV ,
                                         const double          iU       ,
                                         const double          iV       ,
                                         const double        * iDU      = NULL,
                                         const double        * iDV      = NULL,
                                         const double        * iDU2     = NULL,
                                         const double        * iDUV     = NULL,
                                         const double        * iDV2     = NULL) ;

  //---------------------------------------------------------------------------
  // Normal, normal derivatives and normal second derivatives evaluator.
  //   * ioNormal is the normalized normal output. It is an array of 3 doubles.
  //   * ioDerivU and ioDerivV are the output for the first derivative of
  //     the normalized normal. They are arrays of 3 doubles.
  //   * ioSecondDerivU, ioSecondDerivV, ioSecondDerivUV are the output for the second
  //     derivative of the normalized normal. They are arrays of 3 doubles.
  //   * iU and iV are the parameters where the normal is to be computed.
  //   * iDU, iDV, iDUV, iDU2, iDV2,  iDU2V, iDUV2, iDU3 and iDV3 are optional pointers.
  //     The partial derivative can be given as arguments when available,
  //     for optimisarion.
  //     When given, they are arrays of three doubles.
  //        iDU is the first derivative of the first variable iU.
  //        iDV is the first derivative of the second variable iV.
  //        iDUV is the second derivative of both variables iU and iV.
  //        iDU2 is the second derivative of the fisrt variable iU.
  //        iDUV is the second derivative of the second variable iV.
  //        iDU2V, iDUV2 are third derivatives of both variables iU and iV.
  //        iDU3 is the third derivative of the second variable iU. 
  //        iDV3 is the third derivative of the second variable iV.
                 CATBoolean EvalUpToSecondDeriv
                                              (double        * ioNormal ,
                                               double        * ioDerivU ,
                                               double        * ioDerivV ,
                                               double        * ioSecondDerivU,
                                               double        * ioSecondDerivUV,
                                               double        * ioSecondDerivV,
                                         const double          iU       ,
                                         const double          iV       ,
                                         const double        * iDU      = NULL,
                                         const double        * iDV      = NULL,
                                         const double        * iDU2     = NULL,
                                         const double        * iDUV     = NULL,
                                         const double        * iDV2     = NULL,
                                         const double        * iDU3     = NULL,
                                         const double        * iDU2V    = NULL,
                                         const double        * iDUV2    = NULL,
                                         const double        * iDV3     = NULL) ;
 
 private:

  //---------------------------------------------------------------------------
     CATSurface               * _SURF  ;
     CATSoftwareConfiguration * _Config;

     // Tolerance telling smallest acceptable size
     // of a short edge. 
     // More precise: Suppose d1 is a short derivative of one parameter and d2, of the other 
     // parameter, is substantially longer, the environment is considered degenerated if
     // |d1 x d2|/|d2| < _TOL.
     // CAUTION: XScaleKO, see SetTolerance(), to be discussed/fixed; NLD120718
     double                     _TOL   , // tolerance
                                _SQTOL ; // (and its square) 
     
     int                        _OK ;

     const CATMathFunctionXY  * _X,
                              * _Y,
                              * _Z ;
     //const CATMathIntervalND* _Domain; //domaine de definition des function _X, _Y, _Z
     //dimension = 2
     
     //coord du centre du domaine de definition de _X, _Y, _Z;
     double                     _CenterU,
                                _CenterV;

  //---------------------------------------------------------------------------
                 void       Init        (      CATGeoFactory            * iFactory ,
                                               CATSoftwareConfiguration * iConfig  ,
                                               CATSurface               * iSurf    ) ;
     
     // At degenerated points, first and second derivatives of the normal may be asked for. In  
     // turn, derivatives of _X, _Y, and _Z of higher order than three may be needed. These can't 
     // be calculated by CATMathFunctionXY. These are roughly estimaded by the following method.
     // Precision: Suppose that CATMathFunctionXY evaluate 4n correct digits. The number of correct 
     // digits in the fourth derivatives will be around 2n and on the fifth derivatives, around n.
     
                 void       FiniteMethodHighDerivatives
                                        (const double        * iThirdDeriv,
                                         const CATLONG32       iKindOfThird, // (iThirdDerivative = TD) 0: TD=DU3, 1: TD=DU2V, 2: TD=DUV2 and 3: TD=DV3.
                                         const double          iU        ,
                                         const double          iV        ,
                                               double        * oDUofTD   ,
                                               double        * oDVofTD   = NULL,
                                               double        * oDUUofTD  = NULL,
                                               double        * oDUVofTD  = NULL,
                                               double        * oDVVofTD  = NULL ) const ;

     // Suppose that the derivatives iDU and iDV are calculated at one degenerated edge of a patch.In 
     // first case ( iKind = 0 ) we suppose |iDU| is "large" but |iDU x iDV|/|iDU| < iTol. Then, for
     // constant v = iV, we find a new u = newU such that |iDU x DV(newU, iV)|/|iDU| = iTol. We  assume 
     // that, at (newU, iV), the patch properties can be trusted but at (iU,iV) they can not. 
     // If ( iKind = 1 ) the parameters u and v are switched in an obvious way. 
     // Results: 
     // The "X" in the notation oDX is to be interpreted as an V if iKind = 0 else as an U. 
     // The new derivatives are first calculated in (newU, iV) ( or (iU, newV)) and are then adjusted,
     // by a simple linear metod, to a supposed derivative at (iU, iV). 

                 CATLONG32  TrustedParameter
                                        (const double          iTol      ,
                                         const double          iU        ,
                                         const double          iV        ,
                                         const double        * iDU       ,
                                         const double        * iDV       ,
                                         const double        * iDUV      ,
                                         const double          iNorm2    ,
                                         const CATLONG32       iKind     ,                //if iKind = 0, newU is sought  else (1) newV.
                                         const double          iSign     ,                //if iKind = 0, use sigma       else use tau.
                                         const double          iSqLength ,                //if iKind = 0, norm2DU         else norm2DV.
                                               double        * oDX       ,                //if iKind = 0, oDX   = DV      else oDX   = DU.
                                               double        * oDXU      = NULL,          //if iKind = 0, oDXU  = DVU     else oDXU  = DU2.
                                               double        * oDXV      = NULL,          //if iKind = 0, oDXV  = DV2     else oDXV  = DUV.
                                               double        * oDXUU     = NULL,          //if iKind = 0, oDXUU = DU2V    else oDXUU = DU3.
                                               double        * oDXUV     = NULL,          //if iKind = 0, oDXUV = DUV2    else oDXUV = DU2V.
                                               double        * oDXVV     = NULL ) const ; //if iKind = 0, oDXUV = DV3     else oDXUV = DUV2.
         
     // Classify degenerations
     
                 CATLONG32  CaseSelection
                                        (const double          SQTOL     ,
                                         const double          norm2     ,
                                         const double          norm2DU   ,
                                         const double          norm2DV   ) const ;

};

//=============================================================================
// Create 
//=============================================================================
#ifndef CATSurNormal_ShuntOldCreator
ExportedByY30UIUTI 
CATSurNormal *    CreateCATSurNormal( CATGeoFactory            * iFactory,
                                      CATSurface               * iSurf   ) ;
#endif

ExportedByY30UIUTI 
CATSurNormal * CATCreateCATSurNormal( CATGeoFactory            * iFactory,
                                      CATSoftwareConfiguration * iConfig ,
                                      CATSurface               * iSurf   ) ;

#endif
