#ifndef CATechDataCATMathStream_H
#define CATechDataCATMathStream_H
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
#include "CATechDataMemory.h"

/**
* Class to define an area.
*/

class CATMathStream;

class ExportedByCATTechTools CATechDataCATMathStream : public CATechDataMemory
{
public :

  CATechDataCATMathStream(CATULONG32 iIdSession, CATechSet  * iSet, CATechAttribute  * iAttribute, const CATUnicodeString & iDataType, CATMathStream *iStream);
  virtual ~CATechDataCATMathStream();
 

  virtual HRESULT GetOriginalAreas(size_t        & oGlobalLengthInBytes,
                                   CATULONG32    & oNumberOfArea,
                                   size_t     *  * oAreaLengthInBytes = NULL,
                                   void  *    *  * oAreaAddress = NULL) ;

  virtual void *  GetAsContiguousArea(size_t     &oGlobalLengthInBytes) ;

  virtual HRESULT FreeAreas() ;

protected :

  
   /**
  * @nodoc 
  *    Synchronous management : ...
  */
  virtual void        EmptyBuffer() ;



private :


  CATechDataCATMathStream(const CATechDataCATMathStream &iCopy);
  CATechDataCATMathStream& operator=(const CATechDataCATMathStream &iCopy);

  CATMathStream  * _stream;
};

#endif
