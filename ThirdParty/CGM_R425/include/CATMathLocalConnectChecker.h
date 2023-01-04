#ifndef CATMathLocalConnectChecker_H
#define CATMathLocalConnectChecker_H

   #define CATMathLocalConnectChecker_G2RatioIsAlwaysAPercent     "modifs conjuguees .h .cpp et CATConnectCheckerInterfaceOfCurveSurface.cpp"


// #define CATMathLocalConnectCheckerModifyG2RatioCurveSurface    "Appelants detectés: CATConnectCheckerInterfaceOfCurveSurface"
// #define CATMathLocalConnectCheckerModifyG2RatioSurfaceSurfaceA "Appelants detectés: CATConnectCheckerInterfaceOfSurfaces CATFrFSurLocalConnectChecker FrFOpeSurUtilities"
// #define CATMathLocalConnectCheckerModifyG2RatioSurfaceSurfaceB "Appelants detectés: CATConnectCheckerInterfaceOfSurfaces CATFrFSurLocalConnectChecker"
// #define CATMathLocalConnectCheckerModifyG2RatioCurveCurve      "Appelants detectés: CATConnectCheckerInterfaceOfCurves"

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2005
//=============================================================================
//
// CATMathLocalConnectChecker:
//  Base class for local computation of geometric continuity between two
//  geometries (Curve or Surface) with mathematical input data.
//
//  Inputs of class methods consist in containers (for curve or surface)
//  that allows to record all the required mathematical data that will be
//  used for the requested computation.
//
// Usage notes:
//
// * ComputeG0Continuity requires G0Continuity order for inputs.
// * ComputeG1Continuity requires G1Continuity order for inputs.
// * ComputeG2Continuity requires G1Continuity and G2Continuity
//   orders for inputs.
// * ComputeG3Continuity requires G1Continuity, G2Continuity and
//   G3Continuity orders for inputs.
//
// All methods return an integer as diagnostic:
// * 1 if computation succeded. Then outputs are relevant.
// * 0 is returned if computation failed (not adequate data stored for required
//   order, critical singularity, etc.). Be careful, if 0 is returned, outputs
//   are irrelevant. 
//
//=============================================================================
// Oct   05 CQI Creation                                                    CQI
// 01/07/08 MWE ajout du champ _Resolution
// 09/10/08 NLD Ajout _Scale et _SquareScale
// 10/10/08 NLD Ajout iTolObject en argument du constructeur et de InitializeTolerances()
//              et _TolObject
// 19/09/18 MWE activation du SetTolerances
// 02/10/18 NLD Correction de la documentation de iTol3D dans SetTolerances
// 05/10/18 NLD Desactivation de SetTolerances() et split en 3 méthodes
// 17/12/21 NLD Mise au propre; smart indent
//              Ajout iConfig dans constructeur, et _Config
// 21/12/21 NLD Mise en compatibilité avant livraison du versionning et de l'architecture des frameworks
//              Remplacement de iConfig, _Config par un système basé sur CATMathVersionning (nouveauté)
//              avec iActiveVers1 et _ActiveVers1
//              (et  iActiveVers2 et _ActiveVers2 en prévisionnel pour test)
//              Essentiellement à titre expérimental/intellectuel/didactique
//              _ActiveVers1 declenche correction XScale de la tolerance de torsion de ComputeG3Continuity()
//              avec CGM_Versionning_Sweep_XScaleR32SP2 (après 32000 transitoirement)
//              (car CGM_Versionning_Sweep_XScaleR32SP1 a son créneau déjà fermé on va livrer en SP2)
// 24/05/22 NLD Pilotage par option de précompilation globale et en cohérence
//              de la mise en cohérence du cas courbe/surface avec les autres
//              pour rendre un pourcentage et non plus un ratio
//=============================================================================


#include "CATTolerance.h"
#include "YN000ANL.h"

#include "CATMathLimits.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMathCurveGData.h"
#include "CATMathSurfaceGData.h"
#include "CATMathVersionning.h"
#include "CATTolerance.h"

class CATCGMVirtual;
class CATSoftwareConfiguration;

class ExportedByYN000ANL CATMathLocalConnectChecker : public CATCGMVirtual
{

  #ifdef CATMathLocalConnectCheckerCPP
   // #define CATMathLocalConnectCheckerActiveVers1() 0
   // #define CATMathLocalConnectCheckerActiveVers2() 0
   #else

   #define CATMathLocalConnectCheckerActiveVers1(iConfig)                   \
      CATMathVersionningActive(iConfig, CGM_Versionning_Sweep_XScaleR32SP2) //
   // CATMathVersionningActive(iConfig, CGM_Versionning_Sweep_XScaleR32SP1) //

   // future use
   #define CATMathLocalConnectCheckerActiveVers2(iConfig)                   \
      CATMathVersionningActive(iConfig, CGM_Versionning_XXXXXXXXXXXXXXXXXX) //

   #define CATMathLocalConnectCheckerConfigMacro(iConfig)                   \
      CATMathLocalConnectCheckerActiveVers1(iConfig)                        //
  // ,CATMathLocalConnectCheckerActiveVers2(iConfig)                        //
  #endif

   // ------------------------------------------------------------------------------------
   // N.B versionning rules for this object
   //     - this object implementation must define CATMathLocalConnectCheckerCPP before header file inclusion
   //     - object callers may define CATMathLocalConnectCheckerConfig by precompilation directive
   //       otherwise, it will be used as argument
   // ------------------------------------------------------------------------------------
    // Calling example
   //    CATSofwtareConfiguration* Config = 
   //    CATMathLocalConnectChecker(CATGetTolerance(_Factory),
   //                               CATMathLocalConnectCheckerConfigMacro(Config));
   // ------------------------------------------------------------------------------------

public:
   CATMathLocalConnectChecker(const CATTolerance            & iTolObject   ,
                                    int                       iActiveVers1  // MANDATORY USE OF CATMathLocalConnectCheckerConfigMacro
                                 // int                       iActiveVers2  // 
                             );
                                //  CATSoftwareConfiguration* iConfig   );
  ~CATMathLocalConnectChecker();

  // ------------------------------------------------------------------------------------
  //
  // CURVE / CURVE DEDICATED METHODS
  //
  // ------------------------------------------------------------------------------------
  //
  // ComputeG0Continuity
  //
  // Returns in oG0Error the G0-error at a Curve/Curve connection point:
  // oG0Error = ||P1 - P2|| distance
  //
  int ComputeG0Continuity(CATMathCurveGData   & iData1           ,
                          CATMathCurveGData   & iData2           ,
                          double              & oG0Error         );

  //
  // ComputeG1Continuity
  //
  // Returns in oG1Error the G1-error at a Curve/Curve connection point
  // oG1Error = Angle(TangentToCurve1,TangentToCurve2) in [0,PI]
  //
  int ComputeG1Continuity(CATMathCurveGData   & iData1           ,
                          CATMathCurveGData   & iData2           ,
                          double              & oG1Error         );

  //
  // ComputeG2Continuity
  //
  // Returns the G2-error at a Curve/Curve connection point:
  //
  // Connect Checker like computation:
  // --------------------------------
  //  oG2Ratio = |Curvature2 - Curvature1| / max(Curvature1, Curvature2) in [0,1]
  //             (in fact, multiplied by 100 to obtain a percentage; old behavior since first code version; comment NLD270522)
  //  oG2Angle =  Angle( NormalToCurve1, NormalToCurve2 ) in [0,PI]
  //
  // Curve Smooth like computation: (alternative G2 measure - optionnal)
  // ------------------------------
  //  oG2Delta = ||CurvatureVector2 - CurvatureVector1|| / max(Curvature1, Curvature2)  in [0,1]
  //  oG2Error = 1. / ( 1. + oG2Delta );
  //
  int ComputeG2Continuity(CATMathCurveGData   & iData1           ,
                          CATMathCurveGData   & iData2           ,
                          double              & oG2Ratio         ,
#ifdef CATMathLocalConnectCheckerModifyG2RatioCurveCurve
                          int                   iDummyArg        ,
#endif
                          double              & oG2Angle         ,
                          double              * oG2Delta         = NULL,
                          double              * oG2Error         = NULL);
  
  //
  // ComputeG3Continuity
  //
  // Returns in oG3Error the G3-error at a Curve/Curve connection point:
  // oG3Error = Angle( dR1/ds1 , dR2/ds2 ) in [0,PI] , where dR1/ds1 and dR2/ds2 denote the radius
  //                                                   of curvature vector first derivatives of
  //                                                   curve 1 and 2 associated to arc length s
  //
  int ComputeG3Continuity(CATMathCurveGData   & iData1           ,
                          CATMathCurveGData   & iData2           ,
                          double              & oG3Error         );

  // ------------------------------------------------------------------------------------
  //
  // SURFACE / SURFACE DEDICATED METHODS
  //
  // ------------------------------------------------------------------------------------
  //
  // ComputeG0Continuity
  //
  // Returns in oG0Error the G0-error at a Surface/Surface connection point:
  // oG0Error = ||P1 - P2|| distance
  //
  int ComputeG0Continuity(CATMathSurfaceGData & iData1         ,
                          CATMathSurfaceGData & iData2         ,
                          double              & oG0Error       );

  //
  // ComputeG1Continuity
  //
  // Returns in oG1Error the G1-error at a Surface/Surface connection point
  // oG1Error = Angle(NormalToSurface1,NormalToSurface2) in [0,PI]
  //
  int ComputeG1Continuity(CATMathSurfaceGData & iData1         ,
                          CATMathSurfaceGData & iData2         ,
                          double              & oG1Error       );

  //
  // ComputeG2Continuity
  //
  // Returns the G2-error at a Surface/Surface connection point:
  // oG2Ratio       = |NormalCurvature2 - NormalCurvature1| / max(NormalCurvature1, NormalCurvature2)
  //             (in fact, multiplied by 100 to obtain a percentage; old behavior since first code version; comment NLD270522)
  // oSameConvexity = 1 if convexity is the same for both surfaces (ie. normals scalar product is positive)
  //                  0 otherwise (opposite normals)
  //
  int ComputeG2Continuity(CATMathSurfaceGData & iData1         ,
                          CATMathSurfaceGData & iData2         ,
                          double              & oG2Ratio       ,
#ifdef CATMathLocalConnectCheckerModifyG2RatioSurfaceSurfaceA
                          int                   iDummyArg      ,
#endif
                          int                 & oSameConvexity ,
                          double              * oNormalCurv1   = NULL,
                          double              * oNormalCurv2   = NULL);
  
  //
  // ComputeG3Continuity
  //
  // Returns in oG3Error the G3-error at a Surface/Surface connection point:
  // oG3Error = Angle( dR1/ds1 , dR2/ds2 ) in [0,PI] , where dR1/ds1 and dR2/ds2 denote the radius
  //                                                   of curvature vector first derivatives of
  //                                                   curve 1 and 2 associated to arc length s
  //
  // Curve 1 and Curve 2 are 3D intersection curves between normal plane / surfaces.
  //
  // NB.: if oG2Ratio and oSameConvexity are given, G2-continuity computation is made (single call: increase performance)
  //      (same computation as inComputeG2Continuity())
  int ComputeG3Continuity(CATMathSurfaceGData & iData1         ,
                          CATMathSurfaceGData & iData2         ,
                          double              & oG3Error       ,
#ifdef CATMathLocalConnectCheckerModifyG2RatioSurfaceSurfaceB
                          int                   iDummyArg      ,
#endif
                          double              * oG2Ratio       = NULL,
                          int                 * oSameConvexity = NULL);

  // ------------------------------------------------------------------------------------
  //
  // CURVE / SURFACE DEDICATED METHODS
  //
  // ------------------------------------------------------------------------------------
  //
  // ComputeG0Continuity
  //
  // Returns in oG0Error the G0-error at a Curve/Surface connection point:
  // oG0Error = ||P1-P2|| distance
  //
  int ComputeG0Continuity(CATMathCurveGData   & iData1         ,
                          CATMathSurfaceGData & iData2         ,
                          double              & oG0Error       );

  //
  // ComputeG1Continuity
  //
  // Returns in oG1Error the G1-error at a Curve/Surface connection point
  // oG1Error = | Angle(TangentToCurve,NormalToSurface) - PI/2 | in [0,PI/2]
  //
  int ComputeG1Continuity(CATMathCurveGData   & iData1         ,
                          CATMathSurfaceGData & iData2         ,
                          double              & oG1Error       );

  //
  // ComputeG2Continuity
  //
  // Returns the G2-error at a Curve/Surface connection point:
  // oG2Ratio = | Kc - Ks | / max( Kc , Ks )
  //  , where Kc is the projection length of the curvature vector of the curve over the normal plane to surface
  //          Ks is curvature value of the normal section of the surface
  //
  // CAUTION: here in historical code oG2Ratio is really a ratio and not a percentage
  //          (unlike in other ComputeG2Continuity() signatures)
  //          NLD270522
  #ifdef CATMathLocalConnectChecker_G2RatioIsAlwaysAPercent
  // now converted in a perecentage
  #endif
  // oSameConvexity = 1 if curvature vectors have the same orientation, 0 if we have a lack of same convexity
  //
  int ComputeG2Continuity(CATMathCurveGData   & iData1         ,
                          CATMathSurfaceGData & iData2         ,
                          double              & oG2Ratio       ,
#ifdef CATMathLocalConnectCheckerModifyG2RatioCurveSurface
                          int                   iDummyArg      ,
#endif
                          int                 & oSameConvexity );

  // ------------------------------------------------------------------------------------
  //
  // TOLERANCES MANAGEMENT
  //
  // ------------------------------------------------------------------------------------
  
  //
  // iZero3D          = null vector tolerance, 1.e-9 by default. Used to check the null derivatives and the colinearity of derivatives vectors.
  //                    XScale: must be scale independant; NLD021018
  // iCRBmin, iCRBmax = zero-curvature and infinite curvature tresholds
  // iNumTol          = absolute numerical tolerance used as a zero-treshold
  //                    XScale: must be scale independant; NLD021018
  // CQI       SetTolerances à 4 arguments, inactive, mauvaise documentation de iZero3D
  // MWE190918 SetTolerances à 4 arguments, activée en l'état
  // NLD051018 SetTolerances inactivée; ajout de SetZero3D(), SetCurvatureTolerances(), SetNumericalTol()
//             (ne pas rendre obligatoire la redefinition de iZero3D lorsqu'on définit les tolérances de courbure)
//void SetTolerances         (double iZero3D, double iCRBmin, double iCRBmax, double iNumTol = CATGetDefaultTolerance().EpsgForRelativeTest());

  void SetZero3D             (double iZero3D);

  void SetCurvatureTolerances(double iCRBmin, double iCRBmax);

  void SetNumericalTolerance (double iNumTol); // default value CATGetDefaultTolerance().EpsgForRelativeTest()
private:

  void InitializeTolerances(const CATTolerance& iTolObject);
  
  // - Internal tolerances
        double                     _Tol2       ;  // ce carré est une tolerance relative. (adaptee au scale 1) (NLD101008)
        double                     _CRBmin     ;
        double                     _CRBmax     ;
        double                     _NumTol     ;
        double                     _Resolution ;
        double                     _Scale      ;
        double                     _SquareScale;
  const CATTolerance             * _TolObject  ;

  // Versionning
//      CATSoftwareConfiguration * _Config     ;
        int                        _ActiveVers1; // Versionning XScale de la tolerance de torsion
//      int                        _ActiveVers2; // as example; reserved for future use

};

#endif

