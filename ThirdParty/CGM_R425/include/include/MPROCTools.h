// COPYRIGHT DASSAULT SYSTEMES 2011

#ifndef MPROCTools_h
#define MPROCTools_h

/** @CAA2Required */
#ifdef _STATIC_SOURCE
#define	ExportedByMPROCTools
#elif defined __MPROCTools
#define ExportedByMPROCTools DSYExport
#else
#define ExportedByMPROCTools DSYImport
#endif
#include "DSYExport.h"

#endif

