#ifndef CATSysHTTPRequest_H
#define CATSysHTTPRequest_H
// COPYRIGHT DASSAULT-SYSTEMES 2003

#include "CATSysErrorDef.h"
#include "CATSysDataType.h"
#include "CATISysSockProtocols.h"
class CATSockets;
class CATSysSHCookie;




enum CATSysSHMethod  { 
  CATSysSHMethNONE = 0,
  CATSysSHMethGET = 1,
  CATSysSHMethPOST= 2,
  CATSysSHMethPUT = 3,
  CATSysSHMethHEAD = 4, // HEAD IS NOT RECOMMENDED IN SUB HTTP PROTOCOL
                       // IT IS SUPPORTED SERVER SIDE BUT SHOULD NOT BE
                       // USED IN CLIENT                                
  CATSysSHMethOPTION = 5,
  CATSysSHMethAnswer = 6,
  CATSysSHMethDELETE = 7,
  CATSysSHMethPATCH = 8,
  CATSysSHMethLINK = 9,

  CATSysSHMethCONNECT = 10,

  CATSysSHMethMax
};



enum CATSysSHRqHeader  {
  CATSysSHRqHdConnection = 0,
  CATSysSHRqHdAccept = 1,
  CATSysSHRqHdUserAgent = 2,
  CATSysSHRqHdContentType = 3,
  CATSysSHRqHdContentLength = 4,
  CATSysSHRqHdConnectionClose = 5,
  CATSysSHRqHdAllWithoutVerb = 6,
  CATSysSHRqHdAll = 7
};



enum CATSysSHStatus  { 
  CATSysSHStsOK =0           ,
  CATSysSHStsCreated         ,
  CATSysSHStsAccepted        ,
  CATSysSHStsNoContent       ,
  CATSysSHStsMovedPermanently,
  CATSysSHStsMovedTemporarily,
  CATSysSHStsNotModified     ,
  CATSysSHStsBadRequest      ,
  CATSysSHStsUnauthorized    ,
  CATSysSHStsForbidden       ,
  CATSysSHStsNotFound        ,
  CATSysSHStsInternalSrvError,
  CATSysSHStsNotImplemented  ,
  CATSysSHStsBadGateway      ,
  CATSysSHStsSrvcUnavailable ,
  // 203 205-206
  CATSysSHStsNoAuthInformation              ,
  CATSysSHStsResetContent                   ,
  CATSysSHStsPartialContent                 ,
  //300 303  305-307
  CATSysSHStsMultipleChoices                ,
  CATSysSHStsSeeOther                       ,
  CATSysSHStsUseProxy                       ,
  CATSysSHStsNoLongerUsed                   ,
  CATSysSHStsTemporaryRedirect              ,
  //402  405 - 417
  CATSysSHStsPaymentRequired                ,
  CATSysSHStsMethodNotAllowed               ,
  CATSysSHStsNotAcceptable                  ,
  CATSysSHStsProxyAuthenticationRequired    ,
  CATSysSHStsRequestTimeout                 ,
  CATSysSHStsConflict                       ,
  CATSysSHStsGone                           ,
  CATSysSHStsLengthRequired                 ,
  CATSysSHStsPreconditionFailed             ,
  CATSysSHStsRequestEntityTooLarge          ,
  CATSysSHStsRequestURITooLong              ,
  CATSysSHStsUnsupportedMediaType           ,
  CATSysSHStsRequestedRangeNotSatisfiable   ,
  CATSysSHStsExpectationFailed              ,
  // 504-505
  CATSysSHStsGatewayTimeout                 ,
  CATSysSHStsHTTPVersionNotSupported        ,
  // 100-101
  CATSysSHStsContinue                       ,
  CATSysSHStsSwitchingProtocol              ,

  CATSysSHStsMax                   

};



enum CATSysSHPVersion
{
  CATSysSHvers10=10,
  CATSysSHvers11=11
};

// ==================================
// use for multipart requests
// ==================================
enum CATSysSHChunkInfo
{
  CATSysSHChunkNone=0,
  CATSysSHChunkFirstPart,
  CATSysSHChunkIntermediatePart,
  CATSysSHChunkLastPart
};

// Flag for all method with Flags
#define CATSysSHFlgNone              0x00000000

// flags for SetMethod and for  EasyAnswer
#define CATSysSHFlgAnswerToHEAD     0x00000400
#define CATSysSHFlgPotProxyChlg     0x00000800
#define CATSysSHFlgConxClose		0x00001000 


// flags for TransmitContent
#define CATSysSHFlgDoNotForget       0x00000001
#define CATSysSHFlgOnlyIfOwner       0x00000002


// flags for GetURI             
#define CATSysSHFlgRelativeURI       0x00000004
#define CATSysSHFlgAbsoluteURI       0x00000008
#define CATSysSHFlgWithQueries       0x00000010
#define CATSysSHFlgWithNoQueries     0x00000020

// flags for Send  / EasyRequest             
#define CATSysSHFlgDirectSend   0x00000100
#define CATSysSHFlgWaitAnswer   0x00000200

// flags for DebugDump
#define CATSysSHFlgDumpContent  0x10000000
#define CATSysSHFlgDumpAsText   0x20000000

// known limitations of simple HTTP protocol
// URI cannot exceed 2048 characters

#define CATSysSHShrCopy          0x1
#define CATSysSHShrMoveAndReset  0x2
     
// for SetContent method
// CATSysSHSCBecomesBufferOwner : keeps  the address of the buffer internally and becomes owner of it
//                                 may be used only for char * allocated with new char[]
// CATSysSHSCCopy               :  makes a copy of the  buffer 
// CATSysSHSCCopy               : keeps  the address of the buffer internally and is not in charge of the
//                                deletion . Should only use for static or permanent buffers 
#define CATSysSHSCBecomesBufferOwner        0x0
#define CATSysSHSCCopy                      0x1
#define CATSysSHSCGetBufferWithoutOwnership 0x2 
// default specs
// by default the message includes a  RequestHeader  Connection = Keep-Alive;
// by default the message includes  a RequestHeader  UserAgent   

// Flags that may be used with SetCookiesFromString
#define CATSysSHScfsServerSide 0x1

class ExportedByJS0MT CATSysHTTPRequest : public CATISysSockProtocolRq 
{
	public:
		CATSysHTTPRequest();
		CATSysHTTPRequest(CATSysHTTPRequest &, int iShare = CATSysSHShrCopy);
		virtual ~CATSysHTTPRequest();
		virtual const char*		GetProtocolId();
		virtual void			SetSecure(bool iIsHttps) { _IsHttps = iIsHttps; };
		virtual bool			GetSecure() { return _IsHttps; };
		virtual void			SetServer(const char *iServerWithPort) { _ServerWithPort = iServerWithPort; };
		virtual const char *	GetServer() { return _ServerWithPort; };
		// MUST USE  CATSysSHFlgAnswerToHEAD in iSendFlag when  answering to a  
		// HEAD REQUEST
		virtual HRESULT			SetMethod(CATSysSHMethod iKind, int iFlag = 0);
		virtual HRESULT			SetStatus(CATSysSHStatus iCode);
		virtual HRESULT			SetStatusString(const char *iCode);

		virtual HRESULT			SetURI(const char *iURI);
		virtual HRESULT			SetURIQuery(const char *iParm, const char *iParmVal);
		virtual HRESULT			AddToURI(const char *);

		virtual HRESULT			SkipDefaultRqHeader(CATSysSHRqHeader iSkippedRqHeader);
		virtual HRESULT			RestoreDefaultRqHeader(CATSysSHRqHeader iRqHeader);
		virtual HRESULT			SetRqHeader(CATSysSHRqHeader iRqHeader, const char *iParmVal);
		/**
		 * AddRqHeader
		 * @param iszHeaders is a null-terminated string which format is the following: <header>\r\n*
		 *                   ex: "A:B\r\nC:D"  (ending by \r\n may add unwanted bytes at the end of the body).
		 */
		/*virtual: what for? */
		HRESULT					AddRqHeader(const char *iszHeaders);
        /***
         ** for multi-parts chunked requests 
         ***/
		virtual HRESULT			SetChunkInfo(CATSysSHChunkInfo iChunkInf, unsigned short iPartNb = 0);
		virtual HRESULT			GetChunkInfo(CATSysSHChunkInfo *oChunkInf, unsigned short *oPartNb = NULL);
		virtual HRESULT			GetNextChunkSize(size_t *oSize);
		virtual int				GetChunkOffset();// returns the size
		virtual int				IsChunked();
		virtual HRESULT			WaitForNextChunk(CATSockets *iSock, int iTimeoutInMs);
		virtual HRESULT			ReceiveNextChunkInBuffer(void *iBuffer, size_t iBufferSzInByte, CATSockets *iSocket);
		virtual HRESULT			ReceiveNextChunkAsContent(CATSockets *iSocket);
		virtual HRESULT			Receive(CATSockets* iSock, char **iBuffer, size_t iLen, size_t* oLu);
        /***
         ** GetRqHeader permits to obtain request header informations
         **       
         ** ARGUMENTS
         **    iRqHeader : permits to specify which request header value 
         **                is requested
         **     iRqHeader may be any value of type CATSysSHRqHeader except
         **     CATSysSHRqHdContentLength .
         **     Requesting GetRqHeader with iRqHeader will systematically 
         **     return E_FAIL and will not modify the ioRqHdValBuffer     
         **       
         **     ioRqHdValBuffer : output value buffer  of minimal length 
         **                       must be specified with iBufferLen
         **        ioRqHdValBuffer may be passed equal to NULL         
         **        if not null it must have sufficient length to handle 
         **        the value or E_FAIL will be returned
         **       
         **     iBufferLen : length of ioRqHdValBuffer if it is not null  
         **       
         **  RETURN VALUES:     
         **       S_OK : the requested  RqHeader is set on this
         **               CATSysHTTPRequest
         **       
         **       S_FALSE : the requested  RqHeader is not set on  this
         **               CATSysHTTPRequest
         **       
         **       E_FAIL : ioRqHdValBuffer has unsufficient length OR
         **                iRqHeader ==  CATSysSHRqHdContentLength 
         **       
         ***/
		virtual HRESULT			GetRqHeader(CATSysSHRqHeader iRqHeader, char *ioRqHdValBuffer, int iBufferLen);
		//SIP: added because not possible to get header size and don't want to manage impact of reference on iBufferLen
		virtual HRESULT			GetRqHeaderSize(CATSysSHRqHeader iRqHeader, size_t &iBufferLen);

		virtual HRESULT			SetContent(void *iContent, unsigned int iSize, int iFlag = CATSysSHSCCopy );

		virtual HRESULT			GetMethod(CATSysSHMethod *oKind);
		virtual const char *	GetMethod();
		virtual HRESULT			GetStatus(CATSysSHStatus *oCode);
		virtual HRESULT			GetStatusString(char *iboStrg, unsigned int iBufLen, unsigned int *oLen);

		virtual HRESULT			GetURI(char *iboURI, unsigned int iBufferLen, unsigned int *oNeededLen = NULL, int iFlag = CATSysSHFlgRelativeURI | CATSysSHFlgWithQueries);
		virtual HRESULT			GetTarget(char *iboHost, unsigned int iBuffLen, unsigned short *oPort);
		virtual HRESULT			GetURIQuery(const char *iParm, char *iboParmVal, unsigned int iBuffLen, unsigned int *oRealLenP);
        /**
		HRESULT GetRequestParameter( const char *iParm, unsigned int iBuffLength  , unsigned int *oRealSize );
		HRESULT GetRequestHTTPParameter( const char *iParm, unsigned int iBuffLength, unsigned int *oRealSize);
		HRESULT GetRequestURIParameter( const char *iParm, unsigned int iBuffLength, unsigned int *oRealSize);
		*/
		virtual HRESULT			TransmitContent(void **oContent, unsigned int *oRealSize, int *oOwnership, int iFlag = CATSysSHFlgOnlyIfOwner);
		virtual HRESULT			GetFullMessage(char *iboMsg, unsigned int iBufLength, unsigned int *oRealSize);
		virtual HRESULT			GetFullMessageSize(unsigned int *oRealSize);
		virtual HRESULT			GetContentLength(unsigned int *oRealSize);
		virtual HRESULT			SetHeader(char *iPtr, unsigned int iSize = 0);
		virtual HRESULT			DebugDump(FILE *iFile, const char *iTitle = NULL, int iFlag = 0); 
		int						IsAnswerToHeadRequest();
        //=================================================================
        HRESULT					SetServerCookie(const char *iName, const char *iValue, const char * iPath);
        HRESULT					SetClientCookie(const char *iName, const char *iValue);
        HRESULT					GetCookie(const char *iName, char **oValue,char **oPath);
        HRESULT					GetCookieNamesList(char **oNamesArray[]);

        HRESULT					ResetCookie(const char *iCookieNames);
        HRESULT					ResetAllCookies();

        // Integration with CATHTTPClient
        // Warning SetCookiesFromString modifies iCookieString
        HRESULT					SetCookiesFromString(char *iCookieString, int iFlags = 0);
        // Integration with CATHTTPClient
        HRESULT					StoreCookies(const char *iURL, int (*iStoringFunc)(const char *, const char *, int));

		static int				GetStatusCode(CATSysSHStatus iCode); 
		static const char*		ProtocolId(); 
        virtual HRESULT			Send(int iFlag, CATSysHTTPRequest **oAnswer, CATSockets **ioSocket = NULL, CATSocketResult *oSocketError=NULL);
		static HRESULT			EasyRequest(CATSysSHMethod iMethod, const char *iURI, CATSysHTTPRequest **oReq = NULL, int iDirectSend = 0, int iWaitForAnswer = 0, CATSockets **ioSock = NULL, CATSocketResult *oSocketError = NULL);
		// MUST USE  CATSysSHFlgAnswerToHEAD in iSendFlag when  answering to a  
		// HEAD REQUEST
		static HRESULT			EasyAnswer(CATSysSHStatus iStatus, void *iBody = NULL, unsigned int iBodyLength = 0,CATSysHTTPRequest **oAns = NULL, int iSendFlag = 0, CATSockets **ioSocket = NULL, CATSocketResult *oSocketError = NULL);
		static void				SetDefaultHTTPVersion(CATSysSHPVersion iVersion) { S_Version = iVersion;};
		static CATSysSHPVersion	GetDefaultHTTPVersion() { return S_Version; };
		int						GetSpecialFlags(); /* reserved for internal use **/
	private:
		// MUST USE  CATSysSHFlgAnswerToHEAD in iSendFlag when  answering to a  

		HRESULT						CheckRqHeader(char *iStart, CATSysSHRqHeader iHeader, const char *iTitle);
		HRESULT						SetStatusFromString(const char *iStr);
		HRESULT						ConcatURI(const char *);
		HRESULT						CheckCookies(char *iP, int iAnswerMode, unsigned int iMax = 0);
		virtual void				SetHTTPVersion(CATSysSHPVersion iVersion) { m_Version = iVersion; };
		virtual CATSysSHPVersion	GetHTTPVersion() { return m_Version ; };

		CATSysSHMethod			m_Method;
		const char *			_Method;
		CATSysSHStatus			m_Status;
		char					*m_URI;
		char					*m_RqUA;
		char					*m_RqAccept;
		char					*m_RqContentType;
		char					*m_RqCustomHeaders;
		char					*m_StatusString;
		void					*m_Content;
		unsigned long long		m_ContentLength;
		unsigned long long		m_ContentBuffSize;
		unsigned long long		m_ContentBuffPos;
		char					*m_Target;
		unsigned short			m_TargetPort;
		unsigned short			m_URICurrentMax;
		CATSysSHCookie			*m_Cookie;
		void					*m_ExtD;
		static const char		*S_MethString[CATSysSHMethMax+1];
		static const char		*S_StatusString[CATSysSHStsMax+1];
		static int				S_StatusVal[CATSysSHStsMax+1];
		static CATSysSHPVersion	S_Version;
		char					*m_HeaderString;
		size_t					m_HeaderStringSize;
		unsigned long long		m_RequestContentLength;
		unsigned long long		m_TotalRcv;
	protected:
		int					m_Flags;
		CATSysSHChunkInfo	m_ChunkInfo;
		size_t				m_NxChunkSize;
		unsigned short		m_ChunkOffset;
		unsigned short		m_PartNb;
		CATSysSHPVersion	m_Version;
		bool				_IsHttps;
		const char *		_ServerWithPort;
};
#endif
