#ifdef _STATIC_SOURCE
#define	ExportedByPolySupports
#elif defined(__PolySupports)
#define ExportedByPolySupports DSYExport
#else
#define ExportedByPolySupports DSYImport
#endif
#include "DSYExport.h"
