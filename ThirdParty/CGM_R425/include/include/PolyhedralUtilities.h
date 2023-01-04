// COPYRIGHT DASSAULT SYSTEMES 2010
/** @CAA2Required */
/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/

#ifdef _STATIC_SOURCE
#define	ExportedByPolyhedralUtilities
#elif defined(__PolyhedralUtilities)
#define ExportedByPolyhedralUtilities DSYExport
#else
#define ExportedByPolyhedralUtilities DSYImport
#endif
#include "DSYExport.h"
