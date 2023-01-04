#ifndef CATCGMVersionningDefVarDLR6_h
#define CATCGMVersionningDefVarDLR6_h

//-------------------------------------------------------------------------------------
// Pour definir une nouvelle variable de versionning, decommenter les lignes suivantes
//-------------------------------------------------------------------------------------
// Ligne 1 : Verifie que la variable n'est pas declaree en officiel
// Ligne 2 : Definition de la variable et affectation (32000 non activee)


//OID 
#ifndef CGM_Versionning_ProjectionWithExtrapol_CheckError
#define CGM_Versionning_ProjectionWithExtrapol_CheckError 7100
#endif
// OID End




///////////////////////////////////////////////////////////////////////////////
//
//    OFFICIAL --- ACTIVATED
//
/////
//

// Active : 26-07-2019
// Value = 8780
#ifndef CGM_Versionning_IS_ScarFix
#define CGM_Versionning_IS_ScarFix Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(IS_ScarFix);

// Active : 25-10-2019
// Value = 8897
#ifndef CGM_Versionning_Fix_IS_Propagation
#define CGM_Versionning_Fix_IS_Propagation Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Fix_IS_Propagation);

// Active : 25-10-2019
// Value = 8898
#ifndef CGM_Versionning_Fix_EdgeTwinning_In_ISCreation
#define CGM_Versionning_Fix_EdgeTwinning_In_ISCreation Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Fix_EdgeTwinning_In_ISCreation);

// Active : 29-11-2019
// Value = 8937
#ifndef CGM_Versionning_IntersectTopology_Rectify_ShellTouched
#define CGM_Versionning_IntersectTopology_Rectify_ShellTouched Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(IntersectTopology_Rectify_ShellTouched);

// Active : 29-11-2019
// Value = 8938
#ifndef CGM_Versionning_Compatible_VolDisco_via_DiscoEngine
#define CGM_Versionning_Compatible_VolDisco_via_DiscoEngine Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Compatible_VolDisco_via_DiscoEngine);

// Active : 18-12-2020
// Value = 9694
#ifndef CGM_Versionning_TopManifolder_FixBuildOfJournals
#define CGM_Versionning_TopManifolder_FixBuildOfJournals Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(TopManifolder_FixBuildOfJournals);

// Active : 30-04-2021
// Value = 9822
#ifndef CGM_Versionning_TopManifolder_NewAlgo
#define CGM_Versionning_TopManifolder_NewAlgo Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(TopManifolder_NewAlgo);

// Active : 28-05-2021
// Value = 9875
#ifndef CGM_Versionning_Compatible_TouchVols_WithBBoxInter
#define CGM_Versionning_Compatible_TouchVols_WithBBoxInter Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Compatible_TouchVols_WithBBoxInter);

// Active : 28-05-2021
// Value = 9869
#ifndef CGM_Versionning_FullShells_Support_MultipleFaces
#define CGM_Versionning_FullShells_Support_MultipleFaces Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(FullShells_Support_MultipleFaces);

// Active : 28-05-2021
// Value = 9870
#ifndef CGM_Versionning_FullWires_Support_MultipleEdges
#define CGM_Versionning_FullWires_Support_MultipleEdges Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(FullWires_Support_MultipleEdges);


// Full Shells in volume - Model
// Active by #ifdef CATIACGMR424Code
#ifndef CGM_Versionning_Authorize_FullShells_InModel
#define CGM_Versionning_Authorize_FullShells_InModel Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Authorize_FullShells_InModel);

// Full Wires in volume - Model
// Active by #ifdef CATIACGMR424Code
#ifndef CGM_Versionning_Authorize_FullWires_InModel
#define CGM_Versionning_Authorize_FullWires_InModel Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Authorize_FullWires_InModel);


// Active : 02-07-2021
// Value = 9982
#ifndef CGM_Versionning_WallLimits_On_MixedEdge
#define CGM_Versionning_WallLimits_On_MixedEdge Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(WallLimits_On_MixedEdge);

// Active : 13-08-2021
// Value = 10021
#ifndef CGM_Versionning_PropagateFullSkins
#define CGM_Versionning_PropagateFullSkins Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(PropagateFullSkins);

// IR_826695
// Active : 13-08-2021
// Value = 10022
#ifndef CGM_Versionning_SewSkin_DontTouchShellByBBox
#define CGM_Versionning_SewSkin_DontTouchShellByBBox Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(SewSkin_DontTouchShellByBBox);

// IR_729082
#ifndef CGM_Versionning_Fix_UseOf_CATExtrudeLimitType
#define CGM_Versionning_Fix_UseOf_CATExtrudeLimitType Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Fix_UseOf_CATExtrudeLimitType);

// IR_892004
#ifndef CGM_Versionning_VertexRelimitation_Accept_InterFromWires
#define CGM_Versionning_VertexRelimitation_Accept_InterFromWires Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(VertexRelimitation_Accept_InterFromWires);

// IR_890531
#ifndef CGM_Versionning_Compute_NbBlancksShells_From_CurrentProfile
#define CGM_Versionning_Compute_NbBlancksShells_From_CurrentProfile Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Compute_NbBlancksShells_From_CurrentProfile);

#ifndef CGM_Versionning_Compatible_Create_FullShells
#define CGM_Versionning_Compatible_Create_FullShells Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Compatible_Create_FullShells);

#ifndef CGM_Versionning_Compatible_Create_FullWires
#define CGM_Versionning_Compatible_Create_FullWires Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Compatible_Create_FullWires);

#ifndef CGM_Versionning_RelimitByVolume_Support_Volumes
#define CGM_Versionning_RelimitByVolume_Support_Volumes Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(RelimitByVolume_Support_Volumes);

#ifndef CGM_Versionning_RelimitByVolume_Facto_ShellsVolumes
#define CGM_Versionning_RelimitByVolume_Facto_ShellsVolumes Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(RelimitByVolume_Facto_ShellsVolumes);

//
/////
//
//    OFFICIAL --- ACTIVATED
//
///////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////
//
//    OFFICIAL --- WORK IN PROGRESS
//
/////
//

// RI_723002 and now under THM + QF2
#ifndef CGM_Versionning_IR723002_BodyMerger_CallMultiCompatible
#define CGM_Versionning_IR723002_BodyMerger_CallMultiCompatible Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(IR723002_BodyMerger_CallMultiCompatible);

#ifndef CGM_Versionning_Disco3D_NewTreatment_Flatten
#define CGM_Versionning_Disco3D_NewTreatment_Flatten Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Disco3D_NewTreatment_Flatten);

#ifndef CGM_Versionning_DynBoolDiff_AuthorizeSharedFaceData
#define CGM_Versionning_DynBoolDiff_AuthorizeSharedFaceData Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(DynBoolDiff_AuthorizeSharedFaceData);


#ifndef CGM_Versionning_Disco3D_SpecialTreat_FullyFlattenVols
#define CGM_Versionning_Disco3D_SpecialTreat_FullyFlattenVols Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Disco3D_SpecialTreat_FullyFlattenVols);

//
/////
//
//    OFFICIAL --- WORK IN PROGRESS
//
///////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////
//
//    NON OFFICIAL --- WORK IN PROGRESS
//
/////
//

// IR-931830
#ifndef CGM_Versionning_Pattern_DetectImpossibleOptimization
#define CGM_Versionning_Pattern_DetectImpossibleOptimization Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Pattern_DetectImpossibleOptimization);

// Pattern improvement - necessary for fix of IR-931830
#ifndef CGM_Versionning_Pattern_DetectBooleanEdgesToKeep
#define CGM_Versionning_Pattern_DetectBooleanEdgesToKeep Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Pattern_DetectBooleanEdgesToKeep);

// Case of VB7 - Missing volumes
#ifndef CGM_Versionning_DiscoEngine_TwoStepMatterInside
#define CGM_Versionning_DiscoEngine_TwoStepMatterInside Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(DiscoEngine_TwoStepMatterInside);

#ifndef CGM_Versionning_Disco3D_DetectVolumicWrongPosInConnectorCreation
#define CGM_Versionning_Disco3D_DetectVolumicWrongPosInConnectorCreation Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Disco3D_DetectVolumicWrongPosInConnectorCreation);

#ifndef CGM_Versionning_Disco3DCallbacks_DontMakeComposite
#define CGM_Versionning_Disco3DCallbacks_DontMakeComposite Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Disco3DCallbacks_DontMakeComposite);

#ifndef CGM_Versionning_DOCO_CompatibleAllDisconnecting_AtOnce
#define CGM_Versionning_DOCO_CompatibleAllDisconnecting_AtOnce Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(DOCO_CompatibleAllDisconnecting_AtOnce);

#ifndef CGM_Versionning_DynSolidBoolean_AlwaysUseDisco3D
#define CGM_Versionning_DynSolidBoolean_AlwaysUseDisco3D Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(DynSolidBoolean_AlwaysUseDisco3D);

#ifndef CGM_Versionning_DynSolidBoolean_Disco3D_IntegrateAllSkins
#define CGM_Versionning_DynSolidBoolean_Disco3D_IntegrateAllSkins Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(DynSolidBoolean_Disco3D_IntegrateAllSkins);


#ifndef CGM_Versionning_Authorize_FullVerticesInVol_InModel
#define CGM_Versionning_Authorize_FullVerticesInVol_InModel Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Authorize_FullVerticesInVol_InModel);

// Full Wires
#ifndef CGM_Versionning_SplitWireWithFaceCollision
#define CGM_Versionning_SplitWireWithFaceCollision Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(SplitWireWithFaceCollision);

// RI_723002
#ifndef CGM_Versionning_IR723002_DontCloseScar_UsingEdgeOfSameBody
#define CGM_Versionning_IR723002_DontCloseScar_UsingEdgeOfSameBody Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(IR723002_DontCloseScar_UsingEdgeOfSameBody);

// Imprint
#ifndef CGM_Versionning_Imprint_DecorateBorderFaces
#define CGM_Versionning_Imprint_DecorateBorderFaces Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Imprint_DecorateBorderFaces);

//
/////
//
//    NON OFFICIAL --- WORK IN PROGRESS
//
///////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////
//
//    NON OFFICIAL --- FUTURE PROJECTS
//
/////
//

#ifndef CGM_Versionning_VolSweep_through_VolSpread
#define CGM_Versionning_VolSweep_through_VolSpread Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(VolSweep_through_VolSpread);

#ifndef CGM_Versionning_VolSweep_RelimitAndRetry_VolSpread
#define CGM_Versionning_VolSweep_RelimitAndRetry_VolSpread Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(VolSweep_RelimitAndRetry_VolSpread);


#ifndef CGM_Versionning_RelimitByVolume_FixVerifOnSubdBool_HasIntersection
#define CGM_Versionning_RelimitByVolume_FixVerifOnSubdBool_HasIntersection Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(RelimitByVolume_FixVerifOnSubdBool_HasIntersection);


#ifndef CGM_Versionning_Fix_IVReport_in_IEDestruction
#define CGM_Versionning_Fix_IVReport_in_IEDestruction Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Fix_IVReport_in_IEDestruction);


// CATTopMaxIsoMoveCalculator
#ifndef CGM_Versionning_MaxIsoMove_UseTrigo
#define CGM_Versionning_MaxIsoMove_UseTrigo Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(MaxIsoMove_UseTrigo);

//
/////
//
//    NON OFFICIAL --- FUTURE PROJECTS
//
///////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////
//
//    NON OFFICIAL --- GARBAGE
//
/////
//

#ifndef CGM_Versionning_SewSkin_via_Disco3D
#define CGM_Versionning_SewSkin_via_Disco3D Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(SewSkin_via_Disco3D);

//
/////
//
//    NON OFFICIAL --- GARBAGE
//
///////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////
//
//    NON OFFICIAL --- PERSONNAL USE
//    (Modding of Disco3DEngine)
//
/////
//

#ifndef CGM_Versionning_Disco3D_ForceEngineSimpleRun
#define CGM_Versionning_Disco3D_ForceEngineSimpleRun Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Disco3D_ForceEngineSimpleRun);

#ifndef CGM_Versionning_Disco3D_DoNotPreliminaryAddVolumicDiscoCells
#define CGM_Versionning_Disco3D_DoNotPreliminaryAddVolumicDiscoCells Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Disco3D_DoNotPreliminaryAddVolumicDiscoCells);

#ifndef CGM_Versionning_Disco3D_PreferCtndCB
#define CGM_Versionning_Disco3D_PreferCtndCB Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Disco3D_PreferCtndCB);

#ifndef CGM_Versionning_Disco3D_RecomputeVolAppartenanceThroughSkinParsing
#define CGM_Versionning_Disco3D_RecomputeVolAppartenanceThroughSkinParsing Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Disco3D_RecomputeVolAppartenanceThroughSkinParsing);

#ifndef CGM_Versionning_Disco3D_DoNotSortFinalShellsCompoBySkinNum
#define CGM_Versionning_Disco3D_DoNotSortFinalShellsCompoBySkinNum Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Disco3D_DoNotSortFinalShellsCompoBySkinNum);

#ifndef CGM_Versionning_Disco3D_DoNotSortTheVolumes
#define CGM_Versionning_Disco3D_DoNotSortTheVolumes Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Disco3D_DoNotSortTheVolumes);

#ifndef CGM_Versionning_SplitClosedConnectors
#define CGM_Versionning_SplitClosedConnectors Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(SplitClosedConnectors);

#ifndef CGM_Versionning_DontFixMissingFlattenSkins
#define CGM_Versionning_DontFixMissingFlattenSkins Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(DontFixMissingFlattenSkins);

#ifndef CGM_Versionning_SewskinFixMissingFlattenSkins
#define CGM_Versionning_SewskinFixMissingFlattenSkins Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(SewskinFixMissingFlattenSkins);


#ifndef CGM_Versionning_ExpandVol_DoCompatibleIntersection
#define CGM_Versionning_ExpandVol_DoCompatibleIntersection Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(ExpandVol_DoCompatibleIntersection);

#ifndef CGM_Versionning_ExpandVol_CleanInterData_FromSurfacicSkins
#define CGM_Versionning_ExpandVol_CleanInterData_FromSurfacicSkins Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(ExpandVol_CleanInterData_FromSurfacicSkins);

//
/////
//
//    NON OFFICIAL --- PERSONNAL USE
//    (Modding of Disco3DEngine)
//
///////////////////////////////////////////////////////////////////////////////


#endif
