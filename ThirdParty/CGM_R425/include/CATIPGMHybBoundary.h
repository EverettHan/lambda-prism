#ifndef CATIPGMHybBoundary_h_
#define CATIPGMHybBoundary_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMHybOperatorImp.h"

class CATExtHybBoundary;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMHybBoundary;

/**
* Class defining the operator that computes the boundary of a wire or a shell.
*<br>
* This operator follows the general frame of all operator and satisfies to the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
* <li>CATIPGMHybBoundary is created with the <tt>CATPGMCreateTopBoundary</tt> global function.
* It must be
* directly released with the <tt>Release</tt> method after use.
* It is not streamable. 
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
*</ul>
* @see CATPGMCreateTopBoundary 
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMHybBoundary: public CATIPGMHybOperatorImp
{
public:
  /**
   * Constructor
   */
  CATIPGMHybBoundary();

  /** @nodoc  */
  // (Empty macro in customer release mode; no effect on generated code)
  virtual int Run() = 0;

  /** @nodoc  */
  virtual CATExtHybBoundary *GetHybBoundaryExtensible() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMHybBoundary(); // -> delete can't be called
};

#endif /* CATIPGMHybBoundary_h_ */
