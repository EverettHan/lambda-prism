#ifdef _STATIC_SOURCE
#define	ExportedByY30Approx
#elif defined __Y30Approx
#define ExportedByY30Approx DSYExport
#else
#define ExportedByY30Approx DSYImport
#endif
#include "DSYExport.h"
#include <GeometricOperatorsCommonDec.h>
