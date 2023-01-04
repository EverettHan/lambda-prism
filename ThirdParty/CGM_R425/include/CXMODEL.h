#ifdef _STATIC_SOURCE
#define	ExportedByCXMODEL
#elif defined __CXMODEL
#define ExportedByCXMODEL DSYExport
#else
#define ExportedByCXMODEL DSYImport
#endif
#include "DSYExport.h"
