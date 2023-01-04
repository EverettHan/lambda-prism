#ifdef _STATIC_SOURCE
#define	ExportedByY3DYNOPE
#elif defined __Y3DYNOPE


// COPYRIGHT DASSAULT SYSTEMES 1999

/** @CAA2Required */

/*---------------------------------------------------------------------*/

/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */

/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */

/*---------------------------------------------------------------------*/
#define ExportedByY3DYNOPE DSYExport
#else
#define ExportedByY3DYNOPE DSYImport
#endif
#include "DSYExport.h"
#include <GeometricOperatorsCommonDec.h>
