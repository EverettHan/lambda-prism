#ifdef _STATIC_SOURCE
#define	ExportedByPolyMultiThreading
#elif defined(__PolyMultiThreading)
#define ExportedByPolyMultiThreading DSYExport
#else
#define ExportedByPolyMultiThreading DSYImport
#endif
#include "DSYExport.h"
