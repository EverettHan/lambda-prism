#ifndef _JS0ZLIB0_INCLUDE
#define _JS0ZLIB0_INCLUDE

/************************************************************************/
/* Defines                                                              */
/************************************************************************/
#if defined(__JS0ZLIB)
# define ExportedByJS0ZLIB  DSYExport
#else  /* __JS0ZLIB */
# define ExportedByJS0ZLIB  DSYImport
#endif /* __JS0ZLIB */

#ifdef DSYINSTARCH /* Utilisation archive */
# undef ExportedByJS0ZLIB
# define ExportedByJS0ZLIB DSYLocal
#endif

/************************************************************************/
/* Local includes                                                       */
/************************************************************************/
#include "DSYExport.h"

#endif  /* _JS0ZLIB0_INCLUDE */
