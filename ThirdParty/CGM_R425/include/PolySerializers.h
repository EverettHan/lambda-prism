#ifdef _STATIC_SOURCE
#define	ExportedByPolySerializers
#elif defined(__PolySerializers)
#define ExportedByPolySerializers DSYExport
#else
#define ExportedByPolySerializers DSYImport
#endif
#include "DSYExport.h"
