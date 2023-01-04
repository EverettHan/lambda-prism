#ifndef CATSysSHServer_H
#define CATSysSHServer_H

#include <atomic>
#include "CATSockets.h"
#include "CATSocketConnector.h"
#define CATSysSHSrvInfiniteLoop -1

class CATSysSHRequest;
class CATSockets;
struct CATSysSHRequestHandlerData
{
};

/***
 *** CATSysSHRequestHandler  is the function that is calledback by LoopForEvents and that must handle the requests
 *** CATSysSHRequestHandler function MUST anwer the request except if it specifies TRUE output value in
 *** oMustAnswer argument
 ***
 *** ARGUMENTS
 ***
 ***   iRequ             : INPUT  : iReq is the incoming request that must be handled
 ***                          iReq must NOT be released by  the CATSysSHRequestHandler function
 ***
 ***   iSock             : INPUT  : iSock  is the sockets on which came the request
 ***                          iSock must NOT be deleted by  the CATSysSHRequestHandler function
 ***
 ***   oMustAnswer       : OUTPUT :  oMustAnswer must be set to TRUE value (-1) if CATSysSHRequestHandler
 ***                           function wants LoopForEvents to  give NotFound default answer .
 ***                           In that specific case CATSysSHRequestHandler  may not answer
 ***                           In all other cases oMustAnswer must be set to FALSE value (0)
 ***   oMustCeaseWaiting : OUTPUT : oMustCeaseWaiting must be set to TRUE value (-1) if if CATSysSHRequestHandle
 ***                                 function wants that the calling LoopForEvents cease to wait
 ***                                In all other cases oMustCeaseWaiting must be set to FALSE value (0)
 ***
 ***/
typedef HRESULT(*CATSysSHRequestHandler) (CATSysSHRequest* iReq, CATSockets* iSock, int* oMustAnswer, int* oMustCeaseWaiting, CATSysSHRequestHandlerData* iData);

/***
 *** CATSysSHServer allows to declare a SUBHTTP server and to have it support SUBHTTP protocol
 *** CATSysSHServer is a simplification service that help coding easily simple batch servers
 *** supporting SUBHTTP protocol
 ***
 ***  CATSysSHServer must be created with CATSysSHServer::Create factory static method
 ***
 ***/
class ExportedByJS0MT CATSysSHServer
{
	friend class CATSysSHServerSecure;
	CATSysSHServer();
	CATSocketConnector	*m_SC;
	const char			*_Interface;
	unsigned short		_Port;
	static const char*	_CertPath;
	static const char*	_KeyPath;

public:
	~CATSysSHServer();

	/**
	 ** Create allows to instanciante a CATSysSHServer server
	 ** Returns NULL a problem occured
	 **/
	static CATSysSHServer* Create(unsigned short  iPort, const char* iInterface = nullptr);

	/**
	 ** LoopForEvents allows to wait for  requests to come and handle them through iRequestHandler function
	 **
	 ** iMaxTime allows to cease waiting if an elapsed time without any incoming request occurs
	 **
	 ** iRequestHandler : is a pointer function of type CATSysSHRequestHandler that must be given as input
	 **                   to LoopForRequests in order to handle incoming requests
	 **
	 **/
	HRESULT Loop(CATSysSHRequestHandler iRequestHandler, CATSysSHRequestHandlerData* iData = NULL, int iMaxTime = CATSysSHSrvInfiniteLoop);

	/**
	 **  GetPort : allows to obtain the port on which CATSysSHServer is declared
	 **/
	HRESULT GetPort(unsigned short* oPort)
	{
		if (m_SC && oPort)
		{
			*oPort = m_SC->GetPort();
			return S_OK;
		}
		else
			return E_FAIL;
	};

	/**
	 **  GetNbClients : allows to obtain the current number of clients
	 **/
	HRESULT GetNbOfClients(int* oNb) { return -1; };

	/**
	 **  GetNbClients : allows to obtain the current number of clients
	 **/
	HRESULT SetCertificate(const char* iCert, const char* iKey);
};

#endif
