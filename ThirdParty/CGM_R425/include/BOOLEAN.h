#ifndef BOOLEAN_h
#define BOOLEAN_h

// COPYRIGHT DASSAULT SYSTEMES 1999

#ifdef _STATIC_SOURCE
#define	ExportedByBOOLEAN
#elif defined(__BOOLEAN)
#define ExportedByBOOLEAN DSYExport
#else
#define ExportedByBOOLEAN DSYImport
#endif
#include "DSYExport.h"

#endif
