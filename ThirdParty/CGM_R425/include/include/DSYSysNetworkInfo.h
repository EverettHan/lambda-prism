// COPYRIGHT DASSAULT SYSTEMES 2010
#ifndef DSYSysNetworkInfo_H
#define DSYSysNetworkInfo_H


#include <unistd.h>

#ifdef _WINDOWS_SOURCE
#define HOST_NAME_MAX 256
#include <Winsock2.h>
#else // _WINDOWS_SOURCE
# ifdef _ANDROID_SOURCE
#   define HOST_NAME_MAX 256
# endif // _ANDROID_SOURCE
#endif

#ifdef _SUNOS_SOURCE
#include <netdb.h>
#endif //_SUNOS_SOURCE

#ifdef _AIX_SOURCE
#include <sys/limits.h>
#endif

#ifdef _LINUX_SOURCE
#include <bits/local_lim.h>
#endif

#include "CATSysTS.h"
#include "CATSysDataType.h"


//Function to get the ethernet address of the first interface of the computer.
ExportedByCATSysTS	ULONG get_ethernet_address();


typedef struct DSYSysNetworkInfoList
{
	char							*IfName;
	bool							IsV4;
	bool							IsV6;
	char							Hw_Addr[6];
	unsigned char					Ip_V4[4];
	unsigned short					Ip_V6[8];
	struct DSYSysNetworkInfoList	*Next;
	struct DSYSysNetworkInfoList	*Last;
} S_DSYSysNetworkInfoList;


class ExportedByCATSysTS DSYSysNetworkInfo
{
private:
	S_DSYSysNetworkInfoList	*_IfList;
	S_DSYSysNetworkInfoList	*_IfListCurrent;
	S_DSYSysNetworkInfoList	*_IfListDefault;
	S_DSYSysNetworkInfoList	*_IfListFirstMAC;
#ifdef _MACOSX_SOURCE
	char					_HostName[_SC_HOST_NAME_MAX + 1];
#else
#ifdef _SUNOS_SOURCE
	char					_HostName[MAXHOSTNAMELEN + 1];
#else
	char					_HostName[HOST_NAME_MAX + 1];
#endif
#endif
	
	
protected:
	int							GetIFName(char *CurIF, S_DSYSysNetworkInfoList *Iftmp);
#ifndef _WINDOWS_SOURCE
	int							GetMACAddr(S_DSYSysNetworkInfoList *Iftmp, char *iIFName);
#if defined (_AIX_SOURCE) || defined (_SUNOS_SOURCE)
	int							GetIPAddress(int sockfd, S_DSYSysNetworkInfoList *Iftmp, char *iIFName, unsigned short iFamily);
#else
	int							GetIPAddress(S_DSYSysNetworkInfoList *Iftmp, char *iIFName, unsigned short iFamily);
#endif
#endif //!_WINDOWS_SOURCE
	int							Init();
	
	
public:
	DSYSysNetworkInfo();
	~DSYSysNetworkInfo();

	int							GetFirstInterfaceWithMAC(char *&oInterface);

	int							GetDefaultHostName(char *&oHostname);
	/*
	 for the moment just return the first interfac with an IP (V4 or V6) and a macaddr on Unix.
	 And the fist IF of ethernet type and active on windows
	*/
	int							GetDefaultInterface(char *&oInterface);
	
	/* int GetFirstIf(char *&oIfName)
	 Methode to get the name of the first network interface.
	 Params:
	 oIfName: Name of the first network interface. This value can be null if no interface are found. Return value cannot be deleted or freed and have to be duplicated by caller if caller wants to keep it.
	 return value:
	 Methode return 0 if no error occurs. Else it will return a negativ value to determine the error type (default is -1)
	 Errors are HRESULT when the root cause of the error has been determinated.
	 */
	int							GetFirstIf(char *&oIfName);
	
	/* int GetNextIf(char *&oIfName)
	 Methode to get the name of the next network interface. Return value cannot be deleted or freed and have to be duplicated by caller if caller wants to keep it.
	 Params:
	 oIfName: Name of the next network interface. This value can be null if there to more network interfaces.
	 return value:
	 Methode return 0 if no error occurs. Else it will return a negativ value to determine the error type (default is -1)
	 Errors are HRESULT when the root cause of the error has been determinated.
	 */
	int							GetNextIf(char *&oIfName);
	int							FreeListOfInterface(char ***oList);
	int							GetIP(unsigned char &a1, unsigned char &a2, unsigned char &a3, unsigned char &a4);
	int							GetIP(char oIP[16]);
	int							GetIPV6(unsigned char &a1, unsigned char &a2, unsigned char &a3, unsigned char &a4, unsigned char &a5, unsigned char &a6, unsigned char &a7, unsigned char &a8,
										unsigned char &a9, unsigned char &a10, unsigned char &a11, unsigned char &a12, unsigned char &a13, unsigned char &a14, unsigned char &a15, unsigned char &a16);
	int							GetIPV6(unsigned short &a1, unsigned short &a2, unsigned short &a3, unsigned short &a4, unsigned short &a5, unsigned short &a6, unsigned short &a7, unsigned short &a8);
	int							GetIPV6(char oIP[48]);
	int							GetMAC(int &a1, int &a2, int &a3, int &a4, int &a5, int &a6);
	int							GetMAC(char oMAC[18]);
	bool						IsIPV4();
	bool						IsIPV6();
//	static DSYSysNetworkInfo*	GetDSYSysNetworkInfo();
};

#endif // DSYSysNetworkInfo_H
