#ifndef CATGMayday_h
#define CATGMayday_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */
//-------------------------------------------------------------------------------------------------
//   Event (and optionnally Data) GM's Collector 
//-------------------------------------------------------------------------------------------------
#include "CATechSetup.h"
 

/** 
*  Utility for collecting GM events and data during an unspecified interval of times
*/

class  ExportedByCATTechTools CATGMayday : public CATechSetup 
{ 
public :

 
  /** 
  * BeforePublishOperator  
  *
  * Create Current and Publish 
  * 
  */ 
  static CATechAttribute * BeforePublishOperator(CATechSetup_Domain iDomain, const CATUnicodeString  & iSchemaName);



  /** 
  *   PublishOperator  
  *
  * @param i0Before_1After.
  *
  * @param ioEvent.
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  static HRESULT  PublishOperator(CATechAttribute  *   ioEvent,
                                  int                   i_0Begin_1EndOkay_2EndKO,
                                  CATULONG64            iToolsTicks = 0);
   
 
  
};

 
 
#endif
