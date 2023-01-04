/* -*-c++-*- */
#ifndef CATGemDumpLimits_H_
#define CATGemDumpLimits_H_
// COPYRIGHT DASSAULT SYSTEMES  2002
//============================================================================
//  Enumeration
//============================================================================
typedef unsigned int CATGemDumpLimits;


#define CATGemDumpLimits_Col_Object                 0x00000001
#define CATGemDumpLimits_Col_UsefulLimits           0x00000002
#define CATGemDumpLimits_Col_MaxLimits              0x00000004
#define CATGemDumpLimits_Col_CurrentLimits          0x00000008
#define CATGemDumpLimits_Col_Weights                0x00000010
#define CATGemDumpLimits_Col_LevelDependancy        0x00000040
#define CATGemDumpLimits_Col_StreamSize             0x00000100

#define CATGemDumpLimits_Row_WithOkayLimits         0x00100000
#define CATGemDumpLimits_Row_OnlyWithKnotVector     0x00200000
#define CATGemDumpLimits_Row_WithUnavailableLimits  0x00400000

#define CATGemDumpLimits_Default                    0x00000057

#define CATGemDumpLimits_MAXIMUM                    0xFEFFFFFF

#endif
