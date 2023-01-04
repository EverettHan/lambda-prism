#ifdef _STATIC_SOURCE
#define	ExportedByPolyMathSurfaces
#elif defined(__PolyMathSurfaces)
#define ExportedByPolyMathSurfaces DSYExport
#else
#define ExportedByPolyMathSurfaces DSYImport
#endif
#include "DSYExport.h"
