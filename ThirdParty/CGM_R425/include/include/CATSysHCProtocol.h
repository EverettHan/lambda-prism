#ifndef CATSysHCProtocol_H
#define CATSysHCProtocol_H
// COPYRIGHT DASSAULT-SYSTEMES 2003

#include "IUnknown.h"
#include "CATISysSockProtocols.h"
#include "CATHttp.h"
#ifdef HTTP_ASYNC_ACTIVATED
#include "CATHttpAsyncClient.h"
#else
#include "CATHttpClient.h"
#endif
class CATSockets;




//===================================================================
// Socket extension protocol using CATHttpClient
// ---------------------------------------------
// this protocol is exclusively a client protocol
// ---------------------------------------------
//===================================================================

class ExportedByJS0HTTP CATSysHCProtocol  : public CATISysSockProtocols
{
public:
	CATSysHCProtocol();
	virtual const char *GetProtocolId()  ;
	virtual CATSysSPResult Check(CATISysSockProtocolRq *iReq , CATSysSPOperation iOperation);

	/** 
	* for Protocol Send Message 
	**/

	virtual CATSysSPResult StartSend(CATSockets *iSock,CATISysSockProtocolRq *iReq ,  int *oActionFlag, void  **oBuffer, unsigned int *oLength,void **oBlackBox );

	virtual CATSysSPResult Send(CATSockets *iSock, CATISysSockProtocolRq *iReq ,  int *ioActionFlag, void  **ioBuffer, unsigned int *ioLength, void **ioBlackBox, int iPart  );

	virtual CATSysSPResult EndSend( CATSockets *iSock, CATISysSockProtocolRq *iReq,  int *ioActionFlag,  void  **ioBuffer, unsigned int *ioLength , void **ioBlackBox,int iPart);

	virtual CATSysSPResult ReleaseData( int iAction ,void **iBuffer, void **iBlackBox,int iPart);

	/**
	* for Protocol Receive Message 
	**/
	virtual CATSysSPResult Receive(  CATSockets * ,  CATISysSockProtocolRq **ioReq ,int *oActionFlag, CATSocketResult *oSocketResu);

	/**
	* for Protocol Connect 
	**/
	virtual CATSysSPResult PreConnect( CATSockets *,  CATISysSockProtocolRq *iReq , int *oActionFlag, char *oHostName, unsigned short *oPort);
	virtual CATSysSPResult PostConnect( CATSockets *,  CATISysSockProtocolRq *iReq ,int *oActionFlag);

	/** 
	* for protocol close
	**/
	virtual CATSysSPResult Close( CATSockets * , int iAlreadyClosed);

	/**
	** informs CATSockets of the policies choosen by the protocol
	**/
	virtual CATSysSPResult CheckPolicy( CATSysSPPolicy iFlags );

	/**
	** must be implemented to replace the wait
	**/
	virtual CATSysSPResult Wait( int iTimeOutMS, CATISysSockProtocolRq *iReq =NULL, CATSockets *iSock=NULL );

	virtual CATSysSPResult Operate(CATISysSockProtocolRq *iReq =NULL, int iOperation=0, void *ioData=NULL );


	CATSysSPDeclare

	static const char *GetTheProtocolId();

	//specific methode for HTTP
	HRESULT AddHTTPHeader(const char *iHeader, DWORD iFlags=CATHTTP_REQ_COALESCE);

private :
#ifdef HTTP_ASYNC_ACTIVATED
	CATHttpAsyncClient	*m_Client;
#else
	CATHttpClient		*m_Client;
#endif
	HRESULT				m_LastErr;
	int					m_RqNo;

	char					*m_BodyAtSend;
	int					m_BodyAtSendSize;
	int					m_StatusAtSend;
};


#endif

