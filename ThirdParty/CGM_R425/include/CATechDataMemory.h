#ifndef CATechDataMemory_H
#define CATechDataMemory_H
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2008
/**
 * @level Private
 * @usage U1
 */
//------------------------------------------------------------ 
// Small attribute for genuine Extract/Redo infrastructure
//------------------------------------------------------------ 
#include "ExportedByCATTechTools.h"

#include "CATDataType.h"
#include "CATechDataSingleBuffer.h"

/**
* Class to define an area.
*/

class CATMathStream;

class ExportedByCATTechTools CATechDataMemory : public CATechDataSingleBuffer
{
public :

  CATechDataMemory(CATULONG32 iIdSession, CATechSet  * iSet, CATechAttribute  * iAttribute, const CATUnicodeString & iDataType, size_t   GlobalLengthInBytes, unsigned char  * iBuffer );
  virtual ~CATechDataMemory();
 
  virtual HRESULT GetDataType(CATUnicodeString & oDataType) const   ;

  virtual HRESULT GetOriginalAreas(size_t        & oGlobalLengthInBytes,
                                   CATULONG32    & oNumberOfArea,
                                   size_t     *  * oAreaLengthInBytes = NULL,
                                   void  *    *  * oAreaAddress = NULL) ;

  virtual void *  GetAsContiguousArea(size_t     &oGlobalLengthInBytes) ;

  virtual HRESULT FreeAreas() ;

protected :
  size_t           _BlockBufferSize ;
  unsigned char  * _BlockBuffer ;

   /**
  * @nodoc 
  *    Synchronous management : ...
  */
  virtual void        EmptyBuffer() ;


private :

  CATechDataMemory(const CATechDataMemory &iCopy);
  CATechDataMemory& operator=(const CATechDataMemory &iCopy);

  CATUnicodeString _DataType;
};

#endif
