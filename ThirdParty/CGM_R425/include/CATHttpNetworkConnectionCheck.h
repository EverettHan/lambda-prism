#ifndef CATHttpNetworkConnectionCheck_H
#define CATHttpNetworkConnectionCheck_H
#include "JS0HTTP.h"
#include "CATSysErrorDef.h"
#include "CATEvent.h"

#ifndef HTTPARCH //all
////////////////////////////////////////////
////////////////////////////////////////////
//         NETWORK TEST FUNCTIONS         //
////////////////////////////////////////////
////////////////////////////////////////////
#define CATHttpThreadNetworkCheckTimeout 1
#define CATHttpThreadNetworkCheckLatency 2
#define CATHttpThreadNetworkCheckDownload 3
#define CATHttpThreadNetworkCheckUpload 4
#define CATHttpThreadNetworkCheckAll 65535

//         NETWORK TEST FUNCTIONS         //
extern "C" long ExportedByJS0HTTP CATHttpCheckNetworkAllWithEvent(CATEvent *iEvent);
extern "C" long ExportedByJS0HTTP CATHttpCheckNetworkAll();


////////////////////////////////////////////////////
////////////////////////////////////////////////////
//         NETWORK AVAILABILITY FUNCTIONS         //
////////////////////////////////////////////////////
////////////////////////////////////////////////////
HRESULT ExportedByJS0HTTP DSYSysIsNetworkConnected(bool &oIsConnected);
HRESULT ExportedByJS0HTTP DSYSysIsInternetConnected(bool &oIsConnected);


//Automatically started by CATSysLogonDone.
extern "C" long ExportedByJS0HTTP DSYSysStartHandleNetworkEventWithEvent(CATEvent *iEvent);
extern "C" long ExportedByJS0HTTP DSYSysStartHandleNetworkEvent();
extern "C" long ExportedByJS0HTTP DSYSysStopHandleNetworkEvent();

class DSYSysNetworkEvent
{
public:
	virtual ~DSYSysNetworkEvent()
	{
	};
	virtual HRESULT InternetConnected() = 0;
	virtual HRESULT InternetDisconnected() = 0;
	virtual HRESULT NetworkConnected() = 0;
	virtual HRESULT NetworkDisconnected() = 0;
};

#define MAX_CALLBACK_NETWORK_EVENT_NUMBER	5
extern "C" HRESULT ExportedByJS0HTTP DSYSysAddCallbackToNetworkEvent(DSYSysNetworkEvent* iNetworkEvent);



#endif //HTTPARCH

#endif //CATHttpNetworkConnectionCheck_H
