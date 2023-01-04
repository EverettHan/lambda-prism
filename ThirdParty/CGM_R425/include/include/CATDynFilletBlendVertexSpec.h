#ifndef CATDynFilletBlendVertexSpec_h_
#define CATDynFilletBlendVertexSpec_h_
 
// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CATGMOperatorsInterfaces.h"
#include "CATMathDef.h"
class CATCell;
class CATCGMStream;

/**
 * @level Protected
 * @usage U1
 */

#ifndef NULL
#define NULL 0
#endif

/**
 * Class defining the parameters for one of the edges leading to a blend vertex. <br>
 * A blend vertex (also named hyper vertex or corner with setbacks)
 * is a vertex where three edges blend together at a defined distance from the corner vertex. 
 * Compared to the default corner which is obtained when three edges
 * are simply filletted, the result is more appealing. <br>
 * A CATDynFilletBlendVertexSpec object defines the corner parameters for each edge to be filleted, that is:
 * <ul>
 * <li>the edge
 * <li>the portion od the edge to be rounded
 * <li>the direction with respect to the vertex.
 * </ul>
 * Here is what you have to do to create a blend vertex:
 * <ol>
 * <li>Create a CATIPGMDynFillet
 * <li>For each edge to be filletted and leading to the corner to be rounded:
 * <ol>
 * <li>Create a CATDynFilletBlendVertexSpec
 * <li>Create a CATDynFilletEdgeRibbon and apply the SetReconfigFillFunction method with the 
 * CATDynC1SingleFaceFilling option
 * </ol>
 * <li>Sort the list of CATDynFilletBlendVertexSpec so that they are re-ordered clock-wise.
 * To do this, use CATIPGMSortBlendVertexSpecs
 * <li>Create a CATDynFilletBlendVertex
 * <li>Add each CATDynFilletBlendVertex to the CATIPGMDynFillet.
 * </ol>
 */
class ExportedByCATGMOperatorsInterfaces CATDynFilletBlendVertexSpec
{
public :
	/**
	* @nodoc
	* Use CATCreateDynFilletBlendVertexSpec.
	*/
	CATDynFilletBlendVertexSpec();
    /**
	* @nodoc
	* Destructor.
	*/
	virtual ~CATDynFilletBlendVertexSpec();

};

/**
* Constructs the specification for one edge leading to the blend corner.
* @param iEdge
* The edge to be filletted.
* @param iRatio
* The length of the setback (ratio setback / edge length).
* @param iDirection
* If the edge is oriented towards the vertex to blend, the direction is -1,
* otherwise it is +1.
* @param iSetback
* Not implemented
* @return
* The CATDynFilletBlendVertexSpec operator.
*/

ExportedByCATGMOperatorsInterfaces CATDynFilletBlendVertexSpec* CATCreateDynFilletBlendVertexSpec(CATCell *iEdge, 
																								  double iRatio, 
																								  int iDirection, 
																								  double iSetback);

/** 
* @collection CATLISTP(CATDynFilletBlendVertexSpec)
* Collection class for pointers to the radius definition in a ribbon.
* All the methods of pointer collection classes are available.
* Refer to the articles dealing with collections in the encyclopedia. 
*/

#include "CATCGMLISTP_Declare.h"
CATCGMLISTP_DECLARE(CATDynFilletBlendVertexSpec);

#endif
