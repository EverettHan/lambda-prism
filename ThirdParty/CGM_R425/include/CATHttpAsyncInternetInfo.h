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
#ifndef CATHTTPAsyncInternetInfo_H
#define CATHTTPAsyncInternetInfo_H


#undef min
#undef max
#include <algorithm>
#include <mutex>

#include "CATSysDataType.h"
#include "CATEvent.h"

#include "CATHttp.h"
#include "CATHttpAsyncObject.h"
#include "DSYSysRefCounter.h"
#include "CATHttpRequest.h"


#ifdef _WINDOWS_SOURCE
#include <wininet.h>
#include <winineti.h>
#else
#define HINTERNET unsigned int
#endif

#include <atomic>

#undef min
#undef max


class AsyncInternetInfo : public DSYSysRefCounter
{
public:
    AsyncInternetInfo(unsigned int	lDriverID);
	~AsyncInternetInfo();

	unsigned int			_InternetInfoMode;

	HINTERNET				_Hdl;     //Internet connection
	HINTERNET				_Req;     //Internet Request
	HINTERNET				_HdlWS;     //Internet Request
	std::atomic_uint 		iStatus;       //the url's status

	//SIP: never use DataToRead in main thread
	CATULONG64				_SizeRecvData;
	bool					IsChunkedPost;
	bool					IsPreventIgnoreCertErrors;
	std::mutex				_pWMutex;
	CATEvent*				RequestCompleteEvent;
	CATEvent*				HandleClosedEvent;
	CATEvent*				ConnectedEvent;
	void					*_MyHttpTrace;
	HRESULT					_HR;
	
	bool					IsWS;
	CATHttpRequest			*_CurrentRequest;
	unsigned int			_DriverID;
	std::atomic_bool		_OperationCompleteRecv;
};

#define WIN_REQ_SYNC	1
#define WIN_REQ_ASYNC	2
#define DS_REQ_SYNC		3
#define DS_REQ_ASYNC	4

HRESULT	CloseHandleSync(void *iMyHttpTrace, HINTERNET &iHdl, AsyncInternetInfo *iAsyncInfo);
HRESULT	CloseHandleAsyncNoCB(void *iMyHttpTrace, HINTERNET &iHdl);
HRESULT	CloseHandleAsync(void *iMyHttpTrace, HINTERNET &iHdl, AsyncInternetInfo *iAsyncInfo);
HRESULT	FuncCloseHandle(void *iMyHttpTrace, HINTERNET &iHdl, AsyncInternetInfo *iAsyncInfo);

#endif
