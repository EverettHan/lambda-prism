#ifdef _STATIC_SOURCE
#define	ExportedByPolyMathUtils
#elif defined(__PolyMathUtils)
#define ExportedByPolyMathUtils DSYExport
#else
#define ExportedByPolyMathUtils DSYImport
#endif
#include "DSYExport.h"
