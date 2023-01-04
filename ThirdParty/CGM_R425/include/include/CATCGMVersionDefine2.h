#ifndef CATCGMVersionMacroDefine2_h
#define CATCGMVersionMacroDefine2_h
// COPYRIGHT DASSAULT SYSTEMES  2002

//=========================================================================================================
// V5R14 SP1
//=========================================================================================================
CGMVersionMacroDefine(950 ,Healing_Level13                                             ,JEP ,25-06-2004 ,"V5R14 SP1 - priorite aux faces reconnues planes ")
CGMVersionMacroDefine(951 ,TrimByThick_SharpLyingOnTrimBorder                          ,DPS ,25-06-2004 ,"V5R14 SP1 - optimisation de l\'algo de Trim dans l\'epaississement ") // cas d\'ecole developpement SharpLyingOn
CGMVersionMacroDefine(952 ,CATCurveToCanonic_NewCircle                                 ,STY ,25-06-2004 ,"V5R14 SP1 - RI ")
CGMVersionMacroDefine(953 ,Thick_SelectVolumeLevel                                     ,MNJ ,25-06-2004 ,"V5R14 SP1 - RI A0446630 et A0452387 ") // adl_promote -cr A0446630 A0452387
CGMVersionMacroDefine(954 ,Rib_GestionInitExitGap                                      ,ASE ,25-06-2004 ,"V5R14 SP1 - RI 0455416 ") // activation immediate
CGMVersionMacroDefine(955 ,Sweep_PlanarC0SpineDetection_V2                             ,NLD ,25-06-2004 ,"V5R14 SP1 ") // -cr 446762B
CGMVersionMacroDefine(956 ,FilletFaceFace_RemoveConfusionsInSelfIntersection           ,JMA ,28-06-2004 ,"V5R14 SP1 - RI0433932 ") // -cr 433932A
CGMVersionMacroDefine(957 ,Offset_CreateSmoothEdgeAfterERepBreak                       ,LAP ,28-06-2004 ,"V5R14 SP1 - RI447971 ") // adl_promote -cr 447971C
CGMVersionMacroDefine(958 ,VaribaleFillet_ValidatePointingSet                          ,pkc ,28-06-2004 ,"V5R14 SP1 - RI REG ")
CGMVersionMacroDefine(960 ,Thick_ImportReverseEdgeTopoVtx                              ,DPS ,28-06-2004 ,"V5R14 SP1 - auto ") // adl_promote -cr 457634A
CGMVersionMacroDefine(961 ,Sweep_Interpol_AnalyseInputSegmentationV2                   ,JSX ,28-06-2004 ,"V5R14 SP1 - Utilisation de GetEquivalentParam ")
CGMVersionMacroDefine(962 ,Simplify_Journal_FacesWithConfusion_bis                     ,fds ,28-06-2004 ,"V5R14 SP1 - Correction fonc. journal simplif pour Fabienne ")
CGMVersionMacroDefine(963 ,PointOnSurface_OptimisedComputation                         ,jhn ,05-07-2004 ,"V5R14 SP1 - amelioration perfo entrainant des regressions fonctionnelles. Qttentin deux ODTs GSD KO GSMJournalingLine_Plane_PointRec and GSMReflectLineDim dans GSMXN1.tst : ")
CGMVersionMacroDefine(964 ,UnFoldedAero_CheckRefCurves                                 ,OAU ,05-07-2004 ,"V5R14 SP1 - RI 0453568A ") // Add check NearestProjection PointWire
CGMVersionMacroDefine(965 ,GeodesicPtPt_CheckProjIfBestSolIsOrig                       ,AOV ,05-07-2004 ,"V5R14 SP1 - RI 449381 MustFix ")
CGMVersionMacroDefine(966 ,ThickSurf_SideEdgeTolerantModeling                          ,DPS ,05-07-2004 ,"V5R14 SP1 - robustesse de la creation d\\\'edges laterales weakly sharp (Recognize SheetMetal) ") // adl_promote -cr 449566B
CGMVersionMacroDefine(967 ,Rib_RelimUpdateCuttingVertexOnVertex                        ,ase ,06-07-2004 ,"V5R14 SP1 - RI ") // Activation immediate
CGMVersionMacroDefine(968 ,ThickenOp_CleverPCurveSelection                             ,DPS ,06-07-2004 ,"V5R14 SP1 - optimisation du choix de la PCurve dans la construction des parois laterales ") // cas plan : TabulatedCylinder pour Recognize de SheetMetal
CGMVersionMacroDefine(969 ,FilletFaceFace_NonConnectedInit                             ,PFV ,09-07-2004 ,"V5R14 SP1 - RI 0447993 ") // Pour FiletFaceFace et/ou FilletTriTg
CGMVersionMacroDefine(970 ,RollingEdgeCrvPln_LimitConfiguration                        ,fcx ,09-07-2004 ,"V5R14 SP1 - Stabilisation keep edge plan courbe ") // -cr 457225A
CGMVersionMacroDefine(971 ,Coupling_Projection_SmoothEdge                              ,RHA ,09-07-2004 ,"V5R14 SP1 - SmartProjection ") // SmartProjection pour JHN
CGMVersionMacroDefine(972 ,Sweep_CanonicCaseOnCanonicReference                         ,NLD ,16-07-2004 ,"V5R14 SP1 - generation de surfaces canoniques dans des cas de surfaces de references canoniques ") // -cr 441541A
CGMVersionMacroDefine(973 ,StylingSweep_Report_02                                      ,MMO ,19-07-2004 ,"V5R14 SP1 - Probleme dans le Journal du Styling Sweep ") // Traitement du RI A0453652
CGMVersionMacroDefine(974 ,CleanCurve_ApproxGeneralised                                ,RNO ,23-07-2004 ,"V5R14 SP1 - Bug en cas de NURBS rationnelle (Pbm CAA) ")
CGMVersionMacroDefine(975 ,Corner_Indexation_VariableRadius                            ,alv ,23-07-2004 ,"V5R14 SP1 - Ajout d\'un critère discriminant plusieurs corners(non encore différenciable): le rayon ")
CGMVersionMacroDefine(976 ,ExtractFace_JournalOnFace                                   ,jhn ,26-07-2004 ,"V5R14 SP1 - faux journal dans CATTopExtractFace. Demande FLZ ")
CGMVersionMacroDefine(977 ,ExtrapolDraftSurface_Check3D                                ,fcx ,26-07-2004 ,"V5R14 SP1 - RI 442056 extrapolation d\'une surface draft du mauvais cote ") // -cr 442056A
CGMVersionMacroDefine(978 ,Parallel_BigMacroPtInExtrapol                               ,AOV ,30-07-2004 ,"V5R14 SP1 - Controle creation macropoint dans extrapolation utilisee par le parallele ") // pour regle de check MPG_1 (AJM)
CGMVersionMacroDefine(979 ,GetGeometryOn_MultiPCurves                                  ,PFV ,30-07-2004 ,"V5R14 SP1 - RI 0446287 ")
CGMVersionMacroDefine(980 ,Sweep_C0TreatmentForExplicitSpine                           ,NLD ,30-07-2004 ,"V5R14 SP1 - RI mnt ") // A activer   -cr 460533a
CGMVersionMacroDefine(981 ,Sweep_AutomaticSpineForGuideRedefinition                    ,NLD ,30-07-2004 ,"V5R14 SP1 ") // A activer
CGMVersionMacroDefine(982 ,RollingEdge_MultiConstraints2                               ,pkc ,30-07-2004 ,"V5R14 SP1 - ri ")
CGMVersionMacroDefine(983 ,Sweep_Rule_INF_1                                            ,JSX ,02-08-2004 ,"V5R14 SP1 - Init du coupling par eval au milieu du domaine. ExtremitÃ©s hors modele si spine infinie ")
CGMVersionMacroDefine(984 ,Extrapol_OrientationOfLyingOnEdge                           ,JSX ,02-08-2004 ,"V5R14 SP1 - RI 460436 Orientation logique par la MergeCurve ") // promote -cr A0460436
CGMVersionMacroDefine(985 ,IntersectionCrvCrv_BestPoint_Reconverge                     ,RHA ,02-08-2004 ,"V5R14 SP1 - Sweep Quality ")
CGMVersionMacroDefine(986 ,IntersectionLineRevol_OrthogonalReconverge                  ,aad ,02-08-2004 ,"V5R14 SP1 - RI ") // -cr 459677a 459677b
CGMVersionMacroDefine(987 ,VariableFillet_StrongNonCompleteSet                         ,pkc ,02-08-2004 ,"V5R14 SP1 - RI 458345 ") // -cr 458345A
CGMVersionMacroDefine(988 ,Corner_FixPtOrient                                          ,ALV ,06-08-2004 ,"V5R14 SP1 - Dans le cas d\'un corner sur plan on doit fixer l\'orientation d\'un point en input comme pour un corner sur support(RI0461155) ")
CGMVersionMacroDefine(989 ,CleanCurve_ReduceAndReportVertices                          ,RNO ,06-08-2004 ,"V5R14 SP1 - Amelioration Smoothing dans les cas sans simplification, permet d\'utiliser ce nouveau mode ")
CGMVersionMacroDefine(990 ,Extruder_ByMatrix_PosageComplet                             ,alv ,06-08-2004 ,"V5R14 SP1 - RIA0460413 le posage d\'une curve dans CATExtruderByMatrix doit etre fait sur les MaxLimits ")
//CGMVersionMacroDefine(991 ,Simplify_ClosedSurface_Advanced                             ,fds ,06-08-2004 ,"V5R14 SP1 - Simplif avancee de surfaces closes pour fabienne ") // desactivee le 20-08-2004 dans OFF
CGMVersionMacroDefine(992 ,VarOffset_CheckConstraintWire                               ,PMG ,06-08-2004 ,"V5R14 SP1 - Controle le partage de la topologie : Wire < ")
CGMVersionMacroDefine(993 ,Projection_CrvSur_MappingCircle                             ,sty ,06-08-2004 ,"V5R14 SP1 - Pb de Smart projection ")
CGMVersionMacroDefine(994 ,FilletInit_SupportBoxExtension                              ,JMA ,09-08-2004 ,"V5R14 SP1 - RI0461621 ") // -cr A0461621
CGMVersionMacroDefine(995 ,Offset_ConstraintBisectorBorderVRep                         ,DPS ,13-08-2004 ,"V5R14 SP1 - RI MNT TMC : pb de contrainte sur les bissectrices debouchant sur les bords de skin ") // adl_promote -cr 460536A
CGMVersionMacroDefine(996 ,Offset_CleverCriteriumForOptionalSharpPts                   ,DPS ,13-08-2004 ,"V5R14 SP1 - regression fonctionnelle dans l\'Extrapolation en courbure (TMC) ") // adl_promote -cr 460677A 460677B
CGMVersionMacroDefine(997 ,IntersectionCrvSur_ZeroStabilization                        ,sty ,13-08-2004 ,"V5R14 SP1 - RI458260 ")
CGMVersionMacroDefine(998 ,CATProjectionCrvSur_CheckPNurbs                             ,sty ,13-08-2004 ,"V5R14 SP1 - RI461283 ") // Activation demandee pour vendredi 13 Aout
CGMVersionMacroDefine(999 ,Rib_Relim_CouplingWithGapOnSkin                             ,FBZ ,17-08-2004 ,"V5R14 SP1 - RI 460993 ") // activation immédiate
CGMVersionMacroDefine(1000,Extrapol_GoodMiddlePlaneForHalfCylinders                    ,JSX ,17-08-2004 ,"V5R14 SP1 - La forme se rapproche de l\'extrusion ") // Construction d\'un plan non valide puis mlk
CGMVersionMacroDefine(1001,Extrapol_Until_RemoveNonDisconnectableWire                  ,JSX ,17-08-2004 ,"V5R14 SP1 - RI 460395 ") // -cr 460395
CGMVersionMacroDefine(1002,Parallel_OrderedNuplets                                     ,AOV/MQZ,17-08-2004 ,"V5R14 SP1 - RI parallel ribbon (447121) ") // promote -cr 447121A
CGMVersionMacroDefine(1003,PCurvesOffset_BestQuality                                   ,EAB ,20-08-2004 ,"V5R14 SP1 - RI0448230 ") // promote -cr A0448230
//CGMVersionMacroDefine(1004,CATIntersectionCrvCrvCx2_StabConf                           ,EAB ,20-08-2004 ,"V5R14 SP1 - Ri SUG ") // desactivee le 26-08-2004
CGMVersionMacroDefine(1005,MarshMallow_Level6                                          ,PMG ,20-08-2004 ,"V5R14 SP1 - Correction problemes BMW (Incoherence Limite/Mapping) ")
CGMVersionMacroDefine(1006,MathIntegration_BugTwoClenshawCurtis7                       ,AAD ,20-08-2004 ,"V5R14 SP1 - RI ") // -cr 462811a
CGMVersionMacroDefine(1007,Relim_CoveredFacesForKeepFeature                            ,ase ,20-08-2004 ,"V5R14 SP1 - RI 0463366A ") // activation immediate (-cr 0463366A)
CGMVersionMacroDefine(1008,SweepVaria_ExactEvalOnWB                                    ,JSX ,23-08-2004 ,"V5R14 SP1 - Perfo : Eval ") // Utilisation d\'une ancienne variable sans interet maintenant
CGMVersionMacroDefine(1009,Sweep_2DCombCleanerV2                                       ,JSX ,23-08-2004 ,"V5R14 SP1 - Nouveau comb pour les lofts:pour  C1 et draft reorder ")
//CGMVersionMacroDefine(1010,SweeVaria_PointInterpolation                                ,JSX ,27-08-2004 ,"V5R14 SP1 - Perfo (moins d\'evaluation) et Stabilite (les derivé¥³ ne sont pas precises) ") // Gain de 50% en CPU ( ref ODT GSMModel LocalFormula a modifier )
CGMVersionMacroDefine(1011,CATMathQuickDiscretizeFunctionX_ComputeBorderPoint_Confused ,AAD/KLX,27-08-2004 ,"V5R14 SP1 - Versioning a posteriori de la correction du RI 455132 ") // Activation immediate
CGMVersionMacroDefine(1012,TweakNoSimplifOfSkinFaces                                   ,FBZ ,27-08-2004 ,"V5R14 SP1 ") // Pour activation immédiate
CGMVersionMacroDefine(1013,Corner_TopologicalBiTgtRadInversedInputs                    ,ALV ,30-08-2004 ,"V5R14 SP1 - L\'inversion des inputs dans le CATTopologicalBiTgtRad ne permet pas de stocker le bon BeginOfCorner. ")
CGMVersionMacroDefine(1014,Corner_SecondAttempt_CircleMode                             ,ALV ,30-08-2004 ,"V5R14 SP1 - 30 ")
CGMVersionMacroDefine(1015,ProjectionCrvSur_SurfaceLimits                              ,obh ,31-08-2004 ,"V5R14 SP1 - Regression ") // activation immediate


//=========================================================================================================
// V5R14 SP2
//=========================================================================================================
CGMVersionMacroDefine(1030,Fillet_UnTwistR14SP2                                        ,RR  ,02-09-2004 ,"V5R14 SP2 - RI0461619 ") // Activation immédiate et attendre ouverture R14 SP2
CGMVersionMacroDefine(1031,ConstantFillet_ContactCanonicReport                         ,fcx ,02-09-2004 ,"V5R14 SP2 - RI 434831 ") // -cr 434831A
CGMVersionMacroDefine(1032,Loft_DoNotMoveFromGuideOnFlatZone                           ,jsx ,03-09-2004 ,"V5R14 SP2 - Promote ") // Guide non respectee
CGMVersionMacroDefine(1033,IntersectionCrvTab_BugLogalParam                            ,AAD ,03-09-2004 ,"V5R14 SP2 - Correction Bug ") // -cr 464316a
CGMVersionMacroDefine(1034,CurveAffineSupport_NewRun                                   ,obh ,03-09-2004 ,"V5R14 SP2 - RI externe ") // -cr 457017A  457017B  457017C
CGMVersionMacroDefine(1035,Offset_UniNormalPointForInternalSectorSmoothEdge            ,LAP ,07-09-2004 ,"V5R14 SP2 - RI461707 ") // adl_promote -cr 461707A  (pour la livraison de l\'activation )
CGMVersionMacroDefine(1036,Parallel_ShellBoundary                                      ,jhn ,07-09-2004 ,"V5R14 SP2 - suivi des extremites dans le parallele ") // adl_promote -cr 464005
CGMVersionMacroDefine(1037,PointOnShell_OriginOnSupport                                ,jhn ,07-09-2004 ,"V5R14 SP2 - demande FLZ ") // changement de la descri[tion du point on shell
//CGMVersionMacroDefine(1038,Projection_BooleanSoftware                                  ,JHN ,07-09-2004 ,"V5R14 SP2 - Unifier tous les softs de projection ") // a relier etroitement a la smart projection
CGMVersionMacroDefine(1038,Extremum_StabiliseVolumes                                   ,jhn ,07-09-2004 ,"V5R14 SP2 - bug de stabilite d\'extremum pour les volumes ") // no comment
CGMVersionMacroDefine(1039,Homotopy3Sur_NewDegenerateCase                              ,EAB ,07-09-2004 ,"V5R14 SP2 - RI432347 ") // promote -cr A0432347
//CGMVersionMacroDefine(1040,Join_Journal_InternalEdges                                  ,JBX ,07-09-2004 ,"V5R14 SP2 - Ne pas suivre les aretes internes non creees par l\'algo ") // -cr D0463059 debranchee le 08-09-2004
CGMVersionMacroDefine(1041,Extrapol_NonIsoSharpBoundarySelection                       ,DPS ,07-09-2004 ,"V5R14 SP2 - calcul aberrant de boites utiles pour l\'extrapolation en courbure ") // convergence minimiseur MaxOffset
CGMVersionMacroDefine(1042,Offset_TwinBisectorGeneratorRescue                          ,DPS ,07-09-2004 ,"V5R14 SP2 - convergence RI TMC 463480 ") // ajustement des boites utiles dans les traitements par bissectrices
CGMVersionMacroDefine(1043,TangnetLinePCrvPCrv_PCirclePCircle                          ,obh ,07-09-2004 ,"V5R14 SP2 - RI externe ") // adl_promote -cr  A0461882
CGMVersionMacroDefine(1044,Thick_ForbidBigVerticesLevel                                ,MNJ ,07-09-2004 ,"V5R14 SP2 - RI MustFix 464542A et B ") // adl_promote -cr A0464542 B0464542
CGMVersionMacroDefine(1045,CATProjectCrvSurMapX_ToleranceRHA                           ,EAB ,10-09-2004 ,"V5R14 SP2 - Correction dans le MapX ")
CGMVersionMacroDefine(1046,Relim_InNupletCompletionThruConnection                      ,ase ,10-09-2004 ,"V5R14 SP2 - ODT ") // Activation ASAP pour R14 SP2
CGMVersionMacroDefine(1047,VarOffset_CheckOverlap                                      ,PMG ,10-09-2004 ,"V5R14 SP2 - RI B0459972 ") // promote -cr B0459972
CGMVersionMacroDefine(1048,Sweep_IsParallel_GeoTol                                     ,ndn ,10-09-2004 ,"V5R14 SP2 - Instabilite ") // 0465067A
CGMVersionMacroDefine(1049,Join_Journal_InternalEdges                                  ,JBX ,10-09-2004 ,"V5R14 SP2 - Ne pas suivre les aretes internes non creees par l\\\'algo ") // -cr D0463059
CGMVersionMacroDefine(1050,IntersectionSurSur_PLineDetectionWithChord                  ,XGN ,10-09-2004 ,"V5R14 SP2 - RI464727A+B ") // Activation immediate
CGMVersionMacroDefine(1051,CATExtrapolSurfacesForOffset_MoinsDeGras                    ,EAB ,10-09-2004 ,"V5R14 SP2 - ODT Versionnés livré le 10/09/04 ") // promote -cr A0463480 B0463480 C0463480
CGMVersionMacroDefine(1052,DistanceSurSur_CasPlanPlan                                  ,EAB ,10-09-2004 ,"V5R14 SP2 - RI ext 465100 ") // promote -cr A465100 B465100
CGMVersionMacroDefine(1053,Wrap_JournalingDefect                                       ,dr  ,10-09-2004 ,"V5R14 SP2 - ri 0455021A ") // mauvaise ecriture dans le journal 0455021A
CGMVersionMacroDefine(1054,CATMathQuickDiscretizeFunctionX_RecordPoint_Confused        ,klx ,10-09-2004 ,"V5R14 SP2 - RI 464042 activ immediate ") // -cr 464042A 464042B
CGMVersionMacroDefine(1055,Parallel_SolveByProjection2                                 ,klx ,10-09-2004 ,"V5R14 SP2 - IR 464154 activ immediate ") // -cr 464154A 464154B
//CGMVersionMacroDefine(1056,Thick_RemoveFaceLevel5                                      ,MNJ ,10-09-2004 ,"V5R14 SP2 - RI B0459551 ") // adl_promote -cr B0459551
CGMVersionMacroDefine(1056,Offset_SurfCompatibilityFilterLevel2                        ,DPS ,13-09-2004 ,"V5R14 SP2 - convergence Offset sur Fillet variable ") // bug interne
CGMVersionMacroDefine(1057,Offset_SuperEdgeFilterOnBorderEdge                          ,LAP ,13-09-2004 ,"V5R14 SP2 - Gain perfo ")
//CGMVersionMacroDefine(1058,Offset_SuperEdgeFilterOnMicroEdge                           ,LAP ,13-09-2004 ,"V5R14 SP2 - RI 462804 ") // adl_promote -cr 462804A 462804B (pour la livraison de l\'activation)
CGMVersionMacroDefine(1058,OrnTgWireLayOn2                                             ,CCK ,14-09-2004 ,"V5R14 SP2 - RI465763 ") // -cr 465763
CGMVersionMacroDefine(1059,Fillet_CorrectActivationOfRlmRibs                           ,jma ,14-09-2004 ,"V5R14 SP2 - RI 464709 ") // declaration du flag actif, s\'il vous plait (-cr 464709A)
CGMVersionMacroDefine(1060,Relim_TrimSew_FaceExtrapolRatioVsVolumeBox                  ,ase ,15-09-2004 ,"V5R14 SP2 - TrimSew enhancement ") // activation immediate
//CGMVersionMacroDefine(1061,Thick_ForgetBadXSurSurSolution                              ,MNJ ,13-09-2004 ,"V5R14 SP2 - RI A0463421 ") // adl_promote -cr A0463421
CGMVersionMacroDefine(1061,Relim_Compl_DiffDomains_DuplicConfSupp                      ,ase ,15-09-2004 ,"V5R14 SP2 - Stabilisation dans completion de relimitation ") // Activation immediate
CGMVersionMacroDefine(1062,ExtrapUpTo_CheckInputs                                      ,AOV ,17-09-2004 ,"V5R14 SP2 - RI466096 ")
CGMVersionMacroDefine(1063,Offset_SuperEdgeFilterOnMicroEdge                           ,LAP ,17-09-2004 ,"V5R14 SP2 - RI 462804 ") // adl_promote -cr 462804A 462804B (pour la livraison de l\'activation)
//CGMVersionMacroDefine(1064,Plane_Direction_LinesConfused                               ,ALV ,17-09-2004 ,"V5R14 SP2 - Test sur les lignes confondues trop restrictif cf RI0465402 ")
CGMVersionMacroDefine(1064,Pocket_Complement_Oblique                                   ,fds ,17-09-2004 ,"V5R14 SP2 - RI463440A ") // Activation immediate
//CGMVersionMacroDefine(1065,Corner_TriTangent_PosagePtContact                           ,ALV ,17-09-2004 ,"V5R14 SP2 - posage des points de contact dans le calcul de redondance des corners tri tangent ")
CGMVersionMacroDefine(1065,RollingEdge_ComputeInitPtPln                                ,FCX ,17-09-2004 ,"V5R14 SP2 - RI 465566 ") // promote -cr 465566A
CGMVersionMacroDefine(1066,GeodesicParallel_BorderPoints                               ,klx ,17-09-2004 ,"V5R14 SP2 - RI 463479 ") // activ immediate (-cr deja fait)
CGMVersionMacroDefine(1067,Projection_BooleanSoftware                                  ,JHN ,21-09-2004 ,"V5R14 SP2 - Unifier tous les softs de projection ") // a relier etroitement a la smart projection
CGMVersionMacroDefine(1068,Sweep_AlignClosurePointsBeforeStart                         ,NLD ,21-09-2004 ,"V5R14 SP2 - RI464233 ") // promote -cr 464233a 452735a stabilisation cas guide ouverte / guide fermee
CGMVersionMacroDefine(1069,MaxOffset_DirectMinimizer                                   ,CQI ,21-09-2004 ,"V5R14 SP2 ")
CGMVersionMacroDefine(1070,Thick_RemoveFaceLevel5                                      ,MNJ ,21-09-2004 ,"V5R14 SP2 - RI B0459551 ") // adl_promote -cr B0459551
CGMVersionMacroDefine(1071,Thick_ForgetBadXSurSurSolution                              ,MNJ ,21-09-2004 ,"V5R14 SP2 - RI A0463421 ") // adl_promote -cr A0463421
CGMVersionMacroDefine(1072,Offset_CleverCriteriumForOrphanEdges                        ,DPS ,21-09-2004 ,"V5R14 SP2 - traitement des degenerescences dans l\'offset (RI MNT TMC) ") // adl_promote -cr 466758A
CGMVersionMacroDefine(1073,Parallel_CreateRawTrackFix                                  ,AOV/REN,21-09-2004 ,"V5R14 SP2 - Ri465949 parallele ") // promote -cr 465949A 465949B
CGMVersionMacroDefine(1074,IntersectWW_PointJournal                                    ,ice ,21-09-2004 ,"V5R14 SP2 - RI431545 ") // Info supplementaire pour distinguer les sols point des sols aretes
CGMVersionMacroDefine(1075,RibSweep_180ArcConstraintFix                                ,FDL ,21-09-2004 ,"V5R14 SP2 - Improvement in Sweep circle function ") // adl_promote -cr A0465031 A0465869
CGMVersionMacroDefine(1076,Plane_Direction_LinesConfused                               ,ALV ,21-09-2004 ,"V5R14 SP2 - Test sur les lignes confondues trop restrictif cf RI0465402 ")
CGMVersionMacroDefine(1077,Corner_TriTangent_PosagePtContact                           ,ALV ,21-09-2004 ,"V5R14 SP2 - posage des points de contact dans le calcul de redondance des corners tri tangent ")
CGMVersionMacroDefine(1078,Regul_FacesAdj_MaxOffsetOnBoxUV                             ,FBZ ,24-09-2004 ,"V5R14 SP2 ")
CGMVersionMacroDefine(1079,Fillet_SmoothRelim_R14SP2                                   ,RR  ,24-09-2004 ,"V5R14 SP2 - RI0467217 ") // ACTIVATION IMMEDIATE SVP
CGMVersionMacroDefine(1080,Offset_FilterNonIsoClosingFaces                             ,DPS ,24-09-2004 ,"V5R14 SP2 - RI  MustFix ") // adl_promote -cr 465945A
CGMVersionMacroDefine(1081,ReflectLineDraft_SpecialFaceInhibitor                       ,PFV ,24-09-2004 ,"V5R14 SP2 - RI0467171 ") // Activation immediate
CGMVersionMacroDefine(1082,PowerDef_AddInfo2                                           ,PMG ,27-09-2004 ,"V5R14 SP2 - RI A0465766 ") // -cr A0465766
CGMVersionMacroDefine(1083,TriTangentPCrv_ParallelCurve                                ,PKC ,27-09-2004 ,"V5R14 SP2 - ri ") // -cr 467338 A
CGMVersionMacroDefine(1084,DraftBothSides_ReportInitNew                                ,pkc ,28-09-2004 ,"V5R14 SP2 - correction modele DCS pour Sp2 ")
CGMVersionMacroDefine(1085,Extrapol_NoDomainIntersectionResearch                       ,MNJ ,30-09-2004 ,"V5R14 SP2 - amelioration perfo dans SkinExtrapol ") // adl_promote -cr A0467465


//=========================================================================================================
// V5R14 SP3
//=========================================================================================================
CGMVersionMacroDefine(1101,Rib_Relim_ClosedSurfaceLoopExtension2                       ,FBZ ,01-10-2004 ,"V5R14 SP3 - Complémentaires ") // Activation sur R14SP3
CGMVersionMacroDefine(1102,Simplify_ClosedSurface_Advanced                             ,fds ,01-10-2004 ,"V5R14 SP3 - Simplif avancee de surfaces closes pour fabienne ") // A activer sur R14SP3 en même tps que Rib_Relim_ClosedSurfaceLoopExtension2.
CGMVersionMacroDefine(1103,ImplicitSpine_StabilizeLineProfile                          ,CCK ,01-10-2004 ,"V5R14 SP3 - RI ") // -cr A0467177
CGMVersionMacroDefine(1104,TryConfusionCrvCrv_GrandeTolerance                          ,EAB ,01-10-2004 ,"V5R14 SP3 - RI externe ") // promote -cr D0459285
CGMVersionMacroDefine(1105,Rib_InitVertexGapEval_Enhancement1                          ,ase ,01-10-2004 ,"V5R14 SP3 - tolerant modeling ") // activation immediate (pour R14SP3)
CGMVersionMacroDefine(1106,AutoFill_CheckPOEC                                          ,MPS ,05-10-2004 ,"V5R14 SP3 - traiter les ODTs  d\' AutoFill  KO par la regle MPG_1 ")
CGMVersionMacroDefine(1107,Loft_SmoothedProfileComb                                    ,JSX ,05-10-2004 ,"V5R14 SP3 - Smooth du peigne de tangence (profils des lofts) et activation du similar ") // Impact sur les drafts reorder
CGMVersionMacroDefine(1108,Sweep_MovingFrame_ProjectionPseudoOrtho                     ,JSX ,05-10-2004 ,"V5R14 SP3 - MvPseudoOrtho::Project rend maintenant des solutions si une courbe de la spine est prcisée ") // Fin de la mise en coherence des projects() des movingFrames
CGMVersionMacroDefine(1109,EdgeCurvePropagateQuery_MaxLimitsIflrrelevant               ,AAD ,05-10-2004 ,"V5R14 SP3 - RI CATDUAV5 ") // -cr 464849b 464849c
CGMVersionMacroDefine(1110,UnFoldedAero_DiscretisationPerfo                            ,OAU ,05-10-2004 ,"V5R14 SP3 - ri B0453568 ") // -cr B0453568
CGMVersionMacroDefine(1111,Sweep_CloneMasterWithMergedCurves                           ,NLD ,05-10-2004 ,"V5R14 SP3 - clonage pour eviter extrapolation des mergedcurves C0. RI452735 ") // -cr 452735a
CGMVersionMacroDefine(1112,Sweep_ComputeCCVContinuityV2                                ,NLD ,05-10-2004 ,"V5R14 SP3 - revoir le calcul d\'ecart en tangence en cas de discontinuite en point sur la CCV ") // -cr 466086a
CGMVersionMacroDefine(1113,Sweep_ComputeCCVContinuityV3                                ,NLD ,05-10-2004 ,"V5R14 SP3 - revoir le calcul d\'ecart en tangence en cas de discontinuite en point sur la CCV ") // -cr 466086a
//CGMVersionMacroDefine(1113,DistanceCrvSur_CasLineSurf                                  ,eab ,05-10-2004 ,"V5R14 SP3 - Ri interne ") // promote -cr A0467208 . debranché le 06/10/2004
CGMVersionMacroDefine(1114,CanonicalProjection_IsLogicalConic                          ,pkc ,05-10-2004 ,"V5R14 SP3 - RI ")
CGMVersionMacroDefine(1115,Parallel_NegativeLawCst                                     ,AOV ,08-10-2004 ,"V5R14 SP3 - Ri   bug dans gestion loi negative constante ") // activation immediate
CGMVersionMacroDefine(1116,ShellFromClosedWire_CheckAutoCrossing                       ,FDS ,08-10-2004 ,"V5R14 SP3 - RI ") // Activation imédiate
//CGMVersionMacroDefine(1117,BlendRibbon_Hermetisation_3                                 ,FDL ,08-10-2004 ,"V5R14 SP3 - chgt ref odt CGMTest_NewTopoN1DraftReflectLineBothSides11_Task1753_N1 livraison le 08/10/2004 dans CGMOFF. ")
CGMVersionMacroDefine(1118,InterShlShl_UseAfterAndBeforePosition                       ,jbx ,08-10-2004 ,"V5R14 SP3 ") // Pour sheetmetal,quand toute la trace est interieur-bord et en confusion, stabilise l\'orientation.
CGMVersionMacroDefine(1119,ExtrapolG2_ExtrapOnClosure                                  ,aov ,08-10-2004 ,"V5R14 SP3 - ri extrapolation G2 d\'un cercle ") // activation immediate
//CGMVersionMacroDefine(1120,Fillet_IsotopoSpecsOnSupports                               ,JMA ,08-10-2004 ,"V5R14 SP3 - RI 431094 ") // activation immediate
CGMVersionMacroDefine(1121,Thick_FilterTptFromDeadVRep                                 ,MNJ ,11-10-2004 ,"V5R14 SP3 - RI MustFix ") // adl_promote -cr A0468909 B0468909
CGMVersionMacroDefine(1122,Blend_NoSmoothOnSingleEdgeWire                              ,JSX ,11-10-2004 ,"V5R14 SP3 - precision de la continuite en tang avec les appuis ") // -cr 468236a
CGMVersionMacroDefine(1123,Parallel_DeformTracksDeviation                              ,klx ,11-10-2004 ,"V5R14 SP3 - pour suh ")
CGMVersionMacroDefine(1124,ExtrapUpTo_UpToShellOnSupport                               ,AOV ,11-10-2004 ,"V5R14 SP3 - nouvelle option pour GSD ")
CGMVersionMacroDefine(1125,Inteligent_RefCurve_In_IntCurve                             ,RHA ,11-10-2004 ,"V5R14 SP3 - Perfos ") // asap
CGMVersionMacroDefine(1126,Posage_HomogenizeCuttings                                   ,ice ,15-10-2004 ,"V5R14 SP3 - Homogeneisation plus complete des coupantes dans le cadre du posage ")
CGMVersionMacroDefine(1127,Offset_BulldozerLevel2                                      ,LAP ,15-10-2004 ,"V5R14 SP3 - RI467164 ") // adl_promote -cr 467164A 467164B (a faire lors de l\'activation dans CGMOFF)
CGMVersionMacroDefine(1128,MaxOffset_GenericFillet_NewSampling                         ,CQI ,15-10-2004 ,"V5R14 SP3 - RI 456031 ")
CGMVersionMacroDefine(1129,Rib_CutTracksAgainWithSupports                              ,ase ,15-10-2004 ,"V5R14 SP3 - Besoin TrimSew dans AutoFillet ") // Activation pour R14SP3 seulement
CGMVersionMacroDefine(1130,CATIntersectionCrvCrvCx2_StabConf                           ,EAB ,15-10-2004 ,"V5R14 SP3 - Ri sug ") // Activation sur CGMOFF en fonction de la valid des ODT michelin faite en parallele - Un CGMReplay sera KO par ma variable je m\'occupe de son réenregistrement
CGMVersionMacroDefine(1131,Extrude_Tolerance                                           ,FDS ,15-10-2004 ,"V5R14 SP3 - RI 468838A , activation immédiate demandé ")
CGMVersionMacroDefine(1132,Bump_Level5                                                 ,PMG ,15-10-2004 ,"V5R14 SP3 ") // -cr   A0467236 B0467236
CGMVersionMacroDefine(1133,Extrapol_TolerantModelingForceBisector                      ,dps ,15-10-2004 ,"V5R14 SP3 - Accepter les gros gaps en entree de l\'Extrapolation en courbure (bissectrice sans offset) ") // adl_promote -cr 445127A (Renault, TolerantModeling)
CGMVersionMacroDefine(1134,Offset_XSurTgPCGuideInTrimContext                           ,DPS ,15-10-2004 ,"V5R14 SP3 - Dev R15 FadingEdge in Trim context ") // (appel du SurSur tangent par PCurves guides)
CGMVersionMacroDefine(1135,ExtrapWire_SearchInitFace                                   ,AOV ,15-10-2004 ,"V5R14 SP3 - RI ") // activation immediate
CGMVersionMacroDefine(1136,Corner_OnPlane_ObjectsToDeleteInJourn                       ,ALV ,15-10-2004 ,"V5R14 SP3 - objets detruit dans l\'opérateur corner mais non detruit dans le journal ")
CGMVersionMacroDefine(1137,Rib_Relim_IsCoveredImprovement                              ,FBZ ,15-10-2004 ,"V5R14 SP3 - RI 469398 ")
CGMVersionMacroDefine(1138,ReflectCurve_MarchingSag                                    ,PKC ,18-10-2004 ,"V5R14 SP3 - RI ") // -cr 466469A 466469B
CGMVersionMacroDefine(1139,WrapSurface_ForceConvergence                                ,dr  ,18-10-2004 ,"V5R14 SP3 - ri toyota ")
//CGMVersionMacroDefine(1140,GeodesicParallel_ReportInit                                 ,klx ,18-10-2004 ,"V5R14 SP3 - RI 468785 ") // -cr 468785A 468785B debranchee le 05-11-2004
CGMVersionMacroDefine(1141,MaxOffset_RevolutionSurfaceProfileLimits                    ,FCX ,22-10-2004 ,"V5R14 SP3 - traitement specifique LocalMaxOffset sur des Revol Surfaces ") // -cr 468622A 468622B 468622C
CGMVersionMacroDefine(1142,IntersectionCrvCrv_TrustPlaneMethod                         ,AAD ,22-10-2004 ,"V5R14 SP3 - Perfo ")
CGMVersionMacroDefine(1143,BlendRibbon_Hermetisation_3                                 ,FDL ,22-10-2004 ,"V5R14 SP3 - activation drop tolerant modeling fillet ")
CGMVersionMacroDefine(1144,Fillet_Draft_CheckConnexity                                 ,FBZ ,22-10-2004 ,"V5R14 SP3 - RI ") // -cr 469560A 469560B - Activation immédiate
CGMVersionMacroDefine(1145,CATSpecBissectorSurfaceDef_CorrectionInstabilite            ,EAB ,25-10-2004 ,"V5R14 SP3 - Ri externe ") // promote -cr A0469379 B0469379 C0469379
CGMVersionMacroDefine(1146,UnFoldedAero_ShellExtrapolationIfNoIntersection             ,OAU ,25-10-2004 ,"V5R14 SP3 - Activation immediate ") // Activation immediate  - MUST FIX A0443340 adl_promote -cr A0443340 B0443340 C0443340
CGMVersionMacroDefine(1147,Thick_NoInterGeomDiagImprovement                            ,MNJ ,25-10-2004 ,"V5R14 SP3 - amelioration du diagnostic de non intersection de surfaces ")
CGMVersionMacroDefine(1148,Thick_Disco2DPcLoopPosition                                 ,MNJ ,25-10-2004 ,"V5R14 SP3 - positionnement des petites faces triangulaires dans le disconnect 2D ")
CGMVersionMacroDefine(1149,SmartProject_CGMReplay                                      ,jhn ,25-10-2004 ,"V5R14 SP3 - integration CGMReplay : lui donner ce qu\'il attend ") // no comment
CGMVersionMacroDefine(1150,Projection_AllDistances                                     ,jhn ,25-10-2004 ,"V5R14 SP3 - RI 469784 ") // adl_promote -cr A469784 B469784 C469784
CGMVersionMacroDefine(1151,Simplif_FilletDraft_LocalMode                               ,PFV ,26-10-2004 ,"V5R14 SP3 - RI 0469118 ") // Activation immediate (appel de la simplif en mode local + simplif skin draft dans la couture)
CGMVersionMacroDefine(1152,Corner_OnShellBiTgtRad_LayDownVxOnCurve                     ,alv ,27-10-2004 ,"V5R14 SP3 - Inversion des entrées du lay down lorsque celle ci ne sont pas dans l\'ordre décroissant de leur dimension ")
CGMVersionMacroDefine(1153,Fillet_SkinSkinOneRibbonIntersection                        ,JMA ,29-10-2004 ,"V5R14 SP3 - RI0461008 ") // activation immediate, s\'il te plait
//CGMVersionMacroDefine(1154,Corner_OnPlane_NewTestSupportIsPlane                        ,ALV ,29-10-2004 ,"V5R14 SP3 - RI0468795 On souhaite aussi utiliser le corner sur plan quand le support a comme geometryRep un plan ") // debranche le 17-11-2004
CGMVersionMacroDefine(1155,Offset_HealingGeoPostProLevel2                              ,MNJ ,02-11-2004 ,"V5R14 SP3 - coherence Extrapolation d\'edge ") // adl_promote -cr 450125B 450125C
CGMVersionMacroDefine(1156,Sweep_Relimitation_Surfacic                                 ,fds ,02-11-2004 ,"V5R14 SP3 - Correction bug ") // Activation immediate


//=========================================================================================================
// V5R14 SP4
//=========================================================================================================
CGMVersionMacroDefine(1170,PLinePLine_Corner                                           ,OBH ,05-11-2004 ,"V5R14 SP4 - RI externe ") // adl_promote -cr B0468060 C0468060 D0468060
CGMVersionMacroDefine(1171,ImplicitSpine_OnlyPlanesConfig2                             ,cck ,05-11-2004 ,"V5R14 SP4 - ri 471344 ") // activation immediate
CGMVersionMacroDefine(1172,Simplify_Edges_LocalMode                                    ,fds ,05-11-2004 ,"V5R14 SP4 - RI471500A ") // Activation immediate le 05/10
CGMVersionMacroDefine(1173,DefaultExtrapolRatioVsVolumeBoxValueChange                  ,ASE ,05-11-2004 ,"V5R14 SP4 - relimitation enhancement ") // activation immediate (a partir de R14 SP4)
CGMVersionMacroDefine(1174,Homotopy_Tangent_Surfaces                                   ,CQI ,05-11-2004 ,"V5R14 SP4 - RI 470917 (solution le long d\'un guide du fillet) ") // adl_promote -cr 470917A 470917B 470917C (lors de l\'activation dans CGMOFF)
CGMVersionMacroDefine(1175,HybridVarOffset_DevR15Healing                               ,LAP ,08-11-2004 ,"V5R14 SP4 ") // R15 development ,activation in R14SPx
CGMVersionMacroDefine(1176,Sweep_PlanesDetectionV4                                     ,NLD ,08-11-2004 ,"V5R14 SP4 - RI456074   orientation des plans en cas de face en pointe ") // -cr 456074B
CGMVersionMacroDefine(1177,Offset_RazorBladeDiagFilter                                 ,LAP ,08-11-2004 ,"V5R14 SP4 - Ri470287 ") // adl_promote -cr 470287A 470287B (lors de l\'activation dans CGMOFF)
CGMVersionMacroDefine(1178,Fillet_Init_BlockedSphere                                   ,FDL ,08-11-2004 ,"V5R14 SP4 - Traitement pour fillet init sphere bloquee ") // promote -cr A0467438
CGMVersionMacroDefine(1179,Sweep_OrderingWithCleverShift                               ,NLD ,08-11-2004 ,"V5R14 SP4 - RI sweep tolerant ") // -cr 468914A 468914B
CGMVersionMacroDefine(1180,Offset_NoMaxLimForBorderCollisions                          ,MNJ ,08-11-2004 ,"V5R14 SP4 - probleme de journal dans SkinExtrapol ") // adl_promote -cr A0470648 B0470648
CGMVersionMacroDefine(1181,Sweep_AlignClosurePointsBeforeStartV2                       ,NLD ,08-11-2004 ,"V5R14 SP4 - sweep ko ") // pre-alignement des fermetures dans le cas ou tous les wires sont fermes
CGMVersionMacroDefine(1182,Spline_KeepConnectionCurve                                  ,JHN ,08-11-2004 ,"V5R14 SP4 - RI ") // adl_promote -cr 471068A 471068B 471068C
CGMVersionMacroDefine(1183,CleanCurve_CheckSupportIso                                  ,RNO ,08-11-2004 ,"V5R14 SP4 - Probleme IGES ") // Cas des surfaces avec Iso U et V localement parallele
CGMVersionMacroDefine(1184,BlendRibbon_HermetisationByReport                           ,AJD ,08-11-2004 ,"V5R14 SP4 - IR 0468939 ") // adl_promote -cr A0468939 B0468939 (lors de l\'activation dans CGMOFF)
CGMVersionMacroDefine(1185,Stable_Canonical_Intersection                               ,RHA ,10-11-2004 ,"V5R14 SP4 - RI EXT ") // 1CGMreplay KO livre le 10/11
CGMVersionMacroDefine(1186,Corner_OnPlane_SetTrigoOrientForCorner                      ,ALV ,10-11-2004 ,"V5R14 SP4 - RI471413 lors de la relimitation d\'un corner(complet ou complementaire) prendre en compte l\'orientation du plan support par rapport au shell! ") // adl_promote -cr 0471413A  0471413AB 0471413C
//CGMVersionMacroDefine(1187,Offset_CleverMappingForEdges                                ,DPS ,15-11-2004 ,"V5R14 SP4 - meilleure filiation des edges en cas de disparition de parois minces ") // adl_promote -cr 460151A 471290A 471290B debranche le 17-11-2004
CGMVersionMacroDefine(1188,Draft_TrueMultiRib                                          ,PRL ,15-11-2004 ,"V5R14 SP4 - Activation Draft vrai multi ruban avec filtre ")
CGMVersionMacroDefine(1189,Fillet_KeepEdgeInitCorrectionTwo                            ,JMA ,15-11-2004 ,"V5R14 SP4 - RI0470826 ") // -cr A0470826
CGMVersionMacroDefine(1190,Loft_ProfilePositionWithoutGuideV2                          ,NLD ,15-11-2004 ,"V5R14 SP4 - RI mnt ") // -cr 470272a 470272b
CGMVersionMacroDefine(1191,CleanCurve_SuppressAllSmallCurves                           ,HLN ,19-11-2004 ,"V5R14 SP4 - Suppression de toutes les petites edges en mode 2D et hybride (edges isolees en part.) ") // Pour amelioration du Sweep/Loft
CGMVersionMacroDefine(1192,ExtrapUpTo_InputIntersect                                   ,AOV ,19-11-2004 ,"V5R14 SP4 - RI ")
CGMVersionMacroDefine(1193,Fillet_PointingDeformation_V0_1                             ,FCX ,19-11-2004 ,"V5R14 SP4 - Amelioration deformation en pointe (ODT Ko rel) ")
CGMVersionMacroDefine(1194,DevDev_PreciseAndConvergence1                               ,ndn ,19-11-2004 ,"V5R14 SP4 - RI ") // 0471932A 0471932B 0471932C
CGMVersionMacroDefine(1195,Sweep_Relimitation_BothLimit_Control                        ,fds ,19-11-2004 ,"V5R14 SP4 - RI472325A ")
CGMVersionMacroDefine(1196,Offset_VRepSRepConfusionFromNoInterGeomAnomaly              ,LAP ,19-11-2004 ,"V5R14 SP4 - RI427391 ") // adl_promote -cr 427391B
//CGMVersionMacroDefine(1197,Join_WarningOnSharedCells                                   ,JBX ,19-11-2004 ,"V5R14 SP4 - Modification de l\'algo de Join (la first pass a la reso est dans le meme operateur) pour permettre la gestion du warning des cellules partagees ") // desactive le 17-12-2004
CGMVersionMacroDefine(1198,NoUnnecessaryExtrapol_Boolean2D                             ,jbx ,19-11-2004 ,"V5R14 SP4 - Perfos ") // Modifie le journal.
CGMVersionMacroDefine(1199,Thick_TolerantSmoothVRepMerger                              ,MNJ ,19-11-2004 ,"V5R14 SP4 - convergence remplacement des ProcOffset par des surfaces approchees ") // activation immediate
CGMVersionMacroDefine(1200,Offset_CleverMappingForEdges                                ,DPS ,19-11-2004 ,"V5R14 SP4 - meilleure filiation des edges en cas de disparition de parois minces ") // (activation immediate) adl_promote -cr 460151A 471290A 471290B
CGMVersionMacroDefine(1201,New_GetParamFromLength                                      ,RHA ,21-11-2004 ,"V5R14 SP4 - RI Externe ") // Adl_promote -cr A0470442 B0470422 C0470442
CGMVersionMacroDefine(1202,Rib_InitVertexGapEval_Enhancement2                          ,AJD ,26-11-2004 ,"V5R14 SP4 - Tolerant modeling ") // J\'ai livre aujourd\'hui une modif dans CGMOFF pour que l\'ODT CGMSurfacicTests.tst\\CGMTest_SurfacicFilletEdgeShell10.sh\\Casee100 soit OK avec cette activation
CGMVersionMacroDefine(1203,Fillet_CorrectionForSplittingEdges                          ,JMA ,26-11-2004 ,"V5R14 SP4 - RI 0471024 ") // -cr 0471024A
CGMVersionMacroDefine(1204,Corner_OnPlane_WireResultOrient                             ,ALV ,26-11-2004 ,"V5R14 SP4 - RI0468795 L\'orientation d\'un corner par rapport au shell n\'est pas stable(prendre en compte l\'orientation du shell par rapport a sa geometrie) ") // a activer avant CGM_Versionning_Corner_OnPlane_NewTestSupportIsPlane
CGMVersionMacroDefine(1205,Corner_OnPlane_NewTestSupportIsPlane                        ,ALV ,26-11-2004 ,"V5R14 SP4 - RI0468795 On souhaite aussi utiliser le corner sur plan quand le support a comme geometryRep un plan ") // debranche le 17-11-2004 / -cr 0468795B 0468795C 0468795D
CGMVersionMacroDefine(1206,Parallel_InitHomotopy                                       ,klx ,26-11-2004 ,"V5R14 SP4 - ri 473192 (folded surface) ")
CGMVersionMacroDefine(1207,IntersectionPCrvPCrv_CorrectConfusionZone                   ,EAB ,26-11-2004 ,"V5R14 SP4 - RI externe ")
//CGMVersionMacroDefine(1208,CurveAffineSupport_New                                      ,obh ,26-11-2004 ,"V5R14 SP4 - RI  A0446574 ")
CGMVersionMacroDefine(1209,Offset_PerfectlyIsotopologicalERepCriterion                 ,LAP ,26-11-2004 ,"V5R14 SP4 - Ri 472660 Reg ") // adl_promote -cr 472660A 472660B 472660C
CGMVersionMacroDefine(1210,ThickSurf_ReconvCloneSharpBorderVRep                        ,DPS ,26-11-2004 ,"V5R14 SP4 - Tolerant modeling dans le ThickSurface ") // adl_promote 449609A 449609B
CGMVersionMacroDefine(1211,Fillet_IsotopoSpecsOnSupports                               ,JMA ,29-11-2004 ,"V5R14 SP4 ")
CGMVersionMacroDefine(1212,Regul_SmoothFacesAdj                                        ,FBZ ,29-11-2004 ,"V5R14 SP4 ")
CGMVersionMacroDefine(1213,Split_SimplifyCoupling                                      ,jhn ,29-11-2004 ,"V5R14 SP4 - RI 471119 ") // adl_promote -cr 471119A 471119B 471119C
CGMVersionMacroDefine(1214,TopModify_Unresolved_LyingOn                                ,fdn ,29-11-2004 ,"V5R14 SP4 - Unresolved bodies are supported by lying on links managment in TopModify ") // ri0470676
CGMVersionMacroDefine(1215,Sweep_CleanGuidesParametersV8                               ,NLD ,29-11-2004 ,"V5R14 SP4 ")
CGMVersionMacroDefine(1216,PCurvePCurveSignature                                       ,RHA ,29-11-2004 ,"V5R14 SP4 - RI EXT ") // Adl_promote -cr A0470442 B0470442 C0470442
CGMVersionMacroDefine(1217,Parallel_CheckContinuityFix                                 ,REN/AOV,03-12-2004 ,"V5R14 SP4 - activation immediate ") // bug dans CATParallelRib.
CGMVersionMacroDefine(1218,DistanceMinPtSur_CanonicalCasesStabilization                ,CQI ,03-12-2004 ,"V5R14 SP4 - RI473428 CAA ") // adl_promote -cr 473428A 473428B (lors de l\'activation dans CGMOFF). Problème de GetParam en échec sur l\'Apex d\'un cône ---> aucune solution retournée
CGMVersionMacroDefine(1219,ExtrapolSurfacesForOffset_ExactHomotopy                     ,FCX ,03-12-2004 ,"V5R14 SP4 - RI 472844 ") // activation immediate + promote -cr A0472844 B0472844 C0472844
CGMVersionMacroDefine(1220,Thick_PropagateExitFlagRestriction                          ,MNJ ,03-12-2004 ,"V5R14 SP4 - RI A0472408 et B0472408 ") // activation immediate + promote -cr A0472408 B0472408
CGMVersionMacroDefine(1221,Offset_ThinThicknessError                                   ,LAP ,06-12-2004 ,"V5R14 SP4 - Protection contre des valeurs d\'entrees invalides ")
CGMVersionMacroDefine(1222,PCurveOffset_ModifForAutoFillet                             ,EAB ,06-12-2004 ,"V5R14 SP4 - Problème d\'extrapolation KO dans l\'auto ") // New user = CQI
CGMVersionMacroDefine(1223,CornerPCrvPCrv_NonTangent_Circle                            ,obh ,06-12-2004 ,"V5R14 SP4 - RIA0472355 ")
CGMVersionMacroDefine(1224,Rib_Relim_DisconnectGivesEmptyShell                         ,FBZ ,10-12-2004 ,"V5R14 SP4 - Activation immédiate. ")
CGMVersionMacroDefine(1225,SameSurface_RelimitationOptimisation                        ,ice ,10-12-2004 ,"V5R14 SP4 ") // Optimisation du face/face sur meme fond
CGMVersionMacroDefine(1226,CurveAffineSupport_New                                      ,obh ,10-12-2004 ,"V5R14 SP4 ")
CGMVersionMacroDefine(1227,Offset_KillClosingFaceFromLoopSwap                          ,LAP ,10-12-2004 ,"V5R14 SP4 - Ri473884 Reg ") // creation + activation immediate + adl_promote -cr 473884A 473884B 473884C
CGMVersionMacroDefine(1228,CurveToCanonic_EdgeCrv                                      ,pkc ,10-12-2004 ,"V5R14 SP4 - RI ") // -cr 472639A
CGMVersionMacroDefine(1229,IntersectLineRevol_NewSampling                              ,PKC ,10-12-2004 ,"V5R14 SP4 - RI ext ") // -cr 0474874A 0474874B 0474874C 0473280A 0473280B 0473280C
CGMVersionMacroDefine(1230,Simplify_Only_ImpactedShell                                 ,fds ,10-12-2004 ,"V5R14 SP4 - 10 ")
CGMVersionMacroDefine(1231,Intersection_IsRoot                                         ,klx ,10-12-2004 ,"V5R14 SP4 - IR 474358 ") // adl_promote -cr 474358A 474358B 474358C
CGMVersionMacroDefine(1232,Draft_EvalAtExtremity                                       ,klx ,10-12-2004 ,"V5R14 SP4 - IR 473291 ") // adl_promote -cr 473291A 473291B 473291C
CGMVersionMacroDefine(1233,Projection_JournalOnMCC                                     ,JHN ,13-12-2004 ,"V5R14 SP4 - pb journal projection quand Merge curve coupling en extremite ") // adl_promote -cr 474626A  474626B  474626C
CGMVersionMacroDefine(1234,Healing_Level14                                             ,JJC ,13-12-2004 ,"V5R14 SP4 - Incompatible Edges; Duplication management ") // detection des points de rebroussement; duplication plus fine pour le Healing Local
CGMVersionMacroDefine(1235,CornerPCrvPCrv_GetCircle                                    ,klx ,13-12-2004 ,"V5R14 SP4 - ODT GSM2DViewSection09 KOSUN + UMR ")
CGMVersionMacroDefine(1236,Parallel_ConnectReport                                      ,klx ,13-12-2004 ,"V5R14 SP4 - bug CATParallelPieceCx2::Report ")
CGMVersionMacroDefine(1237,SplitVolBySkin_OffsetOfPlane                                ,jbx ,17-12-2004 ,"V5R14 SP4 - lie au ri 469575  (PAS de promote) ")
CGMVersionMacroDefine(1238,Linear_MinimumEdgeLengthCleanCrv                            ,AOV ,17-12-2004 ,"V5R14 SP4 - RI 475659 creation de line ")
CGMVersionMacroDefine(1239,Rib_Relim_SearchExtrapolVertexOnRCF                         ,fbz ,17-12-2004 ,"V5R14 SP4 - RI 475171 ") // -cr 475171A 475171B 475171C
CGMVersionMacroDefine(1240,Parting_TolForTypeOfCutEdges                                ,FBZ ,17-12-2004 ,"V5R14 SP4 - RI 475347 ") // Activation immédiate avec -cr 475347A 475347B 475347C
CGMVersionMacroDefine(1241,UnFoldedAero_FindNearestEdge                                ,OAU ,20-12-2004 ,"V5R14 SP4 - Rattrap topologique lors de la mise a plat d un point. ") // adl_promote -cr A0476100 B0476100 C0476100


//=========================================================================================================
// V5R14 SP5
//=========================================================================================================
CGMVersionMacroDefine(1250,Unfold_ImproveCrvTransfer                                   ,SUH ,24-12-2004 ,"V5R14 SP5 - amelioration transfer de courbe ")
CGMVersionMacroDefine(1251,Sweep_DelayMovingFrameComputation                           ,NLD ,24-12-2004 ,"V5R14 SP5 ")
CGMVersionMacroDefine(1252,Join_WarningOnSharedCells                                   ,JBX ,24-12-2004 ,"V5R14 SP5 - Modification de l\\\'algo de Join (la first pass a la reso est dans le meme operateur) pour permettre la gestion du warning des cellules partagees ")
CGMVersionMacroDefine(1253,CATMathVectorialFunctionX_CorrectionInstabilite             ,EAB ,22-12-2004 ,"V5R14 SP5 - Faire profiter tous les clients d\'une correction de RI. ") // Variable à activer lorsque les migrations client de CATMathVectorialFunctionX seront toutes faites. (new user = CQI)
CGMVersionMacroDefine(1254,Shell_BooleanPosVolOptimLevel2                              ,DPS ,22-12-2004 ,"V5R14 SP5 - Shell sur body multi ") // adl_promote -cr 476455A 476455B
CGMVersionMacroDefine(1255,CleanCurve_ConfusionEdges                                   ,HLN ,22-12-2004 ,"V5R14 SP5 - Correction RI472100 TMC ") // ko FIXPARTVERS le 17-12-2004 / cas ParJPos_RI251967_N_T10  OK versionne
CGMVersionMacroDefine(1256,Blend_SameShapeFor_G2G0andG0G2_Profiles                     ,JSX ,22-12-2004 ,"V5R14 SP5 - Bug for PlanarSection in FastG2OptimumBiDirRi ") // promote -cr 476311
CGMVersionMacroDefine(1257,Sweep_IgnoreOutsideEdgePartsIfSweepAccess                   ,NLD ,22-12-2004 ,"V5R14 SP5 - pb d\'orientation stiffener (perte de lien pose sur) ")
CGMVersionMacroDefine(1258,SkinExtrapol_AdjustTrustLevelForFaces                       ,MNJ ,22-12-2004 ,"V5R14 SP5 - RI A0472888 et B0472888 ") // adl_promote -cr A0472888  B0472888
CGMVersionMacroDefine(1259,Offset_NewCollisionTrigger                                  ,MNJ ,22-12-2004 ,"V5R14 SP5 - RI A0409591 ") // adl_promote -cr A0409591
CGMVersionMacroDefine(1260,Projection_DistanceOnMCC                                    ,JHN ,22-12-2004 ,"V5R14 SP5 - Distance sur les edges dans la projection non calculee ") // liee au RI 473981. Mais cette correction n\'est pas suffisante
CGMVersionMacroDefine(1261,Sweep_C0TreatmentForExplicitSpineV2                         ,NLD ,22-12-2004 ,"V5R14 SP5 - ri476108 ") // enrichissement traitement sweep c0   au cas spine3d equivalente guide2d
CGMVersionMacroDefine(1262,PCurveOffset_ModifForAutoFillet_2                           ,CQI ,22-12-2004 ,"V5R14 SP5 - Dev. pour l\'auto ") // Relacher les contraintes G0 pour éviter de générer des surf. biss. twistées
CGMVersionMacroDefine(1263,Rib_Relim_CommonSurfaceForChamfer                           ,FBZ ,24-12-2004 ,"V5R14 SP5 - RI 476136 ") // -cr 476136A 476136B 476136C
CGMVersionMacroDefine(1264,Draft_Position_PartingVsNeutral                             ,PFV ,24-12-2004 ,"V5R14 SP5 - RI0476027 ") // Prise en compte de la position du parting / au neutral pour le calcul de son orientation // -cr A0476027 B0476027 C0476027
CGMVersionMacroDefine(1265,SweepCircleCrvSurInitSystem_NewFunctionF                    ,CQI ,07-01-2005 ,"V5R14 SP5 - RI471569 : renforcer les chances de succes de CATMathSystemXY::DSolve grace a une fonctionnelle aux prop. interessantes ") // adl_promote -cr 0471569A 0471569B
CGMVersionMacroDefine(1266,Join_SharedCells_CorrectionShellAndJournal                  ,jbx ,07-01-2005 ,"V5R14 SP5 - Tolerance pour validite face input + Recherche face ancetre dans le journal si 2 passes ")
CGMVersionMacroDefine(1267,Offset_WorkPlaneInternalCase                                ,MNJ ,07-01-2005 ,"V5R14 SP5 - RI A0473654 ") // adl_promote -cr A0473654 B0473654 A0473664 B0473664
CGMVersionMacroDefine(1268,Prism_OpenProfile_AutoIntersectionCheck                     ,fds ,07-01-2005 ,"V5R14 SP5 - RI477961A ")
CGMVersionMacroDefine(1269,Regul_NewFill                                               ,FBZ ,07-01-2005 ,"V5R14 SP5 ")
CGMVersionMacroDefine(1270,DistanceCrvSur_TabCyl_SpecificAlgorithm                     ,CQI ,07-01-2005 ,"V5R14 SP5 - RI478209 : traitement plus robuste pour les tab. cyl. ") // adl_promote -cr 478209A 478209B 478209C
CGMVersionMacroDefine(1271,UnFoldedAero_MassPropertiesLength                           ,OAU ,10-01-2005 ,"V5R14 SP5 - promote ") // CalcLength Deprecated switcher sur CATDynCreateMassProperties3D
CGMVersionMacroDefine(1272,PCurvesOffset_SimplifiedEdgeCurve                           ,CQI ,10-01-2005 ,"V5R14 SP5 - Convergence modeles DCS pour DPS ") // Resoudre les problemes d\'extrapolation des surf. biss. dus a des EdgeCurves fats
CGMVersionMacroDefine(1273,Sweep_TwistDetection_PointedSurfaceTolerance                ,JSX ,10-01-2005 ,"V5R14 SP5 - Pb Client : Detection Instable de twist sur des cas semblabes ") // promote -cr a478213 b478213 c478213
CGMVersionMacroDefine(1274,Loft_TangProfile_ReMapProfileOn_0_1_Segment                 ,jsx ,10-01-2005 ,"V5R14 SP5 - recalage complet du profil et non des seuls points en contact avec les guides ") // promote -cr a468914
CGMVersionMacroDefine(1275,Extrapol_Blend_IterateOnSmoothEdgesForTangentMode           ,JSX ,10-01-2005 ,"V5R14 SP5 - Recherche, autour des extremites du wire, de la premiere arete vive sur le shell ") // Promote -cr 473647
CGMVersionMacroDefine(1276,Loft_ComputeLocalTangWithResThreshold                       ,JSX ,10-01-2005 ,"V5R14 SP5 - Tangente fausse dans le repere locale : Isopare en S ") // promote : NON : mais proactif
CGMVersionMacroDefine(1277,Sweep_ViewingDirection_MinimumDiscretization                ,NLD ,10-01-2005 ,"V5R14 SP5 ") // -cr 477680a 477680b
CGMVersionMacroDefine(1278,Sweep_ShiftCuttingVertices                                  ,NLD ,10-01-2005 ,"V5R14 SP5 ") // -cr 478480a 4784480b
CGMVersionMacroDefine(1279,RegulOffset_NoRegulForFaceNextToExactDegenSurf              ,MNJ ,10-01-2005 ,"V5R14 SP5 - lie au RI A0478163 ")
CGMVersionMacroDefine(1280,ApproxNetwork_Level2                                        ,PMG ,10-01-2005 ,"V5R14 SP5 - RIA0476827 ") // -cr A0476827 B0476827 C0476827
CGMVersionMacroDefine(1281,POECCreationOptimisation                                    ,ice ,14-01-2005 ,"V5R14 SP5 - optimisation de la creation des POEC sur MergedCurve ")
CGMVersionMacroDefine(1282,Connect_AcceptNonCompleteSet_1                              ,FCX ,14-01-2005 ,"V5R14 SP5 - RI + uniformisation des connects ") // -cr 477815B 477815C 477815D
CGMVersionMacroDefine(1283,Prism_Relimitation_Surfacic_Orientation                     ,fds ,14-01-2005 ,"V5R14 SP5 - Meilleure stabilisation de la relimitation surfacique du prisme ")
CGMVersionMacroDefine(1284,Offset_AnomalyPropagationModeForCollision                   ,LAP ,14-01-2005 ,"V5R14 SP5 - Ri 427389 ") // adl_promote -cr 427389B
CGMVersionMacroDefine(1285,AddRemoveDraftOnCone                                        ,PFV ,14-01-2005 ,"V5R14 SP5 - RI 0478641 ") // Activation immediate
CGMVersionMacroDefine(1286,Connect_DefaultMarchingRepartition                          ,FCX ,17-01-2005 ,"V5R14 SP5 - Uniformisation des parametres de cheminement de connect ")
CGMVersionMacroDefine(1288,Offset_BisectorOnWeaklySharpLevel2                          ,DPS ,17-01-2005 ,"V5R14 SP5 - vieux RI TMC clos SUG ") // cas limite d\'edges weakly sharp
CGMVersionMacroDefine(1289,Trim_SearchModifyOrderForSimplifiedFaces                    ,jbx ,17-01-2005 ,"V5R14 SP5 - Modif du journal du trim ") // -cr A0477827  B0477827 C0477827
CGMVersionMacroDefine(1290,GeodesicParallel_ReportInit                                 ,klx ,17-01-2005 ,"V5R14 SP5 - RI 468785 ") // -cr 468785A 468785B
CGMVersionMacroDefine(1291,CGM_Versionning_ProjectionCrvSurDir_ArrangeIndex            ,obh ,17-01-2005 ,"V5R14 SP5 - RI 478217 ") // -cr 478217A 478217B
CGMVersionMacroDefine(1292,Connect_StablePointingDeformationCrvSur                     ,FCX ,21-01-2005 ,"V5R14 SP5 - Amelioration de la deformation en pointe ")
CGMVersionMacroDefine(1293,Loft_RelimitationUsingProfilePositioning                    ,NLD ,21-01-2005 ,"V5R14 SP5 - meilleure strategie de relimitation par les profils sur les cas difficiles ")
CGMVersionMacroDefine(1294,Sweep_Discontinuity_Correction                              ,fds ,21-01-2005 ,"V5R14 SP5 - RI479227A ")
//CGMVersionMacroDefine(1295,Tess_0001                                                   ,tpd ,21-01-2005 ,"V5R14 SP5 - ri ")
CGMVersionMacroDefine(1296,ExtrusionRecogniser_OffsetValue_Fixed                       ,PFV ,21-01-2005 ,"V5R14 SP5 - bug distance offset parallele pour algorithme draft vrai multi rubans ") // activation immediate
CGMVersionMacroDefine(1297,DraftBothSides_NewInterpolOption                            ,PKC ,24-01-2005 ,"V5R14 SP5 - dev qualite ")
CGMVersionMacroDefine(1298,ExtrapWireOnShell_CheckAIOnlyOnExtrapol                     ,AOV ,24-01-2005 ,"V5R14 SP5 - RI ")
CGMVersionMacroDefine(1299,Sweep_OrderingWithNoDefaultOrientationIfUnknownOrder        ,NLD ,24-01-2005 ,"V5R14 SP5 - RI479748 ") // -cr 479748a,b
CGMVersionMacroDefine(1300,IncludeEndNuplet_ConfusionSurfaces                          ,PFV ,28-01-2005 ,"V5R14 SP5 - RI0479776 ") // Activation immediate
//CGMVersionMacroDefine(1301,RollingEdge_StartHomotopy                                   ,FCX ,28-01-2005 ,"V5R14 SP5 - Amelioration du positionnement de l\'init du RollingEdgeFillet ")
//CGMVersionMacroDefine(1302,ConstantFillet_CanonicalTwist                               ,FCX ,28-01-2005 ,"V5R14 SP5 - RI 480403 ") // -cr 480403A 480403B 480403C
//CGMVersionMacroDefine(1303,Fillet_DuplicationWithNoFreeEnd                             ,jma ,31-01-2005 ,"V5R14 SP5 - RI 480245 ") // activation apartir de vendredi 28/01/2005
CGMVersionMacroDefine(1304,DistanceMin_VertexFaceDist                                  ,fds ,31-01-2005 ,"V5R14 SP5 - RI4766688 ")
//CGMVersionMacroDefine(1305,Projection_JoinCE                                           ,JHN ,31-01-2005 ,"V5R14 SP5 - stabilisation orientation projection ") // OK
//CGMVersionMacroDefine(1306,Fillet_SmoothRelim_R15GA                                    ,NDN ,31-01-2005 ,"V5R14 SP5 - RI ") // A0457029
//CGMVersionMacroDefine(1307,Fillet_ContinuePropagAfterConfusion                         ,fdl ,31-01-2005 ,"V5R14 SP5 - amelioration propagation ruban ")
CGMVersionMacroDefine(1308,Offset_DeadFrepPropagation                                  ,LAP ,31-01-2005 ,"V5R14 SP5 - Ri 427390B ") // adl_promote -cr 427390B
CGMVersionMacroDefine(1309,Sweep_CanonicSurfacesDetectionTolerance                     ,nld ,31-01-2005 ,"V5R14 SP5 - cone non detecte dans scenario sheetmetal ") // ********** ACTIVATION DIRECTE ********
CGMVersionMacroDefine(1310,Relim_InhibitGapInVertexOnTrackConnection                   ,ase ,31-01-2005 ,"V5R14 SP5 - RI externe ") // activation immediate (R14 SP5)
CGMVersionMacroDefine(1311,Fillet_SAConnectivityIndependentSelection                   ,JHG ,31-01-2005 ,"V5R14 SP5 - Ri479418 ") // ACTIVATION IMMEDIATE - correction livree activee vendredi 28/01
CGMVersionMacroDefine(1312,Chamfer_CheckPiece                                          ,FCX ,04-02-2005 ,"V5R14 SP5 - RI 458722 ") // -cr 458722A
//CGMVersionMacroDefine(1313,DraftRibbon_WirePreviewCorrection                           ,ase ,04-02-2005 ,"V5R14 SP5 - RI ") // activation immediate
//CGMVersionMacroDefine(1314,Corner_ThrowOfError_NewMethod                               ,ALV ,04-02-2005 ,"V5R14 SP5 - Throw d\'erreur si et seulement si on n\'a pas de solution dans les autres orientations ")
CGMVersionMacroDefine(1315,Tess_0001                                                   ,tpd ,04-02-2005 ,"V5R14 SP5 - ri ")
CGMVersionMacroDefine(1316,Fillet_DuplicationWithNoFreeEnd                             ,jma ,04-02-2005 ,"V5R14 SP5 - correction des 2 odt livree en meme temps par fixpart1 ") // -cr 480245A 480245B 480245C
//CGMVersionMacroDefine(1317,Fillet_SmoothRelim_R15GA                                    ,NDN ,04-02-2005 ,"V5R14 SP5 ") // -cr A0457029
//CGMVersionMacroDefine(1318,Fillet_ContinuePropagAfterConfusion                         ,fdl ,04-02-2005 ,"V5R14 SP5 - correction  odt simultanement par promotion de fixpart1 dans cgmoff ") // -cr A0470524 B0470524
CGMVersionMacroDefine(1319,NewStabilityForBordrerEdges                                 ,JMA ,04-02-2005 ,"V5R14 SP5 - Fillet Selection With faces ") // Activation Immediate
CGMVersionMacroDefine(1320,Extrude_ByLine_ProfileLimits                                ,fds ,04-02-2005 ,"V5R14 SP5 - RI482024A ") // Activation immédiate à partir 04/02
CGMVersionMacroDefine(1321,TritangentFillet_InitializationWithSortedCommonCurve        ,rr  ,04-02-2005 ,"V5R14 SP5 - RI0478574 ") // activation immédiate, svp
CGMVersionMacroDefine(1322,EuclidianParallel_ReversalSingularityTreatment              ,CQI ,04-02-2005 ,"V5R14 SP5 - KO Michelin specifique optimise ") // Stabilisation des retournements du cheminement
CGMVersionMacroDefine(1323,StabilizeWireWireIntersection                               ,ice ,04-02-2005 ,"V5R14 SP5 - Comportement identique entre le 2D et le 3D ")
CGMVersionMacroDefine(1324,HoldCurveCircleFillet_BugInterpol                           ,CQI ,04-02-2005 ,"V5R14 SP5 - RI482329 ") // Probleme de qualite (bug derivee)
CGMVersionMacroDefine(1325,Extrapol_DeploySoftwareConfiguration                        ,JSX ,04-02-2005 ,"V5R14 SP5 - Config a transmettre a l\'operateur geometrique de blend; cas du mode until ") // -cr ri 478794
CGMVersionMacroDefine(1326,Extrapol_NoCatchWithDirectionalEdges2                       ,JSX ,04-02-2005 ,"V5R14 SP5 - Warning inutil  + ratrap des erreurs non topologique : ODT KO GSMXN1.tst GSMExtrapolDIM ") // promote -cr a480992
CGMVersionMacroDefine(1327,Blend_GuideCleanWithinResolution                            ,NLD ,04-02-2005 ,"V5R14 SP5 - (JSX) RI480875 : Blend avec spine : on limite la tol sur les guides lors de l\'appel au sweep ") // blend s\'ecartant des appuis
CGMVersionMacroDefine(1328,Projection_JoinCE                                           ,JHN ,14-02-2005 ,"V5R14 SP5 ") // OK
CGMVersionMacroDefine(1329,Thick_RemoveFaceLevel6                                      ,MNJ ,14-02-2005 ,"V5R14 SP5 - lie au RI A0482901 ")
CGMVersionMacroDefine(1330,Blend_SelectReferenceForMergeCurve                          ,JSX ,14-02-2005 ,"V5R14 SP5 - RI Blend DATUM : Construire les mergedcurve avec l\'iso du blend comme reference ") // -cr 477792a b
CGMVersionMacroDefine(1331,Fillet_SmoothRelim_R15GA                                    ,NDN ,14-02-2005 ,"V5R14 SP5 - relimitation tangente verticale ") // -cr A0457029
CGMVersionMacroDefine(1332,Relim_FreeInit_PropagBeforeComplete                         ,ase ,18-02-2005 ,"V5R14 SP5 - RI ") // activation immediate (R14SP5)
CGMVersionMacroDefine(1333,Fill_NewManagementIntersectionSegment                       ,MPS ,18-02-2005 ,"V5R14 SP5 - RI  482993 ") // adl_promote -cr  A0482993 B0482993 C0482993
CGMVersionMacroDefine(1334,ReorderImpasseDetection                                     ,ice ,18-02-2005 ,"V5R14 SP5 - Meilleure detection des impasses dans IntersectShell ")
CGMVersionMacroDefine(1335,Offset_QualityTolForPCurveGuide                             ,DPS ,18-02-2005 ,"V5R14 SP5 - ajout d\'une nouvelle tolerance pour appeler le SurSurTangent dans l\'offset ") // adl_promote -cr 479853A 479853B
CGMVersionMacroDefine(1336,Corner_ThrowOfError_NewMethod                               ,ALV ,18-02-2005 ,"V5R14 SP5 - Throw d\'erreur si et seulement si on n\'a pas de solution dans les autres orientations ")
CGMVersionMacroDefine(1337,TopModify_MaxGap                                            ,fdn ,18-02-2005 ,"V5R14 SP5 - RI480551Prise en compte du MaxGap des edges curves initiales ") // adl_promote -cr 480551A
CGMVersionMacroDefine(1338,RollingEdge_StabilizeConstraintOnPoint                      ,CQI ,18-02-2005 ,"V5R14 SP5 - RI484211 : Instabilite de la contrainte de retournement en zone de pointe ") // Activation immediate + adl_promote -cr 0484211A 0484211B


//=========================================================================================================
// V5R15 GA
//=========================================================================================================
CGMVersionMacroDefine(1351,Thick_RemoveInvertedFacesByPostPro                          ,MNJ ,24-02-2005 ,"V5R15 GA - RI A0482901 B0482901 ") // adl_promote -cr A0482901 B0482901
CGMVersionMacroDefine(1352,Unfold_ClusterEdgesToTear                                   ,SUH ,24-02-2005 ,"V5R15 GA ")
CGMVersionMacroDefine(1353,Unfold_PositioningDirection                                 ,FDL ,24-02-2005 ,"V5R15 GA - shell unfold : improve positionning direction ")
CGMVersionMacroDefine(1354,InterscetionSurfacePln_StabilizeConstraints                 ,RHA ,24-02-2005 ,"V5R15 GA - RI  A0482608 ") // Adl_promote -cr A0482608 B0482608
CGMVersionMacroDefine(1355,SurSurTg_ReconvergeInits_InputTol                           ,obh ,24-02-2005 ,"V5R15 GA - modele MNJ ")
CGMVersionMacroDefine(1356,Offset_ClashSRepCollisionFilter                             ,DPS ,24-02-2005 ,"V5R15 GA - recherche abusive de collisions entre 2 faces non connexes eloignees => bad result + surcout perfo ") // adl_promote -cr 483598A 483598B
CGMVersionMacroDefine(1357,TrimSew_FaceToReplaceInResult                               ,FBZ ,24-02-2005 ,"V5R15 GA - RI 478405A 478405B ") // promote -cr 0478405A 0478405B
CGMVersionMacroDefine(1358,MarshMallow_CheckLayDown                                    ,PMG ,24-02-2005 ,"V5R15 GA - ri 0484976 ") // -cr 0484976A 0484976B 0484976C
CGMVersionMacroDefine(1359,Fillet_Untwist_UpdateRlmData                                ,JMA ,25-02-2005 ,"V5R15 GA - Correctifs pour SheetMetal AERO (journal) ")
CGMVersionMacroDefine(1360,Sweep_RelimitationUsingTangencyTestAtShiftedPoint           ,NLD ,25-02-2005 ,"V5R15 GA - RI485464 ") // -cr 485464a 485464b 485464c
CGMVersionMacroDefine(1361,Fillet_SmartPointingKeepEdge                                ,rr  ,28-02-2005 ,"V5R15 GA - RI0484691 Boeing ") // Promote -cr 484691A 484691B 484691C 484690A 484690B 484690C
CGMVersionMacroDefine(1362,Fill_NewManagementBigSlopes                                 ,MPS ,28-02-2005 ,"V5R15 GA - RI 482999  (A0482999 et B0482999) ")
CGMVersionMacroDefine(1363,ApproxSurface_CheckDegeneratedSurface                       ,FCX ,28-02-2005 ,"V5R15 GA - RI 485792 ") // -cr 485792A 485792B 485792C 485792D
CGMVersionMacroDefine(1364,SweepVaria_PointInterpolation                               ,JSX ,28-02-2005 ,"V5R15 GA - !!  NIVEAU R15GA et pas R14SP5 et R14SP6 ") // !!  NIVEAU R15GA et pas R14SP5 et R14SP6 -cr RI a447191
CGMVersionMacroDefine(1365,HybridVarOffset_CheckInputBodies3DBox                       ,LAP ,04-03-2005 ,"V5R15 GA - RI 486323ABC ") // adl_promote -cr 486323A 486323B 486323C
CGMVersionMacroDefine(1366,Projection_LevelToMapX                                      ,JHN ,04-03-2005 ,"V5R15 GA - versionning du report de parametre sur la projection ") // lie a la nouvelle projection geometrique
CGMVersionMacroDefine(1367,Fillet_CoarseExtrapolBeforeRelim                            ,JMA ,04-03-2005 ,"V5R15 GA - RI 0485918 ") // activation immediate
CGMVersionMacroDefine(1368,DistanceMin_LittleValue                                     ,JHN ,07-03-2005 ,"V5R15 GA - RI 485782 ") // pour pousser plus loin la precision du calcul
CGMVersionMacroDefine(1369,SupportSpline_JournalOK                                     ,JHN ,07-03-2005 ,"V5R15 GA - correction du journal de spline sur support ") // avoir des journaux de reference dans tous les cas dÓDT
CGMVersionMacroDefine(1370,Draft_StableSupportExtrapol                                 ,ase ,07-03-2005 ,"V5R15 GA - RI ") // -cr 0484407A 0484407B
CGMVersionMacroDefine(1371,TrimSew_FreeRelimInit_AddOrRemoveDetection                  ,ase ,07-03-2005 ,"V5R15 GA - RI 0479551 ") // -cr 0479551B 0479551C


//=========================================================================================================
// V5R15 SP1
//=========================================================================================================
CGMVersionMacroDefine(1381,Fillet_UnTwistR15SP1                                        ,RR  ,11-03-2005 ,"V5R15 SP1 - RI0484453 ") // R15 SP1
CGMVersionMacroDefine(1382,OffsetVar_CheckIsBoundary                                   ,PMG ,11-03-2005 ,"V5R15 SP1 - Pb de contrainte ignoree dans l\'offset variable ") // -cr A0486564 B0486564 C0486564
CGMVersionMacroDefine(1383,CleanCurve_VeryHighCurvature                                ,RNO ,11-03-2005 ,"V5R15 SP1 - Special treatment for curves with very high curvature in the CleanCurveOperator, Help to solve some problems in the parallel operator ")
CGMVersionMacroDefine(1384,ExtrapolG2_ExtrapOnBothExtremities                          ,AOV ,11-03-2005 ,"V5R15 SP1 - correction extrapolation G2 pour dev R16 SheetMetal ") // activation immediate
CGMVersionMacroDefine(1385,TrimShlShl_JournalForDupliFaces                             ,jbx ,14-03-2005 ,"V5R15 SP1 - ri 483252 ")
CGMVersionMacroDefine(1386,DistanceMin_CrvSur_MultipleResult                           ,fds ,14-03-2005 ,"V5R15 SP1 - RI486590A ")
CGMVersionMacroDefine(1387,Simplify_Edges_Keep_IV                                      ,fds ,14-03-2005 ,"V5R15 SP1 - RI482377 ")
CGMVersionMacroDefine(1388,IsPointedSurface_GenericFillet_IrrelevantPoint              ,CQI ,14-03-2005 ,"V5R15 SP1 - RI487541 (CAA) ") // Activation immediate CGMOFF : adl_promote -cr 0487541A 0487541B 0487541C
CGMVersionMacroDefine(1389,Sewing_FlatBodyCheck                                        ,ase ,14-03-2005 ,"V5R15 SP1 - RI ") // activation immediate
CGMVersionMacroDefine(1390,Healing_Level15                                             ,JJC ,18-03-2005 ,"V5R15 SP1 - Stabilisation in AdjustPCurve and BuilderDeform ") // cas des distances 3D et des defauts quasi-nuls
CGMVersionMacroDefine(1391,Parallel_InhibitStabIntersection                            ,AOV ,18-03-2005 ,"V5R15 SP1 - correction pb michelin ")
CGMVersionMacroDefine(1392,Parallel_SolveGapInExtrapolation                            ,AOV ,18-03-2005 ,"V5R15 SP1 - Ri Int 455834 ")
CGMVersionMacroDefine(1393,Corner_CrvPoc_ReorderCurvatureOrient                        ,ALV ,18-03-2005 ,"V5R15 SP1 - curvature orient inversé dans le calcul des corners CrvPoc ")
CGMVersionMacroDefine(1394,OffsetVar_InputTangencyAnalysis                             ,PMG ,18-03-2005 ,"V5R15 SP1 - Leve d\'ambiguite dans les contraintes variables ")
CGMVersionMacroDefine(1395,IntersectionSurSurWithInits_ConvergeInitis_AfterSurSurTg    ,obh ,18-03-2005 ,"V5R15 SP1 - modeles MNJ(Dev C1) ")
CGMVersionMacroDefine(1396,MarshMallow_Level7                                          ,PMG ,18-03-2005 ,"V5R15 SP1 - De nouvelles ameliorations ... ")
CGMVersionMacroDefine(1397,Prism_Filter_Info0_ForEdges                                 ,fds ,18-03-2005 ,"V5R15 SP1 - RI486797 ") // Activation immediate
CGMVersionMacroDefine(1398,Loft_ProfilePositionWithoutGuideV3                          ,NLD ,18-03-2005 ,"V5R15 SP1 - RI488097 ") // activation ASAP; je livre le code le 18/03/05
CGMVersionMacroDefine(1399,EuclidianParallelConstraint_SafeEval                        ,CQI ,18-03-2005 ,"V5R15 SP1 - RI487523 ") // Activation asap (18/03/05)
CGMVersionMacroDefine(1400,IntersectionSurSur_TangentComputation                       ,obh ,18-03-2005 ,"V5R15 SP1 - RI A0487092 ") // activation asap (le 18/03/05)
CGMVersionMacroDefine(1401,Fillet_JournalCleaning                                      ,JMA ,21-03-2005 ,"V5R15 SP1 - Elimination d\'ordres inutiles ") // Activation immediate, s\'il vous plait
CGMVersionMacroDefine(1402,HybridVarOffset_WeaklySharpEdgeError                        ,LAP ,22-03-2005 ,"V5R15 SP1 - Ri 486339ABC + Demande creation ") // adl_promote -cr 486339A 486339B 486339C
CGMVersionMacroDefine(1403,OffsetVar_Level2                                            ,PMG ,25-03-2005 ,"V5R15 SP1 - reduire le nombre d\'edge ouverte ")
CGMVersionMacroDefine(1404,Offset_HealingTopoPostPro                                   ,DPS ,25-03-2005 ,"V5R15 SP1 - reparer par le Healing ce qui est degrade par l\'Offset (> 10 reso) ") // qualite offset + driver le Healing topo avant deploiement plus large
CGMVersionMacroDefine(1405,IntersectionCrvCrv_Helix                                    ,obh ,25-03-2005 ,"V5R15 SP1 - RI interne ")
CGMVersionMacroDefine(1406,Spline_NearPoints                                           ,JHN ,29-03-2005 ,"V5R15 SP1 - RI 488594 ") // erreur quand deux points successifs de la spline sont plus proches que la resolution
CGMVersionMacroDefine(1407,Simplify_Cone_NotSimilitude                                 ,fds ,29-03-2005 ,"V5R15 SP1 - RI486076A ")
CGMVersionMacroDefine(1408,CreateValidBodyAxisSystem_AxisOriginMatchingLines           ,BOM ,01-04-2005 ,"V5R15 SP1 - Lines creation from axis systems should have its origin matching the axis origin for a better use. ") // Revealed in IR 0482724.
CGMVersionMacroDefine(1409,Rib_Relim_ClosedSurfaceLoopExtensionJournal                 ,ase ,01-04-2005 ,"V5R15 SP1 - RI 0489197 ") // activation immediate
CGMVersionMacroDefine(1410,BlendRibbon_Hermetisation_4                                 ,FDL ,04-04-2005 ,"V5R15 SP1 - fillet tolerant modeling drop 3 ")
//CGMVersionMacroDefine(1411,ConstantFillet_InterpolMaxDepth                             ,klx ,04-04-2005 ,"V5R15 SP1 - RI 487788 ") // activ immediate possible, -cr 487788A 487788B, ODTKO = nb patch
CGMVersionMacroDefine(1412,ProjectionPtCrv_MappingOnPlane                              ,obh ,04-04-2005 ,"V5R15 SP1 - RI0489377 ") // adl_promote -cr B0489377 A0489377
CGMVersionMacroDefine(1413,TopRibSewing_ErrorForOnlyUnknownFaces                       ,AJD ,04-04-2005 ,"V5R15 SP1 - Invalid sewing result ")
CGMVersionMacroDefine(1414,DistMinCrvCrv_TryLocalMin                                   ,CQI ,08-04-2005 ,"V5R15 SP1 - RI489548 (CAA) ") // adl_promote -cr 0489548A 0489548B 0489548C 0489548D
CGMVersionMacroDefine(1415,IntersectionCrvSur_TabCyl                                   ,sty ,08-04-2005 ,"V5R15 SP1 - RI490541 ") // -cr 490541B 490541C 490541D
CGMVersionMacroDefine(1416,ProjectCrvSurMapX_BestReconverge                            ,CQI ,08-04-2005 ,"V5R15 SP1 - RI490620 ") // adl_promote -cr 490620B 490620C 490620D
CGMVersionMacroDefine(1417,Fillet_PointingBlockedSphere                                ,PKC ,08-04-2005 ,"V5R15 SP1 - good reason ")
CGMVersionMacroDefine(1418,TriTangentFillet_InitIndex                                  ,PKC ,08-04-2005 ,"V5R15 SP1 - RI ")
CGMVersionMacroDefine(1419,ChamferInitSampling                                         ,PKC ,08-04-2005 ,"V5R15 SP1 - RI ")
CGMVersionMacroDefine(1420,ConstantFillet_InterpolMaxDepth                             ,klx ,11-04-2005 ,"V5R15 SP1 - IR 487788 ") // -cr 487788A 487788B, ODTKO = nb patch
CGMVersionMacroDefine(1421,Offset_RescueForPointedSurface                              ,MNJ ,11-04-2005 ,"V5R15 SP1 - RIs 489512 A, B et C ") // promote -cr A0489512 B0489512 C0489512
CGMVersionMacroDefine(1422,Thick_BulldozerForAll                                       ,DPS ,11-04-2005 ,"V5R15 SP1 - empecher la creation de micro volume twiste dans le Shell non isotopologique ") // adl_promote -cr 490004A 490004B 490004C 490635A 490635B
CGMVersionMacroDefine(1423,Bump_Level6                                                 ,PMG ,11-04-2005 ,"V5R15 SP1 - Reduire les sur ") // -cr A0489494 B0489494 C0489494
CGMVersionMacroDefine(1424,IntersectionTriSur_Reconverge                               ,sty ,15-04-2005 ,"V5R15 SP1 - RI ")
CGMVersionMacroDefine(1425,Fillet_StablePointingDeformationTolPOEC                     ,FCX ,15-04-2005 ,"V5R15 SP1 - Deformation en pointe ")
CGMVersionMacroDefine(1426,Fillet_StablePointingDeformationMoveObjective               ,FCX ,15-04-2005 ,"V5R15 SP1 - Amelioration de la deformation en pointe ")
CGMVersionMacroDefine(1427,RibSweep_EnhancedSignature                                  ,FDL ,15-04-2005 ,"V5R15 SP1 - enhancement in sweep wire skin (AJD) ") // -cr A0489284, B0489284, C0489284
CGMVersionMacroDefine(1428,Stable_Infini_Intersection                                  ,RHA ,15-04-2005 ,"V5R15 SP1 - RI EXT ") // Activation asap le 15/04
CGMVersionMacroDefine(1429,Sewing_KeepAbsorptionOrder                                  ,ice ,15-04-2005 ,"V5R15 SP1 - pour SheetMetal ")
CGMVersionMacroDefine(1430,MostContinuous_BestIntCurveRecovery                         ,HLN ,15-04-2005 ,"V5R15 SP1 - RI490151 A B C ")
CGMVersionMacroDefine(1431,Relim_MultipleSolFilterForIsotopInit                        ,ase ,15-04-2005 ,"V5R15 SP1 - RI0491373 ") // activation immediate, adl_promote -cr 0491373A 0491373B 0491373C 0491373D
CGMVersionMacroDefine(1432,SweepSegment_InitFilter                                     ,PKC ,15-04-2005 ,"V5R15 SP1 - RI EXT ") // Asap sans passer par FIXPARTVERS
//CGMVersionMacroDefine(1433,Fillet_AlwaysExtrapol20Percent_TWO                          ,JMA ,29-04-2005 ,"V5R15 SP1 - (2 kos corrige, livres le 22/04 : CGMReplay_FilletMultiRibbon_CD,CGMTest_NewTopoRIDraftAngleVariable_Task1577_N1) ") // -cr 488703A  488703B  488703C // debranche le 02-05-05
//CGMVersionMacroDefine(1434,Parallel_CheckExtremitiesAfterTrim                          ,AOV ,22-04-2005 ,"V5R15 SP1 - check sur les deux extrmites du wire apres trim ") // KO michelin//debranche PB PERFO
CGMVersionMacroDefine(1435,ExtrapUpTo_CircleTreatment                                  ,AOV ,22-04-2005 ,"V5R15 SP1 - correction Ri 455332 & 455334 extrapolation 3D en courbure up ")
CGMVersionMacroDefine(1436,System6x6s_SymetricNorm                                     ,CQI ,22-04-2005 ,"V5R15 SP1 - Stabilisation Homotopy3Sur (permutation des entrees) ")
CGMVersionMacroDefine(1437,BitangentLine_SmartStabilization                            ,ALV ,22-04-2005 ,"V5R15 SP1 - Stabilisation des lignes bitangentes a l\'aide d\'un nouveau GetResult! ")
CGMVersionMacroDefine(1438,ExtrapG2OfWire_Homotopy                                     ,AOV ,22-04-2005 ,"V5R15 SP1 - dvt R16 extrapolation upto plan+correction RI SUG ")
CGMVersionMacroDefine(1439,SimilarCurve_OrientTgtInWire                                ,AOV ,22-04-2005 ,"V5R15 SP1 - correction bug orientation tangente ") // activation immediate
CGMVersionMacroDefine(1440,TopShellOrientation_Canonic                                 ,fdn ,25-04-2005 ,"V5R15 SP1 - operateur CATTopShellOrientation avec conservation de canoniques ")
CGMVersionMacroDefine(1441,PolarExtremum_DirectionCheck                                ,fds ,29-04-2005 ,"V5R15 SP1 - RI 0491455A ") // -cr 0491455A
CGMVersionMacroDefine(1442,Ribbon_UpdateCutting_MixedVertexEdgeCase                    ,ase ,29-04-2005 ,"V5R15 SP1 - RI 0492194 ") // activation immediate, adl_promote -cr 0492194B 0492194C 0492194D


//=========================================================================================================
// V5R15 SP2
//=========================================================================================================
CGMVersionMacroDefine(1451,DistancePlnSur_SafeRun                                      ,CQI ,04-05-2005 ,"V5R15 SP2 - RI492047 REG ") // -cr A0492047 B0492047 C0492047
CGMVersionMacroDefine(1452,Offset_EliminateMicroFatEdges                               ,DPS ,09-05-2005 ,"V5R15 SP2 - elimination des micro edges fat non isotopologiques ") // convergence de l\'Offset pour la migration MergeCurve -> IntCurve
CGMVersionMacroDefine(1453,HomotopyCrvSur_AllowLargeGap                                ,CQI ,04-05-2005 ,"V5R15 SP2 - HomotopyCrvSur : gestion correcte extrapol manager ")
CGMVersionMacroDefine(1454,CleanCurve_NewComputeDeformation                            ,RNO ,13-05-2005 ,"V5R15 SP2 - improving performance and correcting minor bugs ")
CGMVersionMacroDefine(1455,Fillet_NewNotches_One                                       ,JMA ,13-05-2005 ,"V5R15 SP2 - Ri 483952 et autres ") // activation d\'une partie du code traitant les rubans avec encoches
CGMVersionMacroDefine(1456,Extrude_ByLine_Box3DTo2D                                    ,alv ,13-05-2005 ,"V5R15 SP2 - utilisation des 8 sommets de la box3D au lieux des 2 extrémités lors d\'une projection sur un plan ")
CGMVersionMacroDefine(1457,BitangentLine_ImproveIndexStabilization                     ,ALV ,13-05-2005 ,"V5R15 SP2 - Stabilisation de l\'index par signature pour les lines bitangentes ") // activation immediate le 13 mai
CGMVersionMacroDefine(1458,Parallel_Hermetisation                                      ,FDN ,13-05-2005 ,"V5R15 SP2 - activation demandee par AOV/REN ") // activation immediate le 13 mai
CGMVersionMacroDefine(1459,IntersectionSurSurWithInits_InclusionCrvParam               ,sty ,13-05-2005 ,"V5R15 SP2 - perfo ") // ODT Sheet Metal Ko Rel// activation immediate le 13 mai
CGMVersionMacroDefine(1460,Projection_DegDeg                                           ,jhn ,16-05-2005 ,"V5R15 SP2 - projection : point rend un point ") // correction bug revele par  nouvelle projection
CGMVersionMacroDefine(1461,LayDownVxOnShell_New                                        ,JHN ,16-05-2005 ,"V5R15 SP2 - posage de vertex sur shell nouveau et performant ") // nouvel algo
CGMVersionMacroDefine(1462,HLR_492974InterNodeConfusion                                ,tpg ,16-05-2005 ,"V5R15 SP2 - traitement confusion node intersection ") // RI492974
CGMVersionMacroDefine(1463,Fillet_UnTwistR15SP2                                        ,RR  ,16-05-2005 ,"V5R15 SP2 - Robustesse ")
CGMVersionMacroDefine(1464,Ribbon_ComplFaceEdgeLocationChange                          ,ase ,20-05-2005 ,"V5R15 SP2 - RI ")
CGMVersionMacroDefine(1465,Prism_Until_TopologySharing                                 ,fds ,20-05-2005 ,"V5R15 SP2 - RI494242A ") // Activation immediate
CGMVersionMacroDefine(1466,RollingEdgeCrvPln_MultiConstraints                          ,CQI ,20-05-2005 ,"V5R15 SP2 - RI494624 ") // -cr A0494624 B0494624 // activation immediate le 20 mai
CGMVersionMacroDefine(1467,Chamfer_InitIndex                                           ,pkc ,20-05-2005 ,"V5R15 SP2 - RI ext ") // -cr 494925B 494925C 494925D // activation immediate le 20 mai
CGMVersionMacroDefine(1468,AnalysisPtSurGen_RestrictDomain                             ,PKC ,20-05-2005 ,"V5R15 SP2 - optimisation perfo ") // activation immediate le 20 mai
CGMVersionMacroDefine(1469,DiscoVol_OptimizeExport                                     ,ice ,23-05-2005 ,"V5R15 SP2 - optimisation de l\'export de volumes dans le booleen ")
CGMVersionMacroDefine(1470,Offset_RobustX2SInitSelection                               ,DPS ,23-05-2005 ,"V5R15 SP2 - stabilisation du choix des inits X2S en cas de traversee de fermeture cylindrique ") // adl_promote -cr 493950A 493950B
CGMVersionMacroDefine(1471,Ribbon_UpdateEndVertexOnTrack                               ,AJD ,23-05-2005 ,"V5R15 SP2 - RI0492440 ") // FIX for sweep IR 0492440
CGMVersionMacroDefine(1472,Fillet_AlwaysExtrapol20Percent_TWO                          ,JMA ,23-05-2005 ,"V5R15 SP2 - RI ") // -cr 488703A  488703B  488703C
CGMVersionMacroDefine(1473,Fillet_NewCriterionForPunch                                 ,jma ,27-05-2005 ,"V5R15 SP2 - RI 494847 ") // -cr 494847B,C,D   activation immediate demandee
CGMVersionMacroDefine(1474,IntersectionCrvSur_ChooseExtremity                          ,sty ,27-05-2005 ,"V5R15 SP2 - stabilisation ")
CGMVersionMacroDefine(1475,Rib_PropagCoarseEnhancement_OutsideNeutralDraft_II          ,PFV ,27-05-2005 ,"V5R15 SP2 - RI A0488901 B0488901 ") // adl_promote -cr A0488901 B0488901
CGMVersionMacroDefine(1476,Relim_Completion_ExtrapolSharpEdgeCurve                     ,ase ,27-05-2005 ,"V5R15 SP2 - RI ") // activation immediate
CGMVersionMacroDefine(1477,ImplicitSpine_GeomRuleOnCircle                              ,CCK ,27-05-2005 ,"V5R15 SP2 - pour satisfaire des regles de validite des cercles ") // activation immediate
CGMVersionMacroDefine(1478,Offset_KeepDirSurfOnSuperEdgeBoundary                       ,DPS ,27-05-2005 ,"V5R15 SP2 - robustesse traitement des bords vifs dans l\'offset ") // (activation immédiate le 27 dans OFF) adl_promote -cr 494991A  494991B 494991C
CGMVersionMacroDefine(1479,Fillet_SelfIntersectNoDestroyVertexOnInUseVertex            ,JHG ,27-05-2005 ,"V5R15 SP2 - Ri493972 ") // activation immediate le 27 dans OFF
CGMVersionMacroDefine(1480,UnFoldedAero_QualityImprovementMarching                     ,OAU ,30-05-2005 ,"V5R15 SP2 - DEV R16 ") // Marching algorithm integration in UnFoldedAero Operator.
CGMVersionMacroDefine(1481,UnFoldedAero_QualityImprovementNewInterpolation             ,OAU ,30-05-2005 ,"V5R15 SP2 - DEV R16 ") // Pre-interpolation process in UnFoldedAero Operator.
CGMVersionMacroDefine(1482,WiresOnShell_LogMultipleProjectionOnSameEdge                ,ice ,30-05-2005 ,"V5R15 SP2 - journal de la projection d\'aretes differentes sur une meme arete de shell ")
CGMVersionMacroDefine(1483,Simplify_NonManifoldEdges_No                                ,fds ,31-05-2005 ,"V5R15 SP2 - Pb ancien revelé à corriger ODT CATShfProduction.tst cassé suite à activation level 1459 ") // Activation immédiate
//CGMVersionMacroDefine(1484,Fill_PowerFillLevel10                                       ,mps ,03-06-2005 ,"V5R15 SP2 - A0491938 B0491938 C0491938 ")
CGMVersionMacroDefine(1485,OffsetVar_HealingMaxThresold                                ,PMG ,03-06-2005 ,"V5R15 SP2 - Introduction d\'un angle max de correction. ") // -cr A0495008 B0495008 C0495008
//CGMVersionMacroDefine(1486,Intersect_CloseScarOnFreeEdge                               ,ice ,03-06-2005 ,"V5R15 SP2 ")
CGMVersionMacroDefine(1487,ThickSurface_OneStepVolumeLevel1                            ,MNJ ,03-06-2005 ,"V5R15 SP2 - convergence nouveau ThickSurface ")
CGMVersionMacroDefine(1488,SkinExtrapol_SimilarCurveLevel1                             ,MNJ ,03-06-2005 ,"V5R15 SP2 - dvp similar curve ")
CGMVersionMacroDefine(1489,HLR_NullDotLoop                                             ,TPG ,03-06-2005 ,"V5R15 SP2 - RI496018 ") // calcul de silhouette sur loop a dot nul
CGMVersionMacroDefine(1490,HLR_ConnectSilhInsideLoop                                   ,TPG ,03-06-2005 ,"V5R15 SP2 - RI496467 ") // Calcul de silhouette a l\'interieur d\'une loop
CGMVersionMacroDefine(1491,Loft_ProfileComb_NormeLaw_ForDoubleGuidePoint               ,JSX ,10-06-2005 ,"V5R15 SP2 - Norme nulle auparavant: Surface biscornue au dÃ©but ") // promote -cr a493107 b493107
CGMVersionMacroDefine(1492,Extrapol_CheckNegativeLengths                               ,JSX ,10-06-2005 ,"V5R15 SP2 - Result is illogical. ") // promote -cr a493401 b493401
CGMVersionMacroDefine(1493,Sweep_NormalChoiceOnSharpEdgeV1                             ,NLD ,10-06-2005 ,"V5R15 SP2 - RI496647. choix meilleure normale sur arete vive ") // -cr 496647a 496647b 496647c
CGMVersionMacroDefine(1494,Corner_TriTgt_RedondancyAndNumCell                          ,ALV ,10-06-2005 ,"V5R15 SP2 - Correction d\'un bug impactant le calcul des solutions redondantes(Numcell inversé) RI0496871 + pb journal RI0494348 ")


//=========================================================================================================
// V5R15 SP3
//=========================================================================================================
CGMVersionMacroDefine(1500,MarshMallow_Level8                                          ,PMG ,17-06-2005 ,"V5R15 SP3 - Meilleur gestion des discontinuites G1 & G2 ")
CGMVersionMacroDefine(1501,Fillet_NewNotches_Two                                       ,JMA ,17-06-2005 ,"V5R15 SP3 ") // Treatement of closed ribbon : to be activated after the closure of CXR15SP2
CGMVersionMacroDefine(1502,InclusionAndConfusion_AddEpsToTol                           ,CQI ,17-06-2005 ,"V5R15 SP3 - RI496138 KO AIX ") // Take account of a numerical margin for tolerance to limit instabilities along OS
CGMVersionMacroDefine(1503,IntersectionLineSur_AdjustEpsSol                            ,CQI ,17-06-2005 ,"V5R15 SP3 - RI497890 ") // Adjust EpsSol, and take a less restrictive AbsErr for DSolve (x,y)
CGMVersionMacroDefine(1504,HLR_ContactThinPad                                          ,TPG ,17-06-2005 ,"V5R15 SP3 - RI498462 & RI498618 ") // cas pad mince en contact
CGMVersionMacroDefine(1505,Parallel_SwitchOnDegenerate                                 ,REN/AOV,17-06-2005 ,"V5R15 SP3 - fix non symmetric behaviour of parallel ribbon ")
CGMVersionMacroDefine(1506,Parallel_SuppressInvalidDomain                              ,AOV ,17-06-2005 ,"V5R15 SP3 - correction RI int 488824&474297 ")
//CGMVersionMacroDefine(1507,CATIdenticalSurSur_Correction_Cylinder                      ,obh ,17-06-2005 ,"V5R15 SP3 - RI0497440 ") // adl_promote -cr RIA0497440 RIB0497440
CGMVersionMacroDefine(1508,Offset_MultiFacesSpecLim                                    ,DPS ,17-06-2005 ,"V5R15 SP3 - stabilisation calcul  boite surfacique qq ordre des faces meme support ") // stabilisation ODT CATSpdTestXFormRec005
CGMVersionMacroDefine(1509,ExtrapolAndReconvergeSharpCrvSur_NewRun                     ,CQI ,17-06-2005 ,"V5R15 SP3 - Refonte pour activation variables SurSurTg ") // Stabilisation KO TestShell_138
CGMVersionMacroDefine(1510,Fillet_UnTwistR15SP3                                        ,rr  ,17-06-2005 ,"V5R15 SP3 - RI. Activation immédiate. Livrer dans CGMOFF sur premiere collecte R15SP3. ") // Fillet UnTwist. Activation immédiate. Livrer dans CGMOFF sur premiere collecte R15SP3.
CGMVersionMacroDefine(1511,SurSurResultCurve_Check3DCurvature                          ,FCX ,17-06-2005 ,"V5R15 SP3 - RI MNT ") // ACTIVATION IMMEDIATE
CGMVersionMacroDefine(1512,Relim_BadAndBestCandidate                                   ,PRL ,21-06-2005 ,"V5R15 SP3 - Nouveau choix de completion de relimitation ") // Activation immediate [R15SP3]
CGMVersionMacroDefine(1513,Draft_Junctions_NeutralEqParting                            ,PFV ,21-06-2005 ,"V5R15 SP3 - RI 0499031: export des junctions dans les cas middle neutral=parting ") // Activation immediate
CGMVersionMacroDefine(1514,Intersect_CloseScarOnFreeEdge                               ,ice ,24-06-2005 ,"V5R15 SP3 ")
CGMVersionMacroDefine(1515,ConstantFillet_AcceptNonCompleteSet                         ,PKC ,24-06-2005 ,"V5R15 SP3 - RI fillet ")
CGMVersionMacroDefine(1516,SkinExtrapol_SolveButterflyConfig                           ,MNJ ,24-06-2005 ,"V5R15 SP3 - RI 0498961 A, B & C ") // adl_promote -cr A0498961 B0498961 C0498961
CGMVersionMacroDefine(1517,HLR_CheckVisibilityPointSedge                               ,TPG ,24-06-2005 ,"V5R15 SP3 - RI499149 ") // Point hidden by Edge
CGMVersionMacroDefine(1518,HLR_OccludedNode                                            ,TPG ,24-06-2005 ,"V5R15 SP3 - RI498317 ")
CGMVersionMacroDefine(1519,SurSurTg_Offset_New_Interface                               ,OBH ,24-06-2005 ,"V5R15 SP3 - SurSur tangent dans l\'Offset, gerant les cas d\'extrapolation ")
CGMVersionMacroDefine(1520,Offset_XSurTgPCGuideInExtrapolContext                       ,DPS ,24-06-2005 ,"V5R15 SP3 - stabilisation  FadingEdges en extrapolation [convergence C2 + ODTs a stabiliser] ") // adl_promote -cr 498208A 498208B 466085A
CGMVersionMacroDefine(1521,IntersectionSurSur_InterpolMaxDepth2                        ,klx ,24-06-2005 ,"V5R15 SP3 - RI 495204 ") // ACTIV IMMEDIATE / -cr deja fait
CGMVersionMacroDefine(1522,IntersectionPCrvPCrv_BadParametrized_Stabilization          ,STY ,24-06-2005 ,"V5R15 SP3 - Ri MNT ") // Creation activation asap a confirmer DDR du 21/06/05
CGMVersionMacroDefine(1523,GetBoundingWires_Stability                                  ,fds ,24-06-2005 ,"V5R15 SP3 - Stabilisation ODT NT 64 pour regularisateur , demande ASE ")
CGMVersionMacroDefine(1524,CATIdenticalSurSur_Correction_Cylinder                      ,obh ,24-06-2005 ,"V5R15 SP3 - RI0497440 ") // adl_promote -cr RIA0497440 RIB0497440
CGMVersionMacroDefine(1525,Intersect_PointJournal                                      ,ice ,24-06-2005 ,"V5R15 SP3 ")
//CGMVersionMacroDefine(1526,IntersectionSurSur_SmoothSharpEvaluation                    ,sty ,24-06-2005 ,"V5R15 SP3 - Liv chgt  ref le 24/06 (DirThickSurf_031 & CGMTest_NewTopoN1FilletKeepEdge4) ") // -cr 488988A 488988B 481703B 481703C
CGMVersionMacroDefine(1527,Corner_TriTgt_SafeOldRedondancy                             ,alv ,24-06-2005 ,"V5R15 SP3 - RI0496871 correction de différents bugs lors de l\'appel à la redondance. ")
//CGMVersionMacroDefine(1528,Intersection_OptimizeArcsLevel1                             ,klx ,01-07-2005 ,"V5R15 SP3 - RI 495904 ") // -cr 495904A 495904B 495904C
CGMVersionMacroDefine(1529,ExtractNurbs_SmallArcs                                      ,PKC ,27-06-2005 ,"V5R15 SP3 - odt perfo casse ")
CGMVersionMacroDefine(1530,Blend_SameShapeFor_G2G0andG0G2_Profiles_2                   ,JSX ,01-07-2005 ,"V5R15 SP3 - Blend G0G2 avec une mauvaise forme cas avec spine ") // pas de ri Odt mulitfaceblenb7
CGMVersionMacroDefine(1531,Blend_MeanTangentFunc_FalseFirstDeriv                       ,JSX ,01-07-2005 ,"V5R15 SP3 - erreur d indice ") // pas de ri
CGMVersionMacroDefine(1532,Fillet_SmartSnapping                                        ,rr  ,01-07-2005 ,"V5R15 SP3 - Stabilisation des fillet en configuration de Snapping ")
CGMVersionMacroDefine(1533,StablePointingDeformation_ExactCurvature                    ,CQI ,01-07-2005 ,"V5R15 SP3 - RI492884 ") // compute exact trace curvature Useful for non-curvilign parametrizations
CGMVersionMacroDefine(1534,StablePointingDeformationCrvSur_DeformWithoutInit           ,CQI ,01-07-2005 ,"V5R15 SP3 - RI484691 KeepEdge BOEING ")
CGMVersionMacroDefine(1535,Fillet_StablePointingDeformationCrvSur2                     ,FCX ,01-07-2005 ,"V5R15 SP3 - Amelioration de la deformation en pointe ") // Nouveau resp. = CQI
CGMVersionMacroDefine(1536,CATIdenticalSurSur_Nurbs                                    ,OBH ,01-07-2005 ,"V5R15 SP3 - Dev ")
//CGMVersionMacroDefine(1537,BitangentLine_DiscriminationIndexBySignature                ,ALV ,01-07-2005 ,"V5R15 SP3 - ri0498386 pb d\'index de discrimination des solutions pris sur lensemble des solutions et non par signature ") // activation immediate
CGMVersionMacroDefine(1538,HRV_CAT3DGridNewRep                                         ,TPG ,01-07-2005 ,"V5R15 SP3 - RI495068 ") // new dynamic rep
//CGMVersionMacroDefine(1539,NewProjectionCrvSur                                         ,sty ,01-07-2005 ,"V5R15 SP3 - POur activer la nouvelle projection ")
CGMVersionMacroDefine(1540,TangentLinePCrvPCircleCorrection                            ,OBH ,01-07-2005 ,"V5R15 SP3 - RI RI0494705 ")
CGMVersionMacroDefine(1541,Offset_LampshadeApexRescue                                  ,DPS ,05-07-2005 ,"V5R15 SP3 - rattrapage homotopique pour les traversees d\'Apex offsetables ") // adl_promote -cr 496472A
CGMVersionMacroDefine(1542,TopCleanCurve_ExtractPCEdOnEd                               ,HLN ,05-07-2005 ,"V5R15 SP3 - Amelioration de l\'extraction de PCurve d\'une edge posee sur une edge de jonction ") // Dans le cadre de tests du mode hybride -1 et 2 du clean topo des guide/profile du sweep topo
CGMVersionMacroDefine(1543,Localizer_ChoiceSurparam                                    ,HLN ,05-07-2005 ,"V5R15 SP3 - Echec ODT CGMTest_SurfacicN1FrFShellUnfold4_Case033 suite pb CATLocalizer2DFrom3D ") // pb identifie par SUH
//CGMVersionMacroDefine(1544,IntersectionCrvSur_Helix                                    ,sty ,05-07-2005 ,"V5R15 SP3 - Dev ")
//CGMVersionMacroDefine(1545,Intersection_OptimizeArcsLevel1                             ,klx ,05-07-2005 ,"V5R15 SP3 - RI 495904 ") // -cr 495904A 495904B 495904C
//CGMVersionMacroDefine(1547,Fillet_UntwistAndExtrapolate                                ,JMA ,05-07-2005 ,"V5R15 SP3 - Pb submited by SMAerospace Application (KDI) ")
//CGMVersionMacroDefine(1548,VariableCircleFillet_MarchingRepartition                    ,FCX ,05-07-2005 ,"V5R15 SP3 - Uniformisation des parametres du cheminement pour les fillet (Sag, MaxStep...) ") // Nouveau resp. = CQI
CGMVersionMacroDefine(1549,Sweep_AcceptLaidBodyWithoutAnalysis                         ,NLD ,08-07-2005 ,"V5R15 SP3 ")
CGMVersionMacroDefine(1550,Sweep_CylinderDetectionWithoutMapping                       ,NLD ,08-07-2005 ,"V5R15 SP3 - RI494734 ") // detection des cylindres a parametrage quelconque  -cr 494734a b c
CGMVersionMacroDefine(1551,TopCleanCurve_SnapNodeCanonics                              ,HLN ,08-07-2005 ,"V5R15 SP3 - Traitement des courbes canoniques (sans vecteur nodal) ") // Suite a probleme dans CGMTest_SurfacicSweep38_Case384b
CGMVersionMacroDefine(1552,NurbsCurveTopoToolKit_UpJournal_01                          ,rbd ,08-07-2005 ,"V5R15 SP3 - Correction du fichier journal du ToolKit des Nurbs curves. ")
CGMVersionMacroDefine(1553,CloseScarOnNonManifold                                      ,jbx ,08-07-2005 ,"V5R15 SP3 ") // -cr A0499931 B0499931
CGMVersionMacroDefine(1554,Sweep_WeakMappingBackup                                     ,NLD ,08-07-2005 ,"V5R15 SP3 ") // activation immediate


//=========================================================================================================
// V5R15 SP4
//=========================================================================================================
//CGMVersionMacroDefine(1561,Fillet_UseExtraNupletInExtrapolation                        ,JMA ,15-07-2005 ,"V5R15 SP4 - RI0469846 ")
CGMVersionMacroDefine(1562,VariableCircleFillet_MarchingRepartition                    ,CQI ,15-07-2005 ,"V5R15 SP4 ") // Nouveau resp. = CQI
CGMVersionMacroDefine(1563,Draft_Fixed_SmoothlyClosed                                  ,PFV ,15-07-2005 ,"V5R15 SP4 - RI 501300 ") // Activation immediate si creation en R15SP4
//CGMVersionMacroDefine(1564,Fillet_UntwistAndExtrapolate                                ,JMA ,15-07-2005 ,"V5R15 SP4 - Pb submited by SMAerospace Application (KDI) ")
CGMVersionMacroDefine(1565,Chamfer_UpdateContextualFaces                               ,JMA ,15-07-2005 ,"V5R15 SP4 - RI0501939 ") // -cr 501939A 501939B 501939C
CGMVersionMacroDefine(1566,Fillet_UntwistAndExtrapolate                                ,JMA ,15-07-2005 ,"V5R15 SP4 ")
CGMVersionMacroDefine(1567,SolveX_OldNewtonWithInit                                    ,CQI ,19-07-2005 ,"V5R15 SP4 - New stop criterion ") // Activation immédiate
CGMVersionMacroDefine(1568,Fillet_UnTwistR15SP4                                        ,rr  ,19-07-2005 ,"V5R15 SP4 - maintenance ") // activation immédiate
CGMVersionMacroDefine(1569,RelimTopOp_Init_DestroyUselessEdges                         ,ase ,22-07-2005 ,"V5R15 SP4 - RI ") // Activation immediate dans SP4
CGMVersionMacroDefine(1570,IntersectionCrvSur_Helix                                    ,sty ,22-07-2005 ,"V5R15 SP4 ")
CGMVersionMacroDefine(1571,StablePointingDeformationCrvSur_SharpnessPointingPoint      ,CQI ,22-07-2005 ,"V5R15 SP4 - Take account of G1 default at point ")
CGMVersionMacroDefine(1572,EdgeCurveOffset_UseLimitsForRelativeOrientation             ,CQI ,22-07-2005 ,"V5R15 SP4 ") // Use specified limits instead of MaxLimits when available
//CGMVersionMacroDefine(1573,Intersection_OptimizeArcsLevel1                             ,klx ,22-07-2005 ,"V5R15 SP4 ") // -cr 495904A 495904B 495904C
CGMVersionMacroDefine(1574,DraftRL_ForcePartingUntil                                   ,PFV ,22-07-2005 ,"V5R15 SP4 - RI 0502670 ") // Activation immediate, merci
CGMVersionMacroDefine(1575,Relim_UTurnCheck_TangentCaseEnhancement                     ,ase ,22-07-2005 ,"V5R15 SP4 - RI ") // activation immediate
CGMVersionMacroDefine(1576,DestroyEdgeWithConfusion                                    ,jbx ,22-07-2005 ,"V5R15 SP4 ")
CGMVersionMacroDefine(1577,OptimizeFaceFaceOnIdenticalSurfaces                         ,ice ,22-07-2005 ,"V5R15 SP4 - perfo booleen de face sur fonds identiques ")
//CGMVersionMacroDefine(1578,XVLConvert_1_CubicToNurbs                                   ,CCK ,22-07-2005 ,"V5R15 SP4 - Scrach a l\'open du XVL chez TMC ") // Activation immediate
CGMVersionMacroDefine(1579,Fillet_NewNotches_Three                                     ,JMA ,25-07-2005 ,"V5R15 SP4 ") // fillet robustnes : propagation od spec matching flag on supports
CGMVersionMacroDefine(1580,QuickDiscretizeFunctionX_Dichotomy_KeepPointOK              ,CQI ,25-07-2005 ,"V5R15 SP4 - Bug correction ") // GSMFrontiere22 KO FPExceptions
CGMVersionMacroDefine(1581,Parallel_SimplifLayDown                                     ,AOV ,25-07-2005 ,"V5R15 SP4 - pb de simplification de vertex abusive dans le posage du // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") // ") //
CGMVersionMacroDefine(1582,CircleFillet_KeepBestInit                                   ,PKC ,25-07-2005 ,"V5R15 SP4 - RI ")
CGMVersionMacroDefine(1583,SkinBorderSorting_NewCheck                                  ,JMA ,25-07-2005 ,"V5R15 SP4 - activation immediate ")
CGMVersionMacroDefine(1584,CATIntersectionPLinePCrv_Relimitation                       ,obh ,25-07-2005 ,"V5R15 SP4 - RI050231 ")
CGMVersionMacroDefine(1586,Sweep_SmallCirclePrecisionBySymmetry                        ,NLD ,29-07-2005 ,"V5R15 SP4 - RI Sweep. precision des petits cercles au voisinage des pointes ") // a livrer active le 29/07/05
CGMVersionMacroDefine(1587,Sweep_WeakMappingBackupOptim                                ,nld ,29-07-2005 ,"V5R15 SP4 - CPU en cas de mapping faible ") // a livrer active le 29/07
CGMVersionMacroDefine(1588,Corner_TriTgt_Redondancy3Inputs                             ,alv ,29-07-2005 ,"V5R15 SP4 - utilisation des 3 inputs bodies du corner triTangent pour calculer la redondance. ")
CGMVersionMacroDefine(1589,CATIntersectionCrvSur_CrvTabHelix                           ,sty ,29-07-2005 ,"V5R15 SP4 - RI504795 ")
CGMVersionMacroDefine(1590,ExtrapWireOnShell_SearchPCurveToEvalSurParam                ,AOV ,29-07-2005 ,"V5R15 SP4 - RI ")
CGMVersionMacroDefine(1591,MergeVertices_PoecOnClosedEcrv                              ,jbx ,01-08-2005 ,"V5R15 SP4 ") // -cr A0501391 B0501391
CGMVersionMacroDefine(1592,BlendRibbon_GenericHealing                                  ,AJD ,01-08-2005 ,"V5R15 SP4 ") // Integration of generic healing in advanced fillet
CGMVersionMacroDefine(1593,Relim_ClosedInitEnhancement                                 ,PRL ,01-08-2005 ,"V5R15 SP4 - RI 498993 ") // -cr  B0498993 C0498993 D0498993
CGMVersionMacroDefine(1594,DistanceMin_BoundaryOnEdgeFace                              ,fds ,05-08-2005 ,"V5R15 SP4 - RI499442A ") // Correction distance min
CGMVersionMacroDefine(1595,Intersection_OptimizeArcsLevel1                             ,klx ,05-08-2005 ,"V5R15 SP4 - RI 495904 ABC ") // -cr 495904A 495904B 495904C
CGMVersionMacroDefine(1596,Draft_VarCrv_UseBrentMinimize                               ,KLX ,05-08-2005 ,"V5R15 SP4 - Perfo Draft (limit calls to GetEquivalentParam) ") // To be activated simultaneously with Intersection_OptimizeArcsLevel1
//CGMVersionMacroDefine(1597,ThickSurface_OneStepVolumeLevel2                            ,MNJ ,12-08-2005 ,"V5R15 SP4 - convergence nouveau ThickSurface ") // adl_promote -cr A0507049 B0507049
CGMVersionMacroDefine(1598,Wires_Order                                                 ,fds ,10-08-2005 ,"V5R15 SP4 - RI502096A ( and co ) ") // Activation immediate à faire absolu
CGMVersionMacroDefine(1599,CleanCurve_Manage_PSS0                                      ,RNO ,12-08-2005 ,"V5R15 SP4 - To avoid creating Pcurve outside surface domain (PSS_0) ")
//CGMVersionMacroDefine(1600,ThickSurface_OneStepVolumeLevel2                            ,MNJ ,12-08-2005 ,"V5R15 SP4 ") // convergence nouveau ThickSurface
CGMVersionMacroDefine(1601,Fillet_TwistOrientationOnPiece                              ,ase ,12-08-2005 ,"V5R15 SP4 - RI ") // -cr 0505609A 0505609B
CGMVersionMacroDefine(1602,Relim_RibInsertRemoveManagement                             ,PRL/ASE,12-08-2005 ,"V5R15 SP4 - RI 506478 (externe) ") // -cr 0506478A 0506478B                        (R15 SP4)
CGMVersionMacroDefine(1603,GeodesicSafeLastStep                                        ,CQI ,18-08-2005 ,"V5R15 SP4 - RI506643 ") // -cr B0506643 C0506643 D0506643. Activation immediate

#endif
