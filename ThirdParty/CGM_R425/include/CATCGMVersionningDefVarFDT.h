#ifndef CATCGMVersionningDefVarFDT_h
#define CATCGMVersionningDefVarFDT_h

// ------------------------------------------------------------------------
// CONTENT
// ------------------------------------------------------------------------
// A.  SUB INCLUDE FILES
// B. NOT YET ACTIVATED VARIABLES
// C. VARIABLES THAT HAVE TO BE KEPT
// D. VARIABLES FOR TEMPORARY DECLARATION  -  THEY SHOULD BE CLEAN
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// A.  SUB INCLUDE FILES
// ------------------------------------------------------------------------
#include "CATCGMVersionningDefVarRR.h"
#include "CATCGMVersionningDefVarPRL.h"
#include "CATCGMVersionningDefVarHLN.h" 
#include "CATCGMVersionningDefVarJQS.h"  
#include "CATCGMVersionningDefVarREN.h" 
#include "CATCGMVersionningDefVarDBS.h" 
#include "CATCGMVersionningDefVarAJT1.h" 
#include "CATCGMVersionningDefVarPune.h" 
#include "CATCGMVersionningDefVarLSO.h"
#include "CATCGMVersionningDefVarRL1.h"

// ------------------------------------------------------------------------
// B. NOT YET ACTIVATED VARIABLES
// ------------------------------------------------------------------------
#ifndef CGM_Versionning_NouvelleVariable1FDT
#define CGM_Versionning_NouvelleVariable1FDT 32000 // XXX 2006/mm/dd
#endif

#ifndef   CGM_Versionning_RelimInit_FreeContactLoop
#define CGM_Versionning_RelimInit_FreeContactLoop 32000 // PRL 2005/03/09
#endif

#ifndef CGM_Versionning_Draft_EmptySkinAfterRelim
#define CGM_Versionning_Draft_EmptySkinAfterRelim 32000 // PFV 2005/04/11
#endif

#ifndef CGM_Versionning_Fillet_SelfIgnoreSharpEdge
#define CGM_Versionning_Fillet_SelfIgnoreSharpEdge 32000 // JHG 2005/08/18
#endif

#ifndef CGM_Versionning_GeodesicParallel_R18SP5
#define CGM_Versionning_GeodesicParallel_R18SP5 32000 // IZE 2008/02/22
#endif 

#ifndef CGM_Versionning_Parallel_ZTwistPostTreatment
#define CGM_Versionning_Parallel_ZTwistPostTreatment 32000 // IZE 2008/02/18
#endif 

#ifndef CGM_Versionning_Parallel_R19SP5
#define CGM_Versionning_Parallel_R19SP5 32000// IZE 2009/01/08
#endif

#ifndef CGM_Versionning_GeodesicParallel_ImprovedInitSearch
#define CGM_Versionning_GeodesicParallel_ImprovedInitSearch 32000 // IZE 2009/09/08
#endif

#ifndef CGM_Versionning_Fillet_HoldCurveUntwist
#define CGM_Versionning_Fillet_HoldCurveUntwist 32000 // IZE
#endif

#ifndef CGM_Versionning_Fillet_MultiRibbonDelayShorten
#define CGM_Versionning_Fillet_MultiRibbonDelayShorten 32000 //IZE 2010/10/14
#endif 

#ifndef CGM_Versionning_FilletRecognition_ForbidJointsMonoCtxt
#define CGM_Versionning_FilletRecognition_ForbidJointsMonoCtxt 32000 // IZE 2016/09/02
#endif

#ifndef CGM_Versionning_LiveFillet_RepsConnexitySameSupports
#define CGM_Versionning_LiveFillet_RepsConnexitySameSupports 32000 // IZE 2016/10/06
#endif

#ifndef CGM_Versionning_FilletRecog_BonesTypesOrdering
#define CGM_Versionning_FilletRecog_BonesTypesOrdering 32000 // IZE 2016/11/07
#endif

// ------------------------------------------------------------------------
// C. VARIABLES THAT HAVE TO BE KEPT - SHOULD BE EMPTY
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// D. VARIABLES FOR TEMPORARY DECLARATION  -  THEY MUST BE CLEANED BY THE CREATOR AFTER A FEW WEEKS - DO NOT HESITATE TO USE YOUR OWN FILE.
// ------------------------------------------------------------------------
#ifndef CGM_Versionning_RuledUnfoldRobustness_ForPlanarDirectrix
#define CGM_Versionning_RuledUnfoldRobustness_ForPlanarDirectrix 32000 // VDA3 06 June 17
#endif

#ifndef CGM_Versionning_PlanarSupportSwitchGeodesicToEuclidean
#define CGM_Versionning_PlanarSupportSwitchGeodesicToEuclidean 32000 // S9L23052017
#endif

#ifndef CGM_Versionning_ConnectUtility_ParallelConnectCustomizedLinearityCheck
#define CGM_Versionning_ConnectUtility_ParallelConnectCustomizedLinearityCheck 32000 // S9L29052017
#endif

#ifndef CGM_Versionning_UnfoldTransferWireExtremitiesJournal
#define CGM_Versionning_UnfoldTransferWireExtremitiesJournal 32000 // VDA3 02 June 2017
#endif

#ifndef CGM_Versionning_WallFacesAnalyzer_QuasiOffsetRobustness_3
#define CGM_Versionning_WallFacesAnalyzer_QuasiOffsetRobustness_3 32000 // YT5 October 2018
#endif

#ifndef CGM_Versionning_GMLiveShape_R421_03b
#define CGM_Versionning_GMLiveShape_R421_03b 8602 // ST5 April 2019
#endif

#ifndef CGM_Versionning_GMLiveShape_R423_FD03
#define CGM_Versionning_GMLiveShape_R423_FD03 9527 // QF2 Sept 2020
#endif

#ifndef CGM_Versionning_HiddenSeamPropagation_Level1
#define CGM_Versionning_HiddenSeamPropagation_Level1 9783 // VB7 April 2021
#endif

#endif


