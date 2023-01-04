#ifdef _STATIC_SOURCE
#define	ExportedByInterfaces
#elif defined __Interfaces
#define ExportedByInterfaces DSYExport
#else
#define ExportedByInterfaces DSYImport
#endif
#include "DSYExport.h"
#include <GeometricOperatorsCommonDec.h>
