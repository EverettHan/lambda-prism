#ifndef CATIPGMHybSplit_h_
#define CATIPGMHybSplit_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMHybBoolean.h"

class CATExtHybSplit;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMHybSplit;

/**
* Class defining the operator that splits two bodies.
* The input bodies can be wires or skins.
* <br>Each body is split by the other one. Each body must only contain 
* one domain.
* It follows the general frame of all operator and satisfies to the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
* <ul>
*   <li>CATIPGMHybSplit can be created by several functions:
*     <ul>
*       <li><tt>CATPGMCreateTopSplit</tt></li>
*       <li><tt>CATPGMCreateTopSplitOnSupport</tt></li>
*       <li><tt>CATPGMCreateTopSplitShell</tt> </li>
*       <li><tt>CATPGMCreateTopNewSplitShell</tt> </li>
*       <li><tt>CATPGMCreateTopSplitShellWithKeepRemove</tt></li>
*       <li><tt>CATPGMCreateTopSplitWire</tt></li>
*       <li><tt>CATPGMCreateTopNewSplitWire</tt></li>
*       <li><tt>CATPGMCreateTopSplitWireWithKeepRemove</tt></li>
*     </ul>
*   <li>It must be directly released with the <tt>Release</tt> method after use.
*   <li>It is not streamable. 
*   <li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
*</ul>
* @see CATPGMCreateTopSplit
* @see CATPGMCreateTopSplitOnSupport
* @see CATPGMCreateTopSplitShell 
* @see CATPGMCreateTopNewSplitShell 
* @see CATPGMCreateTopSplitShellWithKeepRemove 
* @see CATPGMCreateTopSplitWire 
* @see CATPGMCreateTopNewSplitWire 
* @see CATPGMCreateTopSplitWireWithKeepRemove 
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMHybSplit: public CATIPGMHybBoolean
{
public:
  /**
   * Constructor
   */
  CATIPGMHybSplit();

  /** @nodoc  */
  // (Empty macro in customer release mode; no effect on generated code)
  virtual int Run() = 0;

  // desactivation of Error on SplitClosedWireWithSingleVertex (to use before run)
  // default value is : 1 --> Error is throw in case of Split a ClosedWire With Single Vertex
  /** @nodoc */
  virtual void SetThrowErrorForClosedWireWithSingleVertex(int yes_or_no = 1) = 0;

  /** @nodoc */
  virtual int GetErrorForClosedWireWithSingleVertexMode() const = 0;

  // treatment with Simplification of the Result (to use before run)
  /** @nodoc */
  virtual void SetSimplifyMode(int yes_or_no = 1) = 0;

  /** @nodoc */
  virtual int GetSimplifyMode() const = 0;

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

  // (to use before run)
  // If iLyingOnMode == 0 : LyingOn links from CuttingBody cells onto SplittingBody cells are deleted
  // If iLyingOnMode == 1 : they are not deleted
  /** @nodoc */
  virtual void SetLyingOnLinksKept(int iLyingOnMode = 1) = 0;

  /** @nodoc  */
  virtual CATExtHybSplit *GetHybSplitExtensible() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMHybSplit(); // -> delete can't be called
};

#endif /* CATIPGMHybSplit_h_ */
