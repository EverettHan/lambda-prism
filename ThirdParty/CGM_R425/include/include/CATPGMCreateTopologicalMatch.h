#ifndef CATPGMCreateTopologicalMatch_h_
#define CATPGMCreateTopologicalMatch_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"
#include "CATSkillValue.h"

class CATBody;
class CATCGMJournalList;
class CATGeoFactory;
class CATIPGMTopologicalMatch;

/**
 * @nodoc
 * Deprecated. Use now @href CATPGMCreateTopologicalMatch .
 * Creates a topological operator of multiple sides matching.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iWire1
 * The array <tt>[NbWires]</tt> of pointers to wire body on the first same surface. 
 * Each body only contains one wire with one edge. The geometry of the edge must
 * be a boundary of <tt>iSupport1</tt>.
 * @param iWire2
 * The array <tt>[NbWires]</tt> of pointers to the corresponding wire bodies to match.
 * Each body only contains one wire with one edge. The geometry of the edge must
 * be a boundary of the corresponding surface in <tt>iSupport2</tt>. 
 * @param iNbWires
 * The number of wires to match.
 * @param iSupport1
 * The pointer to the common surface of the wire bodies of <tt>iWire1</tt>.
 * @param iSupport2
 * The array <tt>[NbWires]</tt> pointers to the corresponding surfaces of the wire bodies of <tt>iWire2</tt>.
 * @param iMode
 * The mode of use.
 * @param iJournal
 * The pointer to the journal corresponding to the operation. If <tt>NULL</tt>, the journal is not written.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 * @see CATTopologicalMatch
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopologicalMatch *CATPGMCreateTopologicalMatch(
  CATGeoFactory *iFactory,
  CATBody **iWire1,
  CATBody **iWire2,
  CATLONG32 iNbWires,
  CATBody *iSupport1,
  CATBody **iSupport2,
  CATSkillValue iMode = BASIC,
  CATCGMJournalList *iJournal = 0);

#endif /* CATPGMCreateTopologicalMatch_h_ */
