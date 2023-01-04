#ifndef CATIPGMHybTrim_h_
#define CATIPGMHybTrim_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMHybBoolean.h"
#include "CATIACGMLevel.h"

class CATExtHybTrim;
class CATHybTrimContextForFastRun;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMHybTrim;

/**
* Class defining the operator that trims two bodies.
* The input bodies must intersect.
* The two bodies must have the same dimensionality and be wires or shells.
* Each body is split by the other one. The Trim operation cannot complete if the bodies do not intersect.
* It follows the general frame of all operators and satisfies to the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
* <ul>
* <li><tt>CATIPGMHybTrim</tt> can be created by different global functions:
*   <ul>
*     <li><tt>CATPGMCreateTopTrim</tt></li>
*     <li><tt>CATPGMCreateTopTrimOnSupport</tt> </li>
*     <li><tt>CATPGMCreateTopTrimShell</tt> </li>
*     <li><tt>CATPGMCreateTopTrimShellWithKeepRemove</tt></li>
*     <li><tt>CATPGMCreateTopTrimWire</tt></li>
*     <li><tt>CATPGMCreateTopTrimWireWithKeepRemove</tt></li>
*   </ul>
* <li>It must be
* directly released with the <tt>Release</tt> method after use.
* It is not streamable. 
* <li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
*</ul>
* @see CATPGMCreateTopTrim
* @see CATPGMCreateTopTrimOnSupport
* @see CATPGMCreateTopTrimShell
* @see CATPGMCreateTopTrimShellWithKeepRemove
* @see CATPGMCreateTopTrimWire
* @see CATPGMCreateTopTrimWireWithKeepRemove
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMHybTrim: public CATIPGMHybBoolean
{
public:
  /**
   * Constructor
   */
  CATIPGMHybTrim();

  virtual int Run() = 0;

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

  /** @nodoc  */
  virtual CATExtHybTrim *GetHybTrimExtensible() const = 0;

#ifdef CATIACGMV5R21
  /**
   * @nodoc
   * Returns the context for fast run specific of CATIPGMHybTrim operator.
   * @param iGetOnly
   * If FALSE and context doesn't exist, it is created.
   * @return
   * The context for fast run.
   */
  virtual CATHybTrimContextForFastRun *GetHybTrimContextForFastRun(CATBoolean iGetOnly) = 0;
#endif

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMHybTrim(); // -> delete can't be called
};

#endif /* CATIPGMHybTrim_h_ */
