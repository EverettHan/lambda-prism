#ifdef _STATIC_SOURCE
#define	ExportedByPolyFactoryImpl
#elif defined(__PolyFactoryImpl)
#define ExportedByPolyFactoryImpl DSYExport
#else
#define ExportedByPolyFactoryImpl DSYImport
#endif
#include "DSYExport.h"
