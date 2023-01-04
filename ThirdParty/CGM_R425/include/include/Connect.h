#ifdef _STATIC_SOURCE
#define	ExportedByConnect
#elif defined __Connect


// COPYRIGHT DASSAULT SYSTEMES 1999

/** @CAA2Required */

/*---------------------------------------------------------------------*/

/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */

/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */

/*---------------------------------------------------------------------*/
#define ExportedByConnect DSYExport
#else
#define ExportedByConnect DSYImport
#endif
#include "DSYExport.h"
#include <GeometricOperatorsCommonDec.h>
