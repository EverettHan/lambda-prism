#ifdef _STATIC_SOURCE
#define	ExportedByFrFGeodesic
#elif defined __FrFGeodesic
#define ExportedByFrFGeodesic DSYExport
#else
#define ExportedByFrFGeodesic DSYImport
#endif
#include "DSYExport.h"
#include <GeometricOperatorsCommonDec.h>
