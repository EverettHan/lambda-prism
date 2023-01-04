#ifdef _STATIC_SOURCE
#define	ExportedByDisconnect
#elif defined __Disconnect
#define ExportedByDisconnect DSYExport
#else
#define ExportedByDisconnect DSYImport
#endif
#include "DSYExport.h"
//------------------------------------------------------------------------------
