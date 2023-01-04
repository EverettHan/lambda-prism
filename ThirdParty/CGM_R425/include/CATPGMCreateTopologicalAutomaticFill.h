#ifndef CATPGMCreateTopologicalAutomaticFill_h_
#define CATPGMCreateTopologicalAutomaticFill_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATCollec.h"
#include "CATTopologicalFillType.h"

#ifndef NULL
#define NULL 0
#endif

class CATBody;
class CATCGMJournalList;
class CATGeoFactory;
class CATTopData;
class CATIPGMTopologicalFill;
class CATLISTP(CATBody);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopologicalFill *CATPGMCreateAutomaticFill(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATLISTP(CATBody) const &iListOfWires,
  CATLISTP(CATBody) const &iListOfSupports,
  const CATTopologicalFillType iFillType = CATTopologicalFillType_analytic);

/**
 * @nodoc
 * Attention constructeurs obsoletes.
 * Utiliser les constructeurs de SurfacicTopoOperators/ProtectedInterfaces/CATopologicalAutomaticFill.h:
 * CATTopologicalAutomaticFill * CATPGMCreateTopologicalAutomaticFill(....) 
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopologicalFill *CATPGMCreateTopologicalAutomaticFill(
  CATGeoFactory *iFactory,
  CATLISTP(CATBody) const &iListOfWires,
  const CATTopologicalFillType iFillType = CATTopologicalFillType_analytic,
  CATCGMJournalList *iJournal = NULL);

#endif /* CATPGMCreateTopologicalAutomaticFill_h_ */
