#ifndef CATCheckTopology_h
#define CATCheckTopology_h
// COPYRIGHT DASSAULT SYSTEMES  2000
/**
* @level Protected
* @usage U1
*/ 
#include "ExportedByCATTopologicalObjects.h"
#include "CATICGMObject.h"

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
/**
 * Performs the topological check of a CGM object.
 * @param iObject
 * The pointer to the object to check.
 * @param ioNumberOfSevereAnomalies
 * The count of detected anomalies.
 * @param ioForDumpOfAnomalies
 * The stream on which the anomalies are dumped.
 * @return
 * The stream on which the anomalies are dumped (same as <tt>ioForDumpOfAnomalies</tt>).
 */
ExportedByCATTopologicalObjects  ostream  & CATCheckTopology
(
 CATICGMObject *iObject,
 int           &ioNumberOfSevereAnomalies,
 ostream       &ioForDumpOfAnomalies 
);


#endif
