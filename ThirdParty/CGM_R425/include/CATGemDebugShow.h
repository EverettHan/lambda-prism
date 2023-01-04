/* -*-c++-*- */
#ifndef CATGemDebugShow_H_
#define CATGemDebugShow_H_
// COPYRIGHT DASSAULT SYSTEMES  2002
//============================================================================
//  Enumeration
//============================================================================
typedef unsigned int CATGemDebugShow;


#define CATGemDebugShow_Col_Tag                   0x00000001
#define CATGemDebugShow_Col_FeatureName           0x00000002
#define CATGemDebugShow_Col_FeatureStatus         0x00000004

#define CATGemDebugShow_Col_FeatureLevel          0x00001000
#define CATGemDebugShow_Col_GeometryLevel         0x00002000

#define CATGemDebugShow_Col_NbCells               0x00000010
#define CATGemDebugShow_Col_NbNewObj              0x00000020
#define CATGemDebugShow_Col_NumberOfFeature       0x00000040
#define CATGemDebugShow_Col_NbDependancies        0x00000080

#define CATGemDebugShow_Col_DiskBytes             0x00000100
#define CATGemDebugShow_Col_MemBytes              0x00000200

#define CATGemDebugShow_Hash_Diezele              0x00010000

#define CATGemDebugShow_OnlyForCartography        0x00020000

#define CATGemDebugShow_Row_GoodFeatBody          0x00100000
#define CATGemDebugShow_Row_BadFeat               0x00200000
#define CATGemDebugShow_Row_RemainingFederator    0x00400000
#define CATGemDebugShow_Row_RemainingAll          0x00800000
#define CATGemDebugShow_Row_EveryObjectWithDepth  0x01000000


#define CATGemDebugShow_Default                   0x00300337

#endif
