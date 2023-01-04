/*-*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATCrvQuinticInterpolation :
// Interface class of the CATCrvQuinticInterpolationCx5(new)/CATCrvQuinticInterpolationCx2(old)
//
//=============================================================================
// Usage notes:
// -----------
//    UpToDate operator creation API should be found below (and no more in CATCreateCrvQuinticInterpolation.h)
//    (see below CATCreateCrvQuinticInterpolation_NewAPI)
//
// sample of use :
// -------------
//    None
//
// XScaleRules:                                                                                 (NLD220714)
// -----------
//  - there is no ScaleOption (of type CATMathAttrScaleOption) describing the operator behaviour:
//    scale behaviour is imposed
//  - parameters        must behave like power   1 of factory scale
//  - points            must behave like power   1 of factory scale
//  And, of course, consequently,
//  - first  derivatives must behave like power  0 of factory scale
//  - second derivatives must behave like power -1 of factory scale
//
//=============================================================================
//  May  99 NDN Creation
// 30/03/07 NLD Ajout transitoire OldDeprecatedCreateCrvQuinticInterpolation()
//              et                OldDeprecatedCATCreateCrvQuinticInterpolation()
//              avec factory, a ne pas interfacer (on va faire migrer les clients vers le CATCreate)
//              (OldDeprecated* migres directement vers CATPrivCreateCrvQuinticInterpolation.h, 02/04/07 cpt)
// 19/03/12 NLD Mise au propre (radical ET terminaison, soit quand meme l'integralité)
//              de l'heterogenissime énumération CATQuinticInterpolationDiagType (version 12 du 31/03/05 de ce bel objet)
//              ne voulant strictement rien dire
//              et renommee CATQuinticInterpolationDiagType
//              avec CATQuinticInterpolationDiag_InvalidTangent en remplacement de CATFrFTopologicalSweepType_InvalidTangent
//              et   CATQuinticInterpolationDiag_SmallArc       en remplacement de CATQuinticInterpolationType_SmallArc
//              (alors que les remplissages par CATQuinticInterpolationCx2 utilisaient d'ailleurs en dur les valeurs 1 et 2,
//              et que la seule utilisation de l'enumeration dans CATSplineOperatorCx3 meritait aussi une bonne refonte)
// 09/07/14 NLD Mise au propre. Smart indent
//              Recommandations de migration sur la bonne signature de CATCreateCrvQuinticInterpolation()
//              Documentation claire des methodes de pilotage des impositions de normes
// 10/07/14 NLD Pour coherence de la definition de classe, mentionnant anciennement des donnees non definies,
//              la definition de CATCreateCrvQuinticInterpolation() est ramenee ici avec la classe CATQuinticInterpolation
// 17/07/14 NLD Documentation des nouvelles specifications de cycle de vie liees a GetParameters()
// 22/07/14 NLD Ajout XScaleRules. Modification Usage notes
//=============================================================================
#ifndef CATQuinticInterpolation_H 
#define CATQuinticInterpolation_H

#include "CATSkillValue.h"
#include "CATBoolean.h"
#include "CATGMModelInterfaces.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"
#include "CATMath.h"
#include "CATTolerance.h"

class CATMathSetOfPointsND;
class CATGeoFactory;
class CATNurbsCurve;
class CATPNurbs;
class CATSplineCurve;
class CATPSpline;
class CATSurface;
class CATMathNurbsMultiForm;
class CATMathVector;
class CATSoftwareConfiguration;
class CATQuinticInterpolation;

//-----------------------------------------------------------------------------
//                                                            // Histo: (N.B Suppression de l'historique de cette enumeration: NLD170714)
typedef enum {
              CATQuinticInterpolationDiag_SmallArc       = 1, // when two consecutive points are too near (distance smaller than resolution)
              CATQuinticInterpolationDiag_InvalidTangent = 2  // when tangent norm is too small           (smaller than resolution divided by factory scale)
             } CATQuinticInterpolationDiagType;
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// WARNING : None of the arrays given as input to this operator are duplicated
//           for performance reasons, including Create functions.
//           Do not delete or change the length or position of these arrays while using
//           this operator.
//-----------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATQuinticInterpolation : public CATCGMVirtual
{
  public :

    struct CATQuinticInterpolationDiagInfo 
    {
      int                             IndexPoint;
      CATQuinticInterpolationDiagType Diag      ;
    };
  
  virtual                              ~CATQuinticInterpolation  ();

  //                                                               //-----------------------------------------------------------------------------
  //                                                               // API modification guide for developer:
  //                                                               // see full and detailed information tagged <@InfoModifAPIQuinticInterpolation>
  //                                                               // in GeometricOperators\Y30C3XGG.m\src\CATCrvQuinticInterpolationCx2.cpp
  //                                                               //-----------------------------------------------------------------------------
   
  virtual       void                    Run                      ()                                                   = 0;


  // Derivatives norm may be managed through SetExactDerivatives()
  // (global behaviour for first and second derivatives in all points)
  // or SetExactFirstDerivatives() / SetExactSecondDerivatives()
  // (behaviour defined in each point)

  // If you want to manage the imposition of the exact norm of the first and second derivatives
  //   iImposed = 1 : direction and the exact norm will be imposed 
  //   iImposed = 0 : direction only               will be imposed 
  // Default behaviour (if no call)
  //   - if parameters imposed (argument iParameters of operator creation method, below)
  //                  direction and the exact norm will be imposed
  //   - if parameters are free
  //                  direction only               will be imposed
  virtual       void                    SetExactDerivatives      (      CATLONG32        iImposed            )        = 0;

  // Array of values for management of the norm of first derivative on the various points
  //  iImposed[i] = 1 in order to impose the exact norm     of the first derivative        (default behaviour)
  //  iImposed[i] = 0 in order to impose only the direction of the first derivative 
  virtual       void                    SetExactFirstDerivatives (const CATLONG32     *  iImposed            )        = 0;

  // Array of values for management of the norm of second derivative on the various points
  //  iImposed[i] = 1 in order to impose the exact norm     of the second derivatives        (default behaviour)
  //  iImposed[i] = 0 in order to impose only the direction of the second derivative 
  virtual       void                    SetExactSecondDerivatives(const CATLONG32     *  iImposed            )        = 0;


  // Set periodicity. MANDATORY : first and last point must be equal.
  // Tangent or SecondDeriv imposition on the last point will not be
  // take into account in this case. WARNING : this option is only 
  // available using the CATCreateCrvQuinticInterpolation creator.
  // Also there should be at least three points to interpolate,
  // to have periodicty.
  // Ouptut values are : - FALSE, periodicity is not possible.
  //                     - TRUE,  periodicity is possible.
  virtual       CATBoolean              SetPeriodicity           ()                                                   = 0;

  // Get methods.

  //            For 3D curves, dimension of the CATMathSetOfPointsND should be equal to 3.
  // Otherwise, for 2D curves, dimension of the CATMathSetOfPointsND should be equal to 2.
  // If iCheck=TRUE, returned pointer will be different from NULL only if the result is compliant
  // with CATIA rules for geometric objects.
  virtual       CATNurbsCurve         * GetNurbsCurve            (      CATGeoFactory *  iFactory            ,
                                                                        CATBoolean       iCheck              = FALSE) = 0;
  
  virtual       CATPNurbs             * GetPNurbs                (      CATGeoFactory *  iFactory            ,
                                                                        CATSurface    *  iSupport            ,
                                                                        CATBoolean       iCheck              = FALSE) = 0;

  virtual       CATSplineCurve        * GetSplineCurve           (      CATGeoFactory *  iFactory            ,
                                                                        CATBoolean       iCheck              = FALSE) = 0;
  
  virtual       CATPSpline            * GetPSpline               (      CATGeoFactory *  iFactory            ,
                                                                        CATSurface    *  iSupport            ,
                                                                        CATBoolean       iCheck              = FALSE) = 0;

  // Get diagnostics, to be called after Get geometry (ex: you ask for GetPNurbs with iCheck=TRUE). Deletion of oAllDiag array is at user responsability.
  virtual       void                    GetAllDiagnosis          (      int            & oNbDiag             ,
                             CATQuinticInterpolation::CATQuinticInterpolationDiagInfo *& oAllDiag            )        = 0;

  // The dimension of the CATMathSetOfPointsND should be a multiple of 2 or 3, i.e (iNbForms * 2) or (iNbForms * 3)
  // iOptimiseContinuity : 0 means results will have a C0 nodal vector (but C2 mathematicaly and faster).
  virtual       CATMathNurbsMultiForm * GetMultiForm             (      CATLONG32        iNbForms            ,
                                                                        CATLONG32        iOptimiseContinuity = 1)     = 0;
  
  // General result. If you call one of this two methods, you will have to
  // manage the deletion of the returned CATMathSetOfPointsND.
  virtual       CATMathSetOfPointsND  * GetTangents              ()                                                   = 0;
  virtual       CATMathSetOfPointsND  * GetSecondDerivatives     ()                                                   = 0;


  // General result. If you call this method, you will have to manage the deletion of the returned array
  // (that may be the one given in input to the constructor through operator creation method)
  // (****** new, logical and consistent behaviour NLD170714, fix in operator implementation with synchronous fix in various calling software *****)
  virtual const double                * GetParameters            ()                                                   = 0;

};


//-----------------------------------------------------------------------------
// This is the one and only recommended API, with
// - Factory               (XScale compliant)
// - SoftwareConfiguration (Versionning compliant)
// - Recommended behaviour (new operator CATCrvQuinticInterpolationCx5 instead of old one CATCrvQuinticInterpolationCx2)
//-----------------------------------------------------------------------------
//
// All set of points, if given (iPoints, ioFirstDerivatives, ioSecondDerivatives) must have
// - same dimension
// - same number of points
// All arrays,        if given (iParameters, iKindOfimpositions) must also have
// - same number of points as the sets of points
//
// iPoints            may not be set to NULL
// iParameters        may be set to NULL: parameters will be internally computed
// iKindOfImpositions may be set to NULL, if no imposition
//                    if given, iKindOfImpositions[i], with i in [0, iPoints->GetNumberOfPoints()-1], means
//                    - iKindOfImpositions[i] = 0 no imposition
//                    - iKindOfImpositions[i] = 1 first derivative imposed
//                    - iKindOfImpositions[i] = 2 second derivative imposed
//                    - iKindOfImpositions[i] = 3 first and second derivative imposed
//
// Nota: Run() is not automatically done by creator, and must be called by calling software
//-----------------------------------------------------------------------------
#define CATCreateCrvQuinticInterpolation_RecommendedAPIDefined "Important pour coherence CATQuinticInterpolation.h CATCreateCrvQuinticInterpolation.h"

//                        CATCreateCrvQuinticInterpolation_NewAPI
ExportedByCATGMModelInterfaces
CATQuinticInterpolation * CATCreateCrvQuinticInterpolation    (      CATGeoFactory            * iFactory            ,
                                                                     CATSoftwareConfiguration * iConfig             ,
                                                               const CATMathSetOfPointsND     * iPoints             ,
                                                               const double                   * iParameters         ,
                                                                     CATMathSetOfPointsND     * ioFirstDerivatives  ,
                                                                     CATMathSetOfPointsND     * ioSecondDerivatives ,
                                                               const CATLONG32                * iKindOfImpositions  ,
                                                                     CATLONG32                  iDummy              = 1); // not used, to be discarded. (old name iComputeSystem)




//-----------------------------------------------------------------------------
// Removes a quintic interpolation operator
//-----------------------------------------------------------------------------
ExportedByCATGMModelInterfaces
void                      Remove                              (      CATQuinticInterpolation  *& ioCrvQuinticInterpolation);

//=============================================================================
// Utility methods
//=============================================================================
//-----------------------------------------------------------------------------
// Fonction permettant de recuperer la derivee seconde a imposer pour l'operateur de CATQuinticInterpolation, pour obtenir la courbure
// en entree. Le vecteur courbure doit etre orthogonal a la derivee premiere passee en argument. La derivee premiere et la seconde doivent etre
// transmises a l'operateur d'interpolation avec imposition des valeurs de normes pour le point ou l'on veut imposer la courbure.
//-----------------------------------------------------------------------------
ExportedByCATGMModelInterfaces
void                      ComputeSecondDerivativeFromCurvature
                                                              (const CATMathVector             & iFirstDerivative   ,
                                                               const CATMathVector             & iCurvature         ,
                                                                     CATMathVector             & oSecondDerivative  ,
                                                               const CATTolerance              & iTol               = CATGetDefaultTolerance()
                                                              );
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

ExportedByCATGMModelInterfaces
void                      ComputeCurvatureFromSecondDerivative(const CATMathVector            & iFirstDerivative    ,
                                                               const CATMathVector            & iSecondDerivative   ,
                                                                     CATMathVector            & oCurvature          ,
                                                               const CATTolerance             & iTol                = CATGetDefaultTolerance() );


//=============================================================================
// Old deprecated interfaces
//=============================================================================
//-----------------------------------------------------------------------------
// ---------------------------------------------------------------------------
//  -------------------------------------------------------------------------
//   ! DO NOT USE (use CATCreateCrvQuinticInterpolation_NewAPI above)      !
//   ! - no Factory               : not XScale compliant                   !
//   ! - no SoftwareConfiguration                                          !
//  -------------------------------------------------------------------------
// ---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//                        CATCreateCrvQuinticInterpolation_VeryOldAPI
ExportedByCATGMModelInterfaces
CATQuinticInterpolation * CATCreateCrvQuinticInterpolation    (const CATMathSetOfPointsND     *  iPoints            ,
                                                               const double                   *  iParameters        ,
                                                                     CATMathSetOfPointsND     *  ioFirstDerivatives ,
                                                                     CATMathSetOfPointsND     *  ioSecondDerivatives,
                                                               const CATLONG32                *  iKindOfImpositions = 0,
                                                                     CATSkillValue               iMode              = BASIC);


//-----------------------------------------------------------------------------
// ---------------------------------------------------------------------------
//  -------------------------------------------------------------------------
//   ! DO NOT USE (use CATCreateCrvQuinticInterpolation_NewAPI above)      !
//   ! - no Factory               : not XScale compliant                   !
//  -------------------------------------------------------------------------
// ---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//                        CATCreateCrvQuinticInterpolation_OldAPI
ExportedByCATGMModelInterfaces
CATQuinticInterpolation * CATCreateCrvQuinticInterpolation    (      CATSoftwareConfiguration *  iConfig            ,
                                                               const CATMathSetOfPointsND     *  iPoints            ,
                                                               const double                   *  iParameters        ,
                                                                     CATMathSetOfPointsND     *  ioFirstDerivatives ,
                                                                     CATMathSetOfPointsND     *  ioSecondDerivatives,
                                                               const CATLONG32                *  iKindOfImpositions = 0,
                                                                     CATSkillValue               iMode              = BASIC);

//-----------------------------------------------------------------------------
// ---------------------------------------------------------------------------
//  -------------------------------------------------------------------------
//   ! DO NOT USE (use CATCreateCrvQuinticInterpolation_NewAPI above)      !
//   ! - old behaviour                                                     !
//   !   (caution: migration to the new one may introduce result changes)  !
//   !   (for old behaviour with factory and SoftwareConfiguration,        !
//   !    use OldDeprecatedCreateCrvQuinticInterpolation()                 !
//   ! - no Factory               : not XScale compliant                   !
//   ! - no SoftwareConfiguration                                          !
//  -------------------------------------------------------------------------
// ---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//                           CreateCrvQuinticInterpolation_OldAPI
ExportedByCATGMModelInterfaces
CATQuinticInterpolation *    CreateCrvQuinticInterpolation    (const CATMathSetOfPointsND     *  iPoints            ,
                                                               const double                   *  iParameters        ,
                                                                     CATMathSetOfPointsND     *  ioFirstDerivatives ,
                                                                     CATMathSetOfPointsND     *  ioSecondDerivatives,
                                                               const CATLONG32                *  iKindOfImpositions = 0,
                                                                     CATSkillValue               iMode              = BASIC);


#endif
