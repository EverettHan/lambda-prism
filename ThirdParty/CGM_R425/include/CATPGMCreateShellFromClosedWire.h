#ifndef CATPGMCreateShellFromClosedWire_h_
#define CATPGMCreateShellFromClosedWire_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATCollec.h"

#ifndef NULL
#define NULL 0
#endif

class CATBody;
class CATCGMJournalList;
class CATGeoFactory;
class CATIPGMShellFromClosedWire;
class CATSurface;

//
/**
 * @nodoc
 * Deprecated. Use CATPGMCreateShellFromClosedWire (CATShellFromClosedWire.h).
 * @return [out, IUnknown#Release]
*/
ExportedByCATGMOperatorsInterfaces CATIPGMShellFromClosedWire *CATPGMCreateShellFromClosedWire(
  CATGeoFactory *iFactory,
  const CATBody *iBody,
  const CATSurface *iSupport,
  CATCGMJournalList *iReport = NULL);

#endif /* CATPGMCreateShellFromClosedWire_h_ */
