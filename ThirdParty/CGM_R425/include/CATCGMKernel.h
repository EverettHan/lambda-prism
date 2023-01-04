#ifdef _STATIC_SOURCE
#define	ExportedByCATCGMKernel
#elif defined __CATCGMKernel
#define ExportedByCATCGMKernel DSYExport
#else
#define ExportedByCATCGMKernel DSYImport
#endif
#include "DSYExport.h"
