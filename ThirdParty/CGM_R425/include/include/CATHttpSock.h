#ifndef CATHttpSock_H
#define CATHttpSock_H

#include <atomic>

#define SIZEBUFFER_READING 65536
#define SLINE	1024
//#define SBUFF   65536

#ifndef DSSocket
#ifdef _WINDOWS_SOURCE
#define DSSocket	SOCKET
#else
#define DSSocket	int
#endif
#endif



class ExportedByJS0HTTP CATBaseSock 
{
public:
	CATBaseSock(unsigned int lDirverID);
	virtual ~CATBaseSock();

	// Methodes de reception/emission basiques
	virtual int		Send(char *iBuffer, size_t iLen) = 0;
	virtual int		Receive(char *iBuffer, size_t iLen, size_t *oLu) = 0;
	virtual int		ReceiveLine(char *iBuffer, size_t iLen, size_t *oLu) = 0;
	virtual int		ReceiveHeader(char **iBuffer, size_t *iLen) = 0;
	virtual int		ReceiveFromBuff(char *iBuffer, size_t iLen) = 0;
	virtual	int		ReceiveNetwork() = 0;
	virtual int		GetOptions(DWORD iOption, void *oBuffer, int *ioLen) = 0;
	virtual int		SetOptions(DWORD iOption, void *iBuffer, int iLen) = 0;


	virtual int CloseConnection();
	virtual int Wait(int iTm)=0;
	virtual int IsSocketAlive() = 0;

	// traitement dedie des transmissions sur http
	virtual int KeepReading(char **oBuffer, size_t *oLu);
	// methode d'Analyse
	virtual int AnalyseChunks(char **EntityBody, size_t *oTotalLen, int iFlag=0);
	// Reception du header de response 
	virtual int GetResponseHeader(char **oResponse, size_t *oLen);
	// Reception du body
	virtual int GetBody(int iTransfert, size_t *ioLenResponse, char **oBody);

	virtual HRESULT	SetBodyType(CATULONG64 iBodyTypeOrSize);
	virtual bool	IsTheEndReached();
	virtual void	SetTheEndReached(bool iIsTheEndReached);

	char					*_HostName;	// host ou on a contacte le serveur
	short					_Port;
	short					_Status;	// Statut courant
	char					_Lbuff[SIZEBUFFER_READING];
	unsigned int			_LbuffSize;
	char					*_CurPos;
	size_t					_CurChunkLen;
	size_t					_CurChunkPos;
	CATULONG64				_TotalRcv;
	std::atomic_ullong		_TotalRcvHeader;
	CATULONG64				_TotalRcvBody;
protected:
	void	Trace(char * EntityBody, size_t TotLenRecue, int text, void *lMyHttpTrace);
	HRESULT	ReturnHRDumpData(void *lMyTrace, const char *iMetName, const char *iFonction, HRESULT hr, char * EntityBody, size_t TotLenRecue);

	std::atomic<long long>	_ReceptionMode;
	bool					_IsTheEndReached;
	void					*_MyHttpTrace;
	unsigned int			_DriverID;
public:
	virtual bool			IsSSLErrorRetryable(void *issl, int iret, const char *iMethName, const char* iSSLMethName) { return false; };
};



class ExportedByJS0HTTP CATHttpSock : public CATBaseSock
{
public:
	CATHttpSock(unsigned int lDriverID);
	virtual ~CATHttpSock();

	//
	virtual int Connect (const char *iHostName, unsigned short iPort,
		const char *iProxy, unsigned short iProxyPort, 
		int iFlags);

	// Methodes de reception/emission basiques
	virtual int		Send(char *iBuffer, size_t iLen);
	virtual int		Receive(char *iBuffer, size_t iLen, size_t *oLu);
	virtual int		ReceiveLine(char *iBuffer, size_t iLen, size_t *oLu);
	virtual int		ReceiveHeader(char **iBuffer, size_t *iLen);
	virtual int		ReceiveFromBuff(char *iBuffer, size_t iLen);
	virtual	int		ReceiveNetwork();

	virtual int		CloseConnection();
	virtual int		Wait(int iTm);
	virtual int		IsSocketAlive();
	virtual int		GetOptions(DWORD iOption, void *oBuffer, int *ioLen);
	virtual int		SetOptions(DWORD iOption, void *iBuffer, int iLen);

	virtual	int		ConnectHTTP(const char *iHostName, unsigned short iPort, const char *iProxy, unsigned short iProxyPort,	int iFlags);

	ULONG			_ReceiveTimeout;
	ULONG			_SendTimeout;

	DSSocket		_Sock;

protected:
	HRESULT			Init();
	bool			_IsTunnelMode;
};

#endif
