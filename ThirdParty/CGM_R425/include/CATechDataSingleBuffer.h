#ifndef CATechDataSingleBuffer_H
#define CATechDataSingleBuffer_H
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
 
/**
* Class to define either serialised data either loaded objects.
*/

class ExportedByCATTechTools CATechDataSingleBuffer : public CATechData
{
public :

  /**
  * @nodoc 
  *    IsSingleBuffer : ...
  */
  virtual CATechDataSingleBuffer *  IsSingleBuffer();

  /**
  * @nodoc 
  * GetOriginalAreas : ...
  */
  virtual HRESULT GetOriginalAreas(size_t       & oGlobalLengthInBytes,
                                   CATULONG32       & oNumberOfArea,
                                   size_t     * * oAreaLengthInBytes = NULL,
                                   void         * * * oAreaAddress = NULL) = 0;

  /**
  * @nodoc 
  * GetOriginalAreas : ...
  */
  virtual void *  GetAsContiguousArea(size_t    & oGlobalLengthInBytes) = 0;

  /**
  * @nodoc 
  * FreeAreas :  .
  */
  virtual HRESULT FreeAreas() = 0;

protected :

  /**
  * @nodoc 
  *   destructor : ...
  */
  virtual ~CATechDataSingleBuffer();

   /**
  * @nodoc 
  *    Synchronous management : ...
  */
  virtual void        EmptyBuffer() ;


  CATechDataSingleBuffer(CATULONG32 iIdSession, CATechSet  * iSet, CATechAttribute  * iAttribute, const CATUnicodeString & iDataType);

private :

  CATechDataSingleBuffer(const CATechDataSingleBuffer &iCopy);
  CATechDataSingleBuffer& operator=(const CATechDataSingleBuffer &iCopy);
 
};

#endif
