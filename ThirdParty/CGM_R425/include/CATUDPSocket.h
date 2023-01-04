#ifndef CATUDPSocket_H 
#define CATUDPSocket_H 


// COPYRIGHT DASSAULT SYSTEMES 2002

//====================================================
//=== INCLUDES =======================================
//====================================================
#include "JS0MT.h"
#include "CATErrorDef.h"

#ifdef _WINDOWS_SOURCE
#include <winsock.h>
#include <wininet.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/param.h>
#endif


#include "CATSocketConnector.h"

#define MAX_UDP_BUFFER_SIZE 1024
#define MCAST_BUFFER_SIZE	1024



//====================================================
//=== CATUDPSocket class  ==============================
//====================================================
class ExportedByJS0MT CATUDPSocket
{

  public:
  CATUDPSocket();
  virtual ~CATUDPSocket();

  CATSocketResult Initialize(const char* local_address, unsigned short port, const char* bcast_address=NULL);
 
  CATSocketResult SetSendingAddress(const char* snd_address, unsigned short port=0); //port=0 <=> port = port du Initialize
  CATSocketResult Send(char *iBuffer, unsigned int iLen);
  CATSocketResult Receive(char *iBuffer, unsigned int iBufLen, unsigned int *oRealLen);
  HRESULT GetLastReceivedAddress(char* hostname, int& port);



  int GetFd()	{return _fdsock;}

  private :

	  CATSocketResult SetBroadcast(const char* bcast_address);

	  struct sockaddr_in _localAddress;
	  struct sockaddr_in _sendingAddress;
	  struct sockaddr _receivedAddress;
	  int _fdsock;


};
#endif
