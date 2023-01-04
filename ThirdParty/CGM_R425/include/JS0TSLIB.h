#ifndef JS0TSLIB_INCLUDE
#define JS0TSLIB_INCLUDE

/* COPYRIGHT DASSAULT SYSTEMES 2005 */

/************************************************************************/
/* Defines                                                              */
/************************************************************************/
#if defined(__JS0TSLIB)
# define ExportedByJS0TSLIB   DSYExport
#else // __JS0STDLIB
# define ExportedByJS0TSLIB   DSYImport
#endif  // __JS0STDLIB

/************************************************************************/
/* Local includes                                                       */
/************************************************************************/
#include "DSYExport.h"

#endif  // JS0TSLIB_INCLUDE
