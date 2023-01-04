#ifndef CATCGMDb_CGMReplayExtended_h
#define CATCGMDb_CGMReplayExtended_h
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
#include "CATCGMDb_Common.h"


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
*/

  

class  ExportedByCATTechTools  CATCGMDb_CGMReplayExtended : public CATCGMDb_Common 
{ 
public :
 
  static const CATechMeta & CheckOutput_LiveBody();   
  static const CATechMeta & CheckOutput_CellTrackerData();   
 
  static const CATechMeta & Run_CPUTime();   
  static const CATechMeta & Run_ElapsedTime();   

  static const CATechMeta & ValidateOutput_CheckFastUpdate();   
  static const CATechMeta & ValidateOutput_CheckVoB();   
  static const CATechMeta & ValidateOutput_CellTrackerData();   
 

  static void GenerateReport(CATBoolean iAppendHEAD, CATechSetOfChar & ioFeedBack, CATechSetOfChar & ioFeedBackExtended, 
                             const CATUnicodeString & PrefixMutualReporting,  const CATUnicodeString & MutualReporting,  
                             CATechAttribute        * iFeedbackSteps,
                             const CATUnicodeString & CommonPrefixHead,   const CATUnicodeString & CommonPrefixValue, 
                             const CATUnicodeString & CommonHead,         const CATUnicodeString & CommonValue );

private :

  static void CoverageExtended();

};


#endif
