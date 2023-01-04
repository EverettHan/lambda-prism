#ifndef CATOGMCoreDataByCopy_H
#define CATOGMCoreDataByCopy_H
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
#include "CATOGMCoreData.h"

//------------ ----------- ---------- 
//  CATOGMCoreDataByCopy
//------------ ----------- ---------- 
class ExportedByCATOGMCore CATOGMCoreDataByCopy : public  CATOGMCoreData
{
public :

  /** CompareValue */
  virtual int  CompareValue(CATOGMCoreData* ipCoreData);

  /** GetValue */
  virtual void  GetValue(size_t & oSize, unsigned char * & opData);

  /** CompareValue */
  CATOGMCoreDataByCopy(const size_t iSize, unsigned char * pData);

  ~CATOGMCoreDataByCopy();

private :  

  size_t           _Size;
  unsigned char *  _Data;
};



#endif
