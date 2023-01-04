#ifdef _STATIC_SOURCE
#define	ExportedByCompactFunction
#elif defined __CompactFunction
#define ExportedByCompactFunction DSYExport
#else
#define ExportedByCompactFunction DSYImport
#endif
#include "DSYExport.h"
#include <AdvancedMathematicsCommonDec.h>
