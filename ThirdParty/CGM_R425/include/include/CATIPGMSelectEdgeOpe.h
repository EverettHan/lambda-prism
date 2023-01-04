#ifndef CATIPGMSelectEdgeOpe_h_
#define CATIPGMSelectEdgeOpe_h_

// COPYRIGHT DASSAULT SYSTEMES 2018

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMAdvancedOperator.h"
#include "CATSelectEdgePropagateMode.h"

class CATBody;
class CATCellHashTable;
class CATGeoFactory;
class CATTopData;
class CATLISTP(CATEdge);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMSelectEdgeOpe;

/**
* This class is used to select faces with.<br>
**/
class ExportedByCATGMOperatorsInterfaces CATIPGMSelectEdgeOpe: public CATIPGMAdvancedOperator
{
public:

  // =========================================================
  // Set Methods ( before Run )
  // =========================================================
  /**
  * Set a list of CATEdge pointer to priorise propagation.
  * @param iGuideEdges
  * The pointer list of CATEdge to append.
  */
  virtual void SetGuideEdges(const CATLISTP(CATEdge) &iGuideEdges) = 0;

  /**
  * Set a list of CATEdge pointer to stop propagation.
  * @param iStoppingEdges
  * The pointer list of CATEdge to append.
  */
  virtual void SetStoppingEdges(const CATLISTP(CATEdge) &iStoppingEdges) = 0;

  /**
  * Set an angle value which define the tangency tolerance for edges propagation.
  * @param iRadAngle
  * The angle value in radians.
  */
  virtual void SetTangencyMaxAngle(CATAngle iRadAngle) = 0;

  //==========================================================
  // Get Methods  ( Output after Run )
  // =========================================================
  /** 
  * Retrieve the result of propagation of CATEdge given in input.
  * @param oResultEdgeList
  *   The list filled of pointers on result CATEdge.
  **/
  virtual void GetSelectedResult(CATLISTP(CATEdge) &oResultEdgeList) const = 0;

  /** 
  * Retrieve the result of propagation of CATEdge given in input.
  * @param oResultEdgeList
  *   The hashtable filled by pointers on result selected CATEdge.
  **/
  virtual void GetSelectedResult(CATCellHashTable &oResultEdgeHT) const = 0;

  /** 
  * Get the hash table result from the operator - avoid copy. Note that the hash
  * table will be own by the caller. Think to delete it after usage.
  * This method can only be called once. 
  * @return
  *   The pointer of the hash table that contains pointers on selected edges.
  **/
  virtual CATCellHashTable *GetSelectedResult() = 0;

protected:

  /**
   * Constructor
   */
  CATIPGMSelectEdgeOpe();

  /**
   * Destructor
   */
  virtual ~CATIPGMSelectEdgeOpe(); // -> delete can't be called
};

//==============================================================================
// Data
//==============================================================================
//==============================================================================
// Official Constructor : CATPGMCreateSelectEdgeOpe
//==============================================================================
/**
* Create operator, it call the constructor.<br>
* <b>Legal Values</b>:<br>
*	<ul>
*	  <li> <tt>iTopData</tt> : It represents the information about the configuration and
*								the journal. If iTopData is NULL , the operator create it.<br>
*	  <li> <tt>iBody</tt> : The body of the edge selection<br>
*   <li> <tt>iInputEdgeList</tt> : The list of the first Edges selected<br>
*   <li> <tt>iEdgeGuideList</tt> : The list of pointers on Edges that are first priority during propagation.<br>
*   <li> <tt>iPropagationMode</tt> : The type of propagation :<br>
*     <ul>
*     <li> ChainEdge,<br>
*    </ul>
*   <li> <tt>iStoppingEdges</tt> : It's optional. The list of the edges not to pass through.<br>
*  </ul>
**/
ExportedByCATGMOperatorsInterfaces CATIPGMSelectEdgeOpe *CATPGMCreateSelectEdgeOpe(
  CATTopData *ipTopData,
  CATBody *ipInputBody,
  const CATLISTP(CATEdge) &iInputEdgeList,
  CATSelectEdgePropagateMode iPropagationMode,
  const CATLISTP(CATEdge) *iEdgeGuideList = NULL,
  const CATLISTP(CATEdge) *iStoppingEdges = NULL);

#endif /* CATIPGMSelectEdgeOpe_h_ */
