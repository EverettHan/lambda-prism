#ifndef CATIPGMSortBlendVertexSpecs_h_
#define CATIPGMSortBlendVertexSpecs_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

/**
 * @level Protected
 * @usage U1
 */

class CATBody;
class CATLISTP(CATICGMTopPropagationEdge);
class CATLISTP(CATDynFilletBlendVertexSpec);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMSortBlendVertexSpecs;

/**
 * Operator which re-orders the CATDynFilletBlendVertexSpec objects used
 * in the definition of a blend vertex.<br>
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
 * The CATIPGMSortBlendVertexSpecs operator is created by using the CATPGMCreateSortBlendVertexSpecs
 * global function.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMSortBlendVertexSpecs: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMSortBlendVertexSpecs();
  /**
   * Runs the operator.
   * @return 
   * 0 if the operation completes, 1 otherwise.
   */
  virtual int Run() = 0;
 
   /**
   * Retrieves the result of the sort operation. 
   * This result is passed as an argument of <tt>CATCreateDynFilletBlendVertex</tt>.
   * @param oCouldBeOrdered
   * TRUE if the list of CATDynFilletBlendVertexSpec has been successfully re-ordered, otherwise FALSE.
   * @param oOrderedSpecs
   * The list of re-orders CATDynFilletBlendVertexSpec.
   * @return 
   * 0 if the operation completes, 1 otherwise.
   */
  virtual void GetResult(
    CATBoolean &oCouldBeOrdered,
    CATLISTP(CATDynFilletBlendVertexSpec) &oOrderedSpecs) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSortBlendVertexSpecs(); // -> delete can't be called
};

/**
* Constructs a CATIPGMSortBlendVertexSpecs operator.
* @param iFactory
* The pointer to the geometry factory.
* @param iTopData
* The pointer to the data defining the configuration and the journal. If the journal inside <tt>iData</tt> 
* is <tt>NULL</tt>, it is not filled.
* @param iBody
* The pointer to the body owning the vertex to be rounded.
* @param iSpecToOrder 
* The list of CATDynFilletBlendVertexSpec to re-order.
* @param CATICGMTopPropagationEdge 
* The list of CATICGMTopPropagationEdge.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMSortBlendVertexSpecs *CATPGMCreateSortBlendVertexSpecs(
	CATGeoFactory *iFactory,
	CATTopData *iTopData,
	CATBody *iBody,
	CATLISTP(CATDynFilletBlendVertexSpec) &iSpecToOrder,
	CATLISTP(CATICGMTopPropagationEdge) &iPropagationEdgeList);

#endif /* CATIPGMSortBlendVertexSpecs_h_ */
