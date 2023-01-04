// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation EDS  03/10/2000
//=============================================================================

#ifndef __CheckOperators_h__
#define __CheckOperators_h__


#ifdef _STATIC_SOURCE
#define	ExportedByCheckOperators
#elif defined(__CheckOperators)
#define ExportedByCheckOperators DSYExport
#else
#define ExportedByCheckOperators DSYImport
#endif
#include "DSYExport.h"

#endif
