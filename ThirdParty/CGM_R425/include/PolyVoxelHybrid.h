#ifdef _STATIC_SOURCE
#define	ExportedByPolyVoxelHybrid
#elif defined(__PolyVoxelHybrid)
#define ExportedByPolyVoxelHybrid DSYExport
#else
#define ExportedByPolyVoxelHybrid DSYImport
#endif
#include "DSYExport.h"
