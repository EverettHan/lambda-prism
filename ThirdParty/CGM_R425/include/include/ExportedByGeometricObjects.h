#ifdef _STATIC_SOURCE
#define	ExportedByGeometricObjects
#elif defined __CATGeometricObjects


// COPYRIGHT DASSAULT SYSTEMES 1999

/** @CAA2Required */

/*---------------------------------------------------------------------*/

/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */

/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */

/*---------------------------------------------------------------------*/
#define ExportedByGeometricObjects DSYExport
#else
#define ExportedByGeometricObjects DSYImport
#endif
#include "DSYExport.h"
#include "GeometricObjectsCommonDec.h"
