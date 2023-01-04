#ifdef _STATIC_SOURCE
#define	ExportedByPolyMODEL
#elif defined __PolyMODEL
#define ExportedByPolyMODEL DSYExport
#else
#define ExportedByPolyMODEL DSYImport
#endif
#include "DSYExport.h"
