#ifndef CATSysHTTPRelay_H
#define CATSysHTTPRelay_H

#include "JS0MT.h"

class CATSockets;
#define MAX_BUFFER_SIZE 8192
#define MAX_HEADER_NUMBER 64
#define CONTENT_LENGTH "Content-Length"
#define TRANSFER_ENCODING "Transfer-Encoding"
#define CRLF "\r\n"
#define RELAY_NO_ERROR 0
#define RELAY_ERROR_SOCKET 1
#define RELAY_ERROR_HEADER 2
#define RELAY_ERROR_TIMEOUT 3
#define RELAY_ERROR_MEMORY 4
#define RELAY_ERROR_FORWARD 5

class CATSysHTTPRelayHelper {
	public:
		virtual int ReadFromClient(char* buffer, int iSize, int& oReceived) = 0;
		virtual int ReadFromServer(char* buffer, int iSize, int& oReceived) = 0;
		virtual int WriteToClient(const char* buffer, int iSize) = 0;
		virtual int WriteToServer(const char* buffer, int iSize) = 0;
};

/**
 * Class used by SDAM to relay HTTP messages from clients to servers
 * 
 * limitations:
 * . only POST and GET request types are supported
 * . total header size including trailing \r\n cannot exceed MAX_HEADER_SIZE
 * . number of headers may not exceed MAX_HEADER_NUMBER
 */
class ExportedByJS0MT CATSysHTTPRelay {

	public:
		CATSysHTTPRelay();
		virtual ~CATSysHTTPRelay();

		/**
		 * Get URL and headers from client
		 * @param iClient: client socket
		 * @param oMethod: method of the request ( only POST and GET are supported )
		 * @param oURL: URL of the request containing parameters
		 * @param oHeaderNames list of header names
		 * @param oHeaderValues list of header values
		 * @param oNbHeaders size of previous lists
		 * @return return code ( 0: OK, 1: communication problem, 2: invalid headers )
		 */
		int GetRequestHeaders(CATSockets* iClient, char*& oMethod, char*& oURL, char**& oHeaderNames, char**& oHeaderValues, int& oNbHeaders);

		/**
		 * Get the body of the request
		 * @param oBody: body content ( must be deallocated whith delete[] ) NULL if no body
		 * @param oBodyLength size of the body
		 * @return return code ( 0: OK, 1: communication problem, 4: memory problem)
		 */
		int GetRequestBody(char*& oBody, int& oBodyLength);

		/**
		 * Forward request to server
		 * @param iServer: server socket
		 * @param iURL: new URL of the request
		 * @param iHeaderNames list of header names
		 * @param iHeaderValues list of header values
		 * @param iNbHeaders size of previous lists
		 * @param iCookieLines list of cookies
		 * @param iNbCookies number of cookies
		 * @param iTimeout timeout for waiting server response
		 * @param iTimeoutFct timeout procedure called to wait for server response; this function returns 1 if operation must be canceled 0 else
		 * @param iTimeoutData argument passed to iTimeoutFct
		 * @return return code ( 0: OK, 1: communication problem, 2: invalid headers, 3: timeout, 5: socket error when responding to client)
		 */
		int Forward(CATSockets* iServer, const char *iHost, const char* iURI, char** iHeaderNames, char** iHeaderValues, int iNbHeaders, char** iCookieLines, int iNbCookies, int iTimeout, int (*iTimeoutFct)(void*) = 0, void* iTimeoutData = 0);
		int Forward(CATSockets* iServer, const char *iHost, const char* iURI, char** iHeaderNames, char** iHeaderValues, int iNbHeaders, int iTimeout, int (*iTimeoutFct)(void*) = 0, void* iTimeoutData = 0) {
			return Forward(iServer, iHost, iURI, iHeaderNames, iHeaderValues, iNbHeaders, 0, 0, iTimeout, iTimeoutFct, iTimeoutData);
		}

		/**
		 * Get URL and headers from client from a previous GetRequestHeaders
		 * @param oMethod: method of the request ( only POST and GET are supported )
		 * @param oURL: URL of the request containing parameters
		 * @param oHeaderNames list of header names
		 * @param oHeaderValues list of header values
		 * @param oNbHeaders size of previous lists
		 * @return return code ( 0: OK, 2: data lost )
		 */
		int RetrieveRequestHeaders(char*& oMethod, char*& oURL, char**& oHeaderNames, char**& oHeaderValues, int& oNbHeaders);

		void SetHelper(CATSysHTTPRelayHelper* helper);

	private:
		int GetWholeHeader(int iFromClient, CATSockets* socket, char* buffer, int& oSize, int& oNbHeaders, int& oInitialBodyLength); 
		int TransferWithContentLengthMode(int iFromClient, CATSockets* iSrc, CATSockets* iDst, int contentLength, char* initialData, int initialLength);
		int TransferWithChunkedMode(int iFromClient, CATSockets* iSrc, CATSockets* iDst, char* initialData, int initialLength);
		int RelayDataBlock(int iFromClient, CATSockets* iSrc, CATSockets* iDst, char* buffer, int iSize, int& oReceived);
		int GetBodyWithChunkedMode(char*& oBody, int& oBodyLength);
		int GetBodyWithContentLengthMode(char*& oBody, int& oBodyLength);

		int SocketRead(int iFromClient, CATSockets* iSocket, char* buffer, int iSize, int& oReceived);
		int SocketWrite(int iFromClient, CATSockets* iSocket, const char* buffer, int iSize);

		char _clientBuffer[MAX_BUFFER_SIZE];
		char* _headers[MAX_HEADER_NUMBER+1];
		char* _clientHeaderNames[MAX_HEADER_NUMBER];
		char* _clientHeaderValues[MAX_HEADER_NUMBER];
		int _nbHeaders;
		int _clientHeaderSize;
		int _initialBodyLength;
		int _contentLength;
		char _bChunkEncoding;
		char _bPost;
		char _bGet;
		char _bHead;
		char _bPut;
		char _bBodyRetrieved;

		//SIP: For TIMEOUT of HTTPRelay. This value indicate the timeout to recieve data from the server
		int _RelayTimeout;

		
		CATSockets *_client;
		CATSysHTTPRelayHelper *_helper;
};
#endif
