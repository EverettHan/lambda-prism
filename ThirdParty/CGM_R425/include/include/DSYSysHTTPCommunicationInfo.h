#ifndef DSYSysHTTPCommunicationInfo_H
#define DSYSysHTTPCommunicationInfo_H

#include "CATSysDataType.h"
#include "CATSysErrorDef.h"
#include "CATHttp.h"
#include "DSYSysRefCounter.h"
#include "DSYString.h"
#include <atomic>
#include <cstdint>

extern "C" ExportedByJS0HTTP HRESULT GetHttpErrorMessage(int iHttpStatus, CATUnicodeString &oMsgCatalog, CATUnicodeString &oMsgId);

class ExportedByJS0HTTP DSYSysHTTPCommunicationInfo : public DSYSysRefCounter
{
	friend class CATThreadHttpNetworkCheck;
public:
	/*
		return : the instance of DSYSysHTTPCommunicationInfo, this instance have to be AddRef and reLease
	*/
	static DSYSysHTTPCommunicationInfo	*GetDSYSysHTTPCommunicationInfo();

	/*
		return : the HRESULT of the latency computing
		oLatency : the value of the computed latency if return HRESULT is S_OK
		oPacketLoss : the value of the computed PacketLoss if return HRESULT is S_OK
	*/
	HRESULT GetM1Latency(CATULONG64 &oLatency, CATULONG64 &oPacketLoss);

	/*
		return : the HRESULT of the upload bandwidth computing
		oUpLoad : the value of the computed upload bandwidth if return HRESULT is S_OK
	*/
	HRESULT GetM1Download(CATULONG64 &oDownload);

	/*
		return : the HRESULT of the download bandwidth computing
		oDownload : the value of the computed download bandwidth if return HRESULT is S_OK
	*/
	HRESULT GetM1Upload(CATULONG64 &oUpLoad);

	/*
		return : the HRESULT of the download bandwidth computing
		oDownload : the value of the computed download bandwidth if return HRESULT is S_OK
	*/
	HRESULT GetM1Timeout(CATULONG64 iTimeout, HRESULT iHR);

protected:
	HRESULT SetM1Latency(CATULONG64 iLatency, CATULONG64 iPacketLoss, HRESULT iHR);
	HRESULT SetM1Download(CATULONG64 iDownload, HRESULT iHR);
	HRESULT SetM1Upload(CATULONG64 iUpLoad, HRESULT iHR);
	HRESULT SetM1Timeout(CATULONG64 iTimeout, HRESULT iHR);

	HRESULT			_M1LHR;
	std::atomic_uint64_t	_M1Latency;
	std::atomic_uint64_t	_M1PacketLoss;
	HRESULT			_M1DHR;
	std::atomic_uint64_t	_M1Download;
	HRESULT			_M1UHR;
	std::atomic_uint64_t	_M1Upload;
private:
	DSYSysHTTPCommunicationInfo();
	~DSYSysHTTPCommunicationInfo();
};



#endif

