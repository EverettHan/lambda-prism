#ifndef CATechTrackCounter_h
#define CATechTrackCounter_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */
//------------------------------------------- 
//  Utilities
//------------------------------------------- 

/* 
* ------------------------------------------------------------------------------------------------------- 
*       
*   Another small Infrastructure Toolkit for perfectible pattern usage 
*       of simplified counter locking lifecycle without knowledge of caller 
*      (originated from distributed objects or IUknown* interfaces )
*       
*   In case of following area provides no solutions occured :
*      software redesign with advanced commodities of "system" ObjetcModeler (CacheExtension,....) or  better proprieraty ...
*      no mkCheckSource detection previously identify incorrect writting
*       
*   To help tiny debug in case of manual MLK tracking of a mismatch AddRef/Release() 
*       
*   This toolkit is intended to reduce noice about memory leaks    
*      with symptoms on official indicators focusing on stack trace of creation (burden on genuine provider)
*      wherever correction is generally about mismatch AddRef/Release() 
*
*   This small toolkit service is intented to fasten analysis and be as be as simple as possible to be reusable
*
*       0/ Build-Time on callee CBU : two main impact of software implementation of CBU
*
*                step A) Change constructor to add as last argument the following default value :
*                          const char *iFwCaller = CATechFrameworkCaller(_MK_FWNAME_)
*                          Purpose is to capture framework creation caller.
*
*                step B) Deploy  CATechTrackCounter services
*                            on Ctor/Dtor and overload QueryInterface()/AddRef()/Release() 
*
                        CATechExt::CATechExt(const char *iFwCaller)  
                        {
                          if ( iFwCaller && (iFwCaller[0] != '\0') )  CATechTrackCounter::TrackCtor(this,iFwCaller);
                        }
*
                        CATechExt::~CATechExt()
                        { 
                          CATechTrackCounter::TrackDtor(this);
                        }
*
                        HRESULT __stdcall CATechExt::QueryInterface(const IID &iIID, void **oPPV) 
                        {
                          HRESULT result = E_FAIL;
                          if (oPPV)
                            *oPPV = NULL;
                          result = this->void::QueryInterface(iIID,oPPV);
                          if (oPPV && *oPPV)
                            CATechTrackCounter::TrackAddRef(this->m_cRef,this);
                          return result;
                        }
*
                        ULONG   __stdcall CATechExt::AddRef() 
                        { 
                          ULONG res = void::AddRef(); 
                          CATechTrackCounter::TrackAddRef(this->m_cRef,this);
                          return res; 
                        }
*
                        ULONG   __stdcall CATechExt::Release() 
                        {
                          CATechTrackCounter::TrackRelease((this->m_cRef-1),this);
                          ULONG res = void::Release();
                          return res; 
                        }
*
*
*       1/ Usage to Activate:  valuate an environnement variable 
*                              with framework caller of creation CBU as filter
*
*                set CATechTrackCounter=Phoenix_Tessellate.tst
*
*
*       2/ Analysis to do : Dump on each instance with adresse to identify callers 
*
*                For ODT Associated filename on Output directory is about :
*
                     Cat0_CpuLoop_NarrowRegion_RI588771.Phoenix_Tessellate.tst_0x 15A9C00.txt
*                
                       Constructor -> 1 
                          CATStackTrace::GetTraceInternal<catstacktrace.cpp:03054>
                          CATStackTrace::GetTrace<catstacktrace.cpp:03765>
                          CATechTrackCounter::CommonTrack<catphoenixmlkcbu.cpp:00199>
                          CATechTrackCounter::TrackCtor<catphoenixmlkcbu.h:00100>
                          CATechExt::CATechExt<catphoenixext.cpp:00024>
                          CATech_CATTessSettingsExt::CATP<catphoenix_cattessse:00046>
                          CATech_Create_CATTessSettings<catphoenix_cattessse:00033>
                          CATechBehavior_FromEggsLateType<catphoenixhandle.cpp:00738>
                          CATTessParameters::HasPhoenixExtension<parameters.cpp:00639>
                          CATech_CATTessellateExt::SendRe<catphoenix_cattessel:01077>
                          CATech_PhoenixImpl::parse_Varia<catphoenix_phoenixim:00438>
                          CATech_Reborn_SAXHandler::Start<catphoenix_reborn_sa:00283>
                          TIECATISAXContentHandlerCATSAXDefau<catsaxdefaulthandler:00018>
                          CATSAXMS3ContentHandlerWrapper::sta<catsaxms3contenthand:00157>
                          TIEISAXContentHandlerCATSAXMS3Conte<catsaxms3contenthand:00032>
                          DllCanUnloadNow
                          DllCanUnloadNow
                          DllCanUnloadNow
                          DllCanUnloadNow
                          0x788e146f[msxml5]
                          0x788e7f69[msxml5]
                          CATSAXMS3XMLReaderImpl::Parse<catsaxms3xmlreaderim:00146>
                          TIECATISAXXMLReaderCATSAXMS3XMLRead<catsaxms3xmlreaderim:00066>
                          CATech_PhoenixImpl::StartDo_rec<catphoenix_phoenixim:00512>
                          CATech_MonitorImpl::StaticRebor<catphoenix_monitorim:00206>
                          CATech_MonitorImpl::Reborn<catphoenix_monitorim:00056>
                          CATechHandle::Reborn<catphoenixhandle.cpp:00263>
                          CATCX_MEMORY_MAIN_FUNCTION<phoenix.cpp:00106>
                          main<phoenix.cpp:00030>
                          _tmainCRTStartup<crtexe.c:00597>
                          RegisterWaitForInputIdle
                          RegisterWaitForInputIdle
 
*
* ------------------------------------------------------------------------------------------------------- 
*/
#include "ExportedByCATTechTools.h"
#include "CATUnicodeString.h"
#include "CATSysSimpleHashTable.h"
 
  
#ifndef CATechFrameworkCaller
#define CATechFrameworkCallerExpansed(x) #x
#define CATechFrameworkCaller(x)         CATechFrameworkCallerExpansed(x)
#endif

//------------------------------------------------------------------------
// CATechTrackCounter for MLK tracking of mismatch AddRef/Release() 
//------------------------------------------------------------------------
class  ExportedByCATTechTools CATechTrackCounter
{ 
public :
 
   
  /** 
  *  Publish Ctor  
  */           
  inline static void TrackCtor( void  *iCBU,  const char *iFwCaller = CATechFrameworkCaller(_MK_FWNAME_) );
 
  /** 
  *  Publish AddRef  
  */           
  inline static void TrackAddRef(LONG iAfter_m_cRef, void   *   iCBU);
 
  /** 
  *  Publish Release  
  */           
  inline static void TrackRelease(LONG iAfter_m_cRef, void   *   iCBU);
    
  /** 
  *  Publish Dtor  
  */           
  inline static void TrackDtor(void   *   iCBU);

 
private : 

  /** 
  *  _Initialize
  */           
  static void   _Initialize();
  
  /** 
  *  CommonTrack  
  *     0 : Ctor
  *    +1 : AddRef
  *    -1 : Release
  *    -2 : Dtor
  */           
  static void CommonTrack(const short iTrack, LONG iAfter_m_cRef, void   *   iCBU);

  /** 
  *  Data
  */ 
  static CATUnicodeString         _FilterName;
  static int                      _IsInitialized;
  static CATSysSimpleHashTable *  _Tracked;

};
           
//-------------------------------------------------------------------------------------------------
// TrackCtor
//-------------------------------------------------------------------------------------------------
inline   void  CATechTrackCounter::TrackCtor(void   *   iCBU, const char *iFilterCaller)
{ 
  if ( !iFilterCaller || !iCBU )  return;
  if ( ! _IsInitialized ) _Initialize();  
  if ( (iFilterCaller[0] != '\0')  && (0 == strcmp(iFilterCaller,_FilterName.ConvertToChar())) )
    CommonTrack(0,+1,iCBU);
}
 
//-------------------------------------------------------------------------------------------------
// TrackAddRef
//-------------------------------------------------------------------------------------------------
inline   void  CATechTrackCounter::TrackAddRef(LONG iAfter_m_cRef, void   *   iCBU)
{ 
  if ( ! iCBU || (+1 != _IsInitialized) || ! _Tracked ) return;
  if ( _Tracked->Locate(iCBU)   )
    CommonTrack(+1,iAfter_m_cRef,iCBU );
}
          
  
//-------------------------------------------------------------------------------------------------
// TrackRelease
//-------------------------------------------------------------------------------------------------
inline   void  CATechTrackCounter::TrackRelease(LONG iAfter_m_cRef, void   *   iCBU)
{ 
  if ( ! iCBU || (+1 != _IsInitialized) || ! _Tracked ) return;
  if ( _Tracked->Locate(iCBU)   )
    CommonTrack(-1,iAfter_m_cRef,iCBU );
}

//-------------------------------------------------------------------------------------------------
// TrackDtor
//-------------------------------------------------------------------------------------------------
inline   void  CATechTrackCounter::TrackDtor(void   *   iCBU)
{ 
  if ( ! iCBU || (+1 != _IsInitialized) || ! _Tracked ) return;
  if ( _Tracked->Locate(iCBU)   )
    CommonTrack(-2,0,iCBU );
}

 
#endif
