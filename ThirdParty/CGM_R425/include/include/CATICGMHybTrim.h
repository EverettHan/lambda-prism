#ifndef CATICGMHybTrim_h_
#define CATICGMHybTrim_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMHybBoolean.h"

class CATExtHybTrim;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMHybTrim;

/**
* Class defining the operator that trims two bodies.
* The input bodies must intersect.
* The two bodies must have the same dimensionality and be wires or shells.
* Each body is split by the other one. The Trim operation cannot complete if the bodies do not intersect.
* It follows the general frame of all operators and satisfies to the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
* <ul>
* <li><tt>CATICGMHybTrim</tt> can be created by different global functions:
*   <ul>
*     <li><tt>CATCGMCreateTopTrim</tt></li>
*     <li><tt>CATCGMCreateTopTrimOnSupport</tt> </li>
*     <li><tt>CATCGMCreateTopTrimShell</tt> </li>
*     <li><tt>CATCGMCreateTopTrimShellWithKeepRemove</tt></li>
*     <li><tt>CATCGMCreateTopTrimWire</tt></li>
*     <li><tt>CATCGMCreateTopTrimWireWithKeepRemove</tt></li>
*   </ul>
* <li>It must be
* directly released with the <tt>Release</tt> method after use.
* It is not streamable. 
* <li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
*</ul>
* @see CATCGMCreateTopTrim
* @see CATCGMCreateTopTrimOnSupport
* @see CATCGMCreateTopTrimShell
* @see CATCGMCreateTopTrimShellWithKeepRemove
* @see CATCGMCreateTopTrimWire
* @see CATCGMCreateTopTrimWireWithKeepRemove
*/
class ExportedByCATGMOperatorsInterfaces CATICGMHybTrim: public CATICGMHybBoolean
{
public:
  /**
   * Constructor
   */
  CATICGMHybTrim();

  virtual int Run() = 0;

#ifdef CATIACGMV5R23
  /**
   * Activates or deactivates simplification of the result.
   * Set the simplify mode before running the operator.
   * @param yes_or_no
   * <ul>
   * <li>0: deactivates the "simplify" mode
   * <li>1: activates the "simplify" mode.
   * </ul>
   */
  virtual void SetSimplifyMode(int yes_or_no = 1) = 0;

  /**
  * Retrieves the simplify mode.
  * @return
  * <ul>
  * <li>0: the "simplify" mode is not activated
  * <li>1: the "simplify" mode is activated.
  * </ul>
  */
  virtual int GetSimplifyMode() const = 0;
#endif

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMHybTrim(); // -> delete can't be called
};

#endif /* CATICGMHybTrim_h_ */
