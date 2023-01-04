#ifndef CATCGAMeasureGeneration_h
#define CATCGAMeasureGeneration_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//==========================================================================
//  September 01   Portage 64 bits                     http://pcs/ 
//==========================================================================
#include "CATUnicodeString.h"
#include "CATMathematics.h"

#define CATCGAMeasureGenerationY              "http://webtechno/"

#define CATCGAMeasureGenerationSTRING         "#1-2013-48-CATCGAMeasure"

#define CATCGAMeasureSectionClearance6WTags   "@ElucidationTags"
#define CATCGAMeasureSectionClearance6WTags_  ",\n"

#define CATCGAMeasureSectionFeedbacks         "@ElucidationFeedbacks"
#define CATCGAMeasureSectionFeedbacks_        ",\n"

#define CATCGAMeasureSectionCSI                  "@CSI"
#define CATCGAMeasureSectionCSI_Category         "Category"
#define CATCGAMeasureSectionCSI_Type             "Type"
#define CATCGAMeasureSectionCSI_Name             "Name"
#define CATCGAMeasureSectionCSI_NbMeasures       "#Measures"
#define CATCGAMeasureSectionCSI_MeanDepth        "MeanDepth"
#define CATCGAMeasureSectionCSI_MinimalHistory   "MinimalHistory"
#define CATCGAMeasureSectionCSI_RatioLucid       "%ELPS(lucid)"

#define CATCGAMeasureSectionCSI_ELPS             "ELPS(ms)"
#define CATCGAMeasureSectionCSI_CPU              "CPU(ms)"
#define CATCGAMeasureSectionCSI_ELPS_Inclusive   "ELPS_Inc(ms)"
#define CATCGAMeasureSectionCSI_CPU_Inclusive    "CPU_Inc(ms)"

#define CATCGAMeasureSectionCSI_MeanDiskSize     "MeanDisk(Bytes)"
#define CATCGAMeasureSectionCSI_MinDiskSize      "MinDisk(Bytes)"
#define CATCGAMeasureSectionCSI_MaxDiskSize      "MaxDisk(Bytes)"
#define CATCGAMeasureSectionCSI_WorkingSetDelta  "WorkingSetDelta"

#define CATCGAMeasureSectionCSI_HeapNb           "HeapNb"
#define CATCGAMeasureSectionCSI_HeapBytes        "HeapBytes"
#define CATCGAMeasureSectionCSI_HeapBlocks       "HeapBlocks"

#define CATCGAMeasureSectionCSI_DLLDelta         "DLL(Delta)"
#define CATCGAMeasureSectionCSI_NbErrors         "#Errors"
#define CATCGAMeasureSectionCSI_Ticks            "Ticks"
#define CATCGAMeasureSectionCSI_ObjCreated       "ObjCreated"
#define CATCGAMeasureSectionCSI_ObjDeleted       "ObjDeleted"

#define CATCGAMeasureSectionCSI_PerCentNbMeasures   "%NbMeasures"
#define CATCGAMeasureSectionCSI_PerCentELPS         "%ELPS"
#define CATCGAMeasureSectionCSI_PerCentCPU          "%CPU"

#define CATCGAMeasureSectionClearance         "@Elucidation"
#define CATCGAMeasureSectionClearance_        ",Indicator,Value,\n" 

#define CATCGAMeasureSectionDLL               "@DLL"
#define CATCGAMeasureSectionDLL_              ",Name,Bytes,Framework,SCM_Tree,Responsible,LocalPath,\n"

#define CATCGAMeasureSectionGMLeaks           "@GMLeaks"
#define CATCGAMeasureSectionGMLeaksTail      ",ErrorName,#,Scenario,Message,\n"
 
#define CATCGAMeasureSectionGMErrors          "@GMErrors"
#define CATCGAMeasureSectionGMErrors_         ",Scenario,MsgCatalog,MsgID,ErrorName,#,Message,\n"
 
#define CATCGAMeasureSectionLeanRoots         "@FilteredLeanRoots"
#define CATCGAMeasureSectionLeanRoots_        ",ObjectName,\n"

#define CATCGAMeasureSectionVariableNodes     "@VariableNodes"
#define CATCGAMeasureSectionVariableNodes_    ",NodeName,,,\n"
 
#define CATCGAMeasureSectionStackTraces       "@StackTraces"
#define CATCGAMeasureSectionStackTraces_      ",LineOfStackTraces,\n"

#define CATCGAMeasureSectionMiscellaneous     "@GMMiscellaneous"
#define CATCGAMeasureSectionMiscellaneous_    ",,\n"

#define CATCGAMeasureSectionAsynchronous      "@GMReplayAsynchronous"
#define CATCGAMeasureSectionAsynchronous_     ",Framework,ODTName,iOperatorId,Step,Scenario,SoftLevel,ControlStep,isFiltered,\n"

#define CATCGAMeasureSectionWorkingFeaturesByTypes       "@WorkingFeaturesByTypes"
#define CATCGAMeasureSectionWorkingFeaturesByInstances   "@WorkingFeaturesByInstances"
#define CATCGAMeasureSectionWorkingFeatures              "@WorkingFeatures"

#define CATCGAMeasureSectionOpRelations   "@OpRelations"
#define CATCGAMeasureSectionOpRelations_  ",Domain-Operation(Callee),#CalledBy,Comment,Domain-Operation(Caller),#Lean,#LeanDeltaWorkingSet,#New,#Del,#AllNew,#AllDel,#Locked,\n"

#define CATCGAMeasureSectionOperations    "@Operations"
#define CATCGAMeasureSectionOperations_   ",Domain-Operation,#Callers,Comment,#Calls,#Lean,#LeanDeltaWorkingSet, #New,#Del, #AllNew,#AllDel,#Locked,\n"

#define CATCGAMeasureSectionCATGeoAbendInfo  "@CATGeoAbendInfo"

#define CATCGAMeasureSectionInMemoryGMPOOL   "@InMemory.GMPOOL"
#define CATCGAMeasureSectionInMemoryGMPOOL_  ",Pool,#Objects,#Classes,PEAK,CUMUL,LEAK,Provider,Modus,\n"

#define CATCGAMeasureSectionInMemoryGMClasses   "@InMemory.GMClasses"
#define CATCGAMeasureSectionInMemoryGMClasses_  ",Class,Pool,#Born,#Leak,MaxBytes,%,#DW,PerPage,USED,\n"

#define CATCGAMeasureSectionInMemoryGMAtClose   "@InMemory.GMAtClose"
#define CATCGAMeasureSectionInMemoryGMAtClose_  ",Category,#Factories,#Objects,\n"

#define CATCGAMeasureKeyWordCPU                 "CPU_ms"
#define CATCGAMeasureKeyWordELPS                "Elapsed_ms"
#define CATCGAMeasureKeyWordTicks               "Ticks"
#define CATCGAMeasureKeyWordDLL                 "Modules"
#define CATCGAMeasureKeyWordGetCGMLevel         "GetCGMLevel"
#define CATCGAMeasureKeyWordObjectBytes         "ObjectBytes"
#define CATCGAMeasureKeyWordDLLBytes            "ModulesBytes"
#define CATCGAMeasureKeyWordWorkingSetPEAK      "WorkingSetGlobalPEAK"
#define CATCGAMeasureKeyWordGMPoolPeakMajorant  "WorkingSetGMPoolPEAKMajorant"
#define CATCGAMeasureKeyWordNbGeoFactoryLeak    "NbGeoFactoryLeak"

#define CATCGAMeasureKeyWordHeapBytesPEAK       "HeapBytesPEAK"
#define CATCGAMeasureKeyWordHeapNbBlocksPEAK    "HeapNbBlocksPEAK"
#define CATCGAMeasureKeyWordHeapNbPEAK          "HeapNbPEAK"

#define CATCGAMeasureKeyWordCurWorkingSetPEAK   "WorkingSetCurrentPEAK"
#define CATCGAMeasureKeyWordDataURLBytes        "DataURLBytes"
 
#define CATCGAMeasureKeyWordHeapLeakBytesPEAK       "HeapLeakBytesPEAK"
#define CATCGAMeasureKeyWordHeapLeakNbBlocksPEAK    "HeapLeakNbBlocksPEAK"
#define CATCGAMeasureKeyWordHeapLeakNbPEAK          "HeapLeakNbPEAK"


#define CATCGAMeasureKeyWordElucidationELPS            "ElucidationELPS"
#define CATCGAMeasureKeyWordElucidationCPU             "ElucidationCPU"
#define CATCGAMeasureKeyWordElucidationTicks           "ElucidationTicks"
#define CATCGAMeasureKeyWordElucidationWorkingSetDelta "ElucidationWorkingSetDelta"

#define CATCGAMeasureKeyWordElucidationRoots           "ElucidationRoots"
#define CATCGAMeasureKeyWordElucidationMeasures        "ElucidationMeasures"

#define CATCGAMeasureKeyWordLucidCPU               "Lucid_CPU"
#define CATCGAMeasureKeyWordLucidELPS              "Lucid_Elapsed"
#define CATCGAMeasureKeyWordLucidTicks             "Lucid_Ticks"
#define CATCGAMeasureKeyWordLucidWorkingSetDelta   "Lucid_WorkingSetDelta"

#endif

