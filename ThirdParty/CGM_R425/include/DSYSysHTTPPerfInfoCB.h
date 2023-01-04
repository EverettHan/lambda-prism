#ifndef DSYSysHTTPPerfInfoCB_H
#define DSYSysHTTPPerfInfoCB_H
#include "JS0HTTP.h"
#include "IUnknown.h"
#include "CATSysTSTime.h"
#include "DSYSysRefCounter.h"

#pragma warning( push )
#pragma warning( disable : 4275 )
class ExportedByJS0HTTP DSYSysHTTPPerfInfoCB : public DSYSysRefCounter
{
public:
	virtual ~DSYSysHTTPPerfInfoCB()
	{
	};

	virtual	HRESULT	RequestStarted(CATULONG64 iTime) = 0;
	virtual	HRESULT RequestSent(CATULONG64 iTime, CATULONG64 iSIDLNBWrite, CATULONG64 iNBWrite) = 0;
	virtual	HRESULT	RequestEnded(CATULONG64 iTime, CATULONG64 iSIDLNBRead, CATULONG64 iNBRead) = 0;

	virtual	HRESULT	WriteStarted(CATULONG64 iTime) = 0;
	virtual	HRESULT	WriteEnded(CATULONG64 iTime) = 0;

	virtual	HRESULT	SIDLWriteStarted(CATULONG64 iTime) = 0;
	virtual	HRESULT	SIDLWriteEnded(CATULONG64 iTime) = 0;

	virtual	HRESULT	ReadStarted(CATULONG64 iTime) = 0;
	virtual	HRESULT	ReadEnded(CATULONG64 iTime) = 0;

	virtual	HRESULT	SIDLReadStarted(CATULONG64 iTime) = 0;
	virtual	HRESULT	SIDLReadEnded(CATULONG64 iTime) = 0;
};
#pragma warning( pop )

#endif
