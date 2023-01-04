#ifdef _STATIC_SOURCE
#define	ExportedByCGMObject
#elif defined(__CGMObject)
#define ExportedByCGMObject DSYExport
#else
#define ExportedByCGMObject DSYImport
#endif
#include "DSYExport.h"
