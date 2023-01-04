//*===========================================================================*
//* COPYRIGHT DASSAULT SYSTEMES 2003                                          *
//*===========================================================================*
//*                                                                           *
//*                                                                           *
//*  Usage Notes:                                                             *
//*===========================================================================*
//*  Creation novembre 2003                                                   *
//*===========================================================================*
#ifndef __DSYSYSMULTIBUFFER
#define __DSYSYSMULTIBUFFER

#include "CATWTypes.h"
#include "JS0BASEILB.h"




class ExportedByJS0BASEILB DSYSysMultiBuffer
{ 
  
public :
   
   virtual ULONG AddRef() = 0;
   virtual ULONG Release() = 0;
    
   virtual HRESULT Realloc(ULARGE_INTEGER iLength) = 0;
   virtual HRESULT CopyTo( ULARGE_INTEGER iOffset, const void *iSource, size_t iLength,  size_t *oWriten) = 0;
 
   virtual HRESULT CopyFrom( ULARGE_INTEGER iOffset, void *oDest, 
		    size_t iLength, size_t *oRead) = 0;
   virtual HRESULT GetSize ( size_t *oSize) = 0;
  
   virtual HRESULT GetBuffersInfo( unsigned int *oNb, size_t *oSize) = 0;
   // Never delete the oBuff pointer !!It is a direct access onto the Buffer
   virtual HRESULT GetBuffer ( unsigned int iIndice, char **oBuff) = 0;
  
  virtual HRESULT FlushBuffer (int iMax=0){return E_FAIL;};
  
  virtual  void setLock(int iVal) = 0;
  virtual  int getLock() = 0;
  
   virtual HRESULT CopyToInt( ULARGE_INTEGER iOffset, const void *iSource, size_t iLength,  size_t *oWriten) = 0;
   virtual HRESULT ReallocInt(ULARGE_INTEGER iLength) = 0;
	
  
};

#endif
