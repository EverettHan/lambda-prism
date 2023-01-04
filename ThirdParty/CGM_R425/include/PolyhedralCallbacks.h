#ifdef _STATIC_SOURCE
#define	ExportedByPolyhedralCallbacks
#elif defined(__PolyhedralCallbacks)
#define ExportedByPolyhedralCallbacks DSYExport
#else
#define ExportedByPolyhedralCallbacks DSYImport
#endif
#include "DSYExport.h"
