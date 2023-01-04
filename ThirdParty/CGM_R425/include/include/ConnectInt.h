#ifdef _STATIC_SOURCE
#define	ExportedByConnectInt
#elif defined __ConnectInt
#define ExportedByConnectInt DSYExport
#else
#define ExportedByConnectInt DSYImport
#endif
#include "DSYExport.h"
#include <GeometricOperatorsCommonDec.h>
