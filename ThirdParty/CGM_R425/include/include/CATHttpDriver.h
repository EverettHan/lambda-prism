//*===========================================================================*
//* COPYRIGHT DASSAULT SYSTEMES 1996                                          *
//*===========================================================================*
//*                                                                           *
//*  CATHttp                                                                  *
//*                                                                           *
//*  Usage Notes:  Client Http V1.0                                           *
//*===========================================================================*
//*  Creation novembre 2003                                       adt         *
//*===========================================================================*
#ifndef CATHTTPDRIVER_H
#define CATHTTPDRIVER_H
#include <stdlib.h>
#include <memory.h>
#include <string>
#include <unordered_map>

#include "CATDataType.h"
#include "CATHttp.h" 
#include "CATHttpClient.h" 
#include "CATHttpFlags.h"
#include "CATHttpTools.h"
#include "CATHttpRequest.h"
#include "CATEvent.h"
#include "DSYSysTimer.h"
#include "CATSysTSTime.h"
#include "DSYSysHTTPPerfInfoCB.h"
#include "DSYSysRefCounter.h"
#include <atomic>
#include "DSYString.h"

//#include <atomic>

#define CLIENT_CONNECTED 1
#define CLIENT_DISCONNECTED 2

#define SIZEB 2048


#define FWIN32      FACILITY_WIN32

//definition des methodes
#define POST	"POST"
#define PUT		"PUT"
#define GET		"GET"
#define HEAD	"HEAD"
#define OPTIONS "OPTIONS"

#define LENGTHLOWER			"content-length: "
#define LENGTH10			LENGTHLOWER
#define LENGTH11			LENGTHLOWER
#define TYPELOWER			"content-type: "
#define TYPE10				TYPELOWER
#define TYPE11				TYPELOWER
#define CONTENTRANGE		"Content-Range: "
#define CONTENTRANGELOWER	"content-range: "
#define TRANSFERENCODING	"Transfer-Encoding: "
#define TRANSENCODINGLOWER	"transfer-encoding: "
#define LOCATIONLOWER		"location: "
#define CONNECTIONLOWER		"connection: "
#define ALIVE				"Connection: Keep-Alive\r\n"
#define PROXYALIVE			"Proxy-Connection: Keep-Alive\r\n"
#define CRLF				"\r\n"
#define BODYSEPAR			"\r\n\r\n"
#define ACCEPTRANGE			"Accept-Ranges: bytes\r\n"
#define RANGE				"Range: bytes="
#define ACCEPTALL			"Accept: */*\r\n"
#define AUTH				"Proxy-authorization: "

#define URLTYP				"application/x-www-form-urlencoded"
#define HTMLTYP				"text/HTML"
#define XMLTYP				"text/xml"
#define XMLUTF8TYP			"text/xml;charset=utf-8"
#define OCTECT				"application/octetstream"
#define DEFTYP				"text/plain"
#define WWWBASICAUTH		"Authorization: Basic "

#define WUSERAGENT			"CATIA HTTP CLIENT v3.0-DS_W"
#define DSUSERAGENT			"CATIA HTTP CLIENT v3.0-DS_U"
#define MACUSERAGENT		"CATIA HTTP CLIENT v3.0-DS_M"
#define IOSUSERAGENT		"CATIA HTTP CLIENT v3.0-DS_I"
#define DEFAULTUSERAGENT	"CATIA HTTP CLIENT v3.0-DS_D"
// CRLF utile qd on construit les requetes soit meme
//SIP: Not used till 24/06/2011 (take care of \r\n)
//#define TSSLUSERAGENT		"CATIA HTTP CLIENT v2.0.ssl-DS\r\n"

// erreurs internes non vues depuis l'exterieur
#define CONTINUEREADING  -11
#define RECEPTION_ERR -12

#define CHUNKED			CATHTTP_CHUNK		// 0x00000001
#define HEADERSENT		0x00000010
#define REQUESTSEND		0x00000020
#define OPENREQDONE		0x00000040
#define RECEPTION		0x00000100
#define OPTIONSSET		0x10000000

#define CHUNK_PER_CHUNK		CATHTTP_CHUNK_PER_CHUNK //0x00001000

class CATSysHttpStreamer;

#pragma warning( push )
#pragma warning( disable : 4275 )
class ExportedByJS0HTTP  CATHttpDriver : public DSYSysRefCounter
{
	friend class CATHttpSSLDriver;
	friend class CATThreadHttpDownload;
	friend class CATThreadHttpCallback;
	friend class CATHttpAsyncClient;

public:
	CATHttpDriver();
	virtual ~CATHttpDriver();

	// Connection methode generale 
	virtual int		Connect(const char *iHostName, unsigned short iPort = 80, int iFlags = 0) = 0;
	// Connection methode simplifiee a partir de l'url brute
	virtual int		Connection(const char *iURL) = 0;


	// Methodes generales pour les actions principales du protocole
	virtual int		Get(const char *iWhatToGet, int iFlags, char **oBufferPointer, int *oReceivedLen, int *oConnectionChanged = nullptr);

	virtual int		Head(const char *iInfo, int iFlags, CATFileInfo64 *info);

	virtual	int		Options(const char * iWhatToGet, int iFlags);
		
	virtual int		Delete(const char *iWhatToGet, int iFlags, char **oBufferPointer, int *oReceivedLen, int *oConnectionChanged = nullptr);
	virtual int		Link(const char *iWhatToGet, int iFlags, char **oBufferPointer, int *oReceivedLen, int *oConnectionChanged = nullptr);

	// Get par troncons
	virtual  int	GetSegment(const char *iWhatToGet, int iFlags, int iPos, off_t iOffset, size_t iLen, char **oBufferPointer, int *oReceivedLen,	int *oConnectionChanged = nullptr);

	// Post d'un bloc
	virtual int		Post(const char *iWhatToGet, int iFlags, const char* iToPost, size_t iLen, CATHTTPType iContentType, int *oConnectionChanged, char **oResponse, int *oResponseLen);
	virtual int		Put(const char *iWhere, int iFlags, const char* iBuffer, size_t iLen, CATHTTPType iContentType, int *oConnectionChanged, char **oResponse = nullptr, int *oResponseLen = 0);
	virtual int		Patch(const char *iWhere, int iFlags, const char* iBuffer, size_t iLen, CATHTTPType iContentType, int *oConnectionChanged, char **oResponse = nullptr, int *oResponseLen = 0);

	// Post en streaming/chunked
	virtual int		Post(const char *iWhatToGet, int iFlags, CATHTTPType iContentType, CATSysHttpStreamer *iStreamer, int *oConnectionChanged, char **oResponse, int *oResponseLen);











	// Manipulation directe du protocole HTTP
	// creation de la requete
	virtual int		OpenRequest(const char *iVerb, const char *iRequestedObject, DWORD iFlags, const char **iAccept = nullptr) = 0;

	// Ajout de header supplementaire
	virtual int		AddRequestHeaders(const char *Header, DWORD iFlags = CATHTTP_REQ_COALESCE) = 0;





	virtual int		SendRequestAsync(int iVerb);
	// Envoi de le requete
	virtual int		SendRequest(CATSysHttpStreamer *iStreamer) = 0;
	// Envoi de le requete
	virtual int		SendRequest(const char *iBuffer = nullptr, size_t iLength = 0, int iVerb = 0) = 0;
	// Debut d'envoi de la requete
	virtual int		BeginSendRequest(int iVerb, size_t iTotalLen, int IsChunked) = 0;
	// Envoi des donnees brutes ( pas de header ici- pour les headers
	// il faut utiliser addheader apres le OpenRequest avant le BeginSend
	// qui se charge du Content-Length et du transfert encoding
	virtual int		SendRawData(const char* iBuffer, size_t iLen) = 0;
	//fin de requete (destruct intarnal for Async)
	virtual int		CloseRequest() = 0;

	//fin de requete for Async
	virtual HRESULT	FinalizeRequest();

	//Return a char * that cannot be deleted or freed by caller
	virtual char*	GetLastRedirectUrl();




	// recuperation de la reponse apres le SendRequest
	virtual int		GetResponseHeaders (char **oHeader, size_t* oLen, size_t* oNext = 0, DWORD iFlags = CATHTTP_QUERY_ALL, const char* iHeader=nullptr) = 0;

	//option de la connection
	virtual int		GetOptions ( DWORD iOption, void *oBuffer, size_t *ioLen) = 0;
	virtual int		SetOptions ( DWORD iOption, const void *iBuffer, size_t iLen) = 0;


	// recuperation de la ressource
	// Non virtuel car c'est le GetBody qui fait le travail
	virtual int		Download(size_t *oLenResponse, char **oBody);
	// Non virtuel car c'est le GetBody qui fait le travail
	virtual int		DownloadEx(int iMode, size_t *oLenResponse, char **oBody, int *NoMoreData);


	virtual int		GetType() = 0;


	virtual HRESULT	Cancel();

	virtual HRESULT	GetThreads();
	virtual HRESULT	StartDLThread(bool iIsLooping = true, HRESULT irc = S_OK);
	virtual HRESULT	StartCBThread(bool iIsLooping = true, HRESULT irc = S_OK);
	virtual HRESULT	StartThreads(bool iIsLooping = true, HRESULT irc = S_OK);
	virtual HRESULT StopThreads();
	virtual HRESULT ReleaseFromClient();

	int	WaitForRelease();
	int	SetRelease();
	int ResetWait();

	std::atomic_bool		_IsUsed;

	//only for traces
	static std::atomic_uint	_DriverID;

protected:
	// Methodes generique en protected  pour servir d'adapteur
	virtual void	Trace(char * EntityBody, size_t TotLenRecue, int text);
	virtual int		ComputeTrace(char *EntityBody, size_t iStart, size_t iEnd);
	virtual int		AnalyseResponse(const char* iUrl,const char* iMethode, char *iResponse, size_t iLen, int *oVersion, int *oHttpRC, CATULONG64 *oLenResponse, int *oTransfert, int *oConnection, char **oLocation,  int *oBody, int *oType, int iFlags = 0);
	virtual int		GetCredentials(const char*iUrl, int iHttpRC, const char *iAuthScheme, const char *iRealm, char ** oCrendential);
	virtual int		NewAddHeaders(const CATUnicodeString Header, DWORD iFlags);
	virtual int		AddHeaders(const char *Header,  DWORD iFlags, size_t *ioLen, char** ioBuff);
	virtual int		InitHeaders();
	virtual int		CloseConnection();
	virtual HRESULT	DSInternetQueryDataAvailable(DWORD &iDispo);
	virtual HRESULT	DSInternetReadFile(size_t *ioLenResponse, char **oBody, DWORD iDispo, DWORD	&Downloaded);
	virtual int		GetBody(int iTransfert, size_t *ioLenResponse, char **oBody);
	virtual	HRESULT	SetLastRedirectUrl(const char *iUrl);
	int				PreModificationOnUrl(); //To put host name in lower case and suppress port 80 and 443
	int				AfterSend(const char *iWhatToGet, const char* iMethode, int  &HttpRC, int iFlags, char *&oLocation, char **oResponseBuffer, CATULONG64 *oResponseLen, int *oConnectionChanged);
	bool			IsOffline();
	int				InternalHttpSendDataEx(const char *iVerb, const char *iWhatToGet, int iFlags, const char * iHeaders, const char* iToSend, size_t iLen,
		CATHTTPType iContentType, int *oConnection, char **oResponseBuffer, CATULONG64 *oResponseLen, CATSysHttpStreamer *iStreamer);
	int				HttpSendDataEx(const char *iVerb, const char *iWhatToGet, int iFlags, const char *iHeaders, const char* iToSend, size_t iLen,
		CATHTTPType iContentType, int *oConnection, char **oResponseBuffer, CATULONG64 *oResponseLen, CATSysHttpStreamer *iStreamer = nullptr);
	bool			IsHttpRedirect(unsigned int ihttpRc);
	bool			IsHttpRedirectSameMethod(unsigned int ihttpRc);


	int						_Is_Keep_Error_Body;
	//Internet TIMEOUT
	// _ReceiveTimeout : Timeout on data read. default = 36000000 (10h)
	// _SendTimeout : Timeout on data write. default = 36000000 (10h)
	// _ConnectTimeout : Timout to establish connection with the servser. default = 10000 (10s)
	ULONG					_ReceiveTimeout;
	ULONG					_SendTimeout;
	ULONG					_ConnectTimeout;
	DWORD					_IsBodyToRead;
	CATULONG64				_Reception;
	bool					_IsResendFormDriver;


	ULONG					_UrlEncodeMode;

	//Timer to get elaps for download and upload limitation
	DSYSysTimer				_DownloadElaps;
	DSYSysTimer				_UploadElaps;

	//Limitation of upload and download
	size_t					_UploadOctetLimitation;
	size_t					_DownloadOctetLimitation;


	//Total Data Size or 0 inb chunk mode
	CATULONG64				_TotalContentLen;
	CATULONG64				_CurContentLen;

	//Total Data Size for send or 0 inb chunk mode
	CATULONG64				_SendTotalContentLen;
	CATULONG64				_SendCurContentLen;

	// Qqs headers preparatoires
	char*					_PreRequest;
	size_t					_PreRequestLen;


	/*
	** Used to manage the user agent name independently of the driver type
	*/
	int						ManageUserAgent(const char *iUserAgent);
	char*					_UserAgent;	//indicate the user agent


	/*
	** Used to able caller to manage redirection
	*/
	char*					_LastRedirectUrl;


	/*
	** Used for full ASYNC request
	*/
	std::atomic_bool		_IsFullAsync;
	bool					_IsSendRequestEx;
	CATUnicodeString		_Url;
	CATUnicodeString		_Verb;
	int						_Flags;
	CATHTTPType				_ContentType;

	/*
	** User/Password for basic authentication in DSDriver
	*/
	char					*_UserName;	//indicate the user name for 401
	char					*_UserPassword;	//indicate the user password for 401
	char					*_ProxyUserName;	//indicate the user name for 407
	char					*_ProxyUserPassword;	//indicate the user password for 407

	static char				*_Credential;
	static char				*_ProxyCredential;

	std::atomic_bool		_NoDownLoadThread;
	DWORD					_AsyncObjAutoDelete;

	//For Traces:
	void					*_MyHttpTrace;

	CATHttpAsyncObject		*_AsyncObj;
	CATSysTSTime			_Time;
	DSYSysHTTPPerfInfoCB	*_PerfInfoCB;

	//SIP: Only usefull to be compatible with QueryDataAvailable
	size_t					_BodyLen;
	char					*_Body;
	unsigned int			_NbTry; //for redirect
	std::atomic_bool		_EndReached;
	std::atomic_bool		_IsAfterSendDone;
	CATEvent				*_FinishEvent;
	int						_HttpRC;
	CATHttpRequest			*_CurrentRequest;
	bool					_CanFollowRedirect;
	std::unordered_map<std::string, std::string>	_HeaderMap;

private:
	virtual int		AnalysePath(const char *iUrl, char **oHost, unsigned short *oPort, char **oPath, char** oCredential) = 0;
	virtual int		Authenticate(const char *iUrl, int iHttpRC, char *iResponse, size_t iLen) = 0;



	int				HttpSendData( const char *iVerb, const char *iWhatToGet, int iFlags, const char* iToSend, size_t iLen, CATHTTPType iContentType, int *oConnection,
		char **oResponseBuffer, int *oResponseLen, CATSysHttpStreamer *iStreamer = nullptr);
};
#pragma warning( pop )


#endif
