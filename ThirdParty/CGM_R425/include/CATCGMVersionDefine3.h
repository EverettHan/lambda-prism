#ifndef CATCGMVersionMacroDefine3_h
#define CATCGMVersionMacroDefine3_h
// COPYRIGHT DASSAULT SYSTEMES  2002

//=========================================================================================================
// V5R16 SP1
//=========================================================================================================
CGMVersionMacroDefine(1611,RelimSkinSmartSharedCells                                   ,jbx ,19-08-2005 ,"V5R16 SP1 ") // -cr A0505049 B0505049
CGMVersionMacroDefine(1612,CornerFace_GenerateConnexSolution                           ,ALV ,19-08-2005 ,"V5R16 SP1 - RI0501861 ")
CGMVersionMacroDefine(1613,IntersectionSurSurWithInits_FilletSupport                   ,sty ,19-08-2005 ,"V5R16 SP1 - dev AMD64 CGMTest_NewTopoRIVariableFilletEdge7 ko, new ref livree le 19/08/05 ")
CGMVersionMacroDefine(1614,Fillet_UpdateNotToSimplifyFatEdges                          ,BPG ,19-08-2005 ,"V5R16 SP1 - Fix the flaw detected in CATBlendTopOp shown by tritangent fillet use of autofillet ") // No comment.
CGMVersionMacroDefine(1615,TrimByThick_FilterXPcPcForInternalEdgesToThick              ,DPS ,19-08-2005 ,"V5R16 SP1 - RI505099 ") // -cr 505099A 505099B    faces non simplifiees -> pb GenericNaming
CGMVersionMacroDefine(1616,ThickSurface_OneStepVolumeLevel2                            ,MNJ ,23-08-2005 ,"V5R16 SP1 - convergence nouveau ThickSurface ") // promote -cr B0507049
CGMVersionMacroDefine(1617,SkinExtrapol_SimilarCurveLevel2                             ,MNJ ,23-08-2005 ,"V5R16 SP1 - dvp SkinExtrapol ")
CGMVersionMacroDefine(1618,Revol_Border_Simplification_Stability                       ,fds ,23-08-2005 ,"V5R16 SP1 - RI497740 ")
//CGMVersionMacroDefine(1619,IntersectionSurSurWithInits_Pline                           ,sty ,23-08-2005 ,"V5R16 SP1 ")
//CGMVersionMacroDefine(1620,Offset_BulldozerLevel3AndCleanIVRepTetrahedron              ,LAP ,26-08-2005 ,"V5R16 SP1 - Simplification en amont ") // pas d adl_promote (le RI sera clos USE)
CGMVersionMacroDefine(1621,Corner_OnPlane_PartiallyLayDownAndRedondancy                ,ALV ,26-08-2005 ,"V5R16 SP1 - RI0488717 prendre en compte le posage partiel dans le calcul des solutions redondante du corner ") // 4 ODT corner KO(GMTest_CornerTwoWireRadius_Case5, GMTest_CornerTwoWireRadius_Case5A, GMTest_CornerTwoWireRadius_Case5B, CGMTest_CornerTwoWireRadius_Case7) je livre la dupliquation des ODT vendredi
//CGMVersionMacroDefine(1622,NewProjectionCrvSur                                         ,OBH ,26-08-2005 ,"V5R16 SP1 - POur activer la nouvelle projection ")
CGMVersionMacroDefine(1623,CoeffForFit                                                 ,DR  ,26-08-2005 ,"V5R16 SP1 - amelioration perfos ") // ok
CGMVersionMacroDefine(1624,DistanceMinPtCrv_ReconvergeBestPoint                        ,CQI ,26-08-2005 ,"V5R16 SP1 - RI505892 ") // -cr B0505892 C0505892
CGMVersionMacroDefine(1625,ConfusedRecursiveCompletionCheck                            ,ase ,26-08-2005 ,"V5R16 SP1 - code correction for V4toV5 test ")
CGMVersionMacroDefine(1626,Unfold_ThrowOnImpossMustTearEdge                            ,SUH ,02-09-2005 ,"V5R16 SP1 - partial result from ShellUnfold ")
CGMVersionMacroDefine(1627,ExtrapolSurfacesForOffset_TryDichotomy                      ,CQI ,02-09-2005 ,"V5R16 SP1 - RI498723 ") // More precise reach boundary diagnostic. Promote -cr A0498723 B0498723
CGMVersionMacroDefine(1628,CCV_MassPropertiesVersionning                               ,ndn ,02-09-2005 ,"V5R16 SP1 ") // -cr C0505711 D0505711
//CGMVersionMacroDefine(1629,DistanceMin_BoundaryOnFace                                  ,JHN ,02-09-2005 ,"V5R16 SP1 - resultats incorrects sur la distance min lors de l\'intervention des frontieres ") // adl_promote
CGMVersionMacroDefine(1630,CurveAffineSupport_Correction                               ,obh ,02-09-2005 ,"V5R16 SP1 - RI  A0506701 ")
CGMVersionMacroDefine(1631,BitangentLine_DiscriminationIndexBySignature                ,ALV ,02-09-2005 ,"V5R16 SP1 - rendre l\'index par signature et non pas l\'ancien index (par longueur) RI0498386 ") // 2 ODT KO CAATopologicalOperators.tst  CAATopLineTangentCrvCrvOperator &  CAATopLineTangentPtCrvOperator
CGMVersionMacroDefine(1632,IntersectionSurSurWithInits_Pline                           ,sty ,02-09-2005 ,"V5R16 SP1 ")
CGMVersionMacroDefine(1633,SurToNurbsSur_SingleDuplicate                               ,fds ,09-09-2005 ,"V5R16 SP1 - Optimisation gestion modele pour EB ")
CGMVersionMacroDefine(1634,CATIntersectionSurSur_NewFindMissedBorder                   ,sty ,09-09-2005 ,"V5R16 SP1 - FPException dans l\'ancienne methode ")
CGMVersionMacroDefine(1635,Fillet_SmartSnapping_2                                      ,RR  ,09-09-2005 ,"V5R16 SP1 - Robustesse ") // SmartSnapping Drop 2
CGMVersionMacroDefine(1636,ExtrapolConnect_CheckTwistOnContact                         ,CQI ,09-09-2005 ,"V5R16 SP1 - RI509297 ") // -cr A0509297 B0509297
CGMVersionMacroDefine(1637,Offset_HealingGeoPostProLevel3                              ,MNJ ,09-09-2005 ,"V5R16 SP1 - RI RemoveFace ") // a activer dans OFF le 09 09 2005
CGMVersionMacroDefine(1638,Healing_Level16                                             ,JJC ,09-09-2005 ,"V5R16 SP1 - traitement des incompatibilites G1 entre 2 PCurves de supports differents ")
CGMVersionMacroDefine(1639,Offset_BulldozerLevel3AndCleanIVRepTetrahedron              ,LAP ,09-09-2005 ,"V5R16 SP1 - scenario Shell fortement non isotopologique ") // Simplification en amont
CGMVersionMacroDefine(1640,DraftBothSides_Extrapol                                     ,PKC ,09-09-2005 ,"V5R16 SP1 - RI ") // activation immediate
CGMVersionMacroDefine(1641,NewProjectionCrvSur                                         ,OBH ,09-09-2005 ,"V5R16 SP1 ") // activation immediate
CGMVersionMacroDefine(1642,HealerOpeFreezeInputBody                                    ,jbx ,12-09-2005 ,"V5R16 SP1 ")
CGMVersionMacroDefine(1643,ExtrapolFilletPlineContactCorrection                        ,OBH ,16-09-2005 ,"V5R16 SP1 - Bug dans l\'extrapol ")
CGMVersionMacroDefine(1644,Fillet_UnTwistR16SP1                                        ,RR  ,16-09-2005 ,"V5R16 SP1 - Convergence ") // Activation immédiate SVP
CGMVersionMacroDefine(1645,Corner_CornerSolution_VariableNbSupport                     ,ALV ,16-09-2005 ,"V5R16 SP1 - Nb support fixé à 2 pour tout les corner (pb pour le corner TriTangent)annexe RI496871 ")
CGMVersionMacroDefine(1646,RSO_Optimize2                                               ,PMG ,16-09-2005 ,"V5R16 SP1 - Optimisation par exploitation de la compacite. ") // gain de 50% sur les perfo
CGMVersionMacroDefine(1647,NullTangentExtremityProjection                              ,obh ,16-09-2005 ,"V5R16 SP1 - RIA0509119 ")
CGMVersionMacroDefine(1648,RibSweep_LawProblems                                        ,ajd ,16-09-2005 ,"V5R16 SP1 - demande fdl pour ajd ") // -cr 0509200 0509827 0509849
CGMVersionMacroDefine(1649,AdvancedCoupling                                            ,dr  ,19-09-2005 ,"V5R16 SP1 - improvement ")
CGMVersionMacroDefine(1650,DistanceMin_BoundaryOnFace                                  ,JHN ,19-09-2005 ,"V5R16 SP1 - effectuer le calcul correct ") // resultats incorrects sur la distance min lors de l\\\'intervention des frontieres
CGMVersionMacroDefine(1651,RibPerfo_SplitEdgeInhibitor                                 ,ase ,23-09-2005 ,"V5R16 SP1 - perfo ") // flag inactif pour mesure perfo et activation ulterieure
CGMVersionMacroDefine(1652,CATIntersectionPlnSur_NewCircle                             ,sty ,23-09-2005 ,"V5R16 SP1 - ri 509830 ")
CGMVersionMacroDefine(1653,CATEdgeCurveSharpnessCut_InversePoec                        ,sty ,23-09-2005 ,"V5R16 SP1 - ri 509830 ")
CGMVersionMacroDefine(1654,SweepVaria_PointInterpolation2                              ,jsx ,23-09-2005 ,"V5R16 SP1 - precision de continuite en tang Reg R15 (test manuel r16) ") // ri REG 511543
CGMVersionMacroDefine(1655,ApproxSurface_GenericRuled                                  ,FCX ,30-09-2005 ,"V5R16 SP1 - RI 510336 ") // promote -cr 510336A 510336B
CGMVersionMacroDefine(1656,MultiCurveApprox_SideContinuity                             ,FCX ,30-09-2005 ,"V5R16 SP1 - Modification nouvelle interface SetSideContinuity ")
CGMVersionMacroDefine(1657,Thick_PerfosLevel2                                          ,MNJ ,30-09-2005 ,"V5R16 SP1 - amelioration perfo ") // activation immediate le 23/09/2005
CGMVersionMacroDefine(1658,HLR_PreciseWireProjection                                   ,TPG ,30-09-2005 ,"V5R16 SP1 - RI503406 ") // precise projection for wire
CGMVersionMacroDefine(1659,AssembleGeoMerge                                            ,jbx ,30-09-2005 ,"V5R16 SP1 ")
CGMVersionMacroDefine(1660,ConstantFillet_KeepLimitsOnCanonicContact                   ,CQI ,30-09-2005 ,"V5R16 SP1 - Avoid to create a MC on infinite maxlim (case of 2 CATMathLine) ")
CGMVersionMacroDefine(1661,Offset_NoVRepPlanConfusionPass                              ,MNJ ,30-09-2005 ,"V5R16 SP1 - RI MNT ") // promote -cr  A0511559  B0511559
CGMVersionMacroDefine(1662,ThickenOp_ClassicalRunWithAppendCorrected                   ,LAP ,30-09-2005 ,"V5R16 SP1 - Correction d\'un bug dans ClassicalRun ") // 1 ODT KO: CAAThickenOp
CGMVersionMacroDefine(1663,Rib_InhibitPrematureClosingConnection                       ,ASE ,30-09-2005 ,"V5R16 SP1 - RI 503943 (activation immediate) ") // -cr 0503943D 0503943E (activation immediate)
CGMVersionMacroDefine(1664,Corner_CrvPoc_TempJournalOnProjection                       ,ALV ,30-09-2005 ,"V5R16 SP1 - Ne pas prendre en compte le journal des projections du pt sur la crv. ")
CGMVersionMacroDefine(1665,Extremum_MultiLayDownForRedondancy                          ,ALV ,30-09-2005 ,"V5R16 SP1 - RI0511906 mauvaise utilisation des ReplaceBody de l\'opérateur LayDown ")
CGMVersionMacroDefine(1666,ReflectLine_Junction                                        ,PFV ,30-09-2005 ,"V5R16 SP1 - RI0511006 ")
CGMVersionMacroDefine(1667,Rib_PropagCoarseForBSDraft                                  ,PRL ,30-09-2005 ,"V5R16 SP1 - RI ")
CGMVersionMacroDefine(1668,CATIntersectionSurSurWithInits_StabilizationPlnCylTangent   ,sty ,30-09-2005 ,"V5R16 SP1 - odt ")
CGMVersionMacroDefine(1669,Fillet_ContinuePropagAfterConfusion                         ,fdl ,30-09-2005 ,"V5R16 SP1 ") // -cr A0470524 B0470524
CGMVersionMacroDefine(1670,SymmetricMatrix_EigenVal                                    ,obh ,30-09-2005 ,"V5R16 SP1 - migration vers les matrices symmetrique ")
CGMVersionMacroDefine(1671,SurSurWithInits_ReconvergeAfterSurSurTg                     ,obh ,30-09-2005 ,"V5R16 SP1 - Offset CF DPS ")
CGMVersionMacroDefine(1672,Simplify_Edges_Symetrical                                   ,fds ,03-10-2005 ,"V5R16 SP1 - Meilleure symetrisation de la simplif des edges curves dans les edges ( demande draft ) ")
CGMVersionMacroDefine(1673,VariableFillet_RelimitSpineWithObjective                    ,CQI ,07-10-2005 ,"V5R16 SP1 - RI510169 ") // -cr A0510169 B0510169
CGMVersionMacroDefine(1674,ComputeConnectionWithCandidatClass                          ,jbx ,07-10-2005 ,"V5R16 SP1 ") // -cr A0511223 B0511223 A0511130 B0511130
CGMVersionMacroDefine(1675,ThickSurface_FillInPlanes                                   ,MNJ ,07-10-2005 ,"V5R16 SP1 - convergence nouveau ThickSurface ")
CGMVersionMacroDefine(1676,ThickSurface_ExTriggerTptFilter                             ,MNJ ,07-10-2005 ,"V5R16 SP1 - cvg ThickSurface OneStepVolume ")
//CGMVersionMacroDefine(1677,IntersectionSurSur_SmoothSharpEvaluation                    ,sty ,07-10-2005 ,"V5R16 SP1 ")
CGMVersionMacroDefine(1678,Fillet_IgnoreSharpEdgeCorrectNupletSelection                ,JHG ,07-10-2005 ,"V5R16 SP1 - prereq pour l\'activation de Fillet_LongPropagationForMax ")
CGMVersionMacroDefine(1679,CanonicalProj_CircleLimits                                  ,pkc ,07-10-2005 ,"V5R16 SP1 - RI ")
CGMVersionMacroDefine(1680,KeepEdgeFillet_Propagation                                  ,PKC ,07-10-2005 ,"V5R16 SP1 - dev stabilisation propagation ")
CGMVersionMacroDefine(1681,StablePointingDeformationCrvSur_MaxLength                   ,cqi ,07-10-2005 ,"V5R16 SP1 - dev IML ") // l\'odt KO va etre relivre vendredi 07/10(reference)
CGMVersionMacroDefine(1682,CornerData_EqualityTestWithCATEpsg                          ,ALV ,07-10-2005 ,"V5R16 SP1 - Calcul des egalitées entre deux corners avec CATEpsg ")
CGMVersionMacroDefine(1683,CATEdgeCurveSharpnessCut_BorderPoint                        ,sty ,07-10-2005 ,"V5R16 SP1 - Dev ")
CGMVersionMacroDefine(1684,GContinuity_NewNullCurvature                                ,RNO ,07-10-2005 ,"V5R16 SP1 - Actual value is too small ") // CATGmoUpd_LSTMaint016 + RI507572
//CGMVersionMacroDefine(1685,Posage_ActivateJournal                                      ,JHN ,10-10-2005 ,"V5R16 SP1 - journal de posage sur vertex extremite pas toujours identique en  fonction des circonstances ") // adl_promote -cr  511141A 511141B
CGMVersionMacroDefine(1686,Extrude_NoStabConf                                          ,fds ,10-10-2005 ,"V5R16 SP1 - RI512729 : destabilisation Extrude due a la variable IntersectionCrvCrv_StabConf ") // RI512729
CGMVersionMacroDefine(1687,Sweep_NormalDerivativeV2                                    ,NLD ,10-10-2005 ,"V5R16 SP1 - RI508513 prise en compte derivee du changement de parametre dans derivee de la normale ") // -cr 508514A
//CGMVersionMacroDefine(1688,Posage_ActivateJournal                                      ,JHN ,14-10-2005 ,"V5R16 SP1 - adl_promote ") // journal de posage sur vertex extremite pas toujours identique en  fonction des circonstances
//CGMVersionMacroDefine(1689,IntersectionSurSur_SmoothSharpEvaluation                    ,sty ,14-10-2005 ,"V5R16 SP1 ") // CATAdvancedAutoFillet14 qui va etre desactive
CGMVersionMacroDefine(1690,MarshMallow_Level9                                          ,PMG ,14-10-2005 ,"V5R16 SP1 ") // -cr A0513040 B0513040 C0513040
CGMVersionMacroDefine(1691,EuclidianParallel_DiscardSingularInit                       ,CQI ,14-10-2005 ,"V5R16 SP1 - RI512735 TOY (discard singular transfered init) ") // -cr A0512735 B0512735 C0512735
CGMVersionMacroDefine(1692,ImplicitSpine_OrnTgWireLayOn3                               ,CCK ,17-10-2005 ,"V5R16 SP1 - RI 513016 ") // -cr 513016a 513016b 513016c
//CGMVersionMacroDefine(1693,Fillet_LongPropagation_One                                  ,JMA ,17-10-2005 ,"V5R16 SP1 - RI ")
CGMVersionMacroDefine(1694,NonLinear_SimCurve                                          ,RHA ,17-10-2005 ,"V5R16 SP1 - Odt Appli ") // Odt Appli

//=========================================================================================================
// V5R16 SP2
//=========================================================================================================
CGMVersionMacroDefine(1701,HLR_MergeSameReflectParts                                   ,TPG ,21-10-2005 ,"V5R16 SP2 - RI503850 ")
CGMVersionMacroDefine(1702,Fillet_LongPropagation_One                                  ,JMA ,21-10-2005 ,"V5R16 SP2 ")
CGMVersionMacroDefine(1703,Fillet_MoreCandForSupportRelim                              ,JMA ,21-10-2005 ,"V5R16 SP2 ") // -cr 513036A 513036B 513036C
CGMVersionMacroDefine(1704,ThickSurface_SideRibbonStabilization                        ,MNJ ,21-10-2005 ,"V5R16 SP2 - dev R17 ")
CGMVersionMacroDefine(1705,Homotopy_MoveInit                                           ,CQI ,24-10-2005 ,"V5R16 SP2 - RI512734 ") // -cr A0512734 B0512734 C0512734
CGMVersionMacroDefine(1706,Healing_Level17                                             ,JJC ,24-10-2005 ,"V5R16 SP2 - RI 512688 ")
CGMVersionMacroDefine(1707,Relim_LoopExtensionForCone                                  ,PRL ,24-10-2005 ,"V5R16 SP2 - RI ") // -cr  A0511471
CGMVersionMacroDefine(1708,CATCanonicalProjection_CircleTol                            ,sty ,28-10-2005 ,"V5R16 SP2 ") // -cr B514065 C514065 D514065
CGMVersionMacroDefine(1709,Fillet_R16SP2                                               ,RR  ,28-10-2005 ,"V5R16 SP2 - Robustesse ")
CGMVersionMacroDefine(1710,ThickSurface_LogicalVolumePosition                          ,MNJ ,28-10-2005 ,"V5R16 SP2 - perfos nouveau ThickSurface ")
CGMVersionMacroDefine(1711,Offset_MultiConfusionAdjust                                 ,MNJ ,28-10-2005 ,"V5R16 SP2 - ODT ") // DirThickSurf_127
CGMVersionMacroDefine(1712,Sweep_SpineCurvatureHalfDerivativeOnBorder                  ,NLD ,28-10-2005 ,"V5R16 SP2 ")
CGMVersionMacroDefine(1713,Sweep_NormalDerivativeV3                                    ,NLD ,28-10-2005 ,"V5R16 SP2 - deploiement du rattrapage de derivees aux bornes de domaines ")
//CGMVersionMacroDefine(1714,Sweep_MappingWithoutShiftOnBorder                           ,NLD ,28-10-2005 ,"V5R16 SP2 - suppression des recalages aux frontieres perturbant les derivees ")
//CGMVersionMacroDefine(1715,Sweep_DeploySoftwareConfigurationV4                         ,NLD ,04-11-2005 ,"V5R16 SP2 - mapping de MF sans config dans certains cas de detwistage ")
CGMVersionMacroDefine(1716,Offset_ForceFiliationForStapleRescue                        ,DPS ,04-11-2005 ,"V5R16 SP2 - filiation artificielle pour les rattrapages homotopiques ") // adl_promote -cr 512307A
CGMVersionMacroDefine(1717,Posage_ActivateJournal                                      ,JHN ,04-11-2005 ,"V5R16 SP2 - adl_promote ") // journal de posage sur vertex extremite pas toujours identique en  fonction des circonstances
CGMVersionMacroDefine(1718,Fillet_SpineExtrapol                                        ,CWM ,04-11-2005 ,"V5R16 SP2 - RI ") // -cr A0512949 B0512949 C0512949
CGMVersionMacroDefine(1719,QuickDiscretizeFunctionX_StopInsideDomain                   ,CQI ,04-11-2005 ,"V5R16 SP2 - Bug correction (revealed by PtDirEnhancement + InputClean) ")
CGMVersionMacroDefine(1720,Offset_SharpTriPtFilter                                     ,MNJ ,04-11-2005 ,"V5R16 SP2 - RI 0512734 A, B&C ") // promote -cr A0512734  B0512734  C0512734
CGMVersionMacroDefine(1721,Offset_PlanarDirectionalSurface                             ,MNJ ,04-11-2005 ,"V5R16 SP2 - RI 0515298 ") // promote -cr  A0515298  B0515298  C0515298
CGMVersionMacroDefine(1722,Draft_TrueMultiRib_OffsetFacesAllowed                       ,SOU ,04-11-2005 ,"V5R16 SP2 - To increase the cases where True multi ") // promote -cr A0514445 B0514445 C0514445 - Allow offsets of plane, cylinder & tabulated cylinder in extrusion body
CGMVersionMacroDefine(1723,SketchGeodesic_NewReport                                    ,AOV ,04-11-2005 ,"V5R16 SP2 - bug ")
CGMVersionMacroDefine(1724,Prism_OpenProfile_NoExternalPad                             ,fds ,04-11-2005 ,"V5R16 SP2 - RI514394A ")
CGMVersionMacroDefine(1725,Ribbon_SolOKOnSupport                                       ,PFV ,04-11-2005 ,"V5R16 SP2 - RI 513236 ") // Gestion des cas Confused
CGMVersionMacroDefine(1726,CleanCurve_UseMaxLimits                                     ,RNO ,04-11-2005 ,"V5R16 SP2 - Ne plus utiliser les Limits courantes ") // promote -cr A0511669 B0511669 C0511669
CGMVersionMacroDefine(1727,OptimizeSimplifForNonManifEdge                              ,jbx ,07-11-2005 ,"V5R16 SP2 ") // -cr A0513951 B0513951 C0513951
CGMVersionMacroDefine(1728,Fillet_InfiniteFace                                         ,RR  ,10-11-2005 ,"V5R16 SP2 - RI514067, 514230 ") // -cr A0514067 B0514067 C0514067 A0514230 B0514230 C0514230
CGMVersionMacroDefine(1729,ParallelConnectTool_LocalC2Piecewise                        ,CQI ,10-11-2005 ,"V5R16 SP2 - RI515252 ") // -cr B0515252 C0515252 D0515252
CGMVersionMacroDefine(1730,PointOnCurve_Equidistant                                    ,fds ,10-11-2005 ,"V5R16 SP2 - RI515620 ")
CGMVersionMacroDefine(1731,DistanceCrvSur_Pln_UseLimits                                ,CQI ,10-11-2005 ,"V5R16 SP2 - RI515539 ") // -cr A0515539 B0515539
CGMVersionMacroDefine(1732,Offset_BetterDisconnectInputForFaceCreation                 ,LAP ,10-11-2005 ,"V5R16 SP2 - RI515974 AB ") // -cr A0515974 B0515974
CGMVersionMacroDefine(1733,Corner_ReplaceCATMathInfiniteByFactoryInfinite              ,ALV ,18-11-2005 ,"V5R16 SP2 - Résultat de l\'opérateur géometrique instable avec un rayon max a CATMAthInfinite ")
CGMVersionMacroDefine(1734,Offset_ForgetBadXSurSurSolutionLevel2                       ,LAP ,18-11-2005 ,"V5R16 SP2 - RI516270 Reg AB ") // -cr A0516270 B0516270
CGMVersionMacroDefine(1735,Thick_PerfosLevel3                                          ,MNJ ,18-11-2005 ,"V5R16 SP2 - RIs ") // promote -cr A0516343 B0516343 C0516343 A0516353 B0516353 C0516353 A0516029 B0516029 C0516029
CGMVersionMacroDefine(1736,CATIntersectionSurSur_TangentRes                            ,sty ,18-11-2005 ,"V5R16 SP2 - ri ") // -cr 514309A 514309B
//CGMVersionMacroDefine(1737,ExtractCombOnLimSurf                                        ,CCK ,18-11-2005 ,"V5R16 SP2 - RI 514 396 : match analytique ") // -cr A0514396 B0514396
CGMVersionMacroDefine(1738,Projection_ConfusedCE                                       ,JHN ,21-11-2005 ,"V5R16 SP2 - adl_promote ") // Ri donc. cas peu frequent
CGMVersionMacroDefine(1739,Chamfer_CorrectionsInErrorProcessing                        ,JMA ,25-11-2005 ,"V5R16 SP2 - RI ") // -cr B0508913
CGMVersionMacroDefine(1740,Healing_Level18                                             ,JJC ,25-11-2005 ,"V5R16 SP2 - Ajustement G1 des PCurves : generalisation ")
CGMVersionMacroDefine(1741,ConnectStartHomotopy_LinearizedInit                         ,CQI ,25-11-2005 ,"V5R16 SP2 - RI515967 ") // -cr A0515967 B0515967
CGMVersionMacroDefine(1742,Sweep_DeploySoftwareConfigurationV4                         ,NLD ,25-11-2005 ,"V5R16 SP2 ") // mapping de MF sans config dans certains cas de detwistage
CGMVersionMacroDefine(1743,Parallel_NonApproxLaw                                       ,AOV ,25-11-2005 ,"V5R16 SP2 - Dev parallele avec lois a tangente verticale ")
//CGMVersionMacroDefine(1744,SurSurTg_CutOnSingular                                      ,obh ,25-11-2005 ,"V5R16 SP2 - Dev Cf DPS (code 100 CGMTest_GeometryReplaySurSurWithInits livraison correction vendredi 25/11/2005) ")
CGMVersionMacroDefine(1745,ProjectionPt_SurfaceEnPointe                                ,obh ,25-11-2005 ,"V5R16 SP2 - ProjectionCourbe Surface ")
CGMVersionMacroDefine(1746,SmartProject_PartialSolution                                ,JHN ,25-11-2005 ,"V5R16 SP2 - smart projection for projection nearest ") // developement
CGMVersionMacroDefine(1747,Corner_Trim_DeleteContactPointInReport                      ,alv ,25-11-2005 ,"V5R16 SP2 - suppression dans le journal d\'éléments indésirables ")
CGMVersionMacroDefine(1748,Corner_HalfCircles                                          ,ALV ,25-11-2005 ,"V5R16 SP2 - Gestion des demi cercles et du mode direct ou complementaire de création de cercles ")
CGMVersionMacroDefine(1749,SmoothCurve_NewTolForOptimise                               ,RNO ,25-11-2005 ,"V5R16 SP2 - Correction des cas en Max Deviation en 2D+  Reduction du nombre d\'arcs ")
CGMVersionMacroDefine(1750,CATIntersectionSurSur_NewReturningPoint                     ,sty ,28-11-2005 ,"V5R16 SP2 ") // -cr 516226B 516226C 516226D
CGMVersionMacroDefine(1751,Sweep_IntersectionCoupling_Eval_InvalidDomain               ,JSX ,28-11-2005 ,"V5R16 SP2 - Newton lance sur un domaine invalide lors de la reconvergence de la de mapping ") // Reg Odt  GSMXPerfo.tst GSMJournalingTolerantModelingSc2


//=========================================================================================================
// V5R16 SP3
//=========================================================================================================
CGMVersionMacroDefine(1760,SurSurTg_RelaxDomain                                        ,OBH ,02-12-2005 ,"V5R16 SP3 ")
CGMVersionMacroDefine(1761,NewProjectionCrvSurInvalidAdmissibleCurve                   ,obh ,02-12-2005 ,"V5R16 SP3 ")
CGMVersionMacroDefine(1762,Fillet_R16SP3                                               ,RR  ,02-12-2005 ,"V5R16 SP3 - RI ") // -cr B0505119
CGMVersionMacroDefine(1763,ExtrapolCurve_FilletContactCheck                            ,CQI ,02-12-2005 ,"V5R16 SP3 - RI517687: check if we have a true contact curve ") // -cr A0517687 B0517687
CGMVersionMacroDefine(1764,SurSurTg_CutOnSingular                                      ,obh ,02-12-2005 ,"V5R16 SP3 ") // Dev Cf DPS (code 100 CGMTest_GeometryReplaySurSurWithInits livraison correction vendredi 25/11/2005
//CGMVersionMacroDefine(1765,Sewing_CvSplitter                                           ,PRL ,06-12-2005 ,"V5R16 SP3 - Dev ")
CGMVersionMacroDefine(1766,Extrude_FreezeMode                                          ,fds ,09-12-2005 ,"V5R16 SP3 - RI505384A ")
CGMVersionMacroDefine(1767,TrimByThick_ELyingOnSharpnessCut                            ,DPS ,09-12-2005 ,"V5R16 SP3 - Dev R17 SheetMetal : liens poses sur avec changement de vivicite ") // injection de singularites dans le SurSurTg
CGMVersionMacroDefine(1768,Offset_SuperFadingEdge                                      ,DPS ,09-12-2005 ,"V5R16 SP3 - developpement R17 + regul weakly sharp edges ")
CGMVersionMacroDefine(1769,TopCleanLoop_GeometricLocalizer                             ,RNO ,09-12-2005 ,"V5R16 SP3 - Probleme Algos Machinist sur Limites de Faces ")
CGMVersionMacroDefine(1770,ReflectDrftRib_CutClosedEdge                                ,PFV ,09-12-2005 ,"V5R16 SP3 - Activation decoupe aretes fermees pour les reflectlines ")
CGMVersionMacroDefine(1771,HLR_ForceSilhExtrapolationForIntersection                   ,TPG ,09-12-2005 ,"V5R16 SP3 - RI517282 ")
CGMVersionMacroDefine(1772,ProjectionCrvSur_RemoveRedondantCurve                       ,sty ,09-12-2005 ,"V5R16 SP3 - RI 446574 ")
CGMVersionMacroDefine(1773,ConnectPtSur_NewCreate                                      ,OAU ,09-12-2005 ,"V5R16 SP3 - Versionning ")
CGMVersionMacroDefine(1774,Thick_NonManifoldERepLevel2                                 ,MNJ ,09-12-2005 ,"V5R16 SP3 - RIs ") // promote -cr A0518187 A0518188 A0488747 B0488747
CGMVersionMacroDefine(1775,TrimByThick_NullRadiusConfig                                ,MNJ ,09-12-2005 ,"V5R16 SP3 - RIs ") // promote -cr A0516940 B0516940 A0518447 B0518447
CGMVersionMacroDefine(1776,RibSweep_Remove180ArcInit                                   ,AJD ,09-12-2005 ,"V5R16 SP3 - IR ") // -cr A0517607 B0517607
CGMVersionMacroDefine(1777,Parallel_IntersectionInit2                                  ,CQI ,09-12-2005 ,"V5R16 SP3 - RI519011: sine law on one period ") // -cr A0519011 B0519011
CGMVersionMacroDefine(1778,ThrowForUnsetCuttingMultiConfEdge                           ,JBX ,09-12-2005 ,"V5R16 SP3 - Protection contre verolage modele via UnsetCutting lors d\'un appel incorrect ")
CGMVersionMacroDefine(1779,Fillet_RelimOnSkinErrors                                    ,JMA ,12-12-2005 ,"V5R16 SP3 - RI ") // -cr A0489627
CGMVersionMacroDefine(1780,Extrude_NewCreateSimCurve                                   ,fds ,12-12-2005 ,"V5R16 SP3 - Regler un probleme de CATFPExceptions ")
CGMVersionMacroDefine(1781,Thick_RemoveFaceLevel10                                     ,MNJ ,12-12-2005 ,"V5R16 SP3 - RI ") // promote -cr A0516353 B0516353 C0516353
CGMVersionMacroDefine(1782,AssembleWire_EqualityTestWithCATEpsg                        ,jbx ,12-12-2005 ,"V5R16 SP3 - Pb parallele ")
CGMVersionMacroDefine(1783,VariableFillet_NewParabola2                                 ,CCK ,12-12-2005 ,"V5R16 SP3 - Dev ")
CGMVersionMacroDefine(1784,DestroyEdge_UpdateTouch                                     ,ice ,12-12-2005 ,"V5R16 SP3 - Reprise du calcul du Touch sur les faces impactees par un DestroyEdge ")
CGMVersionMacroDefine(1785,Thick_PerfosLevel4                                          ,MNJ ,16-12-2005 ,"V5R16 SP3 - RI ") // promote -cr A0516343 B0516343 C0516343
//CGMVersionMacroDefine(1786,SmartProject_AllerRetour                                    ,jhn ,16-12-2005 ,"V5R16 SP3 - dvpt projection near ") // a activer en release ouverte
CGMVersionMacroDefine(1787,AnalysisPtSurGen_InteriorSol                                ,CQI ,16-12-2005 ,"V5R16 SP3 - RI519018 : keep confused points on surface as solutions ") // -cr A0519018 B0519018
CGMVersionMacroDefine(1788,Blend_TopoSweepInfra                                        ,JSX ,22-12-2005 ,"V5R16 SP3 - Modifs diverses et necessaires avant la migration du blend sur le sweep ") // Factorisation du code
CGMVersionMacroDefine(1789,Regul_CheckOffset                                           ,CWM ,22-12-2005 ,"V5R16 SP3 - RegulOffset: Verification de l\'offsetabilite de la face regularisee (non fait en cas d\'offset flou) ") // CGMTest_SurfacicRegul1(cas 8) CGMTest_SurfacicRegul2 (cas 15 et 27)
CGMVersionMacroDefine(1790,Fillet_FaceFaceInitOnControledIn                            ,JMA ,22-12-2005 ,"V5R16 SP3 - RI0505119 ") // -cr B0505119
CGMVersionMacroDefine(1791,Fillet_LongPropagation_Two                                  ,JMA ,22-12-2005 ,"V5R16 SP3 - dev ")
CGMVersionMacroDefine(1792,Sewing_CvSplitter                                           ,PRL ,22-12-2005 ,"V5R16 SP3 - Dev ")
CGMVersionMacroDefine(1793,NewGSDSurProj                                               ,dr  ,22-12-2005 ,"V5R16 SP3 - ri ")
CGMVersionMacroDefine(1794,HLR_PointHiddenByFace                                       ,TPG ,22-12-2005 ,"V5R16 SP3 - RI510897 ")
CGMVersionMacroDefine(1795,GeodesicPtDir_SetParamInside                                ,CQI ,22-12-2005 ,"V5R16 SP3 - RI520144 ") // -cr A0520144 B0520144
CGMVersionMacroDefine(1796,SurSurTg_Loop                                               ,OBH ,23-12-2005 ,"V5R16 SP3 - Convergence de dev ")
CGMVersionMacroDefine(1797,Thick_DirSurfUVBoxExpansion                                 ,MNJ ,02-01-2006 ,"V5R16 SP3 - RI MNT ") // promote -cr A0519911 B0519911
CGMVersionMacroDefine(1798,BasicBody_Invert_Error                                      ,fds ,02-01-2006 ,"V5R16 SP3 - Bug ") // Probleme creation basic body
CGMVersionMacroDefine(1799,Relim_ReturnBackForPropagCoarseSurfaces                     ,PRL ,02-01-2006 ,"V5R16 SP3 - Modele client ")
CGMVersionMacroDefine(1800,Fillet_EdgesRecordForImplicitKeep                           ,JMA ,06-01-2006 ,"V5R16 SP3 - dev + odt ")
CGMVersionMacroDefine(1801,CATProjectCrvSurMapX_TestArret                              ,RHA ,06-01-2006 ,"V5R16 SP3 - Smart Projection ")
CGMVersionMacroDefine(1802,Thick_RemoveFaceLevel11                                     ,MNJ ,06-01-2006 ,"V5R16 SP3 - RI ") // promote -cr  A0520755
//CGMVersionMacroDefine(1803,Fillet_ConfusionsOnFreeEdges                                ,JMA ,09-01-2006 ,"V5R16 SP3 - Dev+ODT ")
CGMVersionMacroDefine(1804,Regul_GestionEdgesFaiblementVives                           ,CWM ,09-01-2006 ,"V5R16 SP3 ") // Dev
CGMVersionMacroDefine(1805,ConstantFillet_HighDegreePrecision                          ,CQI ,09-01-2006 ,"V5R16 SP3 - RI520902 ") // Activation immediate
CGMVersionMacroDefine(1806,GeodesicParallel_GeodesicExtrapol                           ,CQI ,13-01-2006 ,"V5R16 SP3 - PtDir enhancement ")
CGMVersionMacroDefine(1807,Marching_CheckLastPoints                                    ,klx ,13-01-2006 ,"V5R16 SP3 - RI 520879 ") // -cr 520879A 520879B
CGMVersionMacroDefine(1808,Fillet_ConfusionsOnFreeEdges                                ,JMA ,13-01-2006 ,"V5R16 SP3 ")
CGMVersionMacroDefine(1809,Sweep_DeploySoftwareConfigurationV5                         ,NLD ,13-01-2006 ,"V5R16 SP3 - Suite deploiement de la configuration dans FreeForm ")
CGMVersionMacroDefine(1810,Offset_CheckIntraSRepClashParameter                         ,MNJ ,13-01-2006 ,"V5R16 SP3 - RI ")
CGMVersionMacroDefine(1811,Parallel_ProjectOnOriginalSurface                           ,AOV ,13-01-2006 ,"V5R16 SP3 - DEV ")
CGMVersionMacroDefine(1812,EuclidianParallel_CurvatureQuality                          ,CQI ,13-01-2006 ,"V5R16 SP3 - Dev R17 ")
CGMVersionMacroDefine(1813,EuclidianParallelInterpol_CheckOrientation                  ,CQI ,13-01-2006 ,"V5R16 SP3 - Interpolation defect (CGMTest_Parallel_WireShell_LawN_N1_CleanWire) ")
CGMVersionMacroDefine(1814,SmartProject_AllerRetour                                    ,jhn ,13-01-2006 ,"V5R16 SP3 - projection near ")
//CGMVersionMacroDefine(1815,CleanCurve_LocalOpti2                                       ,RNO ,16-01-2006 ,"V5R16 SP3 - Amalioration du comportement sur les cas difficiles ") // POur nouveaux developpement LocalOpti
CGMVersionMacroDefine(1816,Sweep_TwistDetection_PointedSurfaceInsensibleOrientation    ,JSX ,16-01-2006 ,"V5R16 SP3 - Non detection de twist sur les surfaces ayant une pointe en v=vmin ") // -cr A0520695 B0520695
//CGMVersionMacroDefine(1817,Blend_TopoSweepInfra2                                       ,JSX ,16-01-2006 ,"V5R16 SP3 - TolerantBlend : traitement des cas avec pointes laterales ") // dev
CGMVersionMacroDefine(1818,TopOp_CleanDisconnectInfoOption                             ,PRL ,16-01-2006 ,"V5R16 SP3 - RI ") // -cr A0441378
CGMVersionMacroDefine(1819,CleanCurve_LocalOpti2                                       ,RNO ,20-01-2006 ,"V5R16 SP3 - Amalioration du comportement sur les cas difficiles  // POur nouveaux developpement LocalOpti ") // POur nouveaux developpement LocalOpti ") // POur nouveaux developpement LocalOpti ") // POur nouveaux developpement LocalOpti ") // POur nouveaux developpement LocalOpti ") // POur nouveaux developpement LocalOpti ") // POur nouveaux developpement LocalOpti ") // POur nouveaux developpement LocalOpti ") // POur nouveaux developpement LocalOpti ") // POur nouveaux developpement LocalOpti ") // POur nouveaux developpement LocalOpti ") // POur nouveaux developpement LocalOpti ") // POur nouveaux developpement LocalOpti ") // POur nouveaux developpement LocalOpti ") // POur nouveaux developpement LocalOpti ") // POur nouveaux developpement LocalOpti ") // POur nouveaux developpement LocalOpti ") // POur nouveaux developpement LocalOpti ") // POur nouveaux developpement LocalOpti ") // POur nouveaux developpement LocalOpti ") // POur nouveaux
CGMVersionMacroDefine(1820,Thick_ForbidBigVerticesLevel3                               ,MNJ ,20-01-2006 ,"V5R16 SP3 - RIs A0521661 et A0521581 ") // promote -cr A0521661 A0521581
CGMVersionMacroDefine(1821,Sweep_Circle_AlignedPointsManagement                        ,NLD ,20-01-2006 ,"V5R16 SP3 - RI521597 ") // -cr 521597a 521597b
CGMVersionMacroDefine(1822,ConnectStartHomotopy_CheckSolution                          ,CQI ,20-01-2006 ,"V5R16 SP3 - RI520851 ") // -cr A0520851 B0520851
CGMVersionMacroDefine(1823,RollingEdge_CheckSingularity                                ,CQI ,20-01-2006 ,"V5R16 SP3 - ODT FPCONTROL ")
CGMVersionMacroDefine(1824,PCurvesOffset_Report_SetInsideMaxLimits                     ,CQI ,20-01-2006 ,"V5R16 SP3 - ODT ")
CGMVersionMacroDefine(1825,Intersection_PCrvPCrv_Sign                                  ,RHA ,23-01-2006 ,"V5R16 SP3 - RI Externe ") // promote -cr A0521178 B00521178 C521178
CGMVersionMacroDefine(1826,CurveAffineSupport_PCurveOnPlane                            ,obh ,23-01-2006 ,"V5R16 SP3 - RI0520930 ") // adl_promote -cr B0520930  C0520930 D0520930
//CGMVersionMacroDefine(1827,Healing_Level19                                             ,JJC ,23-01-2006 ,"V5R16 SP3 - Improvment for G1 fillet and chamfer ") // Total G1 correction on CGMReplay_FilletHoldCurveG1
CGMVersionMacroDefine(1828,Sweep_Perfo_CCVGetContinuityParams                          ,JSX ,23-01-2006 ,"V5R16 SP3 - perfo : boucle en N2 ") // comparaison SW
CGMVersionMacroDefine(1829,Healing_Level19                                             ,JJC ,27-01-2006 ,"V5R16 SP3 - Improvment for G1 fillet and chamfer ") // Total G1 correction on CGMReplay_FilletHoldCurveG1
CGMVersionMacroDefine(1830,Blend_TopoSweepInfra2                                       ,JSX ,27-01-2006 ,"V5R16 SP3 - Bug detecté suite a l activation de cleanguideLocalopti2 ")
CGMVersionMacroDefine(1831,Fillet_TolerantMultiRibbon                                  ,JMA ,27-01-2006 ,"V5R16 SP3 - ODT part KO configuration instable ")
CGMVersionMacroDefine(1832,Sweep_ProfilePositioningV4                                  ,NLD ,27-01-2006 ,"V5R16 SP3 - RI521803 ") // -cr 521803a 521803b
CGMVersionMacroDefine(1833,Sweep_HomogenizationWithLawScaling                          ,NLD ,27-01-2006 ,"V5R16 SP3 - RI522558 ") // -cr 522558a 522558b
CGMVersionMacroDefine(1834,ProjPtSurGen_LimitPatchSolution                             ,CQI ,27-01-2006 ,"V5R16 SP3 - ODT ") // GSA_RIA0361117 KO HPUX_B
CGMVersionMacroDefine(1835,ConstantFillet_PlnSurInit                                   ,CQI ,27-01-2006 ,"V5R16 SP3 - RI522485 ") // -cr A0522485 B0522485
CGMVersionMacroDefine(1836,CATIntersectionSurSurGen_SignRevol                          ,sty ,27-01-2006 ,"V5R16 SP3 ") // -cr A0522486 B0522486
CGMVersionMacroDefine(1837,IntersectShell_CloseScar_MissingOnBothShells                ,ice ,30-01-2006 ,"V5R16 SP3 - RI521077 ") // Split_ShelShell_Case3/RI469381 passe OK


//=========================================================================================================
// V5R16 SP4
//=========================================================================================================
CGMVersionMacroDefine(1841,Sweep_Circle_3GuidesOrientationStabilization                ,NLD ,03-02-2006 ,"V5R16 SP4 ")
CGMVersionMacroDefine(1842,Fillet_LongPropagation_Three                                ,JMA ,03-02-2006 ,"V5R16 SP4 - Dev, corrections ") // R16SP4
CGMVersionMacroDefine(1843,SkinExtrapol_SimilarERepGen                                 ,MNJ ,03-02-2006 ,"V5R16 SP4 - dev ")
CGMVersionMacroDefine(1844,BothSidesDraft_TwistOnPlanarSupport                         ,PFV ,03-02-2006 ,"V5R16 SP4 ") // Active a partir de la R16SP4
CGMVersionMacroDefine(1845,Fillet_R16SP4                                               ,RR  ,03-02-2006 ,"V5R16 SP4 - Maintenance préventive ") // R16SP4
CGMVersionMacroDefine(1846,Offset_TrustLevelOneForFaceAndShellJournalCorrection        ,LAP ,03-02-2006 ,"V5R16 SP4 - RI522892 et RI511553 ") // -cr 522892A 522892B 511553A 511553B
CGMVersionMacroDefine(1847,IntersectionSurSurWithInits_PlinePCircle                    ,STY ,03-02-2006 ,"V5R16 SP4 - RI Externe attendu pour la R16SP4 ") // -cr 0518617A 0518617B 5018617C
CGMVersionMacroDefine(1848,HomotopyCrvSur_PostRun                                      ,CQI ,03-02-2006 ,"V5R16 SP4 - RI522191 ") // -cr A0522191 B0522191 C0522191
CGMVersionMacroDefine(1849,Propagation_JunctionEdge                                    ,cwm ,03-02-2006 ,"V5R16 SP4 - RI0521404 ")
CGMVersionMacroDefine(1850,CATSurfaceToCanonic_ClosedCylinder                          ,STY ,03-02-2006 ,"V5R16 SP4 - RI MNT ") // -cr 520776A 520776B
CGMVersionMacroDefine(1851,Sweep_EquivalentPointOnClosedCanonicSurface                 ,NLD ,06-02-2006 ,"V5R16 SP4 - RI520776 ") // Report de topologie sur surface canonique fermee
CGMVersionMacroDefine(1852,Sweep_Interpol_CheckParamsStability                         ,JSX ,06-02-2006 ,"V5R16 SP4 - Pb de stabilité Debug/Opti dans le cheminement (choix des parametres ou l\'on mesure l\'erreur) ") // odt multifaceblend7 case151 case152
CGMVersionMacroDefine(1853,VolumeDisconnect_NoRecursivePropagation                     ,ice ,06-02-2006 ,"V5R16 SP4 - zzIndus Sony_V5R7SP4_cfdx948_knobVOL ")
CGMVersionMacroDefine(1854,Intersect_CloseScarOnFreeEdge_Propagate                     ,ice ,10-02-2006 ,"V5R16 SP4 - RI522193 ") // propagation de la fermeture de la cicatrice sur bord libre
//CGMVersionMacroDefine(1855,Tess_0002                                                   ,TPD ,10-02-2006 ,"V5R16 SP4 ") // activation dernieres modifications maillages
CGMVersionMacroDefine(1856,Relim_ClosedInitEnhancementForDRL                           ,PRL ,10-02-2006 ,"V5R16 SP4 - RI ") // -cr A0521880 B0521880
CGMVersionMacroDefine(1857,Relim_FindCouplingOnSameFace                                ,PRL ,10-02-2006 ,"V5R16 SP4 - RI ") // -cr A0522212 B0522212
CGMVersionMacroDefine(1858,Draft_R16SP4                                                ,PFV ,10-02-2006 ,"V5R16 SP4 - RI 0512187 et 0512188 ") // -cr A0512188  B0512188  A0512187  B0512187
//CGMVersionMacroDefine(1859,Offset_NoReconvergeX2SAroundSmoothIVRep                     ,MNJ ,10-02-2006 ,"V5R16 SP4 - RI 501123 ") // promote -cr A0501123 B0501123
CGMVersionMacroDefine(1860,Fillet_NotchesWithMaxRelim                                  ,JMA ,10-02-2006 ,"V5R16 SP4 - complements de dev pour autofillet ")
//CGMVersionMacroDefine(1861,SkinExtrapol_NoLoopSwapDetection                            ,MNJ ,10-02-2006 ,"V5R16 SP4 - correction bug ")
CGMVersionMacroDefine(1862,Spline_Error_NLS                                            ,jbx ,10-02-2006 ,"V5R16 SP4 - CATSplineOperatorCX3 ") // -cr A0522898  B0522898
CGMVersionMacroDefine(1863,Fillet_CorrectPunchSkinOrientation                          ,JMA ,10-02-2006 ,"V5R16 SP4 - RI 523411 ") // -cr A0523411 B0523411
CGMVersionMacroDefine(1864,DraftSurfaceTool_SymetricSampling                           ,CQI ,10-02-2006 ,"V5R16 SP4 - ODT ")
CGMVersionMacroDefine(1865,Unfold_BetterMeshFromTess                                   ,SUH ,10-02-2006 ,"V5R16 SP4 - Dev, ODT ") // use of SetDoctor before tessellation
CGMVersionMacroDefine(1866,Unfold_EnhancedReport                                       ,SUH ,10-02-2006 ,"V5R16 SP4 - Dev ")
//CGMVersionMacroDefine(1867,CanonicalProjectionrCvSur_DegeneratedPEllipse               ,obh ,10-02-2006 ,"V5R16 SP4 - pour RR CGMTest_NewTopoN1FilletCrossParting3 KO ")
CGMVersionMacroDefine(1868,SurSurTg_CutOnSingularConvergence                           ,OBH ,10-02-2006 ,"V5R16 SP4 ")
CGMVersionMacroDefine(1869,IntersectionSurSurWithInits_BorderSolutionImprovement       ,sty ,10-02-2006 ,"V5R16 SP4 - Ri ") // -cr A522908 B522908
CGMVersionMacroDefine(1870,Extrapol_Until_NoTwistDetectionInFirstStage                 ,JSX ,17-02-2006 ,"V5R16 SP4 ") // Confusion sur le nom des variables   -cr a0524528
CGMVersionMacroDefine(1871,RSO_Approx2                                                 ,PMG ,17-02-2006 ,"V5R16 SP4 ") // prevention soucis de coherence des tolerance plus gestion cas degenere
CGMVersionMacroDefine(1872,Posage_MultiWire                                            ,jhn ,17-02-2006 ,"V5R16 SP4 ") // stabiliser l'orientation du posage en cas de wires connexes bodies invalides en entree autorises par Sheet Metal -cr 524635A 524635B
CGMVersionMacroDefine(1873,Sweep_Circle_ReferenceSurfaceAndSpineCaseV1                 ,NLD ,17-02-2006 ,"V5R16 SP4 ") // RI525412  -cr 525412a 525412b
CGMVersionMacroDefine(1874,CanonicalProjectionrCvSur_DegeneratedPEllipse               ,obh ,17-02-2006 ,"V5R16 SP4 ") // problème des pellipses degenrées dans la projection
CGMVersionMacroDefine(1875,Sweep_Interpol_ContinuousBehaviourV1                        ,NLD ,17-02-2006 ,"V5R16 SP4 ") // stabilisation multiplateformes Continuite du comportement pour de faibles variations de la fonction qualite
//CGMVersionMacroDefine(1876,Parallel_ExtrapOnConsecutivesWires                          ,AOV ,17-02-2006 ,"V5R16 SP4 - RI ") // check if the wires to extrap are issued from 2 consecutives wires in the input
CGMVersionMacroDefine(1877,UnFoldedAero_QuickComputation                               ,OAU ,17-02-2006 ,"V5R16 SP4 - RI 0522516A/B ") // -cr A0522516 B0522516
CGMVersionMacroDefine(1878,Intersect_CloseScar_ConnectOnBorder                         ,ice ,24-02-2006 ,"V5R16 SP4 - Positionnement des edges creees par CloseScar sur le bord si necessaire ")
CGMVersionMacroDefine(1879,SkinExtrapol_NoLoopSwapDetection                            ,MNJ ,24-02-2006 ,"V5R16 SP4 - dev pour AutoFillet ")
CGMVersionMacroDefine(1880,Offset_NoReconvergeX2SAroundSmoothIVRep                     ,MNJ ,24-02-2006 ,"V5R16 SP4 - RI ") // promote -cr A0501123 B0501123
CGMVersionMacroDefine(1881,Parallel_ConfusedNupletFix                                  ,REN/AOV,24-02-2006 ,"V5R16 SP4 - RI 515845 ")
//CGMVersionMacroDefine(1882,TrimSew_PropagAlongBorders                                  ,PRL ,27-02-2006 ,"V5R16 SP4 - Dev ")
CGMVersionMacroDefine(1883,MarshMallow_Level10                                         ,PMG ,27-02-2006 ,"V5R16 SP4 - RI ") // -cr A0525715 B0525715
CGMVersionMacroDefine(1884,Sweep_Interpol_ContinuousBehaviourV2                        ,NLD ,27-02-2006 ,"V5R16 SP4 - suite stabilisation cheminement. cas a indice decroissant ")
//CGMVersionMacroDefine(1885,New_Extract_Face                                            ,eqt ,27-02-2006 ,"V5R16 SP4 - Nouveau developpement sur l extract de face ")
CGMVersionMacroDefine(1886,HLR_RI526774_PerViewTorus                                   ,TPG ,03-03-2006 ,"V5R16 SP4 - RI526774 ")
CGMVersionMacroDefine(1887,Offset_NoConstraintOnClosure                                ,MNJ ,03-03-2006 ,"V5R16 SP4 - modele PSA ")
CGMVersionMacroDefine(1888,BasicTools_Offset_Planar                                    ,fds ,03-03-2006 ,"V5R16 SP4 - RI526306 ")
CGMVersionMacroDefine(1889,Coupling_Projection_TolerantModeling                        ,RHA ,03-03-2006 ,"V5R16 SP4 - RI Externe ") // No Odt KO
CGMVersionMacroDefine(1890,Intersection_PCrvPCrv_DegenNormal                           ,RHA ,03-03-2006 ,"V5R16 SP4 - RI externe ") // 0 Odts KO
CGMVersionMacroDefine(1891,New_Extract_Face                                            ,eqt ,03-03-2006 ,"V5R16 SP4 - Pour GSD ") // 2 autofillets ko ajout RLA
CGMVersionMacroDefine(1892,BissectorSurfaceOptim                                       ,CQI ,03-03-2006 ,"V5R16 SP4 - RI527135 Bissector surface deformation performances ") // -cr A0527135 B0527135 C0527135
//CGMVersionMacroDefine(1893,RattrapJournal_KeepOnNonModifiedFace                        ,ice ,06-03-2006 ,"V5R16 SP4 - on pose un ordre Keep sur les faces non modifiees lord d\'un split ou d\'un sewing ")
CGMVersionMacroDefine(1894,Blend_SmoothedCurvature                                     ,JSX ,06-03-2006 ,"V5R16 SP4 - Blend G2 : smooth de la courbure pour assurer le G0 dans le cas de supports juste G1 ") // -cr a0518242
CGMVersionMacroDefine(1895,TrimSew_PropagAlongBorders                                  ,PRL ,03-03-2006 ,"V5R16 SP4 - Pour AutoFillet ")
CGMVersionMacroDefine(1896,ProjectionrvSur_AdmissibilityOnPointedSurface               ,obh ,06-03-2006 ,"V5R16 SP4 - Modele ICem ")
//CGMVersionMacroDefine(1897,RattrapJournal_KeepOnNonModifiedFace                        ,ICE ,10-03-2006 ,"V5R16 SP4 ")
CGMVersionMacroDefine(1898,TopCleanCurve_IncompleteLayDown                             ,HLN ,10-03-2006 ,"V5R16 SP4 - CGMTest_SurfacicSweep86_RHA, Case867 : reference CATErrorID=7040 doit etre change en 6450 ") // Ajout traitement de detection de posage incomplet en new mode hybride plus throw // Suite a probleme dans CGMTest_SurfacicSweep78_Case785 apres reactivation
CGMVersionMacroDefine(1899,Offset_TheoreticalResult                                    ,MNJ ,10-03-2006 ,"V5R16 SP4 - RI 527953 ") // promote -cr A0527953 B0527953 C0527953
CGMVersionMacroDefine(1900,Prism_Surfacic_Lateral                                      ,FDS ,10-03-2006 ,"V5R16 SP4 - RI524643 ")
//CGMVersionMacroDefine(1901,CATIntersectionSurSur_BestReturningPoint                    ,RHA ,10-03-2006 ,"V5R16 SP4 - RI Externe ") // No
//CGMVersionMacroDefine(1902,SplitHelix                                                  ,ICE ,13-03-2006 ,"V5R16 SP4 ")
CGMVersionMacroDefine(1902,Polar_Extremum_Point                                        ,fds ,17-03-2006 ,"V5R16 SP4 - RI524361 ") // Crisit , activation master a prevoir


//=========================================================================================================
// V5R16 SP5
//=========================================================================================================
CGMVersionMacroDefine(1905,Corner_NupletRelimitedByGeometryFix                         ,REN/AOV,17-03-2006 ,"V5R16 SP5 - RI corner closed nuplet ribbon interrupted on closure contact RR ") // promote -cr 524252A  524252B
CGMVersionMacroDefine(1906,Offset_WrongEdgeFromOtherCollision                          ,LAP ,17-03-2006 ,"V5R16 SP5 - 525590AB ") // -cr A0525590 B0525590
CGMVersionMacroDefine(1907,ImplicitSpine_ForceLine_Two3DTangentProfilesCase            ,JSX ,17-03-2006 ,"V5R16 SP5 - Cas ou les plans moyens ne sont pas pertinant. l axe de rotation produit des twist ") // RI HOT FIX 525717
CGMVersionMacroDefine(1908,PtSurRevol_ProfileLimits                                    ,CQI ,17-03-2006 ,"V5R16 SP5 - Dev ") // Bug
//CGMVersionMacroDefine(1909,Mass_Inertia_Wire                                           ,fds ,17-03-2006 ,"V5R16 SP5 - Correction calcul inertie wire pour KDI  stabilité parametrage + inertie relatif au CDG  // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheetmetal ) ") // Pour KDI  ODT sheet
CGMVersionMacroDefine(1910,TrimByThick_AllowBorderInDisco3D_HealingGeoLevel4           ,MNJ ,17-03-2006 ,"V5R16 SP5 - RI ext ") // promote -cr A0526569 B0526569
CGMVersionMacroDefine(1911,Fillet_R16SP5                                               ,RR  ,17-03-2006 ,"V5R16 SP5 - RI ")
CGMVersionMacroDefine(1912,CATIntersectionSurSurWithInits_TangentOrientation           ,sty ,24-03-2006 ,"V5R16 SP5 ")
CGMVersionMacroDefine(1913,TrimShell_SingleReport                                      ,ice ,24-03-2006 ,"V5R16 SP5 - RI521995 ")
CGMVersionMacroDefine(1914,Regul_FreeBorderConstraint                                  ,CWM ,24-03-2006 ,"V5R16 SP5 - RI ") // -cr A0524337 B0524337 C0524337 A0526773 B0526773
CGMVersionMacroDefine(1915,HLR_RI529501_TinySilhouette                                 ,TPG ,24-03-2006 ,"V5R16 SP5 - RI529501 ") // activation immediate
//CGMVersionMacroDefine(1916,LayDownCrvSurPSS                                            ,OBH ,24-03-2006 ,"V5R16 SP5 - Dev chgmts de références de CGMTest_GeometryReplayLayDownCrvSur ")
CGMVersionMacroDefine(1917,TrimSew_ExtrapolRCFForAlign                                 ,PRL ,24-03-2006 ,"V5R16 SP5 - RI ") // -cr  A0528817  B0528817
CGMVersionMacroDefine(1918,TrimSew_ReplaceFaceWithIdSurf                               ,PRL ,24-03-2006 ,"V5R16 SP5 - RI ") // -cr A0528276 B0528276
CGMVersionMacroDefine(1919,Rib_Relim_ActivateNonCompulsoryPropag2                      ,PRL ,24-03-2006 ,"V5R16 SP5 - RI ") // -cr  B0528106  C0528106
CGMVersionMacroDefine(1920,Healing_Level20                                             ,JJC ,24-03-2006 ,"V5R16 SP5 - Improvment for local healing G0 on boundaries ")
CGMVersionMacroDefine(1921,Unfold_IsoParamTransfer                                     ,SUH ,24-03-2006 ,"V5R16 SP5 - RI ") // for IR 0527383
CGMVersionMacroDefine(1922,Offset_OldInitsFilter                                       ,MNJ ,24-03-2006 ,"V5R16 SP5 - RI ") // promote -cr A0526875 B0526875
CGMVersionMacroDefine(1923,Mass_Inertia_Wire                                           ,fds ,24-03-2006 ,"V5R16 SP5 - Réparation ODT sheetmetal ")
CGMVersionMacroDefine(1924,Parallel_ExtrapOnConsecutivesWires                          ,AOV ,24-03-2006 ,"V5R16 SP5 - bug dans les extrapolations quand une solution est hors support ")
CGMVersionMacroDefine(1925,Parallel_GraphSolverTangencyPoint                           ,AOV ,24-03-2006 ,"V5R16 SP5 - RI ")
CGMVersionMacroDefine(1926,Offset_StabilizeIntersectionPcurvePcurve                    ,LAP ,24-03-2006 ,"V5R16 SP5 - ODT instable sur HP ")
CGMVersionMacroDefine(1927,NullTangentExtremityEndProjection                           ,obh ,27-03-2006 ,"V5R16 SP5 - RI 0528147 ")
CGMVersionMacroDefine(1928,Fillet_EdgesJournalingForMultiRibbonCorrections_2           ,CWM ,27-03-2006 ,"V5R16 SP5 - RI ") // -cr A0512130
CGMVersionMacroDefine(1929,TrimByThick_SolveClashIfSameSurfBetween2Volumes             ,MNJ ,31-03-2006 ,"V5R16 SP5 - RI ") // promote -cr A0523383 B0523383
CGMVersionMacroDefine(1930,RemoveFacesInShell_NewBorderEdgeJournal                     ,LAP ,31-03-2006 ,"V5R16 SP5 - RI 522280ABC ") // -cr 522280A 522280B 522280C
CGMVersionMacroDefine(1931,Extremum_Cylinder                                           ,fds ,31-03-2006 ,"V5R16 SP5 - RI528108 ") // Pb de revol et d extremum  RI528108
CGMVersionMacroDefine(1932,Projection_Pole                                             ,OBH ,31-03-2006 ,"V5R16 SP5 - RI 0529418 ")
CGMVersionMacroDefine(1933,EucParallel_Init_CylinderEquation                           ,CQI ,31-03-2006 ,"V5R16 SP5 - RI530074 ")
CGMVersionMacroDefine(1934,Fillet_SmartSnapping_3                                      ,RR  ,31-03-2006 ,"V5R16 SP5 - Robustesse ")
CGMVersionMacroDefine(1935,HybridVarOffset_NewConstraintComputer                       ,LAP ,31-03-2006 ,"V5R16 SP5 - Dev pour TMC ")
CGMVersionMacroDefine(1936,Fill_PlanarDetectionUsingPcurve                             ,JSX ,07-04-2006 ,"V5R16 SP5 - plan du contour detection logique et non plus geometrique car instable opti ") // -cr a529506 b529506
//CGMVersionMacroDefine(1937,LayDownCrvSurPSS                                            ,OBH ,04-04-2006 ,"V5R16 SP5 ")
//CGMVersionMacroDefine(1938,Projection_VertexConnexion                                  ,RLA ,03-04-2006 ,"V5R16 SP5 - dev connexion des vertices donnes par la projection geometrique ") // DEV
CGMVersionMacroDefine(1939,Parting_CutEdgeSignature                                    ,PRL ,07-04-2006 ,"V5R16 SP5 - RI ") // -cr  A0530600  B0530600  C0530600
CGMVersionMacroDefine(1940,Relim_CheckEdgeWithTgts                                     ,PRL ,07-04-2006 ,"V5R16 SP5 - RI ")
CGMVersionMacroDefine(1941,Blend_NoCellReductionInVertexCouplingCase                   ,NLD ,07-04-2006 ,"V5R16 SP5 ")
CGMVersionMacroDefine(1942,Sweep_CanonicityWithPCircleV2                               ,NLD ,07-04-2006 ,"V5R16 SP5 - generation de surfaces canoniques avec guides de type PCircle ")
CGMVersionMacroDefine(1943,UnfoldFrF_NewTessParams                                     ,SUH ,07-04-2006 ,"V5R16 SP5 - Dev ") // for simple cases to work
CGMVersionMacroDefine(1944,Unfold_TearEdgeTransfer                                     ,FDL ,07-04-2006 ,"V5R16 SP5 - transfer de courbe SUH ")
CGMVersionMacroDefine(1945,Projection_VertexConnexion                                  ,RLA ,07-04-2006 ,"V5R16 SP5 - conection de verties apres la projection geometrique ")
CGMVersionMacroDefine(1946,Extrude_Invalid_NOKIA_Curve                                 ,FDS ,07-04-2006 ,"V5R16 SP5 - Resolution pb extrude de NOKIA ") // Activation immediate pour 07/04
CGMVersionMacroDefine(1947,EuclidianParallel_ApplyOffset                               ,CQI ,07-04-2006 ,"V5R16 SP5 - RI531843 ") // -cr A0531843 B0531843
CGMVersionMacroDefine(1948,ConstantFilletInterpol_NullAngle                            ,CQI ,07-04-2006 ,"V5R16 SP5 - RI530878 ") // -cr A0530878 B0530878 C0530878
CGMVersionMacroDefine(1949,Fillet_SelfIntersectWithCompatibleLinkEdges                 ,CWM ,07-04-2006 ,"V5R16 SP5 - RI ") // -cr A0531549 B0531549
CGMVersionMacroDefine(1950,LayDownCrvSurPSS                                            ,OBH ,07-04-2006 ,"V5R16 SP5 ") // odt casse  CGMTest_GeometryReplayLayDownCrvSur + Import_FaceWithSurf190
CGMVersionMacroDefine(1951,Healing_Level21                                             ,JJC ,10-04-2006 ,"V5R16 SP5 - RI ") // -cr A0530923 B0530923
CGMVersionMacroDefine(1952,NewJoin_NonManifLoop                                        ,jbx ,10-04-2006 ,"V5R16 SP5 - RI ") // -cr A0532149  B0532149  C0532149
CGMVersionMacroDefine(1953,Regul_CellFollowUpCorrection                                ,CWM ,14-04-2006 ,"V5R16 SP5 - RI ")
CGMVersionMacroDefine(1954,Unfold_Problems1                                            ,SUH ,14-04-2006 ,"V5R16 SP5 - RI ") // -cr A0529767 B0529767 A0525205 B0525205
CGMVersionMacroDefine(1955,Fillet_PropagateActivationInRlm                             ,JMA ,14-04-2006 ,"V5R16 SP5 - corrections for Long Fillet propagation with coarse ")
CGMVersionMacroDefine(1956,CornerPtPCrv_Correction                                     ,OBH ,14-04-2006 ,"V5R16 SP5 - RI0532579 ")
CGMVersionMacroDefine(1957,CurveAffineSupport_CorrectionPCurveOnPlane                  ,OBH ,14-04-2006 ,"V5R16 SP5 ")
CGMVersionMacroDefine(1958,SplitWire_UntouchedAndClosed                                ,jbx ,21-04-2006 ,"V5R16 SP5 ") // -cr A0532512 B0532512  C0532512
CGMVersionMacroDefine(1959,Chamfer_G1HealingLongFace                                   ,SOU ,21-04-2006 ,"V5R16 SP5 - To avoid large deformation due to G1 healing for long chamfer face ") // -cr A0530923 B0530923
CGMVersionMacroDefine(1960,RattrapJournal_KeepOnNonModifiedFace                        ,ICE ,21-04-2006 ,"V5R16 SP5 ")
CGMVersionMacroDefine(1961,GeodesicParallel_ReportInitWithConfusion                    ,CQI/AOV,24-04-2006 ,"V5R16 SP5 - RI 532332 pb transfert init sur face etroite ")
CGMVersionMacroDefine(1962,MarshMallow_Level11                                         ,PMG ,28-04-2006 ,"V5R16 SP5 - Pb perfo ")
CGMVersionMacroDefine(1963,Offset_WireFrameRebuildConvergence                          ,MNJ ,28-04-2006 ,"V5R16 SP5 - RIs ") // promote -cr A0527160 B0527160 C0527160 A0531191 B0531191
CGMVersionMacroDefine(1964,UnfoldFrF_TwistDetection                                    ,SUH ,28-04-2006 ,"V5R16 SP5 - Dev ")
CGMVersionMacroDefine(1965,SkinExtrapol_WorkSectors                                    ,MNJ ,28-04-2006 ,"V5R16 SP5 - RI ") // activation immediate le 28-04-2006
CGMVersionMacroDefine(1966,Fillet_InitTransferAfterTwist2                              ,RR  ,03-05-2006 ,"V5R16 SP5 - Robustesse ")
CGMVersionMacroDefine(1967,Blend_TopoSweepInfra3                                       ,JSX ,05-05-2006 ,"V5R16 SP5 - Bug dans les directions en cas de wire fermé ") // -cr a533310 b533310
CGMVersionMacroDefine(1968,Thick_ReplaceMultiPCGuideByBisector                         ,MNJ ,05-05-2006 ,"V5R16 SP5 - regression sur modele client ") // activation immediate le 05-05-2006
CGMVersionMacroDefine(1969,Draft_R16SP5                                                ,PFV ,05-05-2006 ,"V5R16 SP5 - RI 0535034 ") // -cr A0535034 B0535034 C0535034
CGMVersionMacroDefine(1970,UnFoldedAero_Twist                                          ,OAU ,09-05-2006 ,"V5R16 SP5 - Gestion   Twist ") // -cr A0525330 B0525330
CGMVersionMacroDefine(1971,DistanceMin_OnVertices                                      ,JHN ,10-05-2006 ,"V5R16 SP5 - RI 536047 ") // toyota


//=========================================================================================================
// V5R16 SP6
//=========================================================================================================
CGMVersionMacroDefine(1976,TopModify_EdgesConf                                         ,fdn ,12-05-2006 ,"V5R16 SP6 - RI 523246A 523246B ") // -cr 523246A 523246B
CGMVersionMacroDefine(1977,Sweep_SmoothOptionNotToLose                                 ,NLD ,12-05-2006 ,"V5R16 SP6 ")
CGMVersionMacroDefine(1978,Fillet_ActivateNewCandidates                                ,CWM ,15-05-2006 ,"V5R16 SP6 - RI ") // -cr A0533930 B0533930
CGMVersionMacroDefine(1979,TrimShell_JournalMultiTrim                                  ,ice ,15-05-2006 ,"V5R16 SP6 - RI535196 et RI521995 ")
CGMVersionMacroDefine(1980,CloseScarOnFreeEdge_AnalyseContext                          ,ice ,19-05-2006 ,"V5R16 SP6 - eviter la creation abusive d\'edge sur les bords libres ")
CGMVersionMacroDefine(1981,Offset_AlreadyExistingTptInjection                          ,MNJ ,19-05-2006 ,"V5R16 SP6 - modele SONY ")
CGMVersionMacroDefine(1982,Shell_JournalCorrectionLevel2                               ,LAP ,19-05-2006 ,"V5R16 SP6 - RI 536776ABC ") // -cr 536776A 536776B 536776C
CGMVersionMacroDefine(1983,Projection_DegeneratedProjected                             ,JHN ,19-05-2006 ,"V5R16 SP6 - bonne ") // adl_promote -cr 526017A 526017B
CGMVersionMacroDefine(1984,SurSurTg_Singul_Threshold                                   ,obh ,19-05-2006 ,"V5R16 SP6 - RI A0536147 ")
CGMVersionMacroDefine(1985,NewProjection_MergeAdmissibleSolution                       ,OBH ,19-05-2006 ,"V5R16 SP6 - DEV JHN SMARTPROJETION ")
CGMVersionMacroDefine(1986,VariableFillet_CliffEdge_CheckSolution                      ,SOU ,19-05-2006 ,"V5R16 SP6 - RI ") // -cr A0536520
CGMVersionMacroDefine(1987,Fillet_SmoothRelim_StabilizeOrientations                    ,CWM ,19-05-2006 ,"V5R16 SP6 - RI ") // -cr A0511624
CGMVersionMacroDefine(1988,IntersectionLineSur_Adjustlevel                             ,RHA ,19-05-2006 ,"V5R16 SP6 - RI Externe ") // adl_promote -cr A0536992 B0536992
CGMVersionMacroDefine(1989,Sweep_RattrapHomogenizationProblemV1                        ,NLD ,24-05-2006 ,"V5R16 SP6 ") // -cr 531711a 531711b
CGMVersionMacroDefine(1990,TopHeal_AvoidInvalidElt                                     ,PRL ,24-05-2006 ,"V5R16 SP6 - Dev ")
CGMVersionMacroDefine(1991,Fillet_R16SP6                                               ,RR  ,24-05-2006 ,"V5R16 SP6 ") // RI
CGMVersionMacroDefine(1992,HybridVarOffset_NewTopAssembleCall                          ,LAP ,24-05-2006 ,"V5R16 SP6 - RI538303AB ") // -cr A0538303 B0538303
CGMVersionMacroDefine(1993,Sweep_ImplicitSpine_XScaleIsoV1                             ,NLD ,24-05-2006 ,"V5R16 SP6 ")
CGMVersionMacroDefine(1994,CATSurfaceToCanonic_ExtractIsopar                           ,sty ,24-05-2006 ,"V5R16 SP6 ")
CGMVersionMacroDefine(1995,TrimByThick_SharpLyingOnCvg                                 ,MNJ ,24-05-2006 ,"V5R16 SP6 - RIs ") // Activation immediate le 24/05/2006 + promote -cr A0534509 A0536147 B0536147
CGMVersionMacroDefine(1996,GetSurfaceValidMaxBoxWithConfig_GEO                         ,OBH ,29-05-2006 ,"V5R16 SP6 ")
CGMVersionMacroDefine(1997,UnFoldedAero_ReportLaw                                      ,OAU ,29-05-2006 ,"V5R16 SP6 - Migration de CATMassProperties1D à CATCrvLengths (robustesse + perfo) ")
CGMVersionMacroDefine(1998,GetSurfaceValidMaxBoxForProcCurve                           ,OBH ,29-05-2006 ,"V5R16 SP6 - RI A0536050 ")
CGMVersionMacroDefine(1999,Relim_ExtrRibInvalidationForReverseOri                      ,PRL ,29-05-2006 ,"V5R16 SP6 - RI ") // -cr  A0538293  B0538293
CGMVersionMacroDefine(2000,NullTangent_twoExtremities                                  ,OBH ,02-06-2006 ,"V5R16 SP6 - RI A0538158 ") // traitementd e tangentes nulles dans la projection des deux extrémités
CGMVersionMacroDefine(2001,LawEqDistCrv_CheckLineLimits                                ,CQI ,02-06-2006 ,"V5R16 SP6 - RI536841 ") // -cr A0536841 B0536841
CGMVersionMacroDefine(2002,Fill_ConfusionNodeDetection                                 ,MPS ,05-06-2006 ,"V5R16 SP6 - RI A0535653  B0535653 ")
CGMVersionMacroDefine(2003,CATIntersectionSurSur_PolePolePoint                         ,RHA ,05-06-2006 ,"V5R16 SP6 - RI externe ") // adl_promote -cr A0539876 B0539876
//CGMVersionMacroDefine(2005,Fillet_EdgesJournalingForTrueMultiRibbon                    ,CWM ,09-06-2006 ,"V5R16 SP6 - RI ") // -cr B0517515 C0517515
CGMVersionMacroDefine(2006,IntersectionCrvSur_Reliability                              ,CQI ,09-06-2006 ,"V5R16 SP6 - RI 540025 539227 ") // -cr A0540025 B0540025 C0540025 A0539227 B0539227
CGMVersionMacroDefine(2007,Intersection_RejectSingularMarching                         ,KLX ,12-06-2006 ,"V5R16 SP6 - RI 538165 ") // -cr 538165A 538165B 538165C
CGMVersionMacroDefine(2008,ApproxNetwork_Level4                                        ,PMG ,12-06-2006 ,"V5R16 SP6 - Bug dans l\'apply ")
//CGMVersionMacroDefine(2009,AutoFillet_TwiceRadiusThinWall                              ,JHG ,12-06-2006 ,"V5R16 SP6 - RI ")
CGMVersionMacroDefine(2010,GeodesicPtPt_BugTol                                         ,AOV ,12-06-2006 ,"V5R16 SP6 - pb composite ")
//CGMVersionMacroDefine(2011,Unfold_CommonPCurveProb                                     ,SUH ,16-06-2006 ,"V5R16 SP6 - RI ") // -cr A0537757 B0537757
CGMVersionMacroDefine(2012,CATSurfaceToCanonic_NewRadiusComparison                     ,sty ,16-06-2006 ,"V5R16 SP6 - ri ")
CGMVersionMacroDefine(2013,CATIntersectionSurSurWithInits_NewDeformIndex               ,sty ,16-06-2006 ,"V5R16 SP6 - dev ")
CGMVersionMacroDefine(2014,TrimByThick_SolveClashIfSameSurfBetween2VolumesLevel2       ,MNJ ,16-06-2006 ,"V5R16 SP6 - RI ")
CGMVersionMacroDefine(2015,Blend_TopoSweepInfra4                                       ,JSX ,16-06-2006 ,"V5R16 SP6 - Lois de tension en courbure non prises en compte ")
CGMVersionMacroDefine(2016,ShellFromClosedWire_MultiCheckAutoCrossing                  ,FDS ,16-06-2006 ,"V5R16 SP6 - RI540944A ")
CGMVersionMacroDefine(2017,Relim_RCFSharpnessForUnkResults                             ,PRL ,16-06-2006 ,"V5R16 SP6 - RI ") // -cr A0539051 B0539051
CGMVersionMacroDefine(2018,Set3DTol_IntersectionPCrvGap                                ,RHA ,16-06-2006 ,"V5R16 SP6 - RI externe ")
CGMVersionMacroDefine(2019,TopModify_Privilege_Border                                  ,fdn ,20-06-2006 ,"V5R16 SP6 - RI ") // -cr  A0526964  B0526964

#endif
