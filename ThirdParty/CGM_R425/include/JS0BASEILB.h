#ifndef _JS0BASEILB_H
#define _JS0BASEILB_H

/************************************************************************/
/* Defines                                                              */
/************************************************************************/
#if defined(__JS0BASEILB)
# define ExportedByJS0BASEILB   DSYExport
#else  // __JS0BASEILB
# define ExportedByJS0BASEILB   DSYImport
#endif // __JS0BASEILB

/************************************************************************/
/* Local includes                                                       */
/************************************************************************/
#include "DSYExport.h"


/* Utilisation archive */
#if defined(DSYINSTARCH) || defined (HTTPARCH) || defined(__mxUtil)
#undef  ExportedByJS0BASEILB 
#define ExportedByJS0BASEILB 
#endif

#endif  // _JS0BASEILB_H
