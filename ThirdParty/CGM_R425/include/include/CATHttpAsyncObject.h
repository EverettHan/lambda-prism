#ifndef CATHttpAsyncObject_h
#define CATHttpAsyncObject_h

#include "CATSysErrorDef.h"
#include "DSYSysRefCounter.h"


/*
	Structure used in HTTP Async callback for async write
*/
typedef struct sendInfo
{
	HRESULT			ErrorCode;
	CATULONG64		CurrentTotalDataSent;
	CATULONG64		TotalDataToSend;
	CATULONG64		CurrentDataSize;
	char *			Data;
} CATHttpAsyncSendInfo;



/*
	Structure used in HTTP Async callback for async read
*/
typedef struct receiveInfo
{
	HRESULT			ErrorCode;
	CATULONG64		TotalDataSize;
	unsigned int	CurrentDataSize;
	char *			Data;
	CATULONG64		TotalDataReaded;
	bool			IsChunk;
} CATHttpAsyncReceiveInfo;

class CATHttpAsyncClient;

/**
 **/
#pragma warning( push )
#pragma warning( disable : 4275 )
class CATHttpAsyncObject : public DSYSysRefCounter
{
public:
	//SIP : add a TS ID to this object. Goal check if an object is reused for multiple request.
	virtual ~CATHttpAsyncObject() {};

	virtual bool IsChunkSend() { return false; };
	virtual bool IsSendCallBackCapable() { return false; };
	virtual bool IsRewindCapable() { return false; };
	virtual HRESULT Rewind() { return E_NOTIMPL; };
	virtual HRESULT SendCallBack(int iSteps, CATHttpAsyncSendInfo* iInfo) { return E_NOTIMPL; };
	virtual HRESULT ReceiveCallBack(int iSteps, CATHttpAsyncReceiveInfo* iInfo)	{ return E_NOTIMPL; };
};
#pragma warning( pop )

#endif
