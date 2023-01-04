#ifdef _STATIC_SOURCE
#define	ExportedByCATGeometricOperators
#elif defined __CATGeometricOperators
#define ExportedByCATGeometricOperators DSYExport
#else
#define ExportedByCATGeometricOperators DSYImport
#endif
#include "DSYExport.h"
#include <GeometricOperatorsCommonDec.h>
