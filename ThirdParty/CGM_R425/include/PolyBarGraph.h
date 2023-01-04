#ifdef _STATIC_SOURCE
#define	ExportedByPolyBarGraph
#elif defined(__PolyBarGraph)
#define ExportedByPolyBarGraph DSYExport
#else
#define ExportedByPolyBarGraph DSYImport
#endif
#include "DSYExport.h"
