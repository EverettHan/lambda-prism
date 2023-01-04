#ifndef CATIPGMTopReflectLine_h_
#define CATIPGMTopReflectLine_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATFace;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopReflectLine;

/**
 * Class defining the operator that computes the reflect lines on a skin body.
 *<br>
 * The CATIPGMTopReflectLine operator follows the global frame of the topological operators and satisfies the smart mechanism: 
 * the input bodies are not modified. A new resulting body is created, 
 * possibly sharing data with the input bodies.
 *<ul>
 * <li>A CATIPGMTopReflectLine operator is created with the <tt>CATPGMCreateTopReflectLine</tt> global method:
 * It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
 *<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
 * to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
 * geometry factory.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopReflectLine: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopReflectLine();

  /**
  * Use this method before the Run() method in order to have a better associativity of the CATIPGMTopReflectLine result.
  */
  virtual void OptimizeDomainStructure() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopReflectLine(); // -> delete can't be called
};

#endif /* CATIPGMTopReflectLine_h_ */
