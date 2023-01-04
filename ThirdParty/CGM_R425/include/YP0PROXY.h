#ifdef _STATIC_SOURCE
#define	ExportedByYP0PROXY
#elif defined __YP0PROXY
#define ExportedByYP0PROXY DSYExport
#else
#define ExportedByYP0PROXY DSYImport
#endif
#include "DSYExport.h"
#include "GeometricObjectsCommonDec.h"
