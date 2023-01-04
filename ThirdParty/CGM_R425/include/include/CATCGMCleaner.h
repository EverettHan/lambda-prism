/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 */
/* -*-c++-*- */
#ifndef CATCGMCleanerInterface_H_
#define CATCGMCleanerInterface_H_
//=============================================================================
// Data for managing CGM cleaner activation and calls
//=============================================================================
#include "ExportedByGeometricObjects.h"
#include "CATMathInline.h"
#include "CATGeoFactory.h"

#include "CATCGMCleanerActivation.h"


class ExportedByGeometricObjects CATCGMCleaner: public CATBaseUnknown
{
public:

  enum FailureMode {CATCGMCleanerNone  =  0,  CATCGMCleanerThrow =  1, CATCGMCleanerAssert = 2};

  //---------------------------------------------------------------------------
  // Constructors/Destructor
  //---------------------------------------------------------------------------
  CATCGMCleaner();
  CATCGMCleaner(const CATCGMCleaner& copy);

  ~CATCGMCleaner();


  //---------------------------------------------------------------------------
  // DeleteStaticCGMRuleDefsAndCGMRules 
  //   GetEnvFailureMode 
  //   SetFailureMode 
  //   GetFailureMode 
  //---------------------------------------------------------------------------

  static void                          DeleteStaticCGMRuleDefsAndCGMRules();

  static CATCGMCleaner::FailureMode    GetEnvFailureMode();

  static void                          SetFailureMode(CATCGMCleaner::FailureMode iMode);

  static CATCGMCleaner::FailureMode    GetFailureMode();

  //---------------------------------------------------------------------------
  // CATGemEvtGenericNamed event management
  //---------------------------------------------------------------------------
  static void                          ActivateCATGemEvtGenericNamedRules();

  //---------------------------------------------------------------------------
  // Mise a jour des CATCGMRuleDef::_pStaticTableChkCGMEntsKO
  //          et des CATCGMRuleDef::_pStaticTableChkCGMEntsKOWitns
  //---------------------------------------------------------------------------
  static void                          DeleteStaticTablesOfChkCGMEnts(CATGeoFactory* ipGeoFactory = NULL);

  static void                          SetShowErrorDialogs(CATBoolean iMode = TRUE);

  static CATBoolean                    IsShowErrorDialogs();

  static CATBoolean                    IsActive();

  //---------------------------------------------------------------------------
  // ...
  //---------------------------------------------------------------------------
  static void                          ActivateApplyCreatedCGMRulesTraces(CATBoolean iForce = TRUE);

  static CATCGMRuleDefHashTable *      CreateStaticTabOfAllCGMRuleDefs(CATBoolean iOnCompletedRules);

  static CATULONG32                    Dec_NB_AtCompletedAndActive_Rules();

  static void                          DecodeCodeLevel                 (int iCodeLevel, char* ioBuffer);

   static int                          DetectUserActivatedRulesForPerfo(CATCGMCleanerImpl*           ipThisCleaner,
                                                                        CATSoftwareConfiguration*    ipSoftConf,
                                                                        CATICGMUnknown*              ipSpecificToCheck,
                                                                        CATListOfInt*                ipSpecificRuleIDs,
                                                                        CATCX_CHECKUP*               iopCATCX_Report,
                                                                        CATCGMCheckBehavior*         ipCheckBehavior,
                                                                        CATCGMCheckClean::CallMethod iCallMethod,
                                                                        CATLISTP(CATICGMObject)*     ipPreCalculatedAllLinks);

  static CATULONG32                    DumpCGMRuleStats(ostream* ipOutput);

  static void                          FillExtendedCheckErrorMsg       (CATCheckRule*                ipCheckRule,
                                                                        CATListValCATUnicodeString*  iopListExtendedErrorMsg);

  static void                          FillExtendedCleanErrorMsg       (CATCheckRule*                ipCheckRule,
                                                                        CATListValCATUnicodeString*  iopListExtendedErrorMsg);

  static void                          ForceActivateAllCGMRules(CATBoolean iForce = TRUE);

  static CATULONG32                    GetBreakpointTag();
  
  static void                          GetCleanMessages(CATCheckRule    * ipCheckRule,
                                                        CATUnicodeString& ioMessage  ,
                                                        CATUnicodeString& ioShortMessage);

  static void                          GetEnvRules(CATListOfCATUnicodeString* iopListEnvRules = NULL,
                                                   CATListOfCATUnicodeString* iopListEnvOFFRules = NULL,
                                                   CATListOfCATUnicodeString* iopListODTRules = NULL);

  static CATCGMRuleDef               * Get_ORIGINAL_CGM_RULE_DEF_FromNumInTab(const int iRuleNum);

  static CATULONG32                    Inc_NB_AtCompletedAndActive_Rules();

  static CATBoolean                    IsBreakpoint();

  static CATBoolean                    IsDumpCallStack();

  static CATBoolean                    IsShowTraces(CATCGMCheckRule* ipCGMCheckRule = NULL);

  static void                          SetActive(CATBoolean iMode = TRUE);

  static void                          SetBreakpoint(CATBoolean iMode);

  static void                          SetBreakpointTag(CATULONG32  iTag = 0);

  static void                          SetDumpCallStack(CATBoolean iMode = TRUE);

  static void                          SetShowTraces(CATBoolean iMode = TRUE);

  static void                          SetVerbose(CATBoolean iVerbose);
};

 
#endif
