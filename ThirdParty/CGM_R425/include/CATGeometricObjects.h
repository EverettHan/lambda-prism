//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  1999
//=============================================================================
/** @CAA2Required */
/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/
#ifdef _STATIC_SOURCE
#define	ExportedByCATGeometricObjects
#elif defined __CATGeometricObjects

#define ExportedByCATGeometricObjects DSYExport
#else
#define ExportedByCATGeometricObjects DSYImport
#endif
#include "DSYExport.h"
#include "GeometricObjectsCommonDec.h"
