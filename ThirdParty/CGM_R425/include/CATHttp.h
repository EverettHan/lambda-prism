#ifndef CATHTTP_H
#define CATHTTP_H

 /* Utilisation archive */
#ifdef HTTPARCH

//////////////////////////////////////////////////////
//           Define for HttpTool                    //
//////////////////////////////////////////////////////
//#define	DSYSysTrace				DSYHttpArchTrace
#define IsDSYCommunicationHubOn		IsDSYCommunicationHubOnARCH
#define GetDSYCommunicationHubPort	GetDSYCommunicationHubPortARCH
#define SetDSYCommunicationHubEnv	SetDSYCommunicationHubEnvARCH

#define GetCATCookieCache		DSYHTTPGetCATCookieCache
#define HTTPOnExit				DSYHTTPOnExit
#define SetField				DSYArchSetField
#define CATSysCodeUrl			DSYSysCodeUrl
#define CATSysCrackUrl			DSYSysCrackUrl
#define DSYSysCharLower			DSYSysArchCharLower
#define realKeyToLower			DSYArchrealKeyToLower
#define KeyToLower				DSYArchKeyToLower
#define realCookieToLower		DSYArchrealCookieToLower
#define CookieToLower			DSYArchCookieToLower
#define ReturnGetLastError		DSYArchReturnGetLastError
#define ReturnOUTOFMEMORY		DSYArchReturnOUTOFMEMORY
#define ReturnHR				DSYArchReturnHR
#define S_MyHttpTrace			S_MyDSYArchHttpTrace
#define CATHttpGetAppName		DSYHttpGetAppName

#ifdef _WINDOWS_SOURCE

#define CreateRegKey			DSYArchCreateRegKey
#define InitializeRegKeys		DSYArchInitializeRegKeys
#endif

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

//////////////////////////////////////////////////////
//           Define for HTTP classes                //
//////////////////////////////////////////////////////
#define CATHttpClient			DSYHttpClient
#define CATHttpAsyncClient		DSYHttpAsyncClient
#define CATHttpAsyncClientPool	DSYHttpAsyncClientPool
#define CATHttpClientPool		DSYHttpClientPool
#define CATHttpFileClientPool	DSYHttpFileClientPool
#define CATHttpConnection		DSYHttpConnection

#define CATThreadHttpPool		DSYThreadHttpPool

#define CATHttpCache			DSYHttpCache
#define CATHttpAuthenticattion	DSYHttpAuthenticattion

#define	AsyncInternetInfo		DSYAsyncInternetInfo

#define CATHttpDriver			DSYHttpDriver
#define CATHttpDriverBase		DSYHttpDriverBase

#define inetCallBackFn			DSYinetCallBackFn

#define CATHttpDSDriver			DSYHttpDSDriver

#define CATBaseSock				DSYBaseSock
#define CATHttpSock				DSYHttpSock

#define CATHttpWDriver			DSYHttpWDriver
#define CATHttpASyncWDriver		DSYHttpASyncWDriver

#define CATHttpFileClient		DSYHttpFileClient

#define CATThreadHttpDownloadCreator	DSYThreadHttpDownloadCreator
#define CATThreadHttpDownload	DSYThreadHttpDownload

//#define CATThreadHttpCallbackCreator	DSYThreadHttpCallbackCreator
//#define CATThreadHttpCallback	DSYThreadHttpCallback

#define	CATHttpWindowHandler	DSYHttpWindowHandler

// define for Mac & iOS
#define DSYSysDriverMacDelegate	DSYSysArchDriverMacDelegate
#define caseInsensitiveEqual	DSYArchcaseInsensitiveEqual
#define caseInsensitiveHash		DSYArchcaseInsensitiveHash
//#define NSHTTPURLResponse		DSYArchNSHTTPURLResponse
#define AsyncMacInfoObjc		DSYArchAsyncMacInfoObjc
#define OuputQObjc				DSYArchOuputQObjc

#define CATHttpMacDriver		DSYHttpMacDriver
#define DSYSysDriverMacBase		DSYSysArchDriverMacBase

#define DSYSysTSDico			DSYSysTSDicoArch

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////


//////////////////////////////////////////////////////
//		       Define for cookies                   //
//////////////////////////////////////////////////////
#define HaskKey					DSYHaskKey
#define GetCookieAttr			DSYGetCookieAttr
#define GetCookiePropertie		DSYGetCookiePropertie
#define CATHttpCookie			DSYHttpCookie
#define InitCookie				DSYInitCookie
#define	IsValidDomain			DSYIsValidDomain
#define CATSysSetCookie			DSYSysSetCookie
#define CATSysGetCookie			DSYSysGetCookie
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////



//////////////////////////////////////////////////////
//             Define SSL Name for HTTPARCH         //
//////////////////////////////////////////////////////
#define CATHttpSSLError			DSYHttpSSLError
#define CATSysSSLVerify			DSYSysSSLVerify
#define CATHttpSSLSetupClient	DSYHttpSSLSetupClient
#define CATHttpSSLSock			DSYHttpSSLSock

#define CATHttpSSLDriver		DSYHttpSSLDriver
//SIP: Redefine in cpp, other ways it won't work
//#define CATBuildHttpDriver	DSYBuildHttpDriver

#define locking_callback		DSYlocking_callback
#define thread_setup			DSYthread_setup
#define thread_cleanup			DSYthread_cleanup

#define	initTerm				DSYinitTerm
#define initSSLLockingCallbacks	DSYinitSSLLockingCallbacks
#define BuildSSLDriver			DSYBuildSSLDriver
#define SSLDriverFreeSession	DSYSSLDriverFreeSession
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////



//////////////////////////////////////////////////////
//             Define CAS Name for HTTPARCH         //
//////////////////////////////////////////////////////
#define CheckIfCASValid DSYCheckIfCASValid
#define CheckIfCASValidV2 DSYCheckIfCASValidV2
#define CheckIfCASValidFromCASUrl DSYCheckIfCASValidFromCASUrl




//////////////////////////////////////////////////////
//     Define OS LEVEL / USERAGENT for HTTPARCH     //
//////////////////////////////////////////////////////
#define CATHttpGetOSVersion             DSYArchHttpGetOSVersion
#define GetCATHttpUserAgentInternal     GetDSYArchHttpUserAgentInternal

#endif /*HTTPARCH */


/************************************************************************/
/* Local includes                                                       */
/************************************************************************/
#include "DSYExport.h"


/************************************************************************/
/* Defines                                                              */
/************************************************************************/
#if defined(__JS0HTTP)
# define ExportedByJS0HTTP   DSYExport
#else  // __JS0HTTP
# define ExportedByJS0HTTP   DSYImport
#endif // __JS0HTTP

#ifdef HTTPARCH
# undef ExportedByJS0HTTP
# define ExportedByJS0HTTP
#endif  // HTTPARCH



#endif
