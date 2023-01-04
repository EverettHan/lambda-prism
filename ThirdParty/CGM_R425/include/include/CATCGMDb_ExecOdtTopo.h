#ifndef CATCGMDb_ExecOdtTopo_h
#define CATCGMDb_ExecOdtTopo_h
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

   TopologicalOperators.tst\ExecOdtTopo.m\src\main.cpp

  TopologicalOperators.tst\ExecOdtTopo.m\LocalInterfaces\CATOdtOperator.h 

    TopologicalOperators.tst\ExecOdtTopo.m\src\CATOdtOperator.cpp 
      CATOdtOperator::Compute()=0;


      GetDiag()  ->   
         static const CATechMeta & CATCGMDb_ExecOdtTopo::Global_RC();  


 *  
*/

  

class  ExportedByCATTechTools  CATCGMDb_ExecOdtTopo  : public CATCGMDb_Common  
{ 
public :
 
   
  //=======================================================================
  //  TopologicalOperators.tst\ExecOdtTopo.m\LocalInterfaces\CATOdtAutomaton.h
  //=======================================================================
 
   static const CATechMeta & CHECK();   
   static const CATechMeta & CHECK_MODEL();   
   static const CATechMeta & FIND();   
   static const CATechMeta & SET();   

   static const CATechMeta & ResultExpected();   
 
   static const CATechMeta & CHECK_DIAG();   
   static const CATechMeta & CHECK_DEGEN_VERTEX();   
   static const CATechMeta & SEVERITY();   


  
  static void GenerateReport(CATBoolean iAppendHEAD,  CATechSetOfChar & ioFeedBack,
                             const CATUnicodeString & PrefixMutualReporting,  const CATUnicodeString & MutualReporting,  
                             CATechAttribute        * iFeedbackSteps,
                             const CATUnicodeString & CommonPrefixHead,   const CATUnicodeString & CommonPrefixValue, 
                             const CATUnicodeString & CommonHead,         const CATUnicodeString & CommonValue );

};

#endif
