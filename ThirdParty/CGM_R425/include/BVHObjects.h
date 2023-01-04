#ifdef _STATIC_SOURCE
#define	ExportedByBVHObjects
#elif defined(__BVHObjects)
#define ExportedByBVHObjects DSYExport
#else
#define ExportedByBVHObjects DSYImport
#endif
#include "DSYExport.h"
