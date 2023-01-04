//*===========================================================================*
//* COPYRIGHT DASSAULT SYSTEMES 1996                                          *
//*===========================================================================*
//*                                                                           *
//*  CATIStorage                                                              *
//*                                                                           *
//*  Usage Notes:                                                             *
//*===========================================================================*
//*  Creation mars 1997                                                       *
//*===========================================================================*
#ifndef __CATSTGAPI
#define __CATSTGAPI

#include "JS0COMP.h"
#include "JS0BASEILB.h"
#include "CATWTypes.h"
#include "CATIStorage.h"
#include "CATIFStream.h"
#include "CATILockBytes.h"
#include "CATILockBytes2.h"
#include "DSYSysMultiBuffer.h"
#include "DSYSysZipFile.h"

class CATSysDRMILB;
class CATUnicodeString;
class CATStream;
class l_CATSysMultiBuffer;
class CATSysMultiBuffer;

#define DSY_SEQUENTIAL_MEDIA 0x00000001
#define DSY_RANDOM_MEDIA     0x00000002

//****** Storage API Prototypes *********************************************
HRESULT ExportedByJS0COMP CATOpenStorage( const CATUnicodeString & iszName,
					  CATIStorage FAR* pstgPriority,
					  DWORD Mode, SNB snbExclude, 
					  DWORD reserved,
					  CATIStorage FAR * FAR * ppstgOpen);
HRESULT ExportedByJS0COMP CATOpenStorage( const CATUC2Bytes FAR* pwcsName,
					  CATIStorage FAR* pstgPriority,
					  DWORD Mode, SNB snbExclude, 
					  DWORD reserved,
					  CATIStorage FAR * FAR * ppstgOpen);

HRESULT ExportedByJS0COMP CATIsStorageFile(const CATUnicodeString & iszName);
HRESULT ExportedByJS0COMP CATIsStorageFile(const CATUC2Bytes FAR* pwcsName);



HRESULT CATCreateOnILockBytes( CATILockBytes FAR* iILB,
						 DWORD Mode, DWORD reserved,
						 CATIStorage FAR* FAR* oStg);

HRESULT CATOpenOnILockBytes( CATILockBytes FAR* iILB,
					       CATIStorage FAR* pstgPriority,
					       DWORD Mode, SNB snbExclude, 
					       DWORD reserved,
					       CATIStorage FAR * FAR * oStg);

HRESULT CATIsStorageILockBytes(CATILockBytes FAR* iILB);




//****** other Storage related API Prototypes ********************************
HRESULT CATReadClassStg ( CATIStorage *iStg, CLSID FAR* pclsid);
HRESULT CATWriteClassStg ( CATIStorage *iStg, REFCLSID rclsid);
HRESULT CATReadClassStm ( CATIFStream *iStm, CLSID FAR* pclsid);


//
HRESULT ExportedByJS0COMP CATGetMemFromILockBytes (CATILockBytes *iLB,
                                                   CATMemHandle *oHmem,
                                                   size_t *oSize);

HRESULT ExportedByJS0COMP CATCreateMemILockBytes (CATILockBytes **oLB,
						  CATMemHandle iHmem,
						  size_t iSize,
						  int iDelMemOnRelease=1);

HRESULT ExportedByJS0COMP CATMemAlloc ( CATMemHandle *oHmem, size_t iSize);
HRESULT ExportedByJS0COMP CATMemFree ( CATMemHandle iHmem);


HRESULT ExportedByJS0COMP CATBuildSNB ( CATUnicodeString * List, unsigned int nb, SNB *oSnb);

void ExportedByJS0COMP CATFreeSNB ( SNB iSnb);



HRESULT ExportedByJS0COMP CATGetStreamFromILockBytes (CATILockBytes *iLB,
						      CATStream **oStream);

HRESULT ExportedByJS0COMP CATCreateStreamILockBytes (CATILockBytes2 **oLB,
						     CATStream *iStr,
						     int iDelOnRelease=0);


HRESULT ExportedByJS0COMP CATCreateFileILockBytes2 (const CATUnicodeString & iszName, CATILockBytes2 **oLB, int iDRMType=0);
HRESULT ExportedByJS0COMP CATCreateFileILockBytes2 (const CATUC2Bytes *iName, CATILockBytes2 **oLB, int iDRMType=0);

HRESULT ExportedByJS0BASEILB DSYCreateOpenDRMILockBytesOnFile (CATILockBytes *& oLB,
							       DSYSysPath & iPath, int iMode, 
							       int iCreationType,  int iDRMType );

HRESULT ExportedByJS0BASEILB DSYCloseDRMILBOnFile (CATILockBytes *& iLB, char * iHttpURL, int iMode = 0);


HRESULT ExportedByJS0COMP CATGetBuffersFromILockBytes(CATILockBytes *iLB,
						      CATSysMultiBuffer **oBuf);
							  
							  
HRESULT  ExportedByJS0BASEILB DSYCreateOpenDRMILockBytesOnBuffers (CATILockBytes **oLB,
								   DSYSysMultiBuffer *iBuff, 
								   int iMode, 
								   int iCreationType,
								   int iDRMType=0 );


HRESULT ExportedByJS0BASEILB DSYSysCreateMultiBuffer(DSYSysMultiBuffer *& oHmem, size_t iSize = 1024, 
						     int iMode=DSY_RANDOM_MEDIA );

HRESULT ExportedByJS0BASEILB DSYSysCreateILockBytesOnBuffers(CATILockBytes **oLB,DSYSysMultiBuffer *iHmem);

HRESULT ExportedByJS0ZLIB DSYSysMakeZipFile(DSYSysZipFile *& poZipFile );

HRESULT ExportedByJS0BASEILB DSYMemAlloc ( CATMemHandle *oHmem, size_t iSize);

HRESULT ExportedByJS0BASEILB DSYMemFree ( CATMemHandle iHmem);


HRESULT ExportedByJS0BASEILB DSYGetMemFromILockBytes (CATILockBytes *iLB,
						      CATMemHandle *oHmem,
						      size_t *oSize);

HRESULT ExportedByJS0BASEILB DSYCreateMemILockBytes (CATILockBytes **oLB,
						     CATMemHandle iHmem,
						     size_t iSize,
						     int iDelMemOnRelease=1);

#if defined(_WINDOWS_SOURCE)    // Signatures provided for Native wchar_t support
inline HRESULT CATOpenStorage( const WCHAR FAR* pwcsName,
					  CATIStorage FAR* pstgPriority,
					  DWORD Mode, SNB snbExclude, 
					  DWORD reserved,
					  CATIStorage FAR * FAR * ppstgOpen)
{
    return CATOpenStorage(reinterpret_cast<const CATUC2Bytes FAR*>(pwcsName), pstgPriority, Mode, snbExclude, reserved, ppstgOpen);
}

inline HRESULT CATIsStorageFile(const WCHAR FAR* pwcsName)
{
    return CATIsStorageFile(reinterpret_cast<const CATUC2Bytes FAR*>(pwcsName));
}

inline HRESULT CATCreateFileILockBytes2 (const WCHAR *iName, CATILockBytes2 **oLB, int iDRMType=0)
{
    return CATCreateFileILockBytes2(reinterpret_cast<const CATUC2Bytes FAR*>(iName), oLB, iDRMType);
}
#endif

#endif
