#ifndef CATCGMModif_h
#define CATCGMModif_h

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "ExportedByCATMathStream.h"
#include "CATBaseUnknown.h"
#include "CATCGMVersionLevel.h"

class CATSoftwareConfiguration;
class CATSoftwareModification;

// Updates of a configuration by a CGM modification.
ExportedByCATMathStream void CATCGMUpdateConfiguration(CATSoftwareConfiguration* iConfig, const char* iModifId);

// Retrieves the level of the code to run.
ExportedByCATMathStream short GetCGMLevel(CATSoftwareConfiguration* iConfig, const char* iModifId);

// Check the level of the CGM modification in the config.
ExportedByCATMathStream short CheckCGMLevel(CATSoftwareConfiguration* iConfig);

// Validate the hotfix level
ExportedByCATMathStream CATBoolean ValidateHFCGMLevel (short iHFLevel, short iHFLevelMax, CATSoftwareConfiguration* iConfig, const char* iModifId);

//----------------------------------------------------------------------------
// For Tests Purpose ONLY !!!
//----------------------------------------------------------------------------

// Creates a closed CGM configuration for a given level.
ExportedByCATMathStream CATSoftwareConfiguration* GetCGMSoftwareConfiguration(short iLevel);

// Force a Level for the CGM Modification in a given SoftwareConfiguration.
ExportedByCATMathStream void ForceCGMLevelInSoftwareConfiguration(CATSoftwareConfiguration* iConfig, short iLevel);

// Get the BSF level of the CGM modification.
ExportedByCATMathStream short GetBSFCGMLevel();

// Force the BSF level of the CGM modification to a given level.
ExportedByCATMathStream short ForceBSFCGMLevel(short iLevel);

// Force the the configuration to react as Open.
ExportedByCATMathStream short ForceOpenConfiguration();

// Permet de savoir si on est en mode ODT.
ExportedByCATMathStream short IsRunningInOdt();

// Permet de savoir si on est en mode Traces.
ExportedByCATMathStream short CATCGMVersionningTraces();

// Permet de desactiver les checks.
ExportedByCATMathStream short CATCGMVersionningCheck();

// Permet de verifier le Versionning type Drop
ExportedByCATMathStream short CATCGMVersionningDrop();

//----------------------------------------------------------------------------
//  Dedicated To Build-Time 
//     for compilation with comparison with short Level
//  Documentation is available in 
//    Mathematics\PrivateInterfaces\CATCGMVersionDefine.h 
//    (only for read, do not attempt include on CATCGMVersionDefine)
//----------------------------------------------------------------------------


CATCGMVersionLevel(TopologicalOperators_TestOnly)
#define CGM_Versionning_TopologicalOperators_TestOnly CATCGMVersionLevel_TopologicalOperators_TestOnly

CATCGMVersionLevel(Project_Journal_Vertex) 
#define CGM_Versionning_Project_Journal_Vertex CATCGMVersionLevel_Project_Journal_Vertex

CATCGMVersionLevel(Project_Journal_LyingOn) 
#define CGM_Versionning_Project_Journal_LyingOn CATCGMVersionLevel_Project_Journal_LyingOn 
 
CATCGMVersionLevel(Project_ClosingVertex) 
#define CGM_Versionning_Project_ClosingVertex CATCGMVersionLevel_Project_ClosingVertex

CATCGMVersionLevel(Intersect_Journal_Vertex) 
#define CGM_Versionning_Intersect_Journal_Vertex CATCGMVersionLevel_Intersect_Journal_Vertex

CATCGMVersionLevel(SplitTrim_Journal_Confusion) 
#define CGM_Versionning_SplitTrim_Journal_Confusion CATCGMVersionLevel_SplitTrim_Journal_Confusion 

CATCGMVersionLevel(SplitTrim_BuildBody) 
#define CGM_Versionning_SplitTrim_BuildBody CATCGMVersionLevel_SplitTrim_BuildBody 

CATCGMVersionLevel(Join_BuildBody) 
#define CGM_Versionning_Join_BuildBody CATCGMVersionLevel_Join_BuildBody

CATCGMVersionLevel(CATCreateTopCreateDomains) 
#define CGM_Versionning_CATCreateTopCreateDomains  CATCGMVersionLevel_CATCreateTopCreateDomains

CATCGMVersionLevel(ExtrapolWire_Orientation)
#define CGM_Versionning_ExtrapolWire_Orientation  CATCGMVersionLevel_ExtrapolWire_Orientation

CATCGMVersionLevel(Sweep_Simplify)
#define CGM_Versionning_Sweep_Simplify CATCGMVersionLevel_Sweep_Simplify

CATCGMVersionLevel(Revol_Angle)
#define CGM_Versionning_Revol_Angle CATCGMVersionLevel_Revol_Angle

CATCGMVersionLevel(Blend_Journal)
#define CGM_Versionning_Blend_Journal CATCGMVersionLevel_Blend_Journal

CATCGMVersionLevel(LoftBlendPreciseDegeneratedEdgesReport)
#define CGM_Versionning_LoftBlendPreciseDegeneratedEdgesReport CATCGMVersionLevel_LoftBlendPreciseDegeneratedEdgesReport

CATCGMVersionLevel(ComputeAdaptativeSweepOrientation)
#define CGM_Versionning_ComputeAdaptativeSweepOrientation CATCGMVersionLevel_ComputeAdaptativeSweepOrientation

CATCGMVersionLevel(Parallel_MappingLaw)
#define CGM_Versionning_Parallel_MappingLaw  CATCGMVersionLevel_Parallel_MappingLaw

CATCGMVersionLevel(Spine_Implicit_PlaneCase)
#define CGM_Versionning_Spine_Implicit_PlaneCase CATCGMVersionLevel_Spine_Implicit_PlaneCase

CATCGMVersionLevel(CircleFillet_Twist)
#define CGM_Versionning_CircleFillet_Twist CATCGMVersionLevel_CircleFillet_Twist

CATCGMVersionLevel(offset_bisector)
#define CGM_Versionning_offset_bisector CATCGMVersionLevel_offset_bisector

CATCGMVersionLevel(Trim_Journal_Bord_a_Bord)
#define CGM_Versionning_Trim_Journal_Bord_a_Bord CATCGMVersionLevel_Trim_Journal_Bord_a_Bord

CATCGMVersionLevel(FilletFaceFace_InversionSupport)
#define CGM_Versionning_FilletFaceFace_InversionSupport CATCGMVersionLevel_FilletFaceFace_InversionSupport

CATCGMVersionLevel(IntersectShell_Orientation)
#define CGM_Versionning_IntersectShell_Orientation CATCGMVersionLevel_IntersectShell_Orientation

CATCGMVersionLevel(Split_ClosedWireBySingleVertex)
#define CGM_Versionning_Split_ClosedWireBySingleVertex CATCGMVersionLevel_Split_ClosedWireBySingleVertex

CATCGMVersionLevel(Join_BuildBody_Wire)
#define CGM_Versionning_Join_BuildBody_Wire  CATCGMVersionLevel_Join_BuildBody_Wire

CATCGMVersionLevel(Fillet_Extrapol_Around_Twist)
#define CGM_Versionning_Fillet_Extrapol_Around_Twist CATCGMVersionLevel_Fillet_Extrapol_Around_Twist

CATCGMVersionLevel(Corner_Relimitation)
#define CGM_Versionning_Corner_Relimitation CATCGMVersionLevel_Corner_Relimitation

CATCGMVersionLevel(Corner_Journal)
#define CGM_Versionning_Corner_Journal CATCGMVersionLevel_Corner_Journal

CATCGMVersionLevel(Sweep_AdvancedTwistDetection)
#define CGM_Versionning_Sweep_AdvancedTwistDetection CATCGMVersionLevel_Sweep_AdvancedTwistDetection

CATCGMVersionLevel(ImplicitSpineOperator_WithGuides)
#define CGM_Versionning_ImplicitSpineOperator_WithGuides CATCGMVersionLevel_ImplicitSpineOperator_WithGuides

CATCGMVersionLevel(Ribbon_Edge_High_Incidence_Crossing)
#define CGM_Versionning_Ribbon_Edge_High_Incidence_Crossing CATCGMVersionLevel_Ribbon_Edge_High_Incidence_Crossing

CATCGMVersionLevel(Fillet_InitialChoiceOfShiftedTracks)
#define CGM_Versionning_Fillet_InitialChoiceOfShiftedTracks CATCGMVersionLevel_Fillet_InitialChoiceOfShiftedTracks

CATCGMVersionLevel(Parallel_Boolean)
#define CGM_Versionning_Parallel_Boolean  CATCGMVersionLevel_Parallel_Boolean

CATCGMVersionLevel(CleanCurve_FillEdges)
#define CGM_Versionning_CleanCurve_FillEdges  CATCGMVersionLevel_CleanCurve_FillEdges

CATCGMVersionLevel(Fill_NewApprox)
#define CGM_Versionning_Fill_NewApprox CATCGMVersionLevel_Fill_NewApprox

CATCGMVersionLevel(RibRelim4Aretes)
#define CGM_Versionning_RibRelim4Aretes  CATCGMVersionLevel_RibRelim4Aretes

CATCGMVersionLevel(Draft_SupportChoiceForDraftSurface)
#define CGM_Versionning_Draft_SupportChoiceForDraftSurface  CATCGMVersionLevel_Draft_SupportChoiceForDraftSurface

CATCGMVersionLevel(Draft_DRLCoveredFaces)
#define CGM_Versionning_Draft_DRLCoveredFaces  CATCGMVersionLevel_Draft_DRLCoveredFaces

CATCGMVersionLevel(Draft_ThrowForDRLKODiagnostics)
#define CGM_Versionning_Draft_ThrowForDRLKODiagnostics  CATCGMVersionLevel_Draft_ThrowForDRLKODiagnostics

CATCGMVersionLevel(RibNuplet_FlatVertex)
#define CGM_Versionning_RibNuplet_FlatVertex  CATCGMVersionLevel_RibNuplet_FlatVertex

CATCGMVersionLevel(Check_Offset_Smooth_Edge)
#define CGM_Versionning_Check_Offset_Smooth_Edge  CATCGMVersionLevel_Check_Offset_Smooth_Edge

CATCGMVersionLevel(BlendRibbon_Hermetisation)
#define CGM_Versionning_BlendRibbon_Hermetisation  CATCGMVersionLevel_BlendRibbon_Hermetisation

CATCGMVersionLevel(Ribbon_BlendPropagationSpecMatching)
#define CGM_Versionning_Ribbon_BlendPropagationSpecMatching  CATCGMVersionLevel_Ribbon_BlendPropagationSpecMatching


// Historique des modifications avant FullVersionning
//=========================================================================================================
//  CGM_Bsf_Level = 1
//=========================================================================================================
// Identificateur Modification : AssembleShellOrientation 
// Operateur                   : Assemble de Shell (CATHybAssembleShell)
// Responsable                 : PBE
// Date                        : 27-03-00
// commentaire                 : stabilisation de l'orientation du resultat                   
//=========================================================================================================
// Identificateur Modification : CornerOri
// Operateur                   : Corner Pt-Crv sur Plan
// Responsable                 : JHN
// Date                        : 27-03-00
// commentaire                 : stabilisation de l'orientation des inputs             
//=========================================================================================================
// Identificateur Modification : CornerOri
// Operateur                   : Corner Crv-Crv sur Face
// Responsable                 : JHN
// Date                        : 27-03-00
// commentaire                 : stabilisation de l'orientation des inputs             
//=========================================================================================================
// Identificateur Modification : CornerOri
// Operateur                   : Corner et Connect en mode Trim
// Responsable                 : JHN
// Date                        : 27-03-00
// commentaire                 : stabilisation de l'orientation du resultat             
//=========================================================================================================
//  CGM_Bsf_Level = 2
//=========================================================================================================
// Identificateur Modification : SkinExtrapolSuiviVertexEtUntil 
// Operateur                   : Extrapolation Shell (CATSkinExtrapolationOperator)
// Responsable                 : BHE
// Date                        : 21-04-00
// commentaire                 : modification du suivi des vertices, relimitation de l'Until                   
//=========================================================================================================
//  CGM_Bsf_Level = 3
//=========================================================================================================
// Identificateur Modification : parallele de wireferme presque G1 
// Operateur                   : Parallele
// Responsable                 : JHN
// Date                        : 21-06-00
// commentaire                 : modification macroscopique du traitement du parallele de wire ferme non G1 uniquement sur la fermeture                   
//=========================================================================================================
// Identificateur Modification : planaroffset 
// Operateur                   : plan
// Responsable                 : JHN
// Date                        : 21-06-00
// commentaire                 : orientation du shell resultant identique a celle du shell initial
//=========================================================================================================
//  CGM_Bsf_Level = 4
//=========================================================================================================
// Identificateur Modification : SweepReportLevelV5R4SP2 
// Operateur                   : sweep
// Responsable                 : NLD
// Date                        : 10-07-00
// commentaire                 : remise a plat du traitement du journal de sweep/loft
CATCGMVersionLevel(Sweep_ReportModifZero)
#define CGM_Versionning_Sweep_ReportModifZero  CATCGMVersionLevel_Sweep_ReportModifZero
//=========================================================================================================
//  CGM_Bsf_Level = 5
//=========================================================================================================
// Identificateur Modification : DebugLyingOnSweepV5R5 
// Operateur                   : sweep
// Responsable                 : NLD
// Date                        : 19-09-00
// commentaire                 : correction pb reconnaissance lying on sur certains cas de
//                               sweep conic et circle; effet de bord sur journal topologique
CATCGMVersionLevel(Sweep_DebugLyingOnV5R5)
#define CGM_Versionning_Sweep_DebugLyingOnV5R5  CATCGMVersionLevel_Sweep_DebugLyingOnV5R5
//=========================================================================================================
//  CGM_Bsf_Level = 6
//=========================================================================================================
// Identificateur Modification : PlaneThroughCurves 
// Operateur                   : Plane
// Responsable                 : JHN
// Date                        : 24-11-00
// commentaire                 : correction pb orientation plane through curves
//=========================================================================================================
//  CGM_Bsf_Level = 7
//=========================================================================================================
// Identificateur Modification : PlanesDetectionInPartDesignSweep 
// Operateur                   : sweep (CATTopSweepImp)
// Responsable                 : NLD
// Date                        : 08-03-01
// commentaire                 : detection des plans dans sweep partdesign CATTopSweepImp
// Identificateur Modification : sweepsuivisimplif 
// Operateur                   : sweep (CATFrFTopologicalSweepCx2)
// Responsable                 : NLD
// Date                        : 08-03-01
// commentaire                 : gestion des simplifications dans suivi sweep 
CATCGMVersionLevel(Sweep_ReportModifSimplif)
#define CGM_Versionning_Sweep_ReportModifSimplif  CATCGMVersionLevel_Sweep_ReportModifSimplif
// Identificateur Modification : CanonicSurfacesWithSpine 
// Operateur                   : sweep (CATFrFTopologicalSweepCx2)
// Responsable                 : NLD
// Date                        : 08-03-01
// commentaire                 : canonicite des sweep unspec a spine droite
CATCGMVersionLevel(Sweep_CanonicSurfacesWithSpine)
#define CGM_Versionning_Sweep_CanonicSurfacesWithSpine  CATCGMVersionLevel_Sweep_CanonicSurfacesWithSpine
// Identificateur Modification : CorrectLoftOrientationManagement 
// Operateur                   : loft (CATFrFTopologicalSweepCx2)
// Responsable                 : NLD
// Date                        : 08-03-01
// commentaire                 : orientation des lofts (correction dans inversion profil)
CATCGMVersionLevel(Loft_CorrectOrientationManagement)
#define CGM_Versionning_Loft_CorrectOrientationManagement  CATCGMVersionLevel_Loft_CorrectOrientationManagement
//=========================================================================================================
//  CGM_Bsf_Level = 8
//=========================================================================================================
// Identificateur Modification : CAThkPilot::Initialize
// Operateur                   : Thickness/Shell/SkinOffset/ThickSurface/SkinExtrapolation
// Responsable                 : DPS
// Date                        : 03-04-01
// commentaire                 : simplification du BRep + modification du journal skin
//=========================================================================================================
//  CGM_Bsf_Level = 9
//=========================================================================================================
// Identificateur Modification : LoftImplicitSpineVersion1_ControlePointes 
// Operateur                   : sweep (CATFrFTopologicalSweepCx2, CATTopSpineCx5)
// Responsable                 : NLD
// Date                        : 05-04-01
// commentaire                 : controle des pointes dans ImplicitSpine
CATCGMVersionLevel(Loft_SpineVersion1Pointe)
#define CGM_Versionning_Loft_SpineVersion1Pointe  CATCGMVersionLevel_Loft_SpineVersion1Pointe
// Identificateur Modification : SweepVariationnelSuiviFunctionalGuide 
// Operateur                   : sweep (CATFrFTopologicalSweepCx2)
// Responsable                 : NLD
// Date                        : 05-04-01
// commentaire                 : protection suivi sweep variationnel sans guide
CATCGMVersionLevel(Sweep_SuiviFunctionalGuides)
#define CGM_Versionning_Sweep_SuiviFunctionalGuides  CATCGMVersionLevel_Sweep_SuiviFunctionalGuides
//=========================================================================================================
//  CGM_Bsf_Level = 10
//=========================================================================================================
// Identificateur Modification : ParallelExtremity
// Operateur                   : Parallel
// Responsable                 : JHN
// Date                        : 13-04-01
// commentaire                 : nouveau soft CATParallel de JHN 
//=========================================================================================================
//  CGM_Bsf_Level = 11
//=========================================================================================================
// Identificateur Modification : SweepAutomaticSpine 
// Operateur                   : sweep (CATFrFTopologicalSweepCx2)
// Responsable                 : NLD
// Date                        : 18-04-01
// commentaire                 : spine automatique deformee a partir de la guide
CATCGMVersionLevel(Sweep_AutomaticSpine)
#define CGM_Versionning_Sweep_AutomaticSpine  CATCGMVersionLevel_Sweep_AutomaticSpine
// Identificateur Modification : SweepVariationnelSuiviFunctionalGuideBis 
// Operateur                   : sweep (CATFrFTopologicalSweepCx2)
// Responsable                 : NLD
// Date                        : 18-04-01
// commentaire                 : protection suivi sweep variationnel sans guide
CATCGMVersionLevel(Sweep_SuiviFunctionalGuidesBis)
#define CGM_Versionning_Sweep_SuiviFunctionalGuidesBis  CATCGMVersionLevel_Sweep_SuiviFunctionalGuidesBis
// Identificateur Modification : SweepImplicitProfileBodyInfoSign 
// Operateur                   : sweep (CATFrFTopologicalSweepCx2)
// Responsable                 : NLD
// Date                        : 18-04-01
// commentaire                 : suivi extremites profils implicites
//                               avec infos -1 et -2 au lieu de 1 et 2
//                               pour bypass conflit avec suivi 
//                               incorrect du CATLayDownOperator (en attente
//                               depuis 1 an)
CATCGMVersionLevel(Sweep_ImplicitProfileBodyInfoSign)
#define CGM_Versionning_Sweep_ImplicitProfileBodyInfoSign  CATCGMVersionLevel_Sweep_ImplicitProfileBodyInfoSign
// Identificateur Modification : LoftProfilesHomogenizationWithG0ImposedPointsCoupling 
// Operateur                   : sweep (CATFrFTopologicalSweepCx2)
// Responsable                 : NLD
// Date                        : 23-04-01
// commentaire                 : coupling G0 dans homogeneisation des profils 
//                               du loft
CATCGMVersionLevel(Loft_ProfilesHomogenizationWithG0ImposedPointsCoupling)
#define CGM_Versionning_Loft_ProfilesHomogenizationWithG0ImposedPointsCoupling  CATCGMVersionLevel_Loft_ProfilesHomogenizationWithG0ImposedPointsCoupling
//=========================================================================================================
//  CGM_Bsf_Level = 12
//=========================================================================================================
// Identificateur Modification : LoftOrientationBis 
// Operateur                   : loft (CATFrFTopologicalSweepCx2)
// Responsable                 : NLD
// Date                        : 03-05-01
// commentaire                 : orientation des lofts (recorrection dans inversion profil)
CATCGMVersionLevel(Loft_CorrectOrientationManagementBis)
#define CGM_Versionning_Loft_CorrectOrientationManagementBis  CATCGMVersionLevel_Loft_CorrectOrientationManagementBis
//=========================================================================================================
//  CGM_Bsf_Level = 13 
//=========================================================================================================
// Identificateur Modification : WireHomogenizationChangeD1CouplingTolerance
// Operateur                   : loft/blend (CATFrFWireHomogenization)
// Responsable                 : NLD
// Date                        : 14-05-01
// commentaire                 : changement tolerance pour couplage vertex G1
// Identificateur Modification : SweepVariationnelSuiviFunctionalGuideTer
// Operateur                   : sweep variationnel (CATFrFTopologicalSweepCx2)
// Responsable                 : NLD
// Date                        : 14-05-01
// commentaire                 : suivi complet avec guides fonctionnelles
CATCGMVersionLevel(Sweep_SuiviFunctionalGuidesTer)
#define CGM_Versionning_Sweep_SuiviFunctionalGuidesTer  CATCGMVersionLevel_Sweep_SuiviFunctionalGuidesTer
// Identificateur Modification : LoftMultiFitting
// Operateur                   : loft (CATFrFTopologicalSweepCx2)
// Responsable                 : NLD
// Date                        : 14-05-01
// commentaire                 : multifitting: lissage couple des profils
CATCGMVersionLevel(Loft_MultiFitting)
#define CGM_Versionning_Loft_MultiFitting  CATCGMVersionLevel_Loft_MultiFitting
//=========================================================================================================
//  CGM_Bsf_Level = 14 
//=========================================================================================================
// Identificateur Modification : LoftImplicitSpineVersion2_ForcePlanesCase
// Operateur                   : loft/spine (CATFrFTopologicalSweepCx2, CATTopSpineCx5)
// Responsable                 : NLD
// Date                        : 15-05-01
// commentaire                 : si aucun profil et que des plans, passage dans le code
//                               specifique plans que l'on ait ou non un point de depart
CATCGMVersionLevel(Loft_SpineVersion2_ForcePlaneCase)
#define CGM_Versionning_Loft_SpineVersion2_ForcePlaneCase  CATCGMVersionLevel_Loft_SpineVersion2_ForcePlaneCase
//=========================================================================================================
//  CGM_Bsf_Level = 15
//=========================================================================================================
// Identificateur Modification : CAThkPilot::Initialize
// Operateur                   : Thickness/Shell/SkinOffset/ThickSurface/SkinExtrapolation
// Responsable                 : LAT
// Date                        : 29-05-01
// commentaire                 : modification du journal skin
//=========================================================================================================

#endif
