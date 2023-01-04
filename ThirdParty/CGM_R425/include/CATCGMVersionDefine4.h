#ifndef CATCGMVersionMacroDefine4_h
#define CATCGMVersionMacroDefine4_h
// COPYRIGHT DASSAULT SYSTEMES  2002



//=========================================================================================================
// V5R17 GA
//=========================================================================================================
CGMVersionMacroDefine(2024,Blend_TopoSweepInfraActivation                              ,JSX ,21-06-2006 ,"V5R17 GA ") // R17GA Ne pas activer sur un SP de la R16
CGMVersionMacroDefine(2025,SplitHelix                                                  ,ICE ,21-06-2006 ,"V5R17 GA ") // R17GA Ne pas activer sur un SP de la R16
//CGMVersionMacroDefine(2026,EdgeSharpness_UseSides                                      ,fdn ,21-06-2006 ,"V5R17 GA - RI ") // -cr  B0511094  C0511094
CGMVersionMacroDefine(2027,NonManifoldVertexIterator                                   ,fdn ,21-06-2006 ,"V5R17 GA - RI ") // -cr B0511711 C0511711


//=========================================================================================================
// V5R17 SP1
//=========================================================================================================
CGMVersionMacroDefine(2031,Offset_KeepFacesWithoutAncestorIVRep                        ,LAP ,23-06-2006 ,"V5R17 SP1 - RI 533988AB ") // -cr 533988A 533988B
CGMVersionMacroDefine(2032,Sewing_AjouteFacesComplWithInnerLoop                        ,PRL ,23-06-2006 ,"V5R17 SP1 - RI ") // -cr A0540884  B0540884
CGMVersionMacroDefine(2033,SystemXY_EdgeTreatment                                      ,CQI ,23-06-2006 ,"V5R17 SP1 - RI522426 ") // -cr A0522426 B0522426 C0522426
CGMVersionMacroDefine(2034,TrimByThick_ParasiticalCollisionEReps                       ,MNJ ,23-06-2006 ,"V5R17 SP1 - RIs MNT ") // -cr B0542281 C0542281 A0541732 B0541732
CGMVersionMacroDefine(2035,Fillet_R17SP1                                               ,RR  ,26-06-2006 ,"V5R17 SP1 - RI ") // R17SP1
CGMVersionMacroDefine(2036,CATIntersectionSurSur_BestReturningPoint                    ,RHA ,26-06-2006 ,"V5R17 SP1 - Ris externes avec gros TAT ")
CGMVersionMacroDefine(2037,EdgeSharpness_UseSides                                      ,fdn ,27-06-2006 ,"V5R17 SP1 - RI ") // -cr  B0511094  C0511094
CGMVersionMacroDefine(2038,Sweep_ImplicitSpine_XScaleNonIsoV1                          ,NLD ,28-06-2006 ,"V5R17 SP1 ")
CGMVersionMacroDefine(2039,ImplicitSpine_UseLogicalProfileClosure                      ,nld ,28-06-2006 ,"V5R17 SP1 ")
CGMVersionMacroDefine(2040,Sweep_TwistedAreasInC0Case                                  ,NLD ,28-06-2006 ,"V5R17 SP1 ")
CGMVersionMacroDefine(2041,Unfold_CommonPCurveProb                                     ,SUH ,28-06-2006 ,"V5R17 SP1 - RI ") // -cr A0537757 B0537757
CGMVersionMacroDefine(2042,AutoFillet_ClosedBlends                                     ,JHG ,28-06-2006 ,"V5R17 SP1 - Ri0539276 ")
CGMVersionMacroDefine(2043,MarshMallow_Level12                                         ,PMG ,28-06-2006 ,"V5R17 SP1 - RI A0540518 ") // -cr A0540518 B0540518
CGMVersionMacroDefine(2044,Prism_LimitCloseFromOffset                                  ,FDS ,28-06-2006 ,"V5R17 SP1 - RI542663 ")
CGMVersionMacroDefine(2045,TrimByThick_SharpLyingOnTrimBorderLevel2                    ,MNJ ,30-06-2006 ,"V5R17 SP1 - ODT KO Rel + RIs ") // promote -cr A0540177 B0540177 A0543068
CGMVersionMacroDefine(2046,Fillet_EdgesJournalingForTrueMultiRibbon                    ,CWM ,30-06-2006 ,"V5R17 SP1 - RI ") // -cr B0517515 C0517515
CGMVersionMacroDefine(2047,ConnectCheckerCrvCrv_NewOverlap                             ,CQI ,30-06-2006 ,"V5R17 SP1 - Dev FSS ")
CGMVersionMacroDefine(2048,Extrapol_Blend_IterateOnSmoothEdgesForTangentMode2          ,JSX ,30-06-2006 ,"V5R17 SP1 - Pb dans le journal d\'extrapolation en mode Modif (info sur edge interne) ")
CGMVersionMacroDefine(2049,Extrapol_Blend_IterateOnSmoothEdgesForTangentMode3          ,JSX ,30-06-2006 ,"V5R17 SP1 - RI 536974 mode edge tang : cas vertex concave ") // promote -cr a536974 b536974
CGMVersionMacroDefine(2050,Relim_Parting_IsCellOnRlmComplLoop                          ,PRL ,03-07-2006 ,"V5R17 SP1 - RI  activation immediate ") // -cr  A0542260  B0542260
CGMVersionMacroDefine(2051,WireMultiTrim_KeepLyingOn                                   ,ice ,03-07-2006 ,"V5R17 SP1 ")
CGMVersionMacroDefine(2052,Unfold_AveragePositioningOnMulitFaces                       ,SUH ,03-07-2006 ,"V5R17 SP1 - Dev ")
CGMVersionMacroDefine(2053,TangentLinePCirclePCurveCorrection                          ,obh ,03-07-2006 ,"V5R17 SP1 - Ri  A0541873 ")
CGMVersionMacroDefine(2054,Fill_AutoFillet_SweepTreatment                              ,MPS ,07-07-2006 ,"V5R17 SP1 - GeomFE donne un resultat  trop tendu dans le cas de deux surfaces sweep  en angle droit ")
CGMVersionMacroDefine(2055,Parallel_RadialSortSmallAngle                               ,AOV ,07-07-2006 ,"V5R17 SP1 - RI ") // -cr A0538946 B0538946
//CGMVersionMacroDefine(2056,GeodesicPtDir_IncreaseControl                               ,CQI ,07-07-2006 ,"V5R17 SP1 - cf. RI506643 ") // Increase error control before last step computation
//CGMVersionMacroDefine(2057,CleanCurve_DataReductionStability1                          ,RNO ,07-07-2006 ,"V5R17 SP1 - Increase cross platform stability in the DataReductionStep ") // promote -cr A0541924 B0541924  A0541922  B0541922
CGMVersionMacroDefine(2058,UnFoldedAero_CanonicDrop1                                   ,OAU ,10-07-2006 ,"V5R17 SP1 - RI ") // -cr 0543917A 0543917B
CGMVersionMacroDefine(2059,Healing_Level22                                             ,JJC ,13-07-2006 ,"V5R17 SP1 - RI542341 ") // -cr A0542341 B0542341
//CGMVersionMacroDefine(2060,Fillet_NewInitialisationOfShiftedTracks_3                   ,CWM ,13-07-2006 ,"V5R17 SP1 - Test avec ruban pour inits en biais ")
CGMVersionMacroDefine(2061,ExtrapolConstantFilletCrvSur                                ,CQI ,13-07-2006 ,"V5R17 SP1 - Dev (see RI524272) ")
CGMVersionMacroDefine(2062,SymmetricTriTangentPCurve                                   ,OBH ,17-07-2006 ,"V5R17 SP1 - Ri A0539852 ")
//CGMVersionMacroDefine(2063,NewDirectionnalProjection                                   ,OBH ,21-07-2006 ,"V5R17 SP1 - RI A0531125 ") // 20 ref a livrer le 21-07-2006
CGMVersionMacroDefine(2064,Fillet_NewInitialisationOfShiftedTracks_3                   ,CWM ,21-07-2006 ,"V5R17 SP1 - Detection des inits en biais grace au PlanarRibMaker ")
CGMVersionMacroDefine(2065,CleanCurve_DataReductionStability1                          ,RNO ,21-07-2006 ,"V5R17 SP1 - Amelioration Perfo et stabilisation de l\'operateur ")
//CGMVersionMacroDefine(2066,AutoFillet_AutomaticSetback                                 ,JHG ,21-07-2006 ,"V5R17 SP1 ")
CGMVersionMacroDefine(2067,AutoFillet_GoodFilletInInSelection                          ,JHG ,21-07-2006 ,"V5R17 SP1 - RI534782 ") // -cr A0534782 B0534782 C0534782
CGMVersionMacroDefine(2068,Extrapol_NoCatchWithDirectionalEdgesV2                      ,NLD ,21-07-2006 ,"V5R17 SP1 - RI546274 ") // -cr 546274a 546274b


//=========================================================================================================
// V5R17 SP2
//=========================================================================================================
CGMVersionMacroDefine(2072,Line_MultiplePointSelection                                 ,FDS ,04-08-2006 ,"V5R17 SP2 - RI545008 ")
CGMVersionMacroDefine(2073,SimilarCurve_2DTangent_ZYVA                                 ,NLD ,04-08-2006 ,"V5R17 SP2 - Z/Y values inverted in 2D tangent correction ")
CGMVersionMacroDefine(2074,Thick_PlanarDirectionalSurfaceLevel2                        ,MNJ ,04-08-2006 ,"V5R17 SP2 - RIs ") // promote -cr A0540517 B0540517 A0542682 B0542682 A0542998 B0542998 A0544102 B0544102
CGMVersionMacroDefine(2075,Fillet_MultiRibbon_SymmetrizeRibInits                       ,cwm ,04-08-2006 ,"V5R17 SP2 - RI ") // -cr B0545124 C0545124
CGMVersionMacroDefine(2076,DraftRL_ConfusedNupletForCoveredFaces                       ,PFV ,04-08-2006 ,"V5R17 SP2 - BMW ") // promote -cr  B0547700  C0547700  D0547700
CGMVersionMacroDefine(2077,Sweep_DoNotTrustSurfaceToCanonicMapping                     ,NLD ,04-08-2006 ,"V5R17 SP2 ") // -cr 547427
CGMVersionMacroDefine(2078,Fillet_OrientationTuningForInitialisation                   ,CWM ,04-08-2006 ,"V5R17 SP2 - RI ")
CGMVersionMacroDefine(2079,ReflectCurveSingular                                        ,OBH ,04-08-2006 ,"V5R17 SP2 - RI A0545122 ")
CGMVersionMacroDefine(2080,CanonicProjectionCorrectionOnCylinder                       ,obh ,04-08-2006 ,"V5R17 SP2 - A0546773 ")
//CGMVersionMacroDefine(2081,CleanCurve_StabilityImprovement2                            ,RNO ,08-08-2006 ,"V5R17 SP2 - Tentatives pour ameliorer le comportement inter plateforme (Notamment ODT GSMCurveSmoothFrozenEltDiscontinuity ) ") // promote -cr B0541922 A0541922
CGMVersionMacroDefine(2082,Projection_ClosedResult                                     ,JHN ,08-08-2006 ,"V5R17 SP2 - RI 544251 ") // adl_promote -cr 544251B 544251A 544251C
CGMVersionMacroDefine(2083,HLR_CutCusp                                                 ,BPG ,08-08-2006 ,"V5R17 SP2 - IR540667 ")
CGMVersionMacroDefine(2084,CleanCurve_StabilityImprovement2                            ,RNO ,11-08-2006 ,"V5R17 SP2 - Tentatives pour ameliorer le comportement inter plateforme (Notamment ODT GSMCurveSmoothFrozenEltDiscontinuity ) ") // promote -cr B0541922 A0541922
CGMVersionMacroDefine(2085,Corner_MultipleConfusion                                    ,FDS ,11-08-2006 ,"V5R17 SP2 - RI5478548 ") // Activation immédiate Vendredi 11 aout -cr A0547548 B0547548 C0547548
CGMVersionMacroDefine(2086,TrimByThick_EdgeFromSingleAncestorVRepLevel1                ,LAP ,11-08-2006 ,"V5R17 SP2 - ODT casse dans une convergence ") // Activation pour le 11 Aout 2006
CGMVersionMacroDefine(2087,Offset_MultiGuidePCDetection                                ,MNJ ,11-08-2006 ,"V5R17 SP2 - RIs ") // promote -cr A0547189 B0547189 C0547189 B0548212 C0548212
CGMVersionMacroDefine(2088,GeodesicPtDir_RunOnSphere                                   ,CQI ,11-08-2006 ,"V5R17 SP2 - RI499656 : pole management ") // -cr B0499656 C0499656
CGMVersionMacroDefine(2089,GeodesicPtDir_IncreaseControl                               ,CQI ,11-08-2006 ,"V5R17 SP2 - pt dir enhancement for MTorres ") // -cr 540881B 540881C
CGMVersionMacroDefine(2090,IntersectionPCrvPCrv_UVDistortionOnCylinder                 ,obh ,11-08-2006 ,"V5R17 SP2 - RI A0547725 ")
CGMVersionMacroDefine(2091,Prism_Relimitation_Tangent                                  ,fds ,18-08-2006 ,"V5R17 SP2 - RI547809 ") // -cr A0547809 B0547809
CGMVersionMacroDefine(2092,Thick_SelectVolumeLevel2                                    ,MNJ ,18-08-2006 ,"V5R17 SP2 - RI 0548443 ") // promote -cr A0548443 B0548443 C0548443
CGMVersionMacroDefine(2093,TrimByThick_G1ContactOnConvexSharpEdge                      ,MNJ ,18-08-2006 ,"V5R17 SP2 - dev ")
CGMVersionMacroDefine(2094,Fillet_CleanCurveMappingCorrection                          ,CWM ,18-08-2006 ,"V5R17 SP2 - RI ") // promote -cr A0548698 B0548698
CGMVersionMacroDefine(2095,ProjectCrvSurMapX_Filter                                    ,CQI ,18-08-2006 ,"V5R17 SP2 - ODT CATSmaDFeature ")
CGMVersionMacroDefine(2096,Homotopy_Singular                                           ,CQI ,18-08-2006 ,"V5R17 SP2 - ODT KO IRIX ")
CGMVersionMacroDefine(2097,EdgePropag_NonManifold                                      ,fds ,18-08-2006 ,"V5R17 SP2 - RI548986 ") // -cr A0548986 B0548986 C0548986
CGMVersionMacroDefine(2098,Offset_PropagateInitMatterOri                               ,LAP ,18-08-2006 ,"V5R17 SP2 - Convergence ")
CGMVersionMacroDefine(2099,SurSurWithInits_CheckAdmissibleEdgeCurve                    ,obh ,21-08-2006 ,"V5R17 SP2 - Ri A0539154 ")
CGMVersionMacroDefine(2100,Project_ReportOnExtremities                                 ,ice ,21-08-2006 ,"V5R17 SP2 - Projection: report sur les extremites de wire par gestion de la classe ")
CGMVersionMacroDefine(2101,MarshMallow_Level13                                         ,PMG ,21-08-2006 ,"V5R17 SP2 - RI 545777 ") // -cr A0545777 B0545777
CGMVersionMacroDefine(2102,Extrapol_CheckAngleBetweenSpinePlanes                       ,JSX ,21-08-2006 ,"V5R17 SP2 - ImpliciteSpine: L\'angle entre 2 plans successifs doit etre inferieur a 180 ") // cr A0518738 B0518738
CGMVersionMacroDefine(2103,Fillet_R17SP2                                               ,RR  ,22-08-2006 ,"V5R17 SP2 - RI ")
CGMVersionMacroDefine(2104,IntersectionCrvSur_CircleSubBoxes                           ,CQI ,25-08-2006 ,"V5R17 SP2 - RI548990 ") // -cr A0548990 B0548990 C0548990
CGMVersionMacroDefine(2105,IntersectionCrvSur_TgtLinearConf                            ,CQI ,25-08-2006 ,"V5R17 SP2 - ODT CATStrFunctionalModeler ")
CGMVersionMacroDefine(2106,Healing_Level23                                             ,JJC ,25-08-2006 ,"V5R17 SP2 - RI 546657 ") // -cr A0546657 B0546657
CGMVersionMacroDefine(2107,NewJoin_WngOnNonManifold_Case1                              ,jbx ,25-08-2006 ,"V5R17 SP2 ") // -cr A0547953 B0547953 C0547953
CGMVersionMacroDefine(2108,AutoFillet_AutomaticSetback                                 ,JHG ,25-08-2006 ,"V5R17 SP2 ")
CGMVersionMacroDefine(2109,Parallel_SurfaceOriForSideComputation                       ,AOV ,25-08-2006 ,"V5R17 SP2 - RI ") // -cr A0548985 B0548985 C0548985
//CGMVersionMacroDefine(2110,SurSurWithInits_Check                                       ,obh ,29-08-2006 ,"V5R17 SP2 ")
CGMVersionMacroDefine(2111,HLR_CreateMissingIntersection                               ,BPG ,29-08-2006 ,"V5R17 SP2 - IR/Dev ")
CGMVersionMacroDefine(2112,Posage_SolutionsMultiples                                   ,JHN ,29-08-2006 ,"V5R17 SP2 - Ri reg ") // adl_promote -cr 542380A 542380B
CGMVersionMacroDefine(2113,Parallel_TwistExtrForRoundExtrap                            ,AOV ,01-09-2006 ,"V5R17 SP2 - RI rolling offset ") // -cr A0546919 B0546919
CGMVersionMacroDefine(2114,Simplify_AutoIntersectingSurface                            ,fds ,01-09-2006 ,"V5R17 SP2 - RI549559A ") // -cr A0549559 B0549559
CGMVersionMacroDefine(2115,Thick_RemoveFaceLevel13                                     ,MNJ ,01-09-2006 ,"V5R17 SP2 - RI ") // activation immediate le 01/09/2006
CGMVersionMacroDefine(2116,SurSurWithInits_Check                                       ,obh ,04-09-2006 ,"V5R17 SP2 - RI0539154 ")
CGMVersionMacroDefine(2117,Corner_Epsilon                                              ,obh ,04-09-2006 ,"V5R17 SP2 - RI 0550319 ")
CGMVersionMacroDefine(2118,CrvCrv_Arcs_limits                                          ,obh ,04-09-2006 ,"V5R17 SP2 - RI 548722 ")
CGMVersionMacroDefine(2119,ProjectionCrvSur_Domain_MaxDist                             ,OBH ,04-09-2006 ,"V5R17 SP2 - RI 0550179 ")
CGMVersionMacroDefine(2120,Sweep_Conic_AuthorizeNullLengthProfile                      ,JSX ,04-09-2006 ,"V5R17 SP2 - Profil de forme valide mais tres court, le reparametrage en abscisse curviligne est impossible (dw=0) ") // -cr a 550189
CGMVersionMacroDefine(2121,Prism_InternalTangentShell                                  ,FDS ,08-09-2006 ,"V5R17 SP2 - RI547625 ") // -cr A0547625 B0547625 C0547625
CGMVersionMacroDefine(2122,WireMultiTrim_ExtremitiesJournal                            ,ice ,11-09-2006 ,"V5R17 SP2 - RI545173 ")
CGMVersionMacroDefine(2123,Thick_HealingPostProJournal                                 ,MNJ ,15-09-2006 ,"V5R17 SP2 - RI ") // promote -cr A0553778 B0553778
CGMVersionMacroDefine(2124,SkinExtrapol_SkipSkinBdIfNoSharpEdgeOrDegenSurf             ,MNJ ,15-09-2006 ,"V5R17 SP2 - RI ") // promote -cr A0554172 B0554172
CGMVersionMacroDefine(2125,Loft_VirtualPtConnectionProfGuide_NoG0Deformation           ,JSX ,15-09-2006 ,"V5R17 SP2 - Need when profile is not exactly on guide. ") // -cr a545470 b545470 c4455470 a549192 b549192 c549192
CGMVersionMacroDefine(2126,Bump_Level7                                                 ,PMG ,15-09-2006 ,"V5R17 SP2 - RI 550345 ") // -cr  A0550345  B0550345  C0550345
CGMVersionMacroDefine(2127,FilletCrvCrv_CutResults                                     ,CQI ,15-09-2006 ,"V5R17 SP2 - Dev (RI545637) ")
CGMVersionMacroDefine(2128,RollingEdge_ReconvInitPtPln                                 ,CQI ,15-09-2006 ,"V5R17 SP2 - RI554442 ") // -cr A0554442 B0554442 C0554442
CGMVersionMacroDefine(2129,Corner_CheckOnStartVertex                                   ,AOV ,15-09-2006 ,"V5R17 SP2 - correction corner KO dans cadre du fillet cross parting (JHG) ")
//CGMVersionMacroDefine(2130,CrvCrvLimitArcs                                             ,obh ,19-09-2006 ,"V5R17 SP2 - RI A0548722 ") // BMB: debranche le 20/09
CGMVersionMacroDefine(2131,SurSurWithInits_MinStep                                     ,obh ,19-09-2006 ,"V5R17 SP2 - Ri 0554378 ")
CGMVersionMacroDefine(2132,SplitCuttingByPointSolution                                 ,ice ,19-09-2006 ,"V5R17 SP2 - RI554301 ")
CGMVersionMacroDefine(2133,NewJoin_StrongCurvature                                     ,JHN ,22-09-2006 ,"V5R17 SP2 - Ri regs ") // -cr A553720 B553720 C553720 A553494 B553494 C553494
CGMVersionMacroDefine(2134,EuclidianCorner_SortInits                                   ,CQI ,22-09-2006 ,"V5R17 SP2 - RI555409 ") // -cr B0555409 C0555409 D0555409
CGMVersionMacroDefine(2135,DistanceCrvSur_Pln_EmptyLimits                              ,CQI ,22-09-2006 ,"V5R17 SP2 - RI555379 ") // -cr A0555379 B0555379 C0555379
CGMVersionMacroDefine(2136,CrvCrvLimitArcs                                             ,obh ,22-09-2006 ,"V5R17 SP2 - RI externe P1 ")
CGMVersionMacroDefine(2137,IntersectionSurSur_ComputeIndex                             ,RHA ,22-09-2006 ,"V5R17 SP2 - RI P1 externe ") // -cr B0555443 C0555443 D0555443
CGMVersionMacroDefine(2138,Projection_JonctionTolerance                                ,JHN ,22-09-2006 ,"V5R17 SP2 - RI MNT ") // -cr 553464A 553464B 553464C . ODT KO CGMTest_Pose_WireShell cas Pose_RI416683 en body mapping livre lundi
CGMVersionMacroDefine(2139,CGMR17SP2HF1                                                ,GDR ,22-09-2006 ,"V5R17 SP2 - Hot Fix ")
CGMVersionMacroDefine(2140,CGMR17SP2HF2                                                ,GDR ,22-09-2006 ,"V5R17 SP2 - Hot Fix ")
CGMVersionMacroDefine(2141,CGMR17SP2HF3                                                ,GDR ,22-09-2006 ,"V5R17 SP2 - Hot Fix ")
CGMVersionMacroDefine(2142,CGMR17SP2HF4                                                ,GDR ,22-09-2006 ,"V5R17 SP2 - Hot Fix ")
CGMVersionMacroDefine(2143,CGMR17SP2HF5                                                ,GDR ,22-09-2006 ,"V5R17 SP2 - Hot Fix ")
CGMVersionMacroDefine(2144,CGMR17SP2HF6                                                ,GDR ,22-09-2006 ,"V5R17 SP2 - Hot Fix ")
CGMVersionMacroDefine(2145,CGMR17SP2HF7                                                ,GDR ,22-09-2006 ,"V5R17 SP2 - Hot Fix ")
CGMVersionMacroDefine(2146,CGMR17SP2HF8                                                ,GDR ,22-09-2006 ,"V5R17 SP2 - Hot Fix ")
CGMVersionMacroDefine(2147,CGMR17SP2HF9                                                ,GDR ,22-09-2006 ,"V5R17 SP2 - Hot Fix ")
CGMVersionMacroDefine(2148,CGMR17SP2HF10                                               ,GDR ,22-09-2006 ,"V5R17 SP2 - Hot Fix ")
CGMVersionMacroDefine(2149,CGMR17SP2HF11                                               ,GDR ,22-09-2006 ,"V5R17 SP2 - Hot Fix ")


//=========================================================================================================
// V5R17 SP3
//=========================================================================================================
CGMVersionMacroDefine(2151,ThickSurface_OneStepVolumeLevel4                            ,MNJ ,27-09-2006 ,"V5R17 SP3 - RI ") // promote -cr A0540576 B0540576 C0540576
CGMVersionMacroDefine(2152,Fillet_R17SP3                                               ,JMA ,27-09-2006 ,"V5R17 SP3 - RI ") // -cr A0548613 B0548613 C0548613 (activation demandee dans SP3)
CGMVersionMacroDefine(2153,ExtractSameTangent_Filter                                   ,CQI ,27-09-2006 ,"V5R17 SP3 - RI549220 ") // -cr A0549220 B0549220 C0549220
CGMVersionMacroDefine(2154,Offset_SuperFadingEdgeDistinctEcrv                          ,MNJ ,29-09-2006 ,"V5R17 SP3 - RI ") // promote -cr A0545417 B0545417 C0545417
CGMVersionMacroDefine(2155,Sweep_CircleGuideCenter_Degen                               ,fds ,29-09-2006 ,"V5R17 SP3 - RI ") // -cr 519001A 519001B 519001C 549016A 555351A
CGMVersionMacroDefine(2156,Sweep_Circle_ControlFullCircleLimit                         ,NLD ,29-09-2006 ,"V5R17 SP3 ") // Controle de non depassement du secteur angulaire du cercle entier
CGMVersionMacroDefine(2157,Sweep_ForceGuideNumberInfoInReport                          ,NLD ,29-09-2006 ,"V5R17 SP3 - RI548710 ")
//CGMVersionMacroDefine(2158,Clean_SplineOnSupport                                       ,RLA ,29-09-2006 ,"V5R17 SP3 - amelioration de la continuite G1 des splines sur support ")
CGMVersionMacroDefine(2159,AutoFillet_SharpEdgeInSmoothSkin                            ,JHG ,29-09-2006 ,"V5R17 SP3 - Dev ")
CGMVersionMacroDefine(2160,PCrvLengthUV_Limits                                         ,CQI ,29-09-2006 ,"V5R17 SP3 - ODT ")
CGMVersionMacroDefine(2161,IntersectionSurSurTg_MergeOption                            ,CQI ,29-09-2006 ,"V5R17 SP3 - RI Externe ") // adl_promote -cr A0548484 B0548484
CGMVersionMacroDefine(2162,FuzzySurfaceOffset_AlloDoctorTess                           ,DPS ,29-09-2006 ,"V5R17 SP3 - optimisation de la forme des triangles en input de l\'Offset polyedrique ") // adl_promote -cr 555915B 555915C 555915D
CGMVersionMacroDefine(2163,TopHeal_R17SP3                                              ,PRL ,02-10-2006 ,"V5R17 SP3 - Dev ")
CGMVersionMacroDefine(2164,Offset_SharpClosureComputation                              ,MNJ ,06-10-2006 ,"V5R17 SP3 - RI ") // -cr A0556133
CGMVersionMacroDefine(2165,Fill_AutoFillet_ImprovePerfo                                ,MPS ,06-10-2006 ,"V5R17 SP3 ") // amelioration perfo de l\'AutoFillet
CGMVersionMacroDefine(2166,ThickSurface_TrimByThick_SmoothRibbon                       ,MNJ ,06-10-2006 ,"V5R17 SP3 - dev healing G1 en post ")
CGMVersionMacroDefine(2167,EucParallel_MissedTwists                                    ,CQI ,06-10-2006 ,"V5R17 SP3 - RI 554820 554980 ")
CGMVersionMacroDefine(2168,SurfaceToCanonic_Reliability                                ,CQI ,06-10-2006 ,"V5R17 SP3 - RI538072 ") // -cr A0538072 B0538072
CGMVersionMacroDefine(2169,ReportCXEdgeStabilization                                   ,jbx ,06-10-2006 ,"V5R17 SP3 - RI 0556537 ")
CGMVersionMacroDefine(2170,Parallel_SolveGapInExtrapolation2                           ,AOV ,06-10-2006 ,"V5R17 SP3 - bug extrapolation quand solutions non issues de  deux wires consecutifs ")
CGMVersionMacroDefine(2171,Loft_CorrectCombsAtProfileParameters                        ,JSX ,06-10-2006 ,"V5R17 SP3 - RI 549608 ") // -cr a549608 b49608 c49608
CGMVersionMacroDefine(2172,Parallel_UsefullLimitsOnDistMin                             ,AOV ,06-10-2006 ,"V5R17 SP3 - RI 554817 ")
CGMVersionMacroDefine(2173,IntersectionCrvSur_Bisection                                ,CQI ,06-10-2006 ,"V5R17 SP3 - RI534696 ") // -cr A0534696 B0534696 C0534696
CGMVersionMacroDefine(2174,SurSurWithInits_RestoreSurLimits                            ,obh ,13-10-2006 ,"V5R17 SP3 - scénario sheetmétal ")
CGMVersionMacroDefine(2175,ExtendPCCM_Level1                                           ,PMG ,13-10-2006 ,"V5R17 SP3 - Bug surface frippes ") // -cr A0556945 B0556945
CGMVersionMacroDefine(2176,ProjectionCrvCrv_SmallDomain                                ,KLX ,13-10-2006 ,"V5R17 SP3 - RI 530008 ") // -cr 530008B 530008C 530008D
CGMVersionMacroDefine(2177,Parallel_SingularInit                                       ,KLX ,13-10-2006 ,"V5R17 SP3 - RI 554306 ") // -cr B554306 C554306 D554306
CGMVersionMacroDefine(2178,EdgeOrder_FPControl                                         ,FDS ,13-10-2006 ,"V5R17 SP3 - FPControl stability for ODT TestCenterEstimation ")
CGMVersionMacroDefine(2179,Offset_BulldozerLevel5                                      ,MNJ ,13-10-2006 ,"V5R17 SP3 - RI ") // activation immediate le 13-10-2006
CGMVersionMacroDefine(2180,Offset_SetOffsetNonRecursiveCall                            ,FKJ ,13-10-2006 ,"V5R17 SP3 - Stack overflow ") // activation immediate le 13-10-2006
CGMVersionMacroDefine(2181,Healing_Level24                                             ,JJC ,20-10-2006 ,"V5R17 SP3 - Improvment for Conical Fillet ")
CGMVersionMacroDefine(2182,TrimByThick_SharpLyingOnCvg4                                ,MNJ ,20-10-2006 ,"V5R17 SP3 - RI 0557677 ") // promote -cr A0557677 B0557677
CGMVersionMacroDefine(2183,Parallel_AssemblyFrozenOnTwist                              ,AOV ,20-10-2006 ,"V5R17 SP3 - RI ")
CGMVersionMacroDefine(2184,IntersectionCrvSur_ReconvergeFromConstraint                 ,CQI ,20-10-2006 ,"V5R17 SP3 - RI554355 ") // -cr A0554355 B0554355
CGMVersionMacroDefine(2185,SystemXY_BorderPatch                                        ,CQI ,20-10-2006 ,"V5R17 SP3 - RI543272 ") // -cr B0543272 C0543272 D0543272
CGMVersionMacroDefine(2186,Project_DoubleLyingOn                                       ,ice ,20-10-2006 ,"V5R17 SP3 - RI554369, SheetMetal ")
CGMVersionMacroDefine(2187,ProjectionCrvSur_CorrectTangent                             ,obh ,23-10-2006 ,"V5R17 SP3 - RI 0557308 ")
CGMVersionMacroDefine(2188,Marching_BestReconvergedPoint                               ,KLX ,27-10-2006 ,"V5R17 SP3 - for RLA ")
CGMVersionMacroDefine(2189,SkinExtrapol_SimilarCurveLevel6                             ,MNJ ,27-10-2006 ,"V5R17 SP3 - RI 0558653 ") // -cr A0558653 B0558653
CGMVersionMacroDefine(2190,CleanCurve_NoFixedPointOnWireExtremities                    ,RNO ,27-10-2006 ,"V5R17 SP3 - En 2D un bug fixe trop de point (FixedData), resoud certains probleme pour Ritha (Spline on support) ")
CGMVersionMacroDefine(2191,Offset_MaxOffsetForMultiFacesSRep                           ,LAP ,27-10-2006 ,"V5R17 SP3 - Dev R18 de NLD ")
//CGMVersionMacroDefine(2192,DistanceMin_WireInfinitePlane                               ,FSQ ,27-10-2006 ,"V5R17 SP3 - RI ") // -cr  A0555569
CGMVersionMacroDefine(2193,DistanceMin_OnAllBoundaries                                 ,FSQ ,27-10-2006 ,"V5R17 SP3 - RI ") // -cr  A0539788  B0539788  C0539788 A0540915 B0540915 C0540915
CGMVersionMacroDefine(2194,AvoidSubElementInKeepRemove                                 ,jbx ,03-11-2006 ,"V5R17 SP3 - RI ") // -cr A0558262  B0558262
CGMVersionMacroDefine(2195,FilletCrvCrv_CutResults2                                    ,CQI ,03-11-2006 ,"V5R17 SP3 - RI545637 ") // -cr B0545637 C0545637 D0545637
CGMVersionMacroDefine(2196,Sweep_ViewingDirection_PipeV4_V4                            ,NLD ,06-11-2006 ,"V5R17 SP3 ") // -cr 559297b 559297c 559297d
CGMVersionMacroDefine(2197,Sweep_Circle_DelireR2D2                                     ,NLD ,06-11-2006 ,"V5R17 SP3 - McCartney ") // - cr A0559430
CGMVersionMacroDefine(2198,WrapDir_TwistDetection                                      ,DR  ,06-11-2006 ,"V5R17 SP3 ") // ri
CGMVersionMacroDefine(2199,CGMR17SP3HF1                                                ,GDR ,06-11-2006 ,"V5R17 SP3 - hotfix ")
CGMVersionMacroDefine(2200,CGMR17SP3HF2                                                ,GDR ,06-11-2006 ,"V5R17 SP3 - Hotfix ")
CGMVersionMacroDefine(2201,CGMR17SP3HF3                                                ,GDR ,06-11-2006 ,"V5R17 SP3 - Hotfix ")
CGMVersionMacroDefine(2202,CGMR17SP3HF4                                                ,GDR ,06-11-2006 ,"V5R17 SP3 - Hotfix ")
CGMVersionMacroDefine(2203,CGMR17SP3HF5                                                ,GDR ,06-11-2006 ,"V5R17 SP3 - Hotfix ")
CGMVersionMacroDefine(2204,CGMR17SP3HF6                                                ,GDR ,06-11-2006 ,"V5R17 SP3 - Hotfix ")
CGMVersionMacroDefine(2205,CGMR17SP3HF7                                                ,GDR ,06-11-2006 ,"V5R17 SP3 - Hotfix ")
CGMVersionMacroDefine(2206,CGMR17SP3HF8                                                ,GDR ,06-11-2006 ,"V5R17 SP3 - Hotfix ")
CGMVersionMacroDefine(2207,CGMR17SP3HF9                                                ,GDR ,06-11-2006 ,"V5R17 SP3 - Hotfix ")
CGMVersionMacroDefine(2208,CGMR17SP3HF10                                               ,GDR ,06-11-2006 ,"V5R17 SP3 - Hotfix ")
CGMVersionMacroDefine(2209,CGMR17SP3HF11                                               ,GDR ,06-11-2006 ,"V5R17 SP3 - Hotfix ")


//=========================================================================================================
// V5R17 SP4
//=========================================================================================================
CGMVersionMacroDefine(2211,Offset_HealingGeoPostProLevel6                              ,MNJ ,13-11-2006 ,"V5R17 SP4 - diag d\'erreur pour TMC ")
CGMVersionMacroDefine(2212,RemoveFace_Stabilization                                    ,MNJ ,13-11-2006 ,"V5R17 SP4 - dev R18 ")
CGMVersionMacroDefine(2213,TrimByThick_NullRadiusOnTorus                               ,FKJ ,13-11-2006 ,"V5R17 SP4 - Dev R18 SheetMetal ")
CGMVersionMacroDefine(2214,PolarExtremum_MaxLimits                                     ,FDS ,13-11-2006 ,"V5R17 SP4 - RI557733 ") // -cr0557733
CGMVersionMacroDefine(2215,Fillet_R17SP4                                               ,rr  ,13-11-2006 ,"V5R17 SP4 - RI corrigé en SP4 ")
CGMVersionMacroDefine(2216,AutoFillet_Phase2Steps                                      ,JHG ,13-11-2006 ,"V5R17 SP4 - RI0557879 ")
CGMVersionMacroDefine(2217,DistanceMin_WireInfinitePlane                               ,FSQ ,17-11-2006 ,"V5R17 SP4 - RI ") // -cr  A0555569
CGMVersionMacroDefine(2218,ConstantFillet_CheckLineTraces                              ,CQI ,17-11-2006 ,"V5R17 SP4 - RI547529, 548255 ")
CGMVersionMacroDefine(2219,SurfaceToCanonic_DetectionFix                               ,CQI ,17-11-2006 ,"V5R17 SP4 - Imports IGS ")
CGMVersionMacroDefine(2220,SkinExtrapol_IncreaseSimilarCurveRelevancy                  ,FKJ ,17-11-2006 ,"V5R17 SP4 - RI ")
CGMVersionMacroDefine(2221,KeepMultiConfused                                           ,JHN ,24-11-2006 ,"V5R17 SP4 - RI ") // -cr 554817A 554817B 554817C
CGMVersionMacroDefine(2222,ToleranceForHelixCutting                                    ,jbx ,24-11-2006 ,"V5R17 SP4 - RI A0561122 ") // -cr A0561122
CGMVersionMacroDefine(2223,Sweep_CanonicCaseOnCanonicReferenceV2                       ,NLD ,24-11-2006 ,"V5R17 SP4 - RI561488 ")
CGMVersionMacroDefine(2224,UnfoldRuled_FlatFacesAlignment                              ,FSQ ,24-11-2006 ,"V5R17 SP4 - RI ") // -cr A0559368 B0559368 C0559368
CGMVersionMacroDefine(2225,Sweep_HybridModeInGetSpine                                  ,NLD ,24-11-2006 ,"V5R17 SP4 ")
CGMVersionMacroDefine(2226,RemoveFace_KeepAndCloneCheck                                ,MNJ ,24-11-2006 ,"V5R17 SP4 - RI ") // -cr   A0561937 B0561937
CGMVersionMacroDefine(2227,Extrapol_SmallNurbsCrvExtrapolation                         ,dr  ,24-11-2006 ,"V5R17 SP4 ")
CGMVersionMacroDefine(2228,IntersectionSurSur_InitLoop_PlaneFirst                      ,CQI ,24-11-2006 ,"V5R17 SP4 - RI 561688 ")
CGMVersionMacroDefine(2229,Extrude_EmptyShapeWhenResultInvariant                       ,fds ,27-11-2006 ,"V5R17 SP4 - RI ") // -cr A0559955 B0559955
CGMVersionMacroDefine(2230,Simplify_SameEdgeCurve_Invariant                            ,FDS ,27-11-2006 ,"V5R17 SP4 - Correction bug interne ( optimisation ) ")
CGMVersionMacroDefine(2231,IntersectShell_CloseScar_MissingOnBothShells2               ,ice ,27-11-2006 ,"V5R17 SP4 - Split SheetMetal ")
CGMVersionMacroDefine(2232,DevDev_PreciseAndConvergence2                               ,NDN ,27-11-2006 ,"V5R17 SP4 - WireDevelop : Ativation de PreciseMapping et traitement des evals hors domaine genere par ledu cheminement ") // -cr a3558320 b3558320
CGMVersionMacroDefine(2233,FuzzySurfaceOffset_AdjustTessTol                            ,DPS ,01-12-2006 ,"V5R17 SP4 - ajustement de la tolerance de tessellation dans le contexte des pieces plastiques ") // objectif R18 (correle aux nouvelles VReps)
CGMVersionMacroDefine(2234,EdgePropag_Curvature                                        ,fds ,01-12-2006 ,"V5R17 SP4 - RI ") // -cr B0562841 C0562841 D0562841 E0562841
CGMVersionMacroDefine(2235,SkinExtrapol_SelectTrickyFaceForPartialExtrapol             ,FKJ ,01-12-2006 ,"V5R17 SP4 - AutoFillet ")
CGMVersionMacroDefine(2236,IntersectionPlnSphere_Stabilze_Pole                         ,RHA ,01-12-2006 ,"V5R17 SP4 - Old RI ") // RI Externe
CGMVersionMacroDefine(2237,Projection_ProjEdgeEdge                                     ,JHN ,04-12-2006 ,"V5R17 SP4 - evolutions pour clore divers RIs SUG de projection sur edge ") // -cr 558662C 558662B 556894B 554331A 554331B 503207B 504647B
CGMVersionMacroDefine(2238,RSO_NewDecimation                                           ,PMG ,04-12-2006 ,"V5R17 SP4 - RI  0560449 ") // -cr  A0560449  B0560449  C0560449
CGMVersionMacroDefine(2239,DistanceBodyBody_PerfoReg                                   ,FSQ ,08-12-2006 ,"V5R17 SP4 - RI ") // -cr A0561181 B0561181
CGMVersionMacroDefine(2240,ConstantFillet_InitIndexH                                   ,CQI ,08-12-2006 ,"V5R17 SP4 - Ri externe ")
CGMVersionMacroDefine(2241,Projection_Stabilize_Coupling                               ,RHA ,11-12-2006 ,"V5R17 SP4 - Activer la nouvelle Projection directionnelle + FPControle ")
CGMVersionMacroDefine(2242,Posage_ProjectionOrientation                                ,JHN ,11-12-2006 ,"V5R17 SP4 - RI ") // -cr 561380B 561380C 561380BD
CGMVersionMacroDefine(2243,Parallel_ConfusedNupletDeformFix                            ,REN ,15-12-2006 ,"V5R17 SP4 - RI0561614 ") // -cr A0561614 B0561614
//CGMVersionMacroDefine(2244,FuzzySurfaceOffset_SwitchToPolyMeshOffset                   ,DPS ,15-12-2006 ,"V5R17 SP4 - dev Offset flou pieces plastiques etc... ") // objectif R17SP4/R18 (nouvelles VReps)
CGMVersionMacroDefine(2245,Fill_ModifOrientationFillAnalytique                         ,MPS ,18-12-2006 ,"V5R17 SP4 - RI 563793 ")
CGMVersionMacroDefine(2246,QuickerJoin                                                 ,EQT ,21-12-2006 ,"V5R17 SP4 ") // -cr A0561450 B0561450 C0561450
CGMVersionMacroDefine(2247,FuzzySurfaceOffset_SwitchToPolyMeshOffset                   ,DPS ,21-12-2006 ,"V5R17 SP4 - dev Offset flou pieces plastiques etc... ") // objectif R17SP4/R18 (nouvelles VReps)
CGMVersionMacroDefine(2248,Sweep_TwistedAreasOverClosure                               ,NLD ,21-12-2006 ,"V5R17 SP4 ")
CGMVersionMacroDefine(2249,SkinExtrapol_TinyEdgesManagement                            ,MNJ ,21-12-2006 ,"V5R17 SP4 - RI 0561412 ") // promote -cr A0561412 B0561412
CGMVersionMacroDefine(2250,Sweep_Interpol_AdaptSecondDerivative                        ,jsx ,22-12-2006 ,"V5R17 SP4 - odt multifaceblend8 case171 sur unix (eval en dehors du domaine) ")
CGMVersionMacroDefine(2251,Blend_RelimitedCoupling                                     ,JSX ,22-12-2006 ,"V5R17 SP4 - Coupling en point impose sur une portion des courbes des wires: ") // Dev R18 pour l\'option Relimitation du BlendDevelop
CGMVersionMacroDefine(2252,UnFoldedAero_Iteratif                                       ,OAU ,22-12-2006 ,"V5R17 SP4 - RI ") // adl_promote -cr 0561854B 0561854c 0561854d  0540549B  0540549c  0540549d
CGMVersionMacroDefine(2253,AutoFillet_TwiceRadiusThinWall                              ,JHG ,22-12-2006 ,"V5R17 SP4 ")
CGMVersionMacroDefine(2254,HLR_BetterLoopOrientation                                   ,SUH ,05-01-2007 ,"V5R17 SP4 - RI ") // -cr A0562407 B0562407
CGMVersionMacroDefine(2255,DistanceMin_ParallelismOfLineLine                           ,FSQ ,05-01-2007 ,"V5R17 SP4 - RI ") // -cr A0560285 B0560285 C0560285 D0560285
CGMVersionMacroDefine(2256,Sweep_FillTwistReportV2                                     ,NLD ,05-01-2007 ,"V5R17 SP4 ")
CGMVersionMacroDefine(2257,DistancePlnSur_Rep                                          ,CQI ,05-01-2007 ,"V5R17 SP4 - RI565294 ") // -cr A0565294 B0565294 C0565294
CGMVersionMacroDefine(2258,CornerFace_SplitWithShell                                   ,FDS ,05-01-2007 ,"V5R17 SP4 - RI ") // -cr A0554369 B0554369
CGMVersionMacroDefine(2259,RemoveFace_CheckOutput                                      ,MNJ ,05-01-2007 ,"V5R17 SP4 - RI ") // promote -cr A0565695 B0565695
CGMVersionMacroDefine(2260,DuplicateVertexClassInProjectionContext                     ,ice ,08-01-2007 ,"V5R17 SP4 ")
CGMVersionMacroDefine(2261,SimilarCurve_DelireSansLimite                               ,NLD ,08-01-2007 ,"V5R17 SP4 ")
CGMVersionMacroDefine(2262,Sweep_MVDWithLimit                                          ,NLD ,08-01-2007 ,"V5R17 SP4 ")
CGMVersionMacroDefine(2263,ChordalFillet_LogicalSharpness                              ,SOU ,12-01-2007 ,"V5R17 SP4 - Dev ") // logical sharpness of transversal edges
CGMVersionMacroDefine(2264,RemoveFace_CheckFRepsLoops                                  ,FKJ ,12-01-2007 ,"V5R17 SP4 - RI ") // -cr B0565601 B0566578 A0566578
CGMVersionMacroDefine(2265,ChamferGeneralInterpol_Quality                              ,CQI ,12-01-2007 ,"V5R17 SP4 - RI565438 ") // -cr A0565438 B0565438
CGMVersionMacroDefine(2266,SamplRatioTriTangentPCurve                                  ,RHA ,12-01-2007 ,"V5R17 SP4 - RI externe ") // adl_promote -cr A0559823 B0559823
CGMVersionMacroDefine(2267,CATIntersectionCrvCrvCx2_VectProp                           ,RHA ,12-01-2007 ,"V5R17 SP4 - RI ") // None
CGMVersionMacroDefine(2268,Extremum_CircleBorder                                       ,fds ,12-01-2007 ,"V5R17 SP4 - RI ") // -cr A0565627 B0565627
CGMVersionMacroDefine(2269,HybridVarOffset_DevR18TrimExtrapol                          ,LAP ,12-01-2007 ,"V5R17 SP4 - Dev R17 ") // activation R17 SP4 finalement
CGMVersionMacroDefine(2270,ChordalFillet_DegenerateTrack                               ,SOU ,12-01-2007 ,"V5R17 SP4 - RI ") // -cr  A0565851
CGMVersionMacroDefine(2271,Extrude_Plane_KeepSmooth                                    ,fds ,15-01-2007 ,"V5R17 SP4 - RI ") // -cr A0567460 B0567460
CGMVersionMacroDefine(2272,FuzzySurfaceOffset_P2SLevel7                                ,DPS ,19-01-2007 ,"V5R17 SP4 - nouvelle parametrisation du Fitting sur les configs FAN ") // adl_promote -cr 560768A
CGMVersionMacroDefine(2273,IntersectionCrvSur_RemoveConfusion                          ,CQI ,19-01-2007 ,"V5R17 SP4 - RI566437 ")
CGMVersionMacroDefine(2274,Thick_RemoveFaceLevel18                                     ,MNJ ,19-01-2007 ,"V5R17 SP4 - RI pour AutoDraft (Highlight R18 urgent) ") // promote -cr A0567729
CGMVersionMacroDefine(2275,VariableCircleFilletInit_GuideIsSpine                       ,CQI ,19-01-2007 ,"V5R17 SP4 ")
CGMVersionMacroDefine(2276,AutoIntersection2D_Closure                                  ,CQI ,19-01-2007 ,"V5R17 SP4 - ODT CATAnnotationModeler ")
CGMVersionMacroDefine(2277,Sweep_ProfilePositioningV5                                  ,NLD ,22-01-2007 ,"V5R17 SP4 ") // -cr 568436b 568436c 568436d
CGMVersionMacroDefine(2278,Intersection_Homogenize2Sides                               ,JHN ,22-01-2007 ,"V5R17 SP4 - RI 566755 ") // -cr 566755B 566755C 566755D
CGMVersionMacroDefine(2279,NullTangent_twoExtremitiesBis                               ,RHA ,22-01-2007 ,"V5R17 SP4 - RI Externe ") // Promote -cr A0562749 B0562749 C0562749
CGMVersionMacroDefine(2280,IntersectionCrvSur_ErrScale                                 ,CQI ,26-01-2007 ,"V5R17 SP4 - RI561551 ")
CGMVersionMacroDefine(2281,ConnectPiece_GuideCurve_Depth                               ,CQI ,26-01-2007 ,"V5R17 SP4 - RI566824 ")
CGMVersionMacroDefine(2282,TrimByThick_InitCheckForG1Healing                           ,MNJ ,26-01-2007 ,"V5R17 SP4 - RI REG (activation R17SP4) ") // promote -cr A0563634 B0563634
CGMVersionMacroDefine(2283,AdvancedBreakPCurveImport                                   ,dr  ,26-01-2007 ,"V5R17 SP4 ") // ri
CGMVersionMacroDefine(2284,CGMR17SP4HF1                                                ,GDR ,31-01-2007 ,"V5R17 SP4 ")
CGMVersionMacroDefine(2285,CGMR17SP4HF2                                                ,GDR ,31-01-2007 ,"V5R17 SP4 ")
CGMVersionMacroDefine(2286,CGMR17SP4HF3                                                ,GDR ,31-01-2007 ,"V5R17 SP4 ")
CGMVersionMacroDefine(2287,CGMR17SP4HF4                                                ,GDR ,31-01-2007 ,"V5R17 SP4 ")
CGMVersionMacroDefine(2288,CGMR17SP4HF5                                                ,GDR ,31-01-2007 ,"V5R17 SP4 ")
CGMVersionMacroDefine(2289,CGMR17SP4HF6                                                ,GDR ,31-01-2007 ,"V5R17 SP4 ")
CGMVersionMacroDefine(2290,CGMR17SP4HF7                                                ,GDR ,31-01-2007 ,"V5R17 SP4 ")
CGMVersionMacroDefine(2291,CGMR17SP4HF8                                                ,GDR ,31-01-2007 ,"V5R17 SP4 ")
CGMVersionMacroDefine(2292,CGMR17SP4HF9                                                ,GDR ,31-01-2007 ,"V5R17 SP4 ")
CGMVersionMacroDefine(2293,CGMR17SP4HF10                                               ,GDR ,31-01-2007 ,"V5R17 SP4 ")
CGMVersionMacroDefine(2294,CGMR17SP4HF11                                               ,GDR ,31-01-2007 ,"V5R17 SP4 ")


//=========================================================================================================
// V5R17 SP5
//=========================================================================================================
CGMVersionMacroDefine(2297,Sweep_CanonicSurfacesDetectionTolerance2                    ,JSX ,02-02-2007 ,"V5R17 SP5 - Check profile tangency for plane acceptance (wrong sharpedges in draft reorder) + RI568904 NLD ") // -cr  568904c 568904b 568904d
CGMVersionMacroDefine(2298,ThickSurface_KeepCanonicity                                 ,MNJ ,02-02-2007 ,"V5R17 SP5 - RI ") // promote -cr A0569502
CGMVersionMacroDefine(2299,TwistSurProj                                                ,dr  ,02-02-2007 ,"V5R17 SP5 - dev ")
CGMVersionMacroDefine(2300,DraftCrvCx2Function2_NoThrow                                ,CQI ,02-02-2007 ,"V5R17 SP5 - MLK R203 ")
CGMVersionMacroDefine(2301,IntersectionSurSur_Offset                                   ,eyl ,02-02-2007 ,"V5R17 SP5 - RI BOEING ")
CGMVersionMacroDefine(2302,Topo_Journal_Integrity_For_Infra                            ,fds ,08-02-2007 ,"V5R17 SP5 - Several journal modification for infra R18 check ")
CGMVersionMacroDefine(2303,Fillet_R17SP5                                               ,PRL ,08-02-2007 ,"V5R17 SP5 - RIs ") // A activer des l\'ouverture du niveau R17 SP5
CGMVersionMacroDefine(2304,ProjectionCrvSurCuspCut                                     ,RHA ,08-02-2007 ,"V5R17 SP5 - RI P1 Externe ") // -cr A0557768 B0557768
CGMVersionMacroDefine(2305,SplitJournal                                                ,RLA ,09-02-2007 ,"V5R17 SP5 - bug dans les journaux du split volume ") // pour GSM
CGMVersionMacroDefine(2306,Fillet_IgnoreSharpEdge_PLineBackUp                          ,SOU ,09-02-2007 ,"V5R17 SP5 - RI ") // -cr A0564307
CGMVersionMacroDefine(2307,ThickSurface_DontNeedSubstitutionByLinearERep               ,FKJ ,09-02-2007 ,"V5R17 SP5 - Correction bug ") // Activation Immediate le 09.02.07
CGMVersionMacroDefine(2308,TrimByThick_G1HealedInputBody                               ,MNJ ,16-02-2007 ,"V5R17 SP5 - RI ") // promote -cr A0569464
CGMVersionMacroDefine(2309,RollingEdgeInit_Reliability                                 ,CQI ,16-02-2007 ,"V5R17 SP5 - RI570907 ")
CGMVersionMacroDefine(2310,VariableDraft_SymmetricalClosedLaw2                         ,PFV ,16-02-2007 ,"V5R17 SP5 - RI 0572355 ")
CGMVersionMacroDefine(2311,ThickSurface_ForbidSmoothX2SpecSurf                         ,FKJ ,16-02-2007 ,"V5R17 SP5 - RI ") // -cr B0571516 A0571516
CGMVersionMacroDefine(2312,Unfold_LocateNonUnfoldableInput                             ,FSQ ,23-02-2007 ,"V5R17 SP5 - RI0568014 ") // -cr A0568014 B0568014
CGMVersionMacroDefine(2313,ThickSurface_IncreaseNbMaxRebuildFRepStep                   ,MNJ ,23-02-2007 ,"V5R17 SP5 - RI 0571718 ") // promote -cr A0571718 B0571718
CGMVersionMacroDefine(2314,PolarExtremum_Point                                         ,fds ,02-03-2007 ,"V5R17 SP5 - RI ")
CGMVersionMacroDefine(2315,Connect_CheckForTwistsOnHoldCurve                           ,cwm ,02-03-2007 ,"V5R17 SP5 - RI ") // -cr A0569423
CGMVersionMacroDefine(2316,UnFoldedAero_SamplingOptimization                           ,OAU ,05-03-2007 ,"V5R17 SP5 - RI A0570678 A0574408 B0574408 ") // New sampling, keep ComputeExplicitSolution Sampling
CGMVersionMacroDefine(2317,UnFoldedAero_DefaultC1Continuity                            ,OAU ,05-03-2007 ,"V5R17 SP5 - Dev ") // Desactivate the C1 computation in C0C1OuputWireCx2 method
CGMVersionMacroDefine(2318,Sweep_CutMasterWithUnorderedAreas                           ,NLD ,05-03-2007 ,"V5R17 SP5 - 05 ")
CGMVersionMacroDefine(2319,Thick_CAThkIsoSideComparison                                ,MNJ ,09-03-2007 ,"V5R17 SP5 - correction rattrap homotopie pour Offset Variable ")
CGMVersionMacroDefine(2320,Draft_R17SP5                                                ,PFV ,09-03-2007 ,"V5R17 SP5 - RI0572532 ")
CGMVersionMacroDefine(2321,Thick_RemoveFaceLevel20                                     ,MNJ ,09-03-2007 ,"V5R17 SP5 - RI REG ") // activation immediate le 09-03-2007 + promote -cr A0574913
CGMVersionMacroDefine(2322,ParallelConnect_InterpolEvalPointAndTangentTolerance        ,JHG ,09-03-2007 ,"V5R17 SP5 - RI574897 ") // adl_promote -cr 574897A 574897B 574897C
CGMVersionMacroDefine(2323,IntersectionCrvSur_PCrv_ErrScale                            ,CQI ,09-03-2007 ,"V5R17 SP5 - RI573856 ")
CGMVersionMacroDefine(2324,Blend_TopoSweepInfra5                                       ,JSX ,12-03-2007 ,"V5R17 SP5 - RI Inversion des contraintes de tangences aux extrémités ") // promote -cr B0573461
CGMVersionMacroDefine(2325,ImplicitSpine_ChangeInfiniteCircleToSpline                  ,JSX ,12-03-2007 ,"V5R17 SP5 - Lines are not precise enough a spline is needed ") // -cr a0571399
//CGMVersionMacroDefine(2326,Sweep_AuthorizeTwistedPlanarSurfaces                        ,NLD ,12-03-2007 ,"V5R17 SP5 ") // -cr 574329 a b c
CGMVersionMacroDefine(2327,Sweep_VolumeOrientationV2                                   ,NLD ,12-03-2007 ,"V5R17 SP5 ") // -cr 574329 a b c
CGMVersionMacroDefine(2328,Unfold_CleanedJournal                                       ,SUH ,17-03-2007 ,"V5R17 SP5 - RI ") // -cr A0570365 B0570365
CGMVersionMacroDefine(2329,Thick_LimitsOnRevolOffsetSurf                               ,MNJ ,16-03-2007 ,"V5R17 SP5 - RI 0574276 ") // promote -cr A0574276
CGMVersionMacroDefine(2330,Sweep_AuthorizeTwistedPlanarSurfaces                        ,NLD ,16-03-2007 ,"V5R17 SP5 ") // -cr 574329 a b c
CGMVersionMacroDefine(2331,NewMassProperties1D_Level1                                  ,EYL ,16-03-2007 ,"V5R17 SP5 - RI+Dev ") // je livre la correction des 12 KOs
CGMVersionMacroDefine(2332,HybridVarOffset_CheckInputOverlapLevel2                     ,LAP ,16-03-2007 ,"V5R17 SP5 - Amelioration pour Composite ")
CGMVersionMacroDefine(2333,Intersection_ConfusionOperationCreation                     ,jhn ,16-03-2007 ,"V5R17 SP5 - RI 568496 ") // -cr 568496D 568496C 568496B
CGMVersionMacroDefine(2334,TrimByThick_NullRadiusConfigLevel3                          ,MNJ ,23-03-2007 ,"V5R17 SP5 - RI ") // promote -cr A0575813
CGMVersionMacroDefine(2335,UnFoldedAero_TwistedPointsIndexFix                          ,REN ,23-03-2007 ,"V5R17 SP5 - RI0575599 ")
CGMVersionMacroDefine(2336,FilletCrvCrv_ConstraintSign                                 ,CQI ,26-03-2007 ,"V5R17 SP5 - RI563651 ")
CGMVersionMacroDefine(2337,CGMR17SP5HF1                                                ,GDR ,24-03-2007 ,"V5R17 SP5 ")
CGMVersionMacroDefine(2338,CGMR17SP5HF2                                                ,GDR ,24-03-2007 ,"V5R17 SP5 ")
CGMVersionMacroDefine(2339,CGMR17SP5HF3                                                ,GDR ,24-03-2007 ,"V5R17 SP5 ")
CGMVersionMacroDefine(2340,CGMR17SP5HF4                                                ,GDR ,24-03-2007 ,"V5R17 SP5 ")
CGMVersionMacroDefine(2341,CGMR17SP5HF5                                                ,GDR ,24-03-2007 ,"V5R17 SP5 ")
CGMVersionMacroDefine(2342,CGMR17SP5HF6                                                ,GDR ,24-03-2007 ,"V5R17 SP5 ")
CGMVersionMacroDefine(2343,CGMR17SP5HF7                                                ,GDR ,24-03-2007 ,"V5R17 SP5 ")
CGMVersionMacroDefine(2344,CGMR17SP5HF8                                                ,GDR ,24-03-2007 ,"V5R17 SP5 ")
CGMVersionMacroDefine(2345,CGMR17SP5HF9                                                ,GDR ,24-03-2007 ,"V5R17 SP5 ")
CGMVersionMacroDefine(2346,CGMR17SP5HF10                                               ,GDR ,24-03-2007 ,"V5R17 SP5 ")
CGMVersionMacroDefine(2347,CGMR17SP5HF11                                               ,GDR ,24-03-2007 ,"V5R17 SP5 ")


//=========================================================================================================
// V5R17 SP6
//=========================================================================================================
CGMVersionMacroDefine(2350,Sweep_ExtractProfileDirectionVerifSens                      ,NLD ,29-03-2007 ,"V5R17 SP6 ") // -cr 573676a
CGMVersionMacroDefine(2351,CCVCleaner_LineDetectionV3                                  ,NLD ,29-03-2007 ,"V5R17 SP6 ") // -cr 570832a
CGMVersionMacroDefine(2352,ThinSolid_Thickness_Check                                   ,FDS ,29-03-2007 ,"V5R17 SP6 - RI570439 ") // A0570439
CGMVersionMacroDefine(2353,CleanFatEdgesOnWire                                         ,fds ,29-03-2007 ,"V5R17 SP6 - Issue TOYOTA  on part size , clean fat edges in wire ")
CGMVersionMacroDefine(2354,NurbsCorrectionForInterfaces                                ,dr  ,29-03-2007 ,"V5R17 SP6 ")
CGMVersionMacroDefine(2355,Fillet_R17SP6                                               ,PRL ,30-03-2007 ,"V5R17 SP6 ") // -cr  A0566879    +  activation pour le SP6 (autour de semaine 16!)
CGMVersionMacroDefine(2356,Plane_FromCurve_Orientation_Stability                       ,FDS ,30-03-2007 ,"V5R17 SP6 - RI577037A ") // -cr A0577037
CGMVersionMacroDefine(2357,Blend_SmoothedCurvature_2                                   ,JSX ,02-04-2007 ,"V5R17 SP6 - suite a l\'activation de CleanCurve_OnOffsetAndC1Stability3 par RNO ") // Fonct de courbure en absCurv+ fermeture+Option cleanCourbures  MultifaceBlend8 case167 162 174
CGMVersionMacroDefine(2358,DistanceMinPtSur_CylinderCaseStabilization                  ,MNJ ,06-04-2007 ,"V5R17 SP6 - RI ") // promote -cr A0577463
CGMVersionMacroDefine(2359,Thick_CylinderDirectionalSurface                            ,MNJ ,06-04-2007 ,"V5R17 SP6 - RI ") // promote -cr A0578008 B0578008 C0578008
CGMVersionMacroDefine(2360,VariableFillet_Marching_ValidateStepOnSpine                 ,cwm ,06-04-2007 ,"V5R17 SP6 - RI ") // -cr A0575438 B0575438
CGMVersionMacroDefine(2361,Thick_FindMoreStaplesForRescue                              ,FKJ ,13-04-2007 ,"V5R17 SP6 - RI ") // -cr A0575831
CGMVersionMacroDefine(2362,Extrapol_ShellG1_Until_MultiDomainsSolution                 ,JSX ,13-04-2007 ,"V5R17 SP6 - Demande SheetMetal ") // en until , on autorise les solutions multi shell
//CGMVersionMacroDefine(2363,Sweep_RelimitationUsingTangencyTestAtShiftedPointV2         ,NLD ,13-04-2007 ,"V5R17 SP6 ") // -cr 579248a
CGMVersionMacroDefine(2364,MarshMallow_Mapping1                                        ,PMG ,13-04-2007 ,"V5R17 SP6 - Correction instabilite decouverte avec le nouveau calcul de longueur. ")
CGMVersionMacroDefine(2365,GetBoundingWires_StabilityLevel2                            ,LAP ,13-04-2007 ,"V5R17 SP6 - Scenario industriel instable ")
CGMVersionMacroDefine(2366,ImplicitSpine_ChangeInfiniteCircleToSpline_Undo             ,JSX ,13-04-2007 ,"V5R17 SP6 - ri CD le code active par ImplicitSpine_ChangeInfiniteCircleToSpline n\'est pas bon ") // SkinExtrapolation
CGMVersionMacroDefine(2367,SmartProject_ConnectExtremitiesOfDegenerated                ,JHN ,16-04-2007 ,"V5R17 SP6 - RI 579735 ") // -cr A0579735 B0579735 C0579735
CGMVersionMacroDefine(2368,CleanCurve_OnOffsetAndC1Stability3                          ,RNO ,20-04-2007 ,"V5R17 SP6 - Stabilite de l\'operateur au traitement des courbes C1 ou des courbes sur support C1 (comme les OffsetSurfaces) ") // promote -cr  A0572489 C0541924 A0541924
CGMVersionMacroDefine(2369,P2S_ParameterizationLevel2                                  ,KTU ,20-04-2007 ,"V5R17 SP6 - RI A0579206 ")
CGMVersionMacroDefine(2370,Regul_SplitInternalLoops                                    ,cwm ,20-04-2007 ,"V5R17 SP6 - RI ") // -cr A0578842 B0578842  C0578842
CGMVersionMacroDefine(2371,RemoveFace_ForceTouchedAttribForX2S                         ,FKJ ,20-04-2007 ,"V5R17 SP6 - RI ") // -cr A0578251
CGMVersionMacroDefine(2372,GeodesicLine_MigrCalcLength                                 ,AOV ,23-04-2007 ,"V5R17 SP6 - RI580855 ")
CGMVersionMacroDefine(2373,Fill_ManageSmallEdges                                       ,MPS ,23-04-2007 ,"V5R17 SP6 - RI  580836 ") // promote -cr  A0580836 B0580836
CGMVersionMacroDefine(2374,Extremum_TestAllPCurves                                     ,fds ,27-04-2007 ,"V5R17 SP6 - RI ") // -cr A0580189 B0580189 C0580189
CGMVersionMacroDefine(2375,FillShellWithFaces_NonManifold                              ,fds ,27-04-2007 ,"V5R17 SP6 - mlk suite a erreur de traitement ")
CGMVersionMacroDefine(2376,Sweep_RelimitationUsingTangencyTestAtShiftedPointV2         ,NLD ,27-04-2007 ,"V5R17 SP6 ") // -cr 579248a
CGMVersionMacroDefine(2377,MaxOffset_CheckDomain                                       ,MNJ ,30-04-2007 ,"V5R17 SP6 - protection contre CD ")
CGMVersionMacroDefine(2378,Loft_Deformation_NonSymmetricG2Point                        ,JSX ,30-04-2007 ,"V5R17 SP6 - check du code : deformation G2 differente en debut et fin de section ") // partie de code non active sur la R17 (mais necessaire pour les updates)
CGMVersionMacroDefine(2379,ImplicitSpine_CodeCheck                                     ,JSX ,30-04-2007 ,"V5R17 SP6 - revue de code a l\'occasion du  CD ri 579265 ") // Restructuration du code , bugs masqués par rattrapage
CGMVersionMacroDefine(2380,ImplicitSpine_GuidesRelimitation_UseOfGoodSide              ,JSX ,30-04-2007 ,"V5R17 SP6 - ODT CGMTest_SurfacicTopSpine0_Task1047_N1 , ") // Wrong crvRef  in input of CATMassProperties1D.GetLengthFromParams
CGMVersionMacroDefine(2381,Sweep_CheckForSpineSmoothing4                               ,NLD ,30-04-2007 ,"V5R17 SP6 ")
CGMVersionMacroDefine(2382,Sweep_KeepIntersectionCCVCCVWithConfusion                   ,NLD ,30-04-2007 ,"V5R17 SP6 ")
CGMVersionMacroDefine(2383,Thick_MicroFaceReplacedByEdgeNotTricky                      ,MNJ ,04-05-2007 ,"V5R17 SP6 - RI MNT ") // promote -cr A0581149 B0581149 C0581149
CGMVersionMacroDefine(2384,Thick_ClashSRepCollisionFilterLevel3                        ,FKJ ,04-05-2007 ,"V5R17 SP6 - RI ")
CGMVersionMacroDefine(2385,CGMJournal_RemoveReportR18                                  ,JMA ,04-05-2007 ,"V5R17 SP6 - RI0569676 ") // -cr A0569676
CGMVersionMacroDefine(2386,CylinderProjectionCuspDetection                             ,EYL ,11-05-2007 ,"V5R17 SP6 - RI ")
CGMVersionMacroDefine(2387,HybridVarOffset_SharpMediumCurveDetection                   ,FKJ ,11-05-2007 ,"V5R17 SP6 - Dev. R18 ")
CGMVersionMacroDefine(2388,OffsetVar_MediumByDelta                                     ,PMG ,21-05-2007 ,"V5R17 SP6 - RI A0581805 ") // -cr A0581805
CGMVersionMacroDefine(2389,CGMR17SP6HF1                                                ,RHA ,29-05-2007 ,"V5R17 SP6 ")
CGMVersionMacroDefine(2390,CGMR17SP6HF2                                                ,RHA ,29-05-2007 ,"V5R17 SP6 ")
CGMVersionMacroDefine(2391,CGMR17SP6HF3                                                ,RHA ,29-05-2007 ,"V5R17 SP6 ")
CGMVersionMacroDefine(2392,CGMR17SP6HF4                                                ,RHA ,29-05-2007 ,"V5R17 SP6 ")
CGMVersionMacroDefine(2393,CGMR17SP6HF5                                                ,RHA ,29-05-2007 ,"V5R17 SP6 ")
CGMVersionMacroDefine(2394,CGMR17SP6HF6                                                ,RHA ,29-05-2007 ,"V5R17 SP6 ")
CGMVersionMacroDefine(2395,CGMR17SP6HF7                                                ,RHA ,29-05-2007 ,"V5R17 SP6 ")
CGMVersionMacroDefine(2396,CGMR17SP6HF8                                                ,RHA ,29-05-2007 ,"V5R17 SP6 ")
CGMVersionMacroDefine(2397,CGMR17SP6HF9                                                ,RHA ,29-05-2007 ,"V5R17 SP6 ")
CGMVersionMacroDefine(2398,CGMR17SP6HF10                                               ,RHA ,29-05-2007 ,"V5R17 SP6 ")
CGMVersionMacroDefine(2399,CGMR17SP6HF11                                               ,RHA ,29-05-2007 ,"V5R17 SP6 ")


//=========================================================================================================
// V5R18 GA
//=========================================================================================================
CGMVersionMacroDefine(2700,Sweep_MultipleViewingDirMovingFrame                         ,NLD ,12-01-2007 ,"V5R18 GA - Moving frame a viewing dir multiple pour cas difficiles pur 3D ") // Activation en R18 seulement -cr 555166a 310531b
CGMVersionMacroDefine(2701,Clean_SplineOnSupport                                       ,RLA ,12-01-2007 ,"V5R18 GA - SPLINE ON SUPPORT ")
CGMVersionMacroDefine(2702,UnfoldFrF_BetterFitting1                                    ,SUH ,06-04-2007 ,"V5R18 GA - Dev ") // Unfold P2SLevel6
CGMVersionMacroDefine(2703,IntersectionCrvSur_Perfos                                   ,RHA ,01-06-2007 ,"V5R18 GA - RI MANDATORY ") // adl_promote -cr  A0583821


//=========================================================================================================
// V5R18 SP1
//=========================================================================================================
CGMVersionMacroDefine(2705,TwistAnalysis_GridLocalOptimum_For_LinearSurface            ,RR  ,01-06-2007 ,"V5R18 SP1 - RIs ")
CGMVersionMacroDefine(2706,RemoveFace_SeamLimitsRebuild                                ,MNJ ,01-06-2007 ,"V5R18 SP1 - RI ext ") // promote -cr B0584723 C0584723
CGMVersionMacroDefine(2707,Fillet_R18SP1                                               ,cwm ,01-06-2007 ,"V5R18 SP1 - RI ") // -cr A0554296 A0585228
CGMVersionMacroDefine(2708,Connect_CleanLineExtremities                                ,cwm ,01-06-2007 ,"V5R18 SP1 - RI ") // -cr A0568268
CGMVersionMacroDefine(2709,TrimByThick_ConfEcrvSurWhenReverseEdgAno                    ,FKJ ,08-06-2007 ,"V5R18 SP1 - RIs ") // -cr A0586065 A0586504
CGMVersionMacroDefine(2710,Sweep_Discontinuity_Limit_Extrapol                          ,fds ,08-06-2007 ,"V5R18 SP1 - RI584499 ")
CGMVersionMacroDefine(2711,TrimByThick_NonBorderAndNonManifoldIVLO                     ,MNJ ,08-06-2007 ,"V5R18 SP1 - dev R19 ")
CGMVersionMacroDefine(2712,ThickSurfacePlus_CheckAllTrickyFacesAreRegularisable        ,FKJ ,08-06-2007 ,"V5R18 SP1 - Dev. ThickSurfacePlus ")
CGMVersionMacroDefine(2713,HomoptCrvSur_PlanLevel2                                     ,LAP ,08-06-2007 ,"V5R18 SP1 - RI586912A ") // -cr 586912A
CGMVersionMacroDefine(2714,Parallel_ExtrapNoSol                                        ,AOV ,08-06-2007 ,"V5R18 SP1 - RI Parallel ")
CGMVersionMacroDefine(2715,RSO_DeltaSimplification                                     ,PMG ,11-06-2007 ,"V5R18 SP1 - Amelioration du conditionnement + optimisation perfo courbe limite ")
CGMVersionMacroDefine(2716,Draft_R18SP1                                                ,PFV ,15-06-2007 ,"V5R18 SP1 - RIs ")
CGMVersionMacroDefine(2717,Sweep_Segment_RelimitedByPlanarOffset                       ,JSX ,18-06-2007 ,"V5R18 SP1 - RI587120 AuthorizedPlanarOffset ") // -cr b587120
CGMVersionMacroDefine(2718,RemoveFace_ExtrapolLengthStabilization                      ,MNJ ,22-06-2007 ,"V5R18 SP1 - stabilisation ODT ")
CGMVersionMacroDefine(2719,SkinExtrapol_SimilarCurveLevel9                             ,MNJ ,22-06-2007 ,"V5R18 SP1 - dev SkinExtrapol pour MetaAutoFillet ")
CGMVersionMacroDefine(2720,IntersectionCrvSur_Helix_stab                               ,dad ,25-06-2007 ,"V5R18 SP1 - Divide by 0 ") // Jetons IPW-1948 & IPW-1949
CGMVersionMacroDefine(2721,ExtrapolG2_ExtrapIsClosed                                   ,AOV ,25-06-2007 ,"V5R18 SP1 - RI ")
CGMVersionMacroDefine(2722,Unfold_Problems2                                            ,SUH ,29-06-2007 ,"V5R18 SP1 - RI ") // -cr A0587598
CGMVersionMacroDefine(2723,SkinExtrapolPlus_LinearEdgeForDegenRescue                   ,MNJ ,29-06-2007 ,"V5R18 SP1 - dev ")
CGMVersionMacroDefine(2724,Sweep_DeploySoftwareConfigurationV6                         ,NLD ,29-06-2007 ,"V5R18 SP1 ")
CGMVersionMacroDefine(2725,Thick_HealingGeoPostProRequiredLevel12                      ,FKJ ,29-06-2007 ,"V5R18 SP1 - RI ") // -cr B0588883 D0588883
CGMVersionMacroDefine(2726,Sweep_XScaleR18SP1                                          ,NLD ,02-07-2007 ,"V5R18 SP1 ")
CGMVersionMacroDefine(2727,Sweep_ProfilePositioningV6                                  ,NLD ,02-07-2007 ,"V5R18 SP1 - RI545092 ")
CGMVersionMacroDefine(2728,Blend_EvalTwistFunctionAndDerivativeInDomain                ,JSX ,02-07-2007 ,"V5R18 SP1 - Pb sur blend Mercedes ") // CATSweepTwistFunctionX
CGMVersionMacroDefine(2729,OffsetVar_PurgeJournal                                      ,PMG ,06-07-2007 ,"V5R18 SP1 - Info parasite dans le journal de l\'offset variable ")
CGMVersionMacroDefine(2730,RemoveFace2D_Level1                                         ,MNJ ,06-07-2007 ,"V5R18 SP1 - dev CATIA Live Shape ")
CGMVersionMacroDefine(2731,Healing_Level25                                             ,JJC ,06-07-2007 ,"V5R18 SP1 - RI ") // -cr A0574326
CGMVersionMacroDefine(2732,CornerConnect_PLineInitReconvergenceFixed                   ,JHG ,06-07-2007 ,"V5R18 SP1 - Ri0587948, Ri0577903 ")
CGMVersionMacroDefine(2733,Sweep_MVDKeepAfterExtrapolation                             ,NLD ,09-07-2007 ,"V5R18 SP1 ") // -cr 588466a
CGMVersionMacroDefine(2734,LayDownCrvSur_Circle                                        ,DAD ,09-07-2007 ,"V5R18 SP1 - RI  A0579813 ; posage des Circle en PCircle ") // -cr A0579813
CGMVersionMacroDefine(2735,AutoDraft_NeutralReflectCriticalPoint                       ,PFV ,09-07-2007 ,"V5R18 SP1 - Dev ")
CGMVersionMacroDefine(2736,UnfoldRuled_AccurateSurfaceComputation                      ,SUH ,13-07-2007 ,"V5R18 SP1 - RI ") // -cr A0588008 B0588008 C0588008
CGMVersionMacroDefine(2737,Sweep_ImplicitSpine_XScaleNonIsoV2                          ,NLD ,13-07-2007 ,"V5R18 SP1 - corrections XScale a non isocomportement meme a echelle 1 ")
CGMVersionMacroDefine(2738,P2S_2DFiltering1                                            ,KTU ,20-07-2007 ,"V5R18 SP1 - RI ") // -cr A0588122, -cr B0588122
CGMVersionMacroDefine(2739,GeodesicProjection_SolveInterval                            ,AOV ,20-07-2007 ,"V5R18 SP1 - RI ") // -cr A0590271,B0590271
CGMVersionMacroDefine(2740,Sweep_ViewingDirection_PipeV4_V5                            ,NLD ,23-07-2007 ,"V5R18 SP1 ") // -cr 587662b
CGMVersionMacroDefine(2741,SmartProjection_GapInShell                                  ,JHN ,23-07-2007 ,"V5R18 SP1 - ri 581840 ") // -cr 581840A
CGMVersionMacroDefine(2742,Unplug_AnalysisCrvSurInits_RunRevol                         ,DAD ,23-07-2007 ,"V5R18 SP1 - RI 0584553 ") // -cr A&B 0584553 ; la methode AnalysisCrvSurInits::RunRevol est completement fausse et elle ne peut etre corrigee car il n\'y a pas de solution canonique a  faible cout dans le cas de la revol.
CGMVersionMacroDefine(2743,HybridVarOffset_StabilzeImpliceVertexValue                  ,LAP ,30-07-2007 ,"V5R18 SP1 - Dev Composite ")
CGMVersionMacroDefine(2744,IntersectPLinePCirc_LineCenterCase                          ,DAD ,30-07-2007 ,"V5R18 SP1 - RI 0586921, le cas ou la PLine passe par le centre du PCircle n\'etait pas gere. ") // -cr B0586921
CGMVersionMacroDefine(2745,CleanCurve_CCVCleanerStability6                             ,RNO ,03-08-2007 ,"V5R18 SP1 - Amelioration de la coherence dans le LocalOpti entre les echelles 0.01 et 1 ")
CGMVersionMacroDefine(2746,Join_CheckAndRepare                                         ,JHN ,06-08-2007 ,"V5R18 SP1 - ri 591800 ") // -cr 591800B 591800C
CGMVersionMacroDefine(2747,SkinExtrapol_AdjustTrustLevelForFacesLevel2                 ,LAP ,06-08-2007 ,"V5R18 SP1 - RI591560 ") // -cr 591560B 591560C
CGMVersionMacroDefine(2748,CGMR18SP1HF1                                                ,RHA ,08-08-2007 ,"V5R18 SP1 ")
CGMVersionMacroDefine(2749,CGMR18SP1HF2                                                ,RHA ,08-08-2007 ,"V5R18 SP1 ")
CGMVersionMacroDefine(2750,CGMR18SP1HF3                                                ,RHA ,08-08-2007 ,"V5R18 SP1 ")
CGMVersionMacroDefine(2751,CGMR18SP1HF4                                                ,RHA ,08-08-2007 ,"V5R18 SP1 ")
CGMVersionMacroDefine(2752,CGMR18SP1HF5                                                ,RHA ,08-08-2007 ,"V5R18 SP1 ")
CGMVersionMacroDefine(2753,CGMR18SP1HF6                                                ,RHA ,08-08-2007 ,"V5R18 SP1 ")
CGMVersionMacroDefine(2754,CGMR18SP1HF7                                                ,RHA ,08-08-2007 ,"V5R18 SP1 ")
CGMVersionMacroDefine(2755,CGMR18SP1HF8                                                ,RHA ,08-08-2007 ,"V5R18 SP1 ")
CGMVersionMacroDefine(2756,CGMR18SP1HF9                                                ,RHA ,08-08-2007 ,"V5R18 SP1 ")
CGMVersionMacroDefine(2757,CGMR18SP1HF10                                               ,RHA ,08-08-2007 ,"V5R18 SP1 ")
CGMVersionMacroDefine(2758,CGMR18SP1HF11                                               ,RHA ,08-08-2007 ,"V5R18 SP1 ")


//=========================================================================================================
// V5R18 SP2
//=========================================================================================================
CGMVersionMacroDefine(2760,MarshMallow_ThrowOnBadInput                                 ,PMG ,10-08-2007 ,"V5R18 SP2 - Gestion d'erreur GSO/ShapeMorphing ")
CGMVersionMacroDefine(2761,RemoveFace_IncreaseBoxScalingFactorForCylinder              ,FKJ ,10-08-2007 ,"V5R18 SP2 - RI ") // -cr A0593124 B0593124 C0593124
CGMVersionMacroDefine(2762,CornerFace_Perfo                                            ,fds ,13-08-2007 ,"V5R18 SP2 - RI , attention je ne suis pas la jusqu\'au 27/08 ,  mais on cherche a reduire la backlog plus tot , voir avec Jean pour tout pb ")
CGMVersionMacroDefine(2763,DistanceBodyBody_FpControlForTessMaxAngle                   ,SUH ,17-08-2007 ,"V5R18 SP2 ") // a detruire
CGMVersionMacroDefine(2764,Thick_RightCollisionFilterOnBorder                          ,LAP ,17-08-2003 ,"V5R18 SP2 - Correction de Bug + Correction partielle de RI ")
CGMVersionMacroDefine(2765,Healing_Level26                                             ,JJC ,24-08-2007 ,"V5R18 SP2 - RI ") // -cr A0589828
CGMVersionMacroDefine(2766,RemoveFace2D_Level2                                         ,FKJ ,24-08-2007 ,"V5R18 SP2 - Dev ")
CGMVersionMacroDefine(2767,KeepAdmissibleCrv                                           ,DAD ,27-08-2007 ,"V5R18 SP2 - RI 0584553 ") // -cr A&B 0584553 ; Keep admissible curve when they connect init has already failed to find them ; Livrer PLineCyl1_CATProjectionCrvSurGen.CGMReplay  et PLineCyl2_CATProjectionCrvSurGen.CGMReplay
CGMVersionMacroDefine(2768,IntCrvSur_a_In_zTest                                        ,DAD ,27-08-2007 ,"V5R18 SP2 - IR 0585910 ") // -cr A0585910 B0585910 ; livrer ODTs CGMReplay IR0585910_CATIntersectionSurSur_CylRevol_1, 2, 3 & 4 sur FIXPARTVERS
CGMVersionMacroDefine(2769,DevDev_PreciseAndConvergence3                               ,JSX ,27-08-2007 ,"V5R18 SP2 - RI 590499 . Utilisation d\'un calcul non signé dans les cas de revol avec portion plane ") // -cr a590499
CGMVersionMacroDefine(2770,FuzzySimplify_OffsetBothSidesThenMedianMesh                 ,dps ,31-08-2007 ,"V5R18 SP2 - implementation strategique du Simplify (MedianMesh) ") // Dev R18 SP2
CGMVersionMacroDefine(2771,Project_PointReference                                      ,JHN ,03-09-2007 ,"V5R18 SP2 - RI ") // -cr 593831A 593831B
CGMVersionMacroDefine(2772,UnfoldRuled_ShortSurfaceProblem                             ,SUH ,03-09-2007 ,"V5R18 SP2 - RI ") // -cr A0594371 B0594371
CGMVersionMacroDefine(2773,SweepVar_InvertKnotVectorBeforeFitting                      ,JSX ,03-09-2007 ,"V5R18 SP2 - RI  A0595387 odt dans ZZCGMPartTest : Profile fitté en imposant  un KV inversé ") // -cr  A0595387 B0595387
CGMVersionMacroDefine(2774,Extrude_ByCircle_Cone_UParam                                ,fds ,07-09-2007 ,"V5R18 SP2 - RI ") // -cr A0591593 B0591593 A0594556 B0594556
CGMVersionMacroDefine(2775,ParallelConnect_InterpolCheckComponentQuinticIntervalFix    ,JHG ,07-09-2007 ,"V5R18 SP2 - Xtreme scale ")
CGMVersionMacroDefine(2776,Parallel_SolveGapInExtrapolation3                           ,AOV ,07-09-2007 ,"V5R18 SP2 - Dev ")
CGMVersionMacroDefine(2777,UnFoldedAero_MapPointFix                                    ,REN ,14-09-2007 ,"V5R18 SP2 - IR585479 & IR590081 ")
CGMVersionMacroDefine(2778,Intersection_4Aretes                                        ,JHN ,14-09-2007 ,"V5R18 SP2 - RI ") // -cr 592577B 592577C
CGMVersionMacroDefine(2779,CleanCurve_XScaleStability01                                ,RNO ,14-09-2007 ,"V5R18 SP2 - Amelioration Sur Support (CheckLimits) et des Concatenations (G2IntoC2), ameliorations sur les grandes echelles ")
CGMVersionMacroDefine(2780,Fillet_R18SP2                                               ,SOU ,14-09-2007 ,"V5R18 SP2 - R18 SP2 Fillet RIs ")
CGMVersionMacroDefine(2781,Relim_R18SP2                                                ,PRL ,14-09-2007 ,"V5R18 SP2 - RI ")
CGMVersionMacroDefine(2782,TopCleanCurve_SafeClosure                                   ,RNO ,14-07-2007 ,"V5R18 SP2 - RI 0595988 ") // Correction sur le choix du vertex de fermeture
CGMVersionMacroDefine(2783,Thick_ConfEcrvSurWhenReverseEdgAno                          ,FKJ ,14-09-2007 ,"V5R18 SP2 - RI ") // -cr B0594564 C0594564
CGMVersionMacroDefine(2784,Healing_Level27                                             ,JJC ,21-09-2007 ,"V5R18 SP2 - RI ") // -cr 593056
CGMVersionMacroDefine(2785,Sweep_FillTwistSimilarInversion                             ,NLD ,21-09-2007 ,"V5R18 SP2 ")
//CGMVersionMacroDefine(2786,RefCrvInCrossingInter                                       ,DAD ,24-09-2007 ,"V5R18 SP2 - RI A0587069,B0587069 ")
CGMVersionMacroDefine(2787,Extrapol_FSG2_ShiftEvalOnExtraordinaryPoint                 ,JSX ,24-09-2007 ,"V5R18 SP2 - RI 526613 ") // -cr a0465213
CGMVersionMacroDefine(2788,Sweep_XScaleR18SP2                                          ,NLD ,24-09-2007 ,"V5R18 SP2 ")
CGMVersionMacroDefine(2789,AutoDraft_MissingSubSubSectors                              ,EYL ,28-09-2007 ,"V5R18 SP2 - Dev ")
CGMVersionMacroDefine(2790,Extrude_Profile_NoECSharing                                 ,fds ,28-09-2007 ,"V5R18 SP2 - RI597246 ") // -cr A0597246
CGMVersionMacroDefine(2791,ParallelConnect_GeodesicStartVxTwist                        ,IZE ,28-09-2007 ,"V5R18 SP2 - dev (smooth parallel) ")
CGMVersionMacroDefine(2792,VariableFilletG1_dCsApproxImprovement                       ,cwm ,28-09-2007 ,"V5R18 SP2 - RI ") // -cr A0595368 B0595368
CGMVersionMacroDefine(2793,EuclidianCornerInit_SolveNewtonWithInit                     ,JHG ,28-09-2007 ,"V5R18 SP2 - Dev (reportinit corner) ")
CGMVersionMacroDefine(2794,ReflectLine_AcceptNonCompleteSet                            ,PFV ,28-09-2007 ,"V5R18 SP2 - IR 0597879 ")
CGMVersionMacroDefine(2795,PowerDef_ApplyPerfo                                         ,PMG ,01-10-2007 ,"V5R18 SP2 - Bug dans l\'apply sur le nombre max de segments. ") // -cr A0597907 B0597907 C0597907
CGMVersionMacroDefine(2796,RibSweep_CheckInit                                          ,IEY ,01-10-2007 ,"V5R18 SP2 - ODT Convergnece for Extreme scale ") // 1 KO ODT
CGMVersionMacroDefine(2797,CGMR18SP2HF1                                                ,RHA ,10-10-2007 ,"V5R18 SP2 ")
CGMVersionMacroDefine(2798,CGMR18SP2HF2                                                ,RHA ,10-10-2007 ,"V5R18 SP2 ")
CGMVersionMacroDefine(2799,CGMR18SP2HF3                                                ,RHA ,10-10-2007 ,"V5R18 SP2 ")
CGMVersionMacroDefine(2800,CGMR18SP2HF4                                                ,RHA ,10-10-2007 ,"V5R18 SP2 ")
CGMVersionMacroDefine(2801,CGMR18SP2HF5                                                ,RHA ,10-10-2007 ,"V5R18 SP2 ")


//=========================================================================================================
// V5R18 SP3
//=========================================================================================================
CGMVersionMacroDefine(2804,Fill_CheckJoin                                              ,MPS ,12-10-2007 ,"V5R18 SP3 - RI  598047 ") // -cr  A0598047
CGMVersionMacroDefine(2805,DraftOrientation                                            ,EYL ,12-10-2007 ,"V5R18 SP3 - RI ") // -cr A0584170
CGMVersionMacroDefine(2806,Fillet_R18SP3                                               ,cwm ,12-10-2007 ,"V5R18 SP3 - RI ") // -cr A0598270
CGMVersionMacroDefine(2807,AutoFillet_FixMix01                                         ,JHG ,12-10-2007 ,"V5R18 SP3 - RI0591823 ")
CGMVersionMacroDefine(2808,Thick_CreateInitForXBiAroundReverseEdgeWithImmobileVRep     ,LAP ,12-10-2007 ,"V5R18 SP3 - Ri Reg ") // -cr 598413A 598413B
CGMVersionMacroDefine(2809,Sweep_FillTwistSimilarCuspControl                           ,NLD ,15-10-2007 ,"V5R18 SP3 ")
CGMVersionMacroDefine(2810,Sweep_UpgradeImplicitSystemInCoupling                       ,nld ,15-10-2007 ,"V5R18 SP3 ")
CGMVersionMacroDefine(2811,Sweep_XScaleR18SP3                                          ,NLD ,15-10-2007 ,"V5R18 SP3 ")
CGMVersionMacroDefine(2812,MapXReconv_TPrev                                            ,DAD ,15-10-2007 ,"V5R18 SP3 - IPW ")
CGMVersionMacroDefine(2813,FuzzySurfaceOffset_OptimizeInternalCalls                    ,DPS ,19-10-2007 ,"V5R18 SP3 - optimisation de sous ") // migration Tess sur PolyMesh, clonage Decimate sur pool d\'alloc, P2S level8
CGMVersionMacroDefine(2814,Connect_SmoothLimiting                                      ,RR  ,19-10-2007 ,"V5R18 SP3 - Optimized Connect Extrapolation + IR + Performances ") // -cr B0599596 C0599596
CGMVersionMacroDefine(2815,Sweep_NormalDerivativeV4                                    ,NLD ,22-10-2007 ,"V5R18 SP3 ")
CGMVersionMacroDefine(2816,Sweep_IntersectionCouplingStabilizeClosure                  ,NLD ,22-10-2007 ,"V5R18 SP3 ")
CGMVersionMacroDefine(2817,DistanceMin_WireInfinitePlane2                              ,FSQ ,22-10-2007 ,"V5R18 SP3 - RI ") // -cr A0598144  C0598144
CGMVersionMacroDefine(2818,SurSurResultCurve_Check3DCurvature_1                        ,IEY ,22-10-2007 ,"V5R18 SP3 - Extreme scale convergence ") // IntersectionSurSur operator compliance for Extreme scale
//CGMVersionMacroDefine(2819,Transfo_OffsetSurface                                       ,fds ,26-10-2007 ,"V5R18 SP3 - RI ") // -cr A0600974 B0600974
CGMVersionMacroDefine(2820,Fillet_IgnoreSharpEdge_LargeAngle                           ,RR  ,26-10-2007 ,"V5R18 SP3 - Maintenance ")
CGMVersionMacroDefine(2821,Sweep_NoSnapOnClosedSurface_C0Case                          ,NLD ,26-10-2007 ,"V5R18 SP3 ")
CGMVersionMacroDefine(2822,HLR_TrimFaceBySilhouetteLevel2                              ,DPS ,02-11-2007 ,"V5R18 SP3 - robustesse du code de silhouette dans le HLR ") // -cr 600632A 600632B 595258A 595258C
//CGMVersionMacroDefine(2823,NewDirectionnalProjection                                   ,OBH ,09-11-2007 ,"V5R18 SP3 - Dev Attendu en R18SP1 ") // -cr A0588622 C0588622 A0598411 B0598411
CGMVersionMacroDefine(2824,UnfoldFrF_EnhancedRemoveBadTri                              ,SUH ,09-11-2007 ,"V5R18 SP3 - RI ") // -cr  B0601699  C0601699
CGMVersionMacroDefine(2825,Sweep_FillTwistReportV3                                     ,NLD ,09-11-2007 ,"V5R18 SP3 ")
CGMVersionMacroDefine(2826,Sweep_FillTwistConcatGuideAtClosure                         ,NLD ,09-11-2007 ,"V5R18 SP3 ")
CGMVersionMacroDefine(2827,ThickSurface_SideRibbonStabilizationLevel3                  ,LAP ,09-11-2007 ,"V5R18 SP3 - RI Reg ") // -cr 598452A 598452B
CGMVersionMacroDefine(2828,IntCrvCrv_ECrvPCrv                                          ,KUU ,12-11-2007 ,"V5R18 SP3 - RI0585964; Management of Edgecurve with a PCurve as RefCurve in Intersection CrvCrv ")
CGMVersionMacroDefine(2829,Transfo_OffsetSurface                                       ,fds ,12-11-2007 ,"V5R18 SP3 - RI A0600974 B0600974 ")
CGMVersionMacroDefine(2830,ExtrapG2OfWire_CheckIntersection                            ,AOV ,12-11-2007 ,"V5R18 SP3 - bug extrapolation G2 up to wire ")
CGMVersionMacroDefine(2831,ChordalFillet_LoopInit                                      ,SOU ,16-11-2007 ,"V5R18 SP3 - RI ") // For R18 SP3
CGMVersionMacroDefine(2832,Revol_Close_Profile                                         ,fds ,16-11-2007 ,"V5R18 SP3 - RI ") // NA
CGMVersionMacroDefine(2833,RefCrvInCrossingInter                                       ,DAD ,16-11-2007 ,"V5R18 SP3 - RI A0587069,B0587069 ")
CGMVersionMacroDefine(2834,AutoDraft_PreProcessUpgrade                                 ,EYL ,16-11-2007 ,"V5R18 SP3 - Dev ")
CGMVersionMacroDefine(2835,Thick_RemoveFaceLevel24                                     ,FKJ ,16-11-2007 ,"V5R18 SP3 - Dev ")
CGMVersionMacroDefine(2836,RemoveFace2D_TptStatusOnWaitingForSharpBorderEdges          ,FKJ ,16-11-2007 ,"V5R18 SP3 - Dev ")
CGMVersionMacroDefine(2837,Extrapol_FS_OrientationImprovement                          ,JSX ,19-11-2007 ,"V5R18 SP3 - Orientation inversée dans certains cas ") // -cr b0465213
CGMVersionMacroDefine(2838,SurfaceToCanonic_XScaleR18SP3                               ,NLD ,19-11-2007 ,"V5R18 SP3 ")
CGMVersionMacroDefine(2839,NewDirectionnalProjection                                   ,OBH ,23-11-2007 ,"V5R18 SP3 - Dev Attendu en R18SP1 ") // -cr A0588622 C0588622 A0598411 B0598411
CGMVersionMacroDefine(2840,PtSurGen_TestDecalage                                       ,KUU ,23-11-2007 ,"V5R18 SP3 - RI0597894 et RI0601364 ")
CGMVersionMacroDefine(2841,Sweep_FillTwistOrientationsManagementV2                     ,NLD ,30-11-2007 ,"V5R18 SP3 ")
CGMVersionMacroDefine(2842,Blend_CouplingLaw_TopoToGeo                                 ,JSX ,30-11-2007 ,"V5R18 SP3 - R19 Evo Topo for Bend Coupling ")
CGMVersionMacroDefine(2843,ThickSurface_OneStepVolumeLevel10                           ,MNJ ,30-11-2007 ,"V5R18 SP3 - RI REG ") // promote -cr B0604086 C0604086 D0604086 B0604675 C0604675 D0604675
CGMVersionMacroDefine(2844,Extrapol_ShellG1_Until_CheckDisconnectableOnlyFor1DDom      ,jsx ,07-12-2007 ,"V5R18 SP3 - MLK dans odt appli ")
CGMVersionMacroDefine(2845,Approx_CheckVerticalTangency                                ,KUB ,07-12-2007 ,"V5R18 SP3 - Ajout d\'un methode pour traiter des tangentes verticales dans l\'approx ") // -cr A0601143 B0601143 C0601143
CGMVersionMacroDefine(2846,Sweep_UseProfilePlanesToClose                               ,NLD ,07-12-2007 ,"V5R18 SP3 ") // -cr 604331a 604331b
CGMVersionMacroDefine(2847,Sweep_FillTwistReductionAtClosure                           ,NLD ,07-12-2007 ,"V5R18 SP3 ")
CGMVersionMacroDefine(2848,PtDir_ChangeFaceFromVtx                                     ,AOV ,07-12-2007 ,"V5R18 SP3 - RI603461 ")
CGMVersionMacroDefine(2849,Parallel_ThrowWhenInvalidBody                               ,IZE ,07-12-2007 ,"V5R18 SP3 - RI ") // -cr B0601762 C0601762 D0601762
CGMVersionMacroDefine(2850,Thick_BetterDistrictAndSector                               ,LAP ,07-12-2007 ,"V5R18 SP3 - RI ") // -cr A0601980 B0601980 C0601980
CGMVersionMacroDefine(2851,Split_ExtrapError                                           ,JHN ,07-12-2007 ,"V5R18 SP3 - RI ") // -cr 605394B 605394C 605394D
CGMVersionMacroDefine(2852,RibSweep_ResidualTouch                                      ,SOU ,10-12-2007 ,"V5R18 SP3 - RI ") // A0603209
CGMVersionMacroDefine(2853,CGMR18SP3HF1                                                ,RHA ,11-12-2007 ,"V5R18 SP3 ")
CGMVersionMacroDefine(2854,CGMR18SP3HF2                                                ,RHA ,11-12-2007 ,"V5R18 SP3 ")
CGMVersionMacroDefine(2855,CGMR18SP3HF3                                                ,RHA ,11-12-2007 ,"V5R18 SP3 ")
CGMVersionMacroDefine(2856,CGMR18SP3HF4                                                ,RHA ,11-12-2007 ,"V5R18 SP3 ")
CGMVersionMacroDefine(2857,CGMR18SP3HF5                                                ,RHA ,11-12-2007 ,"V5R18 SP3 ")


//=========================================================================================================
// V5R18 SP4
//=========================================================================================================
CGMVersionMacroDefine(2858,Compatible_Journal                                          ,JHN ,14-12-2007 ,"V5R18 SP4 - journal complet compatible ") // developpement
CGMVersionMacroDefine(2859,Sweep_XScaleR18SP4                                          ,NLD ,14-12-2007 ,"V5R18 SP4 ")
CGMVersionMacroDefine(2860,ThickSurface_OneStepVolumeLevel11                           ,MNJ ,14-12-2007 ,"V5R18 SP4 - RI ") // -cr B0563475
CGMVersionMacroDefine(2861,Fill_TwistFillAnalytique                                    ,MPS ,14-12-2007 ,"V5R18 SP4 - RI  A604299 B604299 C604299 ") // -cr A0604299 B0604299 C0604299
CGMVersionMacroDefine(2862,Fillet_R18SP4                                               ,RR  ,14-12-2007 ,"V5R18 SP4 - RIs ")
CGMVersionMacroDefine(2863,PosPtLoopEdgeFull                                           ,DAD ,14-12-2007 ,"V5R18 SP4 - Boolean in 3DViaShape ") // CGMTest_GeometryReplayPositionPtLoopBigScale\\CATPositionPtLoopBigScale.CGMReplay
CGMVersionMacroDefine(2864,Corner_Planar_Perfo                                         ,fds ,17-12-2007 ,"V5R18 SP4 - Performance du corner plan ")
CGMVersionMacroDefine(2865,Parallel_RadialSortSurfaceAmbiguity                         ,IZE ,20-12-2007 ,"V5R18 SP4 - RI ") // -cr A0603713 B0603713 A0606347
CGMVersionMacroDefine(2866,DistanceBodyBody_AdditionalInits                            ,FSQ ,21-12-2007 ,"V5R18 SP4 - RI ") // -cr B0603933 C0603933 D0603933
CGMVersionMacroDefine(2867,Thick_RemoveFaceLevel25                                     ,MNJ ,04-01-2008 ,"V5R18 SP4 - dev ")
CGMVersionMacroDefine(2868,Compatible_Lucarne                                          ,JHN ,07-01-2008 ,"V5R18 SP4 - correction Booleen V5 vs Booleen proto ") // no
CGMVersionMacroDefine(2869,Thick_RemoveFaceLevel26                                     ,MNJ ,11-01-2008 ,"V5R18 SP4 - dev ")
CGMVersionMacroDefine(2870,PtSur_BoundaryWithInit                                      ,KUU ,11-01-2008 ,"V5R18 SP4 - RI0602546 ")
CGMVersionMacroDefine(2871,SurfToCan_TorusLogicDetection                               ,DAD ,14-01-2008 ,"V5R18 SP4 - Dev pour ILC ")
CGMVersionMacroDefine(2872,SurfToCan_CylLogicDetection                                 ,DAD ,14-01-2008 ,"V5R18 SP4 - Dev pour ILC ") // 14-01-2008
CGMVersionMacroDefine(2873,AutoFillet_SkinJournal                                      ,cwm ,15-01-2008 ,"V5R18 SP4 - Integration AutoFillet surfacique ")
CGMVersionMacroDefine(2874,Parallel_RelimitationCriteria                               ,IZE ,18-01-2008 ,"V5R18 SP4 - RI ") // -cr A0602824
CGMVersionMacroDefine(2875,IntPlnPln_ConfManagement                                    ,DAD ,18-01-2008 ,"V5R18 SP4 - IR 0594127, confusion management when a corner is or not between other solution ") // -cr A0594127
CGMVersionMacroDefine(2876,Compatible_JournalCLS                                       ,jhn ,18-01-2008 ,"V5R18 SP4 - compatible et CATIALiveShape ")
CGMVersionMacroDefine(2877,RemoveFace_LengthExtrapolationWithCurvature                 ,MNJ ,18-01-2008 ,"V5R18 SP4 - dev ") // activation immédiate le 18-01-2008
CGMVersionMacroDefine(2878,Prism_Until_Journal                                         ,fds ,21-01-2008 ,"V5R18 SP4 - RI ") // -cr A0607549 B0607549
CGMVersionMacroDefine(2879,IntConeSur_TanPoleTreatment                                 ,DAD ,21-01-2008 ,"V5R18 SP4 - RI 0603116 ; traitement des poles dans le cas d\'une intersection Cone ") // -cr B0603116 C0603116 D0603116
CGMVersionMacroDefine(2880,UnfoldTransfer_EdgeOnTear                                   ,SUH ,25-01-2008 ,"V5R18 SP4 - RI ") // -cr A0606841 B0606841
CGMVersionMacroDefine(2881,UnFoldedAero_ShellMathNormalFix                             ,REN ,25-01-2008 ,"V5R18 SP4 - ODT KO ") // -
CGMVersionMacroDefine(2882,MarshMallow_StrechedTreatment                               ,PMG ,25-01-2008 ,"V5R18 SP4 - ri 0606129 ") // -cr B0606129 C606129 D606129
CGMVersionMacroDefine(2883,Extrapol_HoldCurveKeepEdgeFillet                            ,SOU ,25-01-2008 ,"V5R18 SP4 - Dev ") // R18 SP4
CGMVersionMacroDefine(2884,ThickSurface_OneStepVolumeLevel14                           ,MNJ ,25-01-2008 ,"V5R18 SP4 - RI ") // promote -cr A0610179 B0610179 C0610179
CGMVersionMacroDefine(2885,Sewing_RedondantCurve                                       ,JHN ,25-01-2008 ,"V5R18 SP4 - RI Reg ") // adl_promote -cr 603790B 603790C 603790D
CGMVersionMacroDefine(2886,Fill_SingularityDetection                                   ,MPS ,28-01-2008 ,"V5R18 SP4 - probleme detecte dans le Fill pour CATIA LIVE SHAPE ")
CGMVersionMacroDefine(2887,PtSurCanonic_DistOnLimitPoints                              ,DAD ,28-01-2008 ,"V5R18 SP4 - RI 609654 and 609659 ") // -cr B0609654 C0609654  D0609654  B0609659 C0609659 D0609659
CGMVersionMacroDefine(2888,TopoIML_NormalizeConvolution                                ,JJC ,01-02-2008 ,"V5R18 SP4 - Dev ")
CGMVersionMacroDefine(2889,Intersect_DuplicateEdge                                     ,JHN ,01-02-2008 ,"V5R18 SP4 - RI ") // -cr 605355B 605355C 605355D 605355E 605351B 605351C 605351D 605351A
CGMVersionMacroDefine(2890,Intersect_CouplingEE                                        ,JHN ,01-02-2008 ,"V5R18 SP4 - RI 604336 ") // adl_promote -cr 604336B 604336C 604336D 604336E
CGMVersionMacroDefine(2891,DistCrvSur_InitExtremity_BoundingBox                        ,KUU ,08-02-2008 ,"V5R18 SP4 - RI0601184 ")
CGMVersionMacroDefine(2892,AutoDraft_ForFailedExtrapol                                 ,EYL ,08-02-2008 ,"V5R18 SP4 - Dev ")
CGMVersionMacroDefine(2893,AutoFillet_NonConnexPolyLineSupports                        ,IZE ,08-02-2008 ,"V5R18 SP4 - RI ") // -cr A0609450 B0609450 C0609450 D0609450
CGMVersionMacroDefine(2894,TrimByThick_CommonSRepFilterForDisconnect                   ,MNJ ,08-02-2008 ,"V5R18 SP4 - RI MNT ")
CGMVersionMacroDefine(2895,Loft_LooseTangOnGuide_PlaneCase                             ,JSX ,15-02-2008 ,"V5R18 SP4 - RI A0611049 ") // -cr A0611049 C0611049
//CGMVersionMacroDefine(2896,IntSurSur_RattrapAttr                                       ,DAD ,15-02-2008 ,"V5R18 SP4 - RI 0601174 ") // -cr A0601174 B0601174 C0601174 // debranche le 15-02-2008
CGMVersionMacroDefine(2897,NurbsLinearTransfo                                          ,dr  ,15-02-2008 ,"V5R18 SP4 - ri ")
CGMVersionMacroDefine(2898,UnFoldedAero_ProjCrvCrvFix                                  ,REN ,15-02-2008 ,"V5R18 SP4 - RI 608338 ")
CGMVersionMacroDefine(2899,POECDifferentiation                                         ,JHN ,15-02-2008 ,"V5R18 SP4 - Ri MNT ") // -cr 608531A 608531B 608531C 608531D
CGMVersionMacroDefine(2900,Relimit_NeedPosition                                        ,JHN ,15-02-2008 ,"V5R18 SP4 - RI externe ") // -cr 607784A 607784B 607784C
CGMVersionMacroDefine(2901,Compatible_JournalEnCoin                                    ,OID ,15-02-2008 ,"V5R18 SP4 - RI ") // -cr 614856A 614856B
CGMVersionMacroDefine(2902,CGMR18SP4HF1                                                ,RHA ,19-02-2008 ,"V5R18 SP4 ")
CGMVersionMacroDefine(2903,CGMR18SP4HF2                                                ,RHA ,19-02-2008 ,"V5R18 SP4 ")
CGMVersionMacroDefine(2904,CGMR18SP4HF3                                                ,RHA ,19-02-2008 ,"V5R18 SP4 ")
CGMVersionMacroDefine(2905,CGMR18SP4HF4                                                ,RHA ,19-02-2008 ,"V5R18 SP4 ")
CGMVersionMacroDefine(2906,CGMR18SP4HF5                                                ,RHA ,19-02-2008 ,"V5R18 SP4 ")


//=========================================================================================================
// V5R18 SP5
//=========================================================================================================
CGMVersionMacroDefine(2907,RemoveFace_StabilizeHomotopiesCreation                      ,MNJ ,21-02-2008 ,"V5R18 SP5 - dev pour CATIA Live Shape ")
CGMVersionMacroDefine(2908,HomotopyCrvSur_LightCheckResult                             ,MNJ ,21-02-2008 ,"V5R18 SP5 - correction bug ")
CGMVersionMacroDefine(2909,Split_FlattenFace                                           ,JHN ,22-02-2008 ,"V5R18 SP5 - Bug detecte par Remi a corriger + RI ") // -cr 612882B 612882C 612882D 612882E :ODT KO CGMTest_SurfacicSweep88 vu avec NLD
CGMVersionMacroDefine(2910,Prism_Until_Partial                                         ,fds ,22-02-2008 ,"V5R18 SP5 - Evolution pour GSD ")
CGMVersionMacroDefine(2911,Compatible_Vertices                                         ,JHN ,25-02-2008 ,"V5R18 SP5 - RI Interne ") // -cr 615117A 615117B
CGMVersionMacroDefine(2912,Fillet_R18SP5                                               ,PRL ,25-02-2008 ,"V5R18 SP5 - RI ")
CGMVersionMacroDefine(2913,DistanceBodyBody_NewConvergenceDirectionPlanePlane          ,FSQ ,29-02-2008 ,"V5R18 SP5 - RI ") // -cr F0611033
CGMVersionMacroDefine(2914,Fill_LockUnlockManagement                                   ,MPS ,29-02-2008 ,"V5R18 SP5 - RI 612115 ") // -cr B0612115  C0612115  D0612115  E0612115
CGMVersionMacroDefine(2915,Compatible_UnFollowedEdge                                   ,JHN ,29-02-2008 ,"V5R18 SP5 - MUST FIX JHI ") // a venir
CGMVersionMacroDefine(2916,Fillet_DegeneratedEdge                                      ,JHN ,29-02-2008 ,"V5R18 SP5 - RI MNT ") // -cr 613741B 613741C 613741D 613741E
CGMVersionMacroDefine(2917,Sweep_XScaleR18SP5                                          ,NLD ,29-02-2008 ,"V5R18 SP5 ")
CGMVersionMacroDefine(2918,SmartProject_SearchLimit                                    ,JHN ,29-02-2008 ,"V5R18 SP5 - pb BOEING SmartProjection ") // action longue avec RIs originaux clos SUG
//CGMVersionMacroDefine(2919,Extrapol_HoldCurveCircleFillet                              ,IEY ,03-03-2008 ,"V5R18 SP5 - KO Case : CGMTest_SurfacicN1AppFilletShapeShapeShape, Case003 ") // KO Case : CGMTest_SurfacicN1AppFilletShapeShapeShape, Case003 // debranche le 07-03-08
CGMVersionMacroDefine(2920,Fill_OrderedEdges                                           ,MPS ,07-03-2008 ,"V5R18 SP5 - RI 617006 ") // -cr  A0617006 B0617006
CGMVersionMacroDefine(2921,CGMR205HF1                                                  ,RHA ,07-03-2008 ,"V5R18 SP5 ")
CGMVersionMacroDefine(2922,CGMR205HF2                                                  ,RHA ,07-03-2008 ,"V5R18 SP5 ")
CGMVersionMacroDefine(2923,CGMR205HF3                                                  ,RHA ,07-03-2008 ,"V5R18 SP5 ")
CGMVersionMacroDefine(2924,CGMR205HF4                                                  ,RHA ,07-03-2008 ,"V5R18 SP5 ")
CGMVersionMacroDefine(2925,CGMR205HF5                                                  ,RHA ,07-03-2008 ,"V5R18 SP5 ")
CGMVersionMacroDefine(2926,CGMR205HF6                                                  ,RHA ,07-03-2008 ,"V5R18 SP5 ")
CGMVersionMacroDefine(2927,CGMR205HF7                                                  ,RHA ,07-03-2008 ,"V5R18 SP5 ")
CGMVersionMacroDefine(2928,CGMR205HF8                                                  ,RHA ,07-03-2008 ,"V5R18 SP5 ")
CGMVersionMacroDefine(2929,CGMR205HF9                                                  ,RHA ,07-03-2008 ,"V5R18 SP5 ")
CGMVersionMacroDefine(2930,CGMR205HF10                                                 ,RHA ,07-03-2008 ,"V5R18 SP5 ")
CGMVersionMacroDefine(2931,ExtrapolWire_R18SP5                                         ,IZE ,07-03-2008 ,"V5R18 SP5 - RI, développements ")
CGMVersionMacroDefine(2932,SmartProject_Bifurcation                                    ,JHN ,10-03-2008 ,"V5R18 SP5 - problemes BOEING ")
CGMVersionMacroDefine(2933,AutoDraft_Untwist_1                                         ,SOU ,14-03-2008 ,"V5R18 SP5 - R18 SP5 dev ")
CGMVersionMacroDefine(2934,Unfold_RuledSurface_NonDevelopWarning                       ,JSX ,14-03-2008 ,"V5R18 SP5 - RI Pb de precision de l\'unfold des RuledSufaces ")
CGMVersionMacroDefine(2935,RemoveFace_UVBoxForX2S                                      ,MNJ ,14-03-2008 ,"V5R18 SP5 - RI MNT ") // -cr A0615666 C0615666 C0616678 E0616678
CGMVersionMacroDefine(2936,Simplify_GroupSplit_Advanced                                ,FDS ,21-03-2008 ,"V5R18 SP5 - RI ") // -cr A0602667 B0602667 D0602667
CGMVersionMacroDefine(2937,SurfToCan_CircProjRattrap                                   ,DAD ,21-03-2008 ,"V5R18 SP5 - ODT Step / IR 0616687 ") // -cr A0616687 B0616687
CGMVersionMacroDefine(2938,IntCrvCrv_UseGivenLimits                                    ,DAD ,21-03-2008 ,"V5R18 SP5 - RI 0612144 ; Use input limits in IntersectionCrvCrv instead of Max Limits ") // -cr B0612144 C0612144 E0612144
CGMVersionMacroDefine(2939,Loft_G1andG0_DeformationOfProfile                           ,JSX ,21-03-2008 ,"V5R18 SP5 - RI ") // -cr A0616070 B0616070 C0616070 [sweep39 case400b] [sweep97 case977]
CGMVersionMacroDefine(2940,Helix_PeriodTolerance                                       ,JHN ,21-03-2008 ,"V5R18 SP5 - RI MNT ") // -cr 618261A 618261B
CGMVersionMacroDefine(2941,RemoveFace_FaceIsMandatoryThanksToEdge                      ,RR  ,21-03-2008 ,"V5R18 SP5 - RI ") // Creation et activation ASAP, SVP
CGMVersionMacroDefine(2942,CCVCleaner_ApproximateBeforeDeformation                     ,NLD ,21-03-2008 ,"V5R18 SP5 ")
CGMVersionMacroDefine(2943,Sweep_DeploySoftwareConfigurationV7                         ,NLD ,21-03-2008 ,"V5R18 SP5 ")
CGMVersionMacroDefine(2944,Sweep_PartDesignCanonicDetection                            ,NLD ,21-03-2008 ,"V5R18 SP5 ")
CGMVersionMacroDefine(2945,RollLines_ReduceNewtonStep                                  ,JSX ,21-03-2008 ,"V5R18 SP5 - RI 586949 ") // -cr a0586949
CGMVersionMacroDefine(2946,ProjCrvSurGen_SetLimOnSameTan                               ,DAD ,28-03-2008 ,"V5R18 SP5 - ODTs XScale ")
CGMVersionMacroDefine(2947,RemoveFace_SharpTriPtFailureByPass                          ,MNJ ,28-03-2008 ,"V5R18 SP5 - migration SolidWorks ")
CGMVersionMacroDefine(2948,Fillet_FrozenVertex                                         ,JHN ,28-03-2008 ,"V5R18 SP5 - ri MNT externe ") // -cr 616016A 616016B 616016C
CGMVersionMacroDefine(2949,Compatible_VolumesConnectedByFull                           ,OID ,28-03-2008 ,"V5R18 SP5 - Dev ") // Correction bug
CGMVersionMacroDefine(2950,Marching_NonCompleteSetAccepted_TestPointValidity           ,kjd ,31-03-2008 ,"V5R18 SP5 - RI ")
//CGMVersionMacroDefine(2951,CleanCurve_GlobalOptimisation2                              ,RNO ,04-04-2008 ,"V5R18 SP5 - Correction d\'un bug concernant les courbes ayant une orientation negative et dont le parametrage ne demarre pas a 0 ") // debranche le 03-04-2008
CGMVersionMacroDefine(2952,Thick_TriSurPtFilter                                        ,MNJ ,04-04-2008 ,"V5R18 SP5 - perfos ") // activation immédiate le 04-04-2008
CGMVersionMacroDefine(2953,HybridVarOffset_RobustSplit                                 ,FKJ ,04-04-2008 ,"V5R18 SP5 - Dev. R18 ")
CGMVersionMacroDefine(2954,AutoDraft_PolyLineSupportMinimization                       ,EYL ,07-04-2008 ,"V5R18 SP5 - Dev ")
CGMVersionMacroDefine(2955,Corner3D_PCircle                                            ,FDS ,07-04-2008 ,"V5R18 SP5 - RI ") // -cr A0619801 B0619801 C0619801
CGMVersionMacroDefine(2956,Sweep_ForceLocalMinBugCorrected                             ,NLD ,11-04-2008 ,"V5R18 SP5 ")
CGMVersionMacroDefine(2957,Thick_ShuntDisconnect3D                                     ,MNJ ,11-04-2008 ,"V5R18 SP5 - perfos ") // activation immediate le 11-04-2008
CGMVersionMacroDefine(2958,Revol_Circle_Closure                                        ,FDS ,14-04-2008 ,"V5R18 SP5 ") // -cr A0620624 B0620624 C0620624
CGMVersionMacroDefine(2959,OffsetSurface_NbOfSampling                                  ,KUU ,18-04-2008 ,"V5R18 SP5 - RI0610131 ")
CGMVersionMacroDefine(2960,Thick_DirectionalSurfaceQualityLevel1                       ,LAP ,18-04-2008 ,"V5R18 SP5 ") // -cr 614548A


//=========================================================================================================
// V5R18 SP6
//=========================================================================================================
CGMVersionMacroDefine(2961,Parallel_DegenerateNupletOrientationFix                     ,REN ,25-04-2008 ,"V5R18 SP6 - RI 619004 ") // R18 SP6
CGMVersionMacroDefine(2962,Fillet_R18SP6                                               ,cwm ,25-04-2008 ,"V5R18 SP6 - RI ")
CGMVersionMacroDefine(2963,DistanceMin_PtOnFace                                        ,FSQ ,02-05-2008 ,"V5R18 SP6 - RI ") // -cr  A0618146   B0618146   C0618146
CGMVersionMacroDefine(2964,Split_NoIntersectionError                                   ,JHN ,02-05-2008 ,"V5R18 SP6 - RI ") // -cr 621127A 621127B
CGMVersionMacroDefine(2965,Intersect_JournalIsolateVertex                              ,JHN ,02-05-2008 ,"V5R18 SP6 - RI ") // -cr 617472A 617472C
CGMVersionMacroDefine(2966,UnluckyFiniteDifferenceInFuckingLawDistPrototype            ,NLD ,02-05-2008 ,"V5R18 SP6 ") // -cr A0618553 B0618553
CGMVersionMacroDefine(2967,AssembleWire_OneEdge                                        ,JHN ,02-05-2008 ,"V5R18 SP6 - RI ") // -cr 622848A 622848B
CGMVersionMacroDefine(2968,ConfusionPtOnCrvPtOnCrvMassV2                               ,NLD ,02-05-2008 ,"V5R18 SP6 ")
CGMVersionMacroDefine(2969,Revol_Circle_Closure_Bis                                    ,FDS ,09-05-2008 ,"V5R18 SP6 - Correction complementaire ")
//CGMVersionMacroDefine(2970,Parallel_DegenerateSolutionDeletion                         ,IZE ,09-05-2008 ,"V5R18 SP6 - RI+ODT (activation R18SP6) ") // -cr B0619794 C0619794 // debranche le 21-05-2008
CGMVersionMacroDefine(2971,RibSweep_TwistDetection1                                    ,SOU ,09-05-2008 ,"V5R18 SP6 - RI A0617983, C0617983 ") // for R18 SP6 and above
CGMVersionMacroDefine(2972,Compatible_FatEdge                                          ,JHN ,16-05-2008 ,"V5R18 SP6 - traitment fat edge dans compatible ") // probleme CLS et 3DVia
CGMVersionMacroDefine(2973,Thick_StaplesTriggerNewEdgeOffPass                          ,MNJ ,16-05-2008 ,"V5R18 SP6 - RI ") // promote -cr A0622534 B0622534 C0622534 A0621293 A0621295
//CGMVersionMacroDefine(2974,Marching_ActivateLevel8AsDefaultLevel                       ,KJD ,16-05-2008 ,"V5R18 SP6 - Homogeneisation CATMathImplicitSystem ") // debranche le 21-05-2008
CGMVersionMacroDefine(2975,Thick_DirectionalSurfaceQualityLevel1Step2                  ,LAP ,16-05-2008 ,"V5R18 SP6 - RI ") // -cr 614548A
CGMVersionMacroDefine(2976,Intersect_EraseMixedInter                                   ,JHN ,16-05-2008 ,"V5R18 SP6 - RI ") // -cr 620153A 620153B
CGMVersionMacroDefine(2977,Compatible_NoCloseScarForFull                               ,JHN ,16-05-2008 ,"V5R18 SP6 - ri 3dvia ") // -cr 620196A
CGMVersionMacroDefine(2978,RemoveFace_RobustnessLevel5                                 ,MNJ ,23-05-2008 ,"V5R18 SP6 - RI MNT ") // promote -cr A0621952 B0621952
CGMVersionMacroDefine(2979,Homotopy_OrthogonalCheck                                    ,LAP ,23-05-2008 ,"V5R18 SP6 - RI 604182 ") // -cr A0604182
CGMVersionMacroDefine(2980,CGMR18SP6HF1                                                ,RHA ,28-05-2008 ,"V5R18 SP6 ")
CGMVersionMacroDefine(2981,CGMR18SP6HF2                                                ,RHA ,28-05-2008 ,"V5R18 SP6 ")
CGMVersionMacroDefine(2982,CGMR18SP6HF3                                                ,RHA ,28-05-2008 ,"V5R18 SP6 ")
CGMVersionMacroDefine(2983,CGMR18SP6HF4                                                ,RHA ,28-05-2008 ,"V5R18 SP6 ")
CGMVersionMacroDefine(2984,CGMR18SP6HF5                                                ,RHA ,28-05-2008 ,"V5R18 SP6 ")


//=========================================================================================================
// V5R19 GA
//=========================================================================================================
CGMVersionMacroDefine(3050,ParallelGeodesic_InputClean                                 ,AOV ,21-02-2008 ,"V5R19 GA - nouveau projet parallele geodesic option clean ") // activation simultanée avec les variables : ParallelGeodesic_PtDirEnhancement et Parallel_MissingSolTask
CGMVersionMacroDefine(3051,ParallelGeodesic_PtDirEnhancement                           ,REN ,21-02-2008 ,"V5R19 GA - enhancement in PtDir for gap crossing ") // activation simultanée avec les variables : ParallelGeodesic_InputClean et Parallel_MissingSolTask
CGMVersionMacroDefine(3052,Parallel_MissingSolTask                                     ,AOV ,21-02-2008 ,"V5R19 GA - Dev ") // integration JE dans parallele ; activation simultanée avec les variables : ParallelGeodesic_PtDirEnhancement et ParallelGeodesic_InputClean
CGMVersionMacroDefine(3053,Transfo_IsoSimilitudeFixed                                  ,fds ,21-03-2008 ,"V5R19 GA - IsoSimilitude du scaling dans transfomanager a partir R19 ") // IsoSimilitude du scaling dans transfomanager a partir R19
CGMVersionMacroDefine(3054,DistanceBodyBody_WireBodyNewImpl                            ,MPX ,25-04-2008 ,"V5R19 GA - Dev ") // For R19 GA (not for R18)
CGMVersionMacroDefine(3055,DistanceBodyBody_FaceFaceNewImpl                            ,FSQ ,25-04-2008 ,"V5R19 GA - Dev ") // For R19 GA (not for R18)


//=========================================================================================================
// V5R19 SP1
//=========================================================================================================
CGMVersionMacroDefine(3058,UnfoldFrF_BetterFitting2                                    ,SUH ,30-05-2008 ,"V5R19 SP1 - RI ") // -cr A0569691
CGMVersionMacroDefine(3059,Extrapol_ShellG1_NoInitialDeformationOfComb                 ,JSX ,30-05-2008 ,"V5R19 SP1 - RI : on ne deforme pas les peignes à la creation ") // -cr a0608323
CGMVersionMacroDefine(3060,IntersectWS_FillDegenerate                                  ,JHN ,30-05-2008 ,"V5R19 SP1 - ri 622863 ") // -cr 622863B 622863C
CGMVersionMacroDefine(3061,Offset_BorderSteps                                          ,MNJ ,30-05-2008 ,"V5R19 SP1 - RI MNT ") // promote -cr B0624865 C0624865
CGMVersionMacroDefine(3062,Fillet_SmoothRibWithHybShell                                ,RR  ,30-05-2008 ,"V5R19 SP1 - Improve smooting shape in Fillet ") // R19 SP1
CGMVersionMacroDefine(3063,Thick_TrickyFaceSelectionAroundVertex                       ,LAP ,30-05-2008 ,"V5R19 SP1 - Ri ") // -cr B0603323 D0603323
CGMVersionMacroDefine(3064,Pattern_ReduceBooleanOperation                              ,fds ,06-06-2008 ,"V5R19 SP1 - Optimisation perfo pattern pour solidworks ")
CGMVersionMacroDefine(3065,ProjCrvSur_EqSetTol                                         ,DAD ,06-06-2008 ,"V5R19 SP1 - RI 0610407 ") // -cr A0610407 C0610407
CGMVersionMacroDefine(3066,Fillet_R19SP1                                               ,IZE ,06-06-2008 ,"V5R19 SP1 - RI, ODT ")
CGMVersionMacroDefine(3067,TrimByThick_TopAndBottomTouchedImportFaces                  ,MNJ ,06-06-2008 ,"V5R19 SP1 - RI ") // promote -cr A0625862
CGMVersionMacroDefine(3068,SewSkin_TorusDisconnectError                                ,JHN ,06-06-2008 ,"V5R19 SP1 - RI ") // -cr 624615B 624615C
CGMVersionMacroDefine(3069,AutoDraft_AlmostTotalHardZone                               ,EYL ,13-06-2008 ,"V5R19 SP1 - Dev ")
CGMVersionMacroDefine(3070,AutoDraft_FaceSupportsSelection                             ,EYL ,13-06-2008 ,"V5R19 SP1 - dev ")
CGMVersionMacroDefine(3071,ImplicitSystemIsContainingV2                                ,NLD ,13-06-2008 ,"V5R19 SP1 ")
//CGMVersionMacroDefine(3072,TobRibUntwistVFill_RadiusDerivativeV2                       ,NLD ,13-06-2008 ,"V5R19 SP1 ") // debranche le 12/06/08
CGMVersionMacroDefine(3073,VectorialFunctionX_SecondDerivSign                          ,NLD ,13-06-2008 ,"V5R19 SP1 ")
CGMVersionMacroDefine(3074,CATSmoGlobalCutOperatorCx2_FollowCells                      ,RAQ ,13-06-2008 ,"V5R19 SP1 - Dev suivi topologique pour IMA ")
CGMVersionMacroDefine(3075,CATStoSubdivMeshOperatorImpl_InfoOnBorderEdges              ,RAQ ,13-06-2008 ,"V5R19 SP1 - Dev journal topo sur CATEdge bordantes ")
CGMVersionMacroDefine(3076,Projection_DepositPoint                                     ,JHN ,13-06-2008 ,"V5R19 SP1 - RI ") // -cr 626224A 626224B
CGMVersionMacroDefine(3077,SurSurWithInits_MonoArcDefDomainValidity                    ,MNJ ,13-06-2008 ,"V5R19 SP1 - RI ")
CGMVersionMacroDefine(3078,Sweep_Interpol_QualitySegment_CheckAll_BelowTolOverThreshold,JSX ,20-06-2008 ,"V5R19 SP1 - RI 32/64 instability ") // -cr B0626830
CGMVersionMacroDefine(3079,UnfoldFrF_CheckTwistOnFace                                  ,JSX ,20-06-2008 ,"V5R19 SP1 - necessaire a l\'activation P2S Level9 ")
//CGMVersionMacroDefine(3080,CleverInterpol_RunSingular_BalanceCorrection                ,kjd ,20-06-2008 ,"V5R19 SP1 - versionning interpol ") // debranche le 24/06/08
CGMVersionMacroDefine(3081,AutoDraft_R19SP1                                            ,PFV ,20-06-2008 ,"V5R19 SP1 ")
CGMVersionMacroDefine(3082,EdgeCurveTransfo_ReComputeMaxGap                            ,NLD ,20-06-2008 ,"V5R19 SP1 ")
CGMVersionMacroDefine(3083,Projection_MultiDegenerate                                  ,JHN ,20-06-2008 ,"V5R19 SP1 - RI ") // -cr 627102A 627102B
CGMVersionMacroDefine(3084,Homotopy_CrvSur_LargerDomain                                ,LAP ,20-06-2008 ,"V5R19 SP1 - RI621025 ") // -cr A0621025 B0621025 C0621025
CGMVersionMacroDefine(3085,Blend_AvoidTwist_Tangency_Forbidden                         ,JSX ,20-06-2008 ,"V5R19 SP1 - RI ")
CGMVersionMacroDefine(3086,CCVCleaner_CleanR18SP1                                      ,NLD ,20-06-2008 ,"V5R19 SP1 ")
CGMVersionMacroDefine(3087,Compatible_JournalPointCoin                                 ,JHN ,20-06-2008 ,"V5R19 SP1 - RI 3Dvia ") // -cr 628368A
//CGMVersionMacroDefine(3088,Spine_DeploySoftwareConfiguration                           ,NLD ,04-07-2008 ,"V5R19 SP1 ") // debranche le 30-06-08
CGMVersionMacroDefine(3089,IntSurSur_SmallerRelimitInRetPoint                          ,DAD ,04-07-2008 ,"V5R19 SP1 - IR 0623629 ") // -cr B0623629 C0623629
CGMVersionMacroDefine(3090,Revol_MultiFaces_OnAxis                                     ,FDS ,04-07-2008 ,"V5R19 SP1 - RI ") // -cr B620237
CGMVersionMacroDefine(3091,Regul_R19SP1                                                ,cwm ,04-07-2008 ,"V5R19 SP1 - RI ")
CGMVersionMacroDefine(3092,Compatible_NoTwinOnVertex                                   ,JHN ,04-07-2008 ,"V5R19 SP1 - RI ") // -cr 629607B
CGMVersionMacroDefine(3093,Project_MissingOnVertexNoTarget                             ,JHN ,04-07-2008 ,"V5R19 SP1 - RI ") // -cr 629897B 629897D
CGMVersionMacroDefine(3094,Split_ExtrapErrorDim2                                       ,JHN ,04-07-2008 ,"V5R19 SP1 - ri ") // -cr 629750B 629750C
//CGMVersionMacroDefine(3095,SewSkinIntersection_BadOrientation                          ,OID ,04-07-2008 ,"V5R19 SP1 - RI 629631 ") // - cr 629631A 629631B 629631C // debranche le 04/07/2008
CGMVersionMacroDefine(3096,P2S_Level9                                                  ,ktu ,11-07-2008 ,"V5R19 SP1 - Gestion unique des niveaux de l\'operateur ")
CGMVersionMacroDefine(3097,OrientationLoopArea_SquareLengthTest                        ,DAD ,11-07-2008 ,"V5R19 SP1 - Migration BigScale.  N.B Contre ")
CGMVersionMacroDefine(3098,ThickSurface_SideRibbonStabilizationLevel4                  ,MNJ ,11-08-2008 ,"V5R19 SP1 - RI ") // activation immediate le 11-07-2008
CGMVersionMacroDefine(3099,DistanceMin_AllVerticesOfFaceLoop                           ,FSQ ,11-07-2008 ,"V5R19 SP1 - RI ") // -cr A0622007 B0622007
CGMVersionMacroDefine(3100,SewSkinIntersection_BadOrientation                          ,OID ,11-07-2008 ,"V5R19 SP1 - RI 629631 ") // - cr 629631A 629631B 629631C // debranche le 04/07/2008
CGMVersionMacroDefine(3101,Thick_HomotopyResultTolerance                               ,LAP ,18-07-2008 ,"V5R19 SP1 - RI 626948 ") // -cr 626948B 626948C
CGMVersionMacroDefine(3102,Corner_ReportInit_Fix                                       ,IEY ,18-07-2008 ,"V5R19 SP1 - Development to utilize Report Init facility for corner opreator ")
CGMVersionMacroDefine(3103,ShellExpansion_PerfoOptimisation                            ,REN ,25-07-2008 ,"V5R19 SP1 - dev ")
CGMVersionMacroDefine(3104,IntCrvCrv_PCrvPCrvSingleCall                                ,DAD ,25-07-2008 ,"V5R19 SP1 - Perfo PCrvPCrv & IR 622683 ")
CGMVersionMacroDefine(3105,IntPlnSur_SetRadInResult                                    ,DAD ,25-07-2008 ,"V5R19 SP1 - RI 0623923 ") // -cr B0623923
CGMVersionMacroDefine(3106,ProjCrvSur_InitPole                                         ,DAD ,01-08-2008 ,"V5R19 SP1 - IR  0619712 ")


//=========================================================================================================
// V5R19 SP2
//=========================================================================================================
CGMVersionMacroDefine(3117,Sweep_GridEvalInTwistDetection                              ,NLD ,08-08-2008 ,"V5R19 SP2 ")
CGMVersionMacroDefine(3118,LinlCLEFromType_CleanOldCLE                                 ,OID ,08-08-2008 ,"V5R19 SP2 - RI 633 140 ") // -cr B0633140 C0633140
CGMVersionMacroDefine(3119,ForceGridEvalInTwistDetection                               ,NLD ,08-08-2008 ,"V5R19 SP2 ")
CGMVersionMacroDefine(3120,RibSweep_MarchingConstraint1                                ,SOU ,08-08-2008 ,"V5R19 SP2 - RI ") // for IR A0634098 fix to be delivered in R19SP1
CGMVersionMacroDefine(3121,DraftWithNoCells                                            ,EYL ,08-08-2008 ,"V5R19 SP2 - Correction RI ")
CGMVersionMacroDefine(3122,Fillet_R19SP2                                               ,cwm ,08-08-2008 ,"V5R19 SP2 - RIs ") // -cr A0627810 A0623926
CGMVersionMacroDefine(3123,Sweep_MVDKeepAfterExtrapolationV2                           ,NLD ,14-08-2008 ,"V5R19 SP2 ")
CGMVersionMacroDefine(3124,IMA_REVOLVE_ORIENT                                          ,RBD ,14-08-2008 ,"V5R19 SP2 - Dev SPR19 ")
//CGMVersionMacroDefine(3125,Boolean_SearchInBox                                         ,JHN ,14-08-2008 ,"V5R19 SP2 - ri ") // -cr 634104A 634104B
CGMVersionMacroDefine(3126,SameTan_AdmisSolution                                       ,DAD ,14-08-2008 ,"V5R19 SP2 - RI 0633156 ") // -cr B0633156 C0633156
CGMVersionMacroDefine(3127,Fill_AutoFillet_ImproveQuality                              ,MPS ,22-08-2008 ,"V5R19 SP2 - amelioration qualite pb autofillet Daimler Chrysler ")
CGMVersionMacroDefine(3128,SysPCrvPCrv_FindSingPoint_NormTest                          ,DAD ,22-08-2008 ,"V5R19 SP2 - IR 0622683 ") // -cr A0622683 B0622683
CGMVersionMacroDefine(3129,AutoDraft_ThinLinearZoneInit                                ,PFV ,22-08-2008 ,"V5R19 SP2 ")
CGMVersionMacroDefine(3130,ThickSurface_OneStepVolumeLevel15                           ,MNJ ,22-08-2008 ,"V5R19 SP2 - RI0635547 ") // -cr B0635547 C0635547
CGMVersionMacroDefine(3131,DistanceBodyBody_DistanceCrvSurWithInits                    ,FSQ ,22-08-2008 ,"V5R19 SP2 - RI ") // -cr B0627846 C0627846 B0625503 C0625503
CGMVersionMacroDefine(3132,TrimByThick_CheckResultMoved                                ,MNJ ,29-08-2008 ,"V5R19 SP2 - RI ") // -cr B0635547 C0635547 A0634939 B0634939 A0636710 B0636710 C0636710
CGMVersionMacroDefine(3133,SmartProjection_ExtremityDistance                           ,JHN ,29-08-2008 ,"V5R19 SP2 - RIs ") // -cr 635783B 635783C 636356B 636356C
CGMVersionMacroDefine(3134,Projection_ZTreatment                                       ,JHN ,29-08-2008 ,"V5R19 SP2 - ri ") // -cr 633216B 633216C
//CGMVersionMacroDefine(3135,IntSurSur_SurfacesBox                                       ,DAD ,05-09-2008 ,"V5R19 SP2 - IR 0634104 ") // -cr A0634104 B0634104
//CGMVersionMacroDefine(3136,Boolean_SearchInBox                                         ,JHN ,05-09-2008 ,"V5R19 SP2 - ri ") // -cr 634104A 634104B
CGMVersionMacroDefine(3137,UnFoldedAero_SnapEdgeFix                                    ,REN ,05-09-2008 ,"V5R19 SP2 - IR 636003 ")
//CGMVersionMacroDefine(3138,PlanarCurveIntegration                                      ,KUB ,05-09-2008 ,"V5R19 SP2 - RI ") // -cr 0689772A 0629772B
CGMVersionMacroDefine(3139,New_Mass_Computation                                        ,fds ,05-09-2008 ,"V5R19 SP2 - Dev. R18 pour AIRBUS ") // Dev. R18 pour AIRBUS , algorithme des treillis ( Lattice )  avec controle d\'erreur
CGMVersionMacroDefine(3140,Pattern_CircularJournal                                     ,fds ,05-09-2008 ,"V5R19 SP2 - RI ") // -cr A0614787
CGMVersionMacroDefine(3141,Thick_SeamECrvOffsetLimits                                  ,MNJ ,05-09-2008 ,"V5R19 SP2 - pb Daimler ")
CGMVersionMacroDefine(3142,Sewing_TouchOnVertexVolume                                  ,JHN ,05-09-2008 ,"V5R19 SP2 - RI ") // -cr 633903B 633903C
CGMVersionMacroDefine(3143,HLR_StripCrossingRayManagement                              ,dps ,05-09-2008 ,"V5R19 SP2 - Reimplementation du lancer de rayon dans CATHLRSface::surrounding() pour les cas francs (hors bords) ") // -cr A0635921 B0635921
//CGMVersionMacroDefine(3144,LayDownCrvSur_SquareTolInFastInt                            ,DAD ,12-09-2008 ,"V5R19 SP2 - Tolerance bug in Laydown ")
CGMVersionMacroDefine(3145,Sweep_SpineData_SoftwareQuality                             ,JSX ,12-09-2008 ,"V5R19 SP2 - Remove duplicated method, Add Dump in spine Software ") // require  before correction of 0633019
CGMVersionMacroDefine(3146,Sweep_SpineData_StabilizeSpineForLinearProfiles             ,JSX ,12-09-2008 ,"V5R19 SP2 - le spine ne repercute  pas correctement la rotation de ses inputs ") // -cr C0633019 B0633019
CGMVersionMacroDefine(3147,Marching_FindNewPoint_BorderTreatment                       ,KJD ,12-09-2008 ,"V5R19 SP2 - RI ") // -cr A(B)0625166. ODT KO : CGMTest_NewTopoDiff9->livraison vend du changement ref
CGMVersionMacroDefine(3148,AutoDraft_R19SP2                                            ,EYL ,12-09-2008 ,"V5R19 SP2 - dev ")
CGMVersionMacroDefine(3149,HLR_CheckHidingTriangleIsInsideFace                         ,DPS ,12-09-2008 ,"V5R19 SP2 - Renforcement de la condition d\'interiorite a une face pour tout triangle cachant 1 point dont on cherche a determiner la visibilite ") // -cr A0627469 B0627469
CGMVersionMacroDefine(3150,Thick_NoTrickyFaceAroundMultiErep                           ,LAP ,12-09-2008 ,"V5R19 SP2 - RI628505 ") // no -cr
CGMVersionMacroDefine(3151,UnfoldFrF_TwistDetectionFix                                 ,REN ,12-09-2008 ,"V5R19 SP2 - ODT ")
CGMVersionMacroDefine(3152,Chamfer_ChordLength                                         ,BQJ ,12-09-2008 ,"V5R19 SP2 - Dev ")
CGMVersionMacroDefine(3153,Thick_CheckMaxLimitIsopares                                 ,MNJ ,12-09-2008 ,"V5R19 SP2 - perfos ")
CGMVersionMacroDefine(3154,Join_TestConfusionPourrie                                   ,JHN ,12-09-2008 ,"V5R19 SP2 - RIs ") // en attente reponse JEP
CGMVersionMacroDefine(3155,Boolean_SearchInBox                                         ,JHN ,12-09-2008 ,"V5R19 SP2 - ri ") // -cr 634104A 634104B
CGMVersionMacroDefine(3156,RSO_Registration1                                           ,PMG ,19-09-2008 ,"V5R19 SP2 - 2 bugs dans les calcul de convolutions ")
CGMVersionMacroDefine(3157,Thick_NoInterGeomAnomalyNeighborSReps                       ,MNJ ,19-09-2008 ,"V5R19 SP2 - RI ") // -cr B0639023 C0639023
CGMVersionMacroDefine(3158,IntersectionPCrvPCrv_DistanceEqualToResolution              ,KUU ,19-09-2008 ,"V5R19 SP2 - RI 0628420 ")
CGMVersionMacroDefine(3159,General_Perfo_SP2                                           ,FDS ,23-09-2008 ,"V5R19 SP2 - Amelioration performance ")
CGMVersionMacroDefine(3160,CGMR206HF1                                                  ,RHA ,23-09-2008 ,"V5R19 SP2 ")
CGMVersionMacroDefine(3161,CGMR206HF2                                                  ,RHA ,23-09-2008 ,"V5R19 SP2 ")
CGMVersionMacroDefine(3162,CGMR206HF3                                                  ,RHA ,23-09-2008 ,"V5R19 SP2 ")
CGMVersionMacroDefine(3163,CGMR206HF4                                                  ,RHA ,23-09-2008 ,"V5R19 SP2 ")
CGMVersionMacroDefine(3164,CGMR206HF5                                                  ,RHA ,23-09-2008 ,"V5R19 SP2 ")
CGMVersionMacroDefine(3165,Sweep_VolumeOrientationV3                                   ,NLD ,26-09-2008 ,"V5R19 SP2 ") // -cr 634959a  634959c
CGMVersionMacroDefine(3166,MaxOffset_SubdivideStabilization                            ,MNJ ,26-09-2008 ,"V5R19 SP2 - RI ") // -cr B0575123
CGMVersionMacroDefine(3167,Sweep_ViewingDirection_PipeV4_V6                            ,NLD ,26-09-2008 ,"V5R19 SP2 ") // -cr A0638604 B0638604 D0638604
CGMVersionMacroDefine(3168,Blend_DirLaw_ClosedDomain                                   ,JSX ,03-10-2008 ,"V5R19 SP2 - Wrong use of directional law in case of closed Blend ") // -cr a0634979 b0634979 c0634979
CGMVersionMacroDefine(3169,Join_EdgeCurvePourrie                                       ,JHN ,03-10-2008 ,"V5R19 SP2 - ri ") // -cr 639620B 639620C 640165B 640165C
CGMVersionMacroDefine(3170,TrimByThick_EliminateMicroEdges                             ,MNJ ,03-10-2008 ,"V5R19 SP2 - RI ") // -cr A0637898 C0637898 A0638004 C0638004
CGMVersionMacroDefine(3171,DistanceBodyBody_NewPtMeshDistAlgo                          ,MPX ,10-10-2008 ,"V5R19 SP2 - MANDATORY IR (Regression in Perfo ODT ") // -cr A0637948, needed for R19Sp2
//CGMVersionMacroDefine(3172,HLR_OptimDiscretizeCurveToProject                           ,XCZ ,10-10-2008 ,"V5R19 SP2 - Spirale mal interpolée lors de la projection post HLR ") // -cr A0633265 B0633265
CGMVersionMacroDefine(3173,RibSweep_SmallSolutions                                     ,SOU ,10-10-2008 ,"V5R19 SP2 - RI A0635542 ") // to be activated for R19 SP3


//=========================================================================================================
// V5R19 SP3
//=========================================================================================================
CGMVersionMacroDefine(3184,AutoDraft_R19SP3                                            ,PFV ,17-10-2008 ,"V5R19 SP3 - Dev ") // Activation a l\'ouverture du SP3
CGMVersionMacroDefine(3185,HLR_OptimDiscretizeCurveToProject                           ,XCZ ,17-10-2008 ,"V5R19 SP3 - Spirale mal interpolée lors de la projection post HLR ") // -cr A0633265 B0633265 // debranche le 09-10-2008
CGMVersionMacroDefine(3186,RemoveFace_RobustnessLevel7                                 ,MNJ ,17-10-2008 ,"V5R19 SP3 - modele Renault ")
CGMVersionMacroDefine(3187,Fillet_R19SP3                                               ,RR  ,17-10-2008 ,"V5R19 SP3 - Fix ")
CGMVersionMacroDefine(3188,Boolean_SplitLoop                                           ,JHN ,17-10-2008 ,"V5R19 SP3 - RI ") // -cr 577215B
CGMVersionMacroDefine(3189,Loft_PreciseReportWithProfileVertices                       ,NLD ,17-10-2008 ,"V5R19 SP3 ") // -cr 640423a 640423b
CGMVersionMacroDefine(3190,AutoFillet_PointedShapeFillet                               ,cwm ,17-10-2008 ,"V5R19 SP3 - Dev gestion des pointes dans AutoFillet ") // -cr B0603691
CGMVersionMacroDefine(3191,ProjCrvCrv_LineTreatment                                    ,DAD ,24-10-2008 ,"V5R19 SP3 - RI 0578288 & 0574181 ") // -cr E0578288 D0578288 E0574181 D0574181 ; 2 ODTs Ã  rÃ©enregistrer en closed config dÃ¨s que j\'ai le No de variable.
CGMVersionMacroDefine(3192,Simplify_ClosedSurface_Inverse                              ,FDS ,24-10-2008 ,"V5R19 SP3 - RI ") // -cr A0636118 B0636118
CGMVersionMacroDefine(3193,Loft_NoDeformationOfProfilesWithSmallNeighbors              ,JSX ,24-10-2008 ,"V5R19 SP3 - RI ") // -cr b0640632 c0640632
CGMVersionMacroDefine(3194,Marching_ActivateLevel8AsDefaultLevel                       ,KJD ,24-10-2008 ,"V5R19 SP3 - Homogeneisation CATMathImplicitSystem ") // necessite activation prealable de ProjCrvCrv_LineTreatment
CGMVersionMacroDefine(3195,CleverInterpol_RunSingular_BalanceCorrection                ,kjd ,24-10-2008 ,"V5R19 SP3 - versionning interpol ")
CGMVersionMacroDefine(3196,Thick_EdgeSharpnessCut                                      ,MNJ ,24-10-2008 ,"V5R19 SP3 - RI AutoFillet ") // néant
CGMVersionMacroDefine(3197,IntSurSur_CylPlanMarchingType                               ,DAD ,31-10-2008 ,"V5R19 SP3 - PMR06903660706 ") // -cr A0642375 B0642375
CGMVersionMacroDefine(3198,DistanceBodyBody_CacheTessellation                          ,MPX ,31-10-2008 ,"V5R19 SP3 - Dev: new interface ReplaceBody in DistanceBodyBody ")
CGMVersionMacroDefine(3199,Fill_FillAnalytiqueMonoFace                                 ,MPS ,31-10-2008 ,"V5R19 SP3 - RI 642416 ") // -cr   A0642416 B0642416
CGMVersionMacroDefine(3200,IMA_Improve_CutByPlane                                      ,RBD ,31-10-2008 ,"V5R19 SP3 - Dev ")
CGMVersionMacroDefine(3201,Thick_EarlyDismissEndEdgeConfusions                         ,MNJ ,31-10-2008 ,"V5R19 SP3 - RI ") // -cr B0641408 C0641408 A0641745 B0641745
CGMVersionMacroDefine(3202,Sweep_OptimProjectBestPointOnCurrentDomain                  ,NLD ,31-10-2008 ,"V5R19 SP3 ")
//CGMVersionMacroDefine(3203,Tess_Disc_RemoveUselessPoints                               ,TPG ,07-11-2008 ,"V5R19 SP3 - A0642919 ") // pour auto draft
CGMVersionMacroDefine(3204,Sweep_VolumeOrientationV4                                   ,NLD ,07-11-2008 ,"V5R19 SP3 ") // - cr 637264b
CGMVersionMacroDefine(3205,Fill_InnerContraintsManagement                              ,MPS ,07-11-2008 ,"V5R19 SP3 - warning concerning inner constraints in GSD Fill ")
CGMVersionMacroDefine(3206,Sweep_TorusDetection                                        ,NLD ,07-11-2008 ,"V5R19 SP3 - IR ; Cf. DAD ") // -cr B0640351 C0640351
CGMVersionMacroDefine(3207,Compatible_Stabilized_Orientations                          ,oid ,07-11-2008 ,"V5R19 SP3 - Developpement : stabilisation des shells et wires dans compatible ") // Livraison simultanée vendedi de changements de références enR207. Reste 4 odts ko sur PartDBDUP
CGMVersionMacroDefine(3208,BlendRibbon_Hermetisation_CommonSupport                     ,SOU ,07-11-2008 ,"V5R19 SP3 - RI ") // -cr  A0642344 for R19 SP3
CGMVersionMacroDefine(3209,Blend_TopoSweepInfra6                                       ,JSX ,14-11-2008 ,"V5R19 SP3 - Calcul des oerinetations sans CATTopologiaclBlend ") // permet d\'utiliser le posage interne tolerant du sweep  (CFH pour VW en r19sp4 )
CGMVersionMacroDefine(3210,General_Perfo_SP3                                           ,TXO ,14-11-2008 ,"V5R19 SP3 - Perfo ")
CGMVersionMacroDefine(3211,Thick_VRepPlaneConfusionOptim                               ,MNJ ,14-11-2008 ,"V5R19 SP3 - RI ") // activation immédiate le 14-11-2008
CGMVersionMacroDefine(3212,Loi2DistanceBorderLineAVelizy2Mes2                          ,NLD ,21-11-2008 ,"V5R19 SP3 ")
CGMVersionMacroDefine(3213,CrvLengths_OptimLine                                        ,NLD ,28-11-2008 ,"V5R19 SP3 ")
CGMVersionMacroDefine(3214,CATSurfaceToCanonic_ControlMapping                          ,NLD ,28-11-2008 ,"V5R19 SP3 ") // -cr 623022a
CGMVersionMacroDefine(3215,Healing_Level28                                             ,JJC ,28-11-2008 ,"V5R19 SP3 - Dev ") // LocalTouch
CGMVersionMacroDefine(3216,CleanCurve_DataReductionStability2                          ,JSX ,28-11-2008 ,"V5R19 SP3 - Non respect des ratios de vitesse de parametrisation dans le code activé par Stability1 ") // Blend G2 pour VW R19sp3
CGMVersionMacroDefine(3217,WrapDir_AdvancedTwistDetection                              ,dr  ,28-11-2008 ,"V5R19 SP3 ") // Detection des mauvaises convergences (mauvaises surfaces de reference)
CGMVersionMacroDefine(3218,Thick_PropagateInvertedFacesToRemove                        ,MNJ ,28-11-2008 ,"V5R19 SP3 - RI 0641377 ") // promote -cr B0641377 C0641377
CGMVersionMacroDefine(3219,OffsetVar_Level3                                            ,PMG ,28-11-2008 ,"V5R19 SP3 - Correction Healing des normal ") // -cr B0641714 C0641714
CGMVersionMacroDefine(3220,CGMJournal_Tass_KEEP_Creation_A                             ,JMA ,28-11-2008 ,"V5R19 SP3 - RI 621740 ") // -cr A0621740
CGMVersionMacroDefine(3221,HLR_SearchContactWireArcXSilhArc                            ,DPS ,28-11-2008 ,"V5R19 SP3 - recherche des points de contact entre les wires poses geometriquement sur un BodySupport sans lien topologique et les silhouettes de ce Body ") // -cr B0643248 C0643248
CGMVersionMacroDefine(3222,HLR_ComputeExactTorusDistortion                             ,DPS ,28-11-2008 ,"V5R19 SP3 - recherche des distortions exactes sur les tores de facon a appliquer les tolerances 2D conformes aux tolerances 3D ") // -cr B0643896 C0643896
CGMVersionMacroDefine(3223,Disconnect_NbOriginating                                    ,JHN ,28-11-2008 ,"V5R19 SP3 - RI must fix ") // -cr 642679A 642679B
CGMVersionMacroDefine(3224,Fill_ModifConventionOrientation                             ,MPS ,05-12-2008 ,"V5R19 SP3 - Autofill pour SolidWorks => convention de remplissage pour les cylindres. ")
CGMVersionMacroDefine(3225,Fillet_DuplicateWithUpdateTouched                           ,JHN ,05-12-2008 ,"V5R19 SP3 - RI externe ") // -cr 642089B 642089C
CGMVersionMacroDefine(3226,Sewing_VertexProjection                                     ,JHN ,05-12-2008 ,"V5R19 SP3 - correction a versionner sur un RI deja clos ") // -cr 643477A 643477B
CGMVersionMacroDefine(3227,Disconnect_IterativeRewrite                                 ,zfc ,05-12-2008 ,"V5R19 SP3 - Stack overflow sous memory check ")
//CGMVersionMacroDefine(3228,AutoDraft_ContextualHeight                                  ,SOU ,05-12-2008 ,"V5R19 SP3 - Dev R19SP3 ") // debranche le 12-12-08
CGMVersionMacroDefine(3229,WrapSurface_ForceConvergenceBis                             ,dr  ,05-12-2008 ,"V5R19 SP3 ")
CGMVersionMacroDefine(3230,IntSurSur_RetPointEntropyManagement                         ,DAD ,05-12-2008 ,"V5R19 SP3 - ODT CATSpdTestLipRec013 ") // Management of the entropy of the returning point in intersection SurSur ; CGMShapeTests.tst   CGMTest_Intersection_ShellShell_Case6 KO Ã  rÃ©enregistrer en closed config dÃ¨s que j\'ai le numÃ©ro de la variable.
CGMVersionMacroDefine(3231,SmartProject_SetDomain                                      ,RLA ,05-12-2008 ,"V5R19 SP3 - developpement pour Sheet Methal ") // developpement pour Sheet Methal
CGMVersionMacroDefine(3232,Tess_Disc_RemoveUselessPoints                               ,TPG ,12-12-2008 ,"V5R19 SP3 - A0642919 ") // pour auto draft
CGMVersionMacroDefine(3233,AutoFillet_CapSurfaceV2_Rattrape                            ,IZE ,12-12-2008 ,"V5R19 SP3 - Robustesse AutoFillet R19SP3 ")
CGMVersionMacroDefine(3234,Blend_SmoothedCurvature_3                                   ,JSX ,12-12-2008 ,"V5R19 SP3 - Suite : a _2 Traitement pour les coupling ") // Pour Honda
CGMVersionMacroDefine(3235,Parallel_ApproxMaxDeviationCheck                            ,IZE ,12-12-2008 ,"V5R19 SP3 - RI ") // -cr A0640197 B0640197
CGMVersionMacroDefine(3236,ShellExpansion_JoinWiresOnBadMesh                           ,JSX ,12-12-2008 ,"V5R19 SP3 - RI ") // -cr a0639076 c0639076
CGMVersionMacroDefine(3237,IntCrvSur_PCircleCreation_Step1                             ,DAD ,12-12-2008 ,"V5R19 SP3 - RI 0633507 MustFix ") // -cr B0633507
CGMVersionMacroDefine(3238,CGMR19SP3HF1                                                ,RHA ,12-12-2008 ,"V5R19 SP3 ")
CGMVersionMacroDefine(3239,CGMR19SP3HF2                                                ,RHA ,12-12-2008 ,"V5R19 SP3 ")
CGMVersionMacroDefine(3240,CGMR19SP3HF3                                                ,RHA ,12-12-2008 ,"V5R19 SP3 ")
CGMVersionMacroDefine(3241,CGMR19SP3HF4                                                ,RHA ,12-12-2008 ,"V5R19 SP3 ")
CGMVersionMacroDefine(3242,CGMR19SP3HF5                                                ,RHA ,12-12-2008 ,"V5R19 SP3 ")


//=========================================================================================================
// V5R19 SP4
//=========================================================================================================
CGMVersionMacroDefine(3247,OptimizeOneSurfTuning                                       ,dr  ,15-12-2008 ,"V5R19 SP4 ") // -cr 639485
CGMVersionMacroDefine(3248,Fillet_R19SP4                                               ,RR  ,19-12-2008 ,"V5R19 SP4 - Maintenance Fillet SP4 ")
CGMVersionMacroDefine(3249,StylingFilletFixedOrientation                               ,MWE ,19-12-2008 ,"V5R19 SP4 - RI 631807, 636412, 643523 ") // demande CFH
CGMVersionMacroDefine(3250,General_Perfo_SP4                                           ,FDS ,19-12-2008 ,"V5R19 SP4 - Perfo ")
CGMVersionMacroDefine(3251,AutoDraft_R19SP4                                            ,EYL ,19-12-2008 ,"V5R19 SP4 - dev ")
CGMVersionMacroDefine(3252,PositionPtLoop_ShuntMinimize_NicolasRomainCousinHub         ,NLD ,22-12-2008 ,"V5R19 SP4 ")
CGMVersionMacroDefine(3253,Sweep_OptimDistMin_GetEquivalentPoints_NicolasRomainCousinHub,NLD ,22-12-2008 ,"V5R19 SP4 ")
CGMVersionMacroDefine(3254,Thick_SamplesForLongEdges                                   ,ZFC ,22-12-2008 ,"V5R19 SP4 - RI0641134 ") // -cr A0641134 B0641134
CGMVersionMacroDefine(3255,Sweep_DistanceMinCcvCcvSpecialCaseV2                        ,NLD ,22-12-2008 ,"V5R19 SP4 ")
CGMVersionMacroDefine(3256,RollLines_MinimizeWithCATMathFunctionXY                     ,JSX ,22-12-2008 ,"V5R19 SP4 - More reliable Newton ") // -cr a0644934 a0640490
CGMVersionMacroDefine(3257,TopClean_BuildMergeCurveWithIsoParamFirst                   ,RNO ,22-12-2008 ,"V5R19 SP4 - Amelioration Perfo ")
CGMVersionMacroDefine(3258,IntCrvSur_BoxRelimitation                                   ,DAD ,22-12-2008 ,"V5R19 SP4 - RI 0645941 ") // -cr B0645941 C0645941
CGMVersionMacroDefine(3259,Fillet_3VariableCorner                                      ,rr  ,22-12-2008 ,"V5R19 SP4 - dev SWx ")
CGMVersionMacroDefine(3260,DirtyConfig_SetOfPointsND_FindCircle_ClosedCaseStabilization,NLD ,23-12-2008 ,"V5R19 SP4 ")
CGMVersionMacroDefine(3261,Extrapol_ConstantChordalFillet                              ,IEY ,09-01-2009 ,"V5R19 SP4 - New development for extrapolation of Constant Chordal fillet ")
CGMVersionMacroDefine(3262,Extrapol_VariableChordalFillet                              ,IEY ,09-01-2009 ,"V5R19 SP4 - Development for Extrapolation of Variable Chordal Fillet ")
CGMVersionMacroDefine(3263,RemoveFace_RobustnessLevel8                                 ,MNJ ,09-01-2009 ,"V5R19 SP4 - ODT ")
CGMVersionMacroDefine(3264,Extrapol_HoldCurveCircleFillet                              ,IEY ,09-01-2009 ,"V5R19 SP4 - KO Case : CGMTest_SurfacicN1AppFilletShapeShapeShape, Case003 ") // KO Case : CGMTest_SurfacicN1AppFilletShapeShapeShape, Case003
CGMVersionMacroDefine(3265,CanonicalIntegration                                        ,KUB ,09-01-2009 ,"V5R19 SP4 - Dev ")
CGMVersionMacroDefine(3266,Parallel_R19SP4                                             ,IZE ,09-01-2009 ,"V5R19 SP4 - RIs ")
CGMVersionMacroDefine(3267,Thick_DiscoCallBack3DLevel1                                 ,ZFC ,09-01-2009 ,"V5R19 SP4 - RI 648016 ") // -cr A0648016 B0648016
CGMVersionMacroDefine(3268,Sweep_EquivalentPointRefinement                             ,NLD ,16-01-2009 ,"V5R19 SP4 ")
CGMVersionMacroDefine(3269,Thick_MixedSolutionInXPcPc                                  ,MNJ ,16-01-2009 ,"V5R19 SP4 - RI MNT ") // promote -cr A0648492 B0648492
CGMVersionMacroDefine(3270,Fill_NewManagementBigSlopes2                                ,MPS ,16-01-2009 ,"V5R19 SP4 - A0647961 ") // -cr A0647961
CGMVersionMacroDefine(3271,ControlInfinuteExtrapolation                                ,dr  ,16-01-2009 ,"V5R19 SP4 - ri ")
CGMVersionMacroDefine(3272,Thick_TolerantComputeSurParam                               ,ZFC ,16-01-2009 ,"V5R19 SP4 - RI 0648144 ") // -cr A0648144 B0648144
CGMVersionMacroDefine(3273,CheckCurve_OptimPLine                                       ,NLD ,23-01-2009 ,"V5R19 SP4 ")
CGMVersionMacroDefine(3274,InclPtCrv_ClosureTreatment                                  ,DAD ,23-01-2009 ,"V5R19 SP4 - Closure treatment on circle in inclusion PtCrv ")
CGMVersionMacroDefine(3275,CornerFace_CirclePerfo                                      ,JHN ,23-01-2009 ,"V5R19 SP4 - RI ") // -cr 648417A 648417B
CGMVersionMacroDefine(3276,Fillet_DuplicateWithUpdateTouched2                          ,JHN ,23-01-2009 ,"V5R19 SP4 - RI ") // -cr 649709B 649709C
CGMVersionMacroDefine(3277,Disconnect_InternalErrorFiltering                           ,ZFC ,23-01-2009 ,"V5R19 SP4 - RI 0646148 ") // -cr B0646148 C0646148
CGMVersionMacroDefine(3278,Assemble_TestMergeVertices                                  ,OID ,23-01-2009 ,"V5R19 SP4 - RI 644872 A et B ")
CGMVersionMacroDefine(3279,ThinSolid_OnCircle                                          ,JHN ,23-01-2009 ,"V5R19 SP4 - Ri ") // -cr 644278B 644278C
CGMVersionMacroDefine(3280,HLR_AdiosShrinkFactorOnNullDot                              ,DPS ,23-01-2009 ,"V5R19 SP4 - RI REG souffrant de silhouettes parasites sur canoniques cause ShrinkFactor ") // -cr A0649460 B0649460
CGMVersionMacroDefine(3281,ConfusionPtOnCrvPtOnCrvMassV3                               ,NLD ,30-01-2009 ,"V5R19 SP4 - Perfos ")
CGMVersionMacroDefine(3282,Boolean_EdgeDegeneration                                    ,JHN ,30-01-2009 ,"V5R19 SP4 - RI ") // -cr 642763A 642763B
CGMVersionMacroDefine(3283,LayDownMarch_MaxArcsLimit                                   ,DAD ,30-01-2009 ,"V5R19 SP4 - IR 0649651 ") // -cr A0649651 B0649651
CGMVersionMacroDefine(3284,MatchCrvOptionBasicOrNot                                    ,MWE ,30-01-2009 ,"V5R19 SP4 - RI 627486 ")
CGMVersionMacroDefine(3285,MassPropertiesOptimizeIntegrationDirection                  ,ZIB ,30-01-2009 ,"V5R19 SP4 - RI ") // -cr A0641406  C0641406 A0644192 B0644192 C0644192
//CGMVersionMacroDefine(3286,Boolean_PositionPrism                                       ,WQO ,30-01-2009 ,"V5R19 SP4 - Convergence Boolean_Perfo et Tolerant Modeling dans le Prism ")
//CGMVersionMacroDefine(3287,Boolean_CheckReportSelection                                ,WQO ,30-01-2009 ,"V5R19 SP4 - Correction de lacunes dans les orientations d\'intersection pour la sélection (Trim, ...) ")
//CGMVersionMacroDefine(3288,Boolean_Perfo                                               ,WQO ,30-01-2009 ,"V5R19 SP4 - Amélioration perfos booléen ") // 2 ODTs KO en phase 1 et 2 en phase 2 (mais pas de config fermé)
CGMVersionMacroDefine(3289,ConfusionPropagationCrvCrv_PropagateConfigInCreate          ,NLD ,06-02-2009 ,"V5R19 SP4 ")
CGMVersionMacroDefine(3290,Sweep_DeploySoftwareConfigurationV8                         ,NLD ,06-02-2009 ,"V5R19 SP4 ")
CGMVersionMacroDefine(3291,Unfold_LocalHealing                                         ,REN ,06-02-2009 ,"V5R19 SP4 - RI 626220 ")
CGMVersionMacroDefine(3292,Unfold_P2SCornerPtFilterOff                                 ,REN ,06-02-2009 ,"V5R19 SP4 - RI 575700, 590863 ")
CGMVersionMacroDefine(3293,HLR_NurbsCurvatureAnalysisTrigger                           ,DPS ,06-02-2009 ,"V5R19 SP4 - etude de courbure en complement des normales pour un meilleur echantilonnage ") // A0650941 B0650941 A0649378 B0649378
CGMVersionMacroDefine(3294,TopoFilletApproxJoiningTolerance                            ,MWE ,06-02-2009 ,"V5R19 SP4 - Dev ")
CGMVersionMacroDefine(3295,Thick_InfiniteFlagFilter                                    ,ZUT ,06-02-2009 ,"V5R19 SP4 - Convergence de developpement ")
CGMVersionMacroDefine(3296,Fill_CleanBeforePowerfill                                   ,MPS ,13-02-2009 ,"V5R19 SP4 - RI 650943 ") // -cr A650943
CGMVersionMacroDefine(3297,GetSurfaceValidMaxBoxWithConfig                             ,OBH ,13-02-2009 ,"V5R19 SP4 - RI A0536050 corrige par ailleurs. mais deploiement config necessaire. NLD090209 ")
CGMVersionMacroDefine(3298,Projection_CreateProjectionWithConfig                       ,OAU ,13-02-2009 ,"V5R19 SP4 - Activation NLD pour deploiement config aux solvers ")
CGMVersionMacroDefine(3299,Thick_DirectionalSurfaceStabilization                       ,ZFC ,20-02-2009 ,"V5R19 SP4 - RI 0650380 ") // -cr A0650380 B0650380
CGMVersionMacroDefine(3300,PtSurCan_ProjPtCone_Closure                                 ,KUU ,20-02-2009 ,"V5R19 SP4 - Dev ")
CGMVersionMacroDefine(3301,Bump_Level8                                                 ,PMG ,20-02-2009 ,"V5R19 SP4 - RI A0652431  Apply + precis a proximite du point centre. ") // -cr A0652431 B0652431
CGMVersionMacroDefine(3302,OldLatticeIntegral_FixRelativeErrorComparisons              ,ZIB ,20-02-2009 ,"V5R19 SP4 - Dev ") // Fixes code comparing relative and absolute errors/tolerances.
CGMVersionMacroDefine(3303,Healing_Level29                                             ,JJC ,20-02-2009 ,"V5R19 SP4 - RI652753 ") // -cr A0652753 B0652753
CGMVersionMacroDefine(3304,VariousNLD_DeployConfigR19SP4                               ,NLD ,20-02-2009 ,"V5R19 SP4 ")
CGMVersionMacroDefine(3305,Join_InvertedLimits_RI647718                                ,OID ,20-02-2009 ,"V5R19 SP4 - RI 647718 ") // -cr A647718 B647718
CGMVersionMacroDefine(3306,Sweep_NormalDerivativeV5                                    ,NLD ,20-02-2008 ,"V5R19 SP4 ") // -cr 652323a 652323b
CGMVersionMacroDefine(3307,ILoveCharron                                                ,RNO ,27-02-2009 ,"V5R19 SP4 - NLD squat de la variable RNO pour une bonne regle de 3 dans l\'extrapolation ") // -cr 654052a 654052b
CGMVersionMacroDefine(3308,MinimizeX_DebugV1                                           ,NLD ,27-02-2009 ,"V5R19 SP4 ")
CGMVersionMacroDefine(3309,SolveX_EpsRootManagement                                    ,NLD ,27-02-2009 ,"V5R19 SP4 ")
CGMVersionMacroDefine(3310,SolveX_FastExit                                             ,NLD ,27-02-2009 ,"V5R19 SP4 ")
CGMVersionMacroDefine(3311,MinimizeX_PreliminaryRMinimizeV2                            ,NLD ,27-02-2009 ,"V5R19 SP4 ")
CGMVersionMacroDefine(3312,Fillet_DelayUnTwist                                         ,RR  ,27-02-2009 ,"V5R19 SP4 - Perfos ")
CGMVersionMacroDefine(3313,CATOffsetSurface_CloneAndMove3D                             ,PFV ,27-02-2009 ,"V5R19 SP4 - RI0649343 ")
CGMVersionMacroDefine(3314,HLR_ContactManagementMiniedgeStability                      ,DPS ,27-02-2009 ,"V5R19 SP4 - Decoupe des Miniedges au point de contact sans destabiliser la recherche d\'intersection ") // -cr A0648375 B0648375
CGMVersionMacroDefine(3315,Parallel_OtherFacesInitFix                                  ,REN ,06-03-2009 ,"V5R19 SP4 - RI 653164 ")
CGMVersionMacroDefine(3316,ProjCrvSur_BorderInitTreatment                              ,DAD ,06-03-2009 ,"V5R19 SP4 - Boeing ")
CGMVersionMacroDefine(3317,SmartProject_Complete                                       ,RLA ,06-03-2009 ,"V5R19 SP4 - trouver des solutions plus larges  si possible ") // prereq ProjCrvSur_BorderInitTreatment
CGMVersionMacroDefine(3318,Boolean_FlattenExtend                                       ,JHN ,06-03-2009 ,"V5R19 SP4 - dev amelioration perfo booleen ") // correction generation bodies invalides
CGMVersionMacroDefine(3319,Boolean_PropagDegenerateVertex                              ,JHN ,06-03-2009 ,"V5R19 SP4 - correction pb activation performance du booleen ") // Dev
CGMVersionMacroDefine(3320,Boolean_PositionPrism                                       ,WQO ,06-03-2009 ,"V5R19 SP4 - Convergence Boolean_Perfo et Tolerant Modeling dans le Prism ") // debranche le 04-02-2009
CGMVersionMacroDefine(3321,Boolean_CheckReportSelection                                ,WQO ,06-03-2009 ,"V5R19 SP4 - Correction de lacunes dans les orientations d\\\'intersection pour la sélection (Trim, ...) ") // debranche le 04-02-2009
CGMVersionMacroDefine(3322,Boolean_Perfo                                               ,WQO ,06-03-2009 ,"V5R19 SP4 - Amélioration perfos booléen ") // 2 ODTs KO en phase 1 et 2 en phase 2 (mais pas de config fermé) // debranche le 04-02-2009
CGMVersionMacroDefine(3323,Boolean_SecureSigns                                         ,WQO ,06-03-2009 ,"V5R19 SP4 - RI0650794 ") // Trim_ShellShell_Case8   KO, rc = 1 livré 06/03/09
CGMVersionMacroDefine(3324,ProjCrvSur_SameCrvInMergeAdm                                ,DAD ,13-03-2009 ,"V5R19 SP4 - code review ")
CGMVersionMacroDefine(3325,Intersection_CuttingPoint                                   ,JHN ,13-03-2009 ,"V5R19 SP4 - RI 649193 ") // -cr 649193A 649193B
CGMVersionMacroDefine(3326,AutoDraft_ContextualHeight                                  ,SOU ,13-03-2009 ,"V5R19 SP4 - Dev R19SP4 ") // debranche le 12-12-08
CGMVersionMacroDefine(3327,Sweep_CircleExtrapolationOnClosure                          ,NLD ,20-03-2009 ,"V5R19 SP4 ") // -cr 651099a 651099b
//CGMVersionMacroDefine(3328,FuncInitProjIsop_NormalEval                                 ,DAD ,20-03-2009 ,"V5R19 SP4 - Bug dans eval deriv de CATFunctionInitProjIsopar ")
CGMVersionMacroDefine(3329,ProjCrvSur_GeomCorrectTangent                               ,DAD ,20-03-2009 ,"V5R19 SP4 - IR 0654050 ") // -cr A0654050 B0654050
CGMVersionMacroDefine(3330,PtSurCan_ProjPtTore_Resolution                              ,KUU ,20-03-2009 ,"V5R19 SP4 - Dev ")
CGMVersionMacroDefine(3331,Fill_FillAnalytique_NormalMode                              ,MPS ,20-03-2009 ,"V5R19 SP4 - RI  649725 ") // -cr A0649725
CGMVersionMacroDefine(3332,RemoveFace_RobustnessLevel9                                 ,LAP ,20-03-2009 ,"V5R19 SP4 - RI 656004 ") // -cr A0656004 B0656004
CGMVersionMacroDefine(3333,Sewing_SuiviEdge                                            ,JHN ,20-03-2009 ,"V5R19 SP4 - Sheet metal ")
CGMVersionMacroDefine(3334,CGMR19SP4HF1                                                ,RHA ,25-03-2009 ,"V5R19 SP4 ")
CGMVersionMacroDefine(3335,CGMR19SP4HF2                                                ,RHA ,25-03-2009 ,"V5R19 SP4 ")
CGMVersionMacroDefine(3336,CGMR19SP4HF3                                                ,RHA ,25-03-2009 ,"V5R19 SP4 ")
CGMVersionMacroDefine(3337,CGMR19SP4HF4                                                ,RHA ,25-03-2009 ,"V5R19 SP4 ")
CGMVersionMacroDefine(3338,CGMR19SP4HF5                                                ,RHA ,25-03-2009 ,"V5R19 SP4 ")


//=========================================================================================================
// V5R19 SP5
//=========================================================================================================
CGMVersionMacroDefine(3340,Fillet_R19SP5                                               ,RR  ,27-03-2009 ,"V5R19 SP5 - Fillet Various R19SP5 fixes ")
CGMVersionMacroDefine(3341,Fillet_G1Healing                                            ,SOU ,27-03-2009 ,"V5R19 SP5 - RI fix for R19SP5 ") // -cr A0657181  B0657181
CGMVersionMacroDefine(3342,Boolean_HomogenizeInCoupling                                ,JHN ,27-03-2009 ,"V5R19 SP5 - RI 653246 ") // -cr 653246A 653246B
CGMVersionMacroDefine(3343,IntersectionSurSurTg_MicroSharpZone                         ,RR  ,27-03-2009 ,"V5R19 SP5 - RI ")
CGMVersionMacroDefine(3344,UnfoldFrF_RemoveBadTrianglesFix                             ,REN ,27-03-2009 ,"V5R19 SP5 - IR 656788 ")
CGMVersionMacroDefine(3345,MarshMallow_LocalTol_Apply                                  ,PMG ,03-04-2009 ,"V5R19 SP5 - RI : Tolerance non tenue le long des courbes ") // -cr A0657648 B0657648
CGMVersionMacroDefine(3346,DistanceMin_NewArchitecture                                 ,RHA ,03-04-2009 ,"V5R19 SP5 - MacCab ")
CGMVersionMacroDefine(3347,Boolean_OutForMultiConfused                                 ,JHN ,03-04-2009 ,"V5R19 SP5 - RI RHA ") // -cr 655821A
CGMVersionMacroDefine(3348,Projection_CoveredFacesMultiShell                           ,JHN ,03-04-2009 ,"V5R19 SP5 - RI ") // -cr 649049A 647656A 647656B 647434A 647434B
CGMVersionMacroDefine(3349,Loft_SmoothedProfileComb2                                   ,JSX ,10-04-2009 ,"V5R19 SP5 - Activation du smooth apres le clean des combs ") // -cr a0652832
CGMVersionMacroDefine(3350,SurfaceToCanonic_XScaleR19SP5                               ,NLD ,10-04-2009 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3351,General_Perfo_SP5                                           ,FDS ,10-04-2009 ,"V5R19 SP5 - Perfo R19SP5 ")
CGMVersionMacroDefine(3352,TrimByThick_JournalFixForDirectionalSurfaces                ,ZFC ,17-04-2009 ,"V5R19 SP5 - ODT Appli Sheetmetal CATSHMCutOut19 (CATSmModel.tst) ")
CGMVersionMacroDefine(3353,Thick_HealingGeoPostProLevel14                              ,ZFC ,17-04-2009 ,"V5R19 SP5 - RI 0659995 ") // -cr A0659995 B0659995
CGMVersionMacroDefine(3354,RemoveFace_RecordExtrapolLengthStabilization                ,ZUT ,17-04-2009 ,"V5R19 SP5 - RI ") // -cr A0656288
CGMVersionMacroDefine(3355,LayD_StepFromPole                                           ,DAD ,17-04-2009 ,"V5R19 SP5 - Pole treatment in laydown; PMR 51260 695 760; IR0659137 ") // -cr A0659137 B0659137 ; 4 ODTs KO: changement de ref à faire à DSP
CGMVersionMacroDefine(3356,GeodesicParallel_CompositesDevs                             ,IZE ,17-04-2009 ,"V5R19 SP5 - RI + Dev ")
CGMVersionMacroDefine(3357,IntSurSur_CleanPointInCurve                                 ,DAD ,24-04-2009 ,"V5R19 SP5 - RI 0633892 ") // -cr B0633892 ; 30 ODTs à relivrer en closed config (changement de ref) dès la définition du numéro
CGMVersionMacroDefine(3358,Sweep_HomogenizationWithShiftOnStickingClosure              ,NLD ,24-04-2009 ,"V5R19 SP5 ") // -cr 660302a 660302b
CGMVersionMacroDefine(3359,Draft_TrueMultiRib_TentProblems                             ,SOU ,24-04-2009 ,"V5R19 SP5 - RI ") // -cr A0645276  for R19SP5
CGMVersionMacroDefine(3360,Sweep_WeakMappingOptimByCCV                                 ,NLD ,24-04-2009 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3361,ConfusionPtOnCrvPtOnCrvMassV4                               ,NLD ,24-04-2009 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3362,Sweep_XScaleR19SP5                                          ,NLD ,24-04-2009 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3363,OrientationVolume_PointOnBoundary                           ,JHN ,24-04-2009 ,"V5R19 SP5 - RI ") // -cr 651288A 651288B
CGMVersionMacroDefine(3364,NewFastIntCrvCrv                                            ,DAD ,30-04-2009 ,"V5R19 SP5 - RI 0648648 ") // -cr A0648648 B0648648 C0648648
//CGMVersionMacroDefine(3365,GMODEL_VertexIterator_FaceMultipleShells                    ,TCX ,30-04-2009 ,"V5R19 SP5 - Correction Iterator ") // REGKillerTopologicalModel.tst   VertexIterator.sh
CGMVersionMacroDefine(3366,CleanCurve_CCVCleaner_StabiliteRebroussement                ,RNO ,30-04-2009 ,"V5R19 SP5 - Stabilisation lors de petites perturbation numerique (type FIXPARTWARN) pour les sommets avec un quasi rebroussement ") // RICleanCurve_3
CGMVersionMacroDefine(3367,HybridVarOffset_BiOffsetFaceJournal                         ,LAP ,30-04-2009 ,"V5R19 SP5 - Dev Composite ")
CGMVersionMacroDefine(3368,IntSurSur_RelativeSize                                      ,DAD ,07-05-2009 ,"V5R19 SP5 - RI 0661579 ; computation of relative sizes of the two surfaces compared to the intersection ") // -cr A0661579 B0661579 C0661579 D0661579
CGMVersionMacroDefine(3369,Boolean_IntersectionsOnCommonConfused                       ,ld2 ,07-05-2009 ,"V5R19 SP5 - RI MF ") // -cr 659106A 659106B
CGMVersionMacroDefine(3370,Projection_TransitiveContainer                              ,JHN ,07-05-2009 ,"V5R19 SP5 - Airbus Composite ") // pas de -cr pour l\'instant
CGMVersionMacroDefine(3371,CGMR207HF1                                                  ,RHA ,07-05-2008 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3372,CGMR207HF2                                                  ,RHA ,07-05-2008 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3373,CGMR207HF3                                                  ,RHA ,07-05-2008 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3374,CGMR207HF4                                                  ,RHA ,07-05-2008 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3375,CGMR207HF5                                                  ,RHA ,07-05-2008 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3376,CGMR207HF6                                                  ,RHA ,07-05-2008 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3377,CGMR207HF7                                                  ,RHA ,07-05-2008 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3378,CGMR207HF8                                                  ,RHA ,07-05-2008 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3379,CGMR207HF9                                                  ,RHA ,07-05-2008 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3380,CGMR207HF10                                                 ,RHA ,07-05-2008 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3381,ComputeUVTolerance_Cylinder_MaxTol                          ,KUU ,15-05-2009 ,"V5R19 SP5 - RI 0572016 ")
CGMVersionMacroDefine(3382,Fillet_Parting_3DCorner                                     ,RR  ,15-05-2009 ,"V5R19 SP5 - RI MNT ")
CGMVersionMacroDefine(3383,LayDown_CoveredFacesMultiShell                              ,JHN ,15-02-2009 ,"V5R19 SP5 - Ri interne sheet metal ") // -cr 660742A 660742B
CGMVersionMacroDefine(3384,Sweep_PseudoOrthoFunctionXDerivativeV2                      ,NLD ,29-05-2009 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3385,DraftBothSides_ExtandSurLimits                              ,PFV ,29-05-2009 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3387,Thick_RazorBladeDiagLevel2                                  ,ZUT ,29-05-2009 ,"V5R19 SP5 - RI ") // -cr A0660842 B0660842
CGMVersionMacroDefine(3388,Extrapol_ShellG1_CheckIdenticalPlane                        ,JSX ,05-06-2009 ,"V5R19 SP5 - bug detecté sur model SW ")
CGMVersionMacroDefine(3389,Thick_HealingGeoPostProLevel15                              ,ZFC ,05-06-2009 ,"V5R19 SP5 - RI 0662110 ") // -cr A0662110 B0662110 C0662110 D0662110
CGMVersionMacroDefine(3390,Sweep_ExtractComb_BugIndexOfC0Vertex                        ,JSX ,05-06-2009 ,"V5R19 SP5 - revue de code ")
CGMVersionMacroDefine(3391,SysPCrvPCrv_OptimFindSingularPoints                         ,NLD ,05-06-2009 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3392,Sewing_JournalShellShell                                    ,LD2 ,05-06-2009 ,"V5R19 SP5 - Bug SW ") // Bug SW
CGMVersionMacroDefine(3393,Projection_ImpasseParTransition                             ,JHN ,05-06-2009 ,"V5R19 SP5 - ODTs KOs FIXPARTBOEING ") // FIXPARTBOEING : pas de RI
CGMVersionMacroDefine(3394,GMODEL_VertexIterator_FaceMultipleShells                    ,TCX ,05-06-2009 ,"V5R19 SP5 - Convergence operee dans le delivery CGMOFF/CGMPRJ du Vendredi 5 Juin 2009 ") // REGKillerTopologicalModel.tst   VertexIterator.sh
CGMVersionMacroDefine(3396,ConvertSurToNurbs_AllowExactSubdivConversion                ,RNO ,12-06-2009 ,"V5R19 SP5 - Activation de la conversion Exacte des subdivisions surface dans le surfitting ")
CGMVersionMacroDefine(3397,Extrapol_ShellG1_G1Spine                                    ,JSX ,12-06-2009 ,"V5R19 SP5 - Used tolerance to build G2 spine leads to an unnecessary deformation ") // ri  -cr  A0658153  B0658153
CGMVersionMacroDefine(3398,Thick_CleanNewerUnusedIfOpeFailed                           ,ZUT ,12-06-2009 ,"V5R19 SP5 - RI ") // RI -cr A0663680 B0663680 C0663680
CGMVersionMacroDefine(3399,Close_OrientShell                                           ,LD2 ,12-06-2009 ,"V5R19 SP5 - Changement de l algorithme pour orienter les shells du CATCloseOperator ")
CGMVersionMacroDefine(3400,ProjCrvSur_HandleNurbsPole                                  ,DAD ,19-06-2009 ,"V5R19 SP5 - IR 650625 ") // -cr A650625 B650625
CGMVersionMacroDefine(3401,Sweep_Interpol_ContinuousBehaviourV3                        ,NLD ,19-06-2009 ,"V5R19 SP5 - stabilisation XScale  et differents OS ")
CGMVersionMacroDefine(3402,TrimByThick_UnforceTouchedAttribForX2S                      ,ZFC ,19-06-2009 ,"V5R19 SP5 - RI 0654667 ") // -cr A0654667 B0654667
CGMVersionMacroDefine(3403,CurveExtrapol_TolerantNewMaxGap                             ,ZFC ,19-06-2009 ,"V5R19 SP5 - RI MUSTFIX 0664229 ") // -cr A0664229 B0664229 C0664229
CGMVersionMacroDefine(3404,Sweep_MVDKeepIsotopoWithMultipleOccurences                  ,NLD ,19-06-2009 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3405,Fillet_WideLocalSelection                                   ,RR  ,19-06-2009 ,"V5R19 SP5 - Performances improvement ")
CGMVersionMacroDefine(3406,UnfoldFrF_ReRunFix                                          ,FSQ ,19-06-2009 ,"V5R19 SP5 - RI ") // -cr A0665487 B0665487 C0665487
CGMVersionMacroDefine(3407,Sweep_TwistFunctionXUniqueEval                              ,NLD ,19-06-2009 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3408,Thick_MergeVerticeFromReconvergence                         ,LAP ,19-06-2009 ,"V5R19 SP5 - RI655262 ") // -cr A0655262 B0655262
CGMVersionMacroDefine(3409,Boolean_IEcutByIV_RI658583                                  ,WQO ,19-06-2009 ,"V5R19 SP5 - Correction partielle RI658583 ")
//CGMVersionMacroDefine(3410,OrientationVolume_PointOnBoundary2                          ,JHN ,19-06-2006 ,"V5R19 SP5 - perfo ") // attente validation TXO
CGMVersionMacroDefine(3411,Offset_SurfCompatibilityFilterLevel4                        ,ZUT ,19-06-2009 ,"V5R19 SP5 - RI ") // -cr A0652228 B0652228
CGMVersionMacroDefine(3412,Loft_ExactInvTransfoForFrame3Mode                           ,JSX ,26-06-2009 ,"V5R19 SP5 - Tang Directon X must be in MvFr Plane ") // -cr a0667612 B0667612
//CGMVersionMacroDefine(3413,Boolean_OBBFiltering                                        ,ZIB ,26-06-2009 ,"V5R19 SP5 - enable OBB filtering in Face/Face intersection code ") // debranche le 010609, le 300609
CGMVersionMacroDefine(3414,Offset_CheckIVRepForTptDoublet                              ,MNJ ,26-06-2009 ,"V5R19 SP5 - RI ") // activation immédiate le 26-06-2009
CGMVersionMacroDefine(3415,Fillet_UnTwistNewParabola                                   ,RR  ,26-06-2009 ,"V5R19 SP5 - Maintenance ")
CGMVersionMacroDefine(3416,ExtrapolOfSubdivSurface                                     ,RNO ,26-06-2009 ,"V5R19 SP5 - Declenche l\'autorisation de l\'extrapolation des SubdivGridSurface ")
CGMVersionMacroDefine(3417,Marching_VerySlowEvolution                                  ,KJD ,26-06-2009 ,"V5R19 SP5 - RI ") // -cr A0663318 B0663318
CGMVersionMacroDefine(3418,RemoveFace2D_AdjustTrustLevel1                              ,ZUT ,03-06-2009 ,"V5R19 SP5 - RI ") // -cr A0666573
CGMVersionMacroDefine(3419,CGMR19SP5HF1                                                ,RHA ,03-06-2009 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3420,CGMR19SP5HF2                                                ,RHA ,03-06-2009 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3421,CGMR19SP5HF3                                                ,RHA ,03-06-2009 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3422,CGMR19SP5HF4                                                ,RHA ,03-06-2009 ,"V5R19 SP5 ")
CGMVersionMacroDefine(3423,CGMR19SP5HF5                                                ,RHA ,03-06-2009 ,"V5R19 SP5 ")


//=========================================================================================================
// V5R19 SP6
//=========================================================================================================
CGMVersionMacroDefine(3434,Offset_OptimizedCutIntoManifoldsAtSimplif                   ,MNJ ,09-07-2009 ,"V5R19 SP6 - RI perfos ")
CGMVersionMacroDefine(3435,Boolean_MissingWithContinuity                               ,JHN ,09-07-2009 ,"V5R19 SP6 - RI ") // -cr 66036A 660364B
//CGMVersionMacroDefine(3436,BooleanFace_CommonEdge                                      ,JHN ,09-07-2009 ,"V5R19 SP6 - Pb Swx ") // booleen face/face avec contact sur une edge entre faces
CGMVersionMacroDefine(3437,PosVsSurfBorder_CheckPNurbs                                 ,ZUT ,09-07-2009 ,"V5R19 SP6 - RI ") // -cr A0667849
CGMVersionMacroDefine(3438,Thick_DetectRazorBladeEdgeFromReverseEdge                   ,LAP ,09-07-2009 ,"V5R19 SP6 - RI B0657064 ") // -cr B0657064
CGMVersionMacroDefine(3439,Completed_Journal                                           ,RLA ,09-07-2009 ,"V5R19 SP6 - evolution SW ") // journal complet dans les operateurs booleans
CGMVersionMacroDefine(3440,LawEquationDistPCrvPCrv_DomainTol                           ,PKC ,10-07-2009 ,"V5R19 SP6 - RI ")
CGMVersionMacroDefine(3441,Sweep_NoForcedCloningForClosedProfile                       ,NLD ,10-07-2009 ,"V5R19 SP6 - Surfaces sharing management. SolidWorks ")
CGMVersionMacroDefine(3442,CrossAndSignServ_NormalCompute                              ,DAD ,17-07-2009 ,"V5R19 SP6 - Dev service Crossing and Signature ")
CGMVersionMacroDefine(3443,Fillet_R19SP6                                               ,cwm ,17-07-2009 ,"V5R19 SP6 ")
CGMVersionMacroDefine(3444,Fillet_WithKeepEdge_JournalCorrection                       ,cwm ,17-07-2009 ,"V5R19 SP6 ")
CGMVersionMacroDefine(3445,Offset_OptionalSharpPtsDeactivationLevel2                   ,MNJ ,17-07-2009 ,"V5R19 SP6 - RI Daimler ") // promote -cr A0668475 B0668475 C0668475
CGMVersionMacroDefine(3446,Marching_StabilizeQuadraticForm                             ,NLD ,17-07-2009 ,"V5R19 SP6 - stabilisation XScale  et differents OS ")
CGMVersionMacroDefine(3447,Sweep_XScaleR19SP6                                          ,NLD ,17-07-2009 ,"V5R19 SP6 ")
//CGMVersionMacroDefine(3448,JournalsDynBool_DeleteWrong                                 ,LD2 ,17-07-2009 ,"V5R19 SP6 - RI ") // -cr 669582 // desactive le 21/07
CGMVersionMacroDefine(3449,RSO_MultiThread                                             ,PMG ,24-07-2009 ,"V5R19 SP6 - Stabilise le code avec ou sans MultiThreading ") // Demande d\'activation par KTU pour le compte de PMG
CGMVersionMacroDefine(3450,Marching_ParamDistortion                                    ,KJD ,24-07-2009 ,"V5R19 SP6 - RI ") // -cr A0664293 B0664293 C0664293
CGMVersionMacroDefine(3451,ThinSolidWire_RelimitEdges_VerticesEquality                 ,LD2 ,24-07-2009 ,"V5R19 SP6 - RI ") // -cr A0664773 B0664773 C0664773
CGMVersionMacroDefine(3452,HLR_StrictOcclusionTolerance                                ,DPS ,24-07-2009 ,"V5R19 SP6 - SWATCH ")
CGMVersionMacroDefine(3453,DistanceBodyBody_CanonicalInitTolCheckCorrection            ,MPX ,31-07-2009 ,"V5R19 SP6 - RI ") // -cr  A0670320  B0670320
CGMVersionMacroDefine(3454,DistPtRevolBooster                                          ,NLD ,31-07-2009 ,"V5R19 SP6 - Perfos et fiabilite. correction derivee seconde ")
CGMVersionMacroDefine(3455,Sweep_DistanceMinCcvCcvDebugBoxes                           ,NLD ,31-07-2009 ,"V5R19 SP6 ")
CGMVersionMacroDefine(3456,Connector_SimpleSolve_PropagateNoThrow                      ,LD2 ,31-07-2009 ,"V5R19 SP6 - RI ") // -cr A0666968 B0666968
CGMVersionMacroDefine(3457,Offset_SameEdgeCurveDetectionForTpts                        ,ZFC ,31-07-2009 ,"V5R19 SP6 - RI 0665585 ") // -cr A0665585 B0665585
CGMVersionMacroDefine(3458,Regul_SplitLargeFaces                                       ,cwm ,31-07-2009 ,"V5R19 SP6 ") // dev SW
CGMVersionMacroDefine(3459,JournalsDynBool_DeleteWrong                                 ,LD2 ,31-07-2009 ,"V5R19 SP6 - RI ") // -cr 669582
CGMVersionMacroDefine(3460,ProjCrvSur_HandleOffsetSurface                              ,DAD ,07-08-2009 ,"V5R19 SP6 - Perfo ProjectionCrvSur ")
CGMVersionMacroDefine(3461,ProjCrvSur_RemoveInNullTreat                                ,DAD ,07-08-2009 ,"V5R19 SP6 - Problem in NullTreatment when removing points ")
CGMVersionMacroDefine(3462,BooleanFace_CommonEdge                                      ,JHN ,21-08-2009 ,"V5R19 SP6 - Pb Swx ") // booleen face/face avec contact sur une edge entre faces
CGMVersionMacroDefine(3463,DistanceBodyBody_RefPointCorrection                         ,MPX ,21-08-2009 ,"V5R19 SP6 - RI ") // -cr A0671804WIM B0671804WIM
CGMVersionMacroDefine(3464,Offset_NoInterGeomDiagAroundSingleVRepImage                 ,MNJ ,21-08-2009 ,"V5R19 SP6 - RI ") // -cr B0661087 A0640710 C0640710 D0640710
CGMVersionMacroDefine(3465,OffsetMultiConst_SuperEdgesOnBorder                         ,MNJ ,21-08-2009 ,"V5R19 SP6 - modele composites ") // promote -cr A0668531 B0668531 C0668531
CGMVersionMacroDefine(3466,RelimitSkin_EmptyResult_UntouchTrimmingShells               ,LD2 ,21-08-2009 ,"V5R19 SP6 - RI ") // -cr A0672229 B0672229 C0672229
CGMVersionMacroDefine(3467,Offset_ImproveOffsetDiagnosis                               ,ZUT ,21-08-2009 ,"V5R19 SP6 - RI ") // -cr A0669129 B0669129 C0669129
CGMVersionMacroDefine(3468,Join_InvertedLimits_RI665592                                ,OID ,28-08-2009 ,"V5R19 SP6 - RI665592 A, RI665592 B, RI665592 C ") // -cr A665592 B665592 C665592
CGMVersionMacroDefine(3469,CXLoop_Flatten_CleanTwin                                    ,LD2 ,28-08-2009 ,"V5R19 SP6 - RI ") // -cr IR-008796V5R19 IR-008796V5R20 IR-008796V6R2010x IR-008796V6R2011
CGMVersionMacroDefine(3470,Apply_ImproveCutSens                                        ,PMG ,28-08-2009 ,"V5R19 SP6 - Pb de qualite d\'aprox ") // -cr IR-011793V5R19WIM  IR-011793V5R20WIM IR-011793V6R2010xWIM  IR-011793V6R2011WIM
CGMVersionMacroDefine(3471,ProjCrvSur_HandleOffsetSurface2                             ,DAD ,04-09-2009 ,"V5R19 SP6 - Management of the offset in several directions and several depths ")
//CGMVersionMacroDefine(3472,IntersectionPCrvPCrv_SameTag                                ,DAD ,04-09-2009 ,"V5R19 SP6 - Perfo PCrvPCrv; Same Tag treatment ")
CGMVersionMacroDefine(3473,Relimit_MixedSolution                                       ,JHN ,04-09-2009 ,"V5R19 SP6 - RI ") // -cr 668272A 668272B
CGMVersionMacroDefine(3474,Fillet_CrossParting_BetterShapeonConcaveEdge                ,RR  ,04-09-2009 ,"V5R19 SP6 - maintenance Fillet Cross Parting ")
CGMVersionMacroDefine(3475,TopCleanCurve_LocalizerOpti                                 ,RNO ,04-09-2009 ,"V5R19 SP6 - Optimisation des Localizer ") // Optimisation importante des cas 2D michelins sur les supports plans
CGMVersionMacroDefine(3476,ThickSurface_BackUpForReconvergenceFailure                  ,MNJ ,11-09-2009 ,"V5R19 SP6 - RI a venir ")
CGMVersionMacroDefine(3477,MultiVolume_InterTopo_HasIntersection                       ,LD2 ,11-09-2009 ,"V5R19 SP6 - Dev ")
CGMVersionMacroDefine(3478,Fill_FillAnalytiqueBadSurface                               ,MPS ,11-09-2009 ,"V5R19 SP6 - IR 013022 ") // -cr  IR-013022V6R2011WIM    IR-013022V6R2010xWIM    IR-013022V5R20WIM
CGMVersionMacroDefine(3479,Compatible_FindWire                                         ,JHN ,11-09-2009 ,"V5R19 SP6 - RI LAP ") // Compatible ODT CGMReplay_LiveTransformFace13 KO code 66 relivre Vendredi par LAP
CGMVersionMacroDefine(3480,StylingFilletTuneUpSegmentationApprox                       ,MWE ,11-09-2009 ,"V5R19 SP6 - RI666863 ")
CGMVersionMacroDefine(3481,Thick_PerfosLevel12                                         ,MNJ ,11-09-2009 ,"V5R19 SP6 - RI 0669604 ")
CGMVersionMacroDefine(3482,Sweep_FindBestFaceWhenSupportShare                          ,NLD ,18-09-2009 ,"V5R19 SP6 ") // -cr IR-011081V5R20WIM IR-011081V6R2011WIM
CGMVersionMacroDefine(3483,SkinExtrapol_ApproximateERepLevel1                          ,MNJ ,18-09-2009 ,"V5R19 SP6 - pour Airbus ") // activation immediate le 18-11-2009
CGMVersionMacroDefine(3484,Parallel_EndEdgeReportInit                                  ,IZE ,18-09-2009 ,"V5R19 SP6 - RI + Dev ")
CGMVersionMacroDefine(3485,Sweep_Domains_HoleManagementV2                              ,NLD ,25-09-2009 ,"V5R19 SP6 ") // -cr IR-017252V6R2011WIM IR-017252V5R19WIM IR-017252V5R20WIM IR-017252V6R2010xWIM
CGMVersionMacroDefine(3486,CATEdgeCurveSharpnessCut_NoRemoveInLoop                     ,MNJ ,25-09-2009 ,"V5R19 SP6 - RI MNT TMC REG 018302 echec offset 0mm ") // activation immediate le 25-09-2009
//CGMVersionMacroDefine(3487,GetParamFromLength_CutAtSuddenCurvatureChanges              ,zib ,25-09-2009 ,"V5R19 SP6 - Fix for 0653193 ")
CGMVersionMacroDefine(3488,Marsh_WeakConstraint                                        ,PMG ,25-09-2009 ,"V5R19 SP6 - RI ") // -cr IR-018173V5R19WIM  IR-018173V5R20WIM IR-018173V6R2010xWIM  IR-018173V6R2011WIM
CGMVersionMacroDefine(3489,BooleanFace_ConfusedEdge                                    ,JHN ,25-09-2009 ,"V5R19 SP6 - swx ") // operations booleennes de faces
CGMVersionMacroDefine(3490,Fillet_R19SP7                                               ,cwm ,25-09-2009 ,"V5R19 SP6 - RI ")
CGMVersionMacroDefine(3492,CGMR19SP6HF1                                                ,RHA ,25-09-2009 ,"V5R19 SP6 ")
CGMVersionMacroDefine(3493,CGMR19SP6HF2                                                ,RHA ,25-09-2009 ,"V5R19 SP6 ")
CGMVersionMacroDefine(3494,CGMR19SP6HF3                                                ,RHA ,25-09-2009 ,"V5R19 SP6 ")
CGMVersionMacroDefine(3495,CGMR19SP6HF4                                                ,RHA ,25-09-2009 ,"V5R19 SP6 ")
CGMVersionMacroDefine(3496,CGMR19SP6HF5                                                ,RHA ,25-09-2009 ,"V5R19 SP6 ")


//=========================================================================================================
// V5R20 GA
//=========================================================================================================
CGMVersionMacroDefine(3550,Boolean_OBBFiltering                                        ,ZIB ,13-07-2009 ,"V5R20 GA - enable OBB filtering in Face/Face intersection code ") // GA R20
CGMVersionMacroDefine(3551,Boolean_AdjacentPositionOnConfusionBorder                   ,WQO ,11-09-2009 ,"V5R20 GA - Developpement pour positionnement hors specs (pb du T ou Diabolo...) ")
CGMVersionMacroDefine(3552,Fillet_R20GA                                                ,cwm ,02-10-2009 ,"V5R20 GA - RI ") // R20GA
CGMVersionMacroDefine(3553,Healing_Level30                                             ,JJC ,02-10-2009 ,"V5R20 GA - bad initialisation ")
CGMVersionMacroDefine(3554,Apply_AdjustOnSingularity                                   ,JJC ,02-10-2009 ,"V5R20 GA - Robustness for EvalNormal ")
//CGMVersionMacroDefine(3555,MultiVolume_SeparationDisconnectPosition                    ,LD2 ,02-10-2009 ,"V5R20 GA - Dev FastRun ")
CGMVersionMacroDefine(3556,AutoCheck_NoIsoDim                                          ,JHN ,02-10-2009 ,"V5R20 GA - migration Subd ") // passage au nouvel Subd
CGMVersionMacroDefine(3557,SkinExtrapol_AntiClosuresIfNeeded                           ,MNJ ,02-10-2009 ,"V5R20 GA - dev FuzzyExtrapol ")
CGMVersionMacroDefine(3558,Unfold_RelativeDistortionFix                                ,REN ,02-10-2009 ,"V5R20 GA - RI 626281, 628164, 626220 ")
CGMVersionMacroDefine(3559,RemoveFace_RobustnessLevel11                                ,ZUT ,02-10-2009 ,"V5R20 GA - Pb RemoveFace dans LiveShape + RI ") // -cr 015372V6R2011WIM
CGMVersionMacroDefine(3560,Draft_MultiFacesNeutralExtrapolation                        ,PFV ,02-10-2009 ,"V5R20 GA - RI ")
CGMVersionMacroDefine(3561,IntSurSur_TolCompInRetPoint                                 ,DAD ,09-10-2009 ,"V5R20 GA - RI 0661579 ") // -cr IR-018844V5R20WIM IR-018844V6R2010xWIM IR-018844V6R2011WIM ; CGMGeometryTests.tst\\CGMTest_GeometryReplayIntersectionSurSur : rc=1 ==> cas IntSurSur_IR0623629_ReturningPoint à réenregistrer en closed config
CGMVersionMacroDefine(3562,Extrude_RelimitationMode                                    ,fds ,09-10-2009 ,"V5R20 GA - Correction pour functional ")
CGMVersionMacroDefine(3563,Homotopy_CrvSur_StabilizeRunOnPole                          ,LAP ,09-10-2009 ,"V5R20 GA - ODT instable ")
CGMVersionMacroDefine(3564,CGMR208HF1                                                  ,RHA ,09-10-2009 ,"V5R20 GA ")
CGMVersionMacroDefine(3565,CGMR208HF2                                                  ,RHA ,09-10-2009 ,"V5R20 GA ")
CGMVersionMacroDefine(3566,CGMR208HF3                                                  ,RHA ,09-10-2009 ,"V5R20 GA ")
CGMVersionMacroDefine(3567,CGMR208HF4                                                  ,RHA ,09-10-2009 ,"V5R20 GA ")
CGMVersionMacroDefine(3568,CGMR208HF5                                                  ,RHA ,09-10-2009 ,"V5R20 GA ")
CGMVersionMacroDefine(3569,CGMR208HF6                                                  ,RHA ,09-10-2009 ,"V5R20 GA ")
CGMVersionMacroDefine(3570,CGMR208HF7                                                  ,RHA ,09-10-2009 ,"V5R20 GA ")
CGMVersionMacroDefine(3571,CGMR208HF8                                                  ,RHA ,09-10-2009 ,"V5R20 GA ")
CGMVersionMacroDefine(3572,CGMR208HF9                                                  ,RHA ,09-10-2009 ,"V5R20 GA ")
CGMVersionMacroDefine(3573,CGMR208HF10                                                 ,RHA ,09-10-2009 ,"V5R20 GA ")
CGMVersionMacroDefine(3574,Boolean_DisconnectMoveOn                                    ,JHN ,16-10-2009 ,"V5R20 GA - RI activation R20 seulement ") // -cr IR-018479V5R20WIM IR-018479V6R2011WIM ODT KO : CGMTest_Split_ShellWire_Case3
CGMVersionMacroDefine(3575,SkinExtrapol_ApproximateERepLevel4                          ,MNJ ,16-10-2009 ,"V5R20 GA - pour dev Draft ")
CGMVersionMacroDefine(3576,Sweep_PlanarWrapDetection                                   ,NLD ,16-10-2009 ,"V5R20 GA ")


//=========================================================================================================
// V5R20 SP1
//=========================================================================================================
CGMVersionMacroDefine(3577,Draft_MultiFacesNeutralExtrapolation_R20SP1                 ,PFV ,16-10-2009 ,"V5R20 SP1 - RI DCS ")
CGMVersionMacroDefine(3578,Fillet_R20SP1                                               ,cwm ,16-10-2009 ,"V5R20 SP1 - RI ")
CGMVersionMacroDefine(3579,Fillet_ImplicitCrossParting                                 ,RR  ,16-10-2009 ,"V5R20 SP1 - Dev ImplicitCrossParting ")
//CGMVersionMacroDefine(3580,Parallelized_InterTopo                                      ,OID ,16-10-2009 ,"V5R20 SP1 - Parallélisation de l\'intersectTopologie en vue du MultiProcessing ") // KO corrigé par la livraison de demain
CGMVersionMacroDefine(3581,Sweep_MovingFrame_ProjectionPseudoOrthoV2                   ,NLD ,23-10-2009 ,"V5R20 SP1 ")
CGMVersionMacroDefine(3582,Sweep_XScaleR20SP1                                          ,NLD ,23-10-2009 ,"V5R20 SP1 ")
CGMVersionMacroDefine(3583,TrimByThick_InitialFacesFilter                              ,MNJ ,23-10-2009 ,"V5R20 SP1 - ODT KO Rel ") // activation immediate le 23-10-2009
CGMVersionMacroDefine(3584,SystemXY_TopologicalDegree_DegeneratedEdgeTreatment         ,KJD ,30-10-2009 ,"V5R20 SP1 - RI ") // -cr IR-016973V5R20WIM IR-016973V6R2010xWIM IR-016973V6R2011WIM IR-016899V5R20WIM IR-016899V6R2010xWIM IR-016899V6R2011WIM
CGMVersionMacroDefine(3585,Thick_PerfosLevel13                                         ,MNJ ,30-10-2009 ,"V5R20 SP1 - perfos CATIALiveShape ") // activation immediate le 30-10-2009
CGMVersionMacroDefine(3586,Fillet_FastSplitEdge                                        ,rr  ,30-10-2009 ,"V5R20 SP1 - performances improvement ")
CGMVersionMacroDefine(3587,General_Perfo_R20                                           ,FDS ,30-10-2009 ,"V5R20 SP1 - Perfo ")
CGMVersionMacroDefine(3588,Homotopy_3Sur_TryExtrapolIfSingular                         ,ZUT ,30-10-2009 ,"V5R20 SP1 - RI ") // -cr IR-022732V6R2011WIM IR-022732V5R21WIM IR-022732V5R20WIM
CGMVersionMacroDefine(3589,Loft_ProfileComb_ExtendedSpeedLaw                           ,NLD ,06-11-2009 ,"V5R20 SP1 ") // -cr IR-017603V5R20WIM    IR-017603V6R2011WIM
CGMVersionMacroDefine(3590,PCurvesOffset_FindMoreCanonicalSurfaces                     ,MNJ ,06-11-2009 ,"V5R20 SP1 - RI ")
CGMVersionMacroDefine(3591,Parallel_RefinedSampling                                    ,ST5 ,06-11-2009 ,"V5R20 SP1 - RI 011082 Arc number density analysis to refine parallel sampling ") // -cr IR-011082V6R2011WIM
CGMVersionMacroDefine(3592,UnfoldTransfer_IncorrectMerge                               ,REN ,06-11-2009 ,"V5R20 SP1 - RI 018550V5R20, 018550V6R2011 ")
CGMVersionMacroDefine(3593,RemoveFace2D_CheckRemoveImpact                              ,ZUT ,13-11-2009 ,"V5R20 SP1 - RI ")
CGMVersionMacroDefine(3594,Loft_TrustImplicitSpineOrientation                          ,NLD ,13-11-2009 ,"V5R20 SP1 ") // -cr IR-023375V5R21WIM IR-023375V6R2011WIM IR-023375V5R20WIM
CGMVersionMacroDefine(3595,HLR_FaceHiddingALineLevel2                                  ,MNA ,13-11-2009 ,"V5R20 SP1 - RI ") // Disable specific treatment of visibility induce by determination of the visibilyty in case which the line is lying on the own surface
CGMVersionMacroDefine(3596,LayDown_OnVolume                                            ,JHN ,13-11-2009 ,"V5R20 SP1 - Dev ") // pour PFV posage sur volume
CGMVersionMacroDefine(3597,Thick_InterruptCapabilityLevel1                             ,ZUT ,13-11-2009 ,"V5R20 SP1 - Dev ")
CGMVersionMacroDefine(3598,GetParamFromLength_CutAtSuddenCurvatureChanges              ,zib ,13-11-2009 ,"V5R20 SP1 - Fix for 0653193 ")
CGMVersionMacroDefine(3599,Fillet_EnhancedTrimRibbons                                  ,RR  ,20-11-2009 ,"V5R20 SP1 - improvement of TrimRibbons option behaviour ")
CGMVersionMacroDefine(3600,Fill_FillAnalytiqueThinSurface                              ,MPS ,20-11-2009 ,"V5R20 SP1 - IR ") // -cr IR-024629V6R2011
CGMVersionMacroDefine(3601,Loft_ProfileComb_ExtendedSpeedLawV2                         ,NLD ,20-11-2009 ,"V5R20 SP1 ")
CGMVersionMacroDefine(3602,BuildDeform_ImproveInternalIncomp                           ,KTU ,20-11-2009 ,"V5R20 SP1 - Correction de bug detecte ") // Correction de la gestion des incompatibilites entre les courbes internes et les bords( bug)
//CGMVersionMacroDefine(3603,BooleanFace_ThroughCompatible                               ,JHN ,20-11-2009 ,"V5R20 SP1 - RI Swx ") // -cr IR-020845V6R2011WIM
CGMVersionMacroDefine(3604,Thick_ImportedFilletRecognition                             ,MNJ ,20-11-2009 ,"V5R20 SP1 - dev pour Swx ")
CGMVersionMacroDefine(3605,HLR_AvoidLimitCaseForEvalPointVisibility                    ,MNA ,20-11-2009 ,"V5R20 SP1 - RI ") // To avoid limitCase for the evaluation of the visibility of a point on a segment
CGMVersionMacroDefine(3606,Sweep_NoInternalThrow                                       ,NLD ,27-11-2009 ,"V5R20 SP1 ")
CGMVersionMacroDefine(3607,Sweep_OrderingWithNaturalIndexWhenUnresolved                ,NLD ,27-11-2009 ,"V5R20 SP1 ")
CGMVersionMacroDefine(3608,Thick_LocalSimplification                                   ,MNJ ,27-11-2009 ,"V5R20 SP1 - perfos CLS ") // activation immediate le 24-11-2009
CGMVersionMacroDefine(3609,Sweep_DeploySoftwareConfigurationV9                         ,NLD ,27-11-2009 ,"V5R20 SP1 ")
CGMVersionMacroDefine(3610,ReflectCurve_RuledSurfaceFilter                             ,PFV ,27-11-2009 ,"V5R20 SP1 - Perfo ")
CGMVersionMacroDefine(3611,BooleanFace_ThroughCompatible                               ,JHN ,27-11-2009 ,"V5R20 SP1 - RI Swx ") // -cr IR-020845V6R2011WIM
CGMVersionMacroDefine(3612,Fill_VolumeTreatment                                        ,MPS ,04-12-2009 ,"V5R20 SP1 ") // Traitement des volumes pour le Fill  demande BlendCorner en phase2
CGMVersionMacroDefine(3613,Silhouette_R2011                                            ,PFV ,04-12-2009 ,"V5R20 SP1 - Dev ")
CGMVersionMacroDefine(3614,HLR_BestJumpAccuracy                                        ,DPS ,11-12-2009 ,"V5R20 SP1 - reconvergence des sauts de visibilite en exact dans le HLR ") // etancheite indispensable pour les ombres chinoises
CGMVersionMacroDefine(3615,Thick_AdjustPCGuidesBoxes                                   ,ZUT ,11-12-2009 ,"V5R20 SP1 - RI ") // -cr IR-027402V5R20WIM IR-027402V5R21WIM IR-027402V6R2011WIM
CGMVersionMacroDefine(3616,TopCleanCurve_ToleranceAtLayDown                            ,RNO ,11-12-2009 ,"V5R20 SP1 - RI0651960V6R2011 ")
CGMVersionMacroDefine(3617,Regul_ConstraintPointsRelocation                            ,MNJ ,11-12-2009 ,"V5R20 SP1 - convergence dev ")
CGMVersionMacroDefine(3618,Interpol_AlwaysAnalyseDiscontinuitiesOnSmallArcs            ,ZIB ,11-12-2009 ,"V5R20 SP1 - Fix SW C1 fillet surface splits (Platter_C1_C1Mixte_C2.NCGM + 5mm fillet) ")
CGMVersionMacroDefine(3619,Parallelized_InterTopo                                      ,OID ,11-12-2009 ,"V5R20 SP1 - Parallélisation de l\\\'intersectTopologie en vue du MultiProcessing ") // KO corrigé par la livraison de demain
CGMVersionMacroDefine(3620,Thick_JournalForBioffsetFacesFromInternalEdges              ,ZFC ,18-12-2009 ,"V5R20 SP1 - RI SWx IR ") // -cr IR-020360V6R2011WIM
CGMVersionMacroDefine(3621,Loft_3DCombWithExtrudeDir                                   ,JSX ,18-12-2009 ,"V5R20 SP1 - TgOnGuideWithPlane : Pincement sur un odt SW Xbox ") // Sweep111
//CGMVersionMacroDefine(3622,SmartProject_Journal                                        ,RLA ,18-12-2009 ,"V5R20 SP1 - RI664878 ") // projection new journal to composite, 4 ODT KO livres OK, vendredi
//CGMVersionMacroDefine(3623,CATMathSystemXY_NewtonDichotomy_QuickTest                   ,KJD ,18-12-2009 ,"V5R20 SP1 - RI ") // -cr IR-018623V5R21WIM IR-018623V6R2011WIM
//CGMVersionMacroDefine(3624,Chamfer_Untwist                                             ,BQJ ,18-12-2009 ,"V5R20 SP1 - Dev ")
CGMVersionMacroDefine(3625,StylingFilletTuneUpApproxOfTraces                           ,MWE ,21-12-2009 ,"V5R20 SP1 - Dev ") // Fillet G2 et StylingFillet restent homogenes
CGMVersionMacroDefine(3626,Sweep_NoForcedCloningForClosedProfileV2                     ,NLD ,21-12-2009 ,"V5R20 SP1 ") // -cr IR-024627V6R2011WIM
CGMVersionMacroDefine(3627,Sweep_Interpol_OptimShuntNewton                             ,NLD ,21-12-2009 ,"V5R20 SP1 - perfos a la Roger Hassenforder ")
CGMVersionMacroDefine(3628,FilletBlendVertex_VersionWithParting                        ,JMA ,21-12-2009 ,"V5R20 SP1 - Dev ")
//CGMVersionMacroDefine(3629,SmartProject_Journal                                        ,RLA ,08-01-2010 ,"V5R20 SP1 - RI664878 ") // projection new journal to composite, 4 ODT KO livres OK, vendredi // debranche le 18-12-2009 et le 13-01-2010
CGMVersionMacroDefine(3630,IMA_RI011293_CutByPlane                                     ,RBD ,08-01-2010 ,"V5R20 SP1 - RI ") // -cr IR-011293, CATDesDivide KO
CGMVersionMacroDefine(3631,ProjCrvSur_CleanCuspCut                                     ,DAD ,08-01-2010 ,"V5R20 SP1 - RI 024761; clean of parasitical points after CuspCut treatment in ProjectionCrvSur ") // -cr IR-024761V5R20WIM IR-024761V5R21WIM IR-024761V6R2011WIM
CGMVersionMacroDefine(3632,SaveLowerDimInAbsorption                                    ,LD2 ,08-01-2010 ,"V5R20 SP1 - RI ") // -cr IR-020458V6R2011WIM IR-020458V5R20WIM IR-020458V5R19WIM IR-020458V5R21WIM
CGMVersionMacroDefine(3633,CGMR20SP1HF1                                                ,RHA ,08-01-2010 ,"V5R20 SP1 ")
CGMVersionMacroDefine(3634,CGMR20SP1HF2                                                ,RHA ,08-01-2010 ,"V5R20 SP1 ")
CGMVersionMacroDefine(3635,CGMR20SP1HF3                                                ,RHA ,08-01-2010 ,"V5R20 SP1 ")
CGMVersionMacroDefine(3636,CGMR20SP1HF4                                                ,RHA ,08-01-2010 ,"V5R20 SP1 ")
CGMVersionMacroDefine(3637,CGMR20SP1HF5                                                ,RHA ,08-01-2010 ,"V5R20 SP1 ")


//=========================================================================================================
// V5R20 SP2
//=========================================================================================================
CGMVersionMacroDefine(3638,Thick_SimplifyEdgesParametrizationCheck                     ,MNJ ,15-01-2010 ,"V5R20 SP2 - convergence dev SolidWorks ")
CGMVersionMacroDefine(3639,Thick_CleanNewerUnusedIfOpeFailedLvl2                       ,ZUT ,15-01-2010 ,"V5R20 SP2 - Corrections OLK dans operateurs Shells ")
CGMVersionMacroDefine(3640,RuledUnfold_NewAssembleOpe                                  ,REN ,15-01-2010 ,"V5R20 SP2 - RI 026333 ")
CGMVersionMacroDefine(3641,General_Perfo_R20SP2                                        ,FDS ,15-01-2010 ,"V5R20 SP2 - Perfo ")
CGMVersionMacroDefine(3642,Chamfer_R20SP2                                              ,RR  ,15-01-2010 ,"V5R20 SP2 - Chamfer Maintenance ")
CGMVersionMacroDefine(3643,Fillet_R20SP2                                               ,IZE ,15-01-2010 ,"V5R20 SP2 - RI + Dev ")
CGMVersionMacroDefine(3644,RSO_Stabilize_PreFunc                                       ,PMG ,15-01-2010 ,"V5R20 SP2 - RI ") // -cr IR-031478V5R20WIM IR-031478V5R21WIM IR-031478V5R21WIM
CGMVersionMacroDefine(3645,CleanCurve_HybridModeCorrectifsReportRemainingPoints        ,RNO ,15-01-2010 ,"V5R20 SP2 ") // Correction Bugs Limits + Bug Fermeture.
CGMVersionMacroDefine(3646,TopCleanCurve_ToleranceAtLayDown2                           ,RNO ,15-01-2010 ,"V5R20 SP2 - ODT ICMDMCatiaV5CTBMap_SelfTest_0006 Casse en Rel ") // ODT ICMDMCatiaV5CTBMap_SelfTest_0006
CGMVersionMacroDefine(3647,Thick_LineageSearchForEdgeTrustLevel                        ,ZFC ,22-01-2010 ,"V5R20 SP2 - IR ") // -cr IR-029677V6R2011WIM IR-029677V5R21WIM
CGMVersionMacroDefine(3648,SweepDraft_FastProject                                      ,NLD ,22-01-2010 ,"V5R20 SP2 ")
CGMVersionMacroDefine(3649,Sweep_XScaleR20SP2                                          ,NLD ,22-01-2010 ,"V5R20 SP2 ")
//CGMVersionMacroDefine(3650,InterFaceFace_Activation                                    ,OID ,22-01-2010 ,"V5R20 SP2 - Dev ")
CGMVersionMacroDefine(3651,Fill_NewManagementBigSlopes1                                ,MPS ,22-01-2010 ,"V5R20 SP2 - IR ") // -cr IR-029972V6R2011WIM
CGMVersionMacroDefine(3652,Regul_OneOffsetValuePerFace                                 ,MNJ ,22-01-2010 ,"V5R20 SP2 - dev robustesse regul ")
CGMVersionMacroDefine(3653,SweepDraft_StabilizeCutters                                 ,NLD ,22-01-2010 ,"V5R20 SP2 ")
CGMVersionMacroDefine(3654,Parallel_R20SP2                                             ,ST5 ,22-01-2010 ,"V5R20 SP2 - RI ")
CGMVersionMacroDefine(3655,RemoveFace_RobustnessLevel13                                ,ZUT ,22-01-2010 ,"V5R20 SP2 - RI + Dev ") // -cr 0639765V6R2011WIM IR-032203V6R2011WIM
CGMVersionMacroDefine(3656,CATMathSystemXY_NewtonDichotomy_QuickTest                   ,KJD ,22-01-2010 ,"V5R20 SP2 - RI ") // -cr IR-018623V5R21WIM IR-018623V6R2011WIM 18623V5R20WIM
CGMVersionMacroDefine(3657,Loft_ClosedOnSpine                                          ,JSX ,29-01-2010 ,"V5R20 SP2 - New functionality ")
CGMVersionMacroDefine(3658,Fill_ComponentsManagement                                   ,MPS ,29-01-2010 ,"V5R20 SP2 - IR ") // -cr IR-035126V5R20WIM  IR-035126V6R2011WIM  IR-035126V5R21WIM
CGMVersionMacroDefine(3659,Extrude_ByCircle_ProfileLimits                              ,DAD ,29-01-2010 ,"V5R20 SP2 - Migration current limits ")
CGMVersionMacroDefine(3660,Project_AllSolutions                                        ,jhn ,29-01-2010 ,"V5R20 SP2 - ri ") // -cr IR-029996V5R20WIM IR-029996V6R2011WIM IR-029996V5R21WIM
CGMVersionMacroDefine(3661,_IntersectionCrvSur_CircleRevol                             ,sty ,05-02-2010 ,"V5R20 SP2 - RI 24571: Cas special pour les cercle/revol à axes perpendiculaires ") // promote -cr IR-024571V5R21WIM   	  IR-024571V5R20WIM   	  IR-024571V6R2011WIM
CGMVersionMacroDefine(3662,Projection_2EdgesWireClosure                                ,JHN ,05-02-2010 ,"V5R20 SP2 - RI 25889 ") // -cr IR-025889V6R2011WIM IR-025889V5R21WIM IR-025889V5R20WIM IR-025889V5R19WIM
CGMVersionMacroDefine(3663,ProjCrvSur_NonCompSetRevol                                  ,DAD ,05-02-2010 ,"V5R20 SP2 - IR 026806 ") // -cr IR-026806V5R20 IR-026806V5R21 IR-026806V6R2011
CGMVersionMacroDefine(3664,SmartProject_Journal                                        ,RLA ,05-02-2010 ,"V5R20 SP2 - RI664878 ") // projection new journal to composite, 17 ODT KO livres OK, vendredi
CGMVersionMacroDefine(3665,Sweep_MVDKeepAfterExtrapolationV3                           ,NLD ,05-02-2010 ,"V5R20 SP2 ")
CGMVersionMacroDefine(3666,Regul_PointedSurfaceLocalSplit                              ,MNJ ,05-02-2010 ,"V5R20 SP2 - dev ") // activation immediate le 05-02-2010
CGMVersionMacroDefine(3667,ExtrapolWire_R20SP2                                         ,ST5 ,12-02-2010 ,"V5R20 SP2 - RI ") // -cr IR-036763V6R2011xWIM, IR-036763V5R21xWIM, IR-036763V5R20xWIM
CGMVersionMacroDefine(3668,MarshMallow_G1Stability                                     ,PMG ,12-02-2010 ,"V5R20 SP2 - RI : Stabilise le choix des normal quand le champ est discontinu. ") // -cr IR-037817V5R20WIM IR-037817V5R21WIM IR-037817V6R2011WIM
CGMVersionMacroDefine(3669,HLR_SilhouetteNodeLevel2                                    ,DPS ,12-02-2010 ,"V5R20 SP2 - qualite des silhouettes dans le HLR ") // -cr E0514700WIM 0514700V5R21WIM  IR-027845V5R20WIM IR-027845V6R2011WIM IR-027845V5R21WIM
CGMVersionMacroDefine(3670,Sweep_RelimitRibbon_MultiShell                              ,LAY ,12-02-2010 ,"V5R20 SP2 - RI 671741, CNEXT_030158_TopPrism ") // Improve the way the relimiting shell is chosen when there are multiple shells in the limiting body
CGMVersionMacroDefine(3671,Homotopy_RestraintSubdivExtrapolation                       ,MNJ ,12-02-2010 ,"V5R20 SP2 - dev ") // activation immediate le 12-02-2010
CGMVersionMacroDefine(3672,Revol_Use_Both_Limits_For_Surface                           ,THM ,12-02-2010 ,"V5R20 SP2 - IR 19152 ") // promote -cr IR-019152V5R21WIM IR-019152V6R2011WIM IR-019152V5R20WIM
CGMVersionMacroDefine(3673,Fillet_SplineToCanonic                                      ,RR  ,12-02-2010 ,"V5R20 SP2 - Canonicité ")
CGMVersionMacroDefine(3674,Thick_ConfusionVrepVsSrepOptim                              ,ZUT ,12-02-2010 ,"V5R20 SP2 - RI ") // -cr IR-038379V6R2011WIM IR-037727V6R2011WIM IR-037727V5R20WIM IR-037156V6R2011WIM IR-037156V5R20WIM
CGMVersionMacroDefine(3675,Projection_ClosureOnEdge2                                   ,JHN ,12-02-2010 ,"V5R20 SP2 - internal IR ") // -cr IR-032721V5R20WIM IR-032721V6R2011WIM
CGMVersionMacroDefine(3676,TrimByThick_BorderLOSimplifCorrections                      ,ZFC ,19-02-2010 ,"V5R20 SP2 - IR 033237, 037103, 038147 ") // -cr IR-033237V6R2011WIM IR-037103V6R2011WIM IR-038147V6R2011xWIM IR-038147V6R2011WIM
CGMVersionMacroDefine(3677,Parallel_NewInitComputation                                 ,REN ,19-02-2010 ,"V5R20 SP2 - RI 031483 ")
CGMVersionMacroDefine(3678,Chamfer_Untwist                                             ,BQJ ,19-02-2010 ,"V5R20 SP2 - Dev ") // debranche le 18-12-2009
CGMVersionMacroDefine(3679,Loft_Comb_SensibleG2Evaluation                              ,JSX ,19-02-2010 ,"V5R20 SP2 - DEV Lotf G2 ") // Combs must not systematically return a null curvature.
CGMVersionMacroDefine(3680,Sweep_SpineData_StabilizeSpineForLinearProfiles_2           ,JSX ,19-02-2010 ,"V5R20 SP2 - RI 39135 Cas particulier de profil colineaires ") // -cr IR-039135V5R20WIM IR-039135V5R21WIM IR-039135V6R2011WIM
CGMVersionMacroDefine(3681,SkinExtrapol_AdjustTrustLevelForFacesLevel4                 ,ZUT ,19-02-2010 ,"V5R20 SP2 - RI ") // -cr IR-037727V5R20WIM IR-037727V6R2011WIM IR-037156V5R20WIM IR-037156V6R2011WIM
CGMVersionMacroDefine(3682,AutoCheck_NoCutting                                         ,JHN ,19-02-2010 ,"V5R20 SP2 - autocheck ") // performances
//CGMVersionMacroDefine(3683,NewBooleanBuildArchitecture                                 ,LD2 ,19-02-2010 ,"V5R20 SP2 - Dev ")
CGMVersionMacroDefine(3684,Thick_SymmetryzationLevel1                                  ,MNJ ,19-02-2010 ,"V5R20 SP2 - dev ")
CGMVersionMacroDefine(3685,Split_SemiSpaceError                                        ,JHN ,19-02-2010 ,"V5R20 SP2 - RI ") // -cr IR-039669V5R20WIM IR-039669V6R2011WIM IR-039669V5R21WIM
CGMVersionMacroDefine(3686,CCVCleaner_DeepDuplicateTorusEquation                       ,NLD ,26-02-2010 ,"V5R20 SP2 ")
CGMVersionMacroDefine(3687,BooleanFace_JournalInter                                    ,JHN ,26-02-2010 ,"V5R20 SP2 - ODT SheExtrude01 ") // ODT
//CGMVersionMacroDefine(3688,Thick_InitMatterOriForSelfIntersectionFace                  ,LAP ,26-02-2010 ,"V5R20 SP2 - RI 038670 ") // -cr IR-038670V6R2011WIM
CGMVersionMacroDefine(3689,StylingFilletTuneUpSegmentationApproxBIS                    ,MWE ,26-02-2010 ,"V5R20 SP2 - RI 026738 ")
CGMVersionMacroDefine(3690,ErrorInManifolder                                           ,OID ,26-02-2010 ,"V5R20 SP2 - Correction ")
CGMVersionMacroDefine(3691,Ribbon_UpdateJournalIfNoInfo                                ,EYL ,05-03-2010 ,"V5R20 SP2 - RI ") // -cr IR-029215V5R20
CGMVersionMacroDefine(3692,Extremum_ConfusionOnExtremumPlane                           ,JHN ,05-03-2010 ,"V5R20 SP2 - RIs ") // -cr IR-021765V5R21WIM IR-021765V5R20WIM IR-021765V6R2011WIM  IR-024741V5R21WIM IR-024741V5R20WIM IR-024741V6R2011WIM
CGMVersionMacroDefine(3693,Unfold_VertexTransferFix                                    ,REN ,05-03-2010 ,"V5R20 SP2 - RI 035571 ")
CGMVersionMacroDefine(3694,SameTan_CrvLimInCrvAffSupp                                  ,DAD ,05-03-2010 ,"V5R20 SP2 - Migration current limits ")
CGMVersionMacroDefine(3695,TopShellOrientation_Journal                                 ,JHN ,05-03-2010 ,"V5R20 SP2 - RI externe ") // -cr IR-027187V5R21WIM IR-027187V6R2011WIM IR-027187V5R20WIM
CGMVersionMacroDefine(3696,DistanceBodyBody_MeshPtFilterFix                            ,mpx ,05-03-2010 ,"V5R20 SP2 - RI ") // -cr IR-042370V5R20WIM IR-042370V5R21WIM IR-042370V6R2011WIM IR-042370V6R2011xWIM
CGMVersionMacroDefine(3697,Offset_NonManifoldFRepsFromSameIVRepRelegation              ,MNJ ,05-03-2010 ,"V5R20 SP2 - RI MNT ")
CGMVersionMacroDefine(3698,ExtrapolOfSubdivSurface_ReducedMaxPatch                     ,RNO ,05-03-2010 ,"V5R20 SP2 - Too much memory used on Extrapolation ")
CGMVersionMacroDefine(3699,Sweep_FillTwistV2                                           ,NLD ,05-03-2010 ,"V5R20 SP2 ")
CGMVersionMacroDefine(3700,Sweep_NoForcedCloningForClosedProfileV3                     ,NLD ,05-03-2010 ,"V5R20 SP2 ")
CGMVersionMacroDefine(3701,OffsetVar_ImproveEasyArea                                   ,PMG ,12-03-2010 ,"V5R20 SP2 - ameliore la qualite dans les cas simples (PMR TMC) ")
CGMVersionMacroDefine(3702,ParameterizeOperatorLevel1                                  ,KTU ,12-03-2010 ,"V5R20 SP2 - homogénéisation des niveaux des utilisateurs ") // BM sur CGMTest_SurfacicN1FrFShellUnfold10
CGMVersionMacroDefine(3703,FuzzyOper_FullPolyMesh                                      ,DPS ,12-03-2010 ,"V5R20 SP2 - eradication des CldPolygon dans le FuzzyOffset et le FuzzySimplify ")
CGMVersionMacroDefine(3704,Extrude_SpatialLimits                                       ,NLD ,12-03-2010 ,"V5R20 SP2 ")
CGMVersionMacroDefine(3705,Offset_TwistedSurfaceAnomaly                                ,MNJ ,12-03-2010 ,"V5R20 SP2 - RI ")
CGMVersionMacroDefine(3706,Thick_CheckFuturNonManifoldEdge                             ,LAP ,12-03-2010 ,"V5R20 SP2 - RI ") // -cr IR-030363V6R2011WIM IR-030363V5R21WIM
//CGMVersionMacroDefine(3707,Loft_ProfileG2V0                                            ,JSX ,12-03-2010 ,"V5R20 SP2 - Protection pour l activation du G2 ")
CGMVersionMacroDefine(3708,ProjectionCrvSurGen_FindSurfaceBorderInit_RemoteCurve       ,KJD ,19-03-2010 ,"V5R20 SP2 - RI ") // -cr IR-041019V6R2011WIM IR-041019V5R21WIM IR-041019V5R20WIM
CGMVersionMacroDefine(3709,GeoTools_ComputeNumericalErrorScale_Update                  ,KJD ,19-03-2010 ,"V5R20 SP2 - Dev ")
CGMVersionMacroDefine(3710,Projection_IndexOnVertex                                    ,JHN ,19-03-2010 ,"V5R20 SP2 - ri 28803 ") // -cr IR-028803V5R20WIM IR-028803V5R21WIM IR-028803V6R2011WIM
CGMVersionMacroDefine(3711,CGMR20SP2HF1                                                ,RHA ,22-03-2010 ,"V5R20 SP2 ")
CGMVersionMacroDefine(3712,CGMR20SP2HF2                                                ,RHA ,22-03-2010 ,"V5R20 SP2 ")
CGMVersionMacroDefine(3713,CGMR20SP2HF3                                                ,RHA ,22-03-2010 ,"V5R20 SP2 ")
CGMVersionMacroDefine(3714,CGMR20SP2HF4                                                ,RHA ,22-03-2010 ,"V5R20 SP2 ")
CGMVersionMacroDefine(3715,CGMR20SP2HF5                                                ,RHA ,22-03-2010 ,"V5R20 SP2 ")


//=========================================================================================================
// V5R20 SP3
//=========================================================================================================
CGMVersionMacroDefine(3716,PCurvesOffset_SurfaceReuseTolerance                         ,ZFC ,26-03-2010 ,"V5R20 SP3 - IR ") // -cr IR-044615V6R2011WIM IR-044615V6R2011xWIM
CGMVersionMacroDefine(3717,TrimByThick_SimplifMode1JournalFix                          ,ZFC ,26-03-2010 ,"V5R20 SP3 - IR ") // -cr IR-038257V6R2011WIM IR-038257V6R2011xWIM
CGMVersionMacroDefine(3718,Fillet_R20SP3_Perf                                          ,RR  ,26-03-2010 ,"V5R20 SP3 - performances improvement ")
CGMVersionMacroDefine(3719,Regul_AddG0ConstraintsIfNone                                ,MNJ ,26-03-2010 ,"V5R20 SP3 - RI Swx ")
CGMVersionMacroDefine(3720,SkinExtrapol_CheckNonInversionOfFinalCrv                    ,ZUT ,26-03-2010 ,"V5R20 SP3 - RI ") // -cr IR-039809V5R20WIM IR-039809V5R21WIM IR-039809V6R2011WIM
CGMVersionMacroDefine(3721,Sweep_GetLambdaOnC0Vertex                                   ,NLD ,26-03-2010 ,"V5R20 SP3 ")
CGMVersionMacroDefine(3722,SplineCurve_EvalAloneThirdDerivative                        ,JSX ,02-04-2010 ,"V5R20 SP3 - Curiosité ") // codé mais non utilisé si pas d\'autre evals demandés (Bug Historique)
CGMVersionMacroDefine(3723,Fillet_R20SP3_Reorder                                       ,RR  ,02-04-2010 ,"V5R20 SP3 - Dev ") // Fix Fillet ribbons reordering
CGMVersionMacroDefine(3724,PosVsSurfBorder_PLineLimits                                 ,MNJ ,02-04-2010 ,"V5R20 SP3 - RI Swx ")
CGMVersionMacroDefine(3725,InterFaceFace_Activation                                    ,OID ,02-04-2010 ,"V5R20 SP3 - Dev ")
CGMVersionMacroDefine(3726,Connect_R20SP3                                              ,RR  ,09-04-2010 ,"V5R20 SP3 - RI047467 ") // SafeDivision in PointingDeformationV1
//CGMVersionMacroDefine(3727,NewSplit                                                    ,RLA ,09-04-2010 ,"V5R20 SP3 - Fast run ") // pour la R18
//CGMVersionMacroDefine(3728,Canonical_Plane_Plane_Fillet                                ,UVC ,09-04-2010 ,"V5R20 SP3 - Performance improvement ") // Introducing analytical treatment of plane-plane configurations in filleting
CGMVersionMacroDefine(3729,TrimSew_R20SP3                                              ,PRL ,09-04-2010 ,"V5R20 SP3 - Dev Autodraft ")
CGMVersionMacroDefine(3730,Compatible_CompletionJournal                                ,JHN ,09-04-2010 ,"V5R20 SP3 - RI CLS ") // -cr IR-031105V6R2011WIM
CGMVersionMacroDefine(3731,Sweep_ProfilePositioningV7                                  ,NLD ,09-04-2010 ,"V5R20 SP3 ")
CGMVersionMacroDefine(3732,General_Perfo_R20SP3                                        ,FDS ,09-04-2010 ,"V5R20 SP3 - Perfo ")
CGMVersionMacroDefine(3733,Thick_SymmetryzationLevel2                                  ,MNJ ,09-04-2010 ,"V5R20 SP3 - stabilisation code ")
CGMVersionMacroDefine(3734,SkinExtrapol_CreateMissingSmoothERepsLvl1                   ,ZUT ,09-04-2010 ,"V5R20 SP3 - RI ") // -cr IR-037157V5R21WIM IR-037157V5R20WIM IR-037157V6R2011WIM
CGMVersionMacroDefine(3735,Sweep_SpecialC0ComputationForPCircleProfile                 ,NLD ,09-04-2010 ,"V5R20 SP3 ")
CGMVersionMacroDefine(3736,TrimByThick_ActivateIntersectionForDirSurf                  ,ZFC ,16-04-2010 ,"V5R20 SP3 - IR a livrer pour la R209 (LiveSheetMetal) ") // -cr IR-042002V6R2011WIM IR-042002V6R2011xWIM IR-042676V6R2011WIM IR-042676V6R2011xWIM
CGMVersionMacroDefine(3737,Sweep_SynchroAfterClearObjects                              ,NLD ,16-04-2010 ,"V5R20 SP3 ")
CGMVersionMacroDefine(3738,IMA_Improve_Symmetry                                        ,RBD ,16-04-2010 ,"V5R20 SP3 - Dev : Amélioration résultats ") // ODT impactée :  CGMTest_SurfacicStoMeshTopoOperators_Symmetry5
CGMVersionMacroDefine(3739,Projection_MultiConfusedCutting                             ,JHN ,16-04-2010 ,"V5R20 SP3 - RI Reg interne ") // -cr IR-032721V6R2011WIM
CGMVersionMacroDefine(3740,Projection_SuppressIVFromCompatibleCutting                  ,JHN ,16-04-2010 ,"V5R20 SP3 - RI reg interne ") // -cr IR-048833V5R20WIM IR-048833V5R21WIM IR-048833V6R2011WIM IR-048833V6R2011xWIM
CGMVersionMacroDefine(3741,Fill_NewManagementBigSlopes3                                ,MPS ,23-04-2010 ,"V5R20 SP3 - pb Fill  analytique spatial ")
CGMVersionMacroDefine(3742,CornerMaintenance_R20SP3                                    ,ST5 ,23-04-2010 ,"V5R20 SP3 - RI ") // -cr IR-038574V6R2011WIM
CGMVersionMacroDefine(3743,NewSplit                                                    ,RLA ,23-04-2010 ,"V5R20 SP3 - Fast run ")
CGMVersionMacroDefine(3744,Canonical_Plane_Plane_Fillet                                ,UVC ,23-04-2010 ,"V5R20 SP3 - Performance improvement ") // Introducing analytical treatment of plane-plane configurations in filleting // debranche le 08-04-2010
CGMVersionMacroDefine(3745,Fillet_R20SP3_UnTwist                                       ,RR  ,23-04-2010 ,"V5R20 SP3 - RI ")
CGMVersionMacroDefine(3746,Thick_PerfosLevel17                                         ,ZUT ,23-04-2010 ,"V5R20 SP3 - RI ") // -cr IR-047528V5R20WIM IR-047528V5R21WIM IR-047528V6R2011xWIM 0655260V6R2011xWIM IR-049770V6R2011xWIM
CGMVersionMacroDefine(3747,Fillet_R20SP3                                               ,RR  ,23-04-2010 ,"V5R20 SP3 - Maintenance Fillet ")
CGMVersionMacroDefine(3748,Chamfer_R20SP3                                              ,RR  ,23-04-2010 ,"V5R20 SP3 - Maintenance Chamfer ")
CGMVersionMacroDefine(3749,ParamOpDontSolveWithRatio                                   ,KTU ,30-04-2010 ,"V5R20 SP3 - DEV:Amelioration dans les cas de fixation des bords ")
CGMVersionMacroDefine(3750,StylingFilletRemovalC1ContinuousTraces                      ,mwe ,30-04-2010 ,"V5R20 SP3 - RI 632486 ")
CGMVersionMacroDefine(3751,Thick_SymmetryzationLevel3                                  ,MNJ ,30-04-2010 ,"V5R20 SP3 - stabilisations + RI ")
CGMVersionMacroDefine(3752,Regul_R20SP3                                                ,MNJ ,30-04-2010 ,"V5R20 SP3 - Hull models ") // activation immédiate le 30/04/2010
CGMVersionMacroDefine(3753,Fillet_ExtrapolFromInitialShellBox                          ,RR  ,30-04-2010 ,"V5R20 SP3 - performances improvement ")
CGMVersionMacroDefine(3754,Silhouette_R2011x                                           ,DPS ,30-04-2010 ,"V5R20 SP3 - TopSilhouette evolutions ") // Dev
CGMVersionMacroDefine(3755,Fillet_RecursiveSupportCutting                              ,RR  ,07-05-2010 ,"V5R20 SP3 - Fillet Performances improvement ")
CGMVersionMacroDefine(3756,Sweep_UnspecWithAngleLaw                                    ,NLD ,07-05-2010 ,"V5R20 SP3 ")
CGMVersionMacroDefine(3757,HLR_TreatConfusionInMedgeIntersection                       ,MNA ,07-05-2010 ,"V5R20 SP3 - RI ") // -cr IR-038493V5R21WIM
CGMVersionMacroDefine(3758,Fill_AutoFillet_CorrectMesh                                 ,MPS ,07-05-2010 ,"V5R20 SP3 - IR ") // -cr IR-050938V5R21WIM     IR-050938V5R20WIM    IR-050938V6R2011WIM   IR-050938V6R2011xWIM
//CGMVersionMacroDefine(3759,Fillet_R20SP3_RibbonsReorder                                ,RR  ,07-05-2010 ,"V5R20 SP3 - Maintenance Fillet ")
CGMVersionMacroDefine(3760,RemoveFace_RobustnessLevel14                                ,MNJ ,07-05-2010 ,"V5R20 SP3 - convergence dev Roof Revit ") // activation immediate le 07-05-2010
CGMVersionMacroDefine(3761,CATIntersectionPCrvPCrvPerfoPlineOnPlane                    ,sty ,07-05-2010 ,"V5R20 SP3 - Perfo ")
CGMVersionMacroDefine(3762,Loft_DoNotMoveFromGuideOnFlatZone_2                         ,JSX ,12-05-2010 ,"V5R20 SP3 - dev ") // Correction du pb a la source, la première version etait partielle
CGMVersionMacroDefine(3763,Sweep_EquivalentPointExtendedProfile                        ,NLD ,12-05-2010 ,"V5R20 SP3 ")
CGMVersionMacroDefine(3764,DistanceSurSur_PatchGrid                                    ,sty ,12-05-2010 ,"V5R20 SP3 - RI ") // -cr IR-049603V6R2011xWIM IR-049603V6R2011WIM IR-049603V5R21WIM IR-049603V5R20WIM
CGMVersionMacroDefine(3765,IntersectionCrvSur_LineRevol_Reconverge                     ,STY ,12-05-2010 ,"V5R20 SP3 - RI ") // -cr IR-047718V6R2011xWIM IR-047718V6R2011WIM IR-047718V5R21WIM
CGMVersionMacroDefine(3766,PtSurCan_ProjOnConeApex                                     ,DAD ,12-05-2010 ,"V5R20 SP3 - Bug on the projection of a point on the apex of a cone ")
CGMVersionMacroDefine(3767,GapFill_SingleCapFace                                       ,BQJ ,12-05-2010 ,"V5R20 SP3 - Dev ") // To enable GapFill whan the Neutral Edges intersects, in NN Draft
CGMVersionMacroDefine(3768,RemoveFace_ExtrapolLengthComputationLevel1                  ,ZUT ,21-05-2010 ,"V5R20 SP3 - Stabilisation RemoveFace ")
CGMVersionMacroDefine(3769,Boolean_DeadEndInConfusedLoop                               ,WQO ,21-05-2010 ,"V5R20 SP3 - IR ") // -cr IR-043227V5R21WIM IR-043227V6R2011xWIM IR-043227V5R20WIM IR-043227V6R2011WIM
CGMVersionMacroDefine(3770,DistanceBodyBody_CellBoxTest                                ,NHD ,21-05-2010 ,"V5R20 SP3 - RI ") // -cr IR-050789V5R20WIM
CGMVersionMacroDefine(3771,HLR_FilterOverCutSilhouettes                                ,DPS ,21-05-2010 ,"V5R20 SP3 - Elimination du ResultBrowser des silhouettes parasites issues d\'un surdecoupage ") // -cr IR-050540V5R20WIM IR-050540V5R21WIM IR-050540V6R2011xWIM
CGMVersionMacroDefine(3772,RegularizeFillShell                                         ,LD2 ,21-05-2010 ,"V5R20 SP3 - RI ") // -cr IR-041335V5R21WIM IR-041335V5R20WIM IR-041335V6R2011WIM
CGMVersionMacroDefine(3773,Boolean_CrvParamCorrectionToCalculate3DEdgeBox              ,WQO ,21-05-2010 ,"V5R20 SP3 - IR ") // -cr IR-043255V5R20WIM IR-043255V5R21WIM IR-043255V6R2011WIM IR-043255V6R2011xWIM
CGMVersionMacroDefine(3774,Boolean_DestroyDegenerated                                  ,JHN ,21-05-2010 ,"V5R20 SP3 - interne ")
CGMVersionMacroDefine(3775,Unfold_ConstrainedVerticesIndexFix                          ,REN ,28-05-2010 ,"V5R20 SP3 - dev (FrFUnfold Fixation) ")
CGMVersionMacroDefine(3776,CutSelfOnSkins_BetterDelayedTreatement                      ,LD2 ,28-05-2010 ,"V5R20 SP3 - RI ") // -cr IR-049335V5R20WIM IR-049335V6R2011WIM IR-049335V5R21WIM IR-049335V6R2011xWIM
CGMVersionMacroDefine(3777,Sweep_ExtrapolLawV2                                         ,NLD ,28-05-2010 ,"V5R20 SP3 ")
CGMVersionMacroDefine(3778,Offset_FilterReverseIsoTopoClosingFReps                     ,MNJ ,28-05-2010 ,"V5R20 SP3 - RI Porsche ")
CGMVersionMacroDefine(3779,Regul_RobustnessLevel1                                      ,MNJ ,28-05-2010 ,"V5R20 SP3 - convergence dev Regul locale ") // activation immediate le 28-05-2010
CGMVersionMacroDefine(3780,HLR_UseSilhConfusionInformationASAP                         ,MNA ,28-05-2010 ,"V5R20 SP3 - Ri correction ") // -c r IR-049611V5R20WIM IR-049611V5R19WIM IR-049611V5R21WIM  IR-049611V6R2011xWIM
CGMVersionMacroDefine(3781,Sweep_NoTrimBeforeClosureShift                              ,NLD ,28-05-2010 ,"V5R20 SP3 ") // -cr IR-054010V5R20WIM    IR-054010V5R21WIM    IR-054010V6R2011xWIM
CGMVersionMacroDefine(3782,SplitArchitecture                                           ,RLA ,28-05-2010 ,"V5R20 SP3 - CGMReplay du Split ") // evolution pour SW
CGMVersionMacroDefine(3783,Boolean_RattrapHomogenizeField                              ,JHN ,04-06-2010 ,"V5R20 SP3 - ri ") // -cr IR-048927V5R20WIM IR-048927V6R2011xWIM IR-048927V6R2011WIM IR-048927V5R21WIM
CGMVersionMacroDefine(3784,Fillet_MultiRibbon_Backup                                   ,RR  ,04-06-2010 ,"V5R20 SP3 - maintenance Fillet ")
CGMVersionMacroDefine(3785,Unfold_FixationRelDistFix                                   ,REN ,11-06-2010 ,"V5R20 SP3 - IR 052158, 052269, 052155, 052162, ")
CGMVersionMacroDefine(3786,Regul_SwitchToPolyMeshOffset                                ,CWM ,11-06-2010 ,"V5R20 SP3 - migrer sur le nouvel algo VRep d\'offset flou polyhedrique ")
CGMVersionMacroDefine(3787,Fillet_R20SP3_RibbonsReorder                                ,RR  ,11-06-2010 ,"V5R20 SP3 - Maintenance Fillet ")
CGMVersionMacroDefine(3788,InterShell_CreateFewerWires                                 ,LD2 ,11-06-2010 ,"V5R20 SP3 - RI ") // -cr IR-050825V5R21WIM IR-050825V5R20WIM IR-050825V6R2011xWIM IR-050825V6R2011WIM
CGMVersionMacroDefine(3789,Blend_SmoothedCurvature_4                                   ,JSX ,18-06-2010 ,"V5R20 SP3 - RI Boeing ") // -cr IR-056146V6R2011xWIM IR-056146V5R21WIM
CGMVersionMacroDefine(3790,Blend_SmoothedCurvature_5                                   ,JSX ,18-06-2010 ,"V5R20 SP3 - RI Boeing : pas de smooth de la courbure en mono domaine ")
CGMVersionMacroDefine(3791,Parallel_GraphReportCheckTangency                           ,ST5 ,18-06-2010 ,"V5R20 SP3 - IR ") // -cr IR-043821V5R21WIM IR-043821V6R2011xWIM
CGMVersionMacroDefine(3792,PtSurRevol_EdgeFixDist                                      ,DAD ,18-06-2010 ,"V5R20 SP3 - Edge of the domain management for PtSurRevol projection ") // -cr IR-053568V5R20WIM  IR-053568V5R21WIM IR-053568V6R2011xWIM
CGMVersionMacroDefine(3793,CGMR20SP3HF1                                                ,RHA ,21-06-2010 ,"V5R20 SP3 ")
CGMVersionMacroDefine(3794,CGMR20SP3HF2                                                ,RHA ,21-06-2010 ,"V5R20 SP3 ")
CGMVersionMacroDefine(3795,CGMR20SP3HF3                                                ,RHA ,21-06-2010 ,"V5R20 SP3 ")
CGMVersionMacroDefine(3796,CGMR20SP3HF4                                                ,RHA ,21-06-2010 ,"V5R20 SP3 ")
CGMVersionMacroDefine(3797,CGMR20SP3HF5                                                ,RHA ,21-06-2010 ,"V5R20 SP3 ")


//=========================================================================================================
// V5R20 SP4
//=========================================================================================================
CGMVersionMacroDefine(3800,Fillet_LocalSelection_MaxGap                                ,RR  ,25-06-2010 ,"V5R20 SP4 - Fillet MultiRibbon Robustness ") // R20SP4
CGMVersionMacroDefine(3801,Fillet_ImplicitKeepEdge_NoRollingEdge                       ,RR  ,25-06-2010 ,"V5R20 SP4 - FMP Fillet Robustness ") // R20SP4
CGMVersionMacroDefine(3802,Fillet_LightVolumeCheck                                     ,RR  ,25-06-2010 ,"V5R20 SP4 - performances improvement ") // R20SP4
CGMVersionMacroDefine(3803,Thick_CheckUntouchedFacesLevel2                             ,MNJ ,25-06-2010 ,"V5R20 SP4 - RI ")
CGMVersionMacroDefine(3804,TriTanPCrv_ForbidLim                                        ,DAD ,25-06-2010 ,"V5R20 SP4 - IR 53204 ")
CGMVersionMacroDefine(3805,RelimitByVolume_MigrateJournal                              ,LD2 ,25-06-2010 ,"V5R20 SP4 - Dev ")
CGMVersionMacroDefine(3806,Fillet_ClosedRibbon_Fixes                                   ,RR  ,25-06-2010 ,"V5R20 SP4 - Fixes ")
CGMVersionMacroDefine(3807,Sweep_FillTwistV3                                           ,NLD ,02-07-2010 ,"V5R20 SP4 ")
CGMVersionMacroDefine(3808,Sweep_ReorderedInputSupportV1                               ,NLD ,02-07-2010 ,"V5R20 SP4 ")
CGMVersionMacroDefine(3809,Sweep_SpineDeformationWithExtrapolationV2                   ,NLD ,02-07-2010 ,"V5R20 SP4 ") // -cr IR-056178V6R2011xWIM    IR-056178V5R21WIM    IR-056178V5R20WIM
CGMVersionMacroDefine(3810,Sweep_RestoreDomainsIfErrorV1                               ,NLD ,02-07-2010 ,"V5R20 SP4 ")
CGMVersionMacroDefine(3811,Sweep_BufferizeBooleanOptions                               ,NLD ,02-07-2010 ,"V5R20 SP4 ")
CGMVersionMacroDefine(3812,Thick_MultiValueAroundDegenSRep                             ,MNJ ,02-07-2010 ,"V5R20 SP4 - RI ") // activation immediate le 02-06-2010
CGMVersionMacroDefine(3813,Sweep_ExtrapolationDes3Becs                                 ,NLD ,02-07-2010 ,"V5R20 SP4 ")
CGMVersionMacroDefine(3814,General_Perfo_R20SP4                                        ,TXO ,02-07-2010 ,"V5R20 SP4 - Perfo ")
CGMVersionMacroDefine(3815,Fillet_R20SP4                                               ,ZUS ,02-07-2010 ,"V5R20 SP4 - RIs ")
CGMVersionMacroDefine(3816,Sweep_ComputeGraphSW                                        ,thm ,02-07-2010 ,"V5R20 SP4 - These are new ODTs. They will start passing when the code is promoted to CGMOFF this week. ") // Generalisation of ComputeGraph to handle closed sweep paths.
CGMVersionMacroDefine(3817,Fillet_SmartRibEnd_R20SP4                                   ,RR  ,02-07-2010 ,"V5R20 SP4 - maintenance Fillet ")
CGMVersionMacroDefine(3818,Thick_StabilizationLevel1                                   ,ZUT ,02-07-2010 ,"V5R20 SP4 - Stabilisation pour FastRun ")
CGMVersionMacroDefine(3819,ThickSurface_LogicalMatterSideCBPrefered                    ,MNJ ,09-07-2010 ,"V5R20 SP4 - stabilisation fast update ") // activation immediate le 09/07/2010
CGMVersionMacroDefine(3820,Thick_RevEdgeAnoNewConvexityInversion                       ,ZFC ,09-07-2010 ,"V5R20 SP4 - Stabilisation Fast Update ")
CGMVersionMacroDefine(3821,Fillet_SmartGeometry                                        ,RR  ,16-07-2010 ,"V5R20 SP4 - Maintenance Fillet & chamfer ")
CGMVersionMacroDefine(3822,Extrapol_ShellG1_FixedNormalOnG0Edges                       ,JSX ,23-07-2010 ,"V5R20 SP4 - IR 060785 extrapol G1 ") // -cr IR-060785V5R21WIM IR-060785V6R2011xWIM
CGMVersionMacroDefine(3823,TrimByThick_NullRadiusConfigLevel4                          ,ZFC ,23-07-2010 ,"V5R20 SP4 - RI Externe IR ") // -cr IR-060379V6R2011xWIM
CGMVersionMacroDefine(3824,StylingFilletRattrapEvaluator                               ,mwe ,23-07-2010 ,"V5R20 SP4 - RI 057431 ")
CGMVersionMacroDefine(3825,Fillet_FaceFace_MultiRibbon                                 ,JQS ,23-07-2010 ,"V5R20 SP4 - Dev ") // Allow Face/Face MultiRibbon processing
CGMVersionMacroDefine(3826,ThickWire_ReportParallelErase                               ,ST5 ,23-07-2010 ,"V5R20 SP4 - RI ") // -cr IR-054353V6R2011xWIM
CGMVersionMacroDefine(3827,SplitBySkin_DestroyCompositesInCatch                        ,LD2 ,30-07-2010 ,"V5R20 SP4 - Dev ")
//CGMVersionMacroDefine(3828,Marching_MultipleDomain_MandatorySaturation                 ,KJD ,06-08-2010 ,"V5R20 SP4 - RI 046422 (A activer conjointement avec la variable Marching_Controles_TangentsInSingularArea) ") // IR-046422V5R20WIM IR-046422V5R21WIM IR-046422V6R2011WIM IR-046422V6R2011xWIM
//CGMVersionMacroDefine(3829,Marching_Controles_TangentsInSingularArea                   ,kjd ,06-08-2010 ,"V5R20 SP4 - RI 046422 (activer conjointement avec Marching_MultipleDomain_MandatorySaturation) ") // IR-046422V5R20WIM IR-046422V5R21WIM IR-046422V6R2011WIM IR-046422V6R2011xWIM
CGMVersionMacroDefine(3830,Fill_EmptyBody                                              ,MPS ,06-08-2010 ,"V5R20 SP4 - IR    051773 ") // -cr   IR-051773V6R2011xWIM IR-051773V5R20WIM  IR-051773V5R21WIM
CGMVersionMacroDefine(3831,Fill_JournalForFillWithoutBoundary                          ,MPS ,06-08-2010 ,"V5R20 SP4 - correction du journal dans le fill sans frontiere ")
CGMVersionMacroDefine(3832,MProcBoolean                                                ,ase ,06-08-2010 ,"V5R20 SP4 ")
CGMVersionMacroDefine(3833,ApplyPowerDefUseDefSLimits                                  ,KTU ,06-08-2010 ,"V5R20 SP4 - Stabilite ") // asap
CGMVersionMacroDefine(3834,HLR_ComplexFilletCurvatureAnalysisTrigger                   ,DPS ,06-08-2010 ,"V5R20 SP4 - improve the silhouette computation robustness on complex fillet surfaces ") // -cr IR-054822V6R2011xWIM
CGMVersionMacroDefine(3835,Thick_ElimConfusedFRepLevel1                                ,ZUT ,06-08-2010 ,"V5R20 SP4 - Stabilisation pour FastRun ")
CGMVersionMacroDefine(3836,DistanceBodyBody_CorrectedInitTol                           ,NHD ,13-08-2010 ,"V5R20 SP4 - RI ") // -cr IR-053668V5R21WIM
CGMVersionMacroDefine(3837,Thick_VertexSizeControl                                     ,MNJ ,13-08-2010 ,"V5R20 SP4 - modeles Acis ") // activation immediate le 13/08/2010
CGMVersionMacroDefine(3838,HLR_FixNullDotFaceBoundaryVisibility                        ,DPS ,13-08-2010 ,"V5R20 SP4 - quality for HONDA ") // improve the visibility management on null projected face boundary
CGMVersionMacroDefine(3839,Boolean_SameFaceAdjacency                                   ,JHN ,13-08-2010 ,"V5R20 SP4 - RI ") // pas de -cr
CGMVersionMacroDefine(3840,Thick_DiscoCallBack3DForceInsideOrOutside                   ,ZFC ,13-08-2010 ,"V5R20 SP4 - RI Toyota : activation immediate demandee pour le 13/08/2010 ") // -cr IR-064081V5R20WIM IR-064081V6R2011xWIM IR-064081V5R21WIM
CGMVersionMacroDefine(3841,HLR_StrictResoAsTolConf                                     ,DPS ,20-08-2010 ,"V5R20 SP4 - RI Swatch ") // -cr IR-058775V6R2011xWIM IR-058775V5R21WIM
CGMVersionMacroDefine(3842,Boolean_RI061511                                            ,WQO ,20-08-2010 ,"V5R20 SP4 - RI061511 ") // -cr IR-061511V6R2011xWIM
CGMVersionMacroDefine(3843,Thick_SymmetryzationLevel5                                  ,MNJ ,20-08-2010 ,"V5R20 SP4 - RI TMC REG ") // activation immediate le 20/08/2010
CGMVersionMacroDefine(3844,DistanceBodyBody_RoundOff                                   ,MPX ,20-08-2010 ,"V5R20 SP4 - IR ") // -cr IR-066082V5R20WIM IR-066082V5R21WIM IR-066082V6R2011xWIM
CGMVersionMacroDefine(3845,RemoveEdge_RobustnessLevel1                                 ,ZUT ,20-08-2010 ,"V5R20 SP4 - Robustesse RemoveEdge sur modeles ACIS ")
CGMVersionMacroDefine(3846,Thick_CheckMultiERepsWithSameECrv                           ,ZUT ,20-08-2010 ,"V5R20 SP4 - RI ") // -cr IR-066454V6R2011xWIM IR-066454V6R2012WIM
//CGMVersionMacroDefine(3847,NewBooleanBuildArchitecture                                 ,LD2 ,20-08-2010 ,"V5R20 SP4 - Dev ") // debranche le 22-02-2010
CGMVersionMacroDefine(3848,Thick_NonMergeableERepsManagement                           ,MNJ ,27-08-2010 ,"V5R20 SP4 - modeles Acis ") // activation immediate le 27-08-2010
CGMVersionMacroDefine(3849,UnFoldedAero_FailedTransformationFix                        ,REN ,27-08-2010 ,"V5R20 SP4 - PMR68805299706 ")
//CGMVersionMacroDefine(3850,SurSurTg_EnlargeDomainForSolve                              ,LAP ,27-08-2010 ,"V5R20 SP4 - RI ") // -cr IR-059797V5R20WIM IR-059797V5R21WIM IR-059797V6R2011xWIM
CGMVersionMacroDefine(3851,Fillet_OBBFiltering                                         ,xmh ,27-08-2010 ,"V5R20 SP4 - Performance ") // Fillet project to replace use of axis aligned boxes by object oriented boxes.
CGMVersionMacroDefine(3852,Fillet_HoldCurveExtrapolation                               ,RR  ,27-08-2010 ,"V5R20 SP4 - RI ") // Preventive 20% extrapolation of HoldCurve Geometry
CGMVersionMacroDefine(3853,Sweep_ThinSolid_FilterMisleadingVertices                    ,dlp ,27-08-2010 ,"V5R20 SP4 - RI 052628 ") // IR 052628 rib journal problem
CGMVersionMacroDefine(3854,Blend_GeometricTolForClosedLaw                              ,JSX ,03-09-2010 ,"V5R20 SP4 - RI 036079 ") // -cr IR-036079V5R20WIM IR-036079V6R2011xWIM
CGMVersionMacroDefine(3855,SurSurTg_EnlargeDomainForSolve                              ,LAP ,03-09-2010 ,"V5R20 SP4 - RI ") // -cr IR-059797V5R20WIM IR-059797V5R21WIM IR-059797V6R2011xWIM
CGMVersionMacroDefine(3856,LayDown_EqualDuplicated                                     ,JHN ,03-09-2010 ,"V5R20 SP4 - RI externe (ODT KO CGMReplay_TrimShell_KeepRemove,CGMTest_Disconnect_WireVertex,CGMTest_Disconnect_ShellWire,CGMTest_SimilarCurve_Case02,CGMTest_SimilarCurve_Case01,CGMTest_Split_ShellShell_Case3,TestSUBDCloseScar_CGMReplay,CGM_TrimShell) ") // -cr IR-057095V6R2011xWIM IR-057095V5R20WIM IR-057095V5R21WIM
CGMVersionMacroDefine(3857,Marching_Controles_TangentsInSingularArea                   ,kjd ,03-09-2010 ,"V5R20 SP4 - RI 046422 (activer conjointement avec Marching_MultipleDomain_MandatorySaturation) Corrections supplémentaires effectuées ") // IR-046422V5R20WIM IR-046422V5R21WIM IR-046422V6R2011WIM IR-046422V6R2011xWIM
CGMVersionMacroDefine(3858,Marching_MultipleDomain_MandatorySaturation                 ,KJD ,03-09-2010 ,"V5R20 SP4 - RI 046422 (A activer conjointement avec la variable Marching_Controles_TangentsInSingularArea) ") // IR-046422V5R20WIM IR-046422V5R21WIM IR-046422V6R2011WIM IR-046422V6R2011xWIM
CGMVersionMacroDefine(3859,Thick_MultiConfusionAccuracy                                ,MNJ ,03-09-2010 ,"V5R20 SP4 - modeles Acis ") // activation immediate le 03-09-2010
CGMVersionMacroDefine(3860,Boolean_CATFaceOrder                                        ,WQO ,03-09-2010 ,"V5R20 SP4 - Satbilisation de l\'ordre des Faces en sortie du booléen ")
CGMVersionMacroDefine(3861,NewBooleanBuildArchitecture                                 ,LD2 ,03-09-2010 ,"V5R20 SP4 - Dev ") // debranche le 22-02-2010 // debranche le 25-08-2010
CGMVersionMacroDefine(3862,SmartProject_RI51097                                        ,OID ,03-09-2010 ,"V5R20 SP4 - RI ") // -cr IR-051097V5R20WIM IR-051097V5R21WIM IR-051097V6R2011xWIM IR-051097V6R2011WIM
CGMVersionMacroDefine(3863,ProjCrvSur_CleanCanProj                                     ,DAD ,10-09-2010 ,"V5R20 SP4 - RI 057558; cleaning curves created by Canonical Projection without Set Of Points ")
CGMVersionMacroDefine(3864,Draft_DRLCoveredFaces1                                      ,SOU ,10-09-2010 ,"V5R20 SP4 - RI ") // -cr IR-065237V5R20
CGMVersionMacroDefine(3865,ProjectionPtCrv_Sampling                                    ,PKC ,10-09-2010 ,"V5R20 SP4 - RI ") // -cr IR-060159V5R20WIM  IR-060159V5R21WIM   	IR-060159V6R2011xWIM
CGMVersionMacroDefine(3866,SmartProjection_RI61894                                     ,OID ,10-09-2010 ,"V5R20 SP4 - RI ")
CGMVersionMacroDefine(3867,CGMR20SP4HF1                                                ,RHA ,10-09-2010 ,"V5R20 SP4 ")
CGMVersionMacroDefine(3868,CGMR20SP4HF2                                                ,RHA ,10-09-2010 ,"V5R20 SP4 ")
CGMVersionMacroDefine(3869,CGMR20SP4HF3                                                ,RHA ,10-09-2010 ,"V5R20 SP4 ")
CGMVersionMacroDefine(3870,CGMR20SP4HF4                                                ,RHA ,10-09-2010 ,"V5R20 SP4 ")
CGMVersionMacroDefine(3871,CGMR20SP4HF5                                                ,RHA ,10-09-2010 ,"V5R20 SP4 ")
CGMVersionMacroDefine(3872,CGMR20SP4HF6                                                ,RHA ,10-09-2010 ,"V5R20 SP4 ")
CGMVersionMacroDefine(3873,CGMR20SP4HF7                                                ,RHA ,10-09-2010 ,"V5R20 SP4 ")
CGMVersionMacroDefine(3874,CGMR20SP4HF8                                                ,RHA ,10-09-2010 ,"V5R20 SP4 ")
CGMVersionMacroDefine(3875,CGMR20SP4HF9                                                ,RHA ,10-09-2010 ,"V5R20 SP4 ")
CGMVersionMacroDefine(3876,CGMR20SP4HF10                                               ,RHA ,10-09-2010 ,"V5R20 SP4 ")


//=========================================================================================================
// V5R20 SP5
//=========================================================================================================
CGMVersionMacroDefine(3877,DistanceBodyBody_SolutionSkipImproved                       ,MPX ,17-09-2010 ,"V5R20 SP5 - RI 070400 ") // -cr IR-070400V5R20WIM IR-070400V5R21WIM IR-070400V6R2011xWIM IR-070400V6R2012WIM
CGMVersionMacroDefine(3878,Fillet_R20SP5                                               ,RR  ,17-09-2010 ,"V5R20 SP5 ") // Fillet Maintenance
CGMVersionMacroDefine(3879,Fillet_ThrowIfInitEdgeRemains                               ,RR  ,17-09-2010 ,"V5R20 SP5 - Fillet Maintenance ")
CGMVersionMacroDefine(3880,RemoveFace_ImproveFilletRemoving                            ,ZUT ,17-09-2010 ,"V5R20 SP5 - Robustesse RemoveFace lors de la suppression de fillets ")
CGMVersionMacroDefine(3881,General_Perfo_R20SP5                                        ,FDS ,17-09-2010 ,"V5R20 SP5 - Perfo, if no more versionning in R20SP5 , please call it General_Perfo_R21 ( let me know ) ")
CGMVersionMacroDefine(3882,Thick_ConvergenceForGeoStabilizations                       ,MNJ ,17-09-2010 ,"V5R20 SP5 - ODTs KO Unix / FIXPARTWARN convergence pour diverses stabilisations géométriques ")
CGMVersionMacroDefine(3883,TrimArchitecture                                            ,RLA ,17-09-2010 ,"V5R20 SP5 - evolution pour le FAST RUN ") // odt ko: DSPTest_Variable_Offset_RmFace2 (la correction sera livrée vendredi)
CGMVersionMacroDefine(3884,Close_ThrowIfInvalid                                        ,LD2 ,17-09-2010 ,"V5R20 SP5 - RI ") // -cr IR-068890V5R20WIM IR-068890V6R2012WIM IR-068890V6R2011xWIM IR-068890V5R21WIM
CGMVersionMacroDefine(3885,Draft_RelimWithHoleCreation                                 ,PRL ,17-09-2010 ,"V5R20 SP5 - Dev ") // promote -cr IR-021492V6R2011xWIM
CGMVersionMacroDefine(3886,CGMR210HF1                                                  ,RHA ,17-09-2010 ,"V5R20 SP5 ")
CGMVersionMacroDefine(3887,CGMR210HF2                                                  ,RHA ,17-09-2010 ,"V5R20 SP5 ")
CGMVersionMacroDefine(3888,CGMR210HF3                                                  ,RHA ,17-09-2010 ,"V5R20 SP5 ")
CGMVersionMacroDefine(3889,CGMR210HF4                                                  ,RHA ,17-09-2010 ,"V5R20 SP5 ")
CGMVersionMacroDefine(3890,CGMR210HF5                                                  ,RHA ,17-09-2010 ,"V5R20 SP5 ")
CGMVersionMacroDefine(3891,CGMR210HF6                                                  ,RHA ,17-09-2010 ,"V5R20 SP5 ")
CGMVersionMacroDefine(3892,CGMR210HF7                                                  ,RHA ,17-09-2010 ,"V5R20 SP5 ")
CGMVersionMacroDefine(3893,CGMR210HF8                                                  ,RHA ,17-09-2010 ,"V5R20 SP5 ")
CGMVersionMacroDefine(3894,CGMR210HF9                                                  ,RHA ,17-09-2010 ,"V5R20 SP5 ")
CGMVersionMacroDefine(3895,CGMR210HF10                                                 ,RHA ,17-09-2010 ,"V5R20 SP5 ")
CGMVersionMacroDefine(3896,Fillet_SkinRelimitationForcedTo3D                           ,RR  ,24-09-2010 ,"V5R20 SP5 - FixpartFastRun ")
CGMVersionMacroDefine(3897,FillAnalytique_NewJournal                                   ,MPS ,24-09-2010 ,"V5R20 SP5 - correction du journal du Fill Analytique dans Fillet ")
CGMVersionMacroDefine(3898,SpecBissectorSampler_Derivatives                            ,MNJ ,24-09-2010 ,"V5R20 SP5 - ODTs KO FPExceptions/ instabilites FIPARTWARN/Unix (CQI) ")
CGMVersionMacroDefine(3899,CornerBiTgtRadius_LimitCase_R20SP5                          ,ST5 ,24-09-2010 ,"V5R20 SP5 - RI: Cas limite du Corner Point ") // -cr IR-045405V5R20xWIM, IR-045405V5R21xWIM, IR-045405V5R21xWIM, IR-045405V6R2011xWIM
CGMVersionMacroDefine(3900,Boolean_FixFilterInExtrudeCaseDetection                     ,WQO ,24-09-2010 ,"V5R20 SP5 - PER in CATSubdFace::IsAnExtrudeCase ")
CGMVersionMacroDefine(3901,HomotopyCrvSur_ParametricDistortionFactor                   ,MNJ ,01-10-2010 ,"V5R20 SP5 - modeles Acis ")
CGMVersionMacroDefine(3902,RemoveFace_RobustnessLevel17                                ,ZUT ,01-10-2010 ,"V5R20 SP5 - Modele Spatial ")
CGMVersionMacroDefine(3903,StylingFilletRemoveFaceOnOneSupport                         ,mwe ,08-10-2010 ,"V5R20 SP5 - RI sur update et upgrade ") // regression PSA
CGMVersionMacroDefine(3904,Loft_GuideG2V0                                              ,JSX ,08-10-2010 ,"V5R20 SP5 - LOFT G2 on guide : Actif R211 (v6r2012) ")
CGMVersionMacroDefine(3905,Loft_ProfileG2V0                                            ,JSX ,08-10-2010 ,"V5R20 SP5 - Loft G2 on Profile : Actif R211 (v6r2012) ")
CGMVersionMacroDefine(3906,SurSurTg_BisectorSurfCheck                                  ,MNJ ,08-10-2010 ,"V5R20 SP5 - modeles Acis ")
CGMVersionMacroDefine(3907,Fillet_AvoidFillAtPointedEnd                                ,RR  ,08-10-2010 ,"V5R20 SP5 - performances improvement ")
CGMVersionMacroDefine(3908,Fillet_AnalyticalFill                                       ,RR  ,08-10-2010 ,"V5R20 SP5 - performances improvement ")
CGMVersionMacroDefine(3909,Thick_ConvergenceForHomotopy                                ,MNJ ,08-10-2010 ,"V5R20 SP5 - modeles Acis ") // activation immediate le 08-10-2010
CGMVersionMacroDefine(3910,SystemXY_HyperbolicSingularity_NullInCorner                 ,KJD ,08-10-2010 ,"V5R20 SP5 - RI à tiroir ")
CGMVersionMacroDefine(3911,Parallel_GetGapMaxFix                                       ,REN ,08-10-2010 ,"V5R20 SP5 - RI070922 ")
CGMVersionMacroDefine(3912,MultiVolume_SeparationDisconnectPosition                    ,LD2 ,08-10-2010 ,"V5R20 SP5 - Dev FastRun ")
CGMVersionMacroDefine(3913,IntersectionCrvSur_CleverSamplingTabCyl                     ,STY ,08-10-2010 ,"V5R20 SP5 - ri ")
CGMVersionMacroDefine(3914,Sweep_MovingFrame_ProjectionPseudoOrthoV3                   ,NLD ,15-10-2010 ,"V5R20 SP5 ")
CGMVersionMacroDefine(3915,Fillet_TriTangent_MultiRibbon                               ,JQS ,15-10-2010 ,"V5R20 SP5 - Dev ") // Allow TriTangent MultiRibbon processing
CGMVersionMacroDefine(3916,SurSurWithInits_ParametricDistortionFactor                  ,MNJ ,15-10-2010 ,"V5R20 SP5 - modeles Acis ")
CGMVersionMacroDefine(3917,Homotopy3Sur_ParametricDistortionFactor                     ,MNJ ,15-10-2010 ,"V5R20 SP5 - modeles Acis ")
CGMVersionMacroDefine(3918,Thick_PerfosLevel18                                         ,ZUT ,15-10-2010 ,"V5R20 SP5 - RI ") // -cr IR-063629V6R2012WIM
CGMVersionMacroDefine(3919,PtSurTabCyl_PEllipseCut                                     ,DAD ,22-10-2010 ,"V5R20 SP5 - IR 069714, cut ellipse on axes before minimize to avoid problems with too flat ellipses ") // -cr IR-069714V6R2012WIM IR-069714V5R21WIM IR-069714V6R2011xWIM IR-069714V5R20WIM
CGMVersionMacroDefine(3920,BlendVertex_IR047316                                        ,ZUS ,22-10-2010 ,"V5R20 SP5 - IR ") // -cr IR-047316V5R20WIM IR-047316V5R21WIM IR-047316V6R2011xWIM IR-047316V6R2011WIM IR-047316V6R2012WIM
CGMVersionMacroDefine(3921,NoInfoOnUniqueAncestorEdge                                  ,RAQ ,22-10-2010 ,"V5R20 SP5 - Versionning of Imagine & Shape subdivision journal ")
CGMVersionMacroDefine(3922,Thick_SingularTrickyFaces                                   ,MNJ ,22-10-2010 ,"V5R20 SP5 - Hull models ") // activation immédiate le 22-10-2010
CGMVersionMacroDefine(3923,TrimShell_SeparatePositionAndSelection                      ,LD2 ,22-10-2010 ,"V5R20 SP5 - Dev, prereq Fast Run ")
CGMVersionMacroDefine(3924,Relim_CylinderRebuild                                       ,PRL ,22-10-2010 ,"V5R20 SP5 - Dev ")
CGMVersionMacroDefine(3925,Sweep_OptimGetEdgeRank                                      ,NLD ,29-10-2010 ,"V5R20 SP5 ")
CGMVersionMacroDefine(3926,Simplify_For_ManifoldGroup                                  ,EYL ,29-10-2010 ,"V5R20 SP5 - Dev ")
CGMVersionMacroDefine(3927,RemoveFace_RobustnessLevel18                                ,ZUT ,29-10-2010 ,"V5R20 SP5 - RI ") // -cr IR-073314V5R20WIM IR-073314V5R21WIM IR-073314V6R2012WIM IR-075160V6R2012WIM
CGMVersionMacroDefine(3928,Thick_EvalDirSurfVolSideGuess                               ,ZUT ,29-10-2010 ,"V5R20 SP5 - RI ") // -cr IR-063629V6R2012WIM
CGMVersionMacroDefine(3929,Boolean_SuppressNoTrackIV                                   ,JHN ,05-11-2010 ,"V5R20 SP5 - RI ") // -cr IR-069295V5R21WIM IR-069295V6R2012WIM
CGMVersionMacroDefine(3930,PCurvesOffset_SurfaceReuseStabilization                     ,ZFC ,05-11-2010 ,"V5R20 SP5 - Code stabilization ")
CGMVersionMacroDefine(3931,Thick_SurParamOffsetOfOffset                                ,ZFC ,05-11-2010 ,"V5R20 SP5 - IR ") // -cr IR-051415V6R2012WIM
CGMVersionMacroDefine(3932,CltMatch_CurNull                                            ,MWE ,05-11-2010 ,"V5R20 SP5 - RI 74106 ")
CGMVersionMacroDefine(3933,Thick_PcPcSmoothConfigFullTest                              ,MNJ ,05-11-2010 ,"V5R20 SP5 - stabilite fast update ")
CGMVersionMacroDefine(3934,Sweep_FillTwistV4                                           ,NLD ,05-11-2010 ,"V5R20 SP5 ") // IR-077306V6R2012WIM
CGMVersionMacroDefine(3935,Fillet_SupContactBuffer                                     ,RR  ,05-11-2010 ,"V5R20 SP5 - Ribbon Performances Improvement ")
CGMVersionMacroDefine(3936,Sweep_CanonicCaseOnCanonicReferenceV3                       ,NLD ,05-11-2010 ,"V5R20 SP5 ") // -cr IR-077306V6R2012WIM
CGMVersionMacroDefine(3937,IVwithReportToDelete                                        ,WQO ,05-11-2010 ,"V5R20 SP5 - Fix ")
CGMVersionMacroDefine(3938,No_Automatic_Touch_On_OuterLoop                             ,tcx ,05-11-2010 ,"V5R20 SP5 - PCS ") // Topological SmartDuplication management
CGMVersionMacroDefine(3939,ValidSkinBeyondEdge_New                                     ,LD2 ,05-11-2010 ,"V5R20 SP5 - Dev ")
CGMVersionMacroDefine(3940,TranferSharpnessData_Clever                                 ,LD2 ,05-11-2010 ,"V5R20 SP5 - Dev, prereq Fast Run ")
CGMVersionMacroDefine(3941,Torus_IsConfused                                            ,PKC ,05-11-2010 ,"V5R20 SP5 - bug ")
CGMVersionMacroDefine(3942,Fillet_FaceFaceTriTangentMinimalPropagation                 ,JQS ,12-11-2010 ,"V5R20 SP5 - Dev ") // Allow Face/Face and TriTangent Fillet to provide result with minimal propagation
CGMVersionMacroDefine(3943,StylingFilletJournalTrimmedEdges                            ,MWE ,12-11-2010 ,"V5R20 SP5 - RI 077618 ")
CGMVersionMacroDefine(3944,Canonical_Plane_Cylinder_Fillet                             ,UVC ,12-11-2010 ,"V5R20 SP5 - Performance ") // Canonical Connect Project - Plane - Cylinder case
CGMVersionMacroDefine(3945,IdenticalSurSur_IsContainingTest                            ,PKC ,12-11-2010 ,"V5R20 SP5 - dev ")
CGMVersionMacroDefine(3946,TrimArchitecture2                                           ,LD2 ,12-11-2010 ,"V5R20 SP5 - Dev, separation Create et Run pour TrimShellWithKeepRemove et WirePositioning ")
CGMVersionMacroDefine(3947,Revol_ProfileExtrapoleEschewGarbageDistanceEstimate         ,dlp ,19-11-2010 ,"V5R20 SP5 - RI ") // -cr IR-069619V5R21
CGMVersionMacroDefine(3948,CannotSplitBarByUnknownConnector                            ,WQO ,19-11-2010 ,"V5R20 SP5 - Fix ")
CGMVersionMacroDefine(3949,Regul_R20SP5                                                ,MNJ ,19-11-2010 ,"V5R20 SP5 - corrections vieux bugs ") // activation immediate le 19-11-2010
CGMVersionMacroDefine(3950,GeomFe_PolygonalMailleur2D                                  ,MPS ,19-11-2010 ,"V5R20 SP5 - packaging ACIS V6 passage au mailleur de PolyGonalTools ")
CGMVersionMacroDefine(3951,CATIntersectionSurSur_SphereCylinder                        ,STY ,19-11-2010 ,"V5R20 SP5 - stabilization ")
CGMVersionMacroDefine(3952,TrimShell_CorrectJournal                                    ,LD2 ,19-11-2010 ,"V5R20 SP5 - Dev ")
CGMVersionMacroDefine(3953,ThickWireMaintenance_V6R2012                                ,ST5 ,19-11-2010 ,"V5R20 SP5 - RI ") // -cr	IR-057885V6R2011xWIM, IR-057885V6R2012WIM
CGMVersionMacroDefine(3954,Sweep_ExtrapolateSingleFaceLimits                           ,dlp ,19-11-2010 ,"V5R20 SP5 - Dev ") // Change in behaviour for both Prism and Revol
CGMVersionMacroDefine(3955,IMA_IR078509                                                ,RBD ,26-11-2010 ,"V5R20 SP5 - RI ") // -cr IR-078509V5R21WIM,   CGMTest_SurfacicStoMeshTopoOperators_Primitive*
CGMVersionMacroDefine(3956,Parallel_WrongGeoSolDetection                               ,REN ,26-11-2010 ,"V5R20 SP5 - RI 78283 & old RI (653164) ")
CGMVersionMacroDefine(3957,Fillet_FaceFace_MultiRibbon_DoubleIntPtFix                  ,JQS ,26-11-2010 ,"V5R20 SP5 - Dev ") // Configuration that results in a double self-intersection point
CGMVersionMacroDefine(3958,TrimShell_FaceOrder                                         ,LD2 ,26-11-2010 ,"V5R20 SP5 - Dev ")
CGMVersionMacroDefine(3959,Thick_InitMatterRelOriKeepMultiBrokenEdges                  ,MNJ ,26-11-2010 ,"V5R20 SP5 - RI MNT ") // activation immediate le 26/11/2010
CGMVersionMacroDefine(3960,Project_Snapping                                            ,JHN ,26-11-2010 ,"V5R20 SP5 - RI ") // -cr IR-076179V5R21WIM IR-076179V5R20WIM IR-076179V6R2012WIM
CGMVersionMacroDefine(3961,Extrude_Relimitation_MultipleProfile                        ,FDS ,03-12-2010 ,"V5R20 SP5 - Performance optimization for multi profile ") // Performance optimization for multi profile
CGMVersionMacroDefine(3962,RibbonHomotopy_NonAdjacentFaces                             ,ZUS ,03-12-2010 ,"V5R20 SP5 - Fillet Initialisation Performances Improvement ")
CGMVersionMacroDefine(3963,ProjCrvSur_HandleOffsetNonDir                               ,DAD ,03-12-2010 ,"V5R20 SP5 - HandleOffsetSurface is only for non directional projec tion ")
CGMVersionMacroDefine(3964,Regul_G1G1ConstraintCompatibilityCheck                      ,MNJ ,03-12-2010 ,"V5R20 SP5 - convergence pour correction geo ") // activation immediate le 03/12/2010
//CGMVersionMacroDefine(3965,Revol_ProfileOnAxis                                         ,JHN ,03-12-2010 ,"V5R20 SP5 - Dev ") // New development on revolve contextual limits where profile touches axis
CGMVersionMacroDefine(3966,MaxOffset_GenericFilletNature                               ,KJD ,03-12-2010 ,"V5R20 SP5 - Dev ")
CGMVersionMacroDefine(3967,SkinExtrapol_ApproximateERepLevel7                          ,ZUT ,03-12-2010 ,"V5R20 SP5 - Robustesse SkinExtrapol ")
CGMVersionMacroDefine(3968,Healing_Level31                                             ,JJC ,10-12-2010 ,"V5R20 SP5 - RI073271 ") // -cr RI073271
CGMVersionMacroDefine(3969,Thick_VariableFilletPartialDegeneracy                       ,MNJ ,10-12-2010 ,"V5R20 SP5 - dev Regul Drop V ")
CGMVersionMacroDefine(3970,SurSurWithInits_SearchForIsoparPLineSol                     ,MNJ ,10-12-2010 ,"V5R20 SP5 - stabilite robustesse ")
CGMVersionMacroDefine(3971,StylingFilletImproveConnections                             ,MWE ,17-12-2010 ,"V5R20 SP5 - Dev PSA ")
//CGMVersionMacroDefine(3972,HLR_PrecisePositionPtFace                                   ,NG4 ,17-12-2010 ,"V5R20 SP5 - RI ") // -cr IR-078176V5R20WIM IR-078176V5R21WIM IR-078176V6R2012WIM
CGMVersionMacroDefine(3973,SimilarCurve_NonSymmetricalConstraints                      ,JSX ,17-12-2010 ,"V5R20 SP5 - LOFT G2 on guide : Free G1/G2 on G0 Guide, when the other is G1/G2 ")
CGMVersionMacroDefine(3974,DevProjWire_ReduceNewtonDomainOnMaxIter                     ,JSX ,17-12-2010 ,"V5R20 SP5 - RI 84096 Michelin Wire DevProj ") // -cr IR-084096V5R20WIM
//CGMVersionMacroDefine(3975,FaceAnalyzer_Supports_GeoMode                               ,ZUS ,17-12-2010 ,"V5R20 SP5 - Dev ")
CGMVersionMacroDefine(3976,BodyAxisSystem_CreateOrigin_SharedVertex                    ,TCX ,17-12-2010 ,"V5R20 SP5 - IR ") // FGM_1
CGMVersionMacroDefine(3977,RelByVol_FaceOrder                                          ,LD2 ,17-12-2010 ,"V5R20 SP5 - Dev, prereq Fast Run ")
CGMVersionMacroDefine(3978,Sweep_SpineData_StabilizeSpineForLinearProfiles_3           ,JSX ,17-12-2010 ,"V5R20 SP5 - RI 87917 ") // -cr IR-087917V5R20WIM IR-087917V5R21WIM IR-087917V6R2012WIM
CGMVersionMacroDefine(3979,CGMR20SP5HF1                                                ,RHA ,17-12-2010 ,"V5R20 SP5 ")
CGMVersionMacroDefine(3980,CGMR20SP5HF2                                                ,RHA ,17-12-2010 ,"V5R20 SP5 ")
CGMVersionMacroDefine(3981,CGMR20SP5HF3                                                ,RHA ,17-12-2010 ,"V5R20 SP5 ")
CGMVersionMacroDefine(3982,CGMR20SP5HF4                                                ,RHA ,17-12-2010 ,"V5R20 SP5 ")
CGMVersionMacroDefine(3983,CGMR20SP5HF5                                                ,RHA ,17-12-2010 ,"V5R20 SP5 ")
CGMVersionMacroDefine(3984,CGMR20SP5HF6                                                ,RHA ,17-12-2010 ,"V5R20 SP5 ")
CGMVersionMacroDefine(3985,CGMR20SP5HF7                                                ,RHA ,17-12-2010 ,"V5R20 SP5 ")
CGMVersionMacroDefine(3986,CGMR20SP5HF8                                                ,RHA ,17-12-2010 ,"V5R20 SP5 ")
CGMVersionMacroDefine(3987,CGMR20SP5HF9                                                ,RHA ,17-12-2010 ,"V5R20 SP5 ")
CGMVersionMacroDefine(3988,CGMR20SP5HF10                                               ,RHA ,17-12-2010 ,"V5R20 SP5 ")


//=========================================================================================================
// V5R20 SP6
//=========================================================================================================
CGMVersionMacroDefine(3989,Fillet_R20SP6                                               ,RR  ,22-12-2010 ,"V5R20 SP6 - Fillet Maintenance ")
CGMVersionMacroDefine(3990,Sweep_FillTwistV5                                           ,NLD ,07-01-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(3991,Revol_ExtendSameLimits                                      ,dlp ,07-01-2011 ,"V5R20 SP6 - ODT ") // Stability of results for CGMTest_RevolTwiceContextual
CGMVersionMacroDefine(3992,FaceAnalyzer_Supports_GeoMode                               ,ZUS ,07-01-2011 ,"V5R20 SP6 - Dev ")
CGMVersionMacroDefine(3993,Boolean_NewFillSkinGroup                                    ,LD2 ,07-01-2011 ,"V5R20 SP6 - Dev ")
CGMVersionMacroDefine(3994,RemoveFace_RobustnessLevel19                                ,ZUT ,07-01-2011 ,"V5R20 SP6 - RI 067532 MustFix ") // -cr IR-067532V6R2012WIM
CGMVersionMacroDefine(3995,Thick_StabilizationLevel2                                   ,ZUT ,07-01-2011 ,"V5R20 SP6 - Stabilisation pour FixPartFastRun ")
CGMVersionMacroDefine(3996,Sweep_ExtrapolLawV3                                         ,NLD ,14-01-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(3997,HLR_FixResolutionForOcclusions                              ,NG4 ,14-01-2011 ,"V5R20 SP6 - Dev ") // Occlusion detection fixed (resolution value well computed)
CGMVersionMacroDefine(3998,MultiForm_ReparamForC1                                      ,JSX ,14-01-2011 ,"V5R20 SP6 - bug ")
CGMVersionMacroDefine(3999,SystemXYs_IntervalNewton_InclusionRelaxation                ,KJD ,14-01-2011 ,"V5R20 SP6 - RI ") // -cr 0642514V6R2012WIM 0642514V5R21WIM D0642514WIM
CGMVersionMacroDefine(4000,HLR_PrecisePositionPtFace                                   ,NG4 ,14-01-2001 ,"V5R20 SP6 - RI ") // -cr IR-078176V5R20WIM IR-078176V5R21WIM IR-078176V6R2012WIM
CGMVersionMacroDefine(4001,KeepIVForDestroyImpasse                                     ,LD2 ,14-01-2011 ,"V5R20 SP6 - Dev, symmetric impasse treatement ")
CGMVersionMacroDefine(4002,HLR_HidingInnerEdgeRobustness                               ,DPS ,14-01-2011 ,"V5R20 SP6 - robustesse du code de visibilite pour toute edge cachee par une InnerEdge ") // -cr IR-088782V6R2012WIM IR-088782V5R21WIM
CGMVersionMacroDefine(4003,Fillet_SelfIntersect_ExtrapolIfCandidate                    ,RR  ,21-01-2011 ,"V5R20 SP6 - RI080476 ")
CGMVersionMacroDefine(4004,ParamOpStabilitySolve4NoIntVtx                              ,KTU ,21-01-2011 ,"V5R20 SP6 - Robustesse du calcul dans les  cas sans vertex interieurs ")
CGMVersionMacroDefine(4005,Canonical_Chamfer                                           ,XMH ,21-01-2011 ,"V5R20 SP6 - Performance ")
CGMVersionMacroDefine(4006,PCurvesOffset_SurfaceReuseDuplicateFix                      ,ZFC ,21-01-2011 ,"V5R20 SP6 - Correction bug Bend Design ")
CGMVersionMacroDefine(4007,Sweep_Marching_CheckImposedParam                            ,JSX ,21-01-2011 ,"V5R20 SP6 - RI 81541 ") // -cr IR-081541V6R2012WIM IR-081541V5R21WIM
CGMVersionMacroDefine(4008,Sweep_ParallelToPlaneMF_V1                                  ,NLD ,28-01-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4009,SkinExtrapol_ApproximateERepLevel8                          ,ZUT ,28-01-2011 ,"V5R20 SP6 - RI ") // -cr IR-086855V6R2012WIM
CGMVersionMacroDefine(4010,SaveLowerDimInAbsorption2                                   ,LD2 ,28-01-2011 ,"V5R20 SP6 - Dev ")
CGMVersionMacroDefine(4011,FastIntersectionCrvCrv_SmallCrv                             ,sty ,28-01-2011 ,"V5R20 SP6 - RI Reg ")
//CGMVersionMacroDefine(4012,Revol_ProfileOnAxis                                         ,JHN ,28-01-2011 ,"V5R20 SP6 - Dev ") // New development on revolve contextual limits where profile touches axis
CGMVersionMacroDefine(4013,Boolean_DontIncreaseBoxUVinModel                            ,WQO ,04-02-2011 ,"V5R20 SP6 - Bug grossissant les box UV directement dans le model ")
//CGMVersionMacroDefine(4014,Revol_FullRevolutionWithoutShift                            ,dlp ,04-02-2011 ,"V5R20 SP6 - Dev ") // Suppression of 0.5 radian alteration
CGMVersionMacroDefine(4015,Fillet_WideHomotopicInit                                    ,RR  ,04-02-2011 ,"V5R20 SP6 - Fillet Initialisation Performances Improvement ")
CGMVersionMacroDefine(4016,General_Perfo_R20SP6                                        ,FDS ,04-02-2011 ,"V5R20 SP6 - Performance V5R20SP6 ")
CGMVersionMacroDefine(4017,UnfoldTransfer_NonConnexFix                                 ,s9l ,04-02-2011 ,"V5R20 SP6 - IR ")
//CGMVersionMacroDefine(4018,FilletExternalLaw_NewApprox                                 ,SOU ,04-02-2011 ,"V5R20 SP6 - RI ") // fix for IR-071059V5R21
CGMVersionMacroDefine(4019,Sweep_XScaleR20SP6                                          ,NLD ,04-02-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4020,ParallelMaintenance_IR081371_R20SP6                         ,st5 ,11-02-2011 ,"V5R20 SP6 - IR ") // -cr IR-081371V6R2012WIM, 	IR-081371V6R2012xWIM, IR-081371V5R21WIM
CGMVersionMacroDefine(4021,Projection_ConcatenDegenerated                              ,JHN ,11-02-2011 ,"V5R20 SP6 - RI ") // -cr IR-078085V5R20WIM IR-078085V5R21WIM IR-078085V6R2012WIM IR-078085V6R2012xWIM
CGMVersionMacroDefine(4022,Trim_RelocateOperatorActions                                ,dlp ,11-02-2011 ,"V5R20 SP6 - Dev ") // Correction of replay generation for split etc.
CGMVersionMacroDefine(4023,Sweep_SpecialC0ComputationWithCurvature                     ,NLD ,18-02-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4024,Revol_ProfileOnAxis                                         ,JHN ,18-02-2011 ,"V5R20 SP6 - Dev ") // New development on revolve contextual limits where profile touches axis
CGMVersionMacroDefine(4025,Thick_SymmetryzationLevel6                                  ,MNJ ,18-02-2011 ,"V5R20 SP6 - RI TMC ") // activation immediate le 18-02-2011
CGMVersionMacroDefine(4026,FaceAnalyzer_FacesSupports_AllModes                         ,ZUS ,18-02-2011 ,"V5R20 SP6 - RI ")
CGMVersionMacroDefine(4027,StylingFilletSequence                                       ,MWE ,18-02-2011 ,"V5R20 SP6 - RI 041715 ")
CGMVersionMacroDefine(4028,Fillet_VertexRibbonOrder                                    ,jqs ,18-02-2011 ,"V5R20 SP6 - Dev ")
CGMVersionMacroDefine(4029,RemoveFace_ExtrapolLengthComputationLevel2                  ,ZUT ,18-02-2011 ,"V5R20 SP6 - RI ") // -cr IR-071807V6R2012WIM IR-071807V6R2012xWIM
CGMVersionMacroDefine(4030,Boolean_RI080633                                            ,WQO ,18-02-2011 ,"V5R20 SP6 - RI080633 ") // -cr IR-080633V5R21WIM IR-080633V6R2012WIM IR-080633V6R2012xWIM
CGMVersionMacroDefine(4031,MatchInsideMaxLimits                                        ,MWE ,25-02-2011 ,"V5R20 SP6 - RI 64695 ")
CGMVersionMacroDefine(4032,ReflectCurve_SeamStabilization                              ,D1A ,25-02-2011 ,"V5R20 SP6 - RI ") // -cr IR-084240V5R21WIM IR-084240V5R20WIM IR-084240V5R2012WIM
CGMVersionMacroDefine(4033,EdgeCurveOffset_NonIsoParamCorrectRef                       ,MNJ ,25-02-2011 ,"V5R20 SP6 - RI ") // activation immediate le 25/02/2011
CGMVersionMacroDefine(4034,Boolean_StabilizationsForSimplify                           ,WQO ,25-02-2011 ,"V5R20 SP6 - Fast Update convergence ")
CGMVersionMacroDefine(4035,InterSkin_SolveDiff_BetterError                             ,LD2 ,25-02-2011 ,"V5R20 SP6 - RI ") // -cr IR-091475V6R2012WIM IR-091475V5R21WIM IR-091475V5R20WIM IR-091475V6R2012xWIM
CGMVersionMacroDefine(4036,WarningOnNonManifoldEdges                                   ,LD2 ,25-02-2011 ,"V5R20 SP6 - RI ") // -cr IR-095704V5R21WIM IR-095704V5R20WIM IR-095704V6R2012xWIM IR-095704V6R2012WIM
CGMVersionMacroDefine(4037,RemoveEdge_RobustnessLevel2                                 ,ZUT ,25-02-2011 ,"V5R20 SP6 - RI ") // -cr IR-085654V6R2012WIM IR-085654V6R2012xWIM
CGMVersionMacroDefine(4038,Boolean_DuplicateOnVertex                                   ,JHN ,25-02-2011 ,"V5R20 SP6 - RI ") // -cr IR-094070V5R21WIM IR-094070V6R2012WIM IR-094070V5R20WIM IR-094070V6R2012xWIM
CGMVersionMacroDefine(4039,Intersect_WarningObject                                     ,JHN ,25-02-2011 ,"V5R20 SP6 - RI ") // _cr IR-096181V5R21WIM IR-096181V6R2012WIM IR-096181V6R2012xWIM
CGMVersionMacroDefine(4040,StylingFilletForceCreationAnyway                            ,MWE ,04-03-2011 ,"V5R20 SP6 - Dev PSA ")
CGMVersionMacroDefine(4042,Thick_ConfLinERepSimplif                                    ,MNJ ,04-03-2011 ,"V5R20 SP6 - RI MNT ") // activation immediate le 04-03-2011
CGMVersionMacroDefine(4043,Sweep_AvoidInternalFace                                     ,dlp ,04-03-2011 ,"V5R20 SP6 - RI 073580 ")
CGMVersionMacroDefine(4044,ProgressBarInBooleanOperator                                ,OID ,04-03-2011 ,"V5R20 SP6 - Migration de l\'interrupt du booleen sur l\'interrupt avec ProgressBar ")
CGMVersionMacroDefine(4045,RemoveFace_UntouchedFacesPreventiveImport                   ,ZUT ,04-03-2011 ,"V5R20 SP6 - RI ") // -cr IR-085379V6R2012WIM IR-085379V6R2012xWIM
CGMVersionMacroDefine(4046,HomoptCrvSur_PlanLevel3                                     ,ZUT ,04-03-2011 ,"V5R20 SP6 - RI ") // Demande ZFC
CGMVersionMacroDefine(4047,Boolean_ErrorInPropagDegenerateVertex                       ,JHN ,04-03-2011 ,"V5R20 SP6 - RI ") // -cr IR-093752V5R20WIM IR-093752V5R21WIM IR-093752V6R2012WIM IR-093752V6R2012xWIM
CGMVersionMacroDefine(4048,Boolean_SmoothVertex                                        ,JHN ,04-03-2011 ,"V5R20 SP6 - RI ") // demande ZFC
CGMVersionMacroDefine(4049,Boolean_GarbageUsed                                         ,JHN ,04-03-2011 ,"V5R20 SP6 - RI ") // -cr IR-085436V6R2012WIM IR-085436V5R21WIM IR-085436V6R2012xWIM
CGMVersionMacroDefine(4050,Boolean_EdgeCurveRepair                                     ,JHN ,04-03-2011 ,"V5R20 SP6 - RI externe ") // -cr IR-091897V5R21WIM IR-091897V6R2012WIM IR-091897V5R20WIM IR-091897V6R2012xWIM
CGMVersionMacroDefine(4051,CGMR211HF1                                                  ,RHA ,04-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4052,CGMR211HF2                                                  ,RHA ,04-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4053,CGMR211HF3                                                  ,RHA ,04-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4054,CGMR211HF4                                                  ,RHA ,04-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4055,CGMR211HF5                                                  ,RHA ,04-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4056,CGMR211HF6                                                  ,RHA ,04-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4057,CGMR211HF7                                                  ,RHA ,04-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4058,CGMR211HF8                                                  ,RHA ,04-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4059,CGMR211HF9                                                  ,RHA ,04-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4060,CGMR211HF10                                                 ,RHA ,04-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4061,AutoBase_FixForGeoTrackFollower                             ,EYL ,11-03-2011 ,"V5R20 SP6 - dev ")
CGMVersionMacroDefine(4062,ParallelRibbonMaintenance_R21SP1                            ,ST5 ,11-03-2011 ,"V5R20 SP6 - IR ") // -cr IR-076015V6R2012WIM, IR-076015V6R2012xWIM
//CGMVersionMacroDefine(4063,InterTopo_EdgeReportByCuttings                              ,LD2 ,11-03-2011 ,"V5R20 SP6 - Dev ")
CGMVersionMacroDefine(4064,Manifolder_IR091447_Edge                                    ,WQO ,11-03-2011 ,"V5R20 SP6 - RI CD dans le Manifolder ") // -cr IR-091447V5R20WIM IR-091447V5R21WIM IR-091447V6R2012WIM IR-091447V6R2012xWIM
CGMVersionMacroDefine(4065,TopOperator_UseLocalJournalInMasterJournal                  ,KY1 ,11-03-2011 ,"V5R20 SP6 - Dev ") // Allow creation of local journal for a topological operator and insertion of this latter in the master journal at the end of run
CGMVersionMacroDefine(4066,SewSkin_ManageTouched                                       ,JHN ,11-03-2011 ,"V5R20 SP6 - RI ") // -cr IR-096768V5R20WIM IR-096768V6R2012xWIM IR-096768V6R2012WIM IR-096768V5R21WIM
CGMVersionMacroDefine(4067,Extrude_NoECSharing_ClosedProfile                           ,dlp ,11-03-2011 ,"V5R20 SP6 - RI ") // IR 097692
CGMVersionMacroDefine(4068,Sweep_UseLocalJournalInMasterJournal                        ,NLD ,18-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4069,Sweep_DeploySoftwareConfigurationV10                        ,NLD ,18-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4070,Sweep_EllipseExtrapolationOnClosure                         ,NLD ,18-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4071,Fillet_EvalRadiusAtPoint                                    ,ZUS ,18-03-2011 ,"V5R20 SP6 - Dev ")
CGMVersionMacroDefine(4072,SimilarCurve_Topo_NearestStarPoint                          ,JSX ,25-03-2011 ,"V5R20 SP6 - RI 100029 ") // -cr IR-100029V5R21WIM IR-100029V6R2012xWIM
CGMVersionMacroDefine(4073,LayDownMarching_PoleReconvergence                           ,DAD ,25-03-2011 ,"V5R20 SP6 - IR 066202; reconverge the predicted point when it is on a pole ") // -cr IR-066202V6R2012xWIM
//CGMVersionMacroDefine(4074,DestroyUselessIV                                            ,JHN ,25-03-2011 ,"V5R20 SP6 - RI ") // -cr IR-101271V5R20WIM IR-101271V5R21WIM IR-101271V6R2012xWIM
CGMVersionMacroDefine(4080,CGMR20SP6HF1                                                ,RHA ,25-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4081,CGMR20SP6HF2                                                ,RHA ,25-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4082,CGMR20SP6HF3                                                ,RHA ,25-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4083,CGMR20SP6HF4                                                ,RHA ,25-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4084,CGMR20SP6HF5                                                ,RHA ,25-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4085,CGMR20SP6HF6                                                ,RHA ,25-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4086,CGMR20SP6HF7                                                ,RHA ,25-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4087,CGMR20SP6HF8                                                ,RHA ,25-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4088,CGMR20SP6HF9                                                ,RHA ,25-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4089,CGMR20SP6HF10                                               ,RHA ,25-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4090,CGMR21HF1                                                   ,RHA ,25-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4091,CGMR21HF2                                                   ,RHA ,25-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4092,CGMR21HF3                                                   ,RHA ,25-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4093,CGMR21HF4                                                   ,RHA ,25-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4094,CGMR21HF5                                                   ,RHA ,25-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4095,CGMR21HF6                                                   ,RHA ,25-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4096,CGMR21HF7                                                   ,RHA ,25-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4097,CGMR21HF8                                                   ,RHA ,25-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4098,CGMR21HF9                                                   ,RHA ,25-03-2011 ,"V5R20 SP6 ")
CGMVersionMacroDefine(4099,CGMR21HF10                                                  ,RHA ,25-03-2011 ,"V5R20 SP6 ")


//=========================================================================================================
// V5R21 SP1
//=========================================================================================================
CGMVersionMacroDefine(4100,Sweep_ImplicitSpine_XScaleNonIsoV3                          ,NLD ,01-04-2010 ,"V5R21 SP1 ")
CGMVersionMacroDefine(4101,Sweep_XScaleR20SP7                                          ,NLD ,01-04-2010 ,"V5R21 SP1 ")
CGMVersionMacroDefine(4102,General_Perfo_R21SP1                                        ,FDS ,01-04-2011 ,"V5R21 SP1 ")
CGMVersionMacroDefine(4103,Fill_WireMultiDomain                                        ,MPS ,01-04-2011 ,"V5R21 SP1 - RI  102301 ") // -cr  IR-102301V5R20WIM   IR-102301V5R21WIM  IR-102301V6R2012xWIM
CGMVersionMacroDefine(4104,TopHeal_R21SP1                                              ,PRL ,01-04-2011 ,"V5R21 SP1 - Dev ")
CGMVersionMacroDefine(4105,Fillet_TTMR_IntRibMultiPieces                               ,JQS ,01-04-2011 ,"V5R21 SP1 - Dev ")
CGMVersionMacroDefine(4106,RemoveEdge_RobustnessLevel3                                 ,ZUT ,01-04-2011 ,"V5R21 SP1 - Robustesse RemoveEdge sur modeles SWx ")
CGMVersionMacroDefine(4107,ThickWireMaintenance_V5R21SP1                               ,ST5 ,08-04-2011 ,"V5R21 SP1 - Convergence ") // Phase1 <-> Phase2
CGMVersionMacroDefine(4108,Sweep_DeploySoftwareConfigurationV11                        ,NLD ,08-04-2011 ,"V5R21 SP1 ")
CGMVersionMacroDefine(4109,SurfaceToCanonic_R20SP7Stabilization                        ,NLD ,08-04-2011 ,"V5R21 SP1 ")
CGMVersionMacroDefine(4110,Prism_ExtendRestartEstimation                               ,dlp ,08-04-2011 ,"V5R21 SP1 - Dev ")
CGMVersionMacroDefine(4111,Sweep_ExtendMultiProfile                                    ,dlp ,08-04-2011 ,"V5R21 SP1 - Dev ") // IR 102651
CGMVersionMacroDefine(4112,Thick_FilterStillConfLinERep                                ,MNJ ,08-04-2011 ,"V5R21 SP1 - RI MNT ") // activation immediate le 08-04-2011
CGMVersionMacroDefine(4113,Boolean_ErrorIS                                             ,JHN ,08-04-2011 ,"V5R21 SP1 - RI ") // -cr IR-103129V5R21WIM IR-103129V6R2012xWIM
CGMVersionMacroDefine(4114,FilletExternalLaw_NewApprox                                 ,SOU ,08-04-2011 ,"V5R21 SP1 - RI ")
CGMVersionMacroDefine(4115,Manifolder_IR091447_Vertex                                  ,WQO ,08-04-2011 ,"V5R21 SP1 - Suite de Manifolder_IR091447_Edge ")
CGMVersionMacroDefine(4116,InterTopo_EdgeReportByCuttings                              ,LD2 ,08-04-2011 ,"V5R21 SP1 - Dev ")
CGMVersionMacroDefine(4117,Sweep_ExtendMultiFaceLimits                                 ,dlp ,15-04-2011 ,"V5R21 SP1 - RI ") // IR 101579
CGMVersionMacroDefine(4118,FillAnalytique_CanonicalManagement                          ,MPS ,15-04-2011 ,"V5R21 SP1 - Fill : pb de limites dans la detection des surfaces canoniques ")
CGMVersionMacroDefine(4119,Chamfer_R21SP1                                              ,rr  ,15-04-2011 ,"V5R21 SP1 - Chamfer Fixes ")
CGMVersionMacroDefine(4120,Fillet_R21SP1                                               ,RR  ,15-04-2011 ,"V5R21 SP1 - Fillet Maintenance ")
CGMVersionMacroDefine(4121,Autocheck_With_DifferenceEdges                              ,oid ,15-04-2011 ,"V5R21 SP1 - Dev ")
CGMVersionMacroDefine(4122,CXShell_KeepUsefullExtrapolation_New                        ,LD2 ,15-04-2011 ,"V5R21 SP1 - Dev Multi Trim ")
CGMVersionMacroDefine(4123,LayDownCrvSur_CleanInBorder                                 ,DAD ,15-04-2011 ,"V5R21 SP1 - IR 091627, cleaning of border curves ") // -cr IR-091627V5R21WIM IR-091627V6R2012xWIM
CGMVersionMacroDefine(4124,SurfaceToCanonic_GetAffineSpaceMigration                    ,KJD ,22-04-2011 ,"V5R21 SP1 - methode deprecated fausse ")
//CGMVersionMacroDefine(4125,Sweep_ExtrapolateSingleFaceLimits_General                   ,THM ,22-04-2011 ,"V5R21 SP1 - Dev ") // Enables single face limits to be extrapolated for general Sweep (on closed profiles)
CGMVersionMacroDefine(4126,DestroyUselessIV                                            ,JHN ,22-04-2011 ,"V5R21 SP1 - RI. ODT KO CGMReplay_CATSmFoldUnfoldStampingFacesOperator ") // -cr IR-101271V5R20WIM IR-101271V5R21WIM IR-101271V6R2012xWIM
CGMVersionMacroDefine(4127,TopCrvToNurbsCrv_UseResolutionAsInternalMinLength           ,ZIB ,29-04-2011 ,"V5R21 SP1 - Demande PSA (via shape design) ")
CGMVersionMacroDefine(4128,CornerPlan_OffsetsStabilization_R21SP1                      ,ST5 ,29-04-2011 ,"V5R21 SP1 - RI + Dev ")
//CGMVersionMacroDefine(4129,ConfCrvCrv_SymFromMid                                       ,DAD ,29-04-2011 ,"V5R21 SP1 - Symmetrization of ConfusionCrvCrv, IR 084422 ") // -cr IR-084422V6R2012xWIM IR-084422V5R21WIM ; 7 ODTs KOs au jour d\'aujourd\'hui dont 5 livrés vendredi 29-04 et 2 lundi 2-05
//CGMVersionMacroDefine(4130,GeometricValidationAutocheck                                ,OID ,29-04-2011 ,"V5R21 SP1 - Dev ")
CGMVersionMacroDefine(4131,FaceAnalyzer_JointSupports                                  ,ZUS ,29-04-2011 ,"V5R21 SP1 - IR ")
CGMVersionMacroDefine(4132,RemoveFace_RobustnessLevel20                                ,ZUT ,29-04-2011 ,"V5R21 SP1 - IR ") // -cr IR-095405V6R2012xWIM IR-095405V5R21WIM
CGMVersionMacroDefine(4133,Thick_PseudoIsoTopoFReps                                    ,MNJ ,06-05-2011 ,"V5R21 SP1 - RI ") // activation immediate le 03-05-2011
CGMVersionMacroDefine(4134,HLR_AlmostNullOrientedSFaceDetection                        ,NG4 ,06-05-2011 ,"V5R21 SP1 - RI ") // -cr IR-105690V6R2012x IR-105690V5R21
CGMVersionMacroDefine(4135,GeometricValidationAutocheck                                ,OID ,06-05-2011 ,"V5R21 SP1 - Dev ")
CGMVersionMacroDefine(4136,Regul_GroupSmoothFaces                                      ,DBS ,13-05-2011 ,"V5R21 SP1 - DEV ") // robustness of regul operator : improvement
CGMVersionMacroDefine(4137,Draft_R21SP1                                                ,SOU ,13-05-2011 ,"V5R21 SP1 - RI ")
//CGMVersionMacroDefine(4138,Fillet_CATFaceOrder                                         ,IZE ,13-05-2011 ,"V5R21 SP1 - Dev. Fast Update ")
CGMVersionMacroDefine(4139,SSBW_CorrectTables                                          ,LD2 ,13-05-2011 ,"V5R21 SP1 - Dev SplitShellByWires ")
CGMVersionMacroDefine(4140,OperationWithKeepFeature                                    ,JQS ,13-05-2011 ,"V5R21 SP1 - Dev ")
CGMVersionMacroDefine(4141,Fillet_CleanCuttings_Touched                                ,IZE ,20-05-2011 ,"V5R21 SP1 - Improvement Restore Working context (ODT Ribbons Reorder) ")
CGMVersionMacroDefine(4142,CornerMaintenance_R21SP1                                    ,ST5 ,20-05-2011 ,"V5R21 SP1 - RI ") // -cr IR-108063V5R21WIM, IR-108063V6R2012xWIM
CGMVersionMacroDefine(4143,Prism_SecondOrderDirectionCheck                             ,dlp ,20-05-2011 ,"V5R21 SP1 - IR 106957 ") // IR 106957
CGMVersionMacroDefine(4144,PersistentCell_SearchParentOfBiggerDim                      ,EYL ,20-05-2011 ,"V5R21 SP1 - RI ") // -cr IR-105910V6R2012xWIM
CGMVersionMacroDefine(4145,Fillet_BothSideTwist1                                       ,rr  ,20-05-2011 ,"V5R21 SP1 ") // Fillet Robustness
CGMVersionMacroDefine(4146,Offset_LogicalEdgeSharpnessLevel2                           ,MNJ ,20-05-2011 ,"V5R21 SP1 - RI TMC ") // activation immediate le 20-05-2011
CGMVersionMacroDefine(4147,Revol_EqualLimitFaces                                       ,dlp ,20-05-2011 ,"V5R21 SP1 - IR 103815 ") // IR 103815
CGMVersionMacroDefine(4148,Thick_LocalMaxOffsetForPartialDegenSurfs                    ,ZUT ,20-05-2011 ,"V5R21 SP1 - RI ") // -cr IR-104156V5R21WIM IR-104156V6R2012xWIM
CGMVersionMacroDefine(4149,Sweep_Discontinuity_ShuntNeighbourhoodWithRecoil            ,NLD ,27-05-2011 ,"V5R21 SP1 ") // -cr IR-107069V5R21WIM    IR-107069V6R2012xWIM
CGMVersionMacroDefine(4150,SplitShellByWires_SimplifVtx                                ,LD2 ,27-05-2011 ,"V5R21 SP1 - Dev SplitShellByWires ")
CGMVersionMacroDefine(4151,LayDown_StopMultiConfused                                   ,JHN ,27-05-2011 ,"V5R21 SP1 - RI KJD ")
//CGMVersionMacroDefine(4152,Boolean_EqualAdjacentCut                                    ,JHN ,27-05-2011 ,"V5R21 SP1 - RI ") // -cr IR-107061V5R21WIM IR-107061V6R2012xWIM
CGMVersionMacroDefine(4153,StylingFilletVariableMoreFlexible                           ,MWE ,27-05-2011 ,"V5R21 SP1 - Dev Styling Fillet Variable improvement ")
CGMVersionMacroDefine(4154,Offset_SingularPointAnomaly                                 ,MNJ ,27-05-2011 ,"V5R21 SP1 - RI ") // activation immediate le 27-05-2011
CGMVersionMacroDefine(4155,Fillet_RibbonsReorder_MixedConvexity                        ,UVC ,10-06-2011 ,"V5R21 SP1 - Enhancement ")
CGMVersionMacroDefine(4156,HLR_PreciseSilhouetteShape                                  ,NG4 ,10-06-2011 ,"V5R21 SP1 - RI ") // -cr IR-108276V5R21WIM IR-108276V6R2012xWIM
CGMVersionMacroDefine(4157,Boolean_EqualAdjacentCut                                    ,JHN ,10-06-2011 ,"V5R21 SP1 - RI ") // -cr IR-107061V5R21WIM IR-107061V6R2012xWIM
CGMVersionMacroDefine(4158,PersistentCell_CreateCellManifoldManager                    ,EYL ,10-06-2011 ,"V5R21 SP1 - Dev ")
//CGMVersionMacroDefine(4159,HybBoo_CorrectJournals                                      ,LD2 ,10-06-2011 ,"V5R21 SP1 - Dev ") // Voir mail
CGMVersionMacroDefine(4160,Fill_TwistFillAnalytique1                                   ,MPS ,17-06-2011 ,"V5R21 SP1 - IR ") // -cr IR-113130V6R2012xWIM
CGMVersionMacroDefine(4161,Fillet_BlendVertex_And_ChordLength                          ,RR  ,17-06-2011 ,"V5R21 SP1 - Maintenance ")
//CGMVersionMacroDefine(4162,Sweep_AllowTangentTransitionEdges                           ,THM ,17-06-2011 ,"V5R21 SP1 - IR 96390 ")
CGMVersionMacroDefine(4165,CGMR21SP1HF1                                                ,RHA ,17-06-2011 ,"V5R21 SP1 ")
CGMVersionMacroDefine(4166,CGMR21SP1HF2                                                ,RHA ,17-06-2011 ,"V5R21 SP1 ")
CGMVersionMacroDefine(4167,CGMR21SP1HF3                                                ,RHA ,17-06-2011 ,"V5R21 SP1 ")
CGMVersionMacroDefine(4168,CGMR21SP1HF4                                                ,RHA ,17-06-2011 ,"V5R21 SP1 ")
CGMVersionMacroDefine(4169,CGMR21SP1HF5                                                ,RHA ,17-06-2011 ,"V5R21 SP1 ")
CGMVersionMacroDefine(4170,CGMR21SP1HF6                                                ,RHA ,17-06-2011 ,"V5R21 SP1 ")
CGMVersionMacroDefine(4171,CGMR21SP1HF7                                                ,RHA ,17-06-2011 ,"V5R21 SP1 ")
CGMVersionMacroDefine(4172,CGMR21SP1HF8                                                ,RHA ,17-06-2011 ,"V5R21 SP1 ")
CGMVersionMacroDefine(4173,CGMR21SP1HF9                                                ,RHA ,17-06-2011 ,"V5R21 SP1 ")
CGMVersionMacroDefine(4174,CGMR21SP1HF10                                               ,RHA ,17-06-2011 ,"V5R21 SP1 ")


//=========================================================================================================
// V5R21 SP2
//=========================================================================================================
CGMVersionMacroDefine(4176,Blend_AvoidTwist_WarningOnBox                               ,JSX ,24-06-2011 ,"V5R21 SP2 - warning pour ri P2 ") // -cr IR-103782V5R21WIM
CGMVersionMacroDefine(4177,HybBoo_CorrectJournals                                      ,LD2 ,24-06-2011 ,"V5R21 SP2 - Dev ")
CGMVersionMacroDefine(4178,BendOperator_ConfusedSol                                    ,PKC ,24-06-2011 ,"V5R21 SP2 - RI ") // IR-086033V6R2012xWIM
CGMVersionMacroDefine(4179,SSBW_SimplifAllVertices                                     ,LD2 ,24-06-2011 ,"V5R21 SP2 - Dev SplitShellByWires ")
CGMVersionMacroDefine(4180,SurfaceSimplification_ModifJournal                          ,MPS ,01-07-2011 ,"V5R21 SP2 - Mise en conformite du journal pour CATSurfaceSimplification ")
CGMVersionMacroDefine(4181,TrimByThick_ConflictOffsetCaseBRewrite                      ,ZFC ,01-07-2011 ,"V5R21 SP2 - IR 096430 ") // -cr IR-096430V6R2012xWIM
CGMVersionMacroDefine(4182,Loft_FirstOrLastRelimitationOnSingleProfile                 ,NLD ,01-07-2011 ,"V5R21 SP2 ")
CGMVersionMacroDefine(4183,Sweep_XScaleR21SP2                                          ,NLD ,01-07-2011 ,"V5R21 SP2 ")
CGMVersionMacroDefine(4184,Sweep_Security_R21SP2                                       ,NLD ,01-07-2011 ,"V5R21 SP2 ")
CGMVersionMacroDefine(4185,Sweep_ExtrapolateReportV2                                   ,NLD ,01-07-2011 ,"V5R21 SP2 ")
CGMVersionMacroDefine(4186,Thick_CatchHomotopyError                                    ,MNJ ,01-07-2011 ,"V5R21 SP2 - RI ") // activation immediate le 01/07/2011
CGMVersionMacroDefine(4187,SurfaceSimplification_Optimization1                         ,KTU ,01-07-2011 ,"V5R21 SP2 - Dev ") // Performence improvement
CGMVersionMacroDefine(4188,Fill_TwoClosedCurveDetection                                ,MPS ,08-07-2011 ,"V5R21 SP2 - RI 116083 ") // -cr  IR-116083V6R2012xWIM IR-116083V5R22WIM IR-116083V5R21WIM
CGMVersionMacroDefine(4189,SkinExtrapol_JournalForHookingEdges                         ,ZUT ,08-07-2011 ,"V5R21 SP2 - Fix pour SWx ")
CGMVersionMacroDefine(4190,DistanceBodyBody_DistVectorAngleLimitCorrection             ,MPX ,08-07-2011 ,"V5R21 SP2 - RI ") // -cr IR-118556V5R21WIM IR-117654V5R21WIM
CGMVersionMacroDefine(4191,TwistAnalysis_Sampling                                      ,DAD ,08-07-2011 ,"V5R21 SP2 - IR 93152 ")
CGMVersionMacroDefine(4192,Draft_R21SP2                                                ,SOU ,08-07-2011 ,"V5R21 SP2 - RI ")
CGMVersionMacroDefine(4193,Chamfer_SolverAttrib                                        ,xmh ,08-07-2011 ,"V5R21 SP2 - RI109213 ") // -cr IR-106115V5R21WIM IR-106115V6R2012xWIM
CGMVersionMacroDefine(4194,Boolean_FaceConfusionHomogenize                             ,JHN ,08-07-2011 ,"V5R21 SP2 - RI ") // -cr IR-110641V5R21WIM IR-110641V6R2012xWIM
CGMVersionMacroDefine(4195,Boolean_RebuildHomogenisationTable                          ,JHN ,08-07-2011 ,"V5R21 SP2 - RI ") // -cr IR-110640V5R21WIM IR-110640V6R2012xWIM
CGMVersionMacroDefine(4196,Revol_ErasedLimitation                                      ,JHN ,08-07-2011 ,"V5R21 SP2 - RI journal inrevol for Swx ") // -cr IR-117799V6R2012xWIM
CGMVersionMacroDefine(4197,Offset_BulldozerLevel8                                      ,ZUT ,08-07-2011 ,"V5R21 SP2 - RI ") // -cr IR-118880V5R21WIM IR-118880V5R22WIM IR-118880V6R2012xWIM
CGMVersionMacroDefine(4198,CATIntersectionCrvCrv_MeanPlaneMethodFailed                 ,sty ,15-07-2011 ,"V5R21 SP2 - RI ") // -cr IR-107778V5R21WIM IR-107778V5R20WIM IR-107778V6R212xWIM
CGMVersionMacroDefine(4199,CATIntersectionSurSur_IsoparPline                           ,sty ,15-07-2011 ,"V5R21 SP2 - ri ") // -cr IR-092696V5R20WIM IR-092696V5R21WIM IR-092696V6R212xWIM 	IR-092696V6R212WIM
CGMVersionMacroDefine(4200,Fillet_SelfIntPtAtExistingVertex                            ,JQS ,22-07-2011 ,"V5R21 SP2 - Dev ") // Selfintersection not created correctly in true multi-ribbon
CGMVersionMacroDefine(4201,Fillet_RelimitationWithKeepEdge                             ,JQS ,22-07-2011 ,"V5R21 SP2 - Dev ") // Enhance relimitation for configuration with special edges
CGMVersionMacroDefine(4202,Thick_PerfosLevel20                                         ,ZUT ,22-07-2011 ,"V5R21 SP2 - RI ") // -cr IR-119639V5R21WIM IR-119639V5R22WIM IR-119639V6R2012xWIM
CGMVersionMacroDefine(4203,TopHeal_R21SP2                                              ,PRL ,22-07-2011 ,"V5R21 SP2 - Dev ")
CGMVersionMacroDefine(4204,Curve_Blend_Trim_Closed_Wire                                ,nwp ,29-07-2011 ,"V5R21 SP2 - When a closed wire is trimmed with a blend curve the result is arbitrary. ") // -cr IR-118816V5R21WIM
CGMVersionMacroDefine(4205,PowerDef_CleanWireJournal                                   ,PMG ,05-08-2011 ,"V5R21 SP2 - Correction des journaux dans l\'apply Wire ")
CGMVersionMacroDefine(4206,SurfaceSimplification_Optimization2                         ,KTU ,05-08-2011 ,"V5R21 SP2 - Dev ") // Dev
CGMVersionMacroDefine(4207,Regul_ThinFace                                              ,cwm ,12-08-2011 ,"V5R21 SP2 - Dev ") // Regularisation avec aggrandissement des faces
CGMVersionMacroDefine(4208,AutoParallel_Improvements_R21SP2                            ,REN ,12-08-2011 ,"V5R21 SP2 - Dev ")
CGMVersionMacroDefine(4209,CornerFilletBlendCurveManip                                 ,nwq ,26-08-2011 ,"V5R21 SP2 - Dev,  Mnipulator for Blend Curve Creation ") // R-0025183
CGMVersionMacroDefine(4210,PolyOffset_LimitVRepToOffsetRange                           ,DPS ,26-08-2011 ,"V5R21 SP2 - explosion de la memoire si on raffine l\'octree en dehors de la zone cible ") // -cr IR-119180V6R2012xWIM
CGMVersionMacroDefine(4211,Fillet_TMROnlyIfUnTwistFails                                ,RR  ,26-08-2011 ,"V5R21 SP2 - IR117435 ")
CGMVersionMacroDefine(4212,EuclidianParallel_ComputeInitRobustness                     ,ST5 ,26-04-2011 ,"V5R21 SP2 - Dev ") // Make sure InitPoint is valid for associated ImplicitSystem (KJD IsNull check)
CGMVersionMacroDefine(4213,Fillet_SnappingDetectionWithFaceAnalyzer                    ,RR  ,26-08-2011 ,"V5R21 SP2 - RI113633 ")
CGMVersionMacroDefine(4214,Fillet_BothSideTwist2                                       ,RR  ,26-08-2011 ,"V5R21 SP2 - RI098197 ")
CGMVersionMacroDefine(4215,SkinExtrapol_FaceDeletionReport                             ,MNJ ,26-08-2011 ,"V5R21 SP2 - RI TMC ") // activation immediate le 26-08-2011
CGMVersionMacroDefine(4216,Thick_StaplesForIsoparsOnMaxLimits                          ,ZUT ,26-08-2011 ,"V5R21 SP2 - RI ") // -cr IR-115145V5R21WIM IR-115145V6R2012xWIM
CGMVersionMacroDefine(4217,Silhouette_R2012x                                           ,DPS ,26-08-2011 ,"V5R21 SP2 - TopSilhouette evolutions ") // ReflectLineOper::FilterBorderSolution() activation etc...
CGMVersionMacroDefine(4218,Fillet_NullRadius                                           ,RR  ,26-08-2011 ,"V5R21 SP2 - RI118939 ")
CGMVersionMacroDefine(4219,FIllet_IsPointSingularCriterion                             ,xmh ,26-08-2011 ,"V5R21 SP2 - RI072259 ") // promote -cr IR-072259V5R21WIM IR-072259V6R2012xWIM
CGMVersionMacroDefine(4220,Healing_Level32                                             ,JJC ,02-09-2011 ,"V5R21 SP2 - orientation normale + poids PC ")
CGMVersionMacroDefine(4221,Offset_NoRescueIfHomotopyOK                                 ,MNJ ,02-09-2011 ,"V5R21 SP2 - RI ") // activation immediate le 02-09-2011
CGMVersionMacroDefine(4222,Fillet_R21SP2                                               ,IZE ,02-09-2011 ,"V5R21 SP2 - RI ")
CGMVersionMacroDefine(4223,Sweep_AllowTangentTransitionEdges                           ,THM ,02-09-2011 ,"V5R21 SP2 - IR 96390 ")
CGMVersionMacroDefine(4224,SmartProjection_MergeMinimals                               ,JHN ,02-09-2011 ,"V5R21 SP2 - RI ") // -cr IR-124920V5R21WIM R-124920V5R22WIM IR-124920V6R2012xWIM
CGMVersionMacroDefine(4225,RemoveFace_KeepStopHomTptIfNoRescue                         ,ZUT ,02-09-2011 ,"V5R21 SP2 - RI ") // -cr IR-114820V6R2012xWIM IR-114820V6R2013WIM
CGMVersionMacroDefine(4226,IntersectionPCrvPCrv_ConfReset                              ,DAD ,09-09-2011 ,"V5R21 SP2 - Confusion is called several times without reseting options and results ")
//CGMVersionMacroDefine(4227,ConfCrvCrv_SymFromMid                                       ,DAD ,09-09-2011 ,"V5R21 SP2 - Symmetrization of ConfusionCrvCrv, IR 084422 ") // -cr IR-084422V6R2012xWIM IR-084422V5R21WIM ; 7 ODT KOs : FixpartWarn, changement de ref et closed config à réenregistrer
CGMVersionMacroDefine(4228,BasicExtrapolBipar_DeploySoftwareConfiguration              ,JSX ,09-09-2011 ,"V5R21 SP2 - Import SW ")
CGMVersionMacroDefine(4229,PCurvesOffset_SurfaceReuseOffsetOfPlane                     ,ZFC ,09-09-2011 ,"V5R21 SP2 - IR Bend design ") // -cr IR-117863V6R2012xWIM
CGMVersionMacroDefine(4230,TrimByThick_FilterEmbryoExceptWhenReusedSurfacesLvl1        ,ZFC ,09-09-2011 ,"V5R21 SP2 - RI Mustfix bend design ") // -cr IR-122169V6R2012xWIM
CGMVersionMacroDefine(4231,HLR_PrecisePositionPtFace2                                  ,NG4 ,09-09-2011 ,"V5R21 SP2 - RI ")
CGMVersionMacroDefine(4232,Extremum_SolutionsOnSameEdge                                ,JHN ,09-09-2011 ,"V5R21 SP2 - RI ") // -cr IR-115949V6R2012xWIM IR-115949V5R21WIM
CGMVersionMacroDefine(4233,TrimByThick_KeepParasiteEmbryoWhenSharedByLumps             ,ZFC ,09-09-2011 ,"V5R21 SP2 - IR 121100 Live Bend Design ") // -cr IR-121100V6R2012xWIM
CGMVersionMacroDefine(4250,CGMR21SP2HF1                                                ,RHA ,09-09-2011 ,"V5R21 SP2 ")
CGMVersionMacroDefine(4251,CGMR21SP2HF2                                                ,RHA ,09-09-2011 ,"V5R21 SP2 ")
CGMVersionMacroDefine(4252,CGMR21SP2HF3                                                ,RHA ,09-09-2011 ,"V5R21 SP2 ")
CGMVersionMacroDefine(4253,CGMR21SP2HF4                                                ,RHA ,09-09-2011 ,"V5R21 SP2 ")
CGMVersionMacroDefine(4254,CGMR21SP2HF5                                                ,RHA ,09-09-2011 ,"V5R21 SP2 ")
CGMVersionMacroDefine(4255,CGMR21SP2HF6                                                ,RHA ,09-09-2011 ,"V5R21 SP2 ")
CGMVersionMacroDefine(4256,CGMR21SP2HF7                                                ,RHA ,09-09-2011 ,"V5R21 SP2 ")
CGMVersionMacroDefine(4257,CGMR21SP2HF8                                                ,RHA ,09-09-2011 ,"V5R21 SP2 ")
CGMVersionMacroDefine(4258,CGMR21SP2HF9                                                ,RHA ,09-09-2011 ,"V5R21 SP2 ")
CGMVersionMacroDefine(4259,CGMR21SP2HF10                                               ,RHA ,09-09-2011 ,"V5R21 SP2 ")


//=========================================================================================================
// V5R21 SP3
//=========================================================================================================
CGMVersionMacroDefine(4260,CGMR21SP3HF1                                                ,RHA ,09-09-2011 ,"V5R21 SP3 ")
CGMVersionMacroDefine(4261,CGMR21SP3HF2                                                ,RHA ,09-09-2011 ,"V5R21 SP3 ")
CGMVersionMacroDefine(4262,CGMR21SP3HF3                                                ,RHA ,09-09-2011 ,"V5R21 SP3 ")
CGMVersionMacroDefine(4263,CGMR21SP3HF4                                                ,RHA ,09-09-2011 ,"V5R21 SP3 ")
CGMVersionMacroDefine(4264,CGMR21SP3HF5                                                ,RHA ,09-09-2011 ,"V5R21 SP3 ")
CGMVersionMacroDefine(4265,CGMR21SP3HF6                                                ,RHA ,09-09-2011 ,"V5R21 SP3 ")
CGMVersionMacroDefine(4266,CGMR21SP3HF7                                                ,RHA ,09-09-2011 ,"V5R21 SP3 ")
CGMVersionMacroDefine(4267,CGMR21SP3HF8                                                ,RHA ,09-09-2011 ,"V5R21 SP3 ")
CGMVersionMacroDefine(4268,CGMR21SP3HF9                                                ,RHA ,09-09-2011 ,"V5R21 SP3 ")
CGMVersionMacroDefine(4269,CGMR21SP3HF10                                               ,RHA ,09-09-2011 ,"V5R21 SP3 ")


//=========================================================================================================
// V5R21 SP4
//=========================================================================================================
CGMVersionMacroDefine(4270,CGMR21SP4HF1                                                ,RHA ,09-09-2011 ,"V5R21 SP4 ")
CGMVersionMacroDefine(4271,CGMR21SP4HF2                                                ,RHA ,09-09-2011 ,"V5R21 SP4 ")
CGMVersionMacroDefine(4272,CGMR21SP4HF3                                                ,RHA ,09-09-2011 ,"V5R21 SP4 ")
CGMVersionMacroDefine(4273,CGMR21SP4HF4                                                ,RHA ,09-09-2011 ,"V5R21 SP4 ")
CGMVersionMacroDefine(4274,CGMR21SP4HF5                                                ,RHA ,09-09-2011 ,"V5R21 SP4 ")
CGMVersionMacroDefine(4275,CGMR21SP4HF6                                                ,RHA ,09-09-2011 ,"V5R21 SP4 ")
CGMVersionMacroDefine(4276,CGMR21SP4HF7                                                ,RHA ,09-09-2011 ,"V5R21 SP4 ")
CGMVersionMacroDefine(4277,CGMR21SP4HF8                                                ,RHA ,09-09-2011 ,"V5R21 SP4 ")
CGMVersionMacroDefine(4278,CGMR21SP4HF9                                                ,RHA ,09-09-2011 ,"V5R21 SP4 ")
CGMVersionMacroDefine(4279,CGMR21SP4HF10                                               ,RHA ,09-09-2011 ,"V5R21 SP4 ")


//=========================================================================================================
// V5R21 SP5
//=========================================================================================================
CGMVersionMacroDefine(4280,CGMR21SP5HF1                                                ,RHA ,09-09-2011 ,"V5R21 SP5 ")
CGMVersionMacroDefine(4281,CGMR21SP5HF2                                                ,RHA ,09-09-2011 ,"V5R21 SP5 ")
CGMVersionMacroDefine(4282,CGMR21SP5HF3                                                ,RHA ,09-09-2011 ,"V5R21 SP5 ")
CGMVersionMacroDefine(4283,CGMR21SP5HF4                                                ,RHA ,09-09-2011 ,"V5R21 SP5 ")
CGMVersionMacroDefine(4284,CGMR21SP5HF5                                                ,RHA ,09-09-2011 ,"V5R21 SP5 ")
CGMVersionMacroDefine(4285,CGMR21SP5HF6                                                ,RHA ,09-09-2011 ,"V5R21 SP5 ")
CGMVersionMacroDefine(4286,CGMR21SP5HF7                                                ,RHA ,09-09-2011 ,"V5R21 SP5 ")
CGMVersionMacroDefine(4287,CGMR21SP5HF8                                                ,RHA ,09-09-2011 ,"V5R21 SP5 ")
CGMVersionMacroDefine(4288,CGMR21SP5HF9                                                ,RHA ,09-09-2011 ,"V5R21 SP5 ")
CGMVersionMacroDefine(4289,CGMR21SP5HF10                                               ,RHA ,09-09-2011 ,"V5R21 SP5 ")


//=========================================================================================================
// V5R21 SP6
//=========================================================================================================
CGMVersionMacroDefine(4290,CGMR21SP6HF1                                                ,RHA ,09-09-2011 ,"V5R21 SP6 ")
CGMVersionMacroDefine(4291,CGMR21SP6HF2                                                ,RHA ,09-09-2011 ,"V5R21 SP6 ")
CGMVersionMacroDefine(4292,CGMR21SP6HF3                                                ,RHA ,09-09-2011 ,"V5R21 SP6 ")
CGMVersionMacroDefine(4293,CGMR21SP6HF4                                                ,RHA ,09-09-2011 ,"V5R21 SP6 ")
CGMVersionMacroDefine(4294,CGMR21SP6HF5                                                ,RHA ,09-09-2011 ,"V5R21 SP6 ")
CGMVersionMacroDefine(4295,CGMR21SP6HF6                                                ,RHA ,09-09-2011 ,"V5R21 SP6 ")
CGMVersionMacroDefine(4296,CGMR21SP6HF7                                                ,RHA ,09-09-2011 ,"V5R21 SP6 ")
CGMVersionMacroDefine(4297,CGMR21SP6HF8                                                ,RHA ,09-09-2011 ,"V5R21 SP6 ")
CGMVersionMacroDefine(4298,CGMR21SP6HF9                                                ,RHA ,09-09-2011 ,"V5R21 SP6 ")
CGMVersionMacroDefine(4299,CGMR21SP6HF10                                               ,RHA ,09-09-2011 ,"V5R21 SP6 ")
CGMVersionMacroDefine(4300,CGMR212HF1                                                  ,RHA ,09-09-2011 ,"V5R21 SP6 ")
CGMVersionMacroDefine(4301,CGMR212HF2                                                  ,RHA ,09-09-2011 ,"V5R21 SP6 ")
CGMVersionMacroDefine(4302,CGMR212HF3                                                  ,RHA ,09-09-2011 ,"V5R21 SP6 ")
CGMVersionMacroDefine(4303,CGMR212HF4                                                  ,RHA ,09-09-2011 ,"V5R21 SP6 ")
CGMVersionMacroDefine(4304,CGMR212HF5                                                  ,RHA ,09-09-2011 ,"V5R21 SP6 ")
CGMVersionMacroDefine(4305,CGMR212HF6                                                  ,RHA ,09-09-2011 ,"V5R21 SP6 ")
CGMVersionMacroDefine(4306,CGMR212HF7                                                  ,RHA ,09-09-2011 ,"V5R21 SP6 ")
CGMVersionMacroDefine(4307,CGMR212HF8                                                  ,RHA ,09-09-2011 ,"V5R21 SP6 ")
CGMVersionMacroDefine(4308,CGMR212HF9                                                  ,RHA ,09-09-2011 ,"V5R21 SP6 ")
CGMVersionMacroDefine(4309,CGMR212HF10                                                 ,RHA ,09-09-2011 ,"V5R21 SP6 ")


//=========================================================================================================
// V5R22 SP1
//=========================================================================================================
CGMVersionMacroDefine(4310,Sweep_FastTwistAnalysis                                     ,NLD ,16-09-2011 ,"V5R22 SP1 ")
CGMVersionMacroDefine(4311,SurfaceSimplification_LocalGeoSimplify                      ,MPS ,16-09-2011 ,"V5R22 SP1 - GeoSimplify  pour la Simplification GSD ")
CGMVersionMacroDefine(4312,Fillet_R22SP1                                               ,RR  ,16-09-2011 ,"V5R22 SP1 - Maintenance Fillet ")
CGMVersionMacroDefine(4313,Regul_NoFuzzyOffset                                         ,dbs ,16-09-2011 ,"V5R22 SP1 - remove fuzzy offset in algorithm ")
CGMVersionMacroDefine(4315,Fillet_SelfIntersect_UnStackedClosedLoops                   ,RR  ,16-09-2011 ,"V5R22 SP1 - Maintenance Fillet ")
CGMVersionMacroDefine(4316,MultiTrim_ConnectedIntersection                             ,RLA ,16-09-2011 ,"V5R22 SP1 - evolution du MultiTrim ") // evolution pour le Trim Pieces
CGMVersionMacroDefine(4317,Reflect_SingularLoopInit                                    ,SOU ,16-09-2011 ,"V5R22 SP1 - ODT ") // Activate on Friday 16th in CGMOFF
CGMVersionMacroDefine(4318,HomotopyCrvSur_TolerantSurfDiag                             ,MNJ ,23-09-2011 ,"V5R22 SP1 - RI MNT ")
CGMVersionMacroDefine(4319,MarshMallow_Mapping2                                        ,pmg ,23-09-2011 ,"V5R22 SP1 - Correction de bug dans le mapping ")
CGMVersionMacroDefine(4320,ThickSurface_FilterVRepSurfOptim                            ,MNJ ,23-09-2011 ,"V5R22 SP1 - RI MNT ") // activation immediate le 23-09-2011
CGMVersionMacroDefine(4321,DistMinCrvCrv_SpecialPointsAndIntersection                  ,KJD ,23-09-2011 ,"V5R22 SP1 - RI ") // -cr 	IR-124490V6R2013WIM 	IR-124490V5R22WIM IR-124454V6R2013WIM 	IR-124454V5R22WIM
CGMVersionMacroDefine(4322,SystemXY_StopByIllConditioning                              ,KJD ,23-09-2011 ,"V5R22 SP1 ") // a activer avant SystemXY_IsNull_TestRelaxation
CGMVersionMacroDefine(4323,MathSystemXY_IsNull_TestRelaxation                          ,KJD ,23-09-2011 ,"V5R22 SP1 - RI093152 ") // -cr 	IR-093152V6R2013WIM 	IR-116852V5R22WIM IR-116852V6R2013WIM IR-117224V6R2013WIM  IR-117224V5R22WIM
CGMVersionMacroDefine(4324,Move3D_ReplaceCellByIndex                                   ,LD2 ,23-09-2011 ,"V5R22 SP1 - Dev ") // Stabilisation de l\'ordre des faces dans CATCXShell::Move3D
CGMVersionMacroDefine(4325,ConfCrvCrv_SymFromMid                                       ,DAD ,30-09-2011 ,"V5R22 SP1 - Symmetrization of ConfusionCrvCrv, IR 084422 ") // -cr IR-084422V6R2013WIM; 6 ODT KOs : FixpartWarn, changement de ref et closed config à réenregistrer
CGMVersionMacroDefine(4326,HoldCurveChamfer                                            ,UVC ,30-09-2011 ,"V5R22 SP1 - Dev ") // Implementation of chamfer with hold curve and angle or distance.
CGMVersionMacroDefine(4327,Marching_Stockage_ScalarComputation                         ,KJD ,30-09-2011 ,"V5R22 SP1 - ODT KO ")
CGMVersionMacroDefine(4328,TopHeal_R22SP1                                              ,PRL ,30-09-2011 ,"V5R22 SP1 - Dev ")
CGMVersionMacroDefine(4329,TrimByThick_NullRadiusLyingOnSharpSide                      ,MNJ ,30-09-2011 ,"V5R22 SP1 - RIs MNT ") // activation immediate le 30-09-2011
//CGMVersionMacroDefine(4330,MidSurface_JournalOrdreCreation                             ,ZUS ,30-09-2011 ,"V5R22 SP1 - Dev ")
CGMVersionMacroDefine(4331,SmartProject_TwoConfusions                                  ,JHN ,30-09-2011 ,"V5R22 SP1 - RI ") // -cr IR-130369V6R2013WIM IR-130369V5-6R2012WIM
//CGMVersionMacroDefine(4332,Sweep_DeploySoftwareConfigurationV12                        ,NLD ,07-10-2011 ,"V5R22 SP1 ")
CGMVersionMacroDefine(4333,EuclideanParallel_HomogeneousEquation                       ,S9L ,07-10-2011 ,"V5R22 SP1 - IR ") // Parallel homogenization done for planar supports. Non-planar initialization in progress
CGMVersionMacroDefine(4334,StylingFilletCCKInterDomain                                 ,MWE ,07-10-2011 ,"V5R22 SP1 - RI 034613 ")
CGMVersionMacroDefine(4335,MinimizeXY_LocalMinimization_PathAdjustment                 ,KJD ,07-10-2011 ,"V5R22 SP1 - RI ") // -cr IR-105932V6R2013WIM   || 3 KO attendus : FM_FXH1_CylTopCurved8Faces & RI488860_NurbsFakeZone
CGMVersionMacroDefine(4336,Thick_LemonTorus                                            ,MNJ ,07-10-2011 ,"V5R22 SP1 - dev ") // activation immediate le 07-10-2011
CGMVersionMacroDefine(4337,Thick_AvoidReconvergenceForHazardousX2S                     ,ZUT ,07-10-2011 ,"V5R22 SP1 - RI ") // -cr IR-129992V6R2013WIM
CGMVersionMacroDefine(4338,RemoveFace_RobustnessLevel21                                ,ZUT ,07-10-2011 ,"V5R22 SP1 - RI ") // -cr 0615076V6R2013WIM IR-111504V6R2013WIM IR-043432V6R2013WIM
//CGMVersionMacroDefine(4339,CATIntersectionSurSurWithInits_KeepInitExitOrientation      ,STY ,07-10-2011 ,"V5R22 SP1 - IOPV6 ")
CGMVersionMacroDefine(4340,NonManifoldVertexIteratorRadialSortOperatorWithCheckTangency,TCX ,07-10-2011 ,"V5R22 SP1 - deploiment correctif CheckTangency  et VertexIterator ") // pour Makarand/Satish
CGMVersionMacroDefine(4341,General_Perfo_R22SP1                                        ,FDS ,07-10-2011 ,"V5R22 SP1 - Perfo ")
CGMVersionMacroDefine(4342,Simplify_Reorder_Stabilize                                  ,FDS ,14-10-2011 ,"V5R22 SP1 - Simplification stabilization ") // Simplification stabilization
CGMVersionMacroDefine(4343,Homotopy3Sur_TriIntersectionAndShiftControls                ,MNJ ,14-10-2011 ,"V5R22 SP1 - RI MNT ") // activation immediate le 14-10-2011
CGMVersionMacroDefine(4344,ParallelRibbonMaintenance_R213                              ,ST5 ,14-10-2011 ,"V5R22 SP1 - RI ") // -cr IR-130531V6R2013xWIM
CGMVersionMacroDefine(4345,MidSurface_JournalOrdreCreation                             ,ZUS ,14-10-2011 ,"V5R22 SP1 - Dev ")
CGMVersionMacroDefine(4346,Fillet_FastUpdate_R22SP1                                    ,IZE ,14-10-2011 ,"V5R22 SP1 - Dev ")
CGMVersionMacroDefine(4347,AutoParallel_R22SP1                                         ,REN ,14-10-2011 ,"V5R22 SP1 - IR 132005 ")
CGMVersionMacroDefine(4348,Fill_InnerContraintsManagement_2                            ,MPS ,21-10-2011 ,"V5R22 SP1 - IR 133261 ") // -cr  IR-133261V6R2013WIM  IR-133261V5-6R2012WIM
CGMVersionMacroDefine(4349,JournalSpyOnlyCells                                         ,EYL ,21-10-2011 ,"V5R22 SP1 - dev ")
CGMVersionMacroDefine(4350,PowerDef_ApplyWireMultiSplit                                ,JJC ,21-10-2011 ,"V5R22 SP1 - Dev ")
CGMVersionMacroDefine(4351,Fillet_ParamDistortion                                      ,xmh ,21-10-2011 ,"V5R22 SP1 - IR ")
CGMVersionMacroDefine(4352,MultiTrim_EqualSignatures                                   ,RLA ,21-10-2011 ,"V5R22 SP1 - Same Signatures ") // dev
CGMVersionMacroDefine(4353,Sweep_XScaleR22SP1                                          ,NLD ,28-10-2011 ,"V5R22 SP1 ")
CGMVersionMacroDefine(4354,Intersect_NoConnector                                       ,JHN ,28-10-2011 ,"V5R22 SP1 - RI ") // Ri R21 seulement
CGMVersionMacroDefine(4355,Extrude_Relimit_MultipleProfile_WithThickness               ,THM ,28-10-2011 ,"V5R22 SP1 - RI134633 ") // -cr IR-134633V5-6R2012WIM IR-134633V6R2013WIM IR-134633V5R20WIM IR-134633V5R21WIM
CGMVersionMacroDefine(4356,Boolean_HomogenizeOnPoint                                   ,JHN ,28-10-2011 ,"V5R22 SP1 - RI ") // -cr IR-133280V6R2013WIM IR-133280V5-6R2012WIM
CGMVersionMacroDefine(4357,TrimByThick_JournalFixForDirectionalSurfacesLevel2          ,ZFC ,04-11-2011 ,"V5R22 SP1 - IR ") // -cr IR-132175V6R2013WIM
//CGMVersionMacroDefine(4358,SpeedPattern_UnspecReefManagement                           ,EB  ,04-11-2011 ,"V5R22 SP1 - SpeedPattern Enhancement ") // None
CGMVersionMacroDefine(4359,Sweep_DeploySoftwareConfigurationV12                        ,NLD ,10-11-2011 ,"V5R22 SP1 ")
CGMVersionMacroDefine(4360,Thick_KeepInitMatterSideWhenDisco3DShunted                  ,ZUT ,10-11-2011 ,"V5R22 SP1 - RI ") // -cr IR-134419V5-6R2012WIM IR-134419V6R2013WIM
CGMVersionMacroDefine(4361,Draft_R22SP1                                                ,SOU ,10-11-2011 ,"V5R22 SP1 - dev ")
CGMVersionMacroDefine(4362,UtilSurSurGen_IsPointOnB_ConeTreatment                      ,DAD ,10-11-2011 ,"V5R22 SP1 - Multisurface convergence ")
CGMVersionMacroDefine(4363,Regul_FreeBorderWithConstraintG0                            ,DBS ,10-11-2011 ,"V5R22 SP1 - Dev ")
CGMVersionMacroDefine(4364,Sweep_MappingWithLimitedShiftOnBorder                       ,NLD ,18-11-2011 ,"V5R22 SP1 ")
CGMVersionMacroDefine(4365,SpeedPattern_UnspecReefManagement                           ,EB  ,18-11-2011 ,"V5R22 SP1 - SpeedPattern Enhancement ") // None
CGMVersionMacroDefine(4366,SystemXY_TopologicalDegree_DegeneratedEdgeTreatmentV2       ,NLD ,18-11-2011 ,"V5R22 SP1 ")
CGMVersionMacroDefine(4367,Fillet_WideLocalSelection2                                  ,RR  ,18-11-2011 ,"V5R22 SP1 - Maintenance ")
CGMVersionMacroDefine(4368,Thick_X2SNonIsoInitEdgeResearchLevel2                       ,MNJ ,18-11-2011 ,"V5R22 SP1 - RI MNT ") // activation immediate le 18-11-2011
CGMVersionMacroDefine(4369,Projection_ReportMapX                                       ,JHN ,18-11-2011 ,"V5R22 SP1 - ODT KO for new development ")
CGMVersionMacroDefine(4370,TrimShell_NewSimplificationAlgorithm                        ,LD2 ,18-11-2011 ,"V5R22 SP1 - Dev, prereq Fast Run ") // KO: CGMTest_Trim_ShellShell_Case8, CGMReplay_LiveTransformFace04, CGMReplay_LiveTransformFace19_DuplicateOnly
//CGMVersionMacroDefine(4371,Rib_Relim_ClosedSurfaceLoopExtension                        ,FBZ ,18-11-2011 ,"V5R22 SP1 - Surfaces complementaires ")
CGMVersionMacroDefine(4372,ThickSurfacePlus_ConstantThicknessOff_Level2                ,DBS ,25-11-2011 ,"V5R22 SP1 - Dev ")
CGMVersionMacroDefine(4373,Thick_DiagnosisHelpLevel18                                  ,MNJ ,25-11-2011 ,"V5R22 SP1 - RI ") // activation immediate le 25-11-2011
CGMVersionMacroDefine(4374,ConfCrvCrv_MidPosCorrection                                 ,DAD ,25-11-2011 ,"V5R22 SP1 - Regression on sweep ")
CGMVersionMacroDefine(4375,RelimWithLimiting                                           ,JQS ,25-11-2011 ,"V5R22 SP1 - Dev ") // Different behavior in relimitation identified if limiting is used
CGMVersionMacroDefine(4376,PropaPosVs3DDisco_IsRegular                                 ,LD2 ,25-11-2011 ,"V5R22 SP1 - Dev ")
CGMVersionMacroDefine(4377,StylingFilletG2G3FilletBoundaries                           ,MWE ,25-11-2011 ,"V5R22 SP1 - RI ") // RI 082777 - 091201 PSA
CGMVersionMacroDefine(4378,TrimByThick_EmbryosSharedByLumpsFiltering                   ,ZFC ,02-12-2011 ,"V5R22 SP1 - IR 121100 LIVE SHEET METAL Activation 25 ") // -cr IR-121100V6R2013WIM
CGMVersionMacroDefine(4379,Intersect_CutClosedScar                                     ,JHN ,02-12-2011 ,"V5R22 SP1 - RI ") // -cr IR-127976V6R2013WIM IR-127976V5-6R2012WIM
CGMVersionMacroDefine(4380,Spline_ContactSolutions                                     ,JHN ,02-12-2011 ,"V5R22 SP1 - RI ") // -cr IR-135590V6R2013WIM IR-135590V5-6R2012WIM
CGMVersionMacroDefine(4381,TrimByThick_SharpLyingOnTrimBorderLevel3                    ,MNJ ,02-12-2011 ,"V5R22 SP1 - RI ") // activation immediate le 02-12-2011
CGMVersionMacroDefine(4382,TrimByThick_KeepUnresolvedInitVertexConfusions              ,ZFC ,02-12-2011 ,"V5R22 SP1 - RI EXT IR ") // -cr IR-137578V6R2013WIM
CGMVersionMacroDefine(4383,UtilSurSurGen_IsPointOnB_SphereTreatment                    ,DAD ,02-12-2011 ,"V5R22 SP1 - InterOp: Sphere Treatment in IsPointOnBorder ")
CGMVersionMacroDefine(4384,Sweep_GetLambdaOnC0VertexV2                                 ,NLD ,02-12-2011 ,"V5R22 SP1 ")
CGMVersionMacroDefine(4385,Fill_DegeneratedWire                                        ,MPS ,09-12-2011 ,"V5R22 SP1 - correction  bug dans le cas d\'un wire degenere ")
CGMVersionMacroDefine(4386,RemoveFace_RFRobustnessLevel22                              ,ZUT ,09-12-2011 ,"V5R22 SP1 - RI ") // -cr 0634521V6R2013WIM IR-042619V6R2013WIM
CGMVersionMacroDefine(4387,TrimByThick_SharpLyingOnCvgLevel6                           ,MNJ ,09-12-2011 ,"V5R22 SP1 - RI ") // activation immediate le 09-12-2011
CGMVersionMacroDefine(4388,RemoveUnusefulMissing                                       ,LD2 ,09-12-2011 ,"V5R22 SP1 - RI ") // -cr IR-121605V6R2013WIM IR-121605V5R22WIM
CGMVersionMacroDefine(4389,Boolean_InterPointSolution                                  ,JHN ,09-12-2011 ,"V5R22 SP1 - RI ") // correction partielle seulement
CGMVersionMacroDefine(4390,Sweep_ComputeGraphSW2                                       ,THM ,09-12-2011 ,"V5R22 SP1 - IR135790 ")
CGMVersionMacroDefine(4391,Sweep_FillTwistV6                                           ,NLD ,09-12-2011 ,"V5R22 SP1 ")
CGMVersionMacroDefine(4392,RemoveFace_RemoveFilletRobustnessLevel1                     ,ZUT ,16-12-2011 ,"V5R22 SP1 - RI ") // -cr 0615307V6R2013WIM 0615244V6R2013WIM
CGMVersionMacroDefine(4393,Thick_DiagnosisHelpLevel19                                  ,MNJ ,16-12-2011 ,"V5R22 SP1 - RI ") // activation immediate le 16-12-2011
CGMVersionMacroDefine(4394,CXVtx_LocalDup_RemEdgeOrders                                ,LD2 ,16-12-2011 ,"V5R22 SP1 - Dev ") // Nettoyage ordres d\'edge dans booléen volumique
//CGMVersionMacroDefine(4395,SpecialPCrvPCrv_Domain                                      ,r1y ,16-12-2011 ,"V5R22 SP1 - IR 120051 ")
CGMVersionMacroDefine(4396,Regul_Drop_IVF_Level1                                       ,DBS ,16-12-2011 ,"V5R22 SP1 - Dev ")
CGMVersionMacroDefine(4397,SkinExtrapol_ApproximateERepLevel9                          ,ZUT ,16-12-2011 ,"V5R22 SP1 - Robustesse FuzzyExtrapol ") // Demande ZFC pour XTrim
CGMVersionMacroDefine(4398,StylingFilletCheckBoundaryToExtrapole                       ,MWE ,16-12-2011 ,"V5R22 SP1 - dev ") // mises au point Fillet Variable Tolerant
CGMVersionMacroDefine(4399,TopGeometricalMappingAlgoExtension                          ,KY1 ,16-12-2011 ,"V5R22 SP1 - Dev ") // Extension de l\'algo de mapping des edges pour inclure de nouvelles config de confusions d\'edge
CGMVersionMacroDefine(4400,Marching_ReviewV1                                           ,NLD ,06-01-2012 ,"V5R22 SP1 ")
CGMVersionMacroDefine(4401,PersistentEdges_TolForMerge                                 ,EYL ,06-01-2012 ,"V5R22 SP1 ") // -cr HF-142839V5R20SP4WIM
CGMVersionMacroDefine(4402,TrimByThick_Level20                                         ,MNJ ,06-01-2012 ,"V5R22 SP1 - RI ")
CGMVersionMacroDefine(4403,PersistentFaceOrientationLevel1                             ,VB7 ,06-01-2012 ,"V5R22 SP1 - ODT ") // CGMReplay_MidSurfaceOperator02  rc = 4
CGMVersionMacroDefine(4404,Rib_Relim_ClosedSurfaceLoopExtension                        ,FBZ ,06-01-2012 ,"V5R22 SP1 - Surfaces complementaires ")
CGMVersionMacroDefine(4405,PtSurCan_ProjOnConeApexTol                                  ,DAD ,06-01-2012 ,"V5R22 SP1 - HF 143825 & 143933 ") // -cr IR-143825V6R2013WIM IR-143825V5-6R2012WIM IR-143933V6R2013WIM IR-143933V5-6R2012WIM
CGMVersionMacroDefine(4406,ExtrapolNurbsBipar_C1Corrected                              ,JSX ,06-01-2012 ,"V5R22 SP1 - Dev PSDirect ") // Modif parametrisation pour passer du G1 au C1
CGMVersionMacroDefine(4407,WireMultiTrim_InputExtremities                              ,JHN ,06-01-2012 ,"V5R22 SP1 - RI ") // -cr IR-122914V6R2013WIM
CGMVersionMacroDefine(4408,Boolean_InfiniteUV                                          ,JHN ,06-01-2012 ,"V5R22 SP1 - RI Swx ") // -cr IR-143013V6R2013WIM IR-142737V6R2013WIM IR-143270V6R2013WIM
CGMVersionMacroDefine(4409,Intersect_MergeSmallCurve                                   ,JHN ,06-01-2012 ,"V5R22 SP1 - RI ") // -cr IR-143050V6R2013WIM IR-143050V5-6R2012WIM
//CGMVersionMacroDefine(4410,TopSkin_LocalJournal                                        ,JHN ,06-01-2012 ,"V5R22 SP1 - RI ") // -cr IR-142064V6R2013 IR-142064V5-6R2012WIM
CGMVersionMacroDefine(4411,TrimByThick_InitMatterOriWhenSurfaceReused                  ,ZFC ,06-01-2012 ,"V5R22 SP1 - RI Bend Design IR ") // -cr IR-126347V6R2013WIM
CGMVersionMacroDefine(4412,IntersectionCrvSur_NurbsIsExpensiveSurface                  ,R1Y ,13-01-2012 ,"V5R22 SP1 - RI104894 ") // -cr IR-104894V6R2013WIM
CGMVersionMacroDefine(4413,SpecialPCrvPCrv_Domain                                      ,R1Y ,13-01-2012 ,"V5R22 SP1 - IR 120051 ") // -cr IR-120051V5R22WIM IR-120051V6R2013WIM
CGMVersionMacroDefine(4414,BooleanFastRun_SetToTouched                                 ,LD2 ,13-01-2012 ,"V5R22 SP1 - Dev, correction fast update ")
CGMVersionMacroDefine(4415,Thick_DirSurfVolSideGuessLevel2                             ,MNJ ,13-01-2012 ,"V5R22 SP1 - RI ")
CGMVersionMacroDefine(4416,LiveShape_LiveBodyProtection                                ,VB7 ,13-01-2012 ,"V5R22 SP1 - Dev LiveShape ")
CGMVersionMacroDefine(4417,RemoveFace_RFRobustnessLevel23                              ,ZUT ,13-01-2012 ,"V5R22 SP1 - Robustesse RemoveFace pour Pattern ") // Demande JJ3 & VB7
CGMVersionMacroDefine(4418,Smartification_CompareGeometry                              ,LD2 ,13-01-2012 ,"V5R22 SP1 - Dev ")
CGMVersionMacroDefine(4419,BooleanFastRun_CurveFilterEvolution                         ,WQO ,13-01-2012 ,"V5R22 SP1 - Evolution Fast Run Booleen ")
CGMVersionMacroDefine(4420,DynBoolean_Smartification                                   ,LD2 ,13-01-2012 ,"V5R22 SP1 - Dev ")
CGMVersionMacroDefine(4421,Fillet_ExplodeIntoLumps                                     ,RR  ,20-01-2012 ,"V5R22 SP1 - RI ")
CGMVersionMacroDefine(4422,ParallelMaintenance_R22SP1                                  ,ST5 ,20-01-2012 ,"V5R22 SP1 - IR ") // -cr IR-145641V5-6R2012WIM
CGMVersionMacroDefine(4425,CGMR22SP1HF1                                                ,RHA ,09-09-2011 ,"V5R22 SP1 ")
CGMVersionMacroDefine(4426,CGMR22SP1HF2                                                ,RHA ,09-09-2011 ,"V5R22 SP1 ")
CGMVersionMacroDefine(4427,CGMR22SP1HF3                                                ,RHA ,09-09-2011 ,"V5R22 SP1 ")
CGMVersionMacroDefine(4428,CGMR22SP1HF4                                                ,RHA ,09-09-2011 ,"V5R22 SP1 ")
CGMVersionMacroDefine(4429,CGMR22SP1HF5                                                ,RHA ,09-09-2011 ,"V5R22 SP1 ")
CGMVersionMacroDefine(4430,CGMR22SP1HF6                                                ,RHA ,09-09-2011 ,"V5R22 SP1 ")
CGMVersionMacroDefine(4431,CGMR22SP1HF7                                                ,RHA ,09-09-2011 ,"V5R22 SP1 ")
CGMVersionMacroDefine(4432,CGMR22SP1HF8                                                ,RHA ,09-09-2011 ,"V5R22 SP1 ")
CGMVersionMacroDefine(4433,CGMR22SP1HF9                                                ,RHA ,09-09-2011 ,"V5R22 SP1 ")
CGMVersionMacroDefine(4434,CGMR22SP1HF10                                               ,RHA ,09-09-2011 ,"V5R22 SP1 ")


//=========================================================================================================
// V5R22 SP2
//=========================================================================================================
CGMVersionMacroDefine(4435,PowerDef_ApplyWireLayDownMonoShell                          ,JJC ,27-01-2012 ,"V5R22 SP2 - ODT KO CATGmoUpd_ShapeMorphing_LimitSupport ") // projection des Wires uniquement sur des Bodies Mono-Shell
CGMVersionMacroDefine(4436,TrimByThick_NoDisco2dIntermediate                           ,ZFC ,27-01-2012 ,"V5R22 SP2 - RIs EXT IR ") // -cr IR-147878V5-6R2012WIM IR-147878V6R2013WIM
CGMVersionMacroDefine(4437,RSO_ThrowOnBadInput                                         ,pmg ,27-01-2012 ,"V5R22 SP2 - Dev ") // conformite de RSO avec shapemorphing :Non prise en compte des Load=> Throw
CGMVersionMacroDefine(4438,HybridVarOffset_RabbitEarsRemoval                           ,MNJ ,27-01-2012 ,"V5R22 SP2 - RI MNT ") // activation immediate le 27-01-2012
CGMVersionMacroDefine(4439,Thick_AlgoLevel17                                           ,MNJ ,27-01-2012 ,"V5R22 SP2 - dev ") // activation immediate le 27-01-2012
CGMVersionMacroDefine(4440,RemoveFace_RFRobustnessLevel24                              ,ZUT ,27-01-2012 ,"V5R22 SP2 - RI ") // -cr IR-147404V6R2013WIM
CGMVersionMacroDefine(4441,Ribbon_ContainsWithTransition                               ,RR  ,03-02-2012 ,"V5R22 SP2 - RI ")
CGMVersionMacroDefine(4442,Line_Angle_N_Solutions                                      ,RLA ,03-02-2012 ,"V5R22 SP2 - RI 122769 ") // sortie en ereur si N solutions possibles (N pouvant être infini) -cr  IR-122769V5R22WIM
CGMVersionMacroDefine(4443,RelimFillet_R22SP2                                          ,PRL ,03-02-2012 ,"V5R22 SP2 ")
CGMVersionMacroDefine(4444,Thick_CheckResultAfterSimplif                               ,MNJ ,03-02-2012 ,"V5R22 SP2 - RI CLS ") // activation immediate le 03-02-2012
CGMVersionMacroDefine(4445,Boolean_CellTrackerCorrectOutputs                           ,WQO ,10-02-2012 ,"V5R22 SP2 - Correction of Boolean Journal with Cell Tracker ")
CGMVersionMacroDefine(4446,Smartification_UntouchedAreInvariant                        ,LD2 ,10-02-2012 ,"V5R22 SP2 ")
CGMVersionMacroDefine(4447,Ribbon_CheckContinuity_ClosedCleanCurve                     ,RR  ,10-02-2012 ,"V5R22 SP2 - RI ")
CGMVersionMacroDefine(4448,RemoveFace_CorrectConnectedFacesList                        ,ZUT ,10-02-2012 ,"V5R22 SP2 - RI ") // -cr IR-144179V6R2013WIM
CGMVersionMacroDefine(4449,Thick_HealingGeoPostProLevel16                              ,MNJ ,10-02-2012 ,"V5R22 SP2 - ODT ") // activation immediate le 10-02-2012
//CGMVersionMacroDefine(4450,ConstantFillet_ResearchInitLoop                             ,xmh ,10-02-2012 ,"V5R22 SP2 - RI122378 ")
//CGMVersionMacroDefine(4451,Extrude_BestRelimitation                                    ,THM ,10-02-2012 ,"V5R22 SP2 - Dev ") // Move default relimitation for Prism and Revol from Relimit2 to Relimit3
CGMVersionMacroDefine(4452,StylingFilletPatchParameter                                 ,MWE ,17-02-2012 ,"V5R22 SP2 - RI ") // RI 100150
CGMVersionMacroDefine(4453,Thick_ReverseFRepTrustLevel                                 ,MNJ ,17-02-2012 ,"V5R22 SP2 - RI CLS ") // activation immediate le 17-02-2012
CGMVersionMacroDefine(4454,Fillet_Variable_Warning                                     ,RR  ,17-02-2012 ,"V5R22 SP2 - RI ")
//CGMVersionMacroDefine(4455,DistanceMinPtCrv_Booster                                    ,NLD ,24-02-2012 ,"V5R22 SP2 ")
//CGMVersionMacroDefine(4456,DistanceMinCrvCrv_Booster                                   ,NLD ,24-02-2012 ,"V5R22 SP2 ")
//CGMVersionMacroDefine(4458,Sweep_ExtrapolateSingleFaceLimits_General                   ,THM ,24-02-2012 ,"V5R22 SP2 - Dev ")
//CGMVersionMacroDefine(4459,SmartificationAfterFreeze                                   ,LD2 ,24-02-2012 ,"V5R22 SP2 - Dev ")
//CGMVersionMacroDefine(4460,BooleanFastRun_OptimMakeInter                               ,WQO ,24-02-2012 ,"V5R22 SP2 - Fast Run evolution ")
//CGMVersionMacroDefine(4461,BooleanFastRun_PropagSymetry                                ,WQO ,24-02-2012 ,"V5R22 SP2 - Fast Run evolution ")
//CGMVersionMacroDefine(4462,TrimShell_FreezeDuringRun                                   ,LD2 ,24-02-2012 ,"V5R22 SP2 - Dev, prereq Fast Update ")
CGMVersionMacroDefine(4463,TrimByThick_FindOffsetSurfaceFromBody                       ,ZFC ,24-02-2012 ,"V5R22 SP2 - IR ") // -cr IR-147649V6R2013WIM IR-147649V6R2013xWIM
CGMVersionMacroDefine(4464,CATSubdOrientationVol_TangentCase                           ,LD2 ,24-02-2012 ,"V5R22 SP2 - RI ") // -cr IR-151940V5-6R2012WIM IR-151940V6R2013WIM IR-151940V6R2013xWIM
//CGMVersionMacroDefine(4465,RibbonReorder_3SA_CstVar                                    ,UVC ,24-02-2012 ,"V5R22 SP2 - bug fix ") // -cr IR-151091V6R2013xWIM
CGMVersionMacroDefine(4466,ParallelGraphSolver_NewTangencyPointCases                   ,ST5 ,24-02-2012 ,"V5R22 SP2 - RI ") // -cr IR-145242V5-6R2012WIM, IR-145242V6R2013xWIM
CGMVersionMacroDefine(4467,CGMR22SP2HF1                                                ,RHA ,24-02-2012 ,"V5R22 SP2 ")
CGMVersionMacroDefine(4468,CGMR22SP2HF2                                                ,RHA ,24-02-2012 ,"V5R22 SP2 ")
CGMVersionMacroDefine(4469,CGMR22SP2HF3                                                ,RHA ,24-02-2012 ,"V5R22 SP2 ")
CGMVersionMacroDefine(4470,CGMR22SP2HF4                                                ,RHA ,24-02-2012 ,"V5R22 SP2 ")
CGMVersionMacroDefine(4471,CGMR22SP2HF5                                                ,RHA ,24-02-2012 ,"V5R22 SP2 ")
CGMVersionMacroDefine(4472,CGMR22SP2HF6                                                ,RHA ,24-02-2012 ,"V5R22 SP2 ")
CGMVersionMacroDefine(4473,CGMR22SP2HF7                                                ,RHA ,24-02-2012 ,"V5R22 SP2 ")
CGMVersionMacroDefine(4474,CGMR22SP2HF8                                                ,RHA ,24-02-2012 ,"V5R22 SP2 ")
CGMVersionMacroDefine(4475,CGMR22SP2HF9                                                ,RHA ,24-02-2012 ,"V5R22 SP2 ")
CGMVersionMacroDefine(4476,CGMR22SP2HF10                                               ,RHA ,24-02-2012 ,"V5R22 SP2 ")


//=========================================================================================================
// V5R22 SP3
//=========================================================================================================
CGMVersionMacroDefine(4477,RemoveFace_FaceRelimitationLevel1                           ,ZUT ,02-03-2012 ,"V5R22 SP3 - RI ") // -cr IR-151630V6R2013WIM IR-151630V6R2013xWIM
CGMVersionMacroDefine(4478,DistanceMinCrvCrv_Booster                                   ,NLD ,02-03-2012 ,"V5R22 SP3 ")
CGMVersionMacroDefine(4479,DistanceMinPtCrv_Booster                                    ,NLD ,02-03-2012 ,"V5R22 SP3 ")
CGMVersionMacroDefine(4480,Sweep_ExtrapolateSingleFaceLimits_General                   ,THM ,02-03-2012 ,"V5R22 SP3 - Dev ")
CGMVersionMacroDefine(4481,SmartificationAfterFreeze                                   ,LD2 ,02-03-2012 ,"V5R22 SP3 - Dev ")
CGMVersionMacroDefine(4482,BooleanFastRun_OptimMakeInter                               ,WQO ,02-03-2012 ,"V5R22 SP3 - Fast Run evolution ")
CGMVersionMacroDefine(4483,TrimShell_FreezeDuringRun                                   ,LD2 ,02-03-2012 ,"V5R22 SP3 - Dev, prereq Fast Update ")
CGMVersionMacroDefine(4484,BooleanFastRun_PropagSymetry                                ,WQO ,02-03-2012 ,"V5R22 SP3 - Fast Run evolution ")
CGMVersionMacroDefine(4485,TrimShell_NullJournalForIntersect                           ,LD2 ,02-03-2012 ,"V5R22 SP3 - Dev, evolution in TrimShell journal (and also a prereq for FastRun) ")
CGMVersionMacroDefine(4486,BooleanFastRun_TouchingFacesIntersect                       ,WQO ,02-03-2012 ,"V5R22 SP3 - Fast Run evolution/correction ")
CGMVersionMacroDefine(4487,Boolean_InterWireWireStabilize                              ,WQO ,02-03-2012 ,"V5R22 SP3 - IR ") // -cr IR-147894V5-6R2012WIM IR-147894V6R2013WIM IR-147894V6R2013xWIM
CGMVersionMacroDefine(4488,IntersectWS_EndingJournal                                   ,JHN ,02-03-2012 ,"V5R22 SP3 - RI ") // -cr IR-143050V6R2013WIM IR-143050V5-6R2012WIM IR-143050V6R2013xWIM, KO(CGMTest_Intersection_ShellShell_Case3,CGMTest_Intersection_WireShell,CGMTest_Split_WireShell_SemiSpace,CGMTest_Split_WireVertex, PerfOnly_ski_goggle_boundary)
//CGMVersionMacroDefine(4489,SurfaceSimplification_PrecisionEnhancement                  ,KTU ,09-03-2012 ,"V5R22 SP3 - Dev: Amelioration des precisions, calcul des deviations et remontee des infos de deviation ")
CGMVersionMacroDefine(4490,ProjectionPtCrv_SamplingV2                                  ,NLD ,09-03-2012 ,"V5R22 SP3 ") // -cr IR-151653V6R2013xWIM
CGMVersionMacroDefine(4491,ThickSurface_ThinFaceTolerance                              ,MNJ ,09-03-2012 ,"V5R22 SP3 - RI ")
CGMVersionMacroDefine(4492,HybridVarOffset_TolerantExtrapol                            ,MNJ ,09-03-2012 ,"V5R22 SP3 - dev ")
CGMVersionMacroDefine(4493,HomotopyCrvSur_LargeGapCondition                            ,MNJ ,09-03-2012 ,"V5R22 SP3 - Dev ")
CGMVersionMacroDefine(4494,RestoreWorkingCtxt_Stabilization                            ,ize ,09-03-2012 ,"V5R22 SP3 - RI ") // -cr IR-154009V6R2013x IR-154009V5-6R2012 IR-153887V6R2013x  IR-153887V5-6R2012  IR-149413V6R2013x IR-149413V5-6R2012
CGMVersionMacroDefine(4495,TopHeal_R22SP3                                              ,PRL ,09-03-2012 ,"V5R22 SP3 - RIs ")
CGMVersionMacroDefine(4496,Fillet_ParamDistortionSpecSur                               ,xmh ,09-03-2012 ,"V5R22 SP3 - RI140925 ") // -cr IR-140925V6R2013xWIM
CGMVersionMacroDefine(4497,Fillet_NewNotches_Four                                      ,RR  ,09-03-2012 ,"V5R22 SP3 - Maintenance ")
CGMVersionMacroDefine(4498,RibbonReorder_3SA_CstVar                                    ,UVC ,09-03-2012 ,"V5R22 SP3 - bug fix ") // -cr IR-151091V6R2013xWIM IR-151091V5-6R2012WIM
//CGMVersionMacroDefine(4499,Extrude_BestRelimitation                                    ,THM ,09-03-2012 ,"V5R22 SP3 - Dev ") // Move default relimitation for Prism and Revol from Relimit2 to Relimit3
CGMVersionMacroDefine(4500,PlaneAngle_Parametrisation                                  ,JHN ,09-03-2012 ,"V5R22 SP3 - RI ") // -cr IR-158443V6R2013xWIM  IR-158443V5-6R2012WIM
CGMVersionMacroDefine(4501,SmartProject_Boundaries                                     ,JHN ,09-03-2012 ,"V5R22 SP3 - bug decouvert suite a modification allocateur memoire ") // 2 modifiations de comportement
CGMVersionMacroDefine(4502,Split_NoVolumeError                                         ,JHN ,09-03-2012 ,"V5R22 SP3 - solid work request ") // error when split solid of a shell
CGMVersionMacroDefine(4503,ShellExpansion_ChangeOrdering_V5R20                         ,S9L ,09-03-2012 ,"V5R22 SP3 - Change in ordering of intersection points along the polyline in RunApproxNew method of CATFlattenerStrategy ") // IR-156400V5-6R2012
CGMVersionMacroDefine(4504,Sweep_XScaleR22SP3                                          ,NLD ,16-03-2012 ,"V5R22 SP3 ")
CGMVersionMacroDefine(4505,Sweep_IntersectionCoupling_OptimWithSpineMapping            ,NLD ,16-03-2012 ,"V5R22 SP3 ")
CGMVersionMacroDefine(4506,SystemXY_HyperbolicSingularity_NullInCornerV2               ,NLD ,16-03-2012 ,"V5R22 SP3 ")
CGMVersionMacroDefine(4507,BlendRibbon_Hermetisation_ThinFace                          ,SOU ,16-03-2012 ,"V5R22 SP3 - RI ") // R22SP3
CGMVersionMacroDefine(4508,Fillet_VariableKeepEdgeG1                                   ,SOU ,16-03-2012 ,"V5R22 SP3 - First Drop of development delivered ") // Dev
CGMVersionMacroDefine(4509,SurfaceSimplification_PrecisionEnhancement                  ,KTU ,16-03-2012 ,"V5R22 SP3 - Dev: Amelioration des precisions, calcul des deviations et remontee des infos de deviation ")
CGMVersionMacroDefine(4510,HybridVarOffset_ITPSnapping                                 ,MNJ ,16-03-2012 ,"V5R22 SP3 - RI ") // activation immediate le 16-03-2012
CGMVersionMacroDefine(4511,RemoveFace_RFRobustnessLevel26                              ,ZUT ,16-03-2012 ,"V5R22 SP3 - RI ") // -cr IR-150831V6R2013xWIM
CGMVersionMacroDefine(4512,EdgeStylingFillet                                           ,MWE ,16-03-2012 ,"V5R22 SP3 - dev ") // PSA
CGMVersionMacroDefine(4513,IntersectionCrvSur_CrvTab_GlobalParam                       ,JSX ,23-03-2012 ,"V5R22 SP3 - RI 151040V6R2013 ") // -cr IR-151040V6R2013xWIM IR-151040V6R2013WIM
CGMVersionMacroDefine(4514,Sweep_DeploySoftwareConfigurationV13                        ,NLD ,23-03-2012 ,"V5R22 SP3 ")
CGMVersionMacroDefine(4515,Spine_DeploySoftwareConfiguration                           ,NLD ,23-03-2012 ,"V5R22 SP3 ") // debranche le 30-06-08
CGMVersionMacroDefine(4516,Sweep_MultiDomainReportV2                                   ,NLD ,23-03-2012 ,"V5R22 SP3 ")
CGMVersionMacroDefine(4517,IntersectionCrvSur_IsExpensiveSurfaceLimits                 ,XMH ,23-03-2012 ,"V5R22 SP3 - RI145231 ") // -cr IR-145231V6R2013x  IR-145231V5-6R2012  -cr IR-145231V6R2013x  -cr
CGMVersionMacroDefine(4518,ICMSurfaceGeneration_Journal_CreateOutOfNothing             ,VIF ,23-03-2012 ,"V5R22 SP3 - Bad runtime for huge surface data when using the ICMSurfaceGenerationLT subfeature because of its journal ") // -cr IR-147966V5-6R2012WIM
CGMVersionMacroDefine(4519,Fillet_RibbonsReorderDeadlock                               ,JQS ,23-03-2012 ,"V5R22 SP3 - Dev ")
CGMVersionMacroDefine(4520,Thick_UniNormalPtPartialDegeneration                        ,MNJ ,23-03-2012 ,"V5R22 SP3 - convergence dev ") // activation immediate le 23-03-2012
CGMVersionMacroDefine(4521,Fillet_UnTwist_R22SP3                                       ,rr  ,23-03-2012 ,"V5R22 SP3 - Maintenance ")
CGMVersionMacroDefine(4522,MissingRelimFaceKeepFeature                                 ,JQS ,23-03-2012 ,"V5R22 SP3 - Dev ") // Part of Keep Feature Stage2
CGMVersionMacroDefine(4523,StylingFilletTrimSew                                        ,MWE ,30-03-2012 ,"V5R22 SP3 - dev ") // PSA
CGMVersionMacroDefine(4524,TrimByThick_TwinIVRepsMerge                                 ,ZFC ,30-03-2012 ,"V5R22 SP3 - IR ") // -cr IR-159693V6R2013xWIM
CGMVersionMacroDefine(4525,Thick_StabilizationLevel3                                   ,ZUT ,30-03-2012 ,"V5R22 SP3 - RI ") // -cr IR-151449V6R2013WIM IR-151449V6R2013xWIM
CGMVersionMacroDefine(4526,RemoveFace_ParasiticERepsDetection                          ,ZUT ,30-03-2012 ,"V5R22 SP3 - RI ") // -cr IR-158634V6R2013xWIM IR-158635V6R2013xWIM
CGMVersionMacroDefine(4527,NewSkinGroupLinking                                         ,LD2 ,30-03-2012 ,"V5R22 SP3 - RI ") // -cr  IR-159711V5-6R2012WIM IR-159711V6R2013xWIM
CGMVersionMacroDefine(4528,Sweep_ProfilePositioningV8                                  ,NLD ,06-04-2012 ,"V5R22 SP3 ")
CGMVersionMacroDefine(4529,ConstantFillet_SingularInputInit                            ,xmh ,06-04-2012 ,"V5R22 SP3 - RI155471 ") // -cr IR-155471V5-6R2012WIM IR-155471V6R2013xWIM
CGMVersionMacroDefine(4530,IntersectionSurSur_SurfaceSwapInLoop                        ,Q48 ,06-04-2012 ,"V5R22 SP3 - RI096815 ") // -cr IR-096815V6R2013xWIM
CGMVersionMacroDefine(4531,Connect_MultiSol_ExtrapolSol                                ,SOU ,06-04-2012 ,"V5R22 SP3 - RI ") // for CXR22SP3
//CGMVersionMacroDefine(4532,SmartProjection_FaceOrdering                                ,THM ,06-04-2012 ,"V5R22 SP3 - Dev ")
CGMVersionMacroDefine(4533,ConstantFillet_ResearchInitLoop                             ,xmh ,06-04-2012 ,"V5R22 SP3 - RI122378 ") // Please warn IZE in case of unexpected KOs
CGMVersionMacroDefine(4534,ICM_BlendSrf_DoNotCreateDegenerateSurface                   ,r6n ,06-04-2012 ,"V5R22 SP3 - IR ") // -cr IR-113594V6R2013xWIM IR-134050V5-6R2012WIM IR-134050V6R2013WIM IR-134050V6R2013xWIM
CGMVersionMacroDefine(4535,Compatible_NonManifoldCase                                  ,WQO ,06-04-2012 ,"V5R22 SP3 - Compatible compatibility with extreme non ")
CGMVersionMacroDefine(4536,Marsh_ForceRestartOnSingularity                             ,PMG ,13-04-2012 ,"V5R22 SP3 - RI ") // -cr IR-161134V5-6R2012WIM IR-161134V6R2013xWIM
CGMVersionMacroDefine(4537,ICM_Flange_Project_Single_Chain                             ,nvz ,13-04-2012 ,"V5R22 SP3 - IR ") // -cr IR-148417V5-6R2012WIM IR-148417V6R2013x
CGMVersionMacroDefine(4538,IntersectionSurSurWithInits_OrientationNormTgt              ,xmh ,13-04-2012 ,"V5R22 SP3 - Dev ")
CGMVersionMacroDefine(4539,GetTouchingFaces_Fix                                        ,LD2 ,13-04-2012 ,"V5R22 SP3 - Dev ") // Fix to correct bug in function RecursiveGetAllContainerFaces, discovered during TrimShell FastRun stress tests
CGMVersionMacroDefine(4540,Fillet_RibbonReorder_R22SP3                                 ,UVC ,13-04-2012 ,"V5R22 SP3 - V5R22_SP3Maintenance ")
CGMVersionMacroDefine(4541,ICM_StylingCorner_PlaneOrientation                          ,NVZ ,13-04-2012 ,"V5R22 SP3 - IR ") // -cr IR-147800V5-6R2012WIM IR-147800V6R2013x
CGMVersionMacroDefine(4542,ICM_OffsetCrv_CatchBoundary                                 ,qwl ,13-04-2012 ,"V5R22 SP3 - introduce use_catch_boundary in IcXtSurfaceUtil::param_in_range(..) ") // -cr IR-161272V5-6R2012WIM  IR-161272V6R2013xWIM
CGMVersionMacroDefine(4543,Relim_R22SP3                                                ,PRL ,20-04-2012 ,"V5R22 SP3 - RIs+Dev ")
CGMVersionMacroDefine(4544,ReflectCurve_Sphere                                         ,D1A ,20-04-2012 ,"V5R22 SP3 - Dev ")
CGMVersionMacroDefine(4545,EuclidianParallel_CheckRelimitation                         ,ST5 ,20-04-2012 ,"V5R22 SP3 - RI ") // -cr IR-142841V5-6R2012WIM  IR-142841V6R2013WIM  IR-142841V6R2013xWIM
CGMVersionMacroDefine(4546,RemoveFace_RFRobustnessLevel27                              ,ZUT ,20-04-2012 ,"V5R22 SP3 - Convergence dev ") // Stabilisation ODT RemoveFace_353
CGMVersionMacroDefine(4547,Fill_CleanNotDone                                           ,MPS ,27-04-2012 ,"V5R22 SP3 - IR ") // -cr IR-161119V6R2013xWIM IR-161119V5-6R2012WIM
CGMVersionMacroDefine(4548,Fill_SurfInitKO                                             ,MPS ,27-04-2012 ,"V5R22 SP3 - 163421 ") // -cr  IR-163421V5-6R2012WIM  IR-163421V5-6R2013WIM  IR-163421V6R2013xWIM
CGMVersionMacroDefine(4549,Sweep_OpenProfileContextual                                 ,G5S ,27-04-2012 ,"V5R22 SP3 - Dev ") // allows extrusion of open profiles with extrapolated until limits
CGMVersionMacroDefine(4550,TrimSew_R22SP3                                              ,PRL ,27-04-2012 ,"V5R22 SP3 - Dev ")
CGMVersionMacroDefine(4551,InitialBSplineMustKeepInputCellStructure                    ,nvw ,04-05-2012 ,"V5R22 SP3 - Due to erroneous prior progress on IR ") // -cr IR-094710V5-6R2012WIM
CGMVersionMacroDefine(4552,TrimByThick_CuttingConfusedFaces                            ,ZFC ,04-05-2012 ,"V5R22 SP3 - IR 154397 ") // -cr IR-154397V5-6R2012WIM IR-154397V6R2013xWIM
CGMVersionMacroDefine(4553,Thick_FaceWithInternalLoopLevel3                            ,MNJ ,04-05-2012 ,"V5R22 SP3 - RI ") // activation immediate le 04-05-2012
CGMVersionMacroDefine(4554,Thick_ElimConfusedFRepLevel2                                ,ZUT ,04-05-2012 ,"V5R22 SP3 - Dev ") // Demande LAP pour scenarios SWx et CGMtk
CGMVersionMacroDefine(4555,Project_MultiAdjacence                                      ,JHN ,11-05-2012 ,"V5R22 SP3 - RI MF ") // -cr IR-147341V6R2013xWIM IR-150538V6R2013xWIM
CGMVersionMacroDefine(4556,ICMFillet_Improve_Tol_To_Assure_G1                          ,NVZ ,11-05-2012 ,"V5R22 SP3 - IR ") // -cr IR-101233V5-6R2012WIM IR-101233V6R2013x
CGMVersionMacroDefine(4557,Compatible_InternalLoopStabilisation                        ,JHN ,11-05-2012 ,"V5R22 SP3 - RI interne ") // -cr  IR-074031V6R2013xWIM
CGMVersionMacroDefine(4558,IntersectionSurSur_SimplifyConfusion                        ,xmh ,11-05-2012 ,"V5R22 SP3 - RI151284 ") // -cr IR-151284V6R2013xWIM IR-151284V5-6R2012WIM
CGMVersionMacroDefine(4559,IntersectionSurSurBorderTol                                 ,xmh ,11-05-2012 ,"V5R22 SP3 - Dev ")
CGMVersionMacroDefine(4560,BodyHealer_RemoveGapsKeepingCurves                          ,LD2 ,18-05-2012 ,"V5R22 SP3 - Dev ")
CGMVersionMacroDefine(4561,HLR_ExtendSingularBreaksToReflectEdges                      ,DPS ,18-05-2012 ,"V5R22 SP3 - CATTopSilhouette robustness through HLR quality improvment ") // convergence ODTs Silhouette
CGMVersionMacroDefine(4562,MinimizeX_FMinimize_DerivativeImageAdjustment               ,kjd ,18-05-2012 ,"V5R22 SP3 - RI165371 ") // -cr IR-165371V6R2013xWIM IR-165371V5-6R2012
CGMVersionMacroDefine(4563,SmartProjection_FaceOrdering                                ,THM ,18-05-2012 ,"V5R22 SP3 - Dev ")
CGMVersionMacroDefine(4564,HLR_NHRWiresTreatedByGroupHierarchy                         ,NG4 ,18-05-2012 ,"V5R22 SP3 - RI ")
CGMVersionMacroDefine(4565,KeepFeatureAtSupportBoundary                                ,JQS ,18-05-2012 ,"V5R22 SP3 - Dev ") // Configuration of KeepFeature SeasonII
CGMVersionMacroDefine(4566,Chamfer_ApproximateDistances                                ,REN ,25-05-2012 ,"V5R22 SP3 - Dev ")
CGMVersionMacroDefine(4567,ClosedSurfaceProblemWithWrapSurface                         ,dr  ,25-05-2012 ,"V5R22 SP3 - ir ")
CGMVersionMacroDefine(4568,Thick_CheckResultBodyMass                                   ,MNJ ,25-05-2012 ,"V5R22 SP3 - RI ") // activation immediate le 25-05-2012
CGMVersionMacroDefine(4569,DistanceBodyBody_EvaluatedPointPositionCheck                ,nhd ,25-05-2012 ,"V5R22 SP3 - IR ") // -cr IR-163645V5R21WIM
CGMVersionMacroDefine(4570,EliminateDegeneratedEdge_New                                ,LD2 ,01-06-2012 ,"V5R22 SP3 - Dev ")
CGMVersionMacroDefine(4571,ExtrapolationNurbsProblematique                             ,dr  ,01-06-2012 ,"V5R22 SP3 - ir ")
CGMVersionMacroDefine(4572,SweepBasic_ChooseBetterOrientation                          ,THM ,01-06-2012 ,"V5R22 SP3 - IR ") // -cr IR-165281V6R2013xWIM
CGMVersionMacroDefine(4573,Chamfer_BadShapeFix                                         ,REN ,08-06-2012 ,"V5R22 SP3 - IR 108021 ") // RI
CGMVersionMacroDefine(4574,EdgeSharpness_WrongPropagate_IR156822                       ,tcx ,08-06-2012 ,"V5R22 SP3 - IR156822  (Cf Mail   du  Wed 6/6/2012 1:31 PM) ")
CGMVersionMacroDefine(4575,General_Perfo_R22SP2                                        ,FDS ,08-06-2012 ,"V5R22 SP3 - Performance V5R22SP2 ")
CGMVersionMacroDefine(4576,ICM_APPROX_FillG0InfimumWithG1Value                         ,nvw ,08-06-2012 ,"V5R22 SP3 - ISD Approximation: ensure the use of G0 tolerances smaller than 0.001 mm ")
CGMVersionMacroDefine(4577,Thick_RazorBladeFaces                                       ,MNJ ,08-06-2012 ,"V5R22 SP3 - RI ") // activation immediate le 08-06-2012
CGMVersionMacroDefine(4578,EdgeCurveSimplify_CompareEdgeCurves                         ,MNJ ,15-06-2012 ,"V5R22 SP3 - dev ")
CGMVersionMacroDefine(4579,ICMAdvancedFillet_Version_11                                ,qkh ,15-06-2012 ,"V5R22 SP3 - RI ") // -cr  IR-135371V5-6R2013WIM, IR-135371V5-6R2012WIM,  IR-135371V5-6R2012WIM
//CGMVersionMacroDefine(4580,ICM_Flange_Consider_All_Breakpoints                         ,NVZ ,15-06-2012 ,"V5R22 SP3 - RI ") // -cr IR-168436V6R2013xWIM IR-168436V5-6R2013WIM IR-168436V5-6R2012WIM
CGMVersionMacroDefine(4581,Boolean_BoundaryOverlap                                     ,JHN ,15-06-2012 ,"V5R22 SP3 - CGM component IR ") // -cr IR-169299V6R2013xWIM
CGMVersionMacroDefine(4582,Compatible_MixedDimJournal                                  ,WQO ,15-06-2012 ,"V5R22 SP3 - Dev for DOCO replacing Modif by Create ")
CGMVersionMacroDefine(4583,DOCO_JournalForSelection                                    ,WQO ,15-06-2012 ,"V5R22 SP3 - Dev replacing subdiv by modif+info ")
CGMVersionMacroDefine(4584,Parallel_RadialSortMaintenance_R22SP3                       ,ST5 ,15-06-2012 ,"V5R22 SP3 - IR ") // -cr IR-156096V5-6R2012WIM IR-156096V6R2013WIM IR-156096V6R2013xWIM IR-156096V5-6R2013WIM
//CGMVersionMacroDefine(4585,Extrude_BestRelimitation                                    ,THM ,15-06-2012 ,"V5R22 SP3 - Dev ") // Move default relimitation for Prism and Revol from Relimit2 to Relimit3
CGMVersionMacroDefine(4586,ICMGlobalSurfaceOffsetResultBehaviour                       ,nwp ,15-06-2012 ,"V5R22 SP3 - Changed behaviour (result creation) of global surface offset operator ") // IR-153555 IR-114940 IR-127127 IR-126548
CGMVersionMacroDefine(4587,AutoParallel_R22SP3                                         ,REN ,15-06-2012 ,"V5R22 SP3 - RI 171252 ")
CGMVersionMacroDefine(4588,CGMR22SP3HF1                                                ,RHA ,26-06-2012 ,"V5R22 SP3 ")
CGMVersionMacroDefine(4589,CGMR22SP3HF2                                                ,RHA ,26-06-2012 ,"V5R22 SP3 ")
CGMVersionMacroDefine(4590,CGMR22SP3HF3                                                ,RHA ,26-06-2012 ,"V5R22 SP3 ")
CGMVersionMacroDefine(4591,CGMR22SP3HF4                                                ,RHA ,26-06-2012 ,"V5R22 SP3 ")
CGMVersionMacroDefine(4592,CGMR22SP3HF5                                                ,RHA ,26-06-2012 ,"V5R22 SP3 ")
CGMVersionMacroDefine(4593,CGMR22SP3HF6                                                ,RHA ,26-06-2012 ,"V5R22 SP3 ")
CGMVersionMacroDefine(4594,CGMR22SP3HF7                                                ,RHA ,26-06-2012 ,"V5R22 SP3 ")
CGMVersionMacroDefine(4595,CGMR22SP3HF8                                                ,RHA ,26-06-2012 ,"V5R22 SP3 ")
CGMVersionMacroDefine(4596,CGMR22SP3HF9                                                ,RHA ,26-06-2012 ,"V5R22 SP3 ")
CGMVersionMacroDefine(4597,CGMR22SP3HF10                                               ,RHA ,26-06-2012 ,"V5R22 SP3 ")


//=========================================================================================================
// V5R22 SP4
//=========================================================================================================
CGMVersionMacroDefine(4598,Simplify_RotateClosedSurface                                ,FDS ,22-06-2012 ,"V5R22 SP4 - Closed Surface enhancement for spatial ") // For spatial
CGMVersionMacroDefine(4599,Healing_Level33                                             ,JJC ,22-06-2012 ,"V5R22 SP4 ") // Healing de Vertex
CGMVersionMacroDefine(4600,ICM_CrvBlendMatchSrf_not_G2                                 ,r6n ,22-06-2012 ,"V5R22 SP4 - Rework curve blend ") // -cr  IR-153350V6R2013xWIM  IR-153350V5-6R2013WIM IR-153350V5-6R2012WIM  IR-153350V5R21WIM
CGMVersionMacroDefine(4601,ICMDataMapping_Use_Decreased_Reapproximation_MaxDistance    ,URG ,22-06-2012 ,"V5R22 SP4 - Dev ") // Fix mapping problem wrt IR-163194
CGMVersionMacroDefine(4602,IcBr_Fix_Overlap_Evaluation                                 ,URG ,22-06-2012 ,"V5R22 SP4 - Dev ") // Fix potential error in overlap evaluation
CGMVersionMacroDefine(4603,Fillet_ReInterpolateInSingularRegion                        ,xmh ,22-06-2012 ,"V5R22 SP4 - RI158688 ")
CGMVersionMacroDefine(4604,Thick_InitMatterLevel1                                      ,MNJ ,29-06-2012 ,"V5R22 SP4 - RI MNT ")
CGMVersionMacroDefine(4605,Regul_MarginForCheckOffsetLocalSplit                        ,DBS ,29-06-2012 ,"V5R22 SP4 - RI ")
CGMVersionMacroDefine(4606,ICM_PrepareCurves_UseArrayInEdgeSorter                      ,qwl ,29-06-2012 ,"V5R22 SP4 - use array in edge sorter ") // -cr IR-166437V5-6R2013WIM IR-166437V6R2013x WIM
CGMVersionMacroDefine(4607,HybridVarOffset_WarningCracks                               ,DBS ,29-06-2012 ,"V5R22 SP4 - Dev ")
CGMVersionMacroDefine(4608,ICMDataMapping_Apply_3dCurve_Creation_Fix                   ,URG ,29-06-2012 ,"V5R22 SP4 - Dev ") // CGM-CTB mapping, fixed potential bug in creating 3d curves from 2d curves
CGMVersionMacroDefine(4609,ICMDataMapping_Apply_0_MaxDistance_For_SingleCurve_Edges    ,URG ,29-06-2012 ,"V5R22 SP4 - Dev ") // CTB-CGM Mapping: Do not attach MaxDev value in CATSimCurve creation for single curve edges
CGMVersionMacroDefine(4610,Sweep_C0Meridian_InconsistentInitExitManagement             ,NLD ,06-07-2012 ,"V5R22 SP4 ")
//CGMVersionMacroDefine(4611,ProjCrvSur_TanBorderCompOpt                                 ,DAD ,06-07-2012 ,"V5R22 SP4 - Optimisations perfo in Proj CrvSur; activated for sphere only (RI 147342) ")
//CGMVersionMacroDefine(4612,TransDist_NormProjCrvSur                                    ,DAD ,06-07-2012 ,"V5R22 SP4 - Use of MinimizeDistanceTransverseDistance in Normal Projection CrvSur; activated for sphere only (RI 147342) ") // Impact ODTs CGMShapeTests.tst: CGMTest_SmartProject_NearIndus/RI554331; CGMTest_SmartProject_NearIndus2a
//CGMVersionMacroDefine(4613,ProjCrvSur_PoleSphere                                       ,DAD ,06-07-2012 ,"V5R22 SP4 - RI 147342 ")
CGMVersionMacroDefine(4614,Relim_R22SP4                                                ,PRL ,06-07-2012 ,"V5R22 SP4 - RI ")
CGMVersionMacroDefine(4615,Sweep_XScaleR22SP4                                          ,NLD ,06-07-2012 ,"V5R22 SP4 ")
CGMVersionMacroDefine(4616,TopHeal_R22SP4                                              ,PRL ,06-07-2012 ,"V5R22 SP4 - Dev ")
CGMVersionMacroDefine(4617,Fillet_RibTrackSmoother                                     ,RR  ,06-07-2012 ,"V5R22 SP4 - RI ")
CGMVersionMacroDefine(4618,RemoveFace_CornerCase                                       ,MNJ ,06-07-2012 ,"V5R22 SP4 - RI ")
CGMVersionMacroDefine(4619,ICM_Flange_Consider_All_Breakpoints                         ,NVZ ,06-07-2012 ,"V5R22 SP4 - RI ") // -cr IR-168436V6R2013xWIM IR-168436V5-6R2013WIM IR-168436V5-6R2012WIM
CGMVersionMacroDefine(4620,SkinExtrapol_FuzzyExtrapolLevel2                            ,ZUT ,06-07-2012 ,"V5R22 SP4 - RI ") // -cr  IR-147583V6R2013xWIM IR-155133V6R2013xWIM
CGMVersionMacroDefine(4621,Extrude_BestRelimitation                                    ,THM ,06-07-2012 ,"V5R22 SP4 - Dev ") // Move default relimitation for Prism and Revol from Relimit2 to Relimit3
CGMVersionMacroDefine(4622,ICMAdvancedFillet_Version_12                                ,qkh ,06-07-2012 ,"V5R22 SP4 - IR ") // avoid confusion between version_10 and version_11
CGMVersionMacroDefine(4623,QuinticInterpolation_ThrowOnSolveError                      ,NLD ,13-07-2012 ,"V5R22 SP4 ")
CGMVersionMacroDefine(4624,ICM_Sweep_RespectDeviationHomogenize                        ,qwl ,13-07-2012 ,"V5R22 SP4 - respect deviation homogenize in IcSweep ") // -cr IR-161789V5-6R2012WIM IR-161789V5-6R2013WIM IR-161789V6R2013xWIM
CGMVersionMacroDefine(4625,Thick_FaceWithInternalLoopLevel5                            ,MNJ ,13-07-2012 ,"V5R22 SP4 - RI ")
CGMVersionMacroDefine(4626,ICM_CrvBlendSymmetricAdvancedAdaptLinear                    ,r6n ,13-07-2012 ,"V5R22 SP4 - Improve option Adapt/Linear for curve blends on a support surface. ") // -cr IR-140074V5-6R2012WIM IR-140074V5-6R2013WIM IR-140074V6R2013xWIM
CGMVersionMacroDefine(4627,Fillet_R22SP4                                               ,ZUS ,13-07-2012 ,"V5R22 SP4 - RI+dev ") // -cr IR-162804V6R2013xWIM
CGMVersionMacroDefine(4628,RemoveFace_UntouchedFacesPreventiveImportLvl2               ,ZUT ,13-07-2012 ,"V5R22 SP4 - RI ") // -cr IR-151592V6R2013xWIM
CGMVersionMacroDefine(4629,Interpol_EtaSeurLBalBeur                                    ,NLD ,20-07-2012 ,"V5R22 SP4 ")
CGMVersionMacroDefine(4630,MatchingMultiTarget                                         ,MWE ,20-07-2012 ,"V5R22 SP4 - Dev ")
CGMVersionMacroDefine(4631,AutoParallel_R22SP4                                         ,REN ,20-07-2012 ,"V5R22 SP4 - IR 171252 ")
CGMVersionMacroDefine(4632,ICM_Flange_Consider_Attach_Curve                            ,NVZ ,20-07-2012 ,"V5R22 SP4 - RI ") // MvF consider separate spine
CGMVersionMacroDefine(4633,ICM_OffsetCrv_UseMinKink                                    ,qwl ,20-07-2012 ,"V5R22 SP4 - introduce UseMinKink in ICMCLAIcCurveOffset ") // -cr IR-164931V5-6R2012WIM IR-164931V5-6R2013WIM IR-164931V6R2013xWIM
CGMVersionMacroDefine(4634,FuzzyExtrapol_ExtrapolMonoSurf                              ,ZUT ,20-07-2012 ,"V5R22 SP4 - RI ") // -cr IR-178711V6R2013xWIM
CGMVersionMacroDefine(4635,SweepBasic_ChooseBetterOrientation2                         ,THM ,20-07-2012 ,"V5R22 SP4 - RI ") // -cr IR-165281V6R2013xWIM
CGMVersionMacroDefine(4636,TrimShell_Smartification                                    ,LD2 ,20-07-2012 ,"V5R22 SP4 - Dev ")
CGMVersionMacroDefine(4637,Sweep_CleanGuidesParametersV9                               ,NLD ,27-07-2012 ,"V5R22 SP4 ") // -cr   IR-175104V5-6R2013WIM   IR-175104V6R2013xWIM
CGMVersionMacroDefine(4638,Regul_Drop_IVF_Level2                                       ,DBS ,27-07-2012 ,"V5R22 SP4 - dev drop IVF level 2 ")
CGMVersionMacroDefine(4639,IgnoreMashedFaces                                           ,LD2 ,27-07-2012 ,"V5R22 SP4 - RI ") // -cr IR-171461V5-6R2012WIM IR-171461V5-6R2013WIM IR-171461V6R2013xWIM
CGMVersionMacroDefine(4640,RemoveFace_CollisionFilterLvl1                              ,ZUT ,27-07-2012 ,"V5R22 SP4 - RI ") // -cr IR-157160V6R2013xWIM
CGMVersionMacroDefine(4641,ICM_IcBt_Fix_Wire_Extend                                    ,URG ,03-08-2012 ,"V5R22 SP4 - RI ") // -cr IR-134050V5-6R2012WIM, -cr IR-134050V5-6R2013WIM, -cr IR-134050V6R2013xWIM
CGMVersionMacroDefine(4642,Object_AdvBox_GenericRuledSurface                           ,JSX ,03-08-2012 ,"V5R22 SP4 - ri 179754 ") // -cr IR-179454V5-6R2013WIM   IR-179454V6R2013xWIM
CGMVersionMacroDefine(4643,ICM_Extrapolation_Unequal_InterpolateCorners                ,e33 ,03-08-2012 ,"V5R22 SP4 - RI ") // -cr IR-177007V6R2013xWIM IR-177007V5-6R2013WIM IR-177007V5-6R2012WIM
CGMVersionMacroDefine(4644,ICM_ExtrapolationFeat_Unequal_InterpolateCorners            ,e33 ,03-08-2012 ,"V5R22 SP4 - RI ") // -cr IR-180550V6R2013xWIM IR-180550V5-6R2013WIM IR-180550V5-6R2012WIM
//CGMVersionMacroDefine(4645,PCurveCGM_ComputeBox_EmptyIntersection                      ,kjd ,03-08-2012 ,"V5R22 SP4 - protection CD ")
CGMVersionMacroDefine(4646,NonAdjacentInit_Border                                      ,UVC ,03-08-2012 ,"V5R22 SP4 - Dev ")
CGMVersionMacroDefine(4647,Sweep_VolumicKeepNonClashing                                ,G5S ,03-08-2012 ,"V5R22 SP4 - IR 172671 ") // -cr IR-172671V6R2013xWIM
CGMVersionMacroDefine(4648,ProjCrvSur_PoleSphere                                       ,DAD ,10-08-2012 ,"V5R22 SP4 - RI 147342 ")
//CGMVersionMacroDefine(4649,IntersectionSurSurWithInits_CanonicalResultOnRevol          ,PKC ,10-08-2012 ,"V5R22 SP4 - dev ")
CGMVersionMacroDefine(4650,Intersection_CurveOrientations                              ,D1A ,10-08-2012 ,"V5R22 SP4 - Dev ")
CGMVersionMacroDefine(4651,DraftMultiAngle                                             ,D1A ,10-08-2012 ,"V5R22 SP4 - Dev ")
CGMVersionMacroDefine(4652,RemoveDeadEndsLight                                         ,LD2 ,10-08-2012 ,"V5R22 SP4 - RI ") // -cr IR-181347V5-6R2012WIM IR-181347V5-6R2013WIM IR-181347V6R2013xWIM
CGMVersionMacroDefine(4653,Extrude_PropagOnSplitGraph                                  ,THM ,10-08-2012 ,"V5R22 SP4 - RI ") // -cr IR-167925V6R2013x IR-167925V5-6R2013
CGMVersionMacroDefine(4654,TrimSew_R22SP4                                              ,PRL ,17-08-2012 ,"V5R22 SP4 - RI+ ")
CGMVersionMacroDefine(4655,ICM_FilletShellsInOrder                                     ,nwp ,17-08-2012 ,"V5R22 SP4 - Let shell fillet operator process startvalues in (fixed) order ") // -cr IR-182269V6R2013xWIM
CGMVersionMacroDefine(4656,ICM_ProjectWiresInOrder                                     ,nwp ,17-08-2012 ,"V5R22 SP4 - Let wire projection operation process startvalues in (fixed) order ") // -cr IR-182269V5-6R2013WIM
CGMVersionMacroDefine(4657,ICM_SequentialTopologyRecognition                           ,nwp ,17-08-2012 ,"V5R22 SP4 - Let topology recognition process input model in (fixed) order ") // -cr IR-182269V5-6R2012WIM
CGMVersionMacroDefine(4658,MultiRibbonWithKeepFeature                                  ,JQS ,17-08-2012 ,"V5R22 SP4 - Dev ") // Enhancement for Keep Feature
CGMVersionMacroDefine(4659,SurSurWithInits_PlineReversal                               ,xmh ,24-08-2012 ,"V5R22 SP4 - dev PSDirect project ")
CGMVersionMacroDefine(4660,FaceAnalyzer_Tolerance                                      ,ZUS ,24-08-2012 ,"V5R22 SP4 - RI ") // -cr IR-071801V6R2011xWIM
CGMVersionMacroDefine(4661,Thick_DiagnosisHelpLevel20                                  ,MNJ ,24-08-2012 ,"V5R22 SP4 - RIs ")
CGMVersionMacroDefine(4662,PCurveCGM_ComputeBox_EmptyIntersection                      ,KJD ,24-08-2012 ,"V5R22 SP4 - protection CD ")
CGMVersionMacroDefine(4663,Homotopy_SingularLevel2                                     ,MNJ ,24-08-2012 ,"V5R22 SP4 - RI REG ") // activation immediate le 24-08-2012
CGMVersionMacroDefine(4664,Extrapol_ShellG1_G1Spine_V2                                 ,JSX ,31-08-2012 ,"V5R22 SP4 - RI SkinExtrapolation (G1) ") // -cr IR-167296V5-6R2012WIM IR-167296V5-6R2013WIM IR-167296V6R2013xWIM
CGMVersionMacroDefine(4665,Thick_SelectVolumeLevel5                                    ,MNJ ,31-08-2012 ,"V5R22 SP4 - RI CLS ") // activation immediate le 31-08-2012
CGMVersionMacroDefine(4666,SkinExtrapol_FuzzyExtrapolLevel3                            ,ZUT ,31-08-2012 ,"V5R22 SP4 - RI ") // -cr IR-181498V6R2013xWIM IR-180602V6R2013xWIM
CGMVersionMacroDefine(4667,AutoCheck_EraseAtEnd                                        ,JHN ,31-08-2012 ,"V5R22 SP4 - RI ") // -cr  IR-175976V6R2013xWIM IR-175976V5-6R2013WIM
CGMVersionMacroDefine(4668,Boolean_KeepInter                                           ,JHN ,31-08-2012 ,"V5R22 SP4 - RI ") // -cd IR-174852V6R2013xWIM
CGMVersionMacroDefine(4669,SmartProject_AllSolutionsCovering                           ,JHN ,31-08-2012 ,"V5R22 SP4 - RI partial correction ") // -cr IR-182313V6R2013xWIM IR-182313V5-6R2013WIM
CGMVersionMacroDefine(4670,SmartProject_ReportShellMissing                             ,JHN ,31-08-2012 ,"V5R22 SP4 - RI partual correction ") // -cd IR-182313V5-6R2013WIM   IR-182313V6R2013xWIM
CGMVersionMacroDefine(4671,HybOperator_GetResultGetSlim                                ,LD2 ,07-09-2012 ,"V5R22 SP4 - Dev ") // Prereq pour passer l\'Assemble en MultiResult
CGMVersionMacroDefine(4672,Revol_ShiftRefPlaneToOffset                                 ,THM ,07-09-2012 ,"V5R22 SP4 - RI ") // -cr IR-183604V6R2013xWIM
CGMVersionMacroDefine(4673,HLR_PreciseCircularMedgesSurrounding                        ,NG4 ,07-09-2012 ,"V5R22 SP4 - RI ") // -cr IR-186172V5-6R2013WIM IR-186172V6R2014WIM
CGMVersionMacroDefine(4674,Sweep_ExtrapolateSingleFaceLimits_Surfacic                  ,THM ,07-09-2012 ,"V5R22 SP4 - Dev ") // Enable extrapolated until limits for surfacic general sweep
CGMVersionMacroDefine(4675,ProjCrvSur_ReleaseTolImpSys                                 ,DAD ,14-09-2012 ,"V5R22 SP4 - IR 169689, Release tolerance in implicit system for directional projection ") // -cr IR-169689V6R2013xWIM IR-169689V5-6R2013WIM IR-169689V5-6R2012WIM
CGMVersionMacroDefine(4676,Mirrored_BissectorSurface_Extrapolation                     ,PKC ,14-09-2012 ,"V5R22 SP4 - RI ")
CGMVersionMacroDefine(4677,ICM_Loft_RespectSurfaceDeviation                            ,qwl ,14-09-2012 ,"V5R22 SP4 - Respect surface deviation in Spine mode ") // -cr IR-106060V6R2013xWIM IR-106060V5-6R2012WIM IR-106060V5-6R2013WIM
CGMVersionMacroDefine(4678,ICM_ProjectCrv_AdjustSourceKnots                            ,qwl ,14-09-2012 ,"V5R22 SP4 - Adjust source knots with respect to tol_point ") // -cr IR-181591V6R2013xWIM IR-181591V5-6R2013WIM
CGMVersionMacroDefine(4679,ICM_StylingCorner_MaxCrvParts                               ,qwl ,14-09-2012 ,"V5R22 SP4 - avoid endless loop for very small radius ") // -cr IR-186681V6R2013xWIM IR-186681V6R2014WIM IR-186681V5-6R2012WIM IR-186681V5-6R2013WIM
CGMVersionMacroDefine(4680,RemoveFace_RemoveFilletRobustnessLevel2                     ,ZUT ,14-09-2012 ,"V5R22 SP4 - RI ") // -cr IR-045150V6R2013xWIM
CGMVersionMacroDefine(4681,CanonicalConnect_TolFix                                     ,JQS ,14-09-2012 ,"V5R22 SP4 - RI ") // -cr IR-167542V5-6R2013
CGMVersionMacroDefine(4682,DraftBothSides_IncreaseTwistFreeSol                         ,REN ,14-09-2012 ,"V5R22 SP4 - SUG IR ")
CGMVersionMacroDefine(4683,ProjCrvSur_HelixInitComputation                             ,DAD ,21-09-2012 ,"V5R22 SP4 - IR 149035 & 149431, to build 3 inits per lap of helix ") // -cr IR-149431V5-6R2012WIM IR-149431V5-6R2013WIM IR-149431V6R2013WIM IR-149431V6R2013xWIM IR-149431V6R2014WIM IR-149035V5-6R2012WIM IR-149035V5-6R2013WIM IR-149035V6R2013WIM IR-149035V6R2013xWIM IR-149035V6R2014WIM
//CGMVersionMacroDefine(4684,CATOffsetTabProfileEquationX_ChebyshevConfidence            ,JSX ,21-09-2012 ,"V5R22 SP4 - RI 137524 ") // -cr IR-137524V5-6R2012WIM IR-137524V5-6R2013WIM IR-137524V6R2013xWIM IR-137524V6R2014WIM
CGMVersionMacroDefine(4685,ICM_Sweep_RespectDeviationHomogenizeUpgrade                 ,qwl ,21-09-2012 ,"V5R22 SP4 - respect deviation homogenize for upgraded feature in IcSweep ") // -cr IR-161789V5-6R2012WIM IR-161789V5-6R2013WIM
CGMVersionMacroDefine(4686,ICM_Flange_UseDeviationParametersInApproximation            ,qwl ,21-09-2012 ,"V5R22 SP4 - Use deviation parameters in approximation ") // -cr IR-185698V6R2014WIM
CGMVersionMacroDefine(4687,ParallelRibbonMaintenance_R22SP4                            ,ST5 ,21-09-2012 ,"V5R22 SP4 - RI ") // -cr IR-166168V5-6R2013WIM, IR-166168V6R2013xWIM
CGMVersionMacroDefine(4688,Loft_MultiCurveFitting_IsResultValidV2                      ,NLD ,21-09-2012 ,"V5R22 SP4 ") // -cr IR-189363V5-6R2012WIM IR-189363V5-6R2013WIM IR-189363V6R2013xWIM  IR-189363V6R2014WIM
CGMVersionMacroDefine(4689,StylingFilletSmartProjectionCurve                           ,MWE ,21-09-2012 ,"V5R22 SP4 - RI ")
CGMVersionMacroDefine(4690,ShellUnfold_VertexTransferFix                               ,s9l ,21-09-2012 ,"V5R22 SP4 - Enhancements in vertex transfer in shell unfold ") // Solves the problem of vertex transfer lying at the face corners
CGMVersionMacroDefine(4691,CGMR22SP4HF1                                                ,RHA ,24-09-2012 ,"V5R22 SP4 ")
CGMVersionMacroDefine(4692,CGMR22SP4HF2                                                ,RHA ,24-09-2012 ,"V5R22 SP4 ")
CGMVersionMacroDefine(4693,CGMR22SP4HF3                                                ,RHA ,24-09-2012 ,"V5R22 SP4 ")
CGMVersionMacroDefine(4694,CGMR22SP4HF4                                                ,RHA ,24-09-2012 ,"V5R22 SP4 ")
CGMVersionMacroDefine(4695,CGMR22SP4HF5                                                ,RHA ,24-09-2012 ,"V5R22 SP4 ")
CGMVersionMacroDefine(4696,CGMR22SP4HF6                                                ,RHA ,24-09-2012 ,"V5R22 SP4 ")
CGMVersionMacroDefine(4697,CGMR22SP4HF7                                                ,RHA ,24-09-2012 ,"V5R22 SP4 ")
CGMVersionMacroDefine(4698,CGMR22SP4HF8                                                ,RHA ,24-09-2012 ,"V5R22 SP4 ")
CGMVersionMacroDefine(4699,CGMR22SP4HF9                                                ,RHA ,24-09-2012 ,"V5R22 SP4 ")
CGMVersionMacroDefine(4700,CGMR22SP4HF10                                               ,RHA ,24-09-2012 ,"V5R22 SP4 ")


//=========================================================================================================
// V5R22 SP5
//=========================================================================================================
CGMVersionMacroDefine(4701,CGMR22SP5HF1                                                ,RHA ,24-09-2012 ,"V5R22 SP5 ")
CGMVersionMacroDefine(4702,CGMR22SP5HF2                                                ,RHA ,24-09-2012 ,"V5R22 SP5 ")
CGMVersionMacroDefine(4703,CGMR22SP5HF3                                                ,RHA ,24-09-2012 ,"V5R22 SP5 ")
CGMVersionMacroDefine(4704,CGMR22SP5HF4                                                ,RHA ,24-09-2012 ,"V5R22 SP5 ")
CGMVersionMacroDefine(4705,CGMR22SP5HF5                                                ,RHA ,24-09-2012 ,"V5R22 SP5 ")
CGMVersionMacroDefine(4706,CGMR22SP5HF6                                                ,RHA ,24-09-2012 ,"V5R22 SP5 ")
CGMVersionMacroDefine(4707,CGMR22SP5HF7                                                ,RHA ,24-09-2012 ,"V5R22 SP5 ")
CGMVersionMacroDefine(4708,CGMR22SP5HF8                                                ,RHA ,24-09-2012 ,"V5R22 SP5 ")
CGMVersionMacroDefine(4709,CGMR22SP5HF9                                                ,RHA ,24-09-2012 ,"V5R22 SP5 ")
CGMVersionMacroDefine(4710,CGMR22SP5HF10                                               ,RHA ,24-09-2012 ,"V5R22 SP5 ")


//=========================================================================================================
// V5R22 SP6
//=========================================================================================================
CGMVersionMacroDefine(4711,CGMR22SP6HF1                                                ,RHA ,24-09-2012 ,"V5R22 SP6 ")
CGMVersionMacroDefine(4712,CGMR22SP6HF2                                                ,RHA ,24-09-2012 ,"V5R22 SP6 ")
CGMVersionMacroDefine(4713,CGMR22SP6HF3                                                ,RHA ,24-09-2012 ,"V5R22 SP6 ")
CGMVersionMacroDefine(4714,CGMR22SP6HF4                                                ,RHA ,24-09-2012 ,"V5R22 SP6 ")
CGMVersionMacroDefine(4715,CGMR22SP6HF5                                                ,RHA ,24-09-2012 ,"V5R22 SP6 ")
CGMVersionMacroDefine(4716,CGMR22SP6HF6                                                ,RHA ,24-09-2012 ,"V5R22 SP6 ")
CGMVersionMacroDefine(4717,CGMR22SP6HF7                                                ,RHA ,24-09-2012 ,"V5R22 SP6 ")
CGMVersionMacroDefine(4718,CGMR22SP6HF8                                                ,RHA ,24-09-2012 ,"V5R22 SP6 ")
CGMVersionMacroDefine(4719,CGMR22SP6HF9                                                ,RHA ,24-09-2012 ,"V5R22 SP6 ")
CGMVersionMacroDefine(4720,CGMR22SP6HF10                                               ,RHA ,24-09-2012 ,"V5R22 SP6 ")


#endif
