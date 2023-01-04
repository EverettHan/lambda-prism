#ifndef CATCGMVersionMacroDefine1_h
#define CATCGMVersionMacroDefine1_h
// COPYRIGHT DASSAULT SYSTEMES  2002

CGMVersionMacroDefine(1   ,TopologicalOperators_TestOnly                               ,PBE ,27-03-2000 ,"toujours actif pour tests ")


//=========================================================================================================
// Avant Full Versionning
//=========================================================================================================
CGMVersionMacroDefine(4   ,Sweep_ReportModifZero                                       ,NLD ,10-07-2000 ,"Avant Full Versionning ")
CGMVersionMacroDefine(5   ,Sweep_DebugLyingOnV5R5                                      ,NLD ,19-09-2000 ,"Avant Full Versionning ")
CGMVersionMacroDefine(7   ,Sweep_ReportModifSimplif                                    ,NLD ,08-03-2001 ,"Avant Full Versionning ")
CGMVersionMacroDefine(7   ,Sweep_CanonicSurfacesWithSpine                              ,NLD ,08-03-2001 ,"Avant Full Versionning ")
CGMVersionMacroDefine(7   ,Loft_CorrectOrientationManagement                           ,NLD ,08-03-2001 ,"Avant Full Versionning ")
CGMVersionMacroDefine(9   ,Loft_SpineVersion1Pointe                                    ,NLD ,05-04-2001 ,"Avant Full Versionning ")
CGMVersionMacroDefine(9   ,Sweep_SuiviFunctionalGuides                                 ,NLD ,05-04-2001 ,"Avant Full Versionning ")
CGMVersionMacroDefine(11  ,Sweep_AutomaticSpine                                        ,NLD ,18-04-2001 ,"Avant Full Versionning ")
CGMVersionMacroDefine(11  ,Sweep_SuiviFunctionalGuidesBis                              ,NLD ,18-04-2001 ,"Avant Full Versionning ")
CGMVersionMacroDefine(11  ,Sweep_ImplicitProfileBodyInfoSign                           ,NLD ,18-04-2001 ,"Avant Full Versionning ")
CGMVersionMacroDefine(11  ,Loft_ProfilesHomogenizationWithG0ImposedPointsCoupling      ,NLD ,18-04-2001 ,"Avant Full Versionning ")
CGMVersionMacroDefine(12  ,Loft_CorrectOrientationManagementBis                        ,NLD ,03-05-2001 ,"Avant Full Versionning ")
CGMVersionMacroDefine(13  ,Sweep_SuiviFunctionalGuidesTer                              ,NLD ,14-05-2001 ,"Avant Full Versionning ")
CGMVersionMacroDefine(13  ,Loft_MultiFitting                                           ,NLD ,14-05-2001 ,"Avant Full Versionning ")
CGMVersionMacroDefine(14  ,Loft_SpineVersion2_ForcePlaneCase                           ,NLD ,15-05-2001 ,"Avant Full Versionning ")


//=========================================================================================================
// V5R7 SP1
//=========================================================================================================
CGMVersionMacroDefine(16  ,Project_Journal_Vertex                                      ,PBE ,21-06-2001 ,"V5R7 SP1 ")
CGMVersionMacroDefine(16  ,Project_Journal_LyingOn                                     ,PBE ,21-06-2001 ,"V5R7 SP1 ")
CGMVersionMacroDefine(16  ,Project_ClosingVertex                                       ,PBE ,21-06-2001 ,"V5R7 SP1 ")
CGMVersionMacroDefine(16  ,Intersect_Journal_Vertex                                    ,PBE ,21-06-2001 ,"V5R7 SP1 ")
CGMVersionMacroDefine(16  ,SplitTrim_Journal_Confusion                                 ,PBE ,21-06-2001 ,"V5R7 SP1 ")
CGMVersionMacroDefine(16  ,SplitTrim_BuildBody                                         ,PBE ,21-06-2001 ,"V5R7 SP1 ")
CGMVersionMacroDefine(16  ,Join_BuildBody                                              ,PBE ,21-06-2001 ,"V5R7 SP1 ")
CGMVersionMacroDefine(16  ,CATCreateTopCreateDomains                                   ,TCX ,21-06-2001 ,"V5R7 SP1 ")
CGMVersionMacroDefine(16  ,ExtrapolWire_Orientation                                    ,ALM ,21-06-2001 ,"V5R7 SP1 ")
CGMVersionMacroDefine(16  ,Sweep_Simplify                                              ,FDS ,21-06-2001 ,"V5R7 SP1 ")
CGMVersionMacroDefine(16  ,Revol_Angle                                                 ,SRO ,21-06-2001 ,"V5R7 SP1 ")
CGMVersionMacroDefine(16  ,Blend_Journal                                               ,JSX ,21-06-2001 ,"V5R7 SP1 - passage au meilleur niveau de suivi a ce jour comme en sweep ")
CGMVersionMacroDefine(16  ,LoftBlendPreciseDegeneratedEdgesReport                      ,NLD ,21-06-2001 ,"V5R7 SP1 - suivi fin des pointes en blend et en loft avec heritage des 2 edges entourant la pointe et non plus aleatoirement de l'une ou de l'autre (si pointe en finheritage edge+vertex) ")
CGMVersionMacroDefine(16  ,ComputeAdaptativeSweepOrientation                           ,NLD ,21-06-2001 ,"V5R7 SP1 - dans le sweep adaptatifen l'absence d'homogeneisation des profilset dans la possibilite de recevoir des profils desordonneson stabilise l'orientation du sweep avec les memes conventions que dans le loft: du premier vers le dernier profil dans l'ordre de reception ")
CGMVersionMacroDefine(16  ,Parallel_MappingLaw                                         ,JHN-CCK,21-06-2001 ,"V5R7 SP1 ")
CGMVersionMacroDefine(16  ,Spine_Implicit_PlaneCase                                    ,NDN-NLD,21-06-2001 ,"V5R7 SP1 - dans la spine implicite et dans le loft dans le cas ou l'on ne recoit que des planson supprime le calcul canonique calculant des arcs de cerclesa l'origine de trop grandes variations de courbure ")
CGMVersionMacroDefine(16  ,CircleFillet_Twist                                          ,PKC ,21-06-2001 ,"V5R7 SP1 ")
CGMVersionMacroDefine(16  ,offset_bisector                                             ,DPS ,21-06-2001 ,"V5R7 SP1 ")


//=========================================================================================================
// V5R7 SP1 / V5R10 SP3
//=========================================================================================================
CGMVersionMacroDefine(16  ,Merge_KeepFrozenLyingOn                                     ,TCX ,24-12-2002 ,"V5R7 SP1 / V5R10 SP3 ")


//=========================================================================================================
// V5R7 SP2
//=========================================================================================================
CGMVersionMacroDefine(17  ,Trim_Journal_Bord_a_Bord                                    ,PBE ,21-06-2001 ,"V5R7 SP2 ")
CGMVersionMacroDefine(18  ,FilletFaceFace_InversionSupport                             ,JMA ,21-06-2001 ,"V5R7 SP2 ")
CGMVersionMacroDefine(19  ,IntersectShell_Orientation                                  ,XDT ,21-06-2001 ,"V5R7 SP2 ")


//=========================================================================================================
// V5R7 SP3
//=========================================================================================================
CGMVersionMacroDefine(20  ,Split_ClosedWireBySingleVertex                              ,PBE ,04-09-2001 ,"V5R7 SP3 ")


//=========================================================================================================
// V5R7 SP4
//=========================================================================================================
CGMVersionMacroDefine(21  ,Join_BuildBody_Wire                                         ,PBE ,11-09-2001 ,"V5R7 SP4 ")
CGMVersionMacroDefine(21  ,Fillet_Extrapol_Around_Twist                                ,RR  ,11-09-2001 ,"V5R7 SP4 ")
CGMVersionMacroDefine(21  ,Corner_Relimitation                                         ,JHN ,11-09-2001 ,"V5R7 SP4 ")
CGMVersionMacroDefine(21  ,Corner_Journal                                              ,JHN ,11-09-2001 ,"V5R7 SP4 ")
CGMVersionMacroDefine(22  ,Sweep_AdvancedTwistDetection                                ,NDN-CCK-NLD,11-09-2001 ,"V5R7 SP4 ")
CGMVersionMacroDefine(23  ,ImplicitSpineOperator_WithGuides                            ,NDN-CCK-NLD,11-09-2001 ,"V5R7 SP4 ")
CGMVersionMacroDefine(23  ,Ribbon_Edge_High_Incidence_Crossing                         ,RR  ,11-09-2001 ,"V5R7 SP4 - franchissements en biais des Edges ")
CGMVersionMacroDefine(23  ,Fillet_InitialChoiceOfShiftedTracks                         ,RR-JMA,11-09-2001 ,"V5R7 SP4 ")
CGMVersionMacroDefine(23  ,Parallel_Boolean                                            ,JHN ,11-09-2001 ,"V5R7 SP4 ")
CGMVersionMacroDefine(24  ,CleanCurve_FillEdges                                        ,MMO ,11-09-2001 ,"V5R7 SP4 - reconnaissance aretes de Bouchage CleanCurve ")
CGMVersionMacroDefine(25  ,Fill_NewApprox                                              ,NDN ,11-09-2001 ,"V5R7 SP4 ")


//=========================================================================================================
// V5R7 SP5
//=========================================================================================================
CGMVersionMacroDefine(30  ,RibRelim4Aretes                                             ,FBZ ,11-09-2001 ,"V5R7 SP5 - Activation de nouveaux traitements pour la relimitation a 4 aretes CATIntersectRib : Prise en compte des vertex deja poses coupants sur une arete en confusion avec l'autre coupante ")
CGMVersionMacroDefine(31  ,Draft_SupportChoiceForDraftSurface                          ,RR-PRL,11-09-2001 ,"V5R7 SP5 - Activation du choix de la PCurve (sur la face initiale ou la face neutre) qui sert de support au calcul de la surface draft ")
CGMVersionMacroDefine(31  ,Draft_DRLCoveredFaces                                       ,RR-PRL,11-09-2001 ,"V5R7 SP5 - Activation de la modification du soft de recherche des faces couvertes par des faces reflectline ")
CGMVersionMacroDefine(31  ,Draft_ThrowForDRLKODiagnostics                              ,RR-PRL,11-09-2001 ,"V5R7 SP5 - Activation de la sortie en erreur Draft Reflect en fonction des diagnostics du DSC ")
CGMVersionMacroDefine(32  ,RibNuplet_FlatVertex                                        ,RR-ASE,11-09-2001 ,"V5R7 SP5 ")
CGMVersionMacroDefine(33  ,Check_Offset_Smooth_Edge                                    ,DPS ,11-09-2001 ,"V5R7 SP5 ")
CGMVersionMacroDefine(34  ,BlendRibbon_Hermetisation                                   ,FDL ,11-09-2001 ,"V5R7 SP5 - hermetisation des rubans fillets ")
CGMVersionMacroDefine(35  ,Ribbon_BlendPropagationSpecMatching                         ,RR-JMA,11-09-2001 ,"V5R7 SP5 ")
CGMVersionMacroDefine(36  ,Intersect_Journal_DeleteOrder                               ,PBE ,22-10-2001 ,"V5R7 SP5 - Elimination d'ordre Delete superflu dans Intersectpouvant perturber le journal de Split ")
CGMVersionMacroDefine(37  ,FDT_V5R7SP5_RelimPartingEnhancement_1                       ,ASE ,30-10-2001 ,"V5R7 SP5 - evolutions de Ribbon ")
CGMVersionMacroDefine(38  ,Connect_TwistDetection                                      ,PKC ,09-11-2001 ,"V5R7 SP5 ")
CGMVersionMacroDefine(39  ,Sweep_TwistDetectionOnProfiles                              ,NDN-CCK-NLD,11-09-2001 ,"V5R7 SP5 - Detection de Twist pour Loft ")
CGMVersionMacroDefine(41  ,Fill_ModifOrientationFirstEdge                              ,JEP-MPS,13-11-2001 ,"V5R7 SP5 - orientation dans le remplissage Fill ")
CGMVersionMacroDefine(42  ,Blend_PreciseCCVMapping                                     ,JSX ,13-11-2001 ,"V5R7 SP5 - mapping de courbe plus précis dans le blend ")
CGMVersionMacroDefine(43  ,ThickSurface_NewMappingForBlend                             ,DPS-JSX,13-11-2001 ,"V5R7 SP5 ")
CGMVersionMacroDefine(44  ,NormalComb_Simplify                                         ,NDN-MNA,14-11-2001 ,"V5R7 SP5 - Simplification evaluation du peigne en normal ")
CGMVersionMacroDefine(45  ,Geodesic_WithInit                                           ,JHN ,15-11-2001 ,"V5R7 SP5 ")
CGMVersionMacroDefine(46  ,Offset_BisectorDeformation                                  ,DPS-JBX,15-11-2001 ,"V5R7 SP5 ")


//=========================================================================================================
// V5R7 SP6
//=========================================================================================================
CGMVersionMacroDefine(60  ,RlmUtilSurfExtrapolationOnVertex                            ,GDR ,23-11-2001 ,"V5R7 SP6 - Activation du changement d'extrapolation des surfaces complementaires par passage du vertex au lieu de l'edge ")
CGMVersionMacroDefine(61  ,Loft_SnappingOn2Profiles                                    ,NLD ,27-11-2001 ,"V5R7 SP6 - Activation du snapping entre 2 profils dans le loft ! ")
CGMVersionMacroDefine(62  ,TopRibSewing_ErrorInCaseOfAmbiguousFace                     ,JMA ,30-11-2001 ,"V5R7 SP6 - Sortie en erreur dans le cas de face pathologiques ")
CGMVersionMacroDefine(63  ,RibRelim_BadFacesComeLast                                   ,ASE ,03-12-2001 ,"V5R7 SP6 ")
CGMVersionMacroDefine(64  ,SmartDuplicate_LyingOnLinks                                 ,TCX ,06-12-2001 ,"V5R7 SP6 ")
CGMVersionMacroDefine(65  ,Fillet_EndTwistManagement                                   ,RR  ,07-12-2001 ,"V5R7 SP6 - arete de bouchage ")

//=========================================================================================================
// V5R8 SP1
//=========================================================================================================
CGMVersionMacroDefine(70  ,Simplify_Cylinders_Inverse                                  ,FDS ,10-12-2001 ,"V5R8 SP1 - Simplification des cylindres avec axes opposes ")
CGMVersionMacroDefine(71  ,Junction_Edges                                              ,HCN ,14-12-2001 ,"V5R8 SP1 - arete de bouchage ")
CGMVersionMacroDefine(72  ,Simplif_ConfusionFaces                                      ,XDT ,14-12-2001 ,"V5R8 SP1 - Activation de la simplification TOYOTA ")
CGMVersionMacroDefine(73  ,Draft_RecursiveCompletion                                   ,PRL ,14-12-2001 ,"V5R8 SP1 ")
CGMVersionMacroDefine(74  ,RibRelim_CouplingECrvSur                                    ,FBZ ,14-12-2001 ,"V5R8 SP1 - Recherche de coupling EC/Surf dans la relimitation et la creation de nuplet de connexion ")
CGMVersionMacroDefine(75  ,ExtruderBySweepExtrapolation                                ,SRO ,18-12-2001 ,"V5R8 SP1 - RI326021 ")
CGMVersionMacroDefine(76  ,Fillet_Sharpness_Setting_Level1                             ,RR  ,04-01-2002 ,"V5R8 SP1 - Marquage des Edges mortes dans Fillet ")
CGMVersionMacroDefine(77  ,Sweep_NewSmooth                                             ,NDN ,08-01-2002 ,"V5R8 SP1 - Nouveau Smooth pour le Sweep ")
CGMVersionMacroDefine(78  ,Intersect_StabilizeOrientation                              ,ICE ,11-01-2002 ,"V5R8 SP1 - Stabilisation orientation Intersect Shell Shell ")
CGMVersionMacroDefine(79  ,Offset_KeepFaceAlongDegenSurf                               ,DPS-NBR,11-01-2002 ,"V5R8 SP1 ")
CGMVersionMacroDefine(80  ,Offset_LogicalSmoothEdges                                   ,DPS ,15-01-2002 ,"V5R8 SP1 - marquage des aretes mortes dans Offset ")
CGMVersionMacroDefine(81  ,Extrapol_With_Spine                                         ,JSX ,15-01-2002 ,"V5R8 SP1 - Extrapolation avec utilisation de operateur Sweep ")
CGMVersionMacroDefine(82  ,Projection_NewOption_For_GeometricalOperator                ,PBE ,18-01-2002 ,"V5R8 SP1 ")
CGMVersionMacroDefine(83  ,TriTangent_Orientation                                      ,JHN ,18-01-2002 ,"V5R8 SP1 ")
CGMVersionMacroDefine(84  ,Parallel_SurfaceToCurve                                     ,JHN ,18-01-2002 ,"V5R8 SP1 ")
CGMVersionMacroDefine(85  ,ThroughTwoLines_Parallel                                    ,JHN ,18-01-2002 ,"V5R8 SP1 - RI 327728 ")
CGMVersionMacroDefine(86  ,Sweep_TwistDetectionOnProfiles2                             ,NDN-CCK,21-01-2002 ,"V5R8 SP1 - Detection de Twist pour Loft ")
CGMVersionMacroDefine(87  ,Sweep_SmoothUnspec                                          ,NDN ,23-01-2002 ,"V5R8 SP1 ")


//=========================================================================================================
// V5R8 SP2
//=========================================================================================================
CGMVersionMacroDefine(90  ,Draft_JournalForUnusedDraftFaces                            ,PRL ,01-02-2002 ,"V5R8 SP2 ")
CGMVersionMacroDefine(91  ,Draft_TwistInside_HeightAdjustement                         ,NDN-CCK,01-02-2002 ,"V5R8 SP2 ")
CGMVersionMacroDefine(92  ,Draft_SideToKeepImplement                                   ,GDR ,01-02-2002 ,"V5R8 SP2 ")
CGMVersionMacroDefine(93  ,ImplicitSpineOperator_AdaptativePlaneDetection              ,NLD-CCK,01-02-2002 ,"V5R8 SP2 ")
CGMVersionMacroDefine(94  ,RibRelim_PropagBeyondExtrRib                                ,PRL ,04-02-2002 ,"V5R8 SP2 ")
CGMVersionMacroDefine(95  ,NewJournalForFilletWithLimiting                             ,JMA ,04-02-2002 ,"V5R8 SP2 ")
CGMVersionMacroDefine(96  ,TwistAnalysis_NewTipDetection                               ,SDP ,04-02-2002 ,"V5R8 SP2 ")
CGMVersionMacroDefine(97  ,Sweep_Comb_Compatibility                                    ,MNA-NDN,12-02-2002 ,"V5R8 SP2 ")
CGMVersionMacroDefine(98  ,Fillet_Sharpness_Setting_Level2                             ,RR  ,15-02-2002 ,"V5R8 SP2 - Edges mortes dans Fillet ")
CGMVersionMacroDefine(99  ,Parallel_ExtrapolForTwist                                   ,JHN ,18-02-2002 ,"V5R8 SP2 ")
CGMVersionMacroDefine(100 ,CleanCurve_JournalInfos                                     ,MMO ,18-02-2002 ,"V5R8 SP2 - Nouveau journal avec Infos dans le Clean Curve Topologique ")
CGMVersionMacroDefine(101 ,Sweep_TwistDetectionForSweepDraft                           ,CCK ,18-02-2002 ,"V5R8 SP2 ")
CGMVersionMacroDefine(102 ,Sweep_TrimmedSkin                                           ,JMA ,19-02-2002 ,"V5R8 SP2 - RI333371 ")
CGMVersionMacroDefine(103 ,Corner_OrientGoodCurve                                      ,JHN ,19-02-2002 ,"V5R8 SP2 ")


//=========================================================================================================
// V5R8 SP3
//=========================================================================================================
CGMVersionMacroDefine(110 ,Sweep_PreciseCCVMapping                                     ,JSX ,26-02-2002 ,"V5R8 SP3 ")
CGMVersionMacroDefine(111 ,Intersect_StabilizeOrientation2                             ,EDS ,01-03-2002 ,"V5R8 SP3 - Stabilisation de l'orientation dans Intersect Shell Shell 2 ")
CGMVersionMacroDefine(112 ,Fillet_ExtrapolationEnhancement                             ,JHG ,01-03-2002 ,"V5R8 SP3 ")
CGMVersionMacroDefine(113 ,Parting_ExtrVertexSearch                                    ,PRL ,01-03-2002 ,"V5R8 SP3 ")
CGMVersionMacroDefine(114 ,TgtLine_Index                                               ,JHN ,01-03-2002 ,"V5R8 SP3 ")
CGMVersionMacroDefine(115 ,Rib_FlatDegenNuplet                                         ,ASE ,04-03-2002 ,"V5R8 SP3 ")
CGMVersionMacroDefine(116 ,CCVCleaner_LineDetectionV2                                  ,NLD ,08-03-2002 ,"V5R8 SP3 - RI336757 ")
CGMVersionMacroDefine(117 ,Blend_DirectionChoice                                       ,JSX ,11-03-2002 ,"V5R8 SP3 - Choix des directions en prenant en compte l'ordre des domaines du coupling ")
CGMVersionMacroDefine(118 ,SweepDraft_SpineInsteadOfGuide                              ,NDN ,18-03-2002 ,"V5R8 SP3 ")
CGMVersionMacroDefine(119 ,AutoLoft_SwitchDiagnosis                                    ,MNA ,18-03-2002 ,"V5R8 SP3 - RI336993 ")
CGMVersionMacroDefine(120 ,Sweep_CleanGuidesParametersV2                               ,NLD ,18-03-2002 ,"V5R8 SP3 ")
CGMVersionMacroDefine(121 ,Healing_CurvatureVariation                                  ,JEP/JCT,19-03-2002 ,"V5R8 SP3 ")
CGMVersionMacroDefine(122 ,CornerOnSupport_OffsetOrient                                ,JHN ,22-03-2002 ,"V5R8 SP3 - RI336738 ")
CGMVersionMacroDefine(123 ,ImplicitSpine_NaturalTgtEstimation                          ,CCK ,22-03-2002 ,"V5R8 SP3 - RI334421 ")
CGMVersionMacroDefine(124 ,Sweep_CleanGuidesParametersV3                               ,NLD ,22-03-2002 ,"V5R8 SP3 ")
CGMVersionMacroDefine(125 ,Sweep_CheckForSpineSmoothing1                               ,NDN ,26-03-2002 ,"V5R8 SP3 ")
CGMVersionMacroDefine(126 ,Parallel_WithoutLayDownReport                               ,JHN ,26-03-2002 ,"V5R8 SP3 ")


//=========================================================================================================
// V5R8 SP4
//=========================================================================================================
CGMVersionMacroDefine(130 ,ClosedSweepRib_Journal                                      ,SRO ,29-03-2002 ,"V5R8 SP4 ")
CGMVersionMacroDefine(131 ,Project_Journal_LyingOn2                                    ,PBE ,29-03-2002 ,"V5R8 SP4 - nouveau journal de posage ")
CGMVersionMacroDefine(132 ,Sweep_RelimitationPartialPocket                             ,FDS ,05-04-2002 ,"V5R8 SP4 ")
CGMVersionMacroDefine(133 ,Sweep_ExtractProfileDirection                               ,MNA ,09-04-2002 ,"V5R8 SP4 ")
CGMVersionMacroDefine(134 ,Parallel_NewTwistDetection                                  ,JHN ,10-04-2002 ,"V5R8 SP4 ")
CGMVersionMacroDefine(135 ,Sweep_TwistDetectionOnProfiles3                             ,CCK ,10-04-2002 ,"V5R8 SP4 ")
CGMVersionMacroDefine(136 ,Filling_JournalEvolution                                    ,MBS ,10-04-2002 ,"V5R8 SP4 ")


//=========================================================================================================
// V5R8 SP5
//=========================================================================================================
CGMVersionMacroDefine(140 ,Split_ClosingPointManagement                                ,PBE ,17-04-2002 ,"V5R8 SP5 - Split/Trim Wire et point de fermeture ")
CGMVersionMacroDefine(141 ,Project_Journal_LyingOn3                                    ,PBE ,22-04-2002 ,"V5R8 SP5 ")
CGMVersionMacroDefine(142 ,AutoLoft_TwistDetection                                     ,NDN ,22-04-2002 ,"V5R8 SP5 ")
CGMVersionMacroDefine(143 ,Sweep_ExtractCombOnGuide                                    ,MNA ,22-04-2002 ,"V5R8 SP5 ")
CGMVersionMacroDefine(144 ,SimilarCrv_IsC1                                             ,CCK ,22-04-2002 ,"V5R8 SP5 ")
CGMVersionMacroDefine(145 ,Sweep_ViewingDirection_PipeV4                               ,NLD ,30-04-2002 ,"V5R8 SP5 ")
CGMVersionMacroDefine(146 ,Sweep_DeploySoftwareConfigurationV1                         ,NLD ,30-04-2002 ,"V5R8 SP5 ")
CGMVersionMacroDefine(147 ,Rib_CheckContinuity_ClosedSurfaceCrossing                   ,PRL ,30-04-2002 ,"V5R8 SP5 ")
CGMVersionMacroDefine(148 ,Fillet_NewInitialisationOfShiftedTracks                     ,JMA ,02-05-2002 ,"V5R8 SP5 ")
CGMVersionMacroDefine(149 ,Rib_UnstableMultipleSolutions                               ,ASE ,02-05-2002 ,"V5R8 SP5 ")
CGMVersionMacroDefine(150 ,TwistDetectionOnSweepCanonicSurfaces                        ,NLD ,02-05-2002 ,"V5R8 SP5 ")
CGMVersionMacroDefine(151 ,Fillet_LocalTwist                                           ,RR  ,07-05-2002 ,"V5R8 SP5 - Traitement des twist lateraux locaux ")
CGMVersionMacroDefine(152 ,Relim_CompletionPapillon                                    ,ASE ,07-05-2002 ,"V5R8 SP5 ")
CGMVersionMacroDefine(153 ,Offset_SearchSameEdge                                       ,JBX ,07-05-2002 ,"V5R8 SP5 ")
CGMVersionMacroDefine(154 ,Fillet_SnappingVertex                                       ,FDL ,07-05-2002 ,"V5R8 SP5 ")
CGMVersionMacroDefine(155 ,Fillet_RejectNonMatchMinimalPropagationInit                 ,JHG ,13-05-2002 ,"V5R8 SP5 ")


//=========================================================================================================
// V5R9 SP1
//=========================================================================================================
CGMVersionMacroDefine(160 ,PlanarFill_StableOrientation                                ,NDN ,31-05-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(161 ,Connect_TwistDetection2                                     ,PKC ,31-05-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(162 ,Fill_ModifOrientationPowerFill                              ,MBS ,31-05-2002 ,"V5R9 SP1 - RI344376 ")
CGMVersionMacroDefine(163 ,Simplify_Journal_FacesWithConfusion                         ,FDS ,31-05-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(164 ,LengthOnClosedWire                                          ,SRO ,31-05-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(165 ,Sweep_CleanGuidesParametersV4                               ,NLD ,03-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(166 ,Blend_G0OnG2Point                                           ,JSX ,03-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(167 ,ImposedPointMapping_ClosureForCompositeLaw                  ,JSX ,03-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(168 ,Fillet_NewPointDeformation                                  ,SDP ,07-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(169 ,Sweep_Marching_SmallMargin                                  ,JSX ,07-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(170 ,CreateBodyPlanar                                            ,AOV ,07-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(171 ,Relim_BestFaceForExtrapolRibbon                             ,ASE ,10-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(172 ,Fillet_RejectImpossibleKeepEdgeRelimitation                 ,JHG ,10-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(173 ,Fillet_ExtrapolationBeforeRelimitation                      ,JMA ,10-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(174 ,Sweep_ReportAllInitialEdges                                 ,NLD ,11-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(175 ,Draft_RecursiveCompletionForInitRelim                       ,PRL ,14-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(176 ,SurSurWithInits_KeepIncompleteMergedCurve                   ,SDP ,17-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(177 ,Offset_SameNormalInSuperEdge                                ,DPS ,17-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(178 ,Fillet_MultiParting                                         ,JMA ,18-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(179 ,Fillet_ExportCoarseUntilIn                                  ,FDN ,21-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(180 ,Rib_ComputeSimpleNuplets                                    ,PRL ,21-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(181 ,Sweep_TwistDetectionOnProfiles4                             ,CCK ,21-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(182 ,Draft_FindRealStartAndEnd                                   ,PRL ,21-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(183 ,Fill_PowerFillLevel4                                        ,MBS ,24-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(184 ,Fillet_InitialisationPerformanceOptimisation                ,JMA ,24-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(185 ,Chamfer_TwistDetection                                      ,FCX ,24-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(186 ,CleanCurve_FillEdgesHole                                    ,MMO ,24-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(187 ,Relim_CompletionPropag                                      ,ASE ,24-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(188 ,Project_WireShellOrientation                                ,PBE ,24-06-2002 ,"V5R9 SP1 ")
CGMVersionMacroDefine(189 ,Draft_InitClosedRelim                                       ,PRL ,25-06-2002 ,"V5R9 SP1 ")


//=========================================================================================================
// V5R9 SP2
//=========================================================================================================
CGMVersionMacroDefine(200 ,CleanCurve_OptimLocGlob                                     ,MMO ,21-06-2002 ,"V5R9 SP2 - variable activee en avance pour V5R10 GA ")
CGMVersionMacroDefine(201 ,Smooth_LocalOptimizationForSpine                            ,NDN ,21-06-2002 ,"V5R9 SP2 - variable activee en avance pour V5R10 GA ")
CGMVersionMacroDefine(202 ,Healing_SingularCases                                       ,JJC ,05-07-2002 ,"V5R9 SP2 ")
CGMVersionMacroDefine(203 ,Connect_TwistDetection3                                     ,FCX ,05-07-2002 ,"V5R9 SP2 ")
CGMVersionMacroDefine(204 ,Project_WireShellOrientationMultiDomain                     ,PBE ,05-07-2002 ,"V5R9 SP2 ")
CGMVersionMacroDefine(205 ,Blend_DeploySoftwareConfigurationInThick                    ,JSX ,05-07-2002 ,"V5R9 SP2 ")
CGMVersionMacroDefine(206 ,CloseOperator_Face_Check                                    ,SRO ,09-07-2002 ,"V5R9 SP2 ")
CGMVersionMacroDefine(207 ,Revol_Angle2                                                ,SRO ,09-07-2002 ,"V5R9 SP2 ")
CGMVersionMacroDefine(208 ,Fillet_TestRelimAutoIntersection                            ,JHG ,09-07-2002 ,"V5R9 SP2 ")
CGMVersionMacroDefine(209 ,Fillet_IsotopologicalSelectInRelimitation                   ,JMA ,12-07-2002 ,"V5R9 SP2 - RI347574 ")
CGMVersionMacroDefine(210 ,Sweep_ViewingDirection_PipeV4_V2                            ,NLD ,12-07-2002 ,"V5R9 SP2 ")
CGMVersionMacroDefine(211 ,IntersectShellShell_ClosureStabilization                    ,EDS ,12-07-2002 ,"V5R9 SP2 - RI352867 ")
CGMVersionMacroDefine(212 ,Split_Journal_LyingOn                                       ,PBE ,23-07-2002 ,"V5R9 SP2 ")
CGMVersionMacroDefine(213 ,Fill_ConventionOrientation                                  ,MBS ,23-07-2002 ,"V5R9 SP2 - RI252389 ")
CGMVersionMacroDefine(214 ,Parallel_CasDeLaMarche                                      ,JHN ,23-07-2002 ,"V5R9 SP2 ")
CGMVersionMacroDefine(215 ,RollingEdge_MultiConstraints                                ,FCX ,23-07-2002 ,"V5R9 SP2 ")
CGMVersionMacroDefine(216 ,Fillet_CoplanarSmoothRelimitation                           ,JMA ,23-07-2002 ,"V5R9 SP2 ")
CGMVersionMacroDefine(217 ,Fillet_UnTwist_Sharpness_Check                              ,RR  ,23-07-2002 ,"V5R9 SP2 ")
CGMVersionMacroDefine(218 ,Sweep_Canonic_Stabilization_Orientation                     ,JSX ,26-07-2002 ,"V5R9 SP2 ")
CGMVersionMacroDefine(219 ,Sweep_ImproveMultiSolutionHandling                          ,JHG ,26-07-2002 ,"V5R9 SP2 ")
CGMVersionMacroDefine(220 ,Draft_PbJournal_RI0345467                                   ,GDR ,26-07-2002 ,"V5R9 SP2 ")


//=========================================================================================================
// V5R9 SP3
//=========================================================================================================
CGMVersionMacroDefine(225 ,Parallel_PreciseTwist                                       ,JHN ,09-08-2002 ,"V5R9 SP3 ")
CGMVersionMacroDefine(226 ,ExtrapWireOnShell_Journal                                   ,AOV ,14-08-2002 ,"V5R9 SP3 ")
CGMVersionMacroDefine(227 ,Loft_NewFitOnProfileCombs                                   ,MNA ,14-08-2002 ,"V5R9 SP3 ")
CGMVersionMacroDefine(228 ,Fillet_UseInclusionForSmoothRelim                           ,JHG ,14-08-2002 ,"V5R9 SP3 ")
CGMVersionMacroDefine(229 ,Blend_CouplingLine_CheckHomoOrient                          ,JSX ,14-08-2002 ,"V5R9 SP3 ")
CGMVersionMacroDefine(230 ,Sweep_Plan                                                  ,ALV ,14-08-2002 ,"V5R9 SP3 ")
CGMVersionMacroDefine(231 ,Thickness_FaceWithInternalLoop                              ,NBR ,21-08-2002 ,"V5R9 SP3 ")
CGMVersionMacroDefine(232 ,SweepLoft_NewIntersectionCoupling                           ,MNA ,26-08-2002 ,"V5R9 SP3 ")
CGMVersionMacroDefine(233 ,Loft_ExactGuide                                             ,MNA ,26-08-2002 ,"V5R9 SP3 ")
CGMVersionMacroDefine(234 ,Sweep_DeploySoftwareConfigurationV2                         ,NLD ,26-08-2002 ,"V5R9 SP3 ")
CGMVersionMacroDefine(235 ,ImposedPointMapping_Report_G0_Discontinuity                 ,JSX ,26-08-2002 ,"V5R9 SP3 ")
CGMVersionMacroDefine(236 ,Extrapol_G1_Mix_ISOandG0_Directions                         ,JSX ,26-08-2002 ,"V5R9 SP3 ")
CGMVersionMacroDefine(237 ,Sweep_SmoothAngleCanonicDetection1                          ,NDN ,29-08-2002 ,"V5R9 SP3 ")
CGMVersionMacroDefine(238 ,HealingSingularity_AdjustPoles                              ,JJC ,29-08-2002 ,"V5R9 SP3 ")
CGMVersionMacroDefine(239 ,BodyFromLengthOnShell_DistNull                              ,AOV ,29-08-2002 ,"V5R9 SP3 ")
CGMVersionMacroDefine(240 ,Corner_SystemXY                                             ,FCX ,29-08-2002 ,"V5R9 SP3 ")


//=========================================================================================================
// V5R9 SP4
//=========================================================================================================
CGMVersionMacroDefine(250 ,Sweep_HybridClean2D3D                                       ,NLD ,06-09-2002 ,"V5R9 SP4 ")
CGMVersionMacroDefine(251 ,Fillet_PointDeformationTwistedTraces                        ,SDP ,13-09-2002 ,"V5R9 SP4 ")
CGMVersionMacroDefine(252 ,Sweep_NewIntersectionSurSur                                 ,AOV ,13-09-2002 ,"V5R9 SP4 ")
CGMVersionMacroDefine(253 ,IntersectShell_CloseScar                                    ,XDT ,13-09-2002 ,"V5R9 SP4 ")
CGMVersionMacroDefine(254 ,SplitTrim_KeepRemove_StabilizeOrientation                   ,PBE ,13-09-2002 ,"V5R9 SP4 ")
CGMVersionMacroDefine(255 ,CGMJournal_Tass_A_Creation_A                                ,HCN ,13-09-2002 ,"V5R9 SP4 ")
CGMVersionMacroDefine(256 ,MaxOffset_ImprovedMinimize                                  ,SDP ,17-09-2002 ,"V5R9 SP4 ")


//=========================================================================================================
// V5R10 SP1
//=========================================================================================================
CGMVersionMacroDefine(260 ,Blend_TwistDetection                                        ,JSX ,27-09-2002 ,"V5R10 SP1 ")
CGMVersionMacroDefine(261 ,Corner_Conflit_Indexation                                   ,JHN ,27-09-2002 ,"V5R10 SP1 ")
CGMVersionMacroDefine(262 ,Sweep_RelimitationPartialUpToLastPocket                     ,FDS ,27-09-2002 ,"V5R10 SP1 ")
CGMVersionMacroDefine(263 ,CCVCleaner_SmallCurves                                      ,NLD ,27-09-2002 ,"V5R10 SP1 ")
CGMVersionMacroDefine(264 ,Chamfer_MultiRubanEnhancement                               ,JMA ,30-09-2002 ,"V5R10 SP1 - RI359028 ")
CGMVersionMacroDefine(265 ,Draft_RCFforPartingEqNtrlCases                              ,PRL ,30-09-2002 ,"V5R10 SP1 ")
CGMVersionMacroDefine(266 ,Fillet_KeepEdgePropagation                                  ,FDN ,04-10-2002 ,"V5R10 SP1 ")
CGMVersionMacroDefine(267 ,Rib_RelimComplEnhancement                                   ,ASE ,07-10-2002 ,"V5R10 SP1 ")
CGMVersionMacroDefine(268 ,Parallel_Degen_Twist                                        ,JHN ,07-10-2002 ,"V5R10 SP1 ")
//CGMVersionMacroDefine(269 ,Sweep_Well_Balanced_Samples                                 ,JSX ,07-10-2002 ,"V5R10 SP1 ") // desactivation le 17-10-2002
CGMVersionMacroDefine(270 ,Fillet_Initialisation_NoMaxLimits                           ,RR  ,11-10-2002 ,"V5R10 SP1 ")
CGMVersionMacroDefine(271 ,Fillet_UnTwist_Notch                                        ,RR  ,11-10-2002 ,"V5R10 SP1 ")
CGMVersionMacroDefine(272 ,Project_Journal_PartiallyLyingOn                            ,XDT ,11-10-2002 ,"V5R10 SP1 ")
CGMVersionMacroDefine(273 ,Extrude_ChangeNumericalTest                                 ,ALV ,11-10-2002 ,"V5R10 SP1 ")
CGMVersionMacroDefine(274 ,Fillet_InitWithoutInterference                              ,FDL ,14-10-2002 ,"V5R10 SP1 ")
CGMVersionMacroDefine(275 ,Join_SharpnessEdgeCutting                                   ,PBE ,14-10-2002 ,"V5R10 SP1 ")
CGMVersionMacroDefine(276 ,CleanCurve_CleanClosure                                     ,MMO ,15-10-2002 ,"V5R10 SP1 ")
CGMVersionMacroDefine(277 ,RollingEdge_InitializeConstraintSign                        ,FCX ,18-10-2002 ,"V5R10 SP1 ")
CGMVersionMacroDefine(278 ,Parallel_Of_PCurve                                          ,JHN ,21-10-2002 ,"V5R10 SP1 ")
CGMVersionMacroDefine(279 ,SimilarCurve_Journal                                        ,AOV ,25-10-2002 ,"V5R10 SP1 ")
CGMVersionMacroDefine(280 ,ExtrapWireOnShell_AutoIntersect                             ,AOV ,25-10-2002 ,"V5R10 SP1 ")
CGMVersionMacroDefine(281 ,RibbonHomotopy_Init                                         ,FBZ ,25-10-2002 ,"V5R10 SP1 ")
//CGMVersionMacroDefine(282 ,Merge_KeepFrozenLyingOn                                     ,TCX ,25-10-2002 ,"V5R10 SP1 ") // activation systematique le 24-12-2002
CGMVersionMacroDefine(283 ,Healing_SetSharpnessOnTopology                              ,JEP ,28-10-2002 ,"V5R10 SP1 ")
CGMVersionMacroDefine(284 ,GeodesicPtPt_EdgeConfusion                                  ,AOV ,05-11-2002 ,"V5R10 SP1 ")


//=========================================================================================================
// V5R10 SP2
//=========================================================================================================
CGMVersionMacroDefine(290 ,GeodesicPtPt_NoConvergence                                  ,AOV ,08-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(291 ,SimilarCurve_BuildPoints                                    ,AOV ,08-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(292 ,CornerOnSupport_CircleTooShort                              ,ALV ,08-11-2002 ,"V5R10 SP2 ")
//CGMVersionMacroDefine(293 ,Posage_By_Sewing                                            ,ICE ,08-11-2002 ,"V5R10 SP2 ") // desactivation le 13-10-2002
CGMVersionMacroDefine(294 ,Fillet_Journal_EndingShellEdges                             ,RR  ,08-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(295 ,Sweep_Well_Balanced_Samples                                 ,JSX ,08-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(296 ,SurSurWithInits_MonoArcDeformation                          ,SDP ,12-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(297 ,SurSurWithInits_RestoreTrueTangent                          ,SDP ,12-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(298 ,Planar_Equation                                             ,JHN ,13-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(299 ,CleanCurve_KeepFunctionalEdges                              ,MMO ,15-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(300 ,Blend_TwistDetection_2                                      ,JSX ,15-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(301 ,Simplify_Edges_With_Sharpness_Control                       ,FDS ,15-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(302 ,LengthOnWire_Orientation                                    ,AOV ,15-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(303 ,Fillet_KeepKeep                                             ,FDN ,15-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(304 ,Fillet_MultiRibbonNewInitAnalysis                           ,JHG ,15-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(305 ,Posage_By_Sewing                                            ,ICE ,15-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(306 ,Sweep_ProfilePositioningV2                                  ,NLD ,15-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(307 ,Fillet_PointDeformationCheckGap                             ,KLX ,15-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(308 ,TritangentFillet_TwistDetection                             ,PKC ,18-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(309 ,Parallel_LogicForSmallEdge                                  ,JHN ,22-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(310 ,IntersectionCrvCrv_MeanPlaneMethod                          ,STY ,22-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(311 ,Fillet_MultiFacesNotchesLevel1                              ,JHG ,22-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(312 ,Offset_SimplifyEdges_Stabilization                          ,LAP ,25-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(313 ,Ribbon_ClosedTrack_RareSplit                                ,JMA ,26-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(314 ,Ribbon_ComplExtrapolExactPrediction                         ,ASE ,29-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(315 ,Rib_RelimCommonSurfaceWithEdgeSupport                       ,FBZ ,29-11-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(316 ,Bump_Level2                                                 ,PMG ,02-12-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(317 ,SweepVaria_MarchingWithFuncGuide                            ,JSX ,02-12-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(318 ,Corner_SearchingEndingPoints                                ,AOV ,02-12-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(319 ,Sweep_DerivativeUsingDomainsWidth                           ,JSX ,02-12-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(320 ,Fillet_SmoothRelim_NewShape                                 ,RR  ,03-12-2002 ,"V5R10 SP2 - RI355118 ")
CGMVersionMacroDefine(321 ,ConstantFillet_PointDeformWithoutCommonCurve                ,FCX ,06-12-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(322 ,Offset_MergeSectorsInsideSuperEdge                          ,DPS ,06-12-2002 ,"V5R10 SP2 ")
CGMVersionMacroDefine(323 ,V5R7SP5_Parallel_Error                                      ,JHN ,06-12-2002 ,"V5R10 SP2 ")


//=========================================================================================================
// V5R10 SP3
//=========================================================================================================
CGMVersionMacroDefine(330 ,Fillet_NoPropagCoarseAfterSnapping                          ,RR  ,13-12-2002 ,"V5R10 SP3 ")
CGMVersionMacroDefine(331 ,Fill_PowerFillLevel5                                        ,MPS ,13-12-2002 ,"V5R10 SP3 ")
CGMVersionMacroDefine(332 ,MaxOffset_Subdivide                                         ,SDP ,16-12-2002 ,"V5R10 SP3 ")
CGMVersionMacroDefine(333 ,Offset_LocalCollisionOptimization                           ,DPS ,16-12-2002 ,"V5R10 SP3 ")
CGMVersionMacroDefine(334 ,Fillet_NewCoplanarTolerance                                 ,FDN ,16-12-2002 ,"V5R10 SP3 ")
CGMVersionMacroDefine(335 ,Loft_StabilizeTwoProfiles                                   ,NDN ,16-12-2002 ,"V5R10 SP3 ")
CGMVersionMacroDefine(336 ,Corner_PtOnWireMultiProject                                 ,ALV ,17-12-2002 ,"V5R10 SP3 ")
CGMVersionMacroDefine(337 ,Extremum_ErasePlaneExtremum                                 ,JHN ,17-12-2002 ,"V5R10 SP3 ")
CGMVersionMacroDefine(338 ,Extrapolation_FixedLevel1                                   ,NDN ,07-01-2003 ,"V5R10 SP3 ")
CGMVersionMacroDefine(339 ,Parallel_StopPropagationOnInit                              ,JHN ,08-01-2003 ,"V5R10 SP3 ")
CGMVersionMacroDefine(340 ,IntersectShell_DuplicateLoop                                ,ICE ,10-01-2003 ,"V5R10 SP3 ")
CGMVersionMacroDefine(341 ,PoseSur_PropagateCoupling                                   ,XDT ,10-01-2003 ,"V5R10 SP3 ")
CGMVersionMacroDefine(342 ,FilletRollingEdge_TwistDetection                            ,PKC ,20-01-2003 ,"V5R10 SP3 ")


//=========================================================================================================
// V5R10 SP4
//=========================================================================================================
CGMVersionMacroDefine(350 ,Rib_InNupletCompletionForCheckIfEnded                       ,PRL ,17-01-2003 ,"V5R10 SP4 ")
CGMVersionMacroDefine(351 ,Healing_AdjustPCurveTangency                                ,JEP ,17-01-2003 ,"V5R10 SP4 ")
CGMVersionMacroDefine(352 ,Revol_NewPerpendicularChecker                               ,ALV ,17-01-2003 ,"V5R10 SP4 ")
CGMVersionMacroDefine(353 ,Fillet_KeepEdgePropagationBis                               ,FDN ,17-01-2003 ,"V5R10 SP4 ")
CGMVersionMacroDefine(354 ,Fillet_IsotopologicalInitEnhancement                        ,JMA ,17-01-2003 ,"V5R10 SP4 - RI368251 ")
CGMVersionMacroDefine(355 ,Sweep_ExtractCombNoCheckOfSens                              ,MNA ,24-01-2003 ,"V5R10 SP4 - RI371818 ")
CGMVersionMacroDefine(356 ,Fillet_FaceFaceInitMax                                      ,FDN ,24-01-2003 ,"V5R10 SP4 ")
CGMVersionMacroDefine(357 ,CleanCurve_SmoothConstraints                                ,RNO ,24-01-2003 ,"V5R10 SP4 ")
CGMVersionMacroDefine(358 ,Linear_SupportOrthogonality                                 ,JHN ,24-01-2003 ,"V5R10 SP4 ")
CGMVersionMacroDefine(359 ,Fillet_LocalInnerTwist                                      ,RR  ,24-01-2003 ,"V5R10 SP4 ")
CGMVersionMacroDefine(360 ,Offset_RebuildFaceAlongDegenSurf                            ,DPS ,24-01-2003 ,"V5R10 SP4 ")
CGMVersionMacroDefine(361 ,Fill_NewCombComputation                                     ,MNA ,24-01-2003 ,"V5R10 SP4 ")
CGMVersionMacroDefine(362 ,Offset_SimplifConfusedFace                                  ,NBR ,24-01-2003 ,"V5R10 SP4 ")
//CGMVersionMacroDefine(363 ,Fillet_IsotopoInitForNonAdjFaces                            ,JMA ,24-01-2003 ,"V5R10 SP4 - RI341201 ") // desactivation le 27-01-2003
CGMVersionMacroDefine(364 ,Corner_LyingSupportForReconvergence                         ,JHN ,27-01-2003 ,"V5R10 SP4 ")
CGMVersionMacroDefine(365 ,HoldCurveCircleFillet_MultiConstraints                      ,FCX ,27-01-2003 ,"V5R10 SP4 ")
CGMVersionMacroDefine(366 ,RelimitSkin_FreeEdgesJournal                                ,ICE ,29-01-2003 ,"V5R10 SP4 ")
CGMVersionMacroDefine(367 ,Develop_NewDefaultAxis                                      ,NDN ,31-01-2003 ,"V5R10 SP4 ")
CGMVersionMacroDefine(368 ,Rib_RelimExtrVertexOnContactCell                            ,FBZ ,31-01-2003 ,"V5R10 SP4 ")
CGMVersionMacroDefine(369 ,Corner_ComplementaryMode_PtOnCrvRad                         ,ALV ,31-01-2003 ,"V5R10 SP4 ")
CGMVersionMacroDefine(370 ,Corner_TriTangent_Redondancy                                ,ALV ,03-02-2003 ,"V5R10 SP4 ")
CGMVersionMacroDefine(371 ,Draft_ChangeSpecsWithCheck                                  ,PRL ,04-02-2003 ,"V5R10 SP4 ")
CGMVersionMacroDefine(372 ,Draft_InitClosedRelim2                                      ,PRL ,04-02-2003 ,"V5R10 SP4 ")
CGMVersionMacroDefine(373 ,Fillet_IsotopoInitForNonAdjFaces                            ,JMA ,07-02-2003 ,"V5R10 SP4 - RI341201 ")
CGMVersionMacroDefine(374 ,CleanCurve_SmallArcs                                        ,RNO ,07-02-2003 ,"V5R10 SP4 ")
CGMVersionMacroDefine(375 ,Sweep_Canonic_Stabilization_Orientation2                    ,NDN ,10-02-2003 ,"V5R10 SP4 ")
CGMVersionMacroDefine(376 ,ExtrapWireOnShell_FindInitialFace                           ,AOV ,10-02-2003 ,"V5R10 SP4 ")
//CGMVersionMacroDefine(377 ,PoseSur_RefCurveCouplingMergedCurve                         ,XDT ,14-02-2003 ,"V5R10 SP4 ") // desactivation le 20-02-2003
//CGMVersionMacroDefine(378 ,Parallel_TransfertBouchage                                  ,JHN ,14-02-2003 ,"V5R10 SP4 ") // desactivation le 20-02-2003
//CGMVersionMacroDefine(379 ,Parallel_ChoiceOfCurve                                      ,JHN ,14-02-2003 ,"V5R10 SP4 ") // desactivation le 20-02-2003
//CGMVersionMacroDefine(380 ,Parallel_CurveConsistency                                   ,JHN ,14-02-2003 ,"V5R10 SP4 ") // desactivation le 20-02-2003


//=========================================================================================================
// V5R11 SP1
//=========================================================================================================
CGMVersionMacroDefine(390 ,Line_NewInfiniteLimits                                      ,ALV ,24-02-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(391 ,CGMJournal_FindFirstLast                                    ,HCN ,24-02-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(392 ,ImplicitSpine_VersionCx10                                   ,CCK ,24-02-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(393 ,Sweep_GuidesHomogenizationWithLaws                          ,NLD ,24-02-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(394 ,Sweep_ProfilePositioningV3                                  ,NLD ,24-02-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(395 ,PoseSur_RefCurveCouplingMergedCurve                         ,XDT ,26-02-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(396 ,Parallel_TransfertBouchage                                  ,JHN ,26-02-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(397 ,Parallel_ChoiceOfCurve                                      ,JHN ,26-02-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(398 ,Parallel_CurveConsistency                                   ,JHN ,26-02-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(399 ,Healing_Singularity_Improvements                            ,JJC ,26-02-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(400 ,RollingEdge_SingularSystem                                  ,KLX ,26-02-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(401 ,MaxOffset_TotalDegeneracy                                   ,SDP ,28-02-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(402 ,Blend_PlanarG2Section                                       ,JSX ,28-02-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(403 ,Healing_AdjustOnSmallPCurve                                 ,JEP ,28-02-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(404 ,Corner_IndexationNextWireNotClosed                          ,ALV ,28-02-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(405 ,Fillet_ExtrapolForMultiRibbon                               ,JMA ,28-02-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(406 ,Fillet_AlwaysExtrapol20Percent                              ,RR  ,03-03-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(407 ,Linear_Simplification                                       ,JHN ,04-03-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(408 ,CanonicSweep_ComputeImposedParameter                        ,MNA ,07-03-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(409 ,Rib_RlmExtrapolRibConvexitySmoothCommonEdge                 ,ASE ,07-03-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(410 ,Intersection_CleanInterpol                                  ,KLX ,07-03-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(411 ,Intersection_CheckComponent                                 ,KLX ,07-03-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(412 ,ReflectCurve_NewSign                                        ,STY ,10-03-2003 ,"V5R11 SP1 ")
//CGMVersionMacroDefine(413 ,SurSurWithInits_ChooseSupportOfPLine                        ,SDP ,10-03-2003 ,"V5R11 SP1 ") // desactivation le 11-03-2003
CGMVersionMacroDefine(413 ,SurSurWithInits_ChooseSupportOfPLine                        ,SDP ,18-03-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(414 ,FilletCrvCrv_TwistDetection                                 ,PKC ,24-03-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(415 ,SurSurWithInits_RestrictedTangentSolve                      ,SDP ,24-03-2003 ,"V5R11 SP1 ")
CGMVersionMacroDefine(416 ,BodyExtremum_IntersectOnBodyIni                             ,ALV ,28-03-2003 ,"V5R11 SP1 ")


//=========================================================================================================
// V5R11 SP2
//=========================================================================================================
CGMVersionMacroDefine(420 ,RibbonHomotopy_StableOrientation                            ,FBZ ,14-03-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(421 ,Fillet_FaceFaceTwistedInitAccepted                          ,JMA ,14-03-2003 ,"V5R11 SP2 ")
//CGMVersionMacroDefine(422 ,SurSurWithInits_RestrictedTangentSolve                      ,SDP ,14-03-2003 ,"V5R11 SP2 ") // remontee V5R11 SP1
CGMVersionMacroDefine(423 ,Fill_PowerFillLevel6                                        ,MPS ,14-03-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(424 ,Project_NewDistanceComputation                              ,PBE ,14-03-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(425 ,Offset_BisectorOnWeaklySharpEdge                            ,DPS ,14-03-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(426 ,ThinSolid_Multiple_MergeEnds                                ,FDS ,17-03-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(427 ,Fill_LoopOrientation                                        ,MPS ,18-03-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(428 ,SmoothCurveLimitDeformation                                 ,NDN ,19-03-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(429 ,TwistAnalysis_MinimizeLevel1                                ,SDP ,21-03-2003 ,"V5R11 SP2 ")
//CGMVersionMacroDefine(430 ,FilletCrvCrv_TwistDetection                                 ,PKC ,21-03-2003 ,"V5R11 SP2 ") // remontee V5R11 SP1
CGMVersionMacroDefine(431 ,ConstantFillet_PointDeformQuality                           ,PKC ,21-03-2003 ,"V5R11 SP2 ")
//CGMVersionMacroDefine(432 ,BodyExtremum_IntersectOnBodyIni                             ,ALV ,24-03-2003 ,"V5R11 SP2 ") // remontee V5R11 SP1
CGMVersionMacroDefine(433 ,TopWire_Closure                                             ,JHN ,25-03-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(434 ,Rib_Relim_SpecSurSurWithInits                               ,FBZ ,28-03-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(435 ,Fillet_IgnoreSharpEdge                                      ,JHG ,28-03-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(436 ,Sweep_MultiDomainReport                                     ,NLD ,28-03-2003 ,"V5R11 SP2 ")
//CGMVersionMacroDefine(437 ,Rib_Relim_GestionInitExit                                   ,FBZ ,01-04-2003 ,"V5R11 SP2 ") // desactivation le 02-04-2003
CGMVersionMacroDefine(438 ,Bump_Level3                                                 ,PMG ,01-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(439 ,Parallel_ConfusedTwist                                      ,JHN ,01-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(440 ,Parallel_VertexOfDomain                                     ,JHN ,01-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(441 ,Parallel_DistanceOfExtremTwist                              ,JHN ,01-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(442 ,SmoothCurveMinArcLength                                     ,MMO ,01-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(443 ,Extrapol_FixedMaxGap                                        ,RHA ,01-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(444 ,Fillet_CleanInterpol                                        ,KLX ,04-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(445 ,Extrapol_CleanInterpol                                      ,KLX ,04-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(446 ,Fill_G2ComponentsAngles                                     ,MPS ,04-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(447 ,SurSurWithInits_SingularInitStableReconv                    ,SDP ,04-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(448 ,Fill_CleanComponents                                        ,MPS ,07-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(449 ,Extrude_StabilizeOrientation                                ,JHN ,08-04-2003 ,"V5R11 SP2 - Operateur Extremum ")
CGMVersionMacroDefine(450 ,DistanceMin_FaceFaceDist                                    ,JHN ,08-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(451 ,Revol_NewChecker_AxisOnProfil                               ,ALV ,11-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(452 ,Fillet_UseConfusedInit                                      ,RR  ,14-04-2003 ,"V5R11 SP2 - Use confused inits for multi solution problems (like sweep) ")
CGMVersionMacroDefine(453 ,Fillet_ImprovedUVSwitch                                     ,FDN ,14-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(454 ,Sweep_CorrectOrientation                                    ,FDN ,14-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(455 ,Healing_Level8                                              ,JJC ,14-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(456 ,Fill_PowerFillG2Improvements                                ,MPS ,14-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(457 ,CleanCurve_SmallArcs2                                       ,RNO ,15-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(458 ,ConstantFillet_CleanResults                                 ,FCX ,15-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(459 ,MostContinuous_RealTreatment                                ,HLN ,18-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(460 ,CGMJournal_Tass_A_B_Cr_A_and_A_Cr_C                         ,HCN ,18-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(461 ,Rib_Relim_GestionInitExit                                   ,FBZ ,18-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(462 ,Relim_JunctionEdgeFlagging                                  ,ASE ,22-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(463 ,Fillet_NupletCandPartToExport                               ,ASE ,23-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(464 ,SweepVaria_DeploySectionSolverData                          ,JSX ,25-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(465 ,Extrude_ByCircleStabilizePlaneOrientation                   ,ALV ,25-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(466 ,Offset_CheckUntouchedFaces                                  ,NBR ,28-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(467 ,Blend_CheckNormal                                           ,JSX ,28-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(468 ,Extrapol_G1_DiscontinuityThreshold                          ,JSX ,28-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(469 ,Connect_CleanInterpol                                       ,KLX ,28-04-2003 ,"V5R11 SP2 ")
CGMVersionMacroDefine(470 ,Extrapol_WeightedConstraintG1Deformation                    ,DPS ,30-04-2003 ,"V5R11 SP2 ")
//CGMVersionMacroDefine(471 ,Fillet_EndingShellForZeroRadiusBend                         ,JMA ,02-05-2003 ,"V5R11 SP2 ") // desactivation le 04-05-2003
CGMVersionMacroDefine(471 ,Fillet_EndingShellForZeroRadiusBend                         ,JMA ,06-05-2003 ,"V5R11 SP2 ") // réactivation le 06-05-2003


//=========================================================================================================
// V5R11 SP3
//=========================================================================================================
CGMVersionMacroDefine(480 ,Intersection_CheckStepAtBorder                              ,KLX ,12-05-2003 ,"V5R11 SP3 ")
CGMVersionMacroDefine(481 ,Homotopy_PointedSurface_CorrectNormal                       ,SDP ,13-05-2003 ,"V5R11 SP3 ")
CGMVersionMacroDefine(482 ,Offset_DuplicateUntouchedCellsInCreation                    ,DPS ,13-05-2003 ,"V5R11 SP3 ")
CGMVersionMacroDefine(483 ,Offset_LocalConfusionOptimisation                           ,DPS ,16-05-2003 ,"V5R11 SP3 ")
CGMVersionMacroDefine(484 ,Fill_NSidesCombs                                            ,NDN ,19-05-2003 ,"V5R11 SP3 ")
CGMVersionMacroDefine(485 ,TopWire_ClosureForAllEdges                                  ,AOV ,19-05-2003 ,"V5R11 SP3 ")
CGMVersionMacroDefine(486 ,Sweep_IntersectionSurSur_BetweenInits                       ,ALV ,20-05-2003 ,"V5R11 SP3 ")
CGMVersionMacroDefine(487 ,Offset_BisectorSurf_AdvancedSampling                        ,SDP ,20-05-2003 ,"V5R11 SP3 ")
CGMVersionMacroDefine(488 ,Fillet_SpecMatchingSkinRelimitation                         ,JHG ,03-06-2003 ,"V5R11 SP3 ")
CGMVersionMacroDefine(489 ,Fillet_SymetricGapMaxConnectCandidates                      ,JHG ,03-06-2003 ,"V5R11 SP3 ")
CGMVersionMacroDefine(490 ,New_PrismRevol_AutoIntersection_Check                       ,FDS ,03-06-2003 ,"V5R11 SP3 ")
//CGMVersionMacroDefine(491 ,DistanceMin_BoundaryOnFace                                  ,JHN ,06-06-2003 ,"V5R11 SP3 ") // desactivation le 16-06-2003
//CGMVersionMacroDefine(492 ,DistanceMin_BoundaryOnFace                                  ,JHN ,20-06-2003 ,"V5R11 SP3 ") // desactivation le 04-07-2003


//=========================================================================================================
// V5R11 SP4
//=========================================================================================================
CGMVersionMacroDefine(500 ,Offset_HealingExtrapolatedECrvWithGap                       ,DPS ,11-06-2003 ,"V5R11 SP4 ")
CGMVersionMacroDefine(501 ,MostContinuous_RealTreatment_2                              ,HLN ,11-06-2003 ,"V5R11 SP4 ")
CGMVersionMacroDefine(502 ,Sweep_CheckForSpineSmoothing2                               ,NDN ,13-06-2003 ,"V5R11 SP4 ")
CGMVersionMacroDefine(503 ,Rib_MultiSol_ReachExit                                      ,FBZ ,13-06-2003 ,"V5R11 SP4 ")
CGMVersionMacroDefine(504 ,Rib_ClearUnknownCandOnAllSupports                           ,FBZ ,13-06-2003 ,"V5R11 SP4 ")
CGMVersionMacroDefine(505 ,Fill_CalcArea                                               ,MPS ,20-06-2003 ,"V5R11 SP4 ")
CGMVersionMacroDefine(506 ,Parallel_GapEdgeCurve                                       ,JHN ,20-06-2003 ,"V5R11 SP4 ")
CGMVersionMacroDefine(507 ,CleanCurve_SmallCurves2                                     ,RNO ,20-06-2003 ,"V5R11 SP4 ")
CGMVersionMacroDefine(508 ,Sweep_NoSampling                                            ,JSX ,24-06-2003 ,"V5R11 SP4 ")
CGMVersionMacroDefine(509 ,Blend_Smooth                                                ,JSX ,24-06-2003 ,"V5R11 SP4 ")
CGMVersionMacroDefine(510 ,Blend_SweepShape                                            ,JSX ,24-06-2003 ,"V5R11 SP4 ")
CGMVersionMacroDefine(511 ,Fill_DegreeModification                                     ,MPS ,27-06-2003 ,"V5R11 SP4 ")
CGMVersionMacroDefine(512 ,ComputeUVTolerance_NewRun                                   ,STY ,27-06-2003 ,"V5R11 SP4 ")
CGMVersionMacroDefine(513 ,BorderWireClean_AllOperator                                 ,LAP ,30-06-2003 ,"V5R11 SP4 ")
CGMVersionMacroDefine(514 ,Join_Journal_AutoIntersectionEdges                          ,PBE ,30-06-2003 ,"V5R11 SP4 ")
CGMVersionMacroDefine(515 ,Ribbon_CollisionDetection                                   ,ASE ,30-06-2003 ,"V5R11 SP4 ")
CGMVersionMacroDefine(516 ,Parallel_KeepTwistForLaw                                    ,JHN ,04-07-2003 ,"V5R11 SP4 ")
CGMVersionMacroDefine(517 ,Rib_RCFWithParting                                          ,FBZ ,04-07-2003 ,"V5R11 SP4 ")
CGMVersionMacroDefine(518 ,DistanceMinCrvCrv_NewFuntionLnCrv                           ,STY ,04-07-2003 ,"V5R11 SP4 ")
CGMVersionMacroDefine(519 ,PCurve_MaxLimits_Simplification_Check                       ,FDS ,04-07-2003 ,"V5R11 SP4 ")
CGMVersionMacroDefine(520 ,RibSwe_NewInit                                              ,FDN ,07-07-2003 ,"V5R11 SP4 ")
CGMVersionMacroDefine(521 ,ThreePointsCircle                                           ,SRO ,09-07-2003 ,"V5R11 SP4 ")


//=========================================================================================================
// V5R12 SP1
//=========================================================================================================
CGMVersionMacroDefine(530 ,Healing_Level9                                              ,JEP ,18-07-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(531 ,Sweep_CombCleaner1                                          ,NDN ,18-07-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(532 ,Fillet_IsotopologicalInitEnhancement1                       ,JMA ,18-07-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(533 ,Fillet_ShellShellFullInInitSelection                        ,JHG ,18-07-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(534 ,Fillet_KeepEdgeInitCorrection                               ,JMA ,18-07-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(535 ,Fillet_RelimOnUntwistedTracks                               ,JMA ,21-07-2003 ,"V5R12 SP1 ")
//CGMVersionMacroDefine(536 ,ProjectionCrvSur_AdmissibleProj                             ,STY ,22-07-2003 ,"V5R12 SP1 ") // desactivation le 25-07-2003
CGMVersionMacroDefine(537 ,Project_Journal_Vertex2                                     ,PBE ,22-07-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(538 ,PowerDef_AddInfo                                            ,PMG ,25-07-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(539 ,Sweep_CheckForSpineSmoothing3                               ,NDN ,25-07-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(540 ,Sweep_SmoothNeeded                                          ,NDN ,25-07-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(541 ,SplitTrim_FullSmartDuplicate                                ,PBE ,25-07-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(542 ,Sweep_PlanesDetectionV2                                     ,NLD ,25-07-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(543 ,Sweep_BirailWithAnchorPoints_NoInversion                    ,NLD ,25-07-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(544 ,Extrapolation_EvoForMiddlePlane                             ,JSX ,29-07-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(545 ,Blend_UnifyCurveAndSurface                                  ,JSX ,29-07-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(546 ,Extrapol_PlanesDetection                                    ,JSX ,29-07-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(547 ,Fillet_TrimSupportCheckOutputValidity                       ,JHG ,29-07-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(548 ,Stable_Entropy_Intersection                                 ,RHA ,29-07-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(549 ,DraftBothSides_Constraints2                                 ,PFV ,29-07-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(550 ,Loft_ZScaling                                               ,NLD ,29-07-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(551 ,CleanCurve_InternalHighDef                                  ,RNO ,29-07-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(552 ,Fillet_ClosedRibOnSkin_RelimEnhancement                     ,JMA ,29-07-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(553 ,FilletKeepEdge_TwistLocalization                            ,PKC ,01-08-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(554 ,Rib_Relim_ActivateNonCompulsoryPropag                       ,ASE ,04-08-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(555 ,Parallel_ExtrapolWithGap                                    ,AOV ,08-08-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(556 ,Extrude_GeneratePlane                                       ,ALV ,08-08-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(557 ,Intersection_BorderSingularity                              ,KLX ,08-08-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(558 ,Sweep_CombNoNormalModeForPlane                              ,MNA ,11-08-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(559 ,CleanCurve_NewLengths                                       ,RNO ,11-08-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(560 ,Sweep_ReorderAndMergeTwistArea                              ,CCK ,13-08-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(561 ,Parallel_SinglePoint                                        ,KLX ,14-08-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(562 ,Extrapol_SmoothSpineForExtrapol1                            ,NDN ,19-08-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(563 ,PlanarTg_PlaneLineAngleOrigin                               ,AOV ,19-08-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(564 ,CleanCurve_CleanOneCurve                                    ,RNO ,22-08-2003 ,"V5R12 SP1 ")
CGMVersionMacroDefine(565 ,ProjectionCrvSur_AdmissibleProj                             ,STY ,22-08-2003 ,"V5R12 SP1 ")


//=========================================================================================================
// V5R12 SP2
//=========================================================================================================
CGMVersionMacroDefine(570 ,Offset_CollisionReverseSmoothEdgeOnClosedSurf               ,DPS ,05-09-2003 ,"V5R12 SP2 ")
CGMVersionMacroDefine(571 ,Extrapolation_ChooseSpineStartForClosedGuides               ,JSX ,09-09-2003 ,"V5R12 SP2 ")
CGMVersionMacroDefine(572 ,Sweep_PLineDetectionOnCanonicSurface                        ,JSX ,12-09-2003 ,"V5R12 SP2 ")
CGMVersionMacroDefine(573 ,CleanCurve_SmallCrvHisto                                    ,RNO ,12-09-2003 ,"V5R12 SP2 ")
CGMVersionMacroDefine(574 ,Fillet_NewInitialisationOfShiftedTracks_2                   ,RR  ,12-09-2003 ,"V5R12 SP2 ")
CGMVersionMacroDefine(575 ,Simplify_Fillets                                            ,FDS ,15-09-2003 ,"V5R12 SP2 ")
CGMVersionMacroDefine(576 ,EdgeCurveOffset_UseLimits                                   ,KLX ,15-09-2003 ,"V5R12 SP2 ")
CGMVersionMacroDefine(577 ,BlendRibbon_Hermetisation_2                                 ,FDN ,15-09-2003 ,"V5R12 SP2 ")
CGMVersionMacroDefine(578 ,Sweep_CorrectSignature                                      ,SOU ,15-09-2003 ,"V5R12 SP2 ")
CGMVersionMacroDefine(579 ,Extrapol_SmoothSpineForExtrapol2                            ,NDN ,16-09-2003 ,"V5R12 SP2 ")
CGMVersionMacroDefine(580 ,MaxOffset_ImprovedMinimize1D                                ,XGN ,19-09-2003 ,"V5R12 SP2 ")
CGMVersionMacroDefine(581 ,MarshMallow_Level2                                          ,PMG ,19-09-2003 ,"V5R12 SP2 ")
CGMVersionMacroDefine(582 ,CCVCleaner_SmallCurvesV2                                    ,NLD ,23-09-2003 ,"V5R12 SP2 ")
CGMVersionMacroDefine(583 ,VariableFilletInitSampling                                  ,PKC ,23-09-2003 ,"V5R12 SP2 ")
CGMVersionMacroDefine(584 ,Healing_Level10                                             ,JEP ,26-09-2003 ,"V5R12 SP2 ")


//=========================================================================================================
// V5R12 SP3
//=========================================================================================================
CGMVersionMacroDefine(590 ,SurSurWithInits_NewDeformation                              ,STY ,26-09-2003 ,"V5R12 SP3 ")
CGMVersionMacroDefine(591 ,Sweep_CleanGuidesParametersV5                               ,NLD ,26-09-2003 ,"V5R12 SP3 ")
CGMVersionMacroDefine(592 ,Rib_PropagSingleConfCandidate                               ,FDN ,29-09-2003 ,"V5R12 SP3 ")
CGMVersionMacroDefine(593 ,Fillet_FaceFaceFitRibLimitsToConfusedUpdate                 ,JHG ,29-09-2003 ,"V5R12 SP3 ")
CGMVersionMacroDefine(594 ,Fillet_MultiRibbonMichelinFix                               ,JHG ,29-09-2003 ,"V5R12 SP3 ")
CGMVersionMacroDefine(595 ,Fillet_PropagCoarseForTritangentOnSkin                      ,JMA ,03-10-2003 ,"V5R12 SP3 ")
CGMVersionMacroDefine(596 ,Offset_CheckPropagationAmbiguity                            ,NBR ,03-10-2003 ,"V5R12 SP3 ")
CGMVersionMacroDefine(597 ,Parallel_CutBySphere                                        ,JHN ,06-10-2003 ,"V5R12 SP3 ")
CGMVersionMacroDefine(598 ,Fillet_ForceUniqueConnexInPartSelection                     ,JHG ,07-10-2003 ,"V5R12 SP3 ")
CGMVersionMacroDefine(599 ,Parallel_CutByConstraint                                    ,PKC ,08-10-2003 ,"V5R12 SP3 ")
CGMVersionMacroDefine(600 ,OffsetVar_HealNormal                                        ,PMG ,10-10-2003 ,"V5R12 SP3 ")
CGMVersionMacroDefine(601 ,ReflectLine_Concatenation_Improvement                       ,ASE ,13-10-2003 ,"V5R12 SP3 ")
CGMVersionMacroDefine(602 ,Fillet_ShortExportOnSynchronousStop                         ,RR  ,13-10-2003 ,"V5R12 SP3 ")
CGMVersionMacroDefine(603 ,Parallel_ConstraintMgt                                      ,KLX ,14-10-2003 ,"V5R12 SP3 ")
CGMVersionMacroDefine(604 ,Fillet_TestOutputShellConnexity                             ,JHG ,14-10-2003 ,"V5R12 SP3 ")
CGMVersionMacroDefine(605 ,Offset_XSurSurTgWith2InitByPCGuide                          ,DPS ,14-10-2003 ,"V5R12 SP3 ")
CGMVersionMacroDefine(606 ,Fillet_KeepEdgeNewSearchForBumbers                          ,JMA ,14-10-2003 ,"V5R12 SP3 ")
CGMVersionMacroDefine(607 ,Canonic_Boundary_Intersection                               ,RHA ,14-10-2003 ,"V5R12 SP3 ")
CGMVersionMacroDefine(608 ,Extrapol_Linear_Trivial_MapX                                ,RHA ,17-10-2003 ,"V5R12 SP3 ")
CGMVersionMacroDefine(609 ,FilletSkinSkinNewEdgesForMax                                ,JMA ,17-10-2003 ,"V5R12 SP3 ")
CGMVersionMacroDefine(610 ,Sweep_TwistDetectionOnPseudoRationalProfiles                ,CCK ,21-10-2003 ,"V5R12 SP3 - RI ")
CGMVersionMacroDefine(611 ,StylingSweep_Report_01                                      ,MMO ,22-10-2003 ,"V5R12 SP3 ")
CGMVersionMacroDefine(612 ,Optimize_Open_Profile                                       ,FDS ,22-10-2003 ,"V5R12 SP3 ")
CGMVersionMacroDefine(613 ,Extrapol_SpecSurface_Level1                                 ,SDP ,23-10-2003 ,"V5R12 SP3 - Reecriture code d'extrapolation des bissectrices ") // Activation R12SP3 souhaitee pour RI DaimlerChrysler (voir DPS)
CGMVersionMacroDefine(614 ,Blend_NoFlatnessAtPeak                                      ,JSX ,28-10-2003 ,"V5R12 SP3 - RI Lockheed ") // -cr  397550 a b
CGMVersionMacroDefine(615 ,BisectorForBigEdgeGap                                       ,LAP ,28-10-2003 ,"V5R12 SP3 - Traiter toutes les aretes au dessus de 10 fois la resolution avec les bissectrices ")


//=========================================================================================================
// V5R12 SP4
//=========================================================================================================
CGMVersionMacroDefine(623 ,Rib_ValidRecursiveCompletion                                ,FBZ ,28-10-2003 ,"V5R12 SP4 ") // promote -cr 411316A  - livraison dans R12 SP4 uniquement.
CGMVersionMacroDefine(624 ,Parallel_EvalExplicit                                       ,KLX ,28-10-2003 ,"V5R12 SP4 - changement de geometrie ") // -cr 414474A
CGMVersionMacroDefine(625 ,Sweep_Conic_CheckLinearProfile                              ,JSX ,28-10-2003 ,"V5R12 SP4 - ri ") // -cr 404840 b c d
CGMVersionMacroDefine(626 ,Fillet_MaxRelimitationOnVertexLink                          ,JMA ,28-10-2003 ,"V5R12 SP4 - RI0375726 ")
CGMVersionMacroDefine(627 ,TopCleanLoop_CleanVers                                      ,RNO ,31-10-2003 ,"V5R12 SP4 - Amelioration Qualite et Performance de l'operateur CleanLoopOfFace ") // Deja validee sur FIXPARTVERS . OK
CGMVersionMacroDefine(628 ,CleanCurve_SmallArcsGeneralized                             ,RNO ,31-10-2003 ,"V5R12 SP4 - Correction pou RI0410137 ") // promote -cr A0410137
CGMVersionMacroDefine(629 ,Parallel_Journal_UnknownCells                               ,JHN ,07-11-2003 ,"V5R12 SP4 - journal parallele ") // ODT corrections
CGMVersionMacroDefine(630 ,MarshMallow_Level3                                          ,PMG ,07-11-2003 ,"V5R12 SP4 - Correction problemes Toyota ")
CGMVersionMacroDefine(631 ,Sweep_PlanesDetectionV3                                     ,NLD ,07-11-2003 ,"V5R12 SP4 ") // -cr 414314a 416512a
CGMVersionMacroDefine(632 ,Fillet_InnerTwist_OutsideEarlyExport                        ,RR  ,10-11-2003 ,"V5R12 SP4 - RI0410712 ") // promote -cr 410712
CGMVersionMacroDefine(633 ,Sweep_TwistDetection_DegeneratedPointe                      ,CCK ,07-11-2003 ,"V5R12 SP4 ")
CGMVersionMacroDefine(634 ,Fillet_JournalPartingAndKeepEdges                           ,AJD ,07-11-2003 ,"V5R12 SP4 ") // suivi par FDN
CGMVersionMacroDefine(635 ,Unfold_ShellOrientation                                     ,FDN ,07-11-2003 ,"V5R12 SP4 - orientation du shell resultat du unfold ")
CGMVersionMacroDefine(636 ,Bump_Level4                                                 ,PMG ,10-11-2003 ,"V5R12 SP4 - Paremetre de controle de forme toujours effectif ")
CGMVersionMacroDefine(637 ,Ribbon_RelimExtrapolationCombination                        ,JHG ,14-11-2003 ,"V5R12 SP4 - pour cloture RI ") // adl_promote -cr 413052B
CGMVersionMacroDefine(638 ,Parallel_NonCompleteSet                                     ,KLX ,17-11-2003 ,"V5R12 SP4 - reg Tolerant Mod. ")
CGMVersionMacroDefine(639 ,GeodesicParallel_ConfusedInit                               ,KLX ,17-11-2003 ,"V5R12 SP4 - RI 415185 ")
CGMVersionMacroDefine(640 ,Fillet_MaxRelimitationImprovement                           ,JMA ,17-11-2003 ,"V5R12 SP4 - RI 417643 ") // traiter les rubans fillet qui n'atteignent les bords libres de skin en 3 points d'extremite
CGMVersionMacroDefine(641 ,Fillet_FaceFaceMultiSolEnhancement                          ,JMA ,17-11-2003 ,"V5R12 SP4 - RI 407321A 407229A ") // amelioration de l'algo vrai multiruban dans fillet edge
CGMVersionMacroDefine(642 ,ReflectCurve_Pline                                          ,STY ,17-11-2003 ,"V5R12 SP4 - La correction du ri415656 entraine un bodiesMapping ds CGMTest_SurfacicTopReflectLineMultiSol2_Task1634_N1 ")
CGMVersionMacroDefine(643 ,Sweep_TwistDetectionWhenRational                            ,CCK ,21-11-2003 ,"V5R12 SP4 - pour RI 414154 ") // -cr A414154
CGMVersionMacroDefine(644 ,Sweep_CleanGuidesParametersV6                               ,NLD ,21-11-2003 ,"V5R12 SP4 ")
CGMVersionMacroDefine(645 ,Parallel_IntersectionInit                                   ,KLX ,27-11-2003 ,"V5R12 SP4 ")


//=========================================================================================================
// V5R12 SP5
//=========================================================================================================
CGMVersionMacroDefine(646 ,MultiplePartingFaces_Contact                                ,ASE ,28-11-2003 ,"V5R12 SP5 - changement de resultat (amelioration) apres activation ") // promote -cr 0417395A
CGMVersionMacroDefine(647 ,LayDown_Journal_SharedTopology                              ,ICE ,28-11-2003 ,"V5R12 SP5 - Mise a jour du journal en cas de partage de topologie ") // Ordre de destruction sur les cellules partagees dupliquees
CGMVersionMacroDefine(648 ,MathIntegrationInMassProperties1D                           ,AAD ,28-11-2003 ,"V5R12 SP5 ") // promote -cr 400249b 407372b
CGMVersionMacroDefine(649 ,Multiple_AutoIntersection_Check                             ,fds ,05-12-2003 ,"V5R12 SP5 - Correction du RI419647A ") // Gestion check auto intersection PAD et REVOL from surface
CGMVersionMacroDefine(650 ,Simplify_Edges_Advanced                                     ,FDS ,05-12-2003 ,"V5R12 SP5 ")
CGMVersionMacroDefine(651 ,Fill_Stabilize3DComb                                        ,NDN ,05-12-2003 ,"V5R12 SP5 ") // -cr  0418478A
CGMVersionMacroDefine(652 ,Sweep_TwistDetectionWhenRational1                           ,NDN ,05-12-2003 ,"V5R12 SP5 - Instabilite revelee par TwistDetectionWhenRational dams sweep629 ")
CGMVersionMacroDefine(653 ,Fillet_JournalInCaseOfTwistCorrection                       ,jma ,05-12-2003 ,"V5R12 SP5 - RI 419388 ")
CGMVersionMacroDefine(654 ,Rib_ConfusedVertexTrack_SetAsCutting                        ,rr  ,05-12-2003 ,"V5R12 SP5 - RI0420180 ") // promote -cr 420180B
CGMVersionMacroDefine(655 ,ProjectionCrvSur_Pline                                      ,STY ,05-12-2003 ,"V5R12 SP5 ")
CGMVersionMacroDefine(656 ,Parallel_RoundConfusion                                     ,jhn ,05-12-2003 ,"V5R12 SP5 - parallel michelin ") // correction
//CGMVersionMacroDefine(657 ,EdgeCurveSharpnessCut_Perfo                                 ,STY ,05-12-2003 ,"V5R12 SP5 ") // desactivation ls 15-01-2004
CGMVersionMacroDefine(658 ,AddRemoveDraftOnCylinder                                    ,ASE ,05-12-2003 ,"V5R12 SP5 - Draft adds or removes matter on cylinder with tilted pulling direction ") // To be activated in either R13SP1 or R12SP4
CGMVersionMacroDefine(659 ,Extrapol_NoCatchWithDirectionalEdges                        ,JSX ,05-12-2003 ,"V5R12 SP5 - Ri 416360a ") // promote -cr
CGMVersionMacroDefine(660 ,RollingEdge_InitializeConstraintSign2                       ,PKC ,08-12-2003 ,"V5R12 SP5 - comme son nom l'indique ") // idem
CGMVersionMacroDefine(661 ,EdgeCurveOffset_Level1                                      ,SDP ,12-12-2003 ,"V5R12 SP5 - New operator architecture ") // validation OK . a livrer le 12-12-2003
CGMVersionMacroDefine(662 ,Intersect_StabilizeOrientation3                             ,JBX ,15-12-2003 ,"V5R12 SP5 - Stabilisation l'orientation de l'IntersectShell si resultat ferme avec 2 edges. ") // -cr B0421573 C0421573
CGMVersionMacroDefine(663 ,Rib_Relim_PropagConfCand_MinDistMultipleFreeList            ,FBZ ,15-12-2003 ,"V5R12 SP5 - RI 415991 ") // -cr 415991A
CGMVersionMacroDefine(664 ,Spine_WhenOnlyPlanes                                        ,cck ,15-12-2003 ,"V5R12 SP5 - RI 425207 ") // promote -cr B0425207 C0425207
CGMVersionMacroDefine(665 ,Extremum_SetMargin                                          ,jhn ,15-12-2003 ,"V5R12 SP5 - RI operateur extremum ") // adl_promote -cr 406061A
CGMVersionMacroDefine(666 ,Offset_CGMInternalSharpAngle                                ,LAP ,15-12-2003 ,"V5R12 SP5 ")
CGMVersionMacroDefine(667 ,MarshMallow_Level4                                          ,PMG ,16-12-2003 ,"V5R12 SP5 - Nouvelles ameliorations + Correction d\'un RI ") // -cr A0420561
CGMVersionMacroDefine(668 ,ConstantFilletInit_NewRun                                   ,pkc ,17-12-2003 ,"V5R12 SP5 - RI toyota ") // optim perfo + fiabilisation + promote -cr 418771A
CGMVersionMacroDefine(669 ,Extrapol_UseSweepForUntilPlane                              ,jsx ,19-12-2003 ,"V5R12 SP5 - ri420656 ") // Promote -cr 420656 a Migration des cas UntilPlane sur le Sweep
CGMVersionMacroDefine(670 ,CATIdenticalSurSur_IsContaining_CATEpsg                     ,AAD ,19-12-2003 ,"V5R12 SP5 - RI 403271: changement du nombre de faces ") // -cr 403271b
//CGMVersionMacroDefine(671 ,ProjectionCrvSur_NewInit                                    ,sty ,19-12-2003 ,"V5R12 SP5 - Nouveau calcul d\'init pouvant destabiliser certaine projection ") // desactivation le 23-12-2003
CGMVersionMacroDefine(672 ,TriTangentFillet_ConnexInitSelection                        ,rr  ,22-12-2003 ,"V5R12 SP5 - RI0427531 ")
CGMVersionMacroDefine(673 ,VarOffset_CHECKNOUSE                                        ,PMG ,22-12-2003 ,"V5R12 SP5 - Correction problemes Toyota (RI0424430) ") // -cr 0424430A 0424430B
CGMVersionMacroDefine(674 ,ThinSolid_MergeEnds_WithConfusion                           ,fds ,22-12-2003 ,"V5R12 SP5 - Correction 425424A ") // Correction plusieurs RI sur le meme sujet
CGMVersionMacroDefine(675 ,Fillet_MinPropagCriteriumStabilization                      ,JHG ,22-12-2003 ,"V5R12 SP5 - Correction DUC ")
CGMVersionMacroDefine(676 ,HoldCurve_InfiniteRadiusInterpolation                       ,FCX ,22-12-2003 ,"V5R12 SP5 - RI 421794 : pb de parametrage du aux grandes valeurs de rayons ")
CGMVersionMacroDefine(677 ,Sweep_CleanGuidesParametersV7                               ,NLD ,06-01-2004 ,"V5R12 SP5 - Reduction de cellules dans clean du sweep si la compositelaw est c1 ")
CGMVersionMacroDefine(678 ,Thick_MinimizeMatterAroundVertex                            ,DPS ,07-01-2004 ,"V5R12 SP5 - optimisation du comportement des sommets a 4 aretes dans le Shell ") // RI TMC MUSTFIX 428998 A, B et C
CGMVersionMacroDefine(679 ,MissedProjection_NoJunctionStatus                           ,ice ,12-01-2004 ,"V5R12 SP5 - ne plus marquer Edge de bouchage les aretes trouvees par admissibilite dans la projection ")
CGMVersionMacroDefine(680 ,SupportSpline_JournalExtrem                                 ,jhn ,13-01-2003 ,"V5R12 SP5 - remettre d'equerre les extremites de spline sur support lorsqu\'elles sont sur une arete et donnent lieu a une confusion ") // RI MustFix 428308. remonter r12 et r13 ga/sp1


//=========================================================================================================
// V5R13 SP2
//=========================================================================================================
CGMVersionMacroDefine(700 ,ProjectionCrvSur_NewInit                                    ,sty ,12-01-2004 ,"V5R13 SP2 ")
CGMVersionMacroDefine(701 ,LayDown_AdmissibleWire                                      ,ICE ,12-01-2004 ,"V5R13 SP2 - Recherche d'un bord admissible avec le wire a poser ")
CGMVersionMacroDefine(702 ,SplitByPlane_SideVsShell                                    ,JBX ,12-01-2004 ,"V5R13 SP2 - Correction du calcul du cote specifie par l\'utilisateur ")
CGMVersionMacroDefine(703 ,Hole_LastRelimitation                                       ,fds ,13-01-2003 ,"V5R13 SP2 - RI418378 ") // Hole + Last + Exterieur matiere
CGMVersionMacroDefine(704 ,FilletKeepEdge_TwistLocalization2                           ,pkc ,13-01-2003 ,"V5R13 SP2 - pb JFR scenario boeing ")
CGMVersionMacroDefine(705 ,SurSurTg2                                                   ,SDP ,13-01-2003 ,"V5R13 SP2 - Evolution of the CATIntersectionSurSurTg operator ")
CGMVersionMacroDefine(706 ,Fillet_InitTransferAfterTwist                               ,rr  ,13-01-2003 ,"V5R13 SP2 - Performances ")
CGMVersionMacroDefine(707 ,Ribbon_FlatVertexOnParting                                  ,ase ,13-01-2003 ,"V5R13 SP2 - Flat vertex on parting element ") // RI 417398
CGMVersionMacroDefine(708 ,IntersectionSurSur_InterpolDomain                           ,KLX ,13-01-2003 ,"V5R13 SP2 - envoi du max domain a l\'interpol ")
CGMVersionMacroDefine(709 ,Offset_XSurTgPCGuideInSmoothContext                         ,DPS ,14-01-2004 ,"V5R13 SP2 - développement R14 Fading Edges ") // conditionner l\'appel au SurSur tangent avec multi-inits dont 1 Smooth
CGMVersionMacroDefine(710 ,PCurve_Limits_Simplification_Check                          ,fds ,16-01-2004 ,"V5R13 SP2 - RI410319A ") // 2e tentative mais cette fois c\'est la bonne !
CGMVersionMacroDefine(711 ,CATTangentSurSurSingular_NormalizeTol                       ,eab ,16-01-2004 ,"V5R13 SP2 - Fillet multi ")
CGMVersionMacroDefine(712 ,UnFoldedAero_Compensation                                   ,oau ,20-01-2004 ,"V5R13 SP2 - Versionnement de l operateur UnFoldeAero pour switcher sur une nouvelle compensation. ") // Pour RI  A0422581  Implement R14
CGMVersionMacroDefine(713 ,ThinSolid_WireHealer                                        ,fds ,20-01-2004 ,"V5R13 SP2 - Utilisation du healer de wire par Thin Solid ")
CGMVersionMacroDefine(714 ,IntersectionSurSur_CheckSegment                             ,klx ,20-01-2004 ,"V5R13 SP2 - cheminement ")
CGMVersionMacroDefine(715 ,Parallel_ComputeInitFace                                    ,AOV ,20-01-2004 ,"V5R13 SP2 - utilisation autre methode pour calcul face init ") // RI416432 &429717
CGMVersionMacroDefine(716 ,ApproxCurve_CheckPCurveWithinSupport                        ,AAD ,20-01-2004 ,"V5R13 SP2 - correction CGMTest_SurfacicSurToNurbsSur_Case2_Task1054_N1 (KO avec PSS_1) ")
CGMVersionMacroDefine(717 ,OffsetVar_AutoTrim                                          ,PMG ,20-01-2004 ,"V5R13 SP2 - Limitation des Faces intersectantes comme dans l\'offset constant. ") // 0423707A
CGMVersionMacroDefine(718 ,ImplicitSpine_OrnTgWireLayOn                                ,CCK ,20-01-2004 ,"V5R13 SP2 - pour Ri 429078 ") // faire un promote -cr A0429078
//CGMVersionMacroDefine(719 ,Fillet_EdgesJournalingForMultiRibbonCorrections             ,JMA ,23-01-2004 ,"V5R13 SP2 - Correction du Drop BOEING2126 ") // desactivee le 27-01-2004 dans fixpartvers
CGMVersionMacroDefine(720 ,Healing_Level11                                             ,JEP ,23-01-2004 ,"V5R13 SP2 - Verification degradation de tangence. Cas PSA ")
CGMVersionMacroDefine(721 ,Sweep_CheckSurfaceParametrization_VDirection                ,JSX ,23-01-2004 ,"V5R13 SP2 - Surface sweep mal parametree en V (10 ") // promote -cr 427430a
CGMVersionMacroDefine(722 ,SearchPointOnFace_EdgeCurveIterator                         ,ALV ,23-01-2004 ,"V5R13 SP2 - L\'iterateur d\'EdgeCurve ne fonctionne pas, à cause d\'un mauvais appel. ")
CGMVersionMacroDefine(723 ,Corner_TriTangent_CircleTriRelation                         ,ALV ,23-01-2004 ,"V5R13 SP2 - Utilisation d\'un seul opérateur géométrique dans le corner Tritangent (CATCircleTriRelation). ")
CGMVersionMacroDefine(724 ,VariableFillet_MarchingSagDefinition                        ,PKC ,23-01-2003 ,"V5R13 SP2 - RI 0429641A ") // promote -cr 429641A, si si j\'insiste, cette fois ca devrait etre OK
CGMVersionMacroDefine(725 ,UnFoldedAero_Discretisation                                 ,OAU ,26-01-2004 ,"V5R13 SP2 - Suppression de doublon de points de Discretisation ") // Pour RI 0413025
CGMVersionMacroDefine(726 ,IntersectionWithInits_EndPointsTangent                      ,KLX ,26-01-2004 ,"V5R13 SP2 - RI427605 DUC BMW PRISMA_0002971085 ") // -cr 427605A 427605B
CGMVersionMacroDefine(727 ,IntersectionSurSurWithInits_AcceptableTol                   ,klx ,26-01-2004 ,"V5R13 SP2 - Action PCurveOutOfSupport + FatEdge ")
CGMVersionMacroDefine(728 ,SimilarCrv_TolLengthCrv                                     ,CCK ,27-01-2004 ,"V5R13 SP2 - pour Ri 431212 ") // promote -cr A0431212 B0431212
CGMVersionMacroDefine(729 ,ProjectionCrvSur_NewStretch                                 ,sty ,27-01-2004 ,"V5R13 SP2 - Ri 418560 ")
CGMVersionMacroDefine(730 ,ExtandSurLimits_OrderOfExtrapol                             ,FBZ ,27-01-2004 ,"V5R13 SP2 - RI430937 ") // -cr 430937A 430937B
CGMVersionMacroDefine(731 ,Open_Profile_One_Offset_Optimisation                        ,fds ,27-01-2004 ,"V5R13 SP2 - Optimisation + correction ")
CGMVersionMacroDefine(732 ,TopCleanCurve_G0Check                                       ,RNO ,27-01-2004 ,"V5R13 SP2 - JunctionEdge ... ") // Raise an error when output G0Gap is bigger than input G0Gap
CGMVersionMacroDefine(733 ,Offset_NumericalFilterForPlans                              ,LAP ,30-01-2004 ,"V5R13 SP2 ")
CGMVersionMacroDefine(734 ,Rib_Relim_FreezeCoveredFacesCandidate                       ,FBZ ,03-02-2004 ,"V5R13 SP2 - RI431324 ") // -cr 431324B 431324C
//CGMVersionMacroDefine(735 ,VariableFillet_MarchingLevel4                               ,klx ,06-02-2004 ,"V5R13 SP2 - reg NewTopoRIVariableFilletEdge3 suite a nouvelle sag ") // pb concurrence contrainte / singularite . debranchee le 10-02-2004
CGMVersionMacroDefine(736 ,Parallel_InputClean                                         ,JHN ,06-02-2004 ,"V5R13 SP2 - activation nouveau parallele ")
CGMVersionMacroDefine(737 ,SplitWire_KeepSignOnSmoothEdges                             ,ice ,06-02-2004 ,"V5R13 SP2 ") // Conservation du signe d\'intersection sur les points relimites sur edge morte
CGMVersionMacroDefine(738 ,Sweep_ThinFacesElimination                                  ,NLD ,06-02-2004 ,"V5R13 SP2 - Elimination des faces fines dans le sweep ")
CGMVersionMacroDefine(739 ,Corner_Indexation_BadCornerOrientation                      ,ALV ,06-02-2004 ,"V5R13 SP2 - ri0427625 pb d\'orientation entre l\'edge et le wire du corner non prise en compte ")
CGMVersionMacroDefine(740 ,UnFoldedAero_ShellExtrapolation                             ,OAU ,06-02-2004 ,"V5R13 SP2 - Versionnement de l operateur UnFoldeAero afin d extrapoler si necessaire les Shells Supports ") // Pour RI 0429293
//CGMVersionMacroDefine(741 ,Fillet_EdgesJournalingForMultiRibbonCorrections             ,JMA ,06-02-2004 ,"V5R13 SP2 - Correction du Drop BOEING2126 ")
CGMVersionMacroDefine(742 ,Prism_LastLast_Relimitation                                 ,fds ,09-02-2004 ,"V5R13 SP2 - RI429198A ")
CGMVersionMacroDefine(743 ,CloneAndMovePCurve_SameParameterisation                     ,AAD ,09-02-2004 ,"V5R13 SP2 - Correction ODT TestThicken (KO avec set CATCylinderCGM_NonIsoparametricOffset=1) ")
CGMVersionMacroDefine(744 ,LinearTangent_NormalComputation                             ,jhn ,09-02-2004 ,"V5R13 SP2 - RI MNT ") // adl_promote -cr 431939A 431939B
CGMVersionMacroDefine(745 ,Loft_UseIntermediateProfileForSharpEdgeReport               ,NLD ,09-02-2004 ,"V5R13 SP2 ")
CGMVersionMacroDefine(746 ,TopCleanCurve_JournalDeletionAndTass                        ,HLN ,09-02-2004 ,"V5R13 SP2 - Fournir un Journal ne contenant que l\'essentiel : suppression des items intermediaires ") // Suite a demande et prototypage de SUH
CGMVersionMacroDefine(747 ,Projection_BooleanStabilization                             ,ICE ,09-02-2004 ,"V5R13 SP2 - Branchement de la stabilisation booleenne dans la projection ")
CGMVersionMacroDefine(748 ,CGM_Versionning_MarshMallow_Stabilize                       ,PMG ,13-02-2004 ,"V5R13 SP2 - RI A0429773 ") // Pas de -cr (RI clos en sug)
CGMVersionMacroDefine(749 ,DevelopWire_FindSupportFaceFromLyingOn                      ,jhg ,17-02-2004 ,"V5R13 SP2 - RI Close List Michelin ") // promote -cr 431852


//=========================================================================================================
// V5R13 SP3
//=========================================================================================================
CGMVersionMacroDefine(780 ,Rib_Relim_CouplingNewStep                                   ,FBZ ,20-02-2004 ,"V5R13 SP3 - RI430930 ")
CGMVersionMacroDefine(781 ,CleanCurve_SmallOverConstrained                             ,rno ,20-02-2004 ,"V5R13 SP3 - RI C0421586,A0421586 BMW DUC + parallele correction small ") // Rebelote
CGMVersionMacroDefine(782 ,Fillet_EdgesJournalingForMultiRibbonCorrections             ,JMA ,23-02-2004 ,"V5R13 SP3 - Correction du Drop BOEING2126 ")
CGMVersionMacroDefine(783 ,Draft_ManageDisconnectResult                                ,FBZ ,23-02-2004 ,"V5R13 SP3 - RI432061 ") // -cr 432061A
CGMVersionMacroDefine(784 ,Chamfer_MultiRubanCorrections                               ,jma ,23-02-2004 ,"V5R13 SP3 - RI 406400 ")
CGMVersionMacroDefine(785 ,UnFoldedAero_OrientationAfterProjection                     ,oau ,23-02-2004 ,"V5R13 SP3 - Remise d equerre des Orientations Cellules apres projection Topo ") // RI  0431646A
CGMVersionMacroDefine(786 ,LinearNormal_TwoPointsError                                 ,jhn ,23-02-2004 ,"V5R13 SP3 - RI MNT ") // adl_promote -cr 434513A
CGMVersionMacroDefine(787 ,VariableFillet_MarchingLevel4                               ,klx ,23-02-2004 ,"V5R13 SP3 - reg NewTopoRIVariableFilletEdge3 suite a nouvelle sag ") // pb concurrence contrainte / singularite
CGMVersionMacroDefine(788 ,PointOnCurve_Off_Curve                                      ,jhn ,23-02-2004 ,"V5R13 SP3 - RI mnt ") // adl_promote -cr 433790A
CGMVersionMacroDefine(789 ,RibSweep_MarchingConstraint                                 ,AJD ,23-02-2004 ,"V5R13 SP3 - tolerant modeling pour sweep ") // promote -cr 416187A 420311A
CGMVersionMacroDefine(790 ,RibSweep_SupportExtrapolation                               ,FDL ,23-02-2004 ,"V5R13 SP3 - Extraoplation support pour hermetization. ") // promote -cr 416187A 420311A
CGMVersionMacroDefine(791 ,RibSweep_FilterDegenSol                                     ,PKC ,23-02-2004 ,"V5R13 SP3 - RI sweep ") // promote -cr 416187A 420311A
CGMVersionMacroDefine(792 ,DrftRlmInit_UseBoxUVFace_BetterSelectionOfFaces             ,fbz ,01-03-2004 ,"V5R13 SP3 ")
CGMVersionMacroDefine(793 ,Shell_BooleanPosVolOptim                                    ,dps ,01-03-2004 ,"V5R13 SP3 - migration vers un positionnement face ") // le versionning est motive par un changement de comportement en cas d\'operandes invalides
CGMVersionMacroDefine(794 ,ApproxCurve_InputPCurveGap                                  ,AAD ,01-03-2004 ,"V5R13 SP3 - Correction bug ")
CGMVersionMacroDefine(795 ,Corner_CenterOnPt_GoodOrient                                ,ALV ,01-03-2004 ,"V5R13 SP3 - Stabilisation des orientations dans le calcul des corners centrés sur point ") // RIB0435156 et RIA0435156
CGMVersionMacroDefine(796 ,Fillet_PlanarRelimitationOnAnySurface                       ,rr  ,01-03-2004 ,"V5R13 SP3 - Fillet ACA ")
CGMVersionMacroDefine(797 ,EdgeCurveSharpnessCut_Perfo                                 ,STY ,05-03-2004 ,"V5R13 SP3 ")
CGMVersionMacroDefine(798 ,PowerDef_ApplyOnTabulatedCylinder                           ,PMG ,05-03-2004 ,"V5R13 SP3 - RIA0436103 ") // -cr A0436103
CGMVersionMacroDefine(799 ,Fillet_CorrectionsForClosedRibbon                           ,jma ,08-03-2004 ,"V5R13 SP3 - RI0434299 ") // -cr B0434299 C0434299
CGMVersionMacroDefine(800 ,Sweep_DeploySoftwareConfigurationV3                         ,JSX ,08-03-2004 ,"V5R13 SP3 - versioning du cleanCurve des spines implicites ")
CGMVersionMacroDefine(801 ,Sweep_ViewingDirection_PlaneDetection                       ,NLD ,08-03-2004 ,"V5R13 SP3 - affiner la detection de plan pour cas faiblement c0 ")
CGMVersionMacroDefine(802 ,Helix_TaperAngle                                            ,jhn ,08-03-2004 ,"V5R13 SP3 - RI 435947 ") // adl_promote -cr 435947A
CGMVersionMacroDefine(803 ,ComputeUVTolerance_Cylinder                                 ,pkc ,08-03-2004 ,"V5R13 SP3 - traitement canonique des cylindres ") // code livre le 06/03 dans OFF
CGMVersionMacroDefine(804 ,FatEdgeFixed                                                ,FBZ ,12-03-2004 ,"V5R13 SP3 - Fat Edge ") // demandé par RR
CGMVersionMacroDefine(805 ,CleanCurve_C1Hybride                                        ,RNO ,12-03-2004 ,"V5R13 SP3 - Pour le C1 dans le cleancurve en mode  Hybride (pour les sweep) ") // Si les ODT CGMTest_SurfacicSweep59 et CGMTest_SurfacicSweep60 sont KO=1 cf JSX
CGMVersionMacroDefine(806 ,Sweep_MonoProfilLoftWithTangent                             ,JSX ,15-03-2004 ,"V5R13 SP3 - Prendre en compte l\'otirentation de la spine ") // Pour l\'autoLoft
CGMVersionMacroDefine(807 ,Pad_NextLimit_After_InvalidLimit                            ,fds ,15-03-2004 ,"V5R13 SP3 - RI439731A ")
CGMVersionMacroDefine(808 ,Extrapol_NoAntiClosure                                      ,DPS ,19-03-2004 ,"V5R13 SP3 - subdivision indesirable de faces sur les surfaces fermees ") // demande provenant du Draft pour une extrapolation de skin en interne.
CGMVersionMacroDefine(809 ,Offset_OptimIsoSharpBorderVRep                              ,dps ,19-03-2004 ,"V5R13 SP3 - minimisation du nombre de micro faces et micro edges ") // optimisation du resultat du RI MNT 440093 TMC
CGMVersionMacroDefine(810 ,Fill_PowerFillLevel8                                        ,MPS ,22-03-2004 ,"V5R13 SP3 - correction du RI  439503 ")
CGMVersionMacroDefine(811 ,Offset_BisectorSurf_NonIsoParam                             ,oau ,22-03-2004 ,"V5R13 SP3 - Ajout d un coef Lambda dans CATSpecBissectorSurfaceDef afin de casser l IsoParam des surfaces Bisectrices. ") // MicroFillet SheetMetal  RIs 0416030 0396770 0431328 0429933 0422581 0402685 0415680
//CGMVersionMacroDefine(812 ,Offset_CylinderCGM_NonIsoParam                              ,oau ,22-03-2004 ,"V5R13 SP3 - Versionnement de l Offset NonIsoParam des Cylindres ") // MicroFillet SheetMetal  RIs 0416030 0396770 0431328 0429933 0422581 0402685 0415680
CGMVersionMacroDefine(813 ,Thick_NoManifoldEdgeForbidden                               ,dps ,23-03-2004 ,"V5R13 SP3 - interdire la config NonManifold pour une meilleure selection volumique ") // adl_promote -cr 441869A      (RI MNT)
CGMVersionMacroDefine(814 ,IntersectWireShell_Stabilization                            ,ice ,23-03-2004 ,"V5R13 SP3 - Stabilisation des resultats de l\'intersect Wires/Shells ") // adl_promote -cr 442459B 442459C
CGMVersionMacroDefine(815 ,Desextrapolation_3DTol                                      ,aad ,23-03-2004 ,"V5R13 SP3 - Tolerance 3D pour determiner les limites de la desextrapolation ") // -cr 434572a
CGMVersionMacroDefine(816 ,IntersectionWithInits_EndPointsMustBeNull                   ,klx ,26-03-2004 ,"V5R13 SP3 - RI 441507 ") // promote -cr 441507A
CGMVersionMacroDefine(817 ,ImplicitSpine_NoFormOptimizIfOnlyPlanes                     ,CCK ,29-03-2004 ,"V5R13 SP3 - Ri442697 ") // promote -cr B0442697 C0442697
CGMVersionMacroDefine(818 ,SmartTouchManagement                                        ,fdn ,29-03-2004 ,"V5R13 SP3 - Suppression des touch inutiles apres SmartDuplicate ")
//CGMVersionMacroDefine(819 ,IntersectionSurSur_InterpolMaxDepth                         ,klx ,29-03-2004 ,"V5R13 SP3 - Cleaner ICG ") // debranché le 31-03-2004
CGMVersionMacroDefine(820 ,DraftRibbonInit_NonConnected                                ,PFV ,29-03-2004 ,"V5R13 SP3 - RI0439950 ")
CGMVersionMacroDefine(821 ,Rib_Relim_DeactivateComplFaceCheck                          ,ase ,29-03-2004 ,"V5R13 SP3 - Performance improvement, check is not used in current test base ") // Performance improvement, check is not used in current test base

//=========================================================================================================
// V5R13 SP4
//=========================================================================================================
CGMVersionMacroDefine(840 ,Thick_RemoveFaceLevel2                                      ,DPS ,02-04-2004 ,"V5R13 SP4 - traitements RemoveFace pour le calcul de longueur d\'extrapolation en cas complexe ") // adl_promote -cr 0420119A 0428973A 0428969A
CGMVersionMacroDefine(841 ,UnFoldedAero_ConnectVertex                                  ,OAU ,02-04-2004 ,"V5R13 SP4 - RI 0442488A  CAT514IN ") // Traitement du Point de connexion au cours de la Tranfo
CGMVersionMacroDefine(842 ,CloseOperator_Face_Intersection                             ,fds ,05-04-2004 ,"V5R13 SP4 - Dev. TOYOTA + RI 440845A ")
CGMVersionMacroDefine(843 ,MarshMallow_Level5                                          ,PMG ,05-04-2004 ,"V5R13 SP4 - Nouvelles ameliorations de l\'algo ")
CGMVersionMacroDefine(844 ,Pad_Until_Directionnel                                      ,fds ,09-04-2004 ,"V5R13 SP4 - RI425870 + demande Ferrari , PAD avec offset + until orientable dans tous les cas ")
CGMVersionMacroDefine(845 ,VarOffset_TrimWithExtrapol                                  ,PMG ,09-04-2004 ,"V5R13 SP4 ") // Augmenter le taux de succes du trim.
CGMVersionMacroDefine(846 ,Parallel_ZStabilization                                     ,AOV ,09-04-2004 ,"V5R13 SP4 - correction KO michelin ") // stabilisation traitement du Z
//CGMVersionMacroDefine(847 ,Loft_NewSectionDeformWithSimilarComputation                 ,MNA ,09-04-2004 ,"V5R13 SP4 - Pour integrer une nouvelle methodo de calcul des sections G1 dans le Loft ") // desactivee le 19-04-2004
CGMVersionMacroDefine(848 ,Offset_CylinderCGM_NonIsoParam                              ,oau ,09-04-2004 ,"V5R13 SP4 - Versionnement de l Offset NonIsoParam des Cylindres. ") // MicroFillet SheetMetal  RIs 0416030 0396770 0431328 0429933 0422581 0402685 0415680
CGMVersionMacroDefine(849 ,Healing_AdjustAllPCurveG1                                   ,JJC ,09-04-2004 ,"V5R13 SP4 - Ajustement des frontieres en tangence ")
//CGMVersionMacroDefine(850 ,Fillet_WithParting_JournalCorrection                        ,jma ,16-04-2004 ,"V5R13 SP4 - RI0444167 ") // desactivé le 19-04-2004
CGMVersionMacroDefine(851 ,Sweep_IntersectionCoupling_LengthParametrization            ,JSX ,16-04-2004 ,"V5R13 SP4 - homogeneite des coordonnées du systemes de creation du mapping du couplin d\\\'intersection ") // -cr ri 443160 A et B
//CGMVersionMacroDefine(852 ,Sweep_CombCleaner3                                          ,NDN ,16-04-2004 ,"V5R13 SP4 - Stabilite CleanCurve ") // Pour decoupler le smooth de la spine . debranche le 20-04-2004
CGMVersionMacroDefine(853 ,Linear_SupportOrthogonality2                                ,jhn ,19-04-2004 ,"V5R13 SP4 - RI ") // adl_promote -cr 445422A
CGMVersionMacroDefine(854 ,IntersectionSurSur_InterpolMaxDepth                         ,klx ,19-04-2004 ,"V5R13 SP4 - Cleaner ICG ")
CGMVersionMacroDefine(855 ,CornerPtPCrv_PtOnCrv                                        ,klx ,20-04-2004 ,"V5R13 SP4 - RI 446819 ") // -cr 446819A 446819B
CGMVersionMacroDefine(856 ,Parallel_SolveByProjection                                  ,klx ,20-04-2004 ,"V5R13 SP4 - RI 446765 parallel with a null law ") // -cr 446765A 446765B 446765C
CGMVersionMacroDefine(857 ,TopCleanCurve_CheckDescendance                              ,RNO ,23-04-2004 ,"V5R13 SP4 - Bug potentiel dans le journal ")
CGMVersionMacroDefine(858 ,Fillet_FlatTwist                                            ,JHG ,23-04-2004 ,"V5R13 SP4 - RI0446007 ") // promote -cr 446007
CGMVersionMacroDefine(859 ,Fillet_PointingDeformationPowerFill                         ,FCX ,23-04-2004 ,"V5R13 SP4 - qualite et stabilite des fillets en pointes (plusieurs RI clos SUG a ce sujet) ")
CGMVersionMacroDefine(860 ,ChordalFillet_TwistDetection                                ,PKC ,23-04-2004 ,"V5R13 SP4 - dev ")
CGMVersionMacroDefine(861 ,Fillet_LocalInnerTwist_NewParabola                          ,cck ,26-04-2004 ,"V5R13 SP4 - pour permettre activation de la nouvelle detection de twist dans le fillet ")
CGMVersionMacroDefine(862 ,RibSweep_CorrectSignature                                   ,FDL ,26-04-2004 ,"V5R13 SP4 - Rib Sweep Orientation ") // adl_promote -cr A0443910
CGMVersionMacroDefine(863 ,ProjectionCrvSur_NewInitComputation                         ,sty ,26-04-2004 ,"V5R13 SP4 - RI447032 ")
CGMVersionMacroDefine(864 ,Loft_NewSectionDeformWithSimilarComputation                 ,MNA ,26-04-2004 ,"V5R13 SP4 - Pour integrer une nouvelle methodo de calcul des sections G1 dans le Loft ")
CGMVersionMacroDefine(865 ,ProjectionPtCrv_DirAdvanced                                 ,sty ,30-04-2004 ,"V5R13 SP4 - RI 447188 ")
CGMVersionMacroDefine(866 ,IntersectionCrvCrv_CircleCircleOFF                          ,sty ,30-04-2004 ,"V5R13 SP4 - RI MNT P1 CAA ")
CGMVersionMacroDefine(867 ,TriTangentPCrv_ValidateRoot                                 ,pkc ,30-04-2004 ,"V5R13 SP4 - RI 447380 ") // 447380A
CGMVersionMacroDefine(868 ,Fillet_WithParting_JournalCorrection                        ,jma ,30-04-2004 ,"V5R13 SP4 - RI0444167 ")
CGMVersionMacroDefine(869 ,Fillet_MultiRibbonClosedRlmRibFix                           ,JHG ,30-04-2004 ,"V5R13 SP4 - mustfix reg ") // -cr 445900A
CGMVersionMacroDefine(870 ,JoinForRegularize_MergeEdgesWithGap                         ,jbx ,30-04-2004 ,"V5R13 SP4 - ri446779 ") // promote -cr B0446779  A0446779
CGMVersionMacroDefine(871 ,SurSurResultCurve_ApproxCurve                               ,EAB ,30-04-2004 ,"V5R13 SP4 - RI 448283 ") // promote -cr A0448283 B0448283
CGMVersionMacroDefine(872 ,CombUsingCCVOrn                                             ,NDN ,30-04-2004 ,"V5R13 SP4 - RI 0443681A ")
CGMVersionMacroDefine(873 ,ImplicitSpine_OneProfile                                    ,cck ,30-04-2004 ,"V5R13 SP4 - RI reg ") // activation immediate . promote -cr 448818
CGMVersionMacroDefine(874 ,Offset_LinearBoundaryEdgeForDegenRescue                     ,LAP ,03-05-2004 ,"V5R13 SP4 - RI 444432 MNT ") // promote -cr 444432A, generation d\'edges lineaires sur les bords en cas de degenerescence de surfaces
CGMVersionMacroDefine(875 ,VariableDraft_SymmetricalClosedLaw                          ,PFV ,03-05-2004 ,"V5R13 SP4 - RI0435306 ") // Pour se premunir d\'une rupture de symetrie en cas de ruban Draft variable ferme
CGMVersionMacroDefine(876 ,Sweep_Interpol_AnalyseInputSegmentation                     ,JSX ,03-05-2004 ,"V5R13 SP4 - Check de l\'interpolation aux parametres correspondants aux arcs des inputs ") // -cr  a 446695
CGMVersionMacroDefine(877 ,SweepDraft_ControlDraftAngle                                ,NLD ,03-05-2004 ,"V5R13 SP4 ") // controle de la validite de l\'angle de depouille
//CGMVersionMacroDefine(878 ,CleanCurve_ActiveSplitByApprox                              ,RNO ,03-05-2004 ,"V5R13 SP4 - Manage very small arcs on input ") // RI CD A0444845  Note: ODT GSMCurveSmoothExtrem06 KO (mais OK en manuel pour moi)
CGMVersionMacroDefine(879 ,TopCleanCurve_ConsecutiveFillEdges                          ,HLN ,03-05-2004 ,"V5R13 SP4 - Traitement des aretes de bouchage consecutives ") // Suite a demande et a modele de FDL
CGMVersionMacroDefine(880 ,Rib_Relim_IsCoveredOnSmoothEdge                             ,FBZ ,04-05-2004 ,"V5R13 SP4 - RI 447892 ") // -cr 447892A
CGMVersionMacroDefine(881 ,SplineOnSupport_Relimitation                                ,jhn ,04-05-2004 ,"V5R13 SP4 - bug RIs externes ") // adl_promote -cr 447958A 447958B 448545A
CGMVersionMacroDefine(882 ,Rib_Relim_PropagDirectionOnSmoothExtrapolationVertex        ,FBZ ,05-05-2004 ,"V5R13 SP4 - RI 449490 ") // activation immédiate
CGMVersionMacroDefine(883 ,Fillet_WithParting_JournalCorrectionForFreeBorderEdges      ,JMA ,10-05-2004 ,"V5R13 SP4 - RI0414254 ") // -cr 414254A
CGMVersionMacroDefine(884 ,Fillet_MultiSolutionsWithConfusedTraces                     ,JMA ,10-05-2004 ,"V5R13 SP4 - RI0446781 ") // -cr 446781A 446781B


//=========================================================================================================
// V5R13 SP5
//=========================================================================================================
CGMVersionMacroDefine(885 ,CleanCurve_MinimalTolForCCVCleaner                          ,RNO ,12-05-2004 ,"V5R13 SP5 - Correction de quelques RIs Renault + Tolerant Modeling ")
CGMVersionMacroDefine(886 ,Offset_AllowOneDirectionalSurfaceForCloseSurface            ,LAP ,14-05-2004 ,"V5R13 SP5 - RI448220 ") // adl_promote -cr 448220A
CGMVersionMacroDefine(887 ,Extrapol_G1DeformationOnlyIfSharpTangentAngle               ,DPS ,14-05-2004 ,"V5R13 SP5 - Tolerant Modeling dans l\'Extrapolation de surface en courbure ") // adl_promote -cr 412584A (Renault)
CGMVersionMacroDefine(888 ,Rib_PropagCoarseEnhancement_OutsideNeutralDraft             ,ase ,17-05-2004 ,"V5R13 SP5 - RI 0445201 ") // Correction + evolution, adl_promote -cr 0445201A
CGMVersionMacroDefine(889 ,Sweep_UntwistOrientationManagement                          ,NLD ,18-05-2004 ,"V5R13 SP5 ")
CGMVersionMacroDefine(890 ,Sweep_ViewingDirection_PipeV4_V3                            ,NLD ,18-05-2004 ,"V5R13 SP5 ") // -cr 449804a
CGMVersionMacroDefine(891 ,CleanFatEdgesOnPartingBorder                                ,ASE ,18-05-2004 ,"V5R13 SP5 - Toyota fillet case ") // Fat Edge (du au limiting/parting element) non nettoyee
//CGMVersionMacroDefine(892 ,Loft_NewShapeWithNoRelimit                                  ,NDN ,24-05-2004 ,"V5R13 SP5 ")
CGMVersionMacroDefine(893 ,ReflectDraft_HeightLimitationFromRibbon                     ,PFV ,24-05-2004 ,"V5R13 SP5 - RI0448694 ")
CGMVersionMacroDefine(894 ,Fillet_RelimitationMinOnUntwistedTracks                     ,JMA ,24-05-2004 ,"V5R13 SP5 - RI0449503 ")
CGMVersionMacroDefine(895 ,Thick_RemoveFaceLevel3                                      ,MNJ ,24-05-2004 ,"V5R13 SP5 - RI MustFix ") // adl_promote -cr A0449828 A0451870
//CGMVersionMacroDefine(896 ,CATCurveToCanonic_NewCircle                                 ,STY ,24-05-2004 ,"V5R13 SP5 - RI ")
CGMVersionMacroDefine(897 ,CleanCurve_ForceFittingOnSmallConcat                        ,RNO ,28-05-2004 ,"V5R13 SP5 - CATCGMCleanerRules Fitting ne fait pas d\'approx ")
//CGMVersionMacroDefine(898 ,Projection_LogPointSolutions                                ,ice ,28-05-2004 ,"V5R13 SP5 ") // Suivi des solutions point dans la projection
CGMVersionMacroDefine(899 ,Fillet_NoGeoPointedSnappingInsideSA                         ,rr  ,28-05-2004 ,"V5R13 SP5 - RI0452779 ") // Activation immédiate svp
CGMVersionMacroDefine(900 ,CATIdenticalSurSur_Cylinder                                 ,PKC ,27-05-2004 ,"V5R13 SP5 - pour versionner IsConfused ") // A446835
CGMVersionMacroDefine(901 ,Sweep_CutUsingReferenceCCVMapping                           ,NLD ,04-06-2004 ,"V5R13 SP5 - RI441434 ") // -cr   441434a 441434b       Precision de la reduction de twist dans le sweep
CGMVersionMacroDefine(902 ,Fillet_UnTwistR14SP5                                        ,RR  ,04-06-2004 ,"V5R13 SP5 - RI0453206 ") // ACTIVATION IMMEDIATE SVP
CGMVersionMacroDefine(903 ,Loft_NewShapeWithNoRelimit                                  ,NDN ,04-06-2004 ,"V5R13 SP5 - Stabilisation Draft Reorder ")
CGMVersionMacroDefine(904 ,CleanCurve_ActiveSplitByApprox                              ,RNO ,07-06-2004 ,"V5R13 SP5 - Manage very small arcs on input  + constraintes extrmite de wire lorsque tout est reduit ") // RI CD A0444845  Note: ODT GSMCurveSmoothExtrem06 KO (mais OK en manuel pour moi)
CGMVersionMacroDefine(905 ,Extremum_ConfusionOnCurve                                   ,jhn ,07-06-2004 ,"V5R13 SP5 - RI 452269 ") // adl_promote -cr 452269A 452269B
CGMVersionMacroDefine(906 ,BodyFromLengthOnWire_StabilizeExtremity                     ,jhn ,07-06-2004 ,"V5R13 SP5 - bug +regression dans ODT ") // a promouvoir tout court. gain de perfos et de taille de donnee attendu
CGMVersionMacroDefine(907 ,Sweep_GuideOrderingCorrectionByProfileOrientation           ,NLD ,11-06-2004 ,"V5R13 SP5 - RI454067, suivi loft ") // -cr 454067a
CGMVersionMacroDefine(908 ,ExtrapolSurface_NewIncreaseDegree                           ,aad ,11-06-2004 ,"V5R13 SP5 - Appel d\'une nouvelle methode optimisee pour IncreaseDegree ") // Perfos du Healing topologique
CGMVersionMacroDefine(909 ,TrimByThick_BijectiveImpactForMappingOffsetFaces            ,DPS ,11-06-2004 ,"V5R13 SP5 - correction changement de journal dans TrimByThick ") // modification des faces par couple d\'offset
CGMVersionMacroDefine(910 ,Projection_LogPointSolutions                                ,ice ,11-06-2004 ,"V5R13 SP5 ") // Suivi des solutions point dans la projection
CGMVersionMacroDefine(911 ,Fillet_InitWithLimiting                                     ,JMA ,14-06-2004 ,"V5R13 SP5 - RI0449454 ") // -cr 449454A
CGMVersionMacroDefine(912 ,ExtractEdge_JournalExtremity                                ,jhn ,14-06-2004 ,"V5R13 SP5 - A la demande de FLZ pour RI externe ") // sans
CGMVersionMacroDefine(913 ,Offset_RecordOffsetPCurveUVBox                              ,DPS ,14-06-2004 ,"V5R13 SP5 - RI CVI mettant en evidence une mauvaise gestion des paves a offseter dans certains cas ") // adl_promote -cr 453303A 455410A
CGMVersionMacroDefine(914 ,Parallel_RelimBySphereCloseWire                             ,AOV ,14-06-2004 ,"V5R13 SP5 - bug dans relimitation par semi sphere du parallele dans cas ou wire ferme ")
CGMVersionMacroDefine(915 ,Sweep_2DCombCleaner                                         ,JSX ,14-06-2004 ,"V5R13 SP5 - Generalisation des comb 2D a tous les sweep ") // pour le C1 R14
CGMVersionMacroDefine(916 ,Offset_NewIntraSRepClashStarter                             ,MNJ ,18-06-2004 ,"V5R13 SP5 - RI A0454847 A0452743 ") // adl_promote -cr A0454847 A0452743
CGMVersionMacroDefine(917 ,RollingEdge_LimitConfiguration                              ,FCX ,18-06-2004 ,"V5R13 SP5 - RI Reg 451735 ") // -cr 451735A
CGMVersionMacroDefine(918 ,DistanceMin_InfiniteComputation                             ,jhn ,22-06-2004 ,"V5R13 SP5 - traitement de l\'infini dans le distancemin sur RI MNT ") // adl_promote -cr 455032A

#endif
