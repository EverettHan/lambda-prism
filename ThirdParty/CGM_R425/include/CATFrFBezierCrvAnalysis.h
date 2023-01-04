/*-*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 2001 
//==========================================================================
//
// CATFrFBezierCrvAnalysis:
//
//   Ceci est un Check pour les MultiFormes composées d'ARCS de BEZIER
//
//  Entree : une multiforme qui DOIT etre C0 par arc
//  ATTENTION : Si on souhaite checker un element avec plusieurs profondeurs de
//  subdivision differentes, il faut creer autant d'objet CATFrFBezierCrvAnalysis
//  que de profondeur de subdivision.
//  Une profondeur = 5 obtient de bons resultats (=> valeur par defaut)
//
//========================================================================== 
//   /02/01 CCK Creation
//   /01/03 PRG Integration des MF2D - on ajoute les equations du support
// 19/08/05 HLN Ajout d'une option d'analyse plus complete, d'une methode
//              CuspDetectionOnBezierArc d'analyse plus complete (argument ioLParamInnerCusp en plus)
//              pour corriger la geometrie
// 28/03/08 NLD Renommons _CurvatureTolerance en _CurvatureRadiusTolerance
// 12/11/13 NLD Suppression des mal nommes compteurs statiques
//              (NbMultiFormEntrees et l'inenarrable NbMultiFormFouareuses)
//              Deplacement de l'interface vers l'implementation de
//                - GetINumOfDegeneratedArcsOrPatchs     ()
//                - GetINumOfArcsOrPatchsWithNullTangents()
//                - GetILParamInnerCusp                  ()
//              Ajout _CGMLevel, _XScaleDebugV1
//========================================================================== 
#ifndef CATFrFBezierCrvAnalysis_H
#define CATFrFBezierCrvAnalysis_H

#include "CATGeoFactory.h"
#include "CATCrvNurbsSpecDiagnostic.h"
#include "YP00IMPL.h"
#include "CATCGMVirtual.h"

class CATMathNurbsMultiForm;
class CATFrFNurbsMultiForm;
class CATMathFunctionXY;

//-----------------------------------------------------------------------------
class ExportedByYP00IMPL CATFrFBezierCrvAnalysis  : public CATCGMVirtual
{
  public :
    // MultiForm Constructor
    CATFrFBezierCrvAnalysis                                  (CATFrFNurbsMultiForm* iNurbsMF,
                                                              CATGeoFactory       * iFactory);

    // 2D MultiForm Constructor
    CATFrFBezierCrvAnalysis                                  (CATFrFNurbsMultiForm* iNurbsMF               ,
                                                              CATGeoFactory       * iFactory               ,
                                                              CATMathFunctionXY   * iSupportXGlobalEquation,
                                                              CATMathFunctionXY   * iSupportYGlobalEquation,
                                                              CATMathFunctionXY   * iSupportZGlobalEquation);
    
    // Destructor
   ~CATFrFBezierCrvAnalysis();

    //==============================================================================
    // Methodes SET
    //  => A faire avant le Run()
    //==============================================================================

    // Set profondeur de subdivision    
    // Valeurs par defaut : 1 si _Degree==1 (droite 3D)
    //                      3 si 1<_Degree<4
    //                      5 sinon
    void                 SetHightSubd                        (CATLONG32& iNbSubd);

    // Set diagnostics a analyser
    void                 SetSpecDiag                         (CATCrvNurbsSpecDiagnostic* iSpecDiag);

    // hln Cusp
    // Set mode d'analyse d'un diagnostic donne : 0 normal (defaut), 1 complet
    // rem : le diagnostic doit etre actif (par SetSpecDiag), sinon inutile
    // rem : actuellement, fonctionne seulement pour le diag CATGeomNurbsCrvDiag_CuspInsideAnArc
    void                 SetAnalysisModePerDiag              (CATGeomNurbsDiagType iDiagType, CATLONG32 iAnalysisMode);

    //==============================================================================
    // Run : appelle tous les checks
    //  => Indispensable
      // Renvoie -1 si donnees invalides (non C0 par exemple)
      // Renvoie 0 si traitement correct
    //==============================================================================
    CATLONG32            Run();

    //==============================================================================
    // Methodes GET
    //  => A faire apres le Run()
    //==============================================================================

    // Longueur totale, approchee, de la forme IndForm
    // retourne 0, ou 1 si erreur dans le process
    CATLONG32            GetCrvLengthApprox                  (CATLONG32 iIndForm, double& oFormLength);

    // Longueur approchee de l'arc IndArc de la forme IndForm
    // retourne 0, ou 1 si erreur dans le process
    CATLONG32            GetArcLengthApprox                  (CATLONG32 iIndForm, CATLONG32 iIndArc, double& oArcLength);

    // Longueur approchee de tous les arcs de la forme IndForm
    // retourne 0, ou 1 si erreur dans le process
    // oArcLength est alloue par un new double[]
    // La destruction de oArcLength doit etre faite par l'appelant
    CATLONG32            GetAllArcLengthApprox               (CATLONG32 iIndForm, double*& oArcLength);

    // Tableau de la validite des tangentes initiales de chaque arc (0 : invalide, 1 : valide)
    // Tableau de la validite des tangentes finales de chaque arc
    // retourne 0, ou 1 si erreur dans le process
    // oInitTgtValid et oEndTgtValid sont alloues par new CATLONG32[]
    // Leurs destructions reviennent a l'appelant
    CATLONG32            GetTgtAtArcExtremities              (CATLONG32*& oInitTgtValid,
                                                              CATLONG32*& oEndTgtValid);

    // renvoie le nombre de diagnostics ou pathologies detectees
    CATLONG32            GetNbDiagnostics                    ();

    // Retourne le diagnostic numero iNumdiag (entre 1 et nbDiagnostics)
    CATGeomNurbsDiagType GetDiagnostic                       (CATLONG32 iNumDiag);

    CATListOfInt       * GetINumOfDegeneratedArcsOrPatchs     ();
    CATListOfInt       * GetINumOfArcsOrPatchsWithNullTangents();

    // hln Cusp
    CATListOfDouble    * GetILParamInnerCusp                  ();

    //  oDiag = forms degenerees : 1 = Start, 2 = End, 3 = Both (0 = Nothing Detected)
    CATLONG32            GetDegenBorderInfo                   (CATLONG32 & oDiag);

   protected :
    // lit les donnees sur la multiforme,
    // fait la duplication si necessaire
    void                 DataInitialisation                   ();

    void                 CPsInitialisation                    ();

    // CheckLengthDegenerated
    // retourne :
    // 0 si la longueur de l'arc est < toleranceV5 de facon sure => arc invalide
    // 1 si la longueur de l'arc est > toleranceV5 de facon sure => arc valide
    // -1 si on ne sait pas dire de facon rapide
    CATLONG32            CheckLengthDegenerated               (CATLONG32 IndForm, CATLONG32 IndArc, CATLONG32& diag);


    //  CheckTgtOnExtremities
    //  la tangente ne doit pas s'annuler (norme < résolution) aux points 
    //  extrémités de la courbe. 
    //  tgtNull vaut : 
    //      0 si les 2 tangentes aux extremites de l'arc sont non nulles (ie valides)
    //    1 si la tangente initiale de l'arc est nulle et seulement elle
    //    2 si la tangente finale de l'arc est nulle et seulement elle
    //    3 si les 2 tangentes aux extremites de l'arc sont nulles
    CATLONG32            CheckTgtOnExtremities                (CATLONG32 IndForm, CATLONG32 IndArc, CATLONG32& tgtNull);
    CATLONG32            CheckTgtOnExtremitiesWhithGoodParam  (CATLONG32 IndForm, CATLONG32 IndArc, CATLONG32& tgtNull); 

    CATLONG32            BadParametrisation                   (CATLONG32 IndForm, CATLONG32 IndArc, CATLONG32& BadParam);

    CATLONG32            ArcOutsideCatiaSpace                 (CATLONG32 IndForm, CATLONG32 IndArc, CATLONG32& OutSide);

    CATLONG32            CheckMicroCurvature                  (CATLONG32 iIndForm, CATLONG32 iIndArc);

    void                 CreateDebugDiagnostic                (CATLONG32       i,
                                                               CATLONG32       j,
                                                               CATLONG32       ArcTooShort,
                                                               CATLONG32       ExtTgtNull ,
                                                               CATLONG32       Cusp,
                                                               CATLONG32       OutSideCatiaSpace,
                                                               CATLONG32       JunctionCusp,
                                                               CATLONG32       BadParam,
                                                               CATLONG32       MicroCurvature,
                                                               CATNurbsCurve*& BezierArc);

    // check de degenerescence 
    CATLONG32 CheckGlobalLength                               (CATLONG32&      isDegenerated);
    CATLONG32 HasConfusedBoundaries                           (CATMathPoint*   CPs, CATLONG32 nbCPsU, CATLONG32 nbCPsV, CATLONG32& diag);
    CATLONG32 IsClosedButNotDegenerated                       (CATMathPoint*   CPs, CATLONG32 nbCPsU, CATLONG32 nbCPsV,
                                                               CATLONG32       iNumKMiddle,
                                                               CATLONG32     & isClosedAndNotDegenereted);
   


   private :
      void Compute3DDistance(const CATMathPoint& P1,
                             const CATMathPoint& P2,
                                   double      & distance,
                                   CATLONG32     squareDistanceNeeded = 0);

      // 
      CATLONG32 IntersPnSeg(const CATMathPoint  &P        ,
                            const CATMathVector &T        ,
                            const CATMathVector &SegNormed,
                            const CATMathPoint &P1        ,
                            const CATMathPoint &P2        ,
                                  double       &Distance  );
    // check normal
      CATLONG32 CuspDetectionOnBezierArc(CATLONG32 IndForm, CATLONG32 IndArc, CATLONG32& cuspDetected);

    // hln Cusp
    // check complet
      CATLONG32 CuspDetectionOnBezierArc(CATLONG32 IndForm, CATLONG32 IndArc, CATLONG32& cuspDetected,
                                         CATListOfDouble &ioLParamInnerCusp);

      CATLONG32 ArcPolygoneLength(CATLONG32 IndForm, CATLONG32 IndArc, double& length);
      CATLONG32 CuspAtArcJunction(CATLONG32 IndForm, CATLONG32 IndArc, CATLONG32& cuspDetected);

    // Si on ne veut la subd que pour la longueur => OnlyForLength = 1
    // Pour gestion des destructeurs....
      CATLONG32 SubdArcAndEstimateLength(CATLONG32 iIndForm, CATLONG32 iIndArc, CATLONG32 OnlyForLength);

      void      VisuFormToAnalyse();
      void      VisuCltPtFormAfterSubd();

      CATFrFNurbsMultiForm*      _NurbsMF;
      CATFrFNurbsMultiForm*      _C0NurbsMF;
      CATGeoFactory*             _Factory;
      CATMathPoint*              _CP;
      CATLONG32                  _Degree;
      CATLONG32                  _NbKnots;
      CATLONG32                  _NbForm;
      double*                    _ArcLengthAfterSubd;
      double*                    _CrvLengthAfterSubd;
      CATLONG32                  _NbSubd;
      CATLONG32                  _CPTooCloseWarning;
      CATMathSetOfPoints*        _CtrlPtsAfterSubd;
      double                     _InitialPolygoneLength;
      CATLONG32*                 _InitTgtValid;           // 0 si InitTgt invalide, 1 sinon
      CATLONG32*                 _EndTgtValid;            // 0 si EndTgt  invalide, 1 sinon
      CATLONG32                  _MicroCurvature;

      // Variables pour la gestion de vie des elements
      CATLONG32                  _GetTtgDone;
      CATLONG32                  _GetSpecDiagDone;

      CATCrvNurbsSpecDiagnostic* _SpecDiag;
      double                     _ArcLengthTolerance;
      double                     _TgtTolerance;
      double                     _InsideAngleMin;
      double                     _JunctionAngleMin;
      double                     _Ratio;
      double                     _Infinite;
      double                     _MinDist;
      double                     _CrvLengthTolerance;
      double                     _CurvatureRadiusTolerance;
      double                     _DegenBorderTol;
      // hln Cusp
      CATLONG32                  _analmodeInnerCusp;
      CATLONG32                  _staTip;
      CATLONG32                  _endTip;

      CATListOfInt               _pathologies;
      CATLONG32                  _nbPathologies;

      CATListOfInt*              _iNumArcsOrPatchsTooSmall;
      CATListOfInt*              _iNumArcsOrPatchsWithNullTangent;
      // hln Cusp
      CATListOfDouble*           _iLParamInnerCusp;
      CATLONG32                  _DegenBorderInfo;

      CATMathFunctionXY*         _supportXGlobalEquation;
      CATMathFunctionXY*         _supportYGlobalEquation;
      CATMathFunctionXY*         _supportZGlobalEquation;

      CATLONG32                  _iDimCrv;

      int                        _CGMLevel;
      int                        _XScaleDebugV1;
};
#endif
