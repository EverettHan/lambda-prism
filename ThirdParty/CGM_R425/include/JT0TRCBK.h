#ifndef _JT0TRCBK_H
#define _JT0TRCBK_H

// COPYRIGHT DASSAULT SYSTEMES 2000

/************************************************************************/
/* Defines                                                              */
/************************************************************************/
#if defined(__JT0TRCBK)
# define ExportedByJT0TRCBK   DSYExport
#else  // __JT0TRCBK
# define ExportedByJT0TRCBK   DSYImport
#endif // __JT0TRCBK

/************************************************************************/
/* Local includes                                                       */
/************************************************************************/
#include "DSYExport.h"

#endif  // _JT0TRCBK_H
