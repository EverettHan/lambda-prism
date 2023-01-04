#ifdef _STATIC_SOURCE
#define	ExportedByPolyFunctions
#elif defined(__PolyFunctions)
#define ExportedByPolyFunctions DSYExport
#else
#define ExportedByPolyFunctions DSYImport
#endif
#include "DSYExport.h"
