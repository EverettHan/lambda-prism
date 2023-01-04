//*===========================================================================*
//* COPYRIGHT DASSAULT SYSTEMES 1996                                          *
//*===========================================================================*
//*                                                                           *
//*  CATHttp                                                                  *
//*                                                                           *
//*  Usage Notes:  Client Http V1.0                                           *
//*===========================================================================*
//*  Creation decembre 97                                                     *
//*===========================================================================*
#ifndef CATHTTPCLIENT_H
#define CATHTTPCLIENT_H
#include "CATHttpAsyncClient.h"
#include "CATHttp.h"



class SSLSessionCache {
public:
	SSLSessionCache() { sslContext = NULL; sslSession = NULL;}
	virtual ~SSLSessionCache() { sslContext = NULL; sslSession = NULL;}
	virtual void Lock() = 0;
	virtual void Unlock() = 0;
	void* sslContext;
	void* sslSession;
};


class CATSysHttpStreamer;
class ExportedByJS0HTTP CATHttpClient : public  CATHttpAsyncClient
{
public:
	/* Construtor: Construtor to be used by default
	   Parameters:
			const char *iUserAgent:
					Default value: By default this parameter is set to NULL and so the default user agent will be the value of the define WUSERAGENT ("CATIA  HTTP  CLIENT  v2.1-DS")
					value: the value of iUserAgent will be used to set the name of the current http communication user agent
			short iMajor:
					Default value: By default this value is set to 1.
					value: The value iMajor will be used to set the major version of http (exemple: if the value is 2, it will set the http version to: 2.1)
			short iMinor:
					Default value: By default this value is set to 1.
					value: The value iMinor will be used to set the minor version of http (exemple: if the value is 2, it will set the http version to: 1.2)
	   return: NONE
	   */
	CATHttpClient(const char *iUserAgent = NULL, short iMajor = 1, short iMinor = 1);
	/* DO NOT USE
		Consturctor only for licencing
	*/
	CATHttpClient(void* sslDriver);
	CATHttpClient(const char*iDriver, const char *iUserAgent, short iMajor = 1, short iMinor = 1);

	/* DO NOT USE
		Consturctor only for DSYSysHttpCommunication
	*/
/*	CATHttpClient(unsigned int iDriverID, const char *iUserAgent, short iMajor, short iMinor);*/


	virtual ~CATHttpClient();
	int Connect(const char *iHostName, unsigned short iPort = 80, int iFlags = 0) override;



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
	int Get(const char *iWhatToGet, int iKeepConnection, char **oBufferPointer, int *oReceivedLen, int *oConnectionChanged = NULL) override;
	int GetSegment(const char *iWhatToGet, int iKeepConnection, int iPos, off_t iOffset, size_t iLen, char **oBufferPointer, int *oReceivedLen, int *oConnectionChanged = NULL) override;
	int Head(const char *iInfo, CATFileInfo *info) override;
	int Head64(const char *iInfo, CATFileInfo64 *info) override;
//	int Head(const char *iInfo, CATFileInfo *info, int iFlags = 0) override;
//	int Head64(const char *iInfo, CATFileInfo64 *info, int iFlags = 0) override;
	int Delete(const char *iWhatToDel, int iKeepConnection, char **oBufferPointer, int *oReceivedLen, int *oConnectionChanged = NULL) override;
	int Link(const char *iWhatToLink, int iKeepConnection, char **oBufferPointer, int *oReceivedLen, int *oConnectionChanged = NULL) override;
	int Options(const char *iWhatToGet, int iKeepConnection) override;

	int Post(const char *iWhatToGet, int iKeepConnection, const char* iToPost, size_t iLen, CATHTTPType iContentType, int *oConnectionChanged, char **oResponse, int *oResponseLen) override;
	int Post(const char *iWhatToGet, int iKeepConnection, CATHTTPType iContentType, CATSysHttpStreamer *iStreamer, int *oConnectionChanged, char **oResponse, int *oResponseLen) override;
	int Put(const char *iWhere, int iKeepConnection, const char *iBuffer, size_t iLen, CATHTTPType iContentType, int *oConnectionChanged, char **oResponse = NULL, int *oResponseLen = NULL) override;
	int Patch(const char * iWhere, int iKeepConnection, const char *iBuffer, size_t iLen, CATHTTPType iContentType, int *oConnectionChanged, char **oResponse = NULL, int *oResponseLen = NULL) override;

	int GetType();

	//Return a char * that cannot be deleted or freed by caller
	char *GetLastRedirectUrl();

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
	int OpenRequest(const char *iVerb, const char *iRequestedObject,
		DWORD iFlags, const char **iAccept = NULL) override; 

	/**
	* Adds headers to a request.
	* <br><b>Role</b>:  Adds header(s) to a http request that has been previously
	* created with @href #OpenRequest.
	* @param iHeader [in]
	*	The header to be added.
	* @param iFlags [in]
	* @return
	*/
	int AddRequestHeaders(const char *iHeader, 
		DWORD iFlags = CATHTTP_REQ_COALESCE) override;

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
	int SendRequest(const char *iBuffer = NULL, size_t iLength = 0) override;

	/**
	* Sends a http request.
	* <br><b>Role</b>:  Sends a http request that has been previously
	* created with @href #OpenRequest.
	* @param iStreamer [in]
	* @return
	*/
	int SendRequest(CATSysHttpStreamer *iStreamer);

	/**
	* Sends a http request without the data.
	* <br><b>Role</b>:  Sends a http request that has been previously
	* created with @href #OpenRequest, but without any data at the moment. 
	* The data will be sent by the caller on demand with @href #SendRawData
	* and the sequence is terminated by a @href #CloseRequest
	* @param iFlag [in]
	*	<b>Legal values</b>:
	*	<br><tt> CATHTTP_CHUNK :</tt> to announce a chunked transfert
	*	<br><tt> CATHTTP_NORMAL_SEND :</tt> to announce a classical transfert
	* @param iLength [in]
	*	The length of data to be sent in case of classical transfert.
	*      The value is ignored if iFlag=CATHTTP_CHUNK
	* @return
	*/
	int BeginSendRequest(int iFlag,  size_t iLength = 0);


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
	int SendRawData(const char* iBuffer, size_t iLen) override;

	/**
	* Close a Http request.
	* <br><b>Role</b>: Close a http request that will be send to a server.
	* This call is only necessary when the data have been sent to the server with
	* @href #SendRawData.
	* @return
	*	0 on succes, negative otherwise.
	*/
	int CloseRequest() override; 


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
	int GetResponseHeaders(char **oHeader, size_t* oLen, size_t *ioNext, DWORD iFlags = CATHTTP_QUERY_ALL, const char* iHeader = NULL) override;

	/**
	* Download the resource.
	* <br><b>Role</b>: Download the body of the response.
	* @param oLenResponse [out]
	*	length of the allocated buffer.
	* @param oBody [out]
	*	pointer that will be allocated to hold the body of the response.
	* @return
	*/
	int Download(size_t *oLenResponse, char **oBody) override;

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
	int DownloadEx(int iMode, size_t *oLenResponse, char **oBody, 
		int *oNoMoreData) override;



	int GetOptions(DWORD iOption, void *oBuffer, size_t *ioLen) override;
	int SetOptions(DWORD iOption, const void *iBuffer, size_t iLen) override;
};


#endif
