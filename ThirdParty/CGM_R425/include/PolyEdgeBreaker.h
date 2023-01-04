#ifdef _STATIC_SOURCE
#define	ExportedByPolyEdgeBreaker
#elif defined(__PolyEdgeBreaker)
#define ExportedByPolyEdgeBreaker DSYExport
#else
#define ExportedByPolyEdgeBreaker DSYImport
#endif
#include "DSYExport.h"
