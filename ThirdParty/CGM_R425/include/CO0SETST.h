

// COPYRIGHT DASSAULT SYSTEMES 2000
/** @CAA2Required */
/**********************************************************************/
/* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME */
/**********************************************************************/

/************************************************************************/
/* Defines                                                              */
/************************************************************************/
#if defined(__CO0SETST)
# define ExportedByCO0SETST   DSYExport
#else // __CO0SETST
# define ExportedByCO0SETST   DSYImport
#endif  // __CO0SETST

/************************************************************************/
/* Local includes                                                       */
/************************************************************************/
#include "DSYExport.h"
