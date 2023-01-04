#ifndef CATCGMDb_Common_h
#define CATCGMDb_Common_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/** @CAA2Required */
/**
* @level Private
* @usage U1
**/
//-------------------------------------------------------------------------------------------------
// Utility for collecting various asynchronous steps :
//-------------------------------------------------------------------------------------------------
#include "ExportedByCATTechTools.h"
#include "CATechMeta.h"
#include "CATechAttribute.h"
#include "CATechSet.h"
#include "CATBoolean.h"
#include "CATCGMManageMemory.h"
#include "CATechSetOfChar.h"
 
/** 
*  Utility for collecting various asynchronous steps :
*
* Default Integer Values
*
*      -1 :  step not done  
*       0 : ending Step  Okay
*      +1 : ending Step with anomalies  
*      +2 : ending Step with warning
*
* For Global_RC
*
*       0 : OK
*      +1 : KO
*      +2 : Evolution
*      +3 : Regression
*
* NumberOfSteps
*
*       1 : Input
*       2 : Input + Referential
*       N : MultipleRun
*
*
*  
*/

  
 

ExportedByCATTechTools void CATCGMMemoryGarbageTechTools(CATCGMEventGarbage iEvent);

class  ExportedByCATTechTools CATCGMDb_Common
{ 
public :
 

  //-------------------------------- 
  //  Reporting management
  //-------------------------------- 
 
  static CATBoolean   WithFeedReporting() ;

  static void         FeedReporting(CATechAttribute * iFeedbackSteps)  ;

  static void         FlushReporting() ;

  //=======================================================================
  //   CGMTestToolkit.tst\PrivateInterfaces\CGMReplayEngine.h
  //=======================================================================
  static const CATechMeta & LoadCGMReplay();   
  static const CATechMeta & Protocol();   

  //-------------------------------- 
  //  HEADER (META-DESCRIPTION)
  //-------------------------------- 

  static const CATechMeta & ODTName();   
  static const CATechMeta & ScenarioName();   
  static const CATechMeta & SoftLevel();   
  static const CATechMeta & NumberOfSteps();   

  static const CATechMeta & FwName();   
  static const CATechMeta & OperatorId();   
  static const CATechMeta & OperatorIdName();   // Back-Up Tools (non operator Id)
  static const CATechMeta & FileName();   

  static const CATechMeta & Global_RC();  


  //-------------------------------- 
  //  FEEDBACK  GLOBAUX
  //-------------------------------- 

  static const CATechMeta & CheckInput_Global();  
  static const CATechMeta & RunOkay();   
  static const CATechMeta & CheckOutput_Global();   
  static const CATechMeta & ValidateOutput_Global();  

  //-------------------------------- 
  //  PCS Full transaction (cf CATCGATimer) Run and Check .... (and recording included)  
  //-------------------------------- 

  static const CATechMeta & Full_msCPU();  
  static const CATechMeta & Full_msELAPSED();   
  static const CATechMeta & Full_TICKS();   


  //-------------------------------- 
  //  FEEDBACK LOCAUX 
  //-------------------------------- 

  static const CATechMeta & CheckInput_Factory();   
 
  static const CATechMeta & CheckOutput_Journal();   
  static const CATechMeta & CheckOutput_Factory();   
  static const CATechMeta & CheckOutput_BodyResult();   
  static const CATechMeta & CheckOutput_Extension();   
  static const CATechMeta & CheckOutput_Persistency();   

  static const CATechMeta & ValidateOutput_BodiesMapping();   
  static const CATechMeta & ValidateOutput_JournalMapping();   
  static const CATechMeta & ValidateOutput_RecyclingRate();   

  static const CATechMeta & ValidateOutput_ValidateTopOutput();   
  static const CATechMeta & ValidateOutput_ValidateOutput();   
  static const CATechMeta & ValidateOutput_ErrorReferential();   

  //-------------------------------- 
  //  TheProtocols
  //-------------------------------- 
  static const CATUnicodeString TheProtocolODTCore;
  static const CATUnicodeString TheProtocolCATCGMReplay;
  static const CATUnicodeString TheProtocolODTOperator;
  static const CATUnicodeString TheProtocolExecOdtTopo;

  enum ProtocolId{ ODTCore = +0, CATCGMReplay = +1, ODTOperator = +2 , ExecOdtTopo = +3 };

 
  static void GetCommon( CATechAttribute * iFeedbackSteps,
                         CATUnicodeString & oCommonPrefixHead,   CATUnicodeString & oCommonPrefixValue, 
                         CATUnicodeString & oCommonHead,   CATUnicodeString & oCommonValue );


  static void GenerateReport(CATBoolean iAppendHEAD, CATechSetOfChar & ioFeedBack,
                             const CATUnicodeString & PrefixMutualReporting,  const CATUnicodeString & MutualReporting,  
                             CATechAttribute        * iFeedbackSteps,
                             const CATUnicodeString & CommonPrefixHead,   const CATUnicodeString & CommonPrefixValue, 
                             const CATUnicodeString & CommonHead,         const CATUnicodeString & CommonValue );
  

  //-------------------------------- 
  //  Various 
  //-------------------------------- 

  static CATUnicodeString _PrefixMutualReporting;
  static CATUnicodeString _ReadMe;
  static CATBoolean       _CheckReadMe ;
  static CATBoolean       _TheReporting  ;
  static CATBoolean       _TheReportingInitialised  ;

  //-------------------------------- 
  //  Various 
  //-------------------------------- 

  static void InitReporting(); 

  //-------------------------------- 
  //  TheProtocols
  //-------------------------------- 

private :

  static CATechSet * _ODTCore;
  static CATechSet * _CATCGMReplay;
  static CATechSet * _ODTOperator;
  static CATechSet * _ExecOdtTopo;

  friend ExportedByCATTechTools void CATCGMMemoryGarbageTechTools(CATCGMEventGarbage iEvent);

};







#endif
