#ifndef CATCGMCheckTopology_h_
#define CATCGMCheckTopology_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMModelInterfaces.h"

#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
class CATICGMObject;

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
ExportedByCATGMModelInterfaces ostream &CATCGMCheckTopology(
  CATICGMObject *iObject,
  int &ioNumberOfSevereAnomalies,
  ostream &ioForDumpOfAnomalies);

#endif /* CATCGMCheckTopology_h_ */
