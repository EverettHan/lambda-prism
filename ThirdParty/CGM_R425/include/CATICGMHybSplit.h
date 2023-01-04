#ifndef CATICGMHybSplit_h_
#define CATICGMHybSplit_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMHybBoolean.h"

class CATExtHybSplit;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMHybSplit;

/**
* Class defining the operator that splits two bodies.
* The input bodies can be wires or skins.
* <br>Each body is split by the other one. Each body must only contain 
* one domain.
* It follows the general frame of all operator and satisfies to the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
* <ul>
*  <li>CATICGMHybSplit can be created by several functions:
*     <ul>
*       <li><tt>CATCGMCreateTopSplit</tt></li>
*       <li><tt>CATCGMCreateTopSplitOnSupport</tt></li>
*       <li><tt>CATCGMCreateTopSplitShell</tt> </li>
*       <li><tt>CATCGMCreateTopNewSplitShell</tt> </li>
*       <li><tt>CATCGMCreateTopSplitShellWithKeepRemove</tt></li>
*       <li><tt>CATCGMCreateTopSplitWire</tt></li>
*       <li><tt>CATCGMCreateTopNewSplitWire</tt></li>
*       <li><tt>CATCGMCreateTopSplitWireWithKeepRemove</tt></li>
*     </ul>
*   <li>It must be directly released with the <tt>Release</tt> method after use.
*   <li>It is not streamable. 
*   <li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
*</ul>
* @see CATCGMCreateTopSplit
* @see CATCGMCreateTopSplitOnSupport
* @see CATCGMCreateTopSplitShell 
* @see CATCGMCreateTopNewSplitShell 
* @see CATCGMCreateTopSplitShellWithKeepRemove 
* @see CATCGMCreateTopSplitWire 
* @see CATCGMCreateTopNewSplitWire 
* @see CATCGMCreateTopSplitWireWithKeepRemove 
*/
class ExportedByCATGMOperatorsInterfaces CATICGMHybSplit: public CATICGMHybBoolean
{
public:
  /**
   * Constructor
   */
  CATICGMHybSplit();

  //rlad
  /**
	 * Sets or unsets the ‘Keep elements in half space’ mode.
	 *   @param iMode
	 *      Mode on (TRUE) or off (FALSE)
	 */
  virtual void SetKeepHalfSpaceMode(CATBoolean iMode = 0) = 0;

  /**
	 * Queries whether ‘Keep elements in half space’ mode is activated or not.
	 *   @param oMode
	 *      Mode on (TRUE) or off (FALSE)
	 */
  virtual void GetKeepHalfSpaceMode(CATBoolean &oMode) = 0;

  /**
	 * Sets or unsets the ‘keep only the no intersecting solutions of extrapolated cuttings’ mode.
	 *    param iMode
	 *      Mode on (TRUE) or off (FALSE)
	 */
  virtual void SetSingleExtrapolMode(CATBoolean iMode = 0) = 0;

  /**
	 * Queries whether ‘keep only the no intersecting solutions of extrapolated cuttings’ mode is activated or not.
	 *    param oMode
	 *      Mode on (TRUE) or off (FALSE)
	 */
  virtual void GetSingleExtrapolMode(CATBoolean &oMode) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMHybSplit(); // -> delete can't be called
};

#endif /* CATICGMHybSplit_h_ */
