#ifndef CATCGMDiag_H
#define CATCGMDiag_H
/**
* @quickReview SRO 05:04:13
*/
//===============================================================================================================================================
// for enhanced relimitation impact of this particular exceptionnal management (on demand and control of applied scenarios),
//    ( ~  3 %  of scenarios for  CATCGMDiagnosis::Init at 01.08.2013 )
//
//           V5R23 : 3 687 ODT(s) impacted on 113 957 
//           R216  : 4 794 ODT(s) impacted on 146 147
//
//  coverage helper (should be effective with VSF impacted database computed from 2013.Week 35) 
//     in relationship with automation http://odtweb2e/dashboard/TAReportImpactPage.aspx
//     and for not yet  declared (optionnally) implicit detection  through CATCGMDiag_::_XXXX symbol
//
//  Warning about same numerical identifier with similar different string name
//      SweepWarning_UnknownSev_TopOpInMaxGapDetection_ERR_5012               +  TopOpInMaxGapDetection_ERR_5012 
//      SweepWarning_DUCSev_TopOpInSweepSmallEdge_ERR_7031                    +  TopOpInSweepSmallEdge_ERR_7031
//      SweepWarning_UnknownSev_TopOpInHybOpTooLowCGMLevelForOption_ERR_7564  +  TopOpInHybOpTooLowCGMLevelForOption_ERR_7564
//===============================================================================================================================================

#include "CATGMModelInterfaces.h"
#include "CATErrorDefs.h"


class CATCGMDiagnosis;

//----------------------------------------------------------------------------------------------------
// Helpers (optional in relationship with this exeptionnal management) with official automation 
//----------------------------------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATCGMDiag_ 
{
public:
  //----------------------------------------------------------------------------------------------------
  // For enhanced relimitation impact following introductions of diagnosis
  //     (even if one thousand type has already been generated)
  //
  // As so far generic data checker are dedicated to internal needs of convergent controls,
  //     or under developpement stage on small extracted unit test cases 
  //    but it remains inactivated in nominal customer scenario 
  //      for appropriate interactive response times with industrial scenarios.
  //    And on demand check can be historically managed through particular methodology such as CATCGMDiagnosis.
  //      
  //  Enhancing relimitations impacts is suggested here with  http://odtweb2e/dashboard/TAReportImpactPage.aspx
  //     imagining  if we introduce a new generic diagnosis  :
  //
  //   a) for all operators 
  //       CATCGMDiag_::ResultUnderWarning should indicated scenarios potentially covered under mecanisms.
  //
  //   b) specificallyt, according to (opened) versioning and associated generated data
  //       occurence rate of created diagnosis may be followed according
  //       to formula : CATCGMDiag_::_8501 / CATCGMDiag_::Before_8501  %
  //    thanks to intermediate processing (new check) introduced for filtering or not this new diagnosis 
  //--------------------------------------------------------------------------------------------------------------------------
  static void BeforeEvaluation( const CATErrorId  iErrorId );
  static void ResultUnderWarning() {};

  //----------------------------------------------------------------------------------------------------
  //  Internal managements
  //----------------------------------------------------------------------------------------------------
private :

  static void Before_XXXX( const CATErrorId  iErrorId )  {};
  static void Before_8501() {}; // TopOpInWarningAdvancedModelSizeExceeded_WNG_8501


  friend class CATCGMDiagnosis;

  static void _XXXX(const CATCGMDiagnosis * iDiag) {}; // Still yet unknown for 

  static void _4501(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolImpossibleSplit_ERR_4501
  static void _4503(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolIncompleteCut_ERR_4503
  static void _4504(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolIncompleteLayDown_ERR_4504
  static void _4506(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolImpossibleReport_ERR_4506
  static void _4507(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolMissedConfusion_ERR_4507
  static void _4508(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolFaceFaceFailed_ERR_4508
  static void _4510(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolTwistedVolume_ERR_4510
  static void _4511(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolInaccurateContact_ERR_4511
  static void _4512(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolImpossibleCut_ERR_4512
  static void _4513(const CATCGMDiagnosis * iDiag) {}; // TopObInSmartProjIncompleteSolution_ERR_4513
  static void _4515(const CATCGMDiagnosis * iDiag) {}; // TopObInSmartProjCheckDistance_ERR_4515
  static void _4516(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolImpossibleSplit_ERR_4516
  static void _4518(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolImpossibleMultiTrim_ERR_4518
  static void _4519(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolPositionComputation_ERR_4519
  static void _4526(const CATCGMDiagnosis * iDiag) {}; // TopObInTopoInaccurateContact_ERR_4526
  static void _4700(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolWarningStabilization_ERR_4700
  static void _4701(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolWarningBoundaryHealing_ERR_4701
  static void _4702(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolWarningRegularizator_ERR_4702
  static void _4703(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolWarningInaccurateContact_ERR_4703
  static void _4704(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolWarningNonManifoldEdges_ERR_4704
  static void _4705(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolWarningClosedWirePositionning_ERR_4705
  static void _4706(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolWarningGapInMissing_ERR_4706
  static void _4707(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolWarningKeepAndDelete_ERR_4707
  static void _4708(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolWarningToleranceValue_ERR_4708
  static void _4709(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolWarningIndexingOfSolutions_ERR_4709
  static void _4710(const CATCGMDiagnosis * iDiag) {}; // TopObInBoolConfusedWiresInSplitShellByWires_ERR_4710

  static void _5012(const CATCGMDiagnosis * iDiag) {}; // SweepWarning_UnknownSev_TopOpInMaxGapDetection_ERR_5012 + TopOpInMaxGapDetection_ERR_5012
  static void _5013(const CATCGMDiagnosis * iDiag) {}; // TopOpInTangencyMaxGapDetection_ERR_5013
  static void _5019(const CATCGMDiagnosis * iDiag) {}; // TopOpInDistanceMaxWarning_ERR_5019
  static void _5020(const CATCGMDiagnosis * iDiag) {}; // TopOpInDistanceMaxWarning_ERR_5020
  static void _5021(const CATCGMDiagnosis * iDiag) {}; // TopOpInDistanceMaxWarning_ERR_5021
  static void _5022(const CATCGMDiagnosis * iDiag) {}; // TopOpInProjection_ERR_5022
  static void _5024(const CATCGMDiagnosis * iDiag) {}; // TopOpInDistanceCalcWarningFailed_ERR_5024
  static void _5026(const CATCGMDiagnosis * iDiag) {}; // TopOpInDistanceCalcWarningOnlyProjectedSol_ERR_5026
  static void _5050(const CATCGMDiagnosis * iDiag) {}; // TopOpInNewtonConvergeKO_ERR_5020

  static void _6050(const CATCGMDiagnosis * iDiag) {}; // TopOpInExtrapolWireOnShellInvalidWire_ERR_6050
  static void _6051(const CATCGMDiagnosis * iDiag) {}; // TopOpInExtrapolWireOnShellSelfIntersection_ERR_6051
  static void _6102(const CATCGMDiagnosis * iDiag) {}; // TopOpInMultiRibbonDefinition_ERR_6102
  static void _6130(const CATCGMDiagnosis * iDiag) {}; // TopOpInVertexBlendTrackCreation_ERR_6130
  static void _6132(const CATCGMDiagnosis * iDiag) {}; // TopOpInVertexBlendSurfaceSewing_ERR_6132
  static void _6136(const CATCGMDiagnosis * iDiag) {}; // TopOpInRibbonCollision_ERR_6136
  static void _6152(const CATCGMDiagnosis * iDiag) {}; // TopOpInDraftTwistOnNeutral_ERR_6152
  static void _6153(const CATCGMDiagnosis * iDiag) {}; // TopOpInDraftInternalTwist_ERR_6153
  static void _6154(const CATCGMDiagnosis * iDiag) {}; // TopOpInDraftCollision_ERR_6154
  static void _6155(const CATCGMDiagnosis * iDiag) {}; // TopOpInDraftCurvatureInversion_ERR_6155
  static void _6156(const CATCGMDiagnosis * iDiag) {}; // TopOpInDraftRelimitation_ERR_6156
  static void _6157(const CATCGMDiagnosis * iDiag) {}; // TopOpInDraftCreationDraftFaces_ERR_6157
  static void _6158(const CATCGMDiagnosis * iDiag) {}; // TopOpInDraftCreationDraftFaces_ERR_6158
  static void _6159(const CATCGMDiagnosis * iDiag) {}; // TopOpInDraftInternalDiscontinuity_ERR_6159
  static void _6164(const CATCGMDiagnosis * iDiag) {}; // TopOpInMultiLimitingIntersection_ERR_6164
  static void _6165(const CATCGMDiagnosis * iDiag) {}; // TopOpInMultiLimitingIntersection_ERR_6165
  static void _6166(const CATCGMDiagnosis * iDiag) {}; // TopOpInRibbonInitializationWithTangentIntersection_ERR_6166
  static void _6167(const CATCGMDiagnosis * iDiag) {}; // TopOpInRibbonInitializationWithLocalAmbiguity_ERR_6167
  static void _6180(const CATCGMDiagnosis * iDiag) {}; // TopOpInDraftAutomaticUntwistFailure_ERR_6180
  static void _6320(const CATCGMDiagnosis * iDiag) {}; // TopOpInParallelDeviationDueToGap_WNG_6320
  static void _6326(const CATCGMDiagnosis * iDiag) {}; // TopOpIn3DCorner_ERR_6326
  static void _6327(const CATCGMDiagnosis * iDiag) {}; // TopOpInParallelReorderingPb_WNG_6327
  static void _6328(const CATCGMDiagnosis * iDiag) {}; // TopOpInParallelIncompleteSolution_WNG_6328
  static void _6566(const CATCGMDiagnosis * iDiag) {}; // TopOpInShellThickSurfaceSideFace_ERR_6566
  static void _6580(const CATCGMDiagnosis * iDiag) {}; // TopOpInShellPropagationConflict_ERR_6580
  static void _6582(const CATCGMDiagnosis * iDiag) {}; // TopOpInThickPlusRegularizedFaces_ERR_6582
  static void _6597(const CATCGMDiagnosis * iDiag) {}; // TopOpInThickPlusRegularizedFaces_ERR_6597
  static void _6599(const CATCGMDiagnosis * iDiag) {}; // TopOpInShellThickSurfaceConstantThickness_ERR_6599
  static void _6605(const CATCGMDiagnosis * iDiag) {}; // TopOpInHybOpInvalidPosition_ERR_6605
  static void _6606(const CATCGMDiagnosis * iDiag) {}; // TopOpInHybOpInvalidKeepRemoveInput_ERR_6606
  static void _6607(const CATCGMDiagnosis * iDiag) {}; // TopOpInHybOpInvalidKeepRemoveConflict_ERR_6607
  static void _6608(const CATCGMDiagnosis * iDiag) {}; // TopOpInHybOpInvalidKeepRemoveAmbiguous_ERR_6608
  static void _6609(const CATCGMDiagnosis * iDiag) {}; // TopOpInHybOpWarningAmbiguousCells_ERR_6609
  static void _6610(const CATCGMDiagnosis * iDiag) {}; // TopOpInHybOpWarningConfusionCells_ERR_6610
  static void _6611(const CATCGMDiagnosis * iDiag) {}; // TopOpInHybOpWarningTangentDesignCells_ERR_6611
  static void _6613(const CATCGMDiagnosis * iDiag) {}; // TopOpInJoinSharedCells_ERR_6613
  static void _6614(const CATCGMDiagnosis * iDiag) {}; // TopOpInJoinSharedFaces_ERR_6614
  static void _6615(const CATCGMDiagnosis * iDiag) {}; // TopOpInJoinSharedCells_ERR_6615
  static void _6616(const CATCGMDiagnosis * iDiag) {}; // TopOpInJoinRazorBladeEdges_ERR_6616
  static void _6617(const CATCGMDiagnosis * iDiag) {}; // TopOpIntHybOpErrorFace_ERR_6617
  static void _6619(const CATCGMDiagnosis * iDiag) {}; // TopOpIntJoinStopOnRBE_ERR_6619
  static void _6620(const CATCGMDiagnosis * iDiag) {}; // TopOpIntJoinWngOnRBE_ERR_6620
  static void _6621(const CATCGMDiagnosis * iDiag) {}; // TopOpIntJoinUnoriSkin_ERR_6621
  static void _6622(const CATCGMDiagnosis * iDiag) {}; // TopOpIntJoinUnoriSkin_ERR_6622
  static void _6623(const CATCGMDiagnosis * iDiag) {}; // TopOpIntJoinNonManifold_ERR_6623
  static void _6624(const CATCGMDiagnosis * iDiag) {}; // TopOpIntJoinNonManifold_ERR_6624
  static void _6950(const CATCGMDiagnosis * iDiag) {}; // TopOpInRegulOffsetDeviation_ERR_6950
  static void _6951(const CATCGMDiagnosis * iDiag) {}; // TopOpInRegulOffsetFacesAdj_ERR_6951
  static void _6952(const CATCGMDiagnosis * iDiag) {}; // TopOpInRegulOffsetFailure_ERR_6952
  static void _6953(const CATCGMDiagnosis * iDiag) {}; // TopOpInRegulOffsetOffsetability_ERR_6953
  static void _6954(const CATCGMDiagnosis * iDiag) {}; // TopOpInRegulOffsetSmoothedFacesOk_ERR_6954

  static void _7031(const CATCGMDiagnosis * iDiag) {}; // SweepWarning_DUCSev_TopOpInSweepSmallEdge_ERR_7031 + TopOpInSweepSmallEdge_ERR_7031
  static void _7033(const CATCGMDiagnosis * iDiag) {}; // TopOpInExtrapolLostOfDir_ERR_7033
  static void _7034(const CATCGMDiagnosis * iDiag) {}; // SweepWarning_DUCSev_TopOpInSweepInternalProfileInReport_ERR_7034
  static void _7035(const CATCGMDiagnosis * iDiag) {}; // SweepWarning_DUCSev_TopOpInSweepInvalidCenterCurveWarning_ERR_7035
  static void _7038(const CATCGMDiagnosis * iDiag) {}; // SweepWarning_UnknownSev_TopOpInSweepImpossibleCleanWarning_ERR_7038
  static void _7040(const CATCGMDiagnosis * iDiag) {}; // TopOpInNotLyingOn_ERR_7040
  static void _7046(const CATCGMDiagnosis * iDiag) {}; // SweepWarning_UnknownSev_TopOpInSweepSmallEdgeFromInitialGuide_ERR_7046
  static void _7047(const CATCGMDiagnosis * iDiag) {}; // SweepWarning_UnknownSev_TopOpInSweepSmallEdgeFromInitialProfile_ERR_7047
  static void _7048(const CATCGMDiagnosis * iDiag) {}; // SweepWarning_UnknownSev_TopOpInSweepSmallEdgeFromFinalGuide_ERR_7048
  static void _7049(const CATCGMDiagnosis * iDiag) {}; // SweepWarning_UnknownSev_TopOpInSweepSmallEdgeFromFinalProfile_ERR_7049
  static void _7050(const CATCGMDiagnosis * iDiag) {}; // SweepWarning_UnknownSev_TopOpInSweepProfileOrderWarning_ERR_7050
  static void _7058(const CATCGMDiagnosis * iDiag) {}; // SweepWarning_UnknownSev_TopOpInSweepCheckDeviationFromProfile_ERR_7058
  static void _7059(const CATCGMDiagnosis * iDiag) {}; // SweepWarning_UnknownSev_TopOpInSweepCheckDeviationFromGuide_ERR_7059
  static void _7060(const CATCGMDiagnosis * iDiag) {}; // TopOpInSweepEdgeLyingOnSharpEdge_ERR_7060
  static void _7070(const CATCGMDiagnosis * iDiag) {}; // SweepWarning_UnknownSev_TopOpInSweepRelimitedGuide_WNG_7070
  static void _7071(const CATCGMDiagnosis * iDiag) {}; // SweepWarning_UnknownSev_TopOpInSweepIgnoredSpec_WNG_7071
  static void _7081(const CATCGMDiagnosis * iDiag) {}; // TopOpInBlendShellContainsAJunctionEdge_7081
  static void _7083(const CATCGMDiagnosis * iDiag) {}; // TopOpInBlendNonCompatibleOption_ERR_7083
  static void _7086(const CATCGMDiagnosis * iDiag) {}; // TopOpInBlendCurvatureContinuityAskedOnInternalEdge_ERR_7086
  static void _7089(const CATCGMDiagnosis * iDiag) {}; // TopOpInBlendAvoidTwist_ERR_7089
  static void _7114(const CATCGMDiagnosis * iDiag) {}; // TopOpInPointDirection_WNG_7114
  static void _7555(const CATCGMDiagnosis * iDiag) {}; // TopOpIntHybOpInvalidAutoIntersectFace_ERR_7555
  static void _7558(const CATCGMDiagnosis * iDiag) {}; // TopOpIntHybOpInvalidAngleBetweenFaces_ERR_7558
  static void _7559(const CATCGMDiagnosis * iDiag) {}; // TopOpIntHybOpInvalidAngleBetweenEdges_ERR_7559
  static void _7564(const CATCGMDiagnosis * iDiag) {}; // SweepWarning_UnknownSev_TopOpInHybOpTooLowCGMLevelForOption_ERR_7564 + TopOpInHybOpTooLowCGMLevelForOption_ERR_7564
  static void _7604(const CATCGMDiagnosis * iDiag) {}; // TopOpInWrapSurfaceTrimmedReferenceSurface_ERR_7604
  static void _7605(const CATCGMDiagnosis * iDiag) {}; // TopOpInWrapSurfaceTrimmedTargetSurface_ERR_7605
  static void _7634(const CATCGMDiagnosis * iDiag) {}; // TopOpInVarOffHighVariation_ERR_7634
  static void _7669(const CATCGMDiagnosis * iDiag) {}; // TopOpInSurfaceUnfoldRuledNonCstTgtPlaneOnRule_ERR_7669
  static void _7670(const CATCGMDiagnosis * iDiag) {}; // TopOpInSurfaceUnfoldPartialTransfer_WNG_7670
  static void _7676(const CATCGMDiagnosis * iDiag) {}; // TopOpInFrFSUDeviationDueToClean_WNG_7676

  static void _8301(const CATCGMDiagnosis * iDiag) {}; // TopOpInSilhouetteOperator_ERR_8301
  static void _8302(const CATCGMDiagnosis * iDiag) {}; // TopOpInSilhouetteOperator_ERR_8302
  static void _8303(const CATCGMDiagnosis * iDiag) {}; // TopOpInSilhouetteOperatorWarning_ERR_8303
  static void _8304(const CATCGMDiagnosis * iDiag) {}; // TopOpInSilhouetteOperator_ERR_8304
  static void _8351(const CATCGMDiagnosis * iDiag) {}; // TopOpInWireDevelopOperator_ERR_8351
  static void _8371(const CATCGMDiagnosis * iDiag) {}; // TopOpInMidSurfaceOperator_ERR_8371
  static void _8401(const CATCGMDiagnosis * iDiag) {}; // TopOpInWarningNoPatternOnSurfacicLiveOpe_ERR_8401
  static void _8501(const CATCGMDiagnosis * iDiag) {}; // TopOpInWarningAdvancedModelSizeExceeded_WNG_8501
};

#endif
