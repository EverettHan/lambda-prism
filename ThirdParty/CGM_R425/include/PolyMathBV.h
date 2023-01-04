#ifdef _STATIC_SOURCE
#define	ExportedByPolyMathBV
#elif defined(__PolyMathBV)
#define ExportedByPolyMathBV DSYExport
#else
#define ExportedByPolyMathBV DSYImport
#endif
#include "DSYExport.h"
