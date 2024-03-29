#ifndef RootContainerCGM_OLK_Defects_h
#define RootContainerCGM_OLK_Defects_h
// COPYRIGHT DASSAULT SYSTEMES 2005
//=============================================================================
// RR 2010_01_18
// mkodt -F TopologicalOperators.tst -s TestMultiRibbonFillet
/*
Il s�agit un � vieil � odt qui teste un composant strictement interne de l�op�rateur fillet. 
Ni ce composant interne, ni le code de l�odt  n�appellent CleanNewerUnused. 
Donc, en terme d�OLK, cet odt n�est pas repr�sentatifs de ses OLKs. 
Les odts pertinents de l�operateur Fillet sont dans CGMTopologyTests et CGMSurfacicTests.tst.
*/
//
#define RootContainerCGM_OLK_Defects_MRF_2010_10_14
//=============================================================================
//
// To follow OLK corrections to be done
//
//=============================================================================
//#define RootContainerCGM_OLK_Defects_Shell_Stream
/*
Case Test17
mkodt -F NewTopologicalObjects.tst -s TestSimplify2
PurgeUndo: delete for 	CATCXFace	125

Case Test14
mkodt -F TopologicalOperators.tst -s TestSimplify
PurgeUndo: delete for 	CATCXFace	125
PurgeUndo: delete for 	CATCXFace 1201
PurgeUndo: delete for 	CATCXFace 1203
PurgeUndo: delete for 	CATCXFace 1315
*/
//#define RootContainerCGM_OLK_Defects_SimplifyManager
/*
Case Test14
mkodt -F TopologicalOperators.tst -s TestSimplify
Case Test17     POEC 1010 et 1016 sont tres resistants
mkodt -F NewTopologicalObjects.tst -s TestSimplify2    
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	421
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	422
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	440
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	441
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	453
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	461
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	483
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	503
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	525
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	563
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	590
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	597
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	613
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	614
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	630
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	631
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	653
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	654
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	664
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	665
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	694
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	714
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	715
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	742
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	777
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	778
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	784
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	801
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	817
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	818
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	826
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	827
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	848
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	864
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	865
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	888
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	907
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	908
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	1001
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	1004
PurgeUndo: delete for 	CATMergedCurveCGM	1007
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	1010
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	1011
PurgeUndo: delete for 	CATMergedCurveCGM	1012
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	1015
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	1016
PurgeUndo: CGMUsedBytes_before= 241664 cleaned= 77824 OLK_Bytes= 163840 OLK_ratio= 67 NbOLKDefects= 47 
Case Test14
mkodt -F NewTopologicalObjects.tst -s TestSimplify
*/
//
// TopologicalOperator.tst CreateFace31 et tout autre CreateFace*  
//#define RootContainerCGM_OLK_Defects_Compatible_2009_12_17
/*
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	80
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	81
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	258
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	259
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	436
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	437
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	614
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	615
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	792
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	793
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	970
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	971
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	1148
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	1149
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	1326
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	1327
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	1504
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	1505
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	1682
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	1683
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	1860
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	1861
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	2038
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	2039
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	2216
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	2217
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	2394
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	2395
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	2572
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	2573
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	2750
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	2751
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	2928
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	2929
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	3106
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	3107
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	3284
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	3285
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	3462
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	3463
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	3640
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	3641
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	3818
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	3819
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	3996
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	3997
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	4174
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	4175
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	4352
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	4353
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	4530
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	4531
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	4708
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	4709
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	4886
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	4887
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	5064
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	5065
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	5242
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	5243
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	5420
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	5421
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	5598
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	5599
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	5776
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	5777
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	5954
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	5955
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	6132
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	6133
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	6310
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	6311
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	6488
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	6489
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	6666
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	6667
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	6844
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	6845
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	7022
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	7023
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	7200
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	7201
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	7378
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	7379
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	7556
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	7557
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	7734
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	7735
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	7912
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	7913
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	8090
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	8091
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	8268
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	8269
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	8446
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	8447
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	8624
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	8625
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	8802
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	8803
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	8980
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	8981
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	9158
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	9159
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	9336
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	9337
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	9514
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	9515
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	9692
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	9693
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	9870
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	9871
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	10048
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	10049
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	10226
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	10227
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	10404
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	10405
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	10582
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	10583
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	10760
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	10761
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	10938
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	10939
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	11116
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	11117
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	11294
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	11295
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	11472
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	11473
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	11650
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	11651
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	11828
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	11829
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	12006
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	12007
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	12184
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	12185
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	12362
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	12363
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	12540
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	12541
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	12718
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	12719
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	12896
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	12897
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	13074
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	13075
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	13252
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	13253
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	13430
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	13431
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	13608
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	13609
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	13786
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	13787
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	13964
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	13965
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	14142
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	14143
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	14320
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	14321
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	14498
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	14499
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	14676
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	14677
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	14854
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	14855
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	15032
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	15033
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	15210
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	15211
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	15388
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	15389
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	15566
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	15567
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	15744
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	15745
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	15922
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	15923
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	16100
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	16101
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	16278
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	16279
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	16456
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	16457
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	16634
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	16635
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	16812
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	16813
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	16990
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	16991
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	17168
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	17169
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	17346
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	17347
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	17524
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	17525
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	17702
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	17703
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	17880
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	17881
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	18058
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	18059
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	18236
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	18237
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	18414
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	18415
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	18592
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	18593
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	18770
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	18771
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	18948
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	18949
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	19126
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	19127
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	19304
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	19305
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	19482
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	19483
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	19660
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	19661
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	19838
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	19839
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	20016
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	20017
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	20194
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	20195
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	20372
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	20373
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	20550
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	20551
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	20728
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	20729
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	20906
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	20907
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	21084
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	21085
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	21262
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	21263
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	21440
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	21441
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	21618
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	21619
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	21796
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	21797
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	21974
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	21975
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	22152
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	22153
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	22330
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	22331
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	22508
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	22509
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	22686
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	22687
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	22864
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	22865
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	23042
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	23043
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	23220
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	23221
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	23398
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	23399
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	23576
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	23577
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	23754
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	23755
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	23932
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	23933
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	24110
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	24111
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	24288
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	24289
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	24466
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	24467
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	24644
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	24645
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	24822
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	24823
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	25000
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	25001
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	25178
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	25179
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	25356
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	25357
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	25534
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	25535
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	25712
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	25713
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	25890
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	25891
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	26068
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	26069
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	26246
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	26247
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	26424
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	26425
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	26602
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	26603
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	26780
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	26781
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	26958
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	26959
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	27136
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	27137
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	27314
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	27315
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	27492
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	27493
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	27670
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	27671
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	27848
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	27849
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	28026
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	28027
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	28204
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	28205
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	28382
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	28383
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	28560
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	28561
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	28738
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	28739
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	28916
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	28917
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	29094
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	29095
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	29272
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	29273
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	29450
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	29451
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	29628
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	29629
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	29806
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	29807
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	29984
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	29985
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	30162
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	30163
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	30340
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	30341
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	30518
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	30519
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	30696
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	30697
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	30874
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	30875
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	31052
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	31053
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	31230
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	31231
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	31408
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	31409
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	31586
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	31587
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	31764
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	31765
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	31942
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	31943
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	32120
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	32121
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	32298
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	32299
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	32476
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	32477
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	32654
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	32655
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	32832
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	32833
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	33010
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	33011
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	33188
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	33189
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	33366
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	33367
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	33544
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	33545
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	33722
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	33723
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	33900
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	33901
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	34078
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	34079
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	34256
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	34257
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	34434
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	34435
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	34612
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	34613
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	34790
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	34791
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	34968
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	34969
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	35146
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	35147
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	35324
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	35325
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	35502
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	35503
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	35680
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	35681
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	35858
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	35859
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	36036
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	36037
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	36214
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	36215
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	36392
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	36393
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	36570
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	36571
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	36748
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	36749
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	36926
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	36927
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	37104
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	37105
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	37282
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	37283
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	37460
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	37461
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	37638
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	37639
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	37816
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	37817
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	37994
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	37995
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	38172
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	38173
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	38350
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	38351
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	38528
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	38529
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	38706
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	38707
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	38884
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	38885
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	39062
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	39063
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	39240
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	39241
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	39418
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	39419
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	39596
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	39597
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	39774
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	39775
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	39952
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	39953
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	40130
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	40131
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	40308
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	40309
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	40486
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	40487
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	40664
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	40665
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	40842
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	40843
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	41020
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	41021
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	41198
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	41199
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	41376
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	41377
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	41554
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	41555
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	41732
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	41733
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	41910
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	41911
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	42088
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	42089
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	42266
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	42267
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	42444
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	42445
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	42622
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	42623
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	42800
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	42801
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	42978
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	42979
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	43156
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	43157
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	43334
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	43335
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	43512
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	43513
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	43690
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	43691
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	43868
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	43869
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	44046
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	44047
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	44224
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	44225
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	44402
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	44403
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	44580
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	44581
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	44758
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	44759
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	44936
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	44937
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	45114
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	45115
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	45292
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	45293
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	45470
PurgeUndo: delete for 	CATPointOnEdgeCurveCGM	45471
PurgeUndo: CGMUsedBytes_before= 299008 cleaned= 69632 OLK_Bytes= 229376 OLK_ratio= 76 NbOLKDefects= 512 
*/
//----------------------------------------------------------------------------------------------------------
//#define RootContainerCGM_OLK_Defects_CAThkEdgeEmbryo_2009_12_17
//----------------------------------------------------------------------------------------------------------
/*
CGMTopologyTests.tst/FunctionTests/Output/intel_a/CGMReplay_UnFoldedAeroOperatorForRIClosure_It.traces
PurgeUndo: delete for CATPointOnEdgeCurveCGM 3781030 
PurgeUndo: delete for CATPointOnEdgeCurveCGM 3781031 
PurgeUndo: delete for CATPointOnEdgeCurveCGM 3781037 
PurgeUndo: delete for CATPointOnEdgeCurveCGM 3781038 
PurgeUndo: delete for CATPointOnEdgeCurveCGM 3781044 
PurgeUndo: delete for CATPointOnEdgeCurveCGM 3781045 
PurgeUndo: delete for CATPointOnEdgeCurveCGM 3781050 
PurgeUndo: delete for CATPointOnEdgeCurveCGM 3781051 
PurgeUndo: CGMUsedBytes_before= 339968 cleaned= 286720 OLK_Bytes= 53248 OLK_ratio= 15 NbOLKDefects= 8
*/
//----------------------------------------------------------------------------------------------------------

#endif
