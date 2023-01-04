//*===========================================================================*
//* COPYRIGHT DASSAULT SYSTEMES 2003                                          *
//*===========================================================================*
//*                                                                           *
//*  CATHttp                                                                  *
//*                                                                           *
//*  Usage Notes:  Utilitaires pour les URL                                   *
//*===========================================================================*
//*  Creation novembre 2003                                       adt         *
//*===========================================================================*
#ifndef CATHTTPTOOLS_H
#define CATHTTPTOOLS_H
#include <stdlib.h>
#include <memory.h>
#include <stdarg.h>
//SIP: To be included in all .h and .cpp on top a all file
#include "CATHttp.h"

#include "CATDataType.h"
#include "CATTSLib.h"
#include "CATHttpClient.h"
#include "CATHttpFlags.h"
#include "JS0HTTP.h"
#include "DSYSysTrace.h"
#include <atomic>




#ifndef HTTPARCH

//For CALLOnExitEx and ONLY FOR CALLONEXIT
int		ExportedByJS0HTTP HTTPOnExit(int  iExitCode);

#endif //HTTPARCH

#ifndef _WINDOWS_SOURCE
typedef void *	HWND;
typedef void *	PCCERT_CONTEXT;
#endif




// Quelques petites macro pour aerer le code
#ifdef _WINDOWS_SOURCE
#define ERRNOHTTP	WSAGetLastError()
#define ERRNO		GetLastError()
#else
// ++vxg - 13:08:01 - Should have this...
# include <errno.h>
// --vxg - 13:08:01
#define ERRNOHTTP errno
#define ERRNO errno
#endif 


#ifndef _WINDOWS_SOURCE
typedef enum
{
	INTERNET_SCHEME_PARTIAL = -2,
    INTERNET_SCHEME_UNKNOWN = -1,
    INTERNET_SCHEME_DEFAULT = 0,
    INTERNET_SCHEME_FTP,
    INTERNET_SCHEME_GOPHER,
    INTERNET_SCHEME_HTTP,
    INTERNET_SCHEME_HTTPS,
    INTERNET_SCHEME_FILE,
    INTERNET_SCHEME_NEWS,
    INTERNET_SCHEME_MAILTO,
    INTERNET_SCHEME_SOCKS,
    INTERNET_SCHEME_FIRST = INTERNET_SCHEME_FTP,
    INTERNET_SCHEME_LAST = INTERNET_SCHEME_SOCKS
} INTERNET_SCHEME;


typedef struct 
{
	DWORD   dwStructSize;			// size of this structure. 
	char*   lpszScheme;			// pointer to scheme name
	DWORD   dwSchemeLength;		// length of scheme name
	INTERNET_SCHEME nScheme;		// enumerated scheme type (if known)
	char*   lpszHostName;			// pointer to host name
	DWORD   dwHostNameLength;		// length of host name
	unsigned short nPort;			// converted port number
	char*   lpszUserName;			// pointer to user name
	DWORD   dwUserNameLength;		// length of user name
	char *   lpszPassword;		// pointer to password
	DWORD   dwPasswordLength;		// length of password
	char*   lpszUrlPath;			// pointer to URL-path
	DWORD   dwUrlPathLength;		// length of URL-path
	char*   lpszExtraInfo;		// pointer to extra information (e.g. ?foo or #foo)
	DWORD   dwExtraInfoLength;	// length of extra information
} CATSysURL;


#define CATURL_ESCAPE      0x80000000  // (un)escape URL characters
#define CATURL_USERNAME    0x40000000  // use internal username & password
#define CATURL_NO_ENCODE   0x20000000  // Don't convert to escape sequence
#define CATURL_DECODE      0x10000000  // Convert %XX  to characters
#define CATURL_BRWCODE	   0x02000000 


#define CATSysInternetCrackUrl CATCrackUrl
#else


#define CATURL_ESCAPE		ICU_ESCAPE
#define CATURL_USERNAME		ICU_USERNAME
#define CATURL_NO_ENCODE	ICU_NO_ENCODE
#define CATURL_DECODE		ICU_DECODE
#define CATURL_BRWCODE		ICU_BROWSER_MODE

#define CATSysURL URL_COMPONENTSA
#define CATSysInternetCrackUrl InternetCrackUrlA
#endif

// NOTE: for simple URL comparison, one can use CATSysURLObj
int ExportedByJS0HTTP CATSysCrackUrl (const char *iUrl, DWORD iLen, DWORD iFlags, CATSysURL *oURL);

int ExportedByJS0HTTP CATSysCodeUrl (const char *iUrl, char **oUrl, DWORD iFlags);
                     
/**
 * DSYEncodeURIComponent.
 * cf. JS API encodeURIComponent: https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/encodeURIComponent 
 * "The encodeURIComponent() function encodes a Uniform Resource Identifier (URI) component by replacing each instance of certain characters 
 * by one, two, three, or four escape sequences representing the UTF-8 encoding of the character (will only be four escape sequences for 
 * characters composed of two "surrogate" characters)."
 *
 * encodeURIComponent escapes all characters except: A-Z a-z 0-9 - _ . ! ~ * ' ( )
 *
 * @param [in]  iUriComponent is the URI component, which may contain UTF-8 characters
 * @param [out] oEncodedURIComponentUSASCII receives the encoded URI upon success
 * @param [in]  iFlags could be used in the future to support RFC 3986 (which reserves !, ', (, ), and *), even though these characters have no formalized URI delimiting uses.
 * @return S_OK in case of success, an error code otherwise.
 */
HRESULT ExportedByJS0HTTP DSYEncodeURIComponent(const CATUnicodeString & iUriComponent, CATUnicodeString & oEncodedURIComponentUSASCII, int iFlags = 0);

//SIP: DO NOT USE (NOT implemented)
HRESULT ExportedByJS0HTTP CATSysCodeUrlParam(const char *iParam, char **oParam, DWORD iFlags);
//SIP: DO NOT USE (NOT fully implemented)
HRESULT ExportedByJS0HTTP CATSysDecodeUrlParam(const char *iParam, char **oParam, DWORD iFlags);

void    DSYSysCharLower(char *tmp);
void	KeyToLower(char *ioHeader);
HRESULT CookieToLower(char *tmp);

HRESULT	ExportedByJS0HTTP ReturnGetLastError(void *lMyTrace, bool iIsTraDestroy, const char *iComment, unsigned int RequestID, DWORD errtmp);
//#define ReturnGetLastError(o, g, m, ...)	static_cast<HRESULT>(false ? static_cast<HRESULT>(printf(m, ##__VA_ARGS__)) : static_cast<HRESULT>(ReturnGetLastErrorFunc(o, g, m, ##__VA_ARGS__)))

HRESULT	ExportedByJS0HTTP ReturnOUTOFMEMORY(unsigned int RequestID, void *lMyTrace, const char *iMetName, const char *iVarName, bool iIsTraDestroy = false);
HRESULT	ExportedByJS0HTTP ReturnHR(unsigned int RequestID, void *lMyTrace, const char *iMetName, const char *iFonction, HRESULT hr, bool iIsTraDestroy = false);
void*	ReturnValue(unsigned int RequestID, void *lMyTrace, const char *iMetName, const char *iFonction, void *result, bool iIsTraDestroy);

//Do not used only for internal purpose
ExportedByJS0HTTP HRESULT	CATHttpSetExitMode();
ExportedByJS0HTTP bool			CATHttpIsInExit();
ExportedByJS0HTTP int		GetCATHttpPoolSize();
ExportedByJS0HTTP void 		CATHttpGetOSVersion(CATUnicodeString& oValue);
ExportedByJS0HTTP char* 	GetCATHttpUserAgent(bool isAllocation_needed, char iDriverType, void* iMyHttpTrace = nullptr, unsigned int iDriverID = 0);
char* GetCATHttpUserAgentInternal(bool isAllocation_needed, char iDriverType, void* iMyHttpTrace, unsigned int iDriverID);
unsigned int				GetNewRequestID();




#ifdef _WINDOWS_SOURCE
HRESULT ReadRegKeysString(void* lMyTrace, HKEY ihKey, const char* istrKeyName, const char* istrValueName, CATUnicodeString& oValue);
HRESULT	CreateRegKey(void *lMyTrace, HKEY iHkey, const char* iAppName, const char* iKey, DWORD iVal);
HRESULT ReadRegKeys(void *lMyTrace, HKEY ihKey, const char *istrKeyName, const char *istrValueName, DWORD &oValue);
HRESULT ExportedByJS0HTTP ReadRegKeysRegSZ(void *lMyTrace, HKEY ihKey, const char *istrKeyName, const char *istrValueName, char *oValue, DWORD &idwBufferSize);

unsigned int ExportedByJS0HTTP DSYSysGetIEVersion();

#endif

char*	CATHttpGetAppName(unsigned int RequestID, void *lMyTrace);

//Not only windows for application name traces
HRESULT	InitializeRegKeys(void *lMyTrace);

void	CATHttpCreateTrace(void *&lMyHttpTrace);

//DS flags for URL Encoding
#define CATHTTP_URL_ENCODE_NONE			(CATURL_ESCAPE | 0x00000000L)
#define	CATHTTP_URL_ENCODE_URL			(CATURL_ESCAPE | 0x00000001L)
#define	CATHTTP_URL_ENCODE_QUERY		(CATURL_ESCAPE | 0x00000002L)
#define	CATHTTP_URL_ENCODE_FRAGMENT		(CATURL_ESCAPE | 0x00000004L)
#define	CATHTTP_URL_ENCODE_PARAM		(CATURL_ESCAPE | 0x00000006L)
#define	CATHTTP_URL_ENCODE_ALL			(CATURL_ESCAPE | CATHTTP_URL_ENCODE_URL | CATHTTP_URL_ENCODE_QUERY | CATHTTP_URL_ENCODE_FRAGMENT)

#endif


