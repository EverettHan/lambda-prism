#ifndef CATIPGMFrFSimilarCurve_h_
#define CATIPGMFrFSimilarCurve_h_

// COPYRIGHT DASSAULT SYSTEMES 2006
//=============================================================================
//
// Les Points et Tangentes aux extremites de la BaseCurve doivent etre donnes 
// implicitement dans la BaseCurve, par le constructeur
//  - StartPoint et EndPoint sur la BaseCurve = les points extremes de la BaseCurve
//    dans ses limites.
//  - StartTgt   et EndTgt   sur la BaseCurve = les tangentes extremes de la BaseCurve
//    dans ses limites.
//
// Pour les donnees de la SimilarCurve, les valeurs par defaut sont les suivantes :
//  - StartPoint et EndPoint sur la SimilarCurve sont les
//    StartPoint et EndPoint sur la BaseCurve
//  - StartTgt et EndTgt de la SimilarCurve sont des vecteurs colineaires aux 
//    StartTgt et EndTgt de la BaseCurve
//
//  Remarque : Dans le cas ou toutes les valeurs sont par defaut, l'operateur ne
//             fait rien.
//    
//
//=============================================================================

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include "CATCollec.h"

class CATFrFNurbsMultiForm;
class CATGeoFactory;
class CATKnotVector;
class CATMathSetOfPoints;
class CATSoftwareConfiguration;
class CATSurface;
class CATMathPoint;
class CATSurParam;
class CATMathVector;
class CATLISTP(CATCrvLimits);
class CATLISTP(CATCurve);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMFrFSimilarCurve;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATIPGMFrFSimilarCurve: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMFrFSimilarCurve();

  // Pour CATCGMOperator
  virtual CATSoftwareConfiguration *  GetSoftwareConfiguration() const = 0;

    // Imposition de points
    // Ce set est a faire si on veut imposer les points extremites de la SimilarCurve.
    // Sinon, on prend les valeurs par defaut, i.e: les points extremites la BaseCurve.
    // Mettre un seul des deux pointeurs revient a demander la valeur par defaut pour l'autre.
    // Les points sont toujours imposés ou conservés
  virtual void                        SetPointsOnSimilarCurve (const CATMathPoint      * iStartPointOnSimilarCurve     , 
                                                               const CATMathPoint      * iEndPointOnSimilarCurve       ) = 0;

    // Pour le cas 2D :
  virtual void                        SetPointsOnSimilarCurve (const CATSurParam       * iStartPointOnSimilarCurve     , 
                                                               const CATSurParam       * iEndPointOnSimilarCurve       ) = 0;

    // Imposition/liberation de tangentes
    // Ce set est a faire si on veut que la SimilarCurve parte tangentiellement a des courbes.
    // Sinon, par defaut, les tangentes sur la SimilarCurve seront prises colineaires a celles sur la BaseCurve.
    // Mettre un seul des deux pointeurs revient a demander la valeur par defaut pour l'autre (colineaire a la base)
    // Les tangentes sont toujours imposées ou conservées
    // NEW! Pour imposer une tangente en laissant libre l'autre il faut utiliser le mode "NullAreFree"
    //   SetTgtsOnSimilarCurve(NULL, NULL)    Impose les tangentes de la base curve ==> (ne change pas le comportement de l'operateur)
    //   SetTgtsOnSimilarCurve(NULL, NULL, 2) Libere la tangente de la base curve 2 ==> (   change     le comportement de l'operateur)
    //                                       (1 pour la base curve 1, 3 pour les 2 courbes)
    // ATTENTION:
    // dans le cas 2D:
    // - les tangentes doivent etre fournies en 3D, leur traduction en 2D etant a la charge de cet operateur
    // - cependant la gestion des tangentes etait archi-buggee. Activation des corrections en V5R27SP2. NLD221116
  virtual void                        SetTgtsOnSimilarCurve   (const CATMathVector     * iStartTgtOnSimilarCurve       ,
                                                               const CATMathVector     * iEndTgtOnSimilarCurve         ,
                                                                     CATLONG32           NullAreFree                   = 0) = 0;

    // Imposition/liberation de courbures
    // Attention : Par defaut les courbures ne sont pas prises en compte dans la deformation (continuite ignorée dans les premieres versions)
    //             Elles sont libres (comportement inverse des tangences)
    //   SetCvtsOnSimilarCurve(NULL, NULL, 0) impose les courbures de la base curve ==> (   change     le comportement de l'operateur)
    //  (SetCvtsOnSimilarCurve(NULL, NULL) ne les impose pas contrairement a ce qui etait indique avant NLD110516)
    //   SetCvtsOnSimilarCurve(NULL, NULL, 3) libere les courbures                  ==> (ne change pas le comportement de l'operateur)
    // CvtOnSimilarCurve       : Vecteur courbure
    // CvtCrvSurMode           : Mode d'imposition:
    //                            0 (crv/crv)
    //                        ou  1 (crv/sur)
    //                        ou 10 (??? usage externe interdit, usage interne reserve au Loft)
    //                              (continuite G2 de la courbe avec une surface sans modifier la courbure dans la direction imposée)
    // ScalarCvtOnSimilarCurve : en mode (Crv/Sur), scalaire representant la courbure (peut etre nul),
    //                           la normale est donnée par iStartCvtOnSimilarCurve/iEndCvtOnSimilarCurve
    // FixedG2Dir              : en mode (Crv/Sur) direction dans laquelle la courbure ne doit pas bouger (par ex plan osculateur de la courbe),
    //                           Permet a un courbe plane de respecter le G2 avec une surface en restant plane.
    //
    // DO NOT USE IN 2D MODE (NLD181116)
    // ---------------------
  virtual void                        SetCvtsOnSimilarCurve   (const CATMathVector     * iStartCvtOnSimilarCurve       , 
                                                               const CATMathVector     * iEndCvtOnSimilarCurve         ,
                                                                     CATLONG32           NullAreFree                   = 3,
                                                                     int                 iStartCvtCrvSurMode           = 0,
                                                                     int                 iEndCvtCrvSurMode             = 0,
                                                                     double              iStartScalarCvtOnSimilarCurve = 0.0,
                                                                     double              iEndScalarCvtOnSimilarCurve   = 0.0,
                                                               const CATMathVector     * iStartFixedG2Dir              = NULL,
                                                               const CATMathVector     * iEndFixedG2Dir                = NULL) = 0;

    // Imposition/liberation de torsions
    // (meme comportement que pour les courbures)
    //   SetTorsOnSimilarCurve(NULL, NULL, 0) impose les torsions de la base curve  ==> (   change     le comportement de l'operateur)
    //  (SetTorsOnSimilarCurve(NULL, NULL) ne les impose pas contrairement a ce qui etait indique avant NLD110516)
    //   SetTorsOnSimilarCurve(NULL, NULL, 3) libere les torsions                   ==> (ne change pas le comportement de l'operateur)
    //
    // DO NOT USE IN 2D MODE (NLD181116)
    // ---------------------
  virtual void                        SetTorsOnSimilarCurve   (const CATMathVector     * iStartCvtOnSimilarCurve       , 
                                                               const CATMathVector     * iEndCvtOnSimilarCurve         ,
                                                                     CATLONG32           NullAreFree                   = 3) = 0;

    // iAlwaysReNormTgt = 0 -> est le mode par defaut impose par Toyota.
    //                         A la demande Toyota, donc pour le ConnectCurve en mode Base Curve, on ne renorme
    //                         pas systematiquement les tangentes aux extremites
    // iAlwaysReNormTgt = 1 -> est preferable pour eviter des oscillations
    // Tout ceci n'est pas tres clair (JSX180510)
    // - Lorsque l'utilisateur "impose" une derivée (c'est une direction) sa norme
    //   est modifiée afin de correspondre à la norme de la BaseCurve.
    // - Ensuite le ratio de la distance(PointDeb, Pointfin) mesurée sur la Base Curve et le resultat
    //   est appliqué pour tenir compte du "scaling" de la courbe
    // - Si iAlwaysReNormTgt= 0, le ratio des distances n'est pas appliqué si une tangente n'est pas imposée
    //   (i.e si on deforme un seul coté l'autre cote ne bouge pas en point et derivée premiere)
  virtual void                        SetAlwaysReNormExtTgt   (      int                 iAlwaysReNormTgt              = 1) = 0;

    // Imput target derivative are given with curvilinear parametrization
    // ||targtn|| is suppose to be 1 !
    // But data are rescaled to fit BaseCurveParametrization
    // This enable small correction of Direction/Curvature without
    // changing BC parametrization
  virtual void                        SetCurvilinearTarget    (      int                 iCurvilinear                  = 1) = 0; 

    // Active le controle de non rebroussement de la similar par rapport a la base curve
  virtual void                        SetCuspControl          (      int                 iActiveCuspControl            = 1) = 0;

    // Pour tester je veux pouvoir passer une MultiForm. MNA

  virtual void                        SetMFForSimilar         (const CATFrFNurbsMultiForm* iNurbsForSimilar            ,
                                                                     int                   iNbCurves                   )    = 0;

  virtual void            SetMatrixChangeKnotVectorComputation(      CATBoolean            iMatrixComputation          = 1) = 0;

  virtual void            SetComputeDeformation               (      CATBoolean            iDeformComputation          = 1) = 0;

  virtual CATLONG32       SetNormalReparametrisationForC1Mode (      CATLONG32             iForceNormalReparametrisationForC1) = 0;

    // Run
    // CODE RETOUR : VOIR INIT()
  virtual int                         Run                     () = 0;


  virtual void                        GetSimilarCurve         (       CATLISTP(CATCurve)     & oListOfSimilarCurves      ,
                                                                      CATLISTP(CATCrvLimits) & oListOfSimilarCurvesLimits,
                                                                      CATListOfInt           & oListOfSimilarCurvesOrns  ) = 0;

    // Return deformation on last run with deformation
  virtual double                      GetDeformation          () = 0;

    //                                                                // MNA pour tester
  virtual CATFrFNurbsMultiForm      * GetMFForSimilar         () = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMFrFSimilarCurve(); // -> delete can't be called
};

// iSimilar2D=1 dans le cas ou les BasesCurves sont des PCurves
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFrFSimilarCurve *CATPGMCreateFrFSimilarCurve(
  CATGeoFactory            *  iFactory,
  CATSoftwareConfiguration *  iSoftwareConfiguration,
  CATLISTP(CATCurve)        & iListOfBaseCurves,
  CATLISTP(CATCrvLimits)    & iListLimitsOfBaseCurves,
  CATListOfInt              & iListOrnOfBaseCurves,
  int iSimilar2D = 0);

// Nouveau constructeur avec des MF deja orientees dans le bon sens.
// Attention : mettre toutes les courbes dans une seule MF
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFrFSimilarCurve *CATPGMCreateFrFSimilarCurve(
  CATGeoFactory            *  iFactory,
  CATSoftwareConfiguration *  iSoftwareConfiguration,
  CATFrFNurbsMultiForm     *  iNurbsForSimilar);

#endif /* CATIPGMFrFSimilarCurve_h_ */
