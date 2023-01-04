#ifdef _STATIC_SOURCE
#define	ExportedByPolyMathCurves
#elif defined(__PolyMathCurves)
#define ExportedByPolyMathCurves DSYExport
#else
#define ExportedByPolyMathCurves DSYImport
#endif
#include "DSYExport.h"

