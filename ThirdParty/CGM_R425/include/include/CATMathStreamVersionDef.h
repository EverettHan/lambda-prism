#ifndef CATMathStreamVersionDef_h
#define CATMathStreamVersionDef_h
// COPYRIGHT DASSAULT SYSTEMES  2007
#include "CATIACGMLevel.h"

/** @CAA2Required */
/**
 * Previous Stream levels definition
 */

//---------------------------------------------------------------------------
// Changes concerning CGM Data 
//   are managed under a mandatory control of CATCGMStreamVersion
// 
// From beginning of 2009 and Multi Level Collaboration
// Forecoming Data Version Format of CGM Persistency definition and management 
//  are declared in ProtectedInterfaces\CATCGMStreamVersionLimited.h
//
//---------------------------------------------------------------------------

#ifndef CATCGMStreamVersion
#define CATCGMStreamVersion int
#endif

// According to correction  bring inside
//    CATCGMStreamIsNewerThanOrEqualTo  / 
//    dynamic session version, never stored ..

// CGM Until 2008 (V5R15-V5R19)

#define    CatCGMStream_R207GA        +1316   
#define    CatCGMStream_R206GA        +1131
#define    CatCGMStream_V5R19GA       +1130

// (CLS) 
#define    CatCGMStream_R205GA        +1124   
// (john doe) -> CatCGMStream_V5R18GA
#define    CatCGMStream_R204GA        +1123  
// (john doe)
#define    CatCGMStream_R203GA        +1122   
// (john doe)
#define    CatCGMStream_R202GA        +1121   
#define    CatCGMStream_V5R18GA       +1120

//comme R17 (john doe) -> CatCGMStream_R20117 
#define    CatCGMStream_R20117        +1113   
#define    CatCGMStream_V5R17GA       +1112

//comme R16 (john doe) -> CatCGMStream_V5R16GA 
#define    CatCGMStream_R201GA        +1109  
#define    CatCGMStream_V5R16GA       +1108

// Cf (convergenc john doe/ Read)
#define    CatCGMStream_BetaVolatile  +1106 
#define    CatCGMStream_V5R15GA       +1105

// CGM Until 2004 (V5R0-V5R14)

#define    CatCGMStream_V5R14GA  +1104
#define    CatCGMStream_V5R13GA  +1014
#define    CatCGMStream_V5R12GA  +1013
#define    CatCGMStream_V5R11GA  +1012
#define    CatCGMStream_V5R10GA  +1011
#define    CatCGMStream_V5R9GA   +1010

#define    CatCGMStream_V5R8GA  +1009
#define    CatCGMStream_V5R7GA  +1008
#define    CatCGMStream_V5R6GA  +1007
#define    CatCGMStream_V5R5GA  +1006
#define    CatCGMStream_V5R4GA  +1005
#define    CatCGMStream_V5R3GA  +1004
#define    CatCGMStream_V5R2GA  +1003
#define    CatCGMStream_V5R1GA  +1002
#define    CatCGMStream_V5R0GA  +1001
#define    CatCGMStream_V5R001  +1000

#ifndef    CatCGMStream_UnknownVersion
#define    CatCGMStream_UnknownVersion  +999
#endif

 

#endif /* CATMathStreamVersionDef_h */
