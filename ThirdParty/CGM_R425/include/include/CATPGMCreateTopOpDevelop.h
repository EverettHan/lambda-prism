#ifndef CATPGMCreateTopOpDevelop_h_
#define CATPGMCreateTopOpDevelop_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"

class CATBody;
class CATCGMJournalList;
class CATGeoFactory;
class CATGeometry;
class CATIPGMSurTo2DGlobalMapping;
class CATTopData;
class CATIPGMTopDevelop;
class CATICGMSurTo2DGlobalMapping;

#ifndef NULL
#define NULL 0
#endif

/** 
* @nodoc
* Use CATPGMCreateTopDevelop (CATTopDevelop.h)
* @return [out, IUnknown#Release]
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopDevelop *CATPGMCreateTopOpDevelop(
  CATGeoFactory *iFactory,
  CATBody *iWire,
  CATBody *iWireSupport,
  CATBody *iTargetSupport,
  CATICGMSurTo2DGlobalMapping *iMappingIn,
  CATICGMSurTo2DGlobalMapping *iMappingOut,
  CATCGMJournalList *iReport = NULL);

/** 
* @nodoc
* Use CATPGMCreateTopDevelop (CATTopDevelop.h)
* @return [out, IUnknown#Release]
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopDevelop *CATPGMCreateTopOpDevelop(
  CATGeoFactory *iFactory,
  CATBody *iWire,
  CATBody *iWireSupport,
  CATBody *iTargetSupport,
  CATICGMSurTo2DGlobalMapping *iMappingIn,
  CATICGMSurTo2DGlobalMapping *iMappingOut,
  CATTopData *iData);

#endif /* CATPGMCreateTopOpDevelop_h_ */
