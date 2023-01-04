#ifdef _STATIC_SOURCE
#define	ExportedByPolyVoxel
#elif defined(__PolyVoxel)
#define ExportedByPolyVoxel DSYExport
#else
#define ExportedByPolyVoxel DSYImport
#endif
#include "DSYExport.h"
