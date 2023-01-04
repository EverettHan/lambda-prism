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
#ifndef CATHTTPFLAGS_H
#define CATHTTPFLAGS_H

#ifdef _WINDOWS_SOURCE
#include <winsock.h>
#include <wininet.h>
#endif


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
//////////////// GLOBAL FLAGS FOR ALL OS //////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
#define CATHTTP_CHUNK					0x00000001
#define CATHTTP_CHUNK_PER_CHUNK			0x00001000
#define CATHTTP_NORMAL_SEND				0x00000000
#define CATHTTP_NO_AUTH401				0x10000000
#define CATHTTP_NO_AUTH407				0x20000000

//DS Flag For CATHtpptClient : SetOptions
#define CATHTTP_PARENT_WINDOW_HANDLER	0x40000000
#define CATHTTP_KEEP_ERROR_BODY			0x80000000
#define	CATHTTP_OPTION_URL_ENCODE_MODE	0x20000000
#define CATHTTP_OPTION_REQUEST_ID		0x10000000

//DS Flag For CATHTTP_KEEP_ERROR_BODY : SetOptions
#define CATHTTP_KEEP_ERROR_BODY_ENABLE	0x00000001
#define CATHTTP_KEEP_ERROR_BODY_DISABLE	0x00000000

//SIP: To make a get and do not retreive the body (ONLY FOR HTTClient, useless with AsyncClient)
#define CATSysHTTPNoFinalGetBody 0x00010000


//DS Flag For Async http client to don't read the body for async
#define CATHTTP_ASYNC_READ_BODY_ENABLE	0x00000001
#define CATHTTP_ASYNC_READ_BODY_DISABLE	0x00000000

//Flags for cookie management class
#define CATHTTP_NO_INTERNET_SET_COOKIE	0x00000001  //Usefull on windows only
#define CATHTTP_NO_PROTECTION_CHECK		0x00000002
#define CATHTTP_INTERNET_COOKIE_HTTPONLY 0x00002000



//Flags for streamer
#define CATHTTP_STREAMER_MORE_DATA		0x00000000  //Usefull on windows only
#define CATHTTP_STREAMER_NO_MORE_DATA	0x00000001  //Usefull on windows only
#define CATHTTP_STREAMER_STOP_STREAMING	0x00000002

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

#define DSYHTTPCOM_FLAGS					0x00800000



#ifndef _WINDOWS_SOURCE
#define CATHTTP_IGNORE_CERT_CN_INVALID		0x00001000
#define CATHTTP_IGNORE_CERT_DATE_INVALID	0x00002000
#define CATHTTP_IGNORE_REDIRECT_TO_HTTPS	0x00004000
#define CATHTTP_IGNORE_REDIRECT_TO_HTTP		0x00008000
//Dangerous Flag
#define CATHTTP_IGNORE_REVOCATION			0x00000080
#define CATHTTP_IGNORE_UNKNOWN_CA			0x00000100
#define CATHTTP_IGNORE_WRONG_USAGE			0x00000200


#define CATHTTP_NO_UI					0x00000200  // Only for cookie dlg on http

#define CATHTTP_SECURE					0x00800000
#define CATHTTP_REQ_COALESCE			0x40000000
#define CATHTTP_REQ_COALESCE_SEMICOLON  0x01000000
#define CATHTTP_ADDREQ_FLAG_REPLACE		0x80000000

#define CATHTTP_NO_COOKIES				0x00080000
#define CATHTTP_NO_AUTH					0x00040000

#define CATHTTP_NO_AUTO_REDIRECT		0x00200000
#define CATHTTP_KEEP_CONNECTION			0x00400000


#else
//Only for cookie dlg on http
#define CATHTTP_NO_UI						INTERNET_FLAG_NO_UI

#define CATHTTP_SECURE						INTERNET_FLAG_SECURE 
#define CATHTTP_KEEP_CONNECTION				INTERNET_FLAG_KEEP_CONNECTION


#define CATHTTP_REQ_COALESCE				HTTP_ADDREQ_FLAG_COALESCE
#define CATHTTP_REQ_COALESCE_SEMICOLON		HTTP_ADDREQ_FLAG_COALESCE_WITH_SEMICOLON
#define CATHTTP_ADDREQ_FLAG_REPLACE			HTTP_ADDREQ_FLAG_REPLACE

#define CATHTTP_NO_COOKIES					INTERNET_FLAG_NO_COOKIES
#define CATHTTP_NO_AUTH						INTERNET_FLAG_NO_AUTH
#define CATHTTP_NO_AUTO_REDIRECT			INTERNET_FLAG_NO_AUTO_REDIRECT


#define CATHTTP_IGNORE_REDIRECT_TO_HTTP		SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTP  
#define CATHTTP_IGNORE_REDIRECT_TO_HTTPS	SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTPS
#define CATHTTP_IGNORE_CERT_DATE_INVALID	SECURITY_FLAG_IGNORE_CERT_DATE_INVALID
#define CATHTTP_IGNORE_CERT_CN_INVALID		SECURITY_FLAG_IGNORE_CERT_CN_INVALID
#define CATHTTP_IGNORE_UNKNOWN_CA			SECURITY_FLAG_IGNORE_UNKNOWN_CA
#define CATHTTP_IGNORE_REVOCATION			SECURITY_FLAG_IGNORE_REVOCATION
#define CATHTTP_IGNORE_WRONG_USAGE			SECURITY_FLAG_IGNORE_WRONG_USAGE

#endif

//you should also use CATHTTP_NO_UI to disable UI for cookie
#define CATHTTP_DISABLE_SECURITY_UI		CATHTTP_IGNORE_CERT_CN_INVALID | CATHTTP_IGNORE_CERT_DATE_INVALID | CATHTTP_IGNORE_REDIRECT_TO_HTTPS | CATHTTP_IGNORE_REDIRECT_TO_HTTP | CATHTTP_IGNORE_UNKNOWN_CA | CATHTTP_IGNORE_REVOCATION | CATHTTP_IGNORE_WRONG_USAGE
//just for test ... and KO #define CATHTTP_DISABLE_SECURITY_UI		0xFFFFFFFF







#ifndef _WINDOWS_SOURCE

#define INTERNET_ERROR_BASE                     12000

#define ERROR_INTERNET_OUT_OF_HANDLES           (INTERNET_ERROR_BASE + 1)
#define ERROR_INTERNET_TIMEOUT                  (INTERNET_ERROR_BASE + 2)
#define ERROR_INTERNET_EXTENDED_ERROR           (INTERNET_ERROR_BASE + 3)
#define ERROR_INTERNET_INTERNAL_ERROR           (INTERNET_ERROR_BASE + 4)
#define ERROR_INTERNET_INVALID_URL              (INTERNET_ERROR_BASE + 5)
#define ERROR_INTERNET_UNRECOGNIZED_SCHEME      (INTERNET_ERROR_BASE + 6)
#define ERROR_INTERNET_NAME_NOT_RESOLVED        (INTERNET_ERROR_BASE + 7)
#define ERROR_INTERNET_PROTOCOL_NOT_FOUND       (INTERNET_ERROR_BASE + 8)
#define ERROR_INTERNET_INVALID_OPTION           (INTERNET_ERROR_BASE + 9)
#define ERROR_INTERNET_BAD_OPTION_LENGTH        (INTERNET_ERROR_BASE + 10)
#define ERROR_INTERNET_OPTION_NOT_SETTABLE      (INTERNET_ERROR_BASE + 11)
#define ERROR_INTERNET_SHUTDOWN                 (INTERNET_ERROR_BASE + 12)
#define ERROR_INTERNET_INCORRECT_USER_NAME      (INTERNET_ERROR_BASE + 13)
#define ERROR_INTERNET_INCORRECT_PASSWORD       (INTERNET_ERROR_BASE + 14)
#define ERROR_INTERNET_LOGIN_FAILURE            (INTERNET_ERROR_BASE + 15)
#define ERROR_INTERNET_INVALID_OPERATION        (INTERNET_ERROR_BASE + 16)
#define ERROR_INTERNET_OPERATION_CANCELLED      (INTERNET_ERROR_BASE + 17)
#define ERROR_INTERNET_INCORRECT_HANDLE_TYPE    (INTERNET_ERROR_BASE + 18)
#define ERROR_INTERNET_INCORRECT_HANDLE_STATE   (INTERNET_ERROR_BASE + 19)
#define ERROR_INTERNET_NOT_PROXY_REQUEST        (INTERNET_ERROR_BASE + 20)
#define ERROR_INTERNET_REGISTRY_VALUE_NOT_FOUND (INTERNET_ERROR_BASE + 21)
#define ERROR_INTERNET_BAD_REGISTRY_PARAMETER   (INTERNET_ERROR_BASE + 22)
#define ERROR_INTERNET_NO_DIRECT_ACCESS         (INTERNET_ERROR_BASE + 23)
#define ERROR_INTERNET_NO_CONTEXT               (INTERNET_ERROR_BASE + 24)
#define ERROR_INTERNET_NO_CALLBACK              (INTERNET_ERROR_BASE + 25)
#define ERROR_INTERNET_REQUEST_PENDING          (INTERNET_ERROR_BASE + 26)
#define ERROR_INTERNET_INCORRECT_FORMAT         (INTERNET_ERROR_BASE + 27)
#define ERROR_INTERNET_ITEM_NOT_FOUND           (INTERNET_ERROR_BASE + 28)
#define ERROR_INTERNET_CANNOT_CONNECT           (INTERNET_ERROR_BASE + 29)
#define ERROR_INTERNET_CONNECTION_ABORTED       (INTERNET_ERROR_BASE + 30)
#define ERROR_INTERNET_CONNECTION_RESET         (INTERNET_ERROR_BASE + 31)
#define ERROR_INTERNET_FORCE_RETRY              (INTERNET_ERROR_BASE + 32)
#define ERROR_INTERNET_INVALID_PROXY_REQUEST    (INTERNET_ERROR_BASE + 33)
#define ERROR_INTERNET_NEED_UI                  (INTERNET_ERROR_BASE + 34)

#define ERROR_INTERNET_HANDLE_EXISTS            (INTERNET_ERROR_BASE + 36)
#define ERROR_INTERNET_SEC_CERT_DATE_INVALID    (INTERNET_ERROR_BASE + 37)
#define ERROR_INTERNET_SEC_CERT_CN_INVALID      (INTERNET_ERROR_BASE + 38)
#define ERROR_INTERNET_HTTP_TO_HTTPS_ON_REDIR   (INTERNET_ERROR_BASE + 39)
#define ERROR_INTERNET_HTTPS_TO_HTTP_ON_REDIR   (INTERNET_ERROR_BASE + 40)
#define ERROR_INTERNET_MIXED_SECURITY           (INTERNET_ERROR_BASE + 41)
#define ERROR_INTERNET_CHG_POST_IS_NON_SECURE   (INTERNET_ERROR_BASE + 42)
#define ERROR_INTERNET_POST_IS_NON_SECURE       (INTERNET_ERROR_BASE + 43)
#define ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED  (INTERNET_ERROR_BASE + 44)
#define ERROR_INTERNET_INVALID_CA               (INTERNET_ERROR_BASE + 45)
#define ERROR_INTERNET_CLIENT_AUTH_NOT_SETUP    (INTERNET_ERROR_BASE + 46)
#define ERROR_INTERNET_ASYNC_THREAD_FAILED      (INTERNET_ERROR_BASE + 47)
#define ERROR_INTERNET_REDIRECT_SCHEME_CHANGE   (INTERNET_ERROR_BASE + 48)
#define ERROR_INTERNET_DIALOG_PENDING           (INTERNET_ERROR_BASE + 49)
#define ERROR_INTERNET_RETRY_DIALOG             (INTERNET_ERROR_BASE + 50)
#define ERROR_INTERNET_HTTPS_HTTP_SUBMIT_REDIR  (INTERNET_ERROR_BASE + 52)
#define ERROR_INTERNET_INSERT_CDROM             (INTERNET_ERROR_BASE + 53)
#define ERROR_INTERNET_SEC_CERT_REV_FAILED		(INTERNET_ERROR_BASE + 54)
#define ERROR_INTERNET_SEC_CERT_ERRORS			(INTERNET_ERROR_BASE + 55)

//
// FTP API errors
//

#define ERROR_FTP_TRANSFER_IN_PROGRESS          (INTERNET_ERROR_BASE + 110)
#define ERROR_FTP_DROPPED                       (INTERNET_ERROR_BASE + 111)
#define ERROR_FTP_NO_PASSIVE_MODE               (INTERNET_ERROR_BASE + 112)

//
// gopher API errors
//

#define ERROR_GOPHER_PROTOCOL_ERROR             (INTERNET_ERROR_BASE + 130)
#define ERROR_GOPHER_NOT_FILE                   (INTERNET_ERROR_BASE + 131)
#define ERROR_GOPHER_DATA_ERROR                 (INTERNET_ERROR_BASE + 132)
#define ERROR_GOPHER_END_OF_DATA                (INTERNET_ERROR_BASE + 133)
#define ERROR_GOPHER_INVALID_LOCATOR            (INTERNET_ERROR_BASE + 134)
#define ERROR_GOPHER_INCORRECT_LOCATOR_TYPE     (INTERNET_ERROR_BASE + 135)
#define ERROR_GOPHER_NOT_GOPHER_PLUS            (INTERNET_ERROR_BASE + 136)
#define ERROR_GOPHER_ATTRIBUTE_NOT_FOUND        (INTERNET_ERROR_BASE + 137)
#define ERROR_GOPHER_UNKNOWN_LOCATOR            (INTERNET_ERROR_BASE + 138)

//
// HTTP API errors
//

#define ERROR_HTTP_HEADER_NOT_FOUND             (INTERNET_ERROR_BASE + 150)
#define ERROR_HTTP_DOWNLEVEL_SERVER             (INTERNET_ERROR_BASE + 151)
#define ERROR_HTTP_INVALID_SERVER_RESPONSE      (INTERNET_ERROR_BASE + 152)
#define ERROR_HTTP_INVALID_HEADER               (INTERNET_ERROR_BASE + 153)
#define ERROR_HTTP_INVALID_QUERY_REQUEST        (INTERNET_ERROR_BASE + 154)
#define ERROR_HTTP_HEADER_ALREADY_EXISTS        (INTERNET_ERROR_BASE + 155)
#define ERROR_HTTP_REDIRECT_FAILED              (INTERNET_ERROR_BASE + 156)
#define ERROR_HTTP_NOT_REDIRECTED               (INTERNET_ERROR_BASE + 160)
#define ERROR_HTTP_COOKIE_NEEDS_CONFIRMATION    (INTERNET_ERROR_BASE + 161)
#define ERROR_HTTP_COOKIE_DECLINED              (INTERNET_ERROR_BASE + 162)
#define ERROR_HTTP_REDIRECT_NEEDS_CONFIRMATION  (INTERNET_ERROR_BASE + 168)

//
// additional Internet API error codes
//

#define ERROR_INTERNET_SECURITY_CHANNEL_ERROR		(INTERNET_ERROR_BASE + 157)
#define ERROR_INTERNET_UNABLE_TO_CACHE_FILE			(INTERNET_ERROR_BASE + 158)
#define ERROR_INTERNET_TCPIP_NOT_INSTALLED			(INTERNET_ERROR_BASE + 159)
#define ERROR_INTERNET_DISCONNECTED					(INTERNET_ERROR_BASE + 163)
#define ERROR_INTERNET_SERVER_UNREACHABLE			(INTERNET_ERROR_BASE + 164)
#define ERROR_INTERNET_PROXY_SERVER_UNREACHABLE		(INTERNET_ERROR_BASE + 165)

#define ERROR_INTERNET_BAD_AUTO_PROXY_SCRIPT		(INTERNET_ERROR_BASE + 166)
#define ERROR_INTERNET_UNABLE_TO_DOWNLOAD_SCRIPT	(INTERNET_ERROR_BASE + 167)
#define ERROR_INTERNET_SEC_INVALID_CERT				(INTERNET_ERROR_BASE + 169)
#define ERROR_INTERNET_SEC_CERT_REVOKED				(INTERNET_ERROR_BASE + 170)

#endif





#ifdef _WINDOWS_SOURCE
#define CATHTTP_QUERY_MIME_VERSION				HTTP_QUERY_MIME_VERSION
#define CATHTTP_QUERY_CONTENT_TYPE				HTTP_QUERY_CONTENT_TYPE
#define CATHTTP_QUERY_CONTENT_TRANSFER_ENCODING	HTTP_QUERY_CONTENT_TRANSFER_ENCODING
#define CATHTTP_QUERY_CONTENT_ID                HTTP_QUERY_CONTENT_ID
#define CATHTTP_QUERY_CONTENT_DESCRIPTION		HTTP_QUERY_CONTENT_DESCRIPTION
#define CATHTTP_QUERY_CONTENT_LENGTH			HTTP_QUERY_CONTENT_LENGTH       
#define CATHTTP_QUERY_CONTENT_LANGUAGE			HTTP_QUERY_CONTENT_LANGUAGE
#define CATHTTP_QUERY_ALLOW                     HTTP_QUERY_ALLOW
#define CATHTTP_QUERY_PUBLIC                    HTTP_QUERY_PUBLIC
#define CATHTTP_QUERY_DATE                      HTTP_QUERY_DATE
#define CATHTTP_QUERY_EXPIRES                   HTTP_QUERY_EXPIRES
#define CATHTTP_QUERY_LAST_MODIFIED             HTTP_QUERY_LAST_MODIFIED
#define CATHTTP_QUERY_MESSAGE_ID                HTTP_QUERY_MESSAGE_ID
#define CATHTTP_QUERY_URI                       HTTP_QUERY_URI
#define CATHTTP_QUERY_DERIVED_FROM              HTTP_QUERY_DERIVED_FROM
#define CATHTTP_QUERY_COST                      HTTP_QUERY_COST
#define CATHTTP_QUERY_LINK                      HTTP_QUERY_LINK
#define CATHTTP_QUERY_PRAGMA                    HTTP_QUERY_PRAGMA
#define CATHTTP_QUERY_VERSION                   HTTP_QUERY_VERSION 
#define CATHTTP_QUERY_STATUS_CODE               HTTP_QUERY_STATUS_CODE 
#define CATHTTP_QUERY_STATUS_TEXT               HTTP_QUERY_STATUS_TEXT 
#define CATHTTP_QUERY_RAW_HEADERS               HTTP_QUERY_RAW_HEADERS
#define CATHTTP_QUERY_RAW_HEADERS_CRLF          HTTP_QUERY_RAW_HEADERS_CRLF
#define CATHTTP_QUERY_CONNECTION                HTTP_QUERY_CONNECTION
#define CATHTTP_QUERY_ACCEPT                    HTTP_QUERY_ACCEPT
#define CATHTTP_QUERY_ACCEPT_CHARSET            HTTP_QUERY_ACCEPT_CHARSET
#define CATHTTP_QUERY_ACCEPT_ENCODING           HTTP_QUERY_ACCEPT_ENCODING
#define CATHTTP_QUERY_ACCEPT_LANGUAGE           HTTP_QUERY_ACCEPT_LANGUAGE
#define CATHTTP_QUERY_AUTHORIZATION             HTTP_QUERY_AUTHORIZATION
#define CATHTTP_QUERY_CONTENT_ENCODING          HTTP_QUERY_CONTENT_ENCODING
#define CATHTTP_QUERY_FORWARDED                 HTTP_QUERY_FORWARDED
#define CATHTTP_QUERY_FROM                      HTTP_QUERY_FROM
#define CATHTTP_QUERY_IF_MODIFIED_SINCE         HTTP_QUERY_IF_MODIFIED_SINCE
#define CATHTTP_QUERY_LOCATION                  HTTP_QUERY_LOCATION
#define CATHTTP_QUERY_ORIG_URI                  HTTP_QUERY_ORIG_URI
#define CATHTTP_QUERY_REFERER                   HTTP_QUERY_REFERER
#define CATHTTP_QUERY_RETRY_AFTER               HTTP_QUERY_RETRY_AFTER
#define CATHTTP_QUERY_SERVER                    HTTP_QUERY_SERVER
#define CATHTTP_QUERY_TITLE                     HTTP_QUERY_TITLE
#define CATHTTP_QUERY_USER_AGENT                HTTP_QUERY_USER_AGENT
#define CATHTTP_QUERY_WWW_AUTHENTICATE          HTTP_QUERY_WWW_AUTHENTICATE
#define CATHTTP_QUERY_PROXY_AUTHENTICATE        HTTP_QUERY_PROXY_AUTHENTICATE
#define CATHTTP_QUERY_ACCEPT_RANGES             HTTP_QUERY_ACCEPT_RANGES
#define CATHTTP_QUERY_SET_COOKIE                HTTP_QUERY_SET_COOKIE
#define CATHTTP_QUERY_COOKIE                    HTTP_QUERY_COOKIE
#define CATHTTP_QUERY_REQUEST_METHOD            HTTP_QUERY_REQUEST_METHOD
#define CATHTTP_QUERY_REFRESH                   HTTP_QUERY_REFRESH
#define CATHTTP_QUERY_CONTENT_DISPOSITION       HTTP_QUERY_CONTENT_DISPOSITION


// HTTP 1.1 defined headers

#define CATHTTP_QUERY_AGE                        HTTP_QUERY_AGE
#define CATHTTP_QUERY_CACHE_CONTROL              HTTP_QUERY_CACHE_CONTROL
#define CATHTTP_QUERY_CONTENT_BASE               HTTP_QUERY_CONTENT_BASE
#define CATHTTP_QUERY_CONTENT_LOCATION           HTTP_QUERY_CONTENT_LOCATION
#define CATHTTP_QUERY_CONTENT_MD5                HTTP_QUERY_CONTENT_MD5
#define CATHTTP_QUERY_CONTENT_RANGE              HTTP_QUERY_CONTENT_RANGE
#define CATHTTP_QUERY_ETAG                       HTTP_QUERY_ETAG
#define CATHTTP_QUERY_HOST                       HTTP_QUERY_HOST
#define CATHTTP_QUERY_IF_MATCH                   HTTP_QUERY_IF_MATCH 
#define CATHTTP_QUERY_IF_NONE_MATCH              HTTP_QUERY_IF_NONE_MATCH
#define CATHTTP_QUERY_IF_RANGE                   HTTP_QUERY_IF_RANGE
#define CATHTTP_QUERY_IF_UNMODIFIED_SINCE        HTTP_QUERY_IF_UNMODIFIED_SINCE
#define CATHTTP_QUERY_MAX_FORWARDS               HTTP_QUERY_MAX_FORWARDS
#define CATHTTP_QUERY_PROXY_AUTHORIZATION        HTTP_QUERY_PROXY_AUTHORIZATION
#define CATHTTP_QUERY_RANGE                      HTTP_QUERY_RANGE
#define CATHTTP_QUERY_TRANSFER_ENCODING          HTTP_QUERY_TRANSFER_ENCODING
#define CATHTTP_QUERY_UPGRADE                    HTTP_QUERY_UPGRADE
#define CATHTTP_QUERY_VARY                       HTTP_QUERY_VARY
#define CATHTTP_QUERY_VIA                        HTTP_QUERY_VIA 
#define CATHTTP_QUERY_WARNING                    HTTP_QUERY_WARNING  

#define CATHTTP_QUERY_MAX                        HTTP_QUERY_MAX
#define CATHTTP_QUERY_CUSTOM                     HTTP_QUERY_CUSTOM 
#define CATHTTP_QUERY_FLAG_NUMBER                HTTP_QUERY_FLAG_NUMBER

#else //Unix

#define CATHTTP_QUERY_MIME_VERSION                 0
#define CATHTTP_QUERY_CONTENT_TYPE                 1
#define CATHTTP_QUERY_CONTENT_TRANSFER_ENCODING    2
#define CATHTTP_QUERY_CONTENT_ID                   3
#define CATHTTP_QUERY_CONTENT_DESCRIPTION          4
#define CATHTTP_QUERY_CONTENT_LENGTH               5
#define CATHTTP_QUERY_CONTENT_LANGUAGE             6
#define CATHTTP_QUERY_ALLOW                        7
#define CATHTTP_QUERY_PUBLIC                       8
#define CATHTTP_QUERY_DATE                         9
#define CATHTTP_QUERY_EXPIRES                      10
#define CATHTTP_QUERY_LAST_MODIFIED                11
#define CATHTTP_QUERY_MESSAGE_ID                   12
#define CATHTTP_QUERY_URI                          13
#define CATHTTP_QUERY_DERIVED_FROM                 14
#define CATHTTP_QUERY_COST                         15
#define CATHTTP_QUERY_LINK                         16
#define CATHTTP_QUERY_PRAGMA                       17
#define CATHTTP_QUERY_VERSION                      18 
#define CATHTTP_QUERY_STATUS_CODE                  19 
#define CATHTTP_QUERY_STATUS_TEXT                  20 
#define CATHTTP_QUERY_RAW_HEADERS                  21  // all headers as ASCIIZ
#define CATHTTP_QUERY_RAW_HEADERS_CRLF             22  // special: all headers
#define CATHTTP_QUERY_CONNECTION                   23
#define CATHTTP_QUERY_ACCEPT                       24
#define CATHTTP_QUERY_ACCEPT_CHARSET               25
#define CATHTTP_QUERY_ACCEPT_ENCODING              26
#define CATHTTP_QUERY_ACCEPT_LANGUAGE              27
#define CATHTTP_QUERY_AUTHORIZATION                28
#define CATHTTP_QUERY_CONTENT_ENCODING             29
#define CATHTTP_QUERY_FORWARDED                    30
#define CATHTTP_QUERY_FROM                         31
#define CATHTTP_QUERY_IF_MODIFIED_SINCE            32
#define CATHTTP_QUERY_LOCATION                     33
#define CATHTTP_QUERY_ORIG_URI                     34
#define CATHTTP_QUERY_REFERER                      35
#define CATHTTP_QUERY_RETRY_AFTER                  36
#define CATHTTP_QUERY_SERVER                       37
#define CATHTTP_QUERY_TITLE                        38
#define CATHTTP_QUERY_USER_AGENT                   39
#define CATHTTP_QUERY_WWW_AUTHENTICATE             40
#define CATHTTP_QUERY_PROXY_AUTHENTICATE           41
#define CATHTTP_QUERY_ACCEPT_RANGES                42
#define CATHTTP_QUERY_SET_COOKIE                   43
#define CATHTTP_QUERY_COOKIE                       44
#define CATHTTP_QUERY_REQUEST_METHOD               45  // special: GET/POST etc.
#define CATHTTP_QUERY_REFRESH                      46
#define CATHTTP_QUERY_CONTENT_DISPOSITION          47


// HTTP 1.1 defined headers

#define CATHTTP_QUERY_AGE                          48
#define CATHTTP_QUERY_CACHE_CONTROL                49
#define CATHTTP_QUERY_CONTENT_BASE                 50
#define CATHTTP_QUERY_CONTENT_LOCATION             51
#define CATHTTP_QUERY_CONTENT_MD5                  52
#define CATHTTP_QUERY_CONTENT_RANGE                53
#define CATHTTP_QUERY_ETAG                         54
#define CATHTTP_QUERY_HOST                         55
#define CATHTTP_QUERY_IF_MATCH                     56
#define CATHTTP_QUERY_IF_NONE_MATCH                57
#define CATHTTP_QUERY_IF_RANGE                     58
#define CATHTTP_QUERY_IF_UNMODIFIED_SINCE          59
#define CATHTTP_QUERY_MAX_FORWARDS                 60
#define CATHTTP_QUERY_PROXY_AUTHORIZATION          61
#define CATHTTP_QUERY_RANGE                        62
#define CATHTTP_QUERY_TRANSFER_ENCODING            63
#define CATHTTP_QUERY_UPGRADE                      64
#define CATHTTP_QUERY_VARY                         65
#define CATHTTP_QUERY_VIA                          66
#define CATHTTP_QUERY_WARNING                      67

#define CATHTTP_QUERY_MAX                          67
#define CATHTTP_QUERY_CUSTOM                       65535
#define CATHTTP_QUERY_FLAG_NUMBER                  0x20000000
#endif

#define CATHTTP_QUERY_RAW_HEADERS_CRLF_UPPER       128


#define CATHTTP_QUERY_ALL		CATHTTP_QUERY_RAW_HEADERS_CRLF

//Global option to manage Async mode.
#define CATHTTP_OPTION_SET_CALLBACK					10000
#define CATHTTP_OPTION_BODY_MODE					10001
#define CATHTTP_OPTION_SET_CALLBACK_AUTO_DELETE		10002
#define	CATHTTP_OPTION_SET_HTTPREQUEST_END_EVENT	10003
#define CATHTTP_OPTION_SET_PERFO_CALLBACK			10004
#define CATHTTP_OPTION_NO_AUTH_CHECK				10005

//Global options Unix/Windows.
#define CATHTTP_OPTION_DOWNLOAD_LIMITATION			10100
#define CATHTTP_OPTION_UPLOAD_LIMITATION			10101

//Options 
#ifndef _WINDOWS_SOURCE
#define CATHTTP_OPTION_CALLBACK					1
#define CATHTTP_OPTION_CONNECT_TIMEOUT			2
#define INTERNET_OPTION_CONNECT_TIMEOUT			CATHTTP_OPTION_CONNECT_TIMEOUT //SIP: OLD naming error
#define CATHTTP_OPTION_CONNECT_RETRIES			3
#define CATHTTP_OPTION_CONNECT_BACKOFF			4
#define CATHTTP_OPTION_SEND_TIMEOUT				5
#define CATHTTP_OPTION_CONTROL_SEND_TIMEOUT		CATHTTP_OPTION_SEND_TIMEOUT
#define INTERNET_OPTION_SEND_TIMEOUT			CATHTTP_OPTION_SEND_TIMEOUT //SIP: OLD naming error
#define CATHTTP_OPTION_RECEIVE_TIMEOUT			6
#define CATHTTP_OPTION_CONTROL_RECEIVE_TIMEOUT	CATHTTP_OPTION_RECEIVE_TIMEOUT
#define INTERNET_OPTION_RECEIVE_TIMEOUT			CATHTTP_OPTION_RECEIVE_TIMEOUT //SIP: OLD naming error
#define CATHTTP_OPTION_DATA_SEND_TIMEOUT		7
#define CATHTTP_OPTION_DATA_RECEIVE_TIMEOUT		8
#define CATHTTP_OPTION_HANDLE_TYPE				9
#define CATHTTP_OPTION_LISTEN_TIMEOUT			11

#define CATHTTP_OPTION_READBUFFER				12
#define CATHTTP_OPTION_WRITEBUFFER				13
#define CATHTTP_OPTION_USERNAME					28
#define CATHTTP_OPTION_PASSWORD					29
#define CATHTTP_OPTION_SECURITY					31
#define CATHTTP_OPTION_PROXY					38
#define CATHTTP_OPTION_PROXY_USERNAME			43
#define CATHTTP_OPTION_PROXY_PASSWORD			44
#define CATHTTP_OPTION_HTTP_DECODING			65


#else

#define CATHTTP_OPTION_CALLBACK					INTERNET_OPTION_CALLBACK
#define CATHTTP_OPTION_CONNECT_TIMEOUT			INTERNET_OPTION_CONNECT_TIMEOUT
#define CATHTTP_OPTION_CONNECT_RETRIES			INTERNET_OPTION_CONNECT_RETRIES
#define CATHTTP_OPTION_CONNECT_BACKOFF			INTERNET_OPTION_CONNECT_BACKOFF
#define CATHTTP_OPTION_SEND_TIMEOUT				INTERNET_OPTION_SEND_TIMEOUT
#define CATHTTP_OPTION_CONTROL_SEND_TIMEOUT		INTERNET_OPTION_SEND_TIMEOUT
#define CATHTTP_OPTION_RECEIVE_TIMEOUT			INTERNET_OPTION_RECEIVE_TIMEOUT
#define CATHTTP_OPTION_CONTROL_RECEIVE_TIMEOUT	INTERNET_OPTION_RECEIVE_TIMEOUT
#define CATHTTP_OPTION_DATA_SEND_TIMEOUT		INTERNET_OPTION_DATA_SEND_TIMEOUT
#define CATHTTP_OPTION_DATA_RECEIVE_TIMEOUT		INTERNET_OPTION_DATA_RECEIVE_TIMEOUT
#define CATHTTP_OPTION_HANDLE_TYPE				INTERNET_OPTION_HANDLE_TYPE
#define CATHTTP_OPTION_LISTEN_TIMEOUT			INTERNET_OPTION_LISTEN_TIMEOUT

#define CATHTTP_OPTION_READBUFFER				INTERNET_OPTION_READ_BUFFER_SIZE
#define CATHTTP_OPTION_WRITEBUFFER				INTERNET_OPTION_WRITE_BUFFER_SIZE
#define CATHTTP_OPTION_SECURITY					INTERNET_OPTION_SECURITY_FLAGS
#define CATHTTP_OPTION_CONNECT_TYPE				INTERNET_OPEN_TYPE_DIRECT
#define CATHTTP_OPTION_PROXY					INTERNET_OPTION_PROXY
#define CATHTTP_OPTION_PROXY_USERNAME			INTERNET_OPTION_PROXY_USERNAME
#define CATHTTP_OPTION_PROXY_PASSWORD			INTERNET_OPTION_PROXY_PASSWORD
#define CATHTTP_OPTION_USERNAME					INTERNET_OPTION_USERNAME
#define CATHTTP_OPTION_PASSWORD					INTERNET_OPTION_PASSWORD
#define CATHTTP_OPTION_HTTP_DECODING			INTERNET_OPTION_HTTP_DECODING

#endif

#define CATHTTP_OPTION_LAST_REDIRECT_URL		5000


#endif