/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 */
/* -*-c++-*- */
#ifndef CATCGMCleanerBridge_H_
#define CATCGMCleanerBridge_H_
//=============================================================================
// Data for managing CGM cleaner activation and calls
//=============================================================================
#include "ExportedByGeometricObjects.h"
#include "CATMathInline.h"
#include "CATGeoFactory.h"

#include "CATCGMCleanerActivation.h"
#include "CATCGMCleaner.h"


class ExportedByGeometricObjects CATCGMCleanerBridge
{
public :

  INLINE static  CATCGMCleanerBridge*  GetCleaner();

  //---------------------------------------------------------------------------------------------------------------------
  //  -> DeleteStaticCGMRuleDefsAndCGMRules  
  //  -> GetEnvFailureMode  
  //  -> SetFailureMode  
  //  -> GetFailureMode
  //---------------------------------------------------------------------------------------------------------------------

	virtual                      void   DeleteStaticCGMRuleDefsAndCGMRules() = 0;

	virtual  CATCGMCleaner::FailureMode   GetEnvFailureMode() = 0;

  virtual                        void   SetFailureMode(CATCGMCleaner::FailureMode iMode) = 0;

  virtual CATCGMCleaner::FailureMode    GetFailureMode() = 0;
 
  virtual void ActivateCATGemEvtGenericNamedRules() = 0;

  //---------------------------------------------------------------------------
  // Mise a jour des CATCGMRuleDef::_pStaticTableChkCGMEntsKO
  //          et des CATCGMRuleDef::_pStaticTableChkCGMEntsKOWitns
  //---------------------------------------------------------------------------
  virtual void       DeleteStaticTablesOfChkCGMEnts(CATGeoFactory* ipGeoFactory = NULL) = 0;

  virtual void       SetShowErrorDialogs(CATBoolean iMode = TRUE) = 0;

  virtual CATBoolean IsShowErrorDialogs() = 0;

  virtual CATBoolean IsActive() = 0;


  //---------------------------------------------------------------------------
  // ...
  //---------------------------------------------------------------------------
  virtual void ActivateApplyCreatedCGMRulesTraces(CATBoolean iForce = TRUE)= 0;

	virtual CATCGMRuleDefHashTable* CreateStaticTabOfAllCGMRuleDefs(CATBoolean iOnCompletedRules)= 0;

  virtual CATULONG32 Dec_NB_AtCompletedAndActive_Rules()= 0;

  virtual void DecodeCodeLevel(int iCodeLevel, char* ioBuffer)= 0;

   virtual int DetectUserActivatedRulesForPerfo(CATCGMCleanerImpl*               ipThisCleaner,
                                              CATSoftwareConfiguration*    ipSoftConf,
                                              CATICGMUnknown*              ipSpecificToCheck,
                                              CATListOfInt*                ipSpecificRuleIDs,
                                              CATCX_CHECKUP*               iopCATCX_Report,
                                              CATCGMCheckBehavior*         ipCheckBehavior,
                                              CATCGMCheckClean::CallMethod iCallMethod,
                                              CATLISTP(CATICGMObject)*     ipPreCalculatedAllLinks)= 0;

  virtual CATULONG32 DumpCGMRuleStats(ostream* ipOutput)= 0;

	virtual void FillExtendedCheckErrorMsg(CATCheckRule* ipCheckRule, CATListValCATUnicodeString* iopListExtendedErrorMsg)= 0;

	virtual void FillExtendedCleanErrorMsg(CATCheckRule* ipCheckRule, CATListValCATUnicodeString* iopListExtendedErrorMsg)= 0;

  virtual void ForceActivateAllCGMRules(CATBoolean iForce = TRUE)= 0;

  virtual CATULONG32  GetBreakpointTag()= 0;
  
	virtual void GetCleanMessages(CATCheckRule* ipCheckRule, CATUnicodeString& ioMessage, CATUnicodeString& ioShortMessage)= 0;

  virtual void GetEnvRules(CATListOfCATUnicodeString* iopListEnvRules = NULL, CATListOfCATUnicodeString* iopListEnvOFFRules = NULL,
                          CATListOfCATUnicodeString* iopListODTRules = NULL)= 0;

	virtual CATCGMRuleDef* Get_ORIGINAL_CGM_RULE_DEF_FromNumInTab(const int iRuleNum)= 0;

	virtual CATULONG32 Inc_NB_AtCompletedAndActive_Rules()= 0;

  virtual CATBoolean IsBreakpoint()= 0;

  virtual CATBoolean IsDumpCallStack()= 0;

  virtual CATBoolean IsShowTraces(CATCGMCheckRule* ipCGMCheckRule = NULL)= 0;

  virtual void SetActive(CATBoolean iMode = TRUE)= 0;

  virtual void SetBreakpoint(CATBoolean iMode)= 0;

  virtual void SetBreakpointTag(CATULONG32  iTag = 0)= 0;

  virtual void SetDumpCallStack(CATBoolean iMode = TRUE)= 0;

	virtual void SetShowTraces(CATBoolean iMode = TRUE)= 0;

 	virtual void SetVerbose(CATBoolean iVerbose )= 0;
 


protected  :
  //------------------------------------------------------------------------
  // LifeCycle
  //------------------------------------------------------------------------
  CATCGMCleanerBridge();
  ~CATCGMCleanerBridge();


private :
  static  CATCGMCleanerBridge*  Init();

  static CATCGMCleanerBridge*    _result ;
  static CATBoolean              _initialized ;

  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATCGMCleanerBridge(const CATCGMCleanerBridge &iCopy);
  CATCGMCleanerBridge& operator=(const CATCGMCleanerBridge &iCopy);
 
};

 
INLINE CATCGMCleanerBridge*  CATCGMCleanerBridge::GetCleaner()
{ return  ! _initialized ?  CATCGMCleanerBridge::Init() : _result; }



/**
* @nodoc
*/
extern "C" { typedef CATCGMCleanerBridge* CATCGMCleanerBridge_Creator(); }  


#endif
