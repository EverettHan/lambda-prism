#ifdef _STATIC_SOURCE
#define	ExportedByClash2D
#elif defined __Clash2D
#define ExportedByClash2D DSYExport
#else
#define ExportedByClash2D DSYImport
#endif
#include "DSYExport.h"
#include <GeometricOperatorsCommonDec.h>
