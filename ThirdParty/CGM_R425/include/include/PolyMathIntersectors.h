#ifdef _STATIC_SOURCE
#define	ExportedByPolyMathIntersectors
#elif defined(__PolyMathIntersectors)
#define ExportedByPolyMathIntersectors DSYExport
#else
#define ExportedByPolyMathIntersectors DSYImport
#endif
#include "DSYExport.h"
