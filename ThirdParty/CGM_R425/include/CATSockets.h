#ifndef CATSockets_H 
#define CATSockets_H 


// COPYRIGHT DASSAULT SYSTEMES 2000

//====================================================
//=== INCLUDES =======================================
//====================================================
#include "JS0MT00.h"
#include "CATSocketConnector.h"
#include "CATISysSockProtocols.h"

#define CATSocketLocalHost NULL
#define CATSOCK_INVALID_ID -1

//====================================================
//=== CONSTANTS ======================================
//====================================================
#define CATSOCK_CLT_OK               0x0000

#define CATSOCK_CLT_READY            0x0000
#define CATSOCK_CLT_INIT             0x3001
#define CATSOCK_CLT_FAILURE          0x3002

#define CATSOCK_CLT_FAIL_IN_SOCKET   0x4001
#define CATSOCK_CLT_FAIL_IN_GETHNAM  0x4002
#define CATSOCK_CLT_FAIL_IN_CONNECT  0x4003
#define CATSOCK_CLT_FAIL_IN_RECV     0x4004
#define CATSOCK_CLT_FAIL_IN_SEND     0x4005
#define CATSOCK_CLT_FAIL_ARG_SEND    0x4006
#define CATSOCK_CLT_FAIL_ARG_RECV    0x4007
#define CATSOCK_CLT_FAIL_STS_CONNECT 0x4008
#define CATSOCK_INSUFFICIENT_LEN     0x4009
#define CATSOCK_CLT_SOCK_INVAL       0x400a
#define CATSOCK_CLT_TIMEOUT          0x400b
#define CATSOCK_CLT_FAIL_IN_IOCTL    0x400c  
#define CATSOCK_CLT_PARTIAL          0x400d  


#define CATSOCK_PROT_MSG_INVALID  0x4020
#define CATSOCK_PROT_ALREADY_SET  0x4021
#define CATSOCK_PROT_NOPROTOCOL   0x4022 
#define CATSOCK_PROT_ERROR        0x4023 
#define CATSOCK_PROT_RQ_INVALID   0x4024
//====================================================
// Flags forBasicReceive        
#define CATSysSockPeek    0x00000001


//====================================================
// enums
//====================================================
enum CATSocketProtocol { CATStandardProtocol, CATStringifiedProtocol };
enum CATSocketOptions { CATSocketNoDelay, CATSocketIPV4, CATSocketIPV6, CATSocketIPDualStack };



//====================================================
//=== CATSockets class  ==============================
//====================================================
class CATSocketsSecure;

class ExportedByJS0MT00 CATSockets
{
	friend CATSocketsSecure;
public:
	CATSockets(CATSocketHandler iSock = CATSOCK_INVALID_ID, CATSocketConnector *iParent = NULL);
	virtual ~CATSockets();
	CATSocketResult  Connect(unsigned short int iPort, const char *Hostname);
	CATSocketResult  ConnectTo(unsigned int remoteAdrs, unsigned short int iPort);
	CATSocketResult  ConnectService(const char *iServName, const char *Hostname = NULL, const char *iProt = "tcp");
	CATSocketResult SetOptions(CATSocketOptions iOptions);
	CATSocketResult SetProtocol(CATSocketProtocol);
	unsigned short int GetPort();
	CATSocketHandler GetHandler();
	CATSocketResult Send(const void *iBuffer, unsigned int iLen);
	CATSocketResult Receive(void *iBuffer, unsigned int iBufLen, unsigned int *oRealLen);
	CATSocketResult Wait(int iTIMEOUTiNms);
	CATSocketResult Peek(char *oBuffer, int iLenOfoBuffer, unsigned int iDecal, int iWaitForIt);
	CATSocketResult Close();
	CATSocketResult BasicSend(const void *iBuffer, unsigned int iLen);
	CATSocketResult BasicReceive(void *iBuffer, unsigned int iLen, int Flag = 0);
	CATSocketResult SmartReceive(void *iBuffer, unsigned int iLen, int iTm = 0, unsigned int *oRec = NULL, int Flag = 0);
	//------------------------------------------------------------------
	// Operators overload
	//------------------------------------------------------------------
	CATSockets& operator << (int   tobeSend);
	CATSockets& operator << (float tobeSend);
	CATSockets& operator << (double tobeSend);
	CATSockets& operator << (const char*  tobeSend);

	CATSockets& operator >> (int& tobeRec);
	CATSockets& operator >> (float& tobeRec);
	CATSockets& operator >> (double& tobeRec);
	CATSockets& operator >> (char*  tobeRec);

	//------------------------------------------------------------------
	// for external protocol enablement
	//------------------------------------------------------------------
	CATSocketResult  SetExternalProtocol(CATISysSockProtocols  *iProtocol);
	/*
		  return the external protocol Id is there is one such protocol
		  return NULL if there is no external protocol
	 */
	const char *GetExternalProtocolId();
	CATSocketResult  ConnectWithProtocol(CATISysSockProtocolRq *iReq, CATSysSPResult *oProtocolError = NULL);
	CATSocketResult  SendWithProtocol(CATISysSockProtocolRq *iReq, CATSysSPResult *oProtocolError = NULL);
	CATSocketResult  ReceiveWithProtocol(CATISysSockProtocolRq **ioReq, CATSysSPResult *oProtocolError = NULL);
	CATSocketResult  WaitWithProtocol(int iTimeoutMs, CATISysSockProtocolRq *iReq);
	/** needless to use that method for most protocols **/
	CATSysSPResult  ExtOperation(CATISysSockProtocolRq *iReq = NULL, int iOp = 0, void  *ioData = NULL);

private:
	CATSocketResult StringifiedReceive(char *);
	CATSocketData *_Data;

protected:
	virtual int		DSPendingByte(CATSocketHandler iSock, CATULONG32 &oLen);
	virtual int		DSConnect(int sockfd, const struct addrinfo *addr);
	virtual int		DSread(CATSocketHandler iSock, void *buf, size_t len, int flags);
	virtual int		DSwrite(CATSocketHandler iSock, const void *buf, size_t len, int flags);
};
#endif
