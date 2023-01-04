#ifndef CATICGMTopParallel_h_
#define CATICGMTopParallel_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"

class CATBody;
class CATICGMDistanceTool;
class CATICGMExtrapolParallelTool;
class CATWire;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopParallel;

/**
* Class representing the operator that computes a wire parallel to another one on a skin body.
* <br>The CATICGMTopParallel operator follows the global frame of the topological operators
* and satisfies the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
* <li>A CATICGMTopParallel operator is created with the <tt>CATCGMCreateTopParallel</tt> global function.
* It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
*<li>The computation is done by the <tt>Run</tt> method. 
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory, after the operator deletion.
*</ul>
*/
class ExportedByCATGMOperatorsInterfaces CATICGMTopParallel: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMTopParallel();

  // 0 = No PLine simplification
  /**
 * Returns the pointer to the resulting body.
 * @return
 * The pointer to the resulting body. If you do not want to keep it, 
 * use the @href CATICGMContainer#Remove method to remove it from the 
 * geometric factory, after the operator deletion.
 */
  virtual CATBody *GetResult() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopParallel(); // -> delete can't be called
};

/**
* Creates a CATICGMTopParallel operator that computes a wire parallel 
* (according to a given law) to another one on a shell.
* <b>Orientation</b>: The resulting wire is oriented as the input one.<br>
* <b>Journal</b>: If the distance is null, a new body is created and 
* the edges are written as kept. If not, the new body contains the new edges, written
* as created.
* @param iOption
* The definition of the parameters for the operation.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMTopParallel *CATCGMCreateTopParallel(
  CATICGMExtrapolParallelTool *iOption,
  CATBody *iCurve);

#endif /* CATICGMTopParallel_h_ */
