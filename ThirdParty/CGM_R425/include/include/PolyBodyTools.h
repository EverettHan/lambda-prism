#ifdef _STATIC_SOURCE
#define	ExportedByPolyBodyTools
#elif defined(__PolyBodyTools)
#define ExportedByPolyBodyTools DSYExport
#else
#define ExportedByPolyBodyTools DSYImport
#endif
#include "DSYExport.h"
