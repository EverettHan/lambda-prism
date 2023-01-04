#ifdef _STATIC_SOURCE
#define	ExportedByMathGeo
#elif defined __MathGeo
#define ExportedByMathGeo DSYExport
#else
#define ExportedByMathGeo DSYImport
#endif
#include "DSYExport.h"
#include <AdvancedMathematicsCommonDec.h>
