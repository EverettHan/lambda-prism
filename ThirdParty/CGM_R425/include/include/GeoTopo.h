#ifdef _STATIC_SOURCE
#define	ExportedByGeoTopo
#elif defined __GeoTopo
#define ExportedByGeoTopo DSYExport
#else
#define ExportedByGeoTopo DSYImport
#endif
#include "DSYExport.h"
#include <GeometricOperatorsCommonDec.h>
