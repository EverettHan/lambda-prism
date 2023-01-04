#ifndef BOOPER_h
#define BOOPER_h

// COPYRIGHT DASSAULT SYSTEMES 1999

#ifdef _STATIC_SOURCE
#define	ExportedByBOOPER
#elif defined(__BOOPER)
#define ExportedByBOOPER DSYExport
#else
#define ExportedByBOOPER DSYImport
#endif
#include "DSYExport.h"

#endif
