#ifdef _STATIC_SOURCE
#define	ExportedByGeoAdvCurves
#elif defined __GeoAdvCurves


#define ExportedByGeoAdvCurves DSYExport
#else
#define ExportedByGeoAdvCurves DSYImport
#endif
#include "DSYExport.h"
#include <GeometricOperatorsCommonDec.h>
