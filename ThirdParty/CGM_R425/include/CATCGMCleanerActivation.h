/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 */
/* -*-c++-*- */
#ifndef CATCGMCleanerActivation_H_
#define CATCGMCleanerActivation_H_
//=============================================================================
// Data for managing CGM cleaner activation and calls
//=============================================================================
// Oct. 02  Creation                                                      HCN
// Nov. 02  CATCGMCleanerIsActive()                                       HCN
// Jan. 03  CATCGMCleanerOFFRules                                         HCN
// Aug. 03  CATCGMCleanerFatEdge, CATCGMCleanerFatEdgeIsActive()          HCN
// Oct. 03  CATCGMCleanerFatEdgeLyingOn, CATCGMFatEdgeLyingOn(),
//          CATCGMCleanerFatEdgeInWire, CATCGMFatEdgeInWire(),
//          CATCGMQueryManagerFollowTag, CATCGMQueryManagerGetFollowedTag() HCN
// Oct. 03  CATCGMCleanerFatEdgeCompleted, CATCGMFatEdgeCompleted()       FDN
// Nov. 03  CATCGMPurgeUndo et CATCGMPurgeUndoIsActive()
//          CATCGMFatEdgeOKInOther()
//          Argument iQueryCATTrace a CATCGMCleanerIsActive(...),
//          CATCGMCleanerCGMRuleStats et CATCGMCleanerCGMRuleStatsIsActive() HCN
// Nov. 03  CATCGMCleanerFatEdgeNoBorder et CATCGMFatEdgeNoBorder()       FDN
// Dec. 03  CATCGMCleanerFatEdgeCanonic et CATCGMFatEdgeCanonic(),
//          CATCGMCleanerPerfTest et CATCGMCleanerFatEdgeIsActive(),
//          "CATCGMCleanerCheckMethod" a la place de "CATCGMCleanerExportedMethod",
//          CATCGMCleanerRuleMethodBeginName,
//          CATCGMCleanerRuleMethodAddName                                HCN
// Jan. 04  CATCGMCleanerFatEdgeNoCleanCP et CATCGMFatEdgeNoCleanCP()     HCN
// Jun. 04  CATCGMCleanerCheckUpStats,
//          CATCGMCleanerCheckUpStatsIsActive()                           HCN
// Nov. 05  GetCATCGMCleanerFailureMode                                   FDN
//=============================================================================

#include "ExportedByGeometricObjects.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATBaseUnknown.h"
#include "CATCGMCheckClean.h"
#include "CATListOfCATUnicodeString.h"
#include "CATListOfCATCGMObjects.h"
#include "CATUnicodeString.h"
#include "CATListOfInt.h"
 
class CATCGMCleanerImpl;
class CATSoftwareConfiguration;
class CATICGMUnknown;
class CATCX_CHECKUP;
class CATCGMCheckBehavior;
class CATCX_CHECKUP;
class CATCheckRule;
class CATListValCATUnicodeString;
class CATCGMRuleDef;
class CATCGMCheckRule;
class CATCGMRuleDefHashTable;
 

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif



#define CATCleanerAppliCATTraceName          "CleanerTracer"

#define CATCleanerAppliCATTraceComment       "Traces Application Cleaner Officielle"

#define CATCleaner_ODT_DOC_CHECK             "ODT_DOC_CHECK"

#define CATCGMCleanerSharedLibrary           "CATCGMCleaner"

#define CATCGMCleanerCheckMethodName         "CATCGMCleanerCheckMethod"

#define CATCGMCleanerRuleMethodBeginName     "CATCGMCleanerBeginRuleMethod"

#define CATCGMCleanerRuleMethodAddName       "CATCGMCleanerAddRuleMethod"
 

#define CATCGMCleanerRuleMethodVerifyName    "CATCGMCleanerVerifyRuleMethod"

#define CATCGMCleanerCATTraceName            CATCGMCleanerSharedLibrary

#define CATCGMCleanerCATTraceComment         "Automatic Topological Cleaner at each Body->Completed()"

#define CATCGMCleanerCGMRuleStats            "CATCGMCleanerCGMRuleStats"

#define CATCGMCleanerCheckUpStats            "CATCGMCleanerCheckUpStats"

#define CATCGMCleanerPerfTest                "CATCGMCleanerPerfTest"

#define CATCGMCleanerRules                   "CATCGMCleanerRules"

#define CATCGMCleanerOFFRules                "CATCGMCleanerOFFRules"

#define CATCGMCleanerVerbose                 "CATCGMCleanerVerbose"

#define CATCheckCleanFollowTag               "CATCheckCleanFollowTag"

#define CATCheckCleanOnCompleted             "CATCheckCleanOnCompleted"

#define CATCGMCleanerFatEdge                 "CATCGMCleanerFatEdge"

#define CATCGMCleanerFatEdgeLyingOn          "CATCGMCleanerFatEdgeLyingOn"

#define CATCGMCleanerFatEdgeInWire           "CATCGMCleanerFatEdgeInWire"

#define CATCGMCleanerFatEdgeOKInOther        "CATCGMCleanerFatEdgeOKInOther"

#define CATCGMCleanerFatEdgeCanonic          "CATCGMCleanerFatEdgeCanonic"

#define CATCGMCleanerFatEdgeNoCleanCP        "CATCGMCleanerFatEdgeNoCleanCP"

#define CATCGMQueryManagerFollowTag          "CATCGMQueryManagerFollowTag"

#define CATCGMCleanerFatEdgeCompleted        "CATCGMCleanerFatEdgeCompleted"

#define CATCGMPurgeUndo                      "CATCGMPurgeUndo"

#define CATCGMCleanerFatEdgeNoBorder         "CATCGMCleanerFatEdgeNoBorder"

ExportedByGeometricObjects CATBoolean CATCGMCleanerIsActive(CATBoolean iQueryCATTrace = TRUE);

// Usage interne cleaner uniquement
ExportedByGeometricObjects int        GetCATCGMCleanerFailureMode();

// Ne pas appeler : pour la classe CATCGMCleaner seulement
ExportedByGeometricObjects void       CATCGMCleanerActivateCATTrace(CATBoolean iMode);

ExportedByGeometricObjects CATBoolean CATCGMCleanerCGMRuleStatsIsActive();

ExportedByGeometricObjects CATBoolean CATCGMCleanerCheckUpStatsIsActive();

// 1 => return at rule check
// 2 => return at rule check and specific call
// 3 => return at rule check and completed call
ExportedByGeometricObjects int        CATCGMCleanerPerfTestIsActive();

ExportedByGeometricObjects CATBoolean CATCGMCleanerFatEdgeIsActive();

ExportedByGeometricObjects CATBoolean CATCGMFatEdgeLyingOn();

ExportedByGeometricObjects CATBoolean CATCGMFatEdgeInWire();

ExportedByGeometricObjects CATBoolean CATCGMFatEdgeOKInOther();

ExportedByGeometricObjects CATBoolean CATCGMFatEdgeCanonic();

ExportedByGeometricObjects CATBoolean CATCGMFatEdgeNoCleanCP();

ExportedByGeometricObjects CATULONG32 CATCGMQueryManagerGetFollowedTag();

ExportedByGeometricObjects int        CATCGMFatEdgeCompleted();

ExportedByGeometricObjects CATBoolean CATCGMPurgeUndoIsActive();

ExportedByGeometricObjects CATBoolean CATCGMFatEdgeNoBorder();

// A commenter
// #define CATCGM_TRACES_DEBUG_QUERY_MANAGER
// => Rebuilder NewTopologicalObjects

// A commenter
// #define CATCGM_TRACES_DEBUG_FATABLE
// => Rebuilder CATGem CGMV5Interoperability CGMV5SpecsQuery GeometricObjectsCGM GeometricObjects NewTopologicalObjects NewTopologicalObjectsCGM

// A commenter
// #define CATCGM_TRACES_DEBUG_FATEDGE
// => Rebuilder CATGem CGMV5Interoperability CGMV5SpecsQuery GeometricObjectsCGM GeometricObjects NewTopologicalObjects NewTopologicalObjectsCGM


/**
*  CATCGMObjectToOperator Mapping 
*/
class CATCGMCleanerBridge;
#include "CATMathInline.h"

#include "CATGeoFactory.h"
#include "CATBoolean.h"

#include "CATCGMCleaner.h"



#endif
