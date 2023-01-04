#ifndef BOOARRAY_h
#define BOOARRAY_h

// COPYRIGHT DASSAULT SYSTEMES 1999

#ifdef _STATIC_SOURCE
#define	ExportedByBOOARRAY
#elif defined(__BOOARRAY)
#define ExportedByBOOARRAY DSYExport
#else
#define ExportedByBOOARRAY DSYImport
#endif
#include "DSYExport.h"

#endif
