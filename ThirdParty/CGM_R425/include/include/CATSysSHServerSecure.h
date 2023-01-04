#ifndef CATSysSHServerSecure_H
#define CATSysSHServerSecure_H

//no CATUnicodeString because of circular dependency between CATSysTS CATSysMultiThreading but char * can be UTF-8
//#include "DSYString.h"
#include "CATSysErrorDef.h"
#include "CATSysSHServer.h"

#if defined(__CATSysMultiThreadingSecured)
# define ExportedByCATSysMultiThreadingSecured  DSYExport
#else  // __JS0MT
# define ExportedByCATSysMultiThreadingSecured  DSYImport
#endif // __JS0MT


class ExportedByCATSysMultiThreadingSecured CATSysSHServerSecure : public CATSysSHServer
{
	CATSysSHServerSecure();

public:
	~CATSysSHServerSecure();

	/**
	 ** Create allows to instanciante a CATSysSHServerSecure server
	 ** Returns NULL a problem occured
	 **/
	//no CATUnicodeString because of circular dependency between CATSysTS CATSysMultiThreading but char * can be UTF-8
	//static CATSysSHServer* Create(unsigned short iPort, CATUnicodeString iCertPath, CATUnicodeString iKeyPath, const char* iInterface = nullptr, const char *iAlgo = nullptr);
	static CATSysSHServer* Create(unsigned short iPort, const char *iCertPath, const char *iKeyPath, const char* iInterface = nullptr, const char *iAlgo = nullptr);
};

extern "C" ExportedByCATSysMultiThreadingSecured CATSockets *funcGetSecuredSockets(CATSockets *iSock, const char *iCertPath, const char *iKeyPath, const char* iAlgo);


#endif
