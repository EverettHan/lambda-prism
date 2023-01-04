#ifdef _STATIC_SOURCE
#define	ExportedByCATTopologicalObjects
#elif defined __CATTopologicalObjects
#define ExportedByCATTopologicalObjects DSYExport
#else
#define ExportedByCATTopologicalObjects DSYImport
#endif
#include "DSYExport.h"

