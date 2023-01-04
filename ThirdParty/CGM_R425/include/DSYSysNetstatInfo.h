#ifndef _DSYSysNetstatInfo_H
#define _DSYSysNetstatInfo_H

//SIP: copy of JS0MT.h because this is a public .h

#if defined(__JS0MT)
# define ExportedByJS0MTLocal  DSYExport
#else  // __JS0MT
# define ExportedByJS0MTLocal  DSYImport
#endif // __JS0MT

/************************************************************************/
/* Local includes                                                       */
/************************************************************************/
#include "DSYExport.h"

#ifdef DSYINSTARCH /* Utilisation archive */
#undef  ExportedByJS0MTLocal  
#define ExportedByJS0MTLocal  
#endif

#ifdef HTTPARCH /* Utilisation archive */
#undef  ExportedByJS0MTLocal  
#define ExportedByJS0MTLocal  
#endif

#include "CATSysDataType.h"

class ExportedByJS0MTLocal DSYSysNetstatInfo
{
public:
	DSYSysNetstatInfo();
	~DSYSysNetstatInfo();
	unsigned int	GetFreePort();
	unsigned int	GetLocalFreePort();
	unsigned int	GetNextFreePort(unsigned int iPort);
	bool		IsPortNumberFree(unsigned int iPort, int iProtocol);
	bool		IsLocalPortNumberFree(unsigned int iPort, int iProtocol);
	unsigned int	GetNextLocalFreePort(unsigned int iPort);
	unsigned int	_iPort; //Fake param to test dll missmatch
};


#endif
