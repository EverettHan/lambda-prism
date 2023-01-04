#ifdef _STATIC_SOURCE
#define	ExportedByPolyMathContainers
#elif defined(__PolyMathContainers)
#define ExportedByPolyMathContainers DSYExport
#else
#define ExportedByPolyMathContainers DSYImport
#endif
#include "DSYExport.h"

#ifdef _LINUX_SOURCE
#define ExportedTemplateByPolyMathContainers DSYExport
#else
#define ExportedTemplateByPolyMathContainers
#endif
