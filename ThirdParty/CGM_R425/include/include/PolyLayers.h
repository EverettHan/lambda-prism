#ifdef _STATIC_SOURCE
#define	ExportedByPolyLayers
#elif defined(__PolyLayers)
#define ExportedByPolyLayers DSYExport
#else
#define ExportedByPolyLayers DSYImport
#endif
#include "DSYExport.h"
