#ifndef CATPGMCreateTopologicalBlendCurve_h_
#define CATPGMCreateTopologicalBlendCurve_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATBodyFreezeMode.h"
#include "CATSkillValue.h"
#include "CATCollec.h"

#ifndef NULL
#define NULL 0
#endif

class CATBody;
class CATCGMJournalList;
class CATGeoFactory;
class CATIPGMTopologicalBlendCurve;

/**
 * @nodoc
 * Deprecated. Use now @href CATPGMCreateTopologicalBlendCurve .
 * Creates a topological operator that connects two wire bodies.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iWire1
 * The pointer to the first wire body, containing only one wire. 
 * @param iWireParam1
 * The pointer to a vertex body on <tt>iWire1</tt>, defining where the connection must be done.
 * @param iWire2
 * The pointer to the second wire body, containing only one wire. 
 * @param iWireParam2
 * The pointer to a vertex body on <tt>iWire2</tt>, defining where the connection must be done.
 * @param iTargetBody
 * The pointer to the body that will contain the resulting the blend curve.
 * @param iBodyFreezeMode
 * The smart mode of the resulting body.
 * @param iMode
 * The mode of use.
 * @param iJournal
 * The pointer to the journal corresponding to the operation. If <tt>NULL</tt>, the journal is not filled in.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 * @see CATTopologicalBlendCurve
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopologicalBlendCurve *CATPGMCreateTopologicalBlendCurve(
  CATGeoFactory *iFactory,
  CATBody *iWire1,
  CATBody *iWireParam1,
  CATBody *iWire2,
  CATBody *iWireParam2,
  CATBody *iTargetBody = NULL,
  CATBodyFreezeMode iBodyFreezeMode = CATBodyFreezeOn,
  CATCGMJournalList *iJournal = NULL,
  CATSkillValue iMode = BASIC);

#endif /* CATPGMCreateTopologicalBlendCurve_h_ */
