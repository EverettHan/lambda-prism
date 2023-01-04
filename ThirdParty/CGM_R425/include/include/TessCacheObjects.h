#ifndef TessCacheObjects_h
#define TessCacheObjects_h

// COPYRIGHT DASSAULT SYSTEMES 1999

#ifdef _STATIC_SOURCE
#define	ExportedByTessCacheObjects
#elif defined(__TessCacheObjects)
#define ExportedByTessCacheObjects DSYExport
#else
#define ExportedByTessCacheObjects DSYImport
#endif
#include "DSYExport.h"

#endif
