
#ifndef __CATCreatePropagationEdgeOpe_H__ 
#define __CATCreatePropagationEdgeOpe_H__ 

// COPYRIGHT DASSAULT SYSTEMES 2002

/**
 * @level Protected
 * @usage U1
 */ 

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopPropagationEdgeOpe.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATEdge.h"
#include "CATBody.h"

class CATTopPropagationEdge;
class CATGeoFactory;
class CATTopData;

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
* The pointer to the created operator. You must <tt>delete</tt> this operator after use.
* <ul>
* <li>After the run, the list of result edges is retrieved by
* <li>CATTopPropagationEdge::GetResultListEdges(CATLISTP(CATCell) & ioListEdges).
*/
ExportedByCATTopologicalObjects CATTopPropagationEdge *
CATCreatePropagationEdge(CATGeoFactory * iFactory,
                         CATTopData * iTopData,
                         CATBody * iBody,
                         CATLISTP(CATCell) * iInitialEdges,
                         CATBody::CATPropagationTypePr3 iPropagationType,
                         CATLISTP(CATEdge) * iRollingEdges = NULL);


/**
* @nodoc
*/
ExportedByCATTopologicalObjects CATTopPropagationEdge * CATCreatePropagationEdge(CATGeoFactory * iFactory,
                                                                                 CATTopData * iTopData);
#endif






