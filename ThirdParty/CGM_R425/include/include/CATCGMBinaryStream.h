/* -*-c++-*- */
#ifndef CATCGMBinaryStream_h
#define CATCGMBinaryStream_h

//------------------------------------------------------------------------------------------
// This interface contains the same methods than CATIOmxBinaryStream
// To avoid the problem of pre-requis (Mathematics -> ObjectModelerCollection)
//
// Creation Sept 2014     YL3
//------------------------------------------------------------------------------------------

#include "ExportedByCATMathStream.h"
#include "CATBaseUnknown.h"
#include "CATDataType.h"

/** Seek from beginning of the archive.*/
#define CGM_SEEK_BEG 1
/** Seek from end of the archive.*/
#define CGM_SEEK_END 2
/** Seek from current position of the archive.*/
#define CGM_SEEK_CUR 4

class ExportedByCATMathStream CATCGMBinaryStream : public CATBaseUnknown
{
public:
  virtual HRESULT Seek(int iStart,CATLONG64 iOffset)=0;
  
  virtual HRESULT Write(CATLONG64 iByteCount,const void* iData)=0;

  virtual HRESULT Read(CATLONG64 iByteCount,void* oData,CATLONG64& oByteCount)=0;

  virtual HRESULT GetCurrentPosition(CATLONG64& oPosition)=0;

  virtual HRESULT Flush()=0;
};


#endif
