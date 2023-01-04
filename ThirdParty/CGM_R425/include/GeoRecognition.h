#ifdef _STATIC_SOURCE
#define	ExportedByGeoRecognition
#elif defined __GeoRecognition


#define ExportedByGeoRecognition DSYExport
#else
#define ExportedByGeoRecognition DSYImport
#endif
#include "DSYExport.h"
#include <GeometricOperatorsCommonDec.h>
