// COPYRIGHT DASSAULT SYSTEMES 2018, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyThreadServices.h
//
//===================================================================
//
// Usage notes:
// Small utilities to manage threads
//
//
//===================================================================
//
// Aug 2018 Creation: JXO
//===================================================================

#ifndef CATPolyThreadServices_h
#define CATPolyThreadServices_h

// Poly
#include "PolyMultiThreading.h"


namespace Poly
{
 /** @name Small utilities to manage threads.
  *
  * CATPolyThreadServices.h
  * @{ */

 /**
  * Reads the "CPUIntensiveUsage" setting and returns the number of available threads (depending on number of cores)
  */
  ExportedByPolyMultiThreading int GetNbThreadsForCPUIntensiveUsage();
 /**
  * Gets the "CPUIntensiveUsage" setting.
  */
  ExportedByPolyMultiThreading int GetCPUIntensiveUsage();
};

/** @} */

#endif /* CATPolyThreadServices */
