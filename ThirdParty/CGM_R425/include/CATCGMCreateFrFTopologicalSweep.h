#ifndef CATCGMCreateFrFTopologicalSweep_h_
#define CATCGMCreateFrFTopologicalSweep_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATIACGMLevel.h"
#include "CATGMOperatorsInterfaces.h"
#include "CATCollec.h"
#include "CATFrFTopologicalSweepDef.h"

class CATBody;
class CATCGMJournalList;
class CATGeoFactory;
class CATTopData;
class CATICGMFrFTopologicalSweep;
class CATLISTP(CATGeometry);

/**
 * Creates a topological sweep operator from a profile and a guide.
 * <br>The constructor generates an "unspec sweep" operator.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iGuide
 * The pointer to the wire body defining the sweep guide.
 * @param iProfile
 * The pointer to the wire body defining the sweep profile.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 * @see CATICGMFrFTopologicalSweep
 */
ExportedByCATGMOperatorsInterfaces CATICGMFrFTopologicalSweep *CATCGMCreateFrFTopologicalSweep(
  CATGeoFactory               * iFactory,
  CATTopData                  * iTopData,
  CATBody                     * iGuide,
  CATBody                     * iProfile);

/**
 * Creates a topological sweep operator from several profiles and guides.
 * <br>This constructor generates:
 * <ul><li> an "unspec sweep" operator, if one guide and one profile.
 *<li> a "bi-rail sweep" operator, if two guides and one profile.
 * <li>a "multi-profiles sweep" operator, in the other cases.
 * </ul>
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iGuides
 * The list of the pointers to the wire bodies defining the sweep guides.
 * @param iProfiles
 * The list of the pointers to the wire bodies defining the sweep profiles.
 * @param iSweepType
 * The type of the generated sweep. <br>To be set to <tt>CATFrFTopologicalSweepType   _Multi</tt> in order
 * to force the multi-profile sweep in any cases.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 * @see CATICGMFrFTopologicalSweep
 */
ExportedByCATGMOperatorsInterfaces CATICGMFrFTopologicalSweep *CATCGMCreateFrFTopologicalSweep(
  CATGeoFactory               * iFactory,
  CATTopData                  * iTopData,
  CATLISTP(CATGeometry)       * iGuides,
  CATLISTP(CATGeometry)       * iProfiles,
  CATFrFTopologicalSweepType    iSweepType = CATFrFTopologicalSweepType_Std);

/**
 * Creates a topological segment sweep operator.
 * <br>The profiles are segments between the guides.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iLimitGuides
 * The list of the pointers to the wire bodies defining the sweep guides. In <tt>BASIC</tt> mode, two
 * guides define a bi-rail segment sweep.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 * @see CATICGMFrFTopologicalSweep
 */
ExportedByCATGMOperatorsInterfaces CATICGMFrFTopologicalSweep *CATCGMCreateFrFTopologicalSegmentSweep(
  CATGeoFactory               * iFactory,
  CATTopData                  * iTopData,
  CATLISTP(CATGeometry)       * iLimitGuides);

/**
 * Creates a topological circle sweep operator.
 * <br>The profiles are circles passing thru the guides.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iLimitGuides
 * The list of the pointers to the wire bodies defining the sweep guides. In <tt>BASIC</tt> mode, three guides
 * are needed.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 * @see CATICGMFrFTopologicalSweep
 */
ExportedByCATGMOperatorsInterfaces CATICGMFrFTopologicalSweep *CATCGMCreateFrFTopologicalCircleSweep(
  CATGeoFactory               * iFactory,
  CATTopData                  * iTopData,
  CATLISTP(CATGeometry)       * iLimitGuides);

/**
 * Creates a topological conic sweep operator.
 * <br>The profiles are conic curves passing thru the guides.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iLimitGuides
 * The list of the pointers to the wire bodies defining the sweep guides. In <tt>BASIC</tt> mode, five guides
 * are needed.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 * @see CATICGMFrFTopologicalSweep
 */
ExportedByCATGMOperatorsInterfaces CATICGMFrFTopologicalSweep *CATCGMCreateFrFTopologicalConicSweep(
  CATGeoFactory               * iFactory,
  CATTopData                  * iTopData,
  CATLISTP(CATGeometry)       * iLimitGuides);

#endif /* CATCGMCreateFrFTopologicalSweep_h_ */
