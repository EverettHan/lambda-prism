#ifndef CATSysSHRequest_H
#define CATSysSHRequest_H
// COPYRIGHT DASSAULT-SYSTEMES 2003

#include "CATSysHTTPRequest.h"
class ExportedByJS0MT CATSysSHRequest : public CATSysHTTPRequest
{
public:
	CATSysSHRequest();
	CATSysSHRequest(CATSysHTTPRequest&, int iShare = 0);
	~CATSysSHRequest();
	virtual HRESULT SetCommand(const char *iCommand);
	virtual HRESULT GetCommand(const char *iParm);
	virtual HRESULT GetCommand(char *iboURI , unsigned int iBufferLen, unsigned int *oNeededLen = NULL);
	virtual HRESULT SetParameter(const char *iParm, const char *iParmVal);
	virtual HRESULT GetParameter(const char *iParm, char *iboParmVal, unsigned int iBuffLen, unsigned int *oRealLenP);

	virtual HRESULT GetParameters(char **oParms, char **oParmsVal, int *oParmsNb);



	HRESULT Send(int iWaitForAnswer, CATSysSHRequest **oAnswer, CATSockets **ioSocket = NULL, CATSocketResult *oSocketError = NULL);
	static  HRESULT EasyRequest(CATSysSHMethod iMethod, const char *iURI, CATSysSHRequest **oReq = NULL, int iDirectSend = 0, int iWaitForAnswer = 0, CATSockets **ioSock = NULL, CATSocketResult *oSocketError = NULL);
	static  HRESULT EasyAnswer(CATSysSHStatus iStatus, const void *iBody = NULL, unsigned int iBodyLength = 0, CATSysSHRequest **oAns = NULL, int iDirectSend = 0, CATSockets **ioSocket = NULL, CATSocketResult *oSocketError = NULL);

};
#endif
