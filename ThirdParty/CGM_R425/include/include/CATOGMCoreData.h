#ifndef CATOGMCoreData_H
#define CATOGMCoreData_H
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2009
/**
 * @level Private
 * @usage U1
 */

//-------------------------------------------------------------------------------------------------
// Be Carefull about limited scope of this interface
//   high performance computation could not rely on central main memory management 
//
// Short term local transaction (change set acquisition)   
//    for extended N1 Operators on statefull modelisation
// Not to used by applied integration 
//    Dedicated to core kernel GM Component based modeler
//
// Cf  Oxxx Geomerical Modeler 
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Core Persistent Structure  
//----------------------------------------------------------------------------------------------
#include "CATOGMCore.h"
#include "stddef.h"

//------------ ----------- ---------- 
//  CATOGMCoreData
//------------ ----------- ---------- 
class ExportedByCATOGMCore CATOGMCoreData 
{
public :

  virtual ~CATOGMCoreData();

  /** CompareValue 
    * 0:equal 1:distinct */
  virtual int  CompareValue(CATOGMCoreData* ipCoreData) = 0;

  /** GetValue */
  virtual void  GetValue(size_t & oSize, unsigned char * & opData) = 0;

protected :
  INLINE CATOGMCoreData();
};


INLINE  CATOGMCoreData::CATOGMCoreData() {}
 

#endif
