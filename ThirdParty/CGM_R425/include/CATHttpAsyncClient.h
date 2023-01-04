//*===========================================================================*
//* COPYRIGHT DASSAULT SYSTEMES 1996                                          *
//*===========================================================================*
//*                                                                           *
//*  CATHttp                                                                  *
//*                                                                           *
//*  Usage Notes:  Client Http V1.1                                           *
//*===========================================================================*
//*  Creation January 2011                                                    *
//*===========================================================================*

#ifndef CATHttpAsyncClient_H
#define CATHttpAsyncClient_H
#include <stdlib.h>
#include <memory.h>
#include "CATSysDataType.h"
#include "CATHttpFlags.h"
#include "CATHttp.h"
#include "CATThrLibraryManager.h"

#include "CATHttpAsyncObject.h"



// Return codes
// < 0 implies an internal system of the client
// >=0 implies a success of the request but the returned code is the http 
// return code of the corresponding request.
#define INVALID_ARGS			-1
#define CONNECT_ERROR			-2
#define UNKNOWN_HOST			-3
#define INTERNAL_ERROR			-4
#define CONNECTION_LOST			-5
#define NO_CONNECTION			-6
#define BADFORMATED_RESPONSE	-7
#define NODATA					-8
#define NO_MEMORY				-9
#define SIZE_OVERFLOW			-10
#define SUCCESS_CODE			0

#define CATHTTP_HEADER_ALLOW	"Allow: "


typedef enum tagTypeFormat
{	
	URLENCODED	= 0,
	HTML		= 1,
	TEXT		= 2,
	XML         = 3,
	XMLUTF8     = 4,
	OCTETSTREAM	= 5,
	HTTPNOTHING	= 6,
	HTTPDEFINED = 7
}  CATHTTPType;

class CATHttpDriver;
class CATSysHttpStreamer;
class DSYSysHTTPCommunication;

class ExportedByJS0HTTP CATHttpAsyncClient
{
	friend class DSYSysHTTPCommunication;

public:
	CATHttpAsyncClient(const char* iUserAgent = NULL, short iMajor = 1, short iMinor = 1, bool iAsyncMode = true);
	/* DO NOT USE
		Consturctor only for licencing
	*/
	CATHttpAsyncClient(const char *iDriver, const char *iUserAgent, short iMajor, short iMinor, bool iAsyncMode = true);
	CATHttpAsyncClient(void* sslDriver, bool iAsyncMode = true);

	/* DO NOT USE
		Consturctor only for DSYSysHttpCommunication
	*/
/*	CATHttpAsyncClient(unsigned int iDriverID, const char *iUserAgent, short iMajor, short iMinor, bool iAsyncMode);*/

	virtual	~CATHttpAsyncClient();
	virtual int	SetAsycObject(CATHttpAsyncObject *iAsyncObj); //do not use because error in naming use : SetAsyncObject (will be deleted ASAP)
	virtual int	SetAsyncObject(CATHttpAsyncObject *iAsyncObj);
	virtual int Connect(const char *iHostName, unsigned short iPort = 80, int iFlags = 0);
	virtual int Connection(const char *iURL);

/*
** XXXXXX   XXXXXX    XXXXX   XXX XXX  XX    XX
**  XX  XX   XX  XX  XX   XX   XX XX    XX  XX
**  XX  XX   XX  XX  XX   XX    XXX      XXXX
**  XXXXX    XXXXX   XX   XX     X        XX
**  XX       XX XX   XX   XX    XXX       XX
**  XX       XX  XX  XX   XX   XX XX      XX
** XXXX     XXX  XX   XXXXX   XXX XXX    XXXX


**  XXXXXX   XX  XX  XXXXXX   XXXXXX    XXXXX   XXXXXX    XXXXXX  XXXXXXX  XXXXXX
** XX    X   XX  XX   XX  XX   XX  XX  XX   XX   XX  XX   X XX X   XX   X   XX  XX
** XX        XX  XX   XX  XX   XX  XX  XX   XX   XX  XX     XX     XX X     XX  XX
**  XXXXX    XX  XX   XXXXX    XXXXX   XX   XX   XXXXX      XX     XXXX     XX  XX
**      XX   XX  XX   XX       XX      XX   XX   XX XX      XX     XX X     XX  XX
** X    XX   XX  XX   XX       XX      XX   XX   XX  XX     XX     XX   X   XX  XX
** XXXXXX     XXXX   XXXX     XXXX      XXXXX   XXX  XX    XXXX   XXXXXXX  XXXXXX
*/

/*
** XXXXXX   XXXXXX    XXXXX   XXX XXX  XX    XX
**  XX  XX   XX  XX  XX   XX   XX XX    XX  XX
**  XX  XX   XX  XX  XX   XX    XXX      XXXX
**  XXXXX    XXXXX   XX   XX     X        XX
**  XX       XX XX   XX   XX    XXX       XX
**  XX       XX  XX  XX   XX   XX XX      XX
** XXXX     XXX  XX   XXXXX   XXX XXX    XXXX


**  XXXXXX   XX  XX  XXXXXX   XXXXXX    XXXXX   XXXXXX    XXXXXX  XXXXXXX  XXXXXX
** XX    X   XX  XX   XX  XX   XX  XX  XX   XX   XX  XX   X XX X   XX   X   XX  XX
** XX        XX  XX   XX  XX   XX  XX  XX   XX   XX  XX     XX     XX X     XX  XX
**  XXXXX    XX  XX   XXXXX    XXXXX   XX   XX   XXXXX      XX     XXXX     XX  XX
**      XX   XX  XX   XX       XX      XX   XX   XX XX      XX     XX X     XX  XX
** X    XX   XX  XX   XX       XX      XX   XX   XX  XX     XX     XX   X   XX  XX
** XXXXXX     XXXX   XXXX     XXXX      XXXXX   XXX  XX    XXXX   XXXXXXX  XXXXXX
*/

	virtual int Get(const char *iWhatToGet, int iKeepConnection, char **oBufferPointer, int *oReceivedLen, int *oConnectionChanged = NULL);
	virtual int Get(const char *iWhatToGet, int iKeepConnection, int *oConnectionChanged = NULL);

	virtual int GetSegment(const char *iWhatToGet, int iKeepConnection, int iPos, off_t iOffset, size_t iLen, char **oResponseBuffer, int *oResponseLen, int *oConnectionChanged);
	virtual int GetSegment(const char *iWhatToGet, int iKeepConnection, int iPos, off_t iOffset, size_t iLen, int *oConnectionChanged = NULL); //For FullAsync

	virtual int Post(const char *iWhatToGet, int iKeepConnection, const char* iToPost, size_t iLen, CATHTTPType iContentType, int *oConnectionChanged, char **oResponse, int *oResponseLen);
	virtual int Post(const char *iWhatToGet, int iKeepConnection, const char* iToPost, size_t iLen, CATHTTPType iContentType, int *oConnectionChanged);
	virtual int Post(const char *iWhatToGet, int iKeepConnection, CATHTTPType iContentType, int *oConnectionChanged = NULL); //For FullAsync

	virtual int Post(const char *iWhatToGet, int iKeepConnection, CATHTTPType iContentType, CATSysHttpStreamer *iStreamer, int *oConnectionChanged, char **oResponse, int *oResponseLen);
	virtual int Post(const char *iWhatToGet, int iKeepConnection, CATHTTPType iContentType, CATSysHttpStreamer *iStreamer, int *oConnectionChanged);

	virtual int Put(const char * iWhere, int iKeepConnection, const char *iBuffer, size_t iLen, CATHTTPType iContentType, int *oConnectionChanged, char **oResponse = NULL, int *oResponseLen = NULL);
	virtual int Put(const char * iWhere, int iKeepConnection, CATHTTPType iContentType, int *oConnectionChanged = NULL); //For FullAsync

	virtual int Patch(const char * iWhere, int iKeepConnection, const char *iBuffer, size_t iLen, CATHTTPType iContentType, int *oConnectionChanged, char **oResponse = NULL, int *oResponseLen = NULL);
	virtual int Patch(const char * iWhere, int iKeepConnection, CATHTTPType iContentType, int *oConnectionChanged = NULL); //For FullAsync

	virtual int Head(const char* iInfo, CATFileInfo* info); //, int iFlags = 0);
	virtual int Head(const char* iUrl); // , int iFlags = 0); //For FullAsync
	virtual int Head64(const char* iInfo, CATFileInfo64* info); // , int iFlags = 0);
	virtual int Head64(const char* iUrl); // , int iFlags = 0); //For FullAsync

	virtual	int Options(const char *iWhatToGet, int iKeepConnection); //For FullAsync or sync

	virtual int Delete(const char *iWhatToDel, int iKeepConnection, char **oBufferPointer, int *oReceivedLen, int *oConnectionChanged = NULL);
	virtual int Delete(const char *iWhatToDel, int iKeepConnection, int *oConnectionChanged = NULL); //For FullAsync

	virtual int Link(const char *iWhatToLink, int iKeepConnection, char **oBufferPointer, int *oReceivedLen, int *oConnectionChanged = NULL);
	virtual int Link(const char *iWhatToLink, int iKeepConnection, int *oConnectionChanged = NULL); //For FullAsync

	HRESULT		Cancel();

/*
** XX   XX   XXXXX          XXXXXX   XXXXXX    XXXXX   XXX XXX  XX    XX
** XXX  XX  XX   XX          XX  XX   XX  XX  XX   XX   XX XX    XX  XX
** XXXX XX  XX   XX          XX  XX   XX  XX  XX   XX    XXX      XXXX
** XX XXXX  XX   XX          XXXXX    XXXXX   XX   XX     X        XX
** XX  XXX  XX   XX          XX       XX XX   XX   XX    XXX       XX
** XX   XX  XX   XX          XX       XX  XX  XX   XX   XX XX      XX
** XX   XX   XXXXX          XXXX     XXX  XX   XXXXX   XXX XXX    XXXX

**  XXXXXX   XX  XX  XXXXXX   XXXXXX    XXXXX   XXXXXX    XXXXXX
** XX    X   XX  XX   XX  XX   XX  XX  XX   XX   XX  XX   X XX X
** XX        XX  XX   XX  XX   XX  XX  XX   XX   XX  XX     XX
**  XXXXX    XX  XX   XXXXX    XXXXX   XX   XX   XXXXX      XX
**      XX   XX  XX   XX       XX      XX   XX   XX XX      XX
** X    XX   XX  XX   XX       XX      XX   XX   XX  XX     XX
** XXXXXX     XXXX   XXXX     XXXX      XXXXX   XXX  XX    XXXX
*/

	/**
	* Opens a Http request.
	* <br><b>Role</b>:  Open a http request that will be send to a server.
	* @param iVerb [in]
	*	The Http command to issue.
	* @param iRequestedObject [in]
	*      The URL of the ressource.
	* @param iFlags [in]
	*	<b>Legal values</b>:
	*	<br><tt> CATHTTP_KEEP_CONNECTION :</tt> To keep the connection with
	*						the server.
	* @param iAccept [in]
	*	The type of accepted object.
	* @return
	*	0 on succes, negative otherwise.
	*/
	virtual int OpenRequest(const char *iVerb, const char *iRequestedObject, DWORD iFlags, const char **iAccept = NULL);

	/**
	* Adds headers to a request.
	* <br><b>Role</b>:  Adds header(s) to a http request that has been previously
	* created with @href #OpenRequest.
	* @param iHeader [in]
	*	The header to be added.
	* @param iFlags [in]
	* @return
	*/
	virtual int AddRequestHeaders(const char *iHeader, DWORD iFlags = CATHTTP_REQ_COALESCE);

	/**
	* Sends a http request.
	* <br><b>Role</b>:  Sends a http request that has been previously
	* created with @href #OpenRequest.
	* @param iBuffer [in]
	*	pointer to a buffer containing any optional data to be sent after the
	*	the request headers generaly for PUT or POST commands.
	* @param iLength [in]
	*	size of the optional datas.
	* @return
	*/
	virtual int SendRequest(const char *iBuffer = NULL, size_t iLength = 0);

	/**
	* Sends the data of a http request.
	* <br><b>Role</b>:  Sends a the data of a http request that has been 
	* previously  created with @href #OpenRequest, and with a send sequence 
	* initialized by  @href #BeginSendRequest
	* The data will be sent by the caller on demand, if the transfert has been
	* declared as chunked, the method can be call many times, and each iBuffer
	* will correspond to a separate chunk. The last chunk of 0 size must not
	* be send with this method. The  @href #CloseRequest will do the work.
	* @param iBuffer [in]
	*	pointer to a buffer containing data to be sent.
	* @param iLength [in]
	*	size of the optional datas.
	* @return
	*/
	virtual int SendRawData(const char* iBuffer, size_t iLen);

	/**
	* Close a Http request.
	* <br><b>Role</b>: Close a http request that will be send to a server.
	* This call is only necessary when the data have been sent to the server with
	* @href #SendRawData.
	* @return
	*	0 on succes, negative otherwise.
	*/
	virtual int CloseRequest(); 


	/**
	* Retrieves the response headers.
	* <br><b>Role</b>: Retrieves the response headers sent by the server after a 
	* call to @href #SendRequest.
	* @param oHeader [out]
	*	pointer that will be allocated to hold the header(s).
	* @param oLen [out]
	*	length of the allocated buffer.
	* @param ioNext [in/out]
	*	initialized to 0, will be increased if multiple header have the same key
	* @param iFlags
	*	Type of header to be retrieved.
	* @param iHeader
	*      the Header to be retrieved if used with iFlags=CATHTTP_QUERY_CUSTOM
	* @return
	*/
	virtual int GetResponseHeaders(char **oHeader, size_t* oLen,size_t *ioNext, DWORD iFlags = CATHTTP_QUERY_ALL, const char* iHeader = NULL);


	/**
	* Download the resource on demand
	* <br><b>Role</b>: Download the body of the response chunk per chunk. Even if
	* this method can be used to download a body in a single call, it only makes 
	* sense to used it, if the response is returned in chunked mode. In this
	* case it is possible to retrieve the body on demand chunk per chunk, until
	* oLenResponse becomes Null and NoMoreData becomes true.
	* @param iMode
	*        CATHTTP_CHUNK_PER_CHUNK to indicate a download chunk per chunk
	*        in all other case the method behaves like @href #Download
	* @param oLenResponse [out]
	*	length of the allocated buffer.
	* @param oBody [out]
	*	pointer that will be allocated to hold the body of the response.
	* @param oNoMoreData [out]
	*      to indicate if there is some more data to download.
	* @return
	*/
	virtual int DownloadEx(int iMode, size_t *oLenResponse, char **oBody, int *oNoMoreData);



	virtual int GetOptions(DWORD iOption, void *oBuffer, size_t *ioLen);
	virtual int SetOptions(DWORD iOption, const void *iBuffer, size_t iLen);

	//UnSupported because dangeous usage for memory
	virtual int	Download(size_t *oLenResponse, char **oBody);

protected:
	virtual void		DRIVERSWITCH(const char *iWhatToGet);
	CATHttpDriver		*_Data;
	CATHttpAsyncObject	*_AsyncObj;
	ULONG				_Is_Keep_Error_Body;
	bool				_DontSwitchDriver;
//	std::atomic_uint	_DriverID;

private:
	static int	GetLoadExternHttpDriver(const char *iDriver);
	void		ExecuteBuildHttpDriver(const char *iUserAgent, short iMajor, short iMinor);
	void		Init(const char *iUserAgent, short iMajor, short iMinor, bool iAsyncMode);
};

#endif
