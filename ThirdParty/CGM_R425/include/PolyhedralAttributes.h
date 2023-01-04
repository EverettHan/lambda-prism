// COPYRIGHT DASSAULT SYSTEMES 2010
/** @CAA2Required */
/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/

#ifdef _STATIC_SOURCE
#define	ExportedByPolyhedralAttributes
#elif defined(__PolyhedralAttributes)
#define ExportedByPolyhedralAttributes DSYExport
#else
#define ExportedByPolyhedralAttributes DSYImport
#endif
#include "DSYExport.h"
