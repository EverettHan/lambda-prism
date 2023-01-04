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
#ifndef __CATISTORAGE
#define __CATISTORAGE

#include "CATWTypes.h"
#include "CATSysDataType.h" // CATUC2Bytes
#include "IUnknown.h"

class  CATIEnumSTATSTG;
class  CATIFStream;

extern IID IID_CATIStorage;

class  CATIStorage :public IUnknown
{

 public:
  virtual HRESULT __stdcall CreateStream( const OLECHAR FAR* ipwcsName,
					  DWORD iMode,
					  DWORD reserved1,
					  DWORD reserved2,
					  CATIFStream FAR*FAR* oStream) = 0;
        
  virtual HRESULT __stdcall OpenStream( const OLECHAR FAR *ipwcsName,
					void FAR *reserved1,
					DWORD iMode,
					DWORD reserved2,
					CATIFStream FAR*FAR* oStream) = 0;
        
  virtual HRESULT __stdcall CreateStorage( const OLECHAR FAR *ipwcsName,
					   DWORD iMode,
					   DWORD dwStgFmt,
					   DWORD reserved2, 
					   CATIStorage FAR*FAR* oStorage) = 0;
        
  virtual HRESULT __stdcall OpenStorage( const OLECHAR FAR* ipwcsName,
					  CATIStorage FAR* pstgPriority,
					  DWORD iMode, 
					  SNB iSnbExclude,
					  DWORD reserved, 
					  CATIStorage FAR*FAR* oStorage) = 0;
        
  virtual HRESULT __stdcall CopyTo( DWORD iCiidExclude,
				    const IID FAR* iRgiidExclude,
				    SNB iSnbExclude, 
				    CATIStorage FAR* iStgDest) = 0;
        
  virtual HRESULT __stdcall MoveElementTo( const OLECHAR FAR *iName,
					   CATIStorage FAR *iStgDest,
					   const OLECHAR FAR* iNewName,
					   DWORD iFlags) = 0;
        
  virtual HRESULT __stdcall Commit( DWORD iCommitFlags) = 0;
        
  virtual HRESULT __stdcall Revert( void) = 0;
        
  virtual  HRESULT __stdcall EnumElements( DWORD reserved1,
					   void FAR* reserved2,
					   DWORD reserved3,
					   CATIEnumSTATSTG FAR*FAR* oEnum) = 0;
        
  virtual HRESULT __stdcall DestroyElement( const OLECHAR FAR* iName) = 0;
        
  virtual HRESULT  __stdcall RenameElement( const OLECHAR FAR* iOldName,
					    const OLECHAR FAR* iNewName) = 0;
        
  virtual HRESULT  __stdcall SetElementTimes( const OLECHAR FAR* ipwcsName,
					      const FILETIME FAR* ipctime,
					      const FILETIME FAR* ipatime,
					      const FILETIME FAR* ipmtime) = 0;
        
  virtual HRESULT __stdcall SetClass( REFCLSID iClsid) = 0;
        
  virtual HRESULT __stdcall SetStateBits( DWORD iStateBits, DWORD iMask) = 0;
        
  virtual HRESULT __stdcall Stat( STATSTG FAR* oStatstg, DWORD iStatFlag) = 0;
  
  
#if defined(_WINDOWS_SOURCE)
  // For interoperability with CATUnicodeString
  static_assert(sizeof(OLECHAR) == sizeof(CATUC2Bytes), "sizeof(OLECHAR) must be equal to sizeof(CATUC2Bytes) for the following implementation to be valid!");

  HRESULT __stdcall CreateStream( const CATUC2Bytes FAR* ipwcsName,
					  DWORD iMode,
					  DWORD reserved1,
					  DWORD reserved2,
					  CATIFStream FAR*FAR* oStream)
  {
      return CreateStream(reinterpret_cast<const OLECHAR FAR*>(ipwcsName), iMode, reserved1, reserved2, oStream);
  };
        
  HRESULT __stdcall OpenStream( const CATUC2Bytes FAR *ipwcsName,
					void FAR *reserved1,
					DWORD iMode,
					DWORD reserved2,
					CATIFStream FAR*FAR* oStream)
  {
      return OpenStream(reinterpret_cast<const OLECHAR FAR*>(ipwcsName), reserved1, iMode, reserved2, oStream);
  }
        
  HRESULT __stdcall CreateStorage( const CATUC2Bytes FAR *ipwcsName,
					   DWORD iMode,
					   DWORD dwStgFmt,
					   DWORD reserved2, 
					   CATIStorage FAR*FAR* oStorage)
  {
      return CreateStorage(reinterpret_cast<const OLECHAR FAR*>(ipwcsName), iMode, dwStgFmt, reserved2, oStorage);
  }
        
  HRESULT __stdcall OpenStorage( const CATUC2Bytes FAR* ipwcsName,
					  CATIStorage FAR* pstgPriority,
					  DWORD iMode, 
					  SNB iSnbExclude,
					  DWORD reserved, 
					  CATIStorage FAR*FAR* oStorage)
  {
      return OpenStorage(reinterpret_cast<const OLECHAR FAR*>(ipwcsName), pstgPriority, iMode, iSnbExclude, reserved, oStorage);
  }
                      
  HRESULT __stdcall MoveElementTo( const CATUC2Bytes FAR *iName,
					   CATIStorage FAR *iStgDest,
					   const CATUC2Bytes FAR* iNewName,
					   DWORD iFlags)
  {
      return MoveElementTo(reinterpret_cast<const OLECHAR FAR*>(iName), iStgDest, reinterpret_cast<const OLECHAR FAR*>(iNewName), iFlags);
  }
  
  HRESULT __stdcall DestroyElement( const CATUC2Bytes FAR* iName)
  {
      return DestroyElement(reinterpret_cast<const OLECHAR FAR*>(iName));
  }
        
  HRESULT  __stdcall RenameElement( const CATUC2Bytes FAR* iOldName, const CATUC2Bytes FAR* iNewName)
  {
      return RenameElement(reinterpret_cast<const OLECHAR FAR*>(iOldName), reinterpret_cast<const OLECHAR FAR*>(iNewName));
  }
        
  HRESULT  __stdcall SetElementTimes( const CATUC2Bytes FAR* ipwcsName,
					      const FILETIME FAR* ipctime,
					      const FILETIME FAR* ipatime,
					      const FILETIME FAR* ipmtime)
  {
      return SetElementTimes(reinterpret_cast<const OLECHAR FAR*>(ipwcsName), ipctime, ipatime, ipmtime);
  }
#endif
};

 
#endif
