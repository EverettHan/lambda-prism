#ifdef _STATIC_SOURCE
#define	ExportedByPolyPartitions
#elif defined(__PolyPartitions)
#define ExportedByPolyPartitions DSYExport
#else
#define ExportedByPolyPartitions DSYImport
#endif
#include "DSYExport.h"
