#ifndef CATechDataCATPhoenix_H
#define CATechDataCATPhoenix_H
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2008
/** @CAA2Required */
/**
* @level Private
* @usage U1
*    GMTk journaling idea is to collect an history of operations
*        in one zip auto-described file with data meaningfull for a GM support.
*    It enables some preliminary analysis of a scenario focusing on GM domain.
*     (forcasting availability inside CGMOFF/CGMPRJ workspace is about collect of end week 42 of year 2010)
* 
*    Objective is to ease some debug/support with application based upon GMTk.
*        by mean of an auto-described zip files containing a all-in-one list of GM operations or data.
*     Remarks 1) not all GM operations may have implemented GMTkJournaling mecanisms (with underlining CGMReplay file).
*     Remarks 2) GMTkJournaling is also gathering information about scenarios
*                   (some statistics on I/O operations, or intermediate operation data (CATCX_NCGM))
* 
*   About some known limitations : structure of zip may changed at any software iteration.
*       -each type of file has its own data compatibility management (NCGM,CGMReplay)
*       -CSV file has no defined compatibility management 
*/
//------------------------------------------------------------ 
// area(s) of data
//------------------------------------------------------------ 
#include "CATechData.h"

#include "CATechSet.h"
#include "CATechAttribute.h"
#include "CATechExt.h"
  

/**
* Class to define either serialised data either loaded objects.
*/

class ExportedByCATTechTools CATechDataCATPhoenix : public CATechData
{
public :

  /**
  * GetDataType  
  */
  virtual HRESULT GetDataType(CATUnicodeString & oDataType) const ;


  /**
  * @nodoc 
  *    IsSingleBuffer : ...
  */
  virtual CATechDataSingleBuffer *  IsSingleBuffer()  ;
 


  /**
  * @nodoc 
  *   constructor : ...
  */ 
  CATechDataCATPhoenix(CATULONG32 iIdSession, CATechSet  * iSet, CATechAttribute  * iAttribute);



protected :
  /**
  * @nodoc 
  *   destructor : ...
  */
  virtual ~CATechDataCATPhoenix();


private :

  CATechDataCATPhoenix(const CATechDataCATPhoenix &iCopy);
  CATechDataCATPhoenix& operator=(const CATechDataCATPhoenix &iCopy);


};

#endif
