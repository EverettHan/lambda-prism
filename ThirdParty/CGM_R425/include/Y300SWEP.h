#ifdef _STATIC_SOURCE
#define	ExportedByY300SWEP
#elif defined __Y300SWEP
#define ExportedByY300SWEP DSYExport
#else
#define ExportedByY300SWEP DSYImport
#endif
#include "DSYExport.h"


#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#include <GeometricOperatorsCommonDec.h>
