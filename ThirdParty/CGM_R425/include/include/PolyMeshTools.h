#ifdef _STATIC_SOURCE
#define	ExportedByPolyMeshTools
#elif defined(__PolyMeshTools)
#define ExportedByPolyMeshTools DSYExport
#else
#define ExportedByPolyMeshTools DSYImport
#endif
#include "DSYExport.h"
