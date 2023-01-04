#ifndef __CATCreateSplitShellByWires_h__ 
#define __CATCreateSplitShellByWires_h__ 

#include "ExportedByCATTopologicalObjects.h"
#include "ListPOfCATBody.h"

class CATTopSplitShellByWires; // forward necessaire
class CATGeoFactory;
class CATTopData;
class CATBody;
class CATExtrapolTool;


/**
 * Creates a CATTopSplitShellByWires operator.
 * @param iFactory
 * The pointer to the geometry factory. 
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iSplittingBodies
 * A list of bodies containing only one wire.
 * @param iSkinBody
 * The skin body to be split by iSplittingBodies. 
 * @return
 * The pointer to the created operator. To delete with the usual C++ <tt>delete</tt> operator after use.
 */

ExportedByCATTopologicalObjects CATTopSplitShellByWires*
CATCreateSplitShellByWires(CATGeoFactory     * iFactory,
                            CATTopData        * iTopData,
                            CATLISTP(CATBody) * iSplittingBodies,
                            CATBody           * iSkinBody);

/**
 * Creates a CATTopSplitShellByWires operator with an explicit extrapolation.
 * Use of Default extrapolation, please see : TopologicalOperators\ProtectedInterfaces\
 * @param iExtrap
 * The pointer to the Extrapol tool Which have a TopData, A body support and a Factory. 
 * @param iSplittingBodies
 * A list of bodies containing only one wire.
 * @return
 * The pointer to the created operator. To delete with the usual C++ <tt>delete</tt> operator after use.
 */

ExportedByCATTopologicalObjects CATTopSplitShellByWires*
CATCreateSplitShellByWires(CATExtrapolTool     * iExtrap,
                           CATLISTP(CATBody) * iSplittingBodies);

#endif






