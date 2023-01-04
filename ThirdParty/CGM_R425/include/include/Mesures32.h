#ifndef Mesures32_h
#define Mesures32_h

#ifdef _STATIC_SOURCE
#define	ExportedByMesures32
#elif defined(__Mesures32)
#define ExportedByMesures32 DSYExport
#else
#define ExportedByMesures32 DSYImport
#endif
#include "DSYExport.h"

#endif
