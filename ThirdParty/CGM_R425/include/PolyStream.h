#ifdef _STATIC_SOURCE
#define	ExportedByPolyStream
#elif defined(__PolyStream)
#define ExportedByPolyStream DSYExport
#else
#define ExportedByPolyStream DSYImport
#endif
#include "DSYExport.h"
