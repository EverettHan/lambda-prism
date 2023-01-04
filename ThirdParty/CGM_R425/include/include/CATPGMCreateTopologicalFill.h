#ifndef CATPGMCreateTopologicalFill_h_
#define CATPGMCreateTopologicalFill_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"
#include "CATSkillValue.h"

class CATBody;
class CATCGMJournalList;
class CATGeoFactory;
class CATIPGMTopologicalFill;

/**
 * @nodoc
 * Creates a topological operator that fills a closed area defined by a set of wires.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iNumberOfWires
 * The number of wires defining the boundary of the area to fill. 
 * @param iArrayOfWires
 * The array of pointers to the wire bodies, each containing only one wire. 
 * The set of wires must defined a closed area, 
 * and the wires must be given in the right order (but the orientation
 * of each wire is computed by the operator).
 * @param iArrayOfBodySupports
 * The array of pointers to the supporting bodies of the wires, thus allowing you to define G1 and G2 continuity
 * criteria.
 * @param iMode
 * The mode of use.
 * @param iJournal
 * The pointer to the journal corresponding to the operation. If <tt>NULL</tt>, the journal is not filled in.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method afer use.
 * @see CATTopologicalFill
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopologicalFill *CATPGMCreateTopologicalFill(
  CATGeoFactory *iFactory,
  const CATLONG32 iNumberOfWires,
  const CATBody **iArrayOfBodyWires,
  const CATBody **iArrayOfBodySupports,
  CATSkillValue iMode = BASIC,
  CATCGMJournalList *iJournal = 0);

/**
 * @nodoc
 * Creates a topological operator that fills a closed area defined by a set of connecting wires.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iNumberOfWires
 * The number of wires defining the boundary of the area to fill. 
 * @param iArrayOfWires
 * The array of pointers to the wire bodies, each containing only one wire. 
 * The set of wires must defined a closed area, 
 * and the wires must be given in the right order (but the orientation
 * of each wire is computed by the operator).
 * @param iMode
 * The mode of use.
 * @param iJournal
 * The pointer to the journal corresponding to the operation. If <tt>NULL</tt>, the journal is not filled in.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method afer use.
 * @see CATTopologicalFill
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopologicalFill *CATPGMCreateTopologicalFill(
  CATGeoFactory *iFactory,
  const CATLONG32 iNumberOfWires,
  const CATBody **iArrayOfWires,
  CATSkillValue iMode = BASIC,
  CATCGMJournalList *iJournal = 0);

#endif /* CATPGMCreateTopologicalFill_h_ */
