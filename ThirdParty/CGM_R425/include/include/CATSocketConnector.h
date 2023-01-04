#ifndef CATSocketConnector_H 
#define CATSocketConnector_H 


// COPYRIGHT DASSAULT SYSTEMES 2000

//====================================================
//=== INCLUDES =======================================
//====================================================
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#ifdef _WINDOWS_SOURCE
#include <winsock.h>
#include <wininet.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/param.h>
#endif
#include <fcntl.h>

#include "JS0MT00.h"
#include "CATDataType.h"
#include <CATUniStd.h>

//====================================================
//=== CONSTANTS ======================================
//====================================================
#define CATSOCK_SRV_READY                0x0000
#define CATSOCK_SRV_INIT                 0x1001
#define CATSOCK_SRV_FAILURE              0x1002
#define CATSOCK_SRV_OK                   0x0000
#define CATSOCK_INVALID_OBJECT           0x1003
#define CATSOCK_SRV_STILL_IN_ACCEPT      0x1004
#define CATSOCK_SRV_FAIL_IN_SOCK         0x2002
#define CATSOCK_SRV_FAIL_IN_SETSOPT      0x2003
#define CATSOCK_SRV_FAIL_IN_BIND         0x2004
#define CATSOCK_SRV_FAIL_IN_LISTEN       0x2005
#define CATSOCK_SRV_FAIL_IN_GETSNAM      0x2006
#define CATSOCK_SRV_FAIL_IN_ACCEPT       0x2007
#define CATSOCK_SRV_FAIL_STS_ACCEPT      0x2008
#define CATSOCK_SRV_FAIL_ARG_INVAL       0x2009
#define CATSOCK_SRV_NOT_DECLARED         0x200a


#define CATSOCK_USE_OS_MAX_VALUE         0x7fffffff
//====================================================
//=== TYPEDEFS  ======================================
//====================================================
typedef int  CATSocketResult; // to return a  result
//Ia64C#ifdef _WINDOWS_SOURCE
//Ia64Ctypedef SOCKET  CATSocketHandler;
//Ia64C#else 
//Ia64Ctypedef int CATSocketHandler ;
//Ia64C#endif
//Ia64+
typedef int CATSocketHandler;
//Ia64-

//====================================================
//=== FORWARDED CLASSES ==============================
//====================================================
class CATSockets;

//====================================================
//=== DATA STRUCTURE    ==============================
//====================================================
struct CATSocketData
{
};


//====================================================
//=== CATSocketConnector class ==========================
//====================================================
class ExportedByJS0MT00 CATSocketConnector
{
public:
	CATSocketConnector(unsigned short int iPort = 0, int _QueuedClients = 10, int iFamily = AF_INET);
	~CATSocketConnector();
	CATSocketResult		Declare(const char* adrs = NULL); // declare myself as server
	unsigned short int	GetPort(); // Get port if available
	CATSocketHandler	GetHandler(); // Get handler if available
	int					GetStatus(); // Get current status of socket server
	int					Accept(CATSockets **); // Get current status of socket server
	CATSocketResult		DeclareAs(const char *iServName, unsigned short *oPort, int DoDeclare = -1, const char *iProt = "tcp");
	int					Select(int *iTimeOut = NULL); // en ms - Null infini

protected:
	virtual CATSockets	*NewCATSockets(CATSocketHandler iSock = -1, CATSocketConnector *iParent = nullptr);

private:
	CATSocketData		*_Data;
};
#endif
