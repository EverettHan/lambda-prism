#ifdef _STATIC_SOURCE
#define	ExportedByPolyMathRay
#elif defined(__PolyMathRay)
#define ExportedByPolyMathRay DSYExport
#else
#define ExportedByPolyMathRay DSYImport
#endif
#include "DSYExport.h"

