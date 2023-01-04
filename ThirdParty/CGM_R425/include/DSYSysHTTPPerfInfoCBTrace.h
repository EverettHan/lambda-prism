#ifndef DSYSysHTTPPerfInfoCBTrace_H
#define DSYSysHTTPPerfInfoCBTrace_H
#include "JS0HTTP.h"
#include "DSYSysHTTPPerfInfoCB.h"
#include "DSYSysTrace.h"

//SIP: Sample and default implementation with HTTPPerfo trace
class ExportedByJS0HTTP DSYSysHTTPPerfInfoCBTrace : public DSYSysHTTPPerfInfoCB
{
public:
	DSYSysHTTPPerfInfoCBTrace();
	~DSYSysHTTPPerfInfoCBTrace();

	HRESULT	RequestStarted(CATULONG64 iTime);
	HRESULT RequestSent(CATULONG64 iTime, CATULONG64 iSIDLNBWrite, CATULONG64 iNBWrite);
	HRESULT	RequestEnded(CATULONG64 iTime, CATULONG64 iSIDLNBRead, CATULONG64 iNBRead);

	HRESULT	WriteStarted(CATULONG64 iTime);
	HRESULT	WriteEnded(CATULONG64 iTime);

	HRESULT	SIDLWriteStarted(CATULONG64 iTime);
	HRESULT	SIDLWriteEnded(CATULONG64 iTime);

	HRESULT	ReadStarted(CATULONG64 iTime);
	HRESULT	ReadEnded(CATULONG64 iTime);

	HRESULT	SIDLReadStarted(CATULONG64 iTime);
	HRESULT	SIDLReadEnded(CATULONG64 iTime);

protected:
	void	*_MyHttpPerfoTrace;
};




#endif
