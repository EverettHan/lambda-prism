#ifdef _STATIC_SOURCE
#define	ExportedByCATCompact
#elif defined(__CATCompact)
#define ExportedByCATCompact DSYExport
#else
#define ExportedByCATCompact DSYImport
#endif
#include "DSYExport.h"
#include "GeometricObjectsCommonDec.h"
