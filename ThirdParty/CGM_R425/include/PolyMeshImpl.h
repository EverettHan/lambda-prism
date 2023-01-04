#ifdef _STATIC_SOURCE
#define	ExportedByPolyMeshImpl
#elif defined(__PolyMeshImpl)
#define ExportedByPolyMeshImpl DSYExport
#else
#define ExportedByPolyMeshImpl DSYImport
#endif
#include "DSYExport.h"
