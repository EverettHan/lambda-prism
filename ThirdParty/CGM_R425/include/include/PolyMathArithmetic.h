#ifdef _STATIC_SOURCE
#define	ExportedByPolyMathArithmetic
#elif defined(__PolyMathArithmetic)
#define ExportedByPolyMathArithmetic DSYExport
#else
#define ExportedByPolyMathArithmetic DSYImport
#endif
#include "DSYExport.h"
