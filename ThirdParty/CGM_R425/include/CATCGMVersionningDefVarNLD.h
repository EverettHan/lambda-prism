#ifndef CATCGMVersionningDefVarNLD_h
#define CATCGMVersionningDefVarNLD_h

//******* Fichier Special NLD, non standard, permettant d'eviter les
//******* impacts stupides de DefVarCSS lors du calcul des odts a rejouer
//******* N'est pas destine a etre inclus dans DefVar6 ou autre
//******* Usage reserve NLD
// 23/10/08 NLD Creation
//-------------------------------------------------------------------------------------
// Exemple:
//      #ifndef CGM_Versionning_XXX
//      #define CGM_Versionning_XXX 32000
//      #endif

//-------------------------------------------------------------------------------------
// N.B NLD261005 je peux referencer plusieurs fois TestOnly1 et TestOnly2,
//  pas grave, genant seulement pour les tests
//-------------------------------------------------------------------------------------
#include <CATCGMVersionningDefVar2.h>

// CATSpineConnexSpace le 140622 
// CGMShapeTests.tst/CGMShapeOperators.m/src/Test_SweepExtrapol01.cpp
// CGMSurfacicTests.tst/SurfSweep.m/src/TestTopSpine6.cpp
// #ifndef CGM_Versionning_Extrapol_SpineConnexSpaceSecurity
// #define CGM_Versionning_Extrapol_SpineConnexSpaceSecurity CGM_Versionning_Sweep_TestOnly1
// #endif

// CATPolyMeshMappingFunctionTopoTools le 190522
// #ifndef CGM_Versionning_AllCGM_DeploySoftwareConfigurationV11
// #define CGM_Versionning_AllCGM_DeploySoftwareConfigurationV11 CGM_Versionning_Sweep_TestOnly1
// #endif

// CATHomotopyCrvSurCx2 le 190522
// #ifndef CGM_Versionning_Homotopy_CrvSur_Security
// #define CGM_Versionning_Homotopy_CrvSur_Security CGM_Versionning_Sweep_TestOnly1
// #endif

// CATParallelCutter    le 170522
// #ifndef CGM_Versionning_ParallelCutterTwistedPieceV2
// #define CGM_Versionning_ParallelCutterTwistedPieceV2 CGM_Versionning_Sweep_TestOnly1
// #endif

// CATParallelCutter le 170522
// #ifndef CGM_Versionning_ParallelCutter_TwistInterpolSecondDerV2
// #define CGM_Versionning_ParallelCutter_TwistInterpolSecondDerV2 CGM_Versionning_Sweep_TestOnly2
// #endif

// divers sources geometriques le 100522
// #ifndef CGM_Versionning_Sweep_XScaleR32SP3
// #define CGM_Versionning_Sweep_XScaleR32SP3 CGM_Versionning_Sweep_TestOnly1
// #endif

// CATIntersectionCrvCrvCx2 le 19/04/22
//#ifndef   CGM_Versionning_IntersectionCrvCrv_BestPoint_ReconvergeV2
//  #define CGM_Versionning_IntersectionCrvCrv_BestPoint_ReconvergeV2                  CGM_Versionning_Sweep_TestOnly1
//#endif

// TwistDetectionOnSweep le 22/03/22
//#ifndef   CGM_Versionning_Sweep_TwistDetection_AreaManagementV3Bis
//  #define CGM_Versionning_Sweep_TwistDetection_AreaManagementV3Bis                  CGM_Versionning_Sweep_TestOnly1
//#endif

// CATMathDirectMinimizerXY le 080322
//#ifndef   CGM_Versionning_Sweep_XScaleR32SP2_R424FD03
//  #define CGM_Versionning_Sweep_XScaleR32SP2_R424FD03                             CGM_Versionning_Sweep_TestOnly1
//#endif


// CATFrFTopologicalSweepCx2 et Sweep162 le 25/02/22
//#ifndef   CGM_Versionning_Sweep_Road_TangencyDiscontinuityInParallel
//  #define CGM_Versionning_Sweep_Road_TangencyDiscontinuityInParallel  CGM_Versionning_Sweep_TestOnly2
//#endif

// CATFrFImplicitSpineCx10 et TopSpine6 le 16/02/22
//#ifndef   CGM_Versionning_ImplicitSpine_LinearCaseInitialPointV1
//  #define CGM_Versionning_ImplicitSpine_LinearCaseInitialPointV1  CGM_Versionning_Sweep_TestOnly1
//#endif

// TwistDetectionOnSweep le 24/01/22
//#ifndef   CGM_Versionning_Sweep_TwistDetection_AreaManagementV3
//  #define CGM_Versionning_Sweep_TwistDetection_AreaManagementV3                     CGM_Versionning_Sweep_TestOnly1
//#endif

// divers  le 19/01/22 (4 sources de GeometricOperators)
//#ifndef   CGM_Versionning_AllCGM_DeploySoftwareConfigurationV10
//  #define CGM_Versionning_AllCGM_DeploySoftwareConfigurationV10               CGM_Versionning_Sweep_TestOnly2
//#endif



//#ifndef   CGM_Versionning_Sweep_XScaleR32SP2
//  #define CGM_Versionning_Sweep_XScaleR32SP2                                  CGM_Versionning_Sweep_TestOnly2
//#endif

// CATMappingDevelop le 13/10/21
//#ifndef   CGM_Versionning_Blend_Develop_StabilizeV1
//  #define CGM_Versionning_Blend_Develop_StabilizeV1                            CGM_Versionning_Sweep_TestOnly1
//#endif

// divers  le 06/10/21
//#ifndef   CGM_Versionning_AllCGM_DeploySoftwareConfigurationV9
//  #define CGM_Versionning_AllCGM_DeploySoftwareConfigurationV9               CGM_Versionning_Sweep_TestOnly2
//#endif

// divers

// #ifndef   CGM_Versionning_Sweep_XScaleR32SP1
//   #define CGM_Versionning_Sweep_XScaleR32SP1                                  CGM_Versionning_Sweep_TestOnly2
// #endif
// FreeFormOperators\FrFAdvancedOpeSur.m\src\CATFrFShapeEvaluator.cpp le 090821
//#ifndef   CGM_Versionning_Sweep_Side_C1DerivForFirstDeriv
//  #define CGM_Versionning_Sweep_Side_C1DerivForFirstDeriv                     CGM_Versionning_Sweep_TestOnly1
//#endif

// GeometricObjectsCGM\SurfaceCGM.m\src\CATFilletSurfaceCGM.cpp le 07/07/21
// GeometricOperators/Y30A3HGG.m/src/CATDistanceSurSurCx2.cpp   le 07/07/21
//#ifndef   CGM_Versionning_XScale_Geometry_R32_GA
//  #define CGM_Versionning_XScale_Geometry_R32_GA                               CGM_Versionning_Sweep_TestOnly1
//#endif

// GeometricOperators\Y30A3HGG.m\src\CATDistanceCrvSurCx2.cpp le 23/06/21
//#ifndef   CGM_Versionning_DistanceCrvSur_XScaleAndSecurity
//  #define CGM_Versionning_DistanceCrvSur_XScaleAndSecurity                     CGM_Versionning_Sweep_TestOnly2
//#endif

// CATSkinExtrapolationOperatorCx7 ...  le 16/06/21
// #ifndef   CGM_Versionning_Extrapol_C0PseudoUntwistV1
//   #define CGM_Versionning_Extrapol_C0PseudoUntwistV1                           CGM_Versionning_Sweep_TestOnly1
// #endif

// CATDynMassProperties3DCGM       ...  le 04/05/21
//#ifndef   CGM_Versionning_Sweep_XScaleR31SP4
//  #define CGM_Versionning_Sweep_XScaleR31SP4                                 CGM_Versionning_Sweep_TestOnly1
//#endif

// CATExtrudedSweepSurfaceByCircle ...  le 27/04/21
//#ifndef   CGM_Versionning_Sweep_CanonicOrientationV2
//  #define CGM_Versionning_Sweep_CanonicOrientationV2                         CGM_Versionning_Sweep_TestOnly1
//#endif

// divers  le 07/04/21
//#ifndef   CGM_Versionning_AllCGM_DeploySoftwareConfigurationV8
//  #define CGM_Versionning_AllCGM_DeploySoftwareConfigurationV8               CGM_Versionning_Sweep_TestOnly2
//#endif

// CATFrFWireHomogenization.cpp le 04/03/21
//#ifndef   CGM_Versionning_Sweep_HomogenizationWithLawScaling2
//  #define CGM_Versionning_Sweep_HomogenizationWithLawScaling2   CGM_Versionning_Sweep_TestOnly1
//#endif

// CATFrFWireHomogenization.cpp le 12/02/21
//#ifndef   CGM_Versionning_Sweep_Homogenization_ClosureSwap
//  #define CGM_Versionning_Sweep_Homogenization_ClosureSwap   CGM_Versionning_Sweep_TestOnly1
//#endif

// CATFrFImplicitSpineCx10.cpp le 29/01/21
//#ifndef   CGM_Versionning_Sweep_ImplicitSpine_StabilizePointsV3
//  #define CGM_Versionning_Sweep_ImplicitSpine_StabilizePointsV3   CGM_Versionning_Sweep_TestOnly1
//#endif

// CATSkinExtrapolationOperatorCx7.cpp le 161120
//#ifndef   CGM_Versionning_Defeature_FuzzyExtrapol_WarningsLvl1
//  #define CGM_Versionning_Defeature_FuzzyExtrapol_WarningsLvl1   CGM_Versionning_Sweep_TestOnly1
//#endif

// CATCrvCrvSweepCx2 le 041120
//#ifndef   CGM_Versionning_Loft_ClosedOnSpineV2
//  #define CGM_Versionning_Loft_ClosedOnSpineV2               CGM_Versionning_Sweep_TestOnly1
//#endif

// CATEuclidianParallelInitSystem le 280920
//#ifndef   CGM_Versionning_Sweep_XScaleR31SP2
//  #define CGM_Versionning_Sweep_XScaleR31SP2               CGM_Versionning_Sweep_TestOnly1
//#endif

// CATAnalysisPtSurGen et CATInterproxSurOne le 120620
//#ifndef   CGM_Versionning_AnalysisPtSurGen_BestSolutionInitV2
//  #define CGM_Versionning_AnalysisPtSurGen_BestSolutionInitV2               CGM_Versionning_Sweep_TestOnly1
//#endif


// CATFrFTopologicalSweepCx2 le 090620
//#ifndef   CGM_Versionning_Sweep_Road_NonIsotopoParallel
//  #define CGM_Versionning_Sweep_Road_NonIsotopoParallel               CGM_Versionning_Sweep_TestOnly2
//#endif

// divers ClassA le 150720
//#ifndef   CGM_Versionning_AllCGM_DeploySoftwareConfigurationV7
//  #define CGM_Versionning_AllCGM_DeploySoftwareConfigurationV7               CGM_Versionning_Sweep_TestOnly2
//#endif

// RelativeCCvOrientation() (FrFUtiMonopar.cpp)  le 110520
//#ifndef   CGM_Versionning_Blend_DefaultWireOrientationV2
//  #define CGM_Versionning_Blend_DefaultWireOrientationV2               CGM_Versionning_Sweep_TestOnly1
//#endif


// CATLawUtilities le 110520
//#ifndef   CGM_Versionning_Sweep_XScaleR31SP1
//  #define CGM_Versionning_Sweep_XScaleR31SP1               CGM_Versionning_Sweep_TestOnly1
//#endif


// CATFrFTopologicalSweepCx2 le 280420
//#ifndef   CGM_Versionning_Sweep_Road_RelimitSolverLaws
//  #define CGM_Versionning_Sweep_Road_RelimitSolverLaws               CGM_Versionning_Sweep_TestOnly1
//#endif

// CATFrFTopologicalSweepCx2 le 200420
//#ifndef   CGM_Versionning_Sweep_Heat2NoDeformedSpineV2
//  #define CGM_Versionning_Sweep_Heat2NoDeformedSpineV2               CGM_Versionning_Sweep_TestOnly1
//#endif

// CATExtruderBySweepWireInfo et CATFrFTopologicalSweepCx2 le 310320
//#ifndef   CGM_Versionning_Sweep_Discontinuity_Limit_Extrapol_V2Closed
//  #define CGM_Versionning_Sweep_Discontinuity_Limit_Extrapol_V2Closed               CGM_Versionning_Sweep_TestOnly1
//#endif

// CATFrFSpineDataCx10 le 250320
// #ifndef   CGM_Versionning_Sweep_SpineData_StabilizeSpineProfileInertia
//  #define CGM_Versionning_Sweep_SpineData_StabilizeSpineProfileInertia               CGM_Versionning_Sweep_TestOnly1
//#endif


// CATFrFTopologicalSweepCx2 le 170320
// #ifndef    CGM_Versionning_Sweep_RetryAfterPauloC0_FuckC19
//   #define CGM_Versionning_Sweep_RetryAfterPauloC0_FuckC19               CGM_Versionning_Sweep_TestOnly1
// #endif

// CATLawEquationDistCrv le 070220
//#ifndef    CGM_Versionning_LawEqDistCrv_RailRoadV3
//  #define CGM_Versionning_LawEqDistCrv_RailRoadV3                 CGM_Versionning_Sweep_TestOnly1
//#endif

// CATSweepBasic le 130120
//#ifndef    CGM_Versionning_SweepBasic_LoopOrderV2
//  #define CGM_Versionning_SweepBasic_LoopOrderV2                 CGM_Versionning_Sweep_TestOnly1
//#endif

// CATFrFTopologicalSweepCx2
//#ifndef    CGM_Versionning_Sweep_UseProfileEdgeOrientationInParallelV2
//  #define CGM_Versionning_Sweep_UseProfileEdgeOrientationInParallelV2                 CGM_Versionning_Sweep_TestOnly1
//#endif

//#ifndef CGM_Versionning_Sweep_XScaleR30SP1
//   #define CGM_Versionning_Sweep_XScaleR30SP1 CGM_Versionning_Sweep_TestOnly1
//#endif

// CATSurfaceToCanonic
//#ifndef CGM_Versionning_SurfaceToCanonic_TorusGreatIsoUSmallIsoV_V2
//   #define CGM_Versionning_SurfaceToCanonic_TorusGreatIsoUSmallIsoV_V2 CGM_Versionning_Sweep_TestOnly1
//#endif

// CATTwistDetectionOnSweep
// #ifndef    CGM_Versionning_Sweep_TwistDetection_RecomputeFormPoints
//   #define CGM_Versionning_Sweep_TwistDetection_RecomputeFormPoints                 CGM_Versionning_Sweep_TestOnly1
//#endif

// CATFrFTopologicalSweepCx2
// #ifndef    CGM_Versionning_Sweep_UseProfileEdgeOrientationInParallel
//   #define CGM_Versionning_Sweep_UseProfileEdgeOrientationInParallel                 CGM_Versionning_Sweep_TestOnly1
//#endif

// FreeFormOperators\FrFAdvancedObjects.m\src\CATFrFGeomRefElementCx2.cpp
// #ifndef   CGM_Versionning_Sweep_GeomRef_NormalOnSurfaceV2
//  #define CGM_Versionning_Sweep_GeomRef_NormalOnSurfaceV2                   CGM_Versionning_Sweep_TestOnly1
// #endif

// Mathematics\ProtectedInterfaces\CATCGMVersionningDefVar6.h
//

//#ifndef    CGM_Versionning_Sweep_XScaleR29SP3
//   #define CGM_Versionning_Sweep_XScaleR29SP3                   CGM_Versionning_Sweep_TestOnly1
//#endif

//#ifndef    CGM_Versionning_SetOfPointsMapX_Reconverge_Precision
//   #define CGM_Versionning_SetOfPointsMapX_Reconverge_Precision CGM_Versionning_Sweep_TestOnly2
//#endif



// FreeFormOperators\FrFAdvancedOpeSur.m\src\CATFrFShapeEvaluator.cpp
//#ifndef    CGM_Versionning_SweepVaria_PointInterpolation2bis
//   #define CGM_Versionning_SweepVaria_PointInterpolation2bis CGM_Versionning_Sweep_TestOnly1
//#endif
// FreeFormOperators\FrFObjects.m\src\CATLawEquationDistCrv.cpp
// FreeFormOperators\FrFObjects.m\src\CATLawEquationDistUtilities.cpp
// #ifndef    CGM_Versionning_LawEqDistCrv_RailRoadV2
//   #define CGM_Versionning_LawEqDistCrv_RailRoadV2 CGM_Versionning_Sweep_TestOnly1
//#endif

//
// FreeFormOperators\FrFAdvancedObjects.m\src\CATFrFImplicitSpineCx10.cpp
// #ifndef CGM_Versionning_Sweep_ImplicitSpine_StabilizePointsV2
// #define CGM_Versionning_Sweep_ImplicitSpine_StabilizePointsV2 CGM_Versionning_Sweep_TestOnly1
// #endif 
// #ifndef CGM_Versionning_Sweep_XScaleR28SP3
// #define CGM_Versionning_Sweep_XScaleR28SP3 CGM_Versionning_Sweep_TestOnly1
// #endif 

// CATFrFApproxCurveFunc le 151117
// #ifndef CGM_Versionning_ApproxCurve_PoteauRentrant
// #define CGM_Versionning_ApproxCurve_PoteauRentrant    CGM_Versionning_Sweep_TestOnly1
// #endif

//

// exemple ::

// CATFrFSpineDataCx10 le 090915
// CATFrFCompositeCurveCx2
// CGM_Versionning_Sweep_Security_R26SP1: trop tard pour delivrer le code associe sur le SP4
// #ifndef CGM_Versionning_Sweep_Security_R26SP1 
// #define CGM_Versionning_Sweep_Security_R26SP1 CGM_Versionning_Sweep_TestOnly1
// #endif


/*
#include "CATCGMVersionningDeclareCountDebug.h"
#ifdef CGM_Versionning_Sweep_DeploySoftwareConfigurationV12
#undef CGM_Versionning_Sweep_DeploySoftwareConfigurationV12
#endif
// une occurence par source
static int _MyCGM_Versionning_UseCount=CATCGMVersionningDeclareCountDebug();
#define CGM_Versionning_Sweep_DeploySoftwareConfigurationV12 (CATCGMVersionLevel_Sweep_DeploySoftwareConfigurationV12+CATCGMVersionningDeclareCountDebugBreak(_MyCGM_Versionning_UseCount)-1)
*/


#endif
