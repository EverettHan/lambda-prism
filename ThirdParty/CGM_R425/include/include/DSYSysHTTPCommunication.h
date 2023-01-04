#ifndef DSYSysHTTPCommunication_H
#define DSYSysHTTPCommunication_H

#include "CATSysDataType.h"
#include "CATSysErrorDef.h"
#include "CATHttp.h"
#include "CATHttpAsyncClient.h"
#include "CATHttpClient.h"
#include "DSYString.h"
#include "DSYSysTSDico.h"
#include "DSYSysFileLogging.h"
#include "CATHttpFlags.h"
#include "DSYSysRefCounter.h"
#include "DSYSysTimer.h"
#include "CATSysTSTime.h"
#include "DSYSysHTTPPerfInfoCB.h"
#include <mutex>

//SIP: Warning this should be #ifdef but to keep compatibility we invert
#ifdef _ENDIAN_LITTLE
#define ENDIANToNetWork16(A) (A)
#define ENDIANToNetWork32(A) (A)
#define ENDIANToNetWork64(A) (A)
#else
#define ENDIANToNetWork16(A) (((A & 0xFF00) >> 8) | ((A & 0x00FF) << 8))
#define ENDIANToNetWork32(A) ((((CATULONG32) A >> 24) & 0x000000FF) | (((CATULONG32) A >> 8) & 0x0000FF00) | (((CATULONG32) A << 8) & 0x00FF0000) | (((CATULONG32) A << 24) & 0xFF000000))
#define ENDIANToNetWork64(A) ((((CATULONG64) A >> 56) & 0x00000000000000FF) | (((CATULONG64) A >> 40) & 0x000000000000FF00) | (((CATULONG64) A >> 24) & 0x0000000000FF0000) | (((CATULONG64) A >> 8) & 0x00000000FF000000) | (((CATULONG64) A << 8) & 0x000000FF00000000) | (((CATULONG64) A << 24) & 0x0000FF0000000000) | (((CATULONG64) A << 40) & 0x00FF000000000000) | (((CATULONG64) A << 56) & 0xFF00000000000000))
#endif

#define SIDLCHUNKEDSTR "SidlChunked"

#define SIDL_DEFAULT_START_STREAM_BUFF_SIZE	256000

//SIP: to be removed after EPB supress code in rel
#define MV_RELEASE_IN_SYSTEMTS

typedef struct
{
	unsigned int	HeaderSize;
	unsigned int	DataSize;
	int				Version;
	int				NumPacket;
	unsigned int	IsCompressed;
	unsigned int	RealDataSize;
	unsigned int	OptionsSize;
	int				PingThreadTimer;
} SidlPacketHeader;


//Structure for send callback
typedef struct DSYSysAsyncSendInfo_s
{
	HRESULT			ErrorCode;
	CATULONG64		CallBackStatusMode;
	CATULONG64		CurrentTotalDataSent; //SizeAllreadySend
	CATULONG64		TotalDataToSend; //CurrentTotalToSendLen
	CATULONG64		CurrentDataSize; //CurrentSendLen
	char			*Data;
	bool			IsChunk;
} DSYSysAsyncSendInfo;

//Structure for receive callback
typedef struct DSYSysAsyncReceiveInfo_s
{
	HRESULT		ErrorCode;
	CATULONG64	CallBackStatusMode;
	CATULONG64	CurrentTotalToReceive;
	CATULONG64	CurrentDataSize;
	char		*Data;
	CATULONG64	SizeAlreadyReceive;
	bool		IsChunk;
	CATULONG64	PartNumOfMultipart;
	char		*MultipartCurrentContentType;
} DSYSysAsyncReceiveInfo;


//Object to be implemented to use DYSSysHTTPCommunication in async mode
#pragma warning( push )
#pragma warning( disable : 4275 )
class DSYSysAsyncObject : public DSYSysRefCounter
{
public:
	DSYSysAsyncObject()
	{
		_msgCatalog = "";
		_msgId = "";
		_IsWebLoginNeeded = false;
		_IsProviderConnectNeeded = false;
	};
	virtual ~DSYSysAsyncObject()
	{
	};
	virtual bool IsChunkSend() { return false; };
	virtual bool IsSendCallBackCapable() { return false; };
	virtual bool IsRewindCapable() { return false; };
	virtual HRESULT Rewind() { return E_NOTIMPL; };
	virtual HRESULT SendCallBack(CATULONG64 iSteps, DSYSysAsyncSendInfo* iInfo) = 0;
	virtual HRESULT ReceiveCallBack(CATULONG64 iSteps, DSYSysAsyncReceiveInfo* iInfo) = 0;

	CATUnicodeString		_msgCatalog;
	CATUnicodeString		_msgId;

protected:
	bool					_IsWebLoginNeeded;
	bool					_IsProviderConnectNeeded;
};
#pragma warning( pop )


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////// DEPRECATED ////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////// DO NOT USE ////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT ExportedByJS0HTTP DSYSysHTTPCommuncationGetError(CATUnicodeString &oMsgCatalog, CATUnicodeString &oMsgId, bool &oIsWebLoginNeeded, bool &oIsProviderConnectNeeded);
//HRESULT DSYSysHTTPCommuncationSetError(CATUnicodeString &iMsgCatalog, CATUnicodeString &iMsgId, bool iIsWebLoginNeeded, bool iIsProviderConnectNeeded);



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////// Internal implementation of callback for CATHttpAsyncClient //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DSYSysHTTPCommunication;

class CATHttpCommunicationAsyncObject : public CATHttpAsyncObject
{
public:
	CATHttpCommunicationAsyncObject(DSYSysAsyncObject *iHttpCommunicationAsyncObj, DSYSysHTTPCommunication *iDSYSysHTTPCommunication);
	~CATHttpCommunicationAsyncObject();
	bool IsChunkSend()
	{
		if (_HttpCommunicationAsyncObj)
			return _HttpCommunicationAsyncObj->IsChunkSend();
		return false;
	};
	bool IsSendCallBackCapable()
	{
		if (_HttpCommunicationAsyncObj)
			return _HttpCommunicationAsyncObj->IsSendCallBackCapable();
		return false;
	};
	bool IsRewindCapable()
	{
		if (_HttpCommunicationAsyncObj)
			return _HttpCommunicationAsyncObj->IsRewindCapable();
		return false;
	};
	HRESULT Rewind()
	{
		if (_HttpCommunicationAsyncObj)
			_HttpCommunicationAsyncObj->Rewind();
		return E_NOTIMPL;
	};
	HRESULT SendCallBack(int iSteps, CATHttpAsyncSendInfo* iInfo);
	HRESULT ReceiveCallBack(int iSteps, CATHttpAsyncReceiveInfo* iInfo);

protected:
	DSYSysAsyncObject		*_HttpCommunicationAsyncObj;
	DSYSysHTTPCommunication	*_DSYSysHTTPCommunication;
	unsigned int			_first;
	void					*_MyHttpTrace;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////// Internal implementation of callback for CATHttpAsyncClient //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





//Define to specify the mode of the client: Synchrone or Async
#define DSYSysHTTPCommunication_Sync	0
#define DSYSysHTTPCommunication_Async	1
#define DSYSysHTTPCommunication_File	2

#pragma warning( push )
#pragma warning( disable : 4275 )
class ExportedByJS0HTTP DSYSysHTTPCommunication : public DSYSysRefCounter
{
  friend class CATHttpCommunicationAsyncObject;
public:
	DSYSysHTTPCommunication(CATULONG64 iMod = DSYSysHTTPCommunication_Async);
	~DSYSysHTTPCommunication();
	static HRESULT	SetBackupSIDLServerUrl(char *iUrl);
	static char*	GetBackupSIDLServerUrl();
	HRESULT	SetUrl(CATUnicodeString &iUrl);
	HRESULT	SetUrl(const char *iUrl);
	HRESULT	SetMethod(CATUnicodeString &iMethod);
	HRESULT	SetMethod(const char *iMethod);
	HRESULT SetUserAgent(CATUnicodeString iUserAgent);
	HRESULT SetOptions(DWORD iOption, const void *iBuffer, size_t iLen);
	HRESULT SetConnectionParameters(DSYSysTSDico *iHashTable); //For SIDL compatibility
	HRESULT SetSIDLMode(bool iIsSIDL); //For SIDL compatibility
	bool	IsSIDLMode(); //For SIDL compatibility
	HRESULT GetOptions(DWORD iOption, void *oBuffer, size_t *ioLen);
	HRESULT BeginRequest();
	HRESULT EndRequest();
	HRESULT SetAsyncObject(DSYSysAsyncObject *iAsyncObj);
	HRESULT SetAsycObject(DSYSysAsyncObject *iAsyncObj);
	HRESULT Write(const void *iData, CATULONG64 iDataSize); //in future: for sync mode
	HRESULT WritePartOfMultyPart(const void *iData, CATULONG64 iDataSize, const char *iContentEncoding); //in future: for sync mode
	HRESULT	WriteFile(const void *iData, CATULONG64 iDataSize);
	HRESULT WriteInt(int iVal); //in future: for sync mode
	HRESULT WriteInt64(CATULONG64 iVal); //in future: for sync mode
	HRESULT WriteDouble(double iVal);
	HRESULT WriteString(const CATUnicodeString &iStrVal); //in future: for sync mode
	HRESULT Read(char *iData, CATULONG64 &ioDataSize);
	HRESULT Read(char **oData, CATULONG64 &ioDataSize); //for sync mode
	HRESULT ReadPartOfMultyPart(char **iData, CATULONG64 iDataSize, const char **oContentEncoding); //in future: for sync mode
	HRESULT ReadInt(int &oVal);
	HRESULT ReadInt64(CATULONG64 &oVal);
	HRESULT ReadDouble(double &oVal);
	HRESULT ReadString(CATUnicodeString &oStrVal);
	HRESULT Cancel();
	HRESULT Ping(CATULONG64 iNbPing, CATULONG64 &oPacketLoss, CATULONG64 &oLatency);
	HRESULT Timeout(CATULONG64 &oTimeoutValue);
	HRESULT Download(CATULONG64 iLatency, CATULONG64 &oDownload);
	HRESULT Upload(CATULONG64 iLatency, CATULONG64 &oUpload);
	HRESULT NetworkTest(CATULONG64 iTestNumber);
	HRESULT	AddRequestHeaders(const char *iHeader, DWORD iFlags=CATHTTP_REQ_COALESCE);
	HRESULT	GetResponseHeaders(char **oHeader, size_t* oLen,size_t *ioNext, DWORD iFlags = CATHTTP_QUERY_ALL, const char* iHeader = NULL);
	HRESULT	PurgePreviousHttpClient(CATHttpAsyncClient *iHttpClient);
	HRESULT GetError(CATUnicodeString &oMsgCatalog, CATUnicodeString &oMsgId, bool &oIsWebLoginNeeded, bool &oIsProviderConnectNeeded);

protected:
	HRESULT			AddSecurityTokenHeaders(CATHttpAsyncClient *iHttpClient);
	HRESULT			AddDefaultHeaders(CATHttpAsyncClient *iHttpClient);
	HRESULT			AddSidlHeaders(CATHttpAsyncClient *iHttpClient);
	HRESULT			InternalEndRequest();
	HRESULT			ReleaseHttpClient();
	HRESULT			GetRequestStatus(HRESULT iHr, int iHttpStatus, bool IsSIDLAnswer);
	HRESULT			CheckResponseHeader();
	HRESULT			HasPassPortlHeader();
	HRESULT			HasXSidlHeader();
	HRESULT			CreateHeader(char *iSrc, int iLen);
	HRESULT			StartRequest(CATHttpAsyncClient *iHttpClient, CATUnicodeString iUrl, const char *iData, int iDataLen, int SendNonChunk);
	HRESULT			DecorateAndSendAChunk(int LastChunk);
// XXXXXX   XXXXX   XXXXXX    XXXXX              XXXX   XX   XX  XXXXXX    XXXXX   XXXXXX    XXXXXX     XX    XX   XX   XXXXXX
// X XX X  XX   XX   XX  XX  XX   XX              XX    XXX XXX   XX  XX  XX   XX   XX  XX   X XX X    XXXX   XXX  XX   X XX X
//   XX    XX   XX   XX  XX  XX   XX              XX    XXXXXXX   XX  XX  XX   XX   XX  XX     XX     XX  XX  XXXX XX     XX
//   XX    XX   XX   XX  XX  XX   XX              XX    XX X XX   XXXXX   XX   XX   XXXXX      XX     XX  XX  XX XXXX     XX
//   XX    XX   XX   XX  XX  XX   XX              XX    XX   XX   XX      XX   XX   XX XX      XX     XXXXXX  XX  XXX     XX
//   XX    XX   XX   XX  XX  XX   XX              XX    XX   XX   XX      XX   XX   XX  XX     XX     XX  XX  XX   XX     XX
//  XXXX    XXXXX   XXXXXX    XXXXX              XXXX   XX   XX  XXXX      XXXXX   XXX  XX    XXXX    XX  XX  XX   XX    XXXX
	/* faire un setoption sur le client HTTP pour supporter les -XXX en = 0, donc erreur HTTP dans la thread en async et dans read si sync*/
	HRESULT			SendAChunk(const char *iSrc, int iLen, int LastChunk);
	HRESULT			compress(char* src, int size, char** cdst, unsigned int* sizedst, size_t *clen);
	HRESULT			uncompress(const char* srcZ, size_t sizeZ, size_t size, char** dsrc);
	HRESULT			GetHttpClient(CATHttpAsyncClient *&oHttpClient);
	HRESULT			GetCurHttpClient(CATHttpAsyncClient *&oHttpClient);

	HRESULT			InitSidl();
	HRESULT			ReceiveFirstPacket();
	HRESULT			TryRealloc(unsigned int TotalSize);
	HRESULT			ReceiveNextChunk();
	unsigned int	GetPacketCtrlSize();
	bool			IsPacketHeaderInBuffer();
	bool			IsPacketInBuffer();
	HRESULT			StoreHeader();
	HRESULT			ReceiveFullPacket();
	HRESULT			StoreAllPacketFromBuffer();
	HRESULT			StoreNextPacketFromBuffer();
	HRESULT			StoreData(char *Data);
	HRESULT			ReadSidl(char *iData, CATULONG64 &ioDataSize);
	HRESULT			SetError(CATUnicodeString &iMsgCatalog, CATUnicodeString &iMsgId);

	void					*_MyHttpTrace;
	HRESULT					_SidlError;

	__int64					_WriteElpTime;
	DSYSysTimer				_WriteElaps;
	std::mutex				_DSYSysHTTPCommunicationMutexClientRelease;
	CATSysTSTime			_Time;
	DSYSysHTTPPerfInfoCB	*_PerfInfoCB;
	CATUnicodeString		_msgCatalog;
	CATUnicodeString		_msgId;

	static std::atomic_uint	_DriverID;

private:
	CATUnicodeString		_Url;
	CATUnicodeString		_Method;
	CATUnicodeString		_UserAgent;
	CATHttpAsyncClient		*_HttpAsyncClient;
	CATHttpClient			*_HttpClient;
	CATULONG64				_Mode;
	DSYSysAsyncObject		*_AsyncObj;



	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////// FOR SIDL ////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//For file base traces
	DSYSysFileLogging		*_TraceFile;
	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////// FOR SIDL WRITING ////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////

	char*					_Protocol;				//Set to the server name (http, https, ...)
	char*					_SDAM;					//Set to the server name (host:port)
	char*					_SessionId;				//Set to the SessionId value
	char*					_URIPrefix;				//Set to the value of URI Prefix (http://host:port/URIPrefix/...)
	char*					_HttpParams;
	char*					_UserName;				//Session user name for SIDL mode (also for X509 at Dassault Aviation


	//Pointer to the begining of the buffer so to the Header.
	char*									_TheOutputPacket;
	//Size of the Header.
	unsigned int							_TheOutputCtrlSize;
	unsigned int							_Allocated; //Size of the all the buffer (Header + data + empty)
	unsigned int							_MaxPacketSize;			//max size of an SIDL packet
	unsigned int							_MaxServerPacketSize;			//max size of an SIDL packet

	//To manage data in the buffer.
	unsigned int							_Pos; //Actual position in buffer (does not care about header)
	char*									_Data; //pointer to the begining of data 

	//Buffer for compress
	char*									_WorkingBuffer;
	unsigned int							_WorkingBufferSize;
	unsigned int							_CompressionTrigger;	//if packet size is greater than this value the packet is compressed
	int										_IsBufferedMode;
	
	int										_NumChunk; //Chunk number for multiple chunk message

	//Timer for timeout
	int										_PingThreadTimer;
	int										_IsPingOn;

	int										_Invalidated;
	int										_IsLogon;				//0 if not a logon request, other value if in logon mode (used for proxy authentication)
	bool									_IsSIDL;
	bool									_IsSIDLHeaderCreated;
	bool									_Keep_HTTP_Error_Body;

	char									*_ProcessorName;



	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////// FOR SIDL READING ////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////
	char*									_StreamBuff;
	char*									_SavStartStreamBuff;
	char*									_StreamBuffUncompressed;
	unsigned int							_StreamBuffUncompressedSize;
	unsigned int							_StreamBuffUncompressedPos;
	unsigned int							_StreamBuffSize;
	unsigned int							_StreamBuffCurSize;
	SidlPacketHeader						_Header;
	bool									_IsLastChunkReceived;
	bool									_ReceiveFirst;
	bool									_HasDefinedContentType;
	static CATUnicodeString					S_SIDLServerUrl;
	bool									_No_Auth_Check;
	int										_Flags;
};
#pragma warning( pop )



#endif

