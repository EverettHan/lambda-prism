#ifndef CATCGMCreatePropagationEdge_h_
#define CATCGMCreatePropagationEdge_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMModelInterfaces.h"
#include "CATBody.h"

class CATGeoFactory;
class CATTopData;
class CATICGMTopPropagationEdge;

/**
* Creates a tangency propagation operator for edges.
* @param iFactory
* A pointer to the factory of the resulting body. 
* @param iTopData
* A pointer to the topological data.
* @param iBody
* A pointer to the body to be propagated on.
* @param iInitialEdges
* A pointer to the list of initial edges in iBody.
* @param iPropagationType
* The propagation type :
* <br><b>Legal values</b>:
* <tt>CATEdgePropagManual</tt> - NOT TO BE USED
* <tt>CATEdgePropagAuto</tt>
* @param iRollingEdges
* A pointer to the list of rolling edges - SPECIFY NULL
* @return
* The pointer to the created operator. You must <tt>Release</tt> this operator after use.
* <ul>
* <li>After the run, the list of result edges is retrieved by
* <li>CATICGMTopPropagationEdge::GetResultListEdges(CATLISTP(CATCell) & ioListEdges).
 * @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATICGMTopPropagationEdge *CATCGMCreatePropagationEdge(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody,
  CATLISTP(CATCell) *iInitialEdges,
  CATBody::CATPropagationTypePr3 iPropagationType,
  CATLISTP(CATEdge) *iRollingEdges = NULL);

#endif /* CATCGMCreatePropagationEdge_h_ */
