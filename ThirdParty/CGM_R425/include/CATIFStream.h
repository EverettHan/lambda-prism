//*===========================================================================*
//* COPYRIGHT DASSAULT SYSTEMES 1996                                          *
//*===========================================================================*
//*                                                                           *
//*  CATFile                                                                  *
//*                                                                           *
//*  Usage Notes:                                                             *
//*===========================================================================*
//*  Creation mars 1997                                                       *
//*===========================================================================*
#ifndef __CATIFSTREAM
#define __CATIFSTREAM

#include "CATWTypes.h"
#include "IUnknown.h"

extern  IID IID_CATIFStream;


class  CATISeqStream : public IUnknown
{
public:
  virtual HRESULT __stdcall Read( void FAR *iBuff,
				  ULONG iLengthToRead,
				  ULONG FAR* oLengthRead) = 0;
        
  virtual HRESULT __stdcall Write( const void FAR *iDataSource,
				   ULONG iLengthToWrite,
				   ULONG FAR* oLengthWritten) = 0;
        
};



class  CATIFStream : public CATISeqStream
{
public:
  virtual HRESULT __stdcall Seek( LARGE_INTEGER dlibMove,
			DWORD dwOrigin,
			ULARGE_INTEGER FAR* plibNewPosition) = 0;
        
  virtual HRESULT __stdcall SetSize( ULARGE_INTEGER libNewSize) = 0;
        
  virtual HRESULT __stdcall CopyTo( CATIFStream FAR* iStream,
				    ULARGE_INTEGER cb,
				    ULARGE_INTEGER FAR* pcbRead,
				    ULARGE_INTEGER FAR* pcbWritten) = 0;
        
  virtual HRESULT __stdcall Commit( DWORD iCommitFlags) = 0;
        
  virtual HRESULT __stdcall Revert( void) = 0;
        
  virtual HRESULT __stdcall LockRegion( ULARGE_INTEGER libOffset,
					ULARGE_INTEGER cb,
					DWORD dwLockType) = 0;
        
  virtual HRESULT __stdcall UnlockRegion( ULARGE_INTEGER libOffset,
					  ULARGE_INTEGER cb,
					  DWORD dwLockType) = 0;
        
  virtual HRESULT __stdcall Stat( STATSTG FAR* oStatstg,
				  DWORD iStatFlag) = 0;
        
  virtual HRESULT __stdcall Clone( CATIFStream FAR*FAR* oClone) = 0;
        
};
 
#endif
