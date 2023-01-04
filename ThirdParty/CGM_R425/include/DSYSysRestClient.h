#ifndef DSYSysRestClient_h
#define DSYSysRestClient_h

/************************************************************************/
/* Includes                                                             */
/************************************************************************/
#include "CATSysDataType.h"
#include "DSYString.h"
#include "DSYSysHTTPCommunication.h"

/************************************************************************/
/* Defines                                                              */
/************************************************************************/

/************************************************************************/
/* Classes declaration                                                  */
/************************************************************************/

class ExportedByJS0HTTP DSYSysRestClient
{
	///////////////////////////////////////////
	////// Types/Constants/Struct/Enum ////////
	///////////////////////////////////////////
public:
	/// Enumeration of managed methods.
	typedef enum class Method_t
	{
		_GET
		, _POST
		, _PUT
		, _DELETE
		, _PATCH
	} Method;

private:
	/// Enumeration for internal state machine.
	typedef enum class State_t
	{
		_Init,
		_Begin,
		_End,
		_Async
	} State;

	///////////////////////////////////////////
	///////////////// Methods /////////////////
	///////////////////////////////////////////
public:
	DSYSysRestClient();
	~DSYSysRestClient();

	/**
	* Ensure that the client is ready to begin a request.
	*/
	void		Reset();

	/// Synchronous.

	/**
	* Full (begin and end) synchronous request without body (i.e. for GET/DELETE).
	* @param iUrl       The URL to use.
	* @param iMethod    The HTTP method.
	* @return E_INVALIDARG if there is no URL,
	*         E_ABORT if the DSYSysRestClient is not ready to begin a request,
	*         else HRESULT of the setting.
	*/
	HRESULT SyncRequestWithoutBody(const CATUnicodeString& iUrl, const Method& iMethod);

	/**
	* Full (begin and end) synchronous request without body (i.e. for GET/DELETE) and added headers.
	* @param iUrl       The URL to use.
	* @param iMethod    The HTTP method.
	* @param ipHeaders  The headers to add (as array pointer).
	* @param iNbHeaders Nb of header in the array.
	* @return E_INVALIDARG if there is no URL,
	*         E_ABORT if the DSYSysRestClient is not ready to begin a request,
	*         else HRESULT of the setting.
	*/
	HRESULT SyncRequestWithoutBody(const CATUnicodeString& iUrl, const Method& iMethod, CATUnicodeString const * ipHeaders, const size_t iNbHeaders);

	/**
	* Begin of synchronous request (which will require an EndRequest afterward) to allow to write a body afterward (i.e for POST/PUT/PATCH).
	* @param iUrl      The URL to use.
	* @param iMethod   The HTTP method.
	* @return E_INVALIDARG if there is no URL,
	*         E_ABORT if the DSYSysRestClient is not ready to begin a request,
	*         else HRESULT of the setting.
	*/
	HRESULT BeginSyncRequestWithBody(const CATUnicodeString& iUrl, const Method& iMethod);

	/**
	* Begin of synchronous request (which will require an EndRequest afterward) to allow to write a body afterward (i.e for POST/PUT/PATCH) and added headers.
	* @param iUrl       The URL to use.
	* @param iMethod    The HTTP method.
	* @param ipHeaders  The headers to add (as array pointer).
	* @param iNbHeaders Nb of header in the array.
	* @return E_INVALIDARG if there is no URL,
	*         E_ABORT if the DSYSysRestClient is not ready to begin a request,
	*         else HRESULT of the setting.
	*/
	HRESULT BeginSyncRequestWithBody(const CATUnicodeString& iUrl, const Method& iMethod, CATUnicodeString const* ipHeaders, const size_t iNbHeaders);

	/**
	* Write the body of the request (between a begin and an end).
	* @param iData				The data to write.
	* @param iDataSize		The size of the data to write.
	* @return E_ABORT if no BeginRequest has been done previously (or if the EndRequest has already been called),
	*					else the result of the write.
	*/
	HRESULT WriteRequestBody(const void* iData, const CATULONG64& iDataSize);

	/**
	* End/Do the request.
	* @return E_ABORT if no BeginRequest has been done previously (or if the EndRequest has already been called),
	*         minus the HTTP error code if the HTTP request failed (or use GetResponseHeaders CATHTTP_QUERY_STATUS_CODE),
	*         HRESULT for other kind of error,
	*					else success.
	*/
	HRESULT EndRequest();

	/**
	* Read the body of the response after an EndRequest (should be used for GET/POST/PACTH and even DELETE).
	* @param oData				The data (or a chunk) of the response body.
	* @param ioDataSize		The size of the data in the response body (at most the size of a chunk).
	* @return E_ABORT if no EndRequest has been done previously,
	*         SUCCEEDED and ioDataSize=0 if a full chunk has been read but there is they still data to read (so call again ReadResponseBody),
	*         SUCCEEDED and ioDataSize!=0 if it's the last part of the data,
	*					else error about the read.
	*/
	HRESULT ReadResponseBody(void** oData, CATULONG64& ioDataSize);

	/**
	* Get details of the last error that occured.
	* @param oMsgCatalog			  The catalog of error message used..
	* @param oMsgId		          The id of the error inside the catalog.
	* @param oIsWebLoginNeeded  Boolean about the login requirement.
	* @return E_ABORT if no request began (so no error could have been catched),
	*					else S_OK.
	*/
	HRESULT GetError(CATUnicodeString& oMsgCatalog, CATUnicodeString& oMsgId, bool& oIsWebLoginNeeded);

	/**
	* Get header data from the response.
	* @param oHeader   Pointer to a buffer that will be allocated.
	* @param oLen			 Size of the allocated buffer.
	* @param iFlags		 (optionnal) Flag to indicate what to retreive in the response header (by default get everything), see SpecialAPI/ProtectedInterfaces/CATHttpFlags.h.
	* @param iHeader	 (optionnal) Name of the header to retreive (by defaut not a specific one). If you want the potential set-cookies, consider using CATSysGetCookie.
	* @return E_ABORT if the has not ended (for synchronous case),
	*					else S_OK.
	*/
	HRESULT	GetResponseHeaders(void** oHeader, size_t* oLen, DWORD iFlags = CATHTTP_QUERY_ALL, const CATUnicodeString &iHeader = "");

private:
	CATUnicodeString MethodToString(const Method& iMethod) const;
	HRESULT BeginRequest(const CATUnicodeString& iUrl, const Method& iMethod, CATUnicodeString const* ipHeaders, const size_t iNbHeaders);

	///////////////////////////////////////////
	///////////////// Members /////////////////
	///////////////////////////////////////////
	DSYSysHTTPCommunication			*m_pCom;
	State												m_State;
};

#endif // DSYSysRestClient_h
