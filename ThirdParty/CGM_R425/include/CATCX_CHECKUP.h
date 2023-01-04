/* -*-c++-*- */
#ifndef CATCX_CHECKUP_H
#define CATCX_CHECKUP_H
// COPYRIGHT DASSAULT SYSTEMES  1998
//=============================================================================
// CATCX_CHECKUP:  CGA geometry-topology checkup
//=============================================================================
// April 98 Delivery                                                      TCX
// Apr. 02  UpdateCheckBehaviourCurrentError                              HCN
// May  03  CATCGMCleanerExportedMethodType,
//          CGMCleanerCheck(...) a la place de SoftCheck(...)             HCN
// Jun. 03  CGMCleanerSpecificCheck(...)                                  HCN
// Oct. 03  Parametre CATGeoClnCheckParameter* pour
//             CATCGMCleanerExportedMethodType,
//             CGMCleanerCheck(...),
//             CGMCleanerSpecificCheck(...)                               HCN
// Dec. 03 CGMCleanerCheckSelectRuleBegin(...),
//         CGMCleanerCheckSelectRuleAdd(...),
//         CATCGMCleanerCheckMethodType a la place de CATCGMCleanerExportedMethodType,
//         CATCGMCleanerRuleMethodType
//         Suppression du parametre CATGeoClnCheckParameter* pour
//            CATCGMCleanerCheckMethodType(...),
//         Parametre CATLISTP(CATICGMObject)* pour
//            CATCX_CHECKUP::CGMCleanerCheck(...) et
//            CATCGMCleanerCheckMethodType                                HCN
// Avr. 04 struct CATGeoClnCheckParameter devient une classe              FDN
// Jun. 04 __NbSpecificCheckCalls, __NbBodyCompletedCalls, __NbPerformedChecks
//         __BodyCompletedCall,
//         DumpCGMRuleStats(...),
//         ResetCGMRuleStats()                                            HCN
// 18/06/08 NLD Ajout GetCheckUpId(), _CheckUpId, CATCX_CHECKUP_DummyCheckUpId
//=============================================================================
#include "ExportedByCATCGMFusion.h"
#include "CATUnicodeString.h"
#include "CATCGMCheck.h"
#include "CATCGMNewArray.h"
#include "CATGeoClnIDs.h"
#include "CATBooleanDef.h"
#include "CATListOfCATICGMObjects.h"
#include "CATCGMCheckClean.h"
#include "CATListOfInt.h"
#include  "CATListOfCATCGMObjects.h"

class CATError;
class CATGeometry;
class CATGeoFactory;
class CATICGMObject;
class CATCGMObject;
class CATCGMOutput;
class CATBaseUnknown;
class CATCGMContainer;
class CATUnicodeString;
class CATCXReport;
class CATCGMCheckBehavior;
class CATICGMUnknown;
class CATGeoClnCheckParameter;
class CATLISTP(CATGeoClnCheckParameter);
class CATCGMHashTable;
class CATCGMHashTableWithAssoc;
class CATCX_SetOfAnomalyManager;
class  CATSoftwareConfiguration;

#include "CATCGMLISTP_Declare.h"

CATCGMLISTP_DECLARE(CATCXReport);

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

class CATCGMAttribute;
class CATCX_CHECKUP;
class oper_NewTopo;

/**
* @nodoc implementation specifique 
* Cf NewTopologicalObjects\CheckUpTopo.m\src\
*        ioReport->Offense(...); // catcxcheckup_doc "CATSubdEdge::CheckUpInternal"
* Cf NewTopologicalObjects\CNext\resources\msgcatalog\Body.CATCX_CHECKUP.CATNls 
*/
typedef void CATCX_CheckUpAttribute(CATCGMAttribute  * iAttribute,
                                     CATCGMObject    * iHolder,
                                     CATCX_CHECKUP   * ioReport);


class ExportedByCATCGMFusion CATCX_CHECKUP
{
public: 
  CATCGMNewClassArrayDeclare;

  //---------------------------------------------------------------------------
  // Est-ce que le Checker est actif dans le contexte actuel ?
  //--------------------------------------------------------------------------
  static int IsActive(CATCGMObject *iObject);

  enum KindOfReport { onlyOffense=0,
                      onlyRespect=1,
                      verbose=2,
		                  OffenseWarning=3,
                      OffenseWarningCleaner=4,
                      onlyWarning=5,
                      onlyPotDeVin=6,
                      onlyCleaner=7,
                      OffenseCleaner=8};

  //---------------------------------------------------------------------------
  // For Usage purpose: create CATCX_CHECKUP and then Generate()
  //--------------------------------------------------------------------------
  //  KindOfEvent : nature of event detected : 
  //                  - Respect : one rule is certified
  //                  - Offense : abnormal situation has been detected
  //                  - Warning : ... 
  // KindOfReport : when the book of events is build, filter can be specified
  //                  on events that must be registred
  //  KindOfScan  : when scanning objects of CGMContainer, we may specified
  //                  filtered objects to be studied.      
  //-------------------------------------------------------------------------
  CATCX_CHECKUP(const CATUnicodeString iOperatorName, 
                CATBoolean             iForCompleted = FALSE);

  void SetFilter(const CATCX_CHECKUP::KindOfReport iHow = CATCX_CHECKUP::onlyOffense );
  
  enum KindOfScan   { onlyShowBody=0, allTopology=1 };
  enum KindOfEvent  { respect=0, offense=1, warning=2 };
  
  int Generate(CATGeoFactory                 * iFactory, 
               const CATLISTP(CATICGMObject) & iToCheck,
               const KindOfReport              iHow = onlyOffense );


  int Generate(CATCGMObject    *object,    const KindOfReport how=onlyOffense,        const int cumulate=0);
  int Generate(CATCGMContainer *container, const KindOfReport how=onlyOffense,  const KindOfScan filter=allTopology);

  ~CATCX_CHECKUP();

  void GetOperatorId(CATUnicodeString &name); 

  //-------------------------------------------------
  // printing on current output, the entire report
  //-------------------------------------------------
  friend ExportedByCATCGMFusion CATCGMOutput& 
    operator<<(CATCGMOutput& os,CATCX_CHECKUP *rep);
  
  ostream& DumpStream(ostream& ioStreamArea); 

  //-------------------------------------------------
  // Check Validity of pointer of Objects
  //-------------------------------------------------
  int IsInvalidCATICGMObject(CATICGMObject *iObject, const char IdentifyContext[] );

  int IsInvalidCATCGMObject(CATCGMObject *iObject, const char IdentifyContext[] );

  //-------------------------------------------------------------------------
  // For Implementation purpose, to incorporate FACT in the final report
  //-------------------------------------------------------------------------
  // To allow Continuous Improvement process (evolution Vs ODT correction) 
  //      true Error can be temporary degenerated as PotDeVin,
  //      waiting for developper to correct code.
  //-------------------------------------------------------------------------
  
  CATCXReport * Offense(CATCGMCheck::Category category, CATCGMObject *topo, 
       const char rule[], const char offense[],
       const int nbWitness=0, CATCGMObject*const *witnesses=NULL, 
       const int nbint=0, const int *tabint=NULL,
       const int nbother=0, CATUnicodeString *const others=NULL,
       const int potDeVin=0,
       const CATGeoClnIDs::RuleID CGMRuleID = CATGeoClnIDs::UndefinedRule);
    
  CATCXReport * OffenseIfCreatedPotDeVinOtherwise(CATCGMCheck::Category category, CATCGMObject *topo, 
       const char rule[], const char offense[],
       const int nbWitness=0, CATCGMObject*const *witnesses=NULL, 
       const int nbint=0, const int *tabint=NULL,
       const int nbother=0, CATUnicodeString *const others=NULL,
       const CATGeoClnIDs::RuleID CGMRuleID = CATGeoClnIDs::UndefinedRule);

  CATCXReport * PotDeVin(CATCGMCheck::Category category, CATCGMObject *topo,
       const char rule[], const char offense[],
       const int nbWitness=0, CATCGMObject*const  *witnesses=NULL, 
       const int nbint=0, const int *tabint=NULL,
       const int nbother=0, CATUnicodeString *const others=NULL);
  
  CATCXReport * KeepItAsBribe(CATCGMCheck::Category category, CATCGMObject *topo,
       const char rule[], const char offense[],
       const int nbWitness=0, CATCGMObject*const  *witnesses=NULL, 
       const int nbint=0, const int *tabint=NULL,
       const int nbother=0, CATUnicodeString *const others=NULL,
       const CATGeoClnIDs::RuleID CGMRuleID = CATGeoClnIDs::UndefinedRule);

  CATCXReport * Warning(CATCGMObject *topo, const char rule[], const char offense[],
       const int nbWitness=0, CATCGMObject*const *witnesses=NULL, 
       const int nbint=0, const int *tabint=NULL,
       const int nbother=0, CATUnicodeString *const others=NULL,
       const CATGeoClnIDs::RuleID CGMRuleID = CATGeoClnIDs::UndefinedRule);
  
  CATCXReport * Respect(CATCGMObject *topo, const char rule[],
       const int nbWitness=0, CATCGMObject*const *witnesses=NULL,
       const int nbint=0, const int *tabint=NULL,
       const int nbother=0, CATUnicodeString *const others=NULL);
  
  //-------------------------------------------------------------------------
  // To tranform GeometricOperators Check Errors into CheckUp
  //-------------------------------------------------------------------------
  CATCXReport * ReportError(CATCGMObject* topo, CATCGMObject* geo, CATError    * err,
                   CATCGMCheck::Category category = CATCGMCheck::NotClassified,
                   const int potDeVin=0);

  //-------------------------------------------------------------------------
  // To avoid useless comtation in report of Respect
  //       1: Respect Event needed in Report
  //       0: No Respect Event Needed
  //-------------------------------------------------------------------------
   int IsWithRespect();
   int IsWithWarning();
   int IsWithOffensePotDeVin();

   //-------------------------------------------------------------------------
   // Identify the Federator Object currently beeing checked
   //-------------------------------------------------------------------------
   CATCGMObject    *WhoIsBeeingChecked(); 

  //----------------------------------------------------------------------
  // Generate Interactive panel from low-level framework
  //    View : for Ketchup command generation
  //    Dump : for Dump (RAD) panel ...
  //    QuickView : for quick panel generation on the fly
  //----------------------------------------------------------------------
  static void View(CATCGMObject *body);    
  static void Dump(CATCGMObject *body);    
  static void QuickView(CATCX_CHECKUP *check=NULL,CATCGMObject *body=NULL, const char IdentityBuildOperator[] = "");
  
  //------------------------------------------------------
  // extract sub-report concerning one object
  //  (do not forget to delete the collection returned)
  //------------------------------------------------------
  CATLISTP(CATCXReport) * GetReportOn(CATCGMObject *const concerned, const KindOfReport filter=verbose);  
  int NumberOfRepressiveErrors();    
  int NumberOfErrors();    
  int NumberOfWarnings(); 
  int NumberOfCleaners();
  
  //-----------------------------------------------------------------------
  // For Environnement Tuning
  //-----------------------------------------------------------------------
  static CATUnicodeString DecodeParagraph(CATCXReport *const event, 
                  int & nbobject,  CATCGMObject* * &objects, 
                  KindOfEvent &nature,const int withHeader=1); 
  static CATCGMObject *DecodeMainObject(CATCXReport*const event,
                  KindOfEvent &nature);
  //-----------------------------------------------------------------------
  // For CGM Check
  //-----------------------------------------------------------------------

  static void CGMCleanerCheck(CATICGMUnknown*              ipSpecificToCheck,
                              CATListOfInt*                ipSpecificRuleIDs,
                              CATCGMCheckClean::CallMethod iCallMethod,
                              CATCX_CHECKUP*               iopCATCX_Report,
                              CATCGMCheckBehavior*         ipCheckBehavior);

  static void CGMCleanerCheck(CATICGMUnknown*                    ipSpecificToCheck,
                              CATListOfInt*                      ipSpecificRuleIDs,
                              CATLISTP(CATGeoClnCheckParameter)* ipRuleCheckParameters,
                              CATCGMCheckClean::CallMethod       iCallMethod,
                              CATCX_CHECKUP*                     iopCATCX_Report,
                              CATCGMCheckBehavior*               ipCheckBehavior,
                              CATLISTP(CATICGMObject)*           ipPreCalculatedAllLinks);

  static CATBoolean CGMCleanerCheckVerifyRuleActivation(CATGeoClnIDs::RuleID ipSpecificRuleID);

  static void CGMCleanerCheckSelectRuleBegin(CATGeoClnIDs::RuleID ipSpecificRuleID, CATGeoClnCheckParameter* ipRuleCheckParameter = NULL);
  static void CGMCleanerCheckSelectRuleAdd(CATGeoClnIDs::RuleID ipSpecificRuleID, CATGeoClnCheckParameter* ipRuleCheckParameter = NULL);

 

  static void CGMCleanerSpecificCheck(CATICGMUnknown * ipSpecificToCheck,
                                      CATCX_CHECKUP  * iReport = NULL);


  static CATBoolean IsCheckUpAlreadyCreated();
  static CATCX_CHECKUP * CreateCheckUpForCompleted(CATCGMObject *body,  const char IdentityBuildOperator[]);
  static void DeleteCheckUpForCompleted();

  //---------------------------------------------------------------------------
  // Entry Points
  //---------------------------------------------------------------------------
  static void IfDebugCompleted(CATCGMObject *body,  const char IdentityBuildOperator[] = "");

  static void IfDebugCompletedAttribute(CATCGMAttribute       * iAttribute,
                                        CATCGMObject          * iHolder,
                                        CATCX_CheckUpAttribute  iCallBack,
                                        const char IdentityBuildOperator[] = "");    

  static  int Checkup(CATCGMObject *body);

  //int CheckupExplicit(CATLISTP(CATCGMObject) &iListOfCGMObjectToCheck);
  //int CheckupExplicit(CATLISTP(CATCGMObject) &iListOfCGMObjectToCheck, CATCGMHashTableWithAssoc *pioHashTableCGMObjectWithLinkedObjects = NULL);
  int CheckupExplicit(CATLISTP(CATCGMObject) &iListOfCGMObjectToCheck, CATCGMHashTable *pioHashTableOfLinkedObjects = NULL);
  

  void SetExplicitCheckLvl(short iExplicitCheckLvl);
  CATBoolean IsExplicitCheckEnabled();

  CATLISTP(CATCXReport)   *GetListOfCATCXReport();

  //---------------------------------------------------------------------------
  // Accessing value & Modification of default value of CATCX_CHECKUP=integer
  //---------------------------------------------------------------------------
  static  int GetDebugStatus();
  static void SetDebugStatus(const int level=0);

  static CATULONG32 DumpCGMRuleStats(ostream* ipOutput);
  static CATULONG32 ResetCGMRuleStats();


  // dummy identifier for a CATCX_CHECKUP object
  #define CATCX_CHECKUP_DummyCheckUpId -1
  // unique identifier of a CATCX_CHECKUP object
  // different from CATCX_CHECKUP_DummyCheckUpId

  int GetCheckUpId() ;

  static void None();

  /*
  @nodoc
  */
  static CATCX_SetOfAnomalyManager *GetSetOfAnomalyManager();
  /*
  @nodoc
  */
  static void Init_CATCX_SetOfAnomalyManager(CATCGMContainer *piFactory, CATBoolean IsCompletedCheck = FALSE);
	/*
  @nodoc
  */
  static void DisableCompleted(CATBoolean iOption);
  /*
  @nodoc
  */
  static CATBoolean IsCompletedDisabled();
  /*
  @nodoc
  */
  CATBoolean IsPotDeVinRelevant(const char *piPotDeVin_PrefixID,const char *piPotDeVin_SuffixID,
								CATCGMObject *piMasterObj, CATCGMObject* const* piTabOfCGMObj, 
								const int iSizeTab);

  /*
  @nodoc
  */
  void InitCheckUp(CATCGMObject    *Who, const KindOfReport how);

  /*
  @nodoc
  */
  static CATBoolean Is_CGM_Context();

  /*
  @nodoc
  */
  static CATSoftwareConfiguration *InitStaticSoftConfig();

   /*
  @nodoc
  */
  static CATSoftwareConfiguration *GetStaticSoftConfig();

  /*
  @nodoc
  */
  static void                      ReleaseStaticSoftConfig();

  /*
  @nodoc (Tmp Location)
  */
  static double GetCATTopTolerantSharpAngle();

  /*
  HVO220210927, Added method to reset _forbiddenPotDeVinIsKnown to get Authorized file presence behavior in multiple checks (MakeTransfer -> CheckOutput CATM2V5Engine)
  */
  static void ReInitForbiddenPotDeVinIsKnown();

private:

    static void IfDebugCompletedAfter(CATCGMObject *body,  const char IdentityBuildOperator[], 
                                     CATCX_CHECKUP::KindOfReport how,
                                     int nbOffenseWarning);


  //static CATULONG32 __NbDetectAllRulesCalls;
  //static CATULONG32 __NbBRepLinkCalls;
  static CATULONG32 __NbSpecificCheckCalls;
  static CATULONG32 __NbBodyCompletedCalls;
  static CATULONG32 __NbPerformedChecks;
  //static CATULONG32 __NbPerformedCleans;
  static CATBoolean __BodyCompletedCall;
  short _ExplicitCheckLvl;             // 0 : not in Explicit Check mode , >=1 : in Explicit Check mode,  1 : PotDevin = Error, 2 : PotDeVin = Warning

  CATCGMObject            *_who;    
  KindOfReport             _inspect;
  CATLISTP(CATCXReport)   *_checkup;
  int                      _nbPotVin;
  CATBoolean               _ForCompleted;
  CATBoolean               _CheckUpHashTableOfLinkedObject; 

  CATUnicodeString         _OperatorId;  // the name of the operator

  static int               _debugStatus;

  CATBoolean               _KeepFirstInitForNotCumul;

  CATListOfInt             _CleanerRulesToSkip;

  static CATCX_SetOfAnomalyManager  _SetOfAnomalyManager; // Pour gestion des PotDeVin petinent : Stockage des PotsDeVin 
																											// puis filtrage pour ne garder que ceux généré par l'opérateur
	static CATBoolean  __DisableCompleted; // pour désactivation du CheckUp lors des Completed.
																				 //	Utilisé dans la gestion des PotsDeVins des Bodies intermédiaire d'un Opérateur Topologique
 
   static CATCX_CHECKUP *__StaticCheckUpForCompleted;

   static CATSoftwareConfiguration  *_pSoftConfig;
  //-----------------------------------------------------------------------
  // Show internal method for ODT Coverage 
  //-----------------------------------------------------------------------
  static void log_INDEX(CATLISTP(CATCXReport) *checkup);  
  
  void Simplify();

  void UpdateCheckBehaviourCurrentError(CATCGMObject  *topo,
                                        const char rule[], 
                                        const char offense[],
                                        const int nbother,
                                        CATUnicodeString *const others,
                                        const CATGeoClnIDs::RuleID CGMRuleID);

  //void InitCheckUp(CATCGMObject    *Who, const KindOfReport how);

  

  static int  ODTCheckUpLog;
  static int  _GetDebugStatus;
  
  static void _init_CATCX_CHECKUP();

  friend class CATCGMObject;
  friend class oper_NewTopo;

  int _CheckUpId ;

  static CATBoolean _forbiddenPotDeVinIsKnown;

};

/*
//-------------------------------------------------------------------
// For check made from UserExit.  set/export CATCX_CHECKUP=5 
// function CATBodyCheck on shared-lib CATBodyCheck will be executed
//-------------------------------------------------------------------
#ifndef CheckNameOfsharedLibrary
#define CheckNameOfsharedLibrary "CATBodyCheck"
#define CheckNameOfFunction      "SoftCheck"
extern "C"  {
 typedef int CATBodyCheck(CATBaseUnknown *object, CATCX_CHECKUP *report);
} 
#endif
*/

//-------------------------------------------------------------------
// For cleaner integration at body completion
// function CATCGMCleanerExportedMethod on shared-lib CATCGMCleaner will be executed
//-------------------------------------------------------------------
extern "C"  {
 typedef int CATCGMCleanerCheckMethodType(CATICGMUnknown*              ipSpecificToCheck,
                                          CATListOfInt*                ipSpecificRuleIDs,
                                          CATCGMCheckClean::CallMethod iCallMethod,
                                          CATCX_CHECKUP*               iopCATCX_Report,
                                          CATCGMCheckBehavior*         ipCheckBehavior,
                                          CATLISTP(CATICGMObject)*     ipPreCalculatedAllLinks);

 typedef int CATCGMCleanerRuleMethodType(CATGeoClnIDs::RuleID ipSpecificRuleID, CATGeoClnCheckParameter* ipRuleCheckParameter);
} 

//-------------------------------------------------------------------
// Pour faciliter les implementations du Checkup
//-------------------------------------------------------------------
#ifndef SetWithoutThrow_macro
#define SetWithoutThrow_macro
#include "CATErrorMacros.h"

#define SetWithoutThrow( variable, retrieve ) \
CATTry   { variable = retrieve ; }                           \
CATCatch(CATError,error) { Flush(error); variable = NULL; }  \
CATCatchOthers           { variable = NULL; }  \
CATEndTry ; 

#endif

#endif // CATCX_CHECKUP_H

