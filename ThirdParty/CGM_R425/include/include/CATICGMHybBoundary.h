#ifndef CATICGMHybBoundary_h_
#define CATICGMHybBoundary_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMHybOperatorImp.h"

class CATExtHybBoundary;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMHybBoundary;

/**
* Class defining the operator that computes the boundary of a wire or a shell. 
* This operator completes on open bodies or bodies which have boundaries.
* For example, it generates a result when the input body is a 2D cylinder
* but it does not generate any result and throws an exception when the input body is a 2D sphere.
* It throws an exception as well when the input body is a close wire. 
* This operator completes on multi-domain bodies. 
* In this case, an initial cell has to be specified as well as a propagation
* mode to determine the area of boundaries to be computed.
* If the body is a multi-domain body and if the domain is not specified, 
* the operator cannot complete and throws an exception. 
* The initial cell and the domain are default arguments of the CATCGMCreateTopBoundary global function. 
* They are not needed when the input body is a single domain body. 
* <br>
* This operator follows the general frame of all operator and satisfies to the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
* <ul>
* <li>CATICGMHybBoundary is created with the <tt>CATCGMCreateTopBoundary</tt> global function.
* It must be
* directly released with the <tt>Release</tt> method after use.
* It is not streamable. 
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
*</ul>
* @see CATCGMCreateTopBoundary 
*/
class ExportedByCATGMOperatorsInterfaces CATICGMHybBoundary: public CATICGMHybOperatorImp
{
public:
  /**
   * Constructor
   */
  CATICGMHybBoundary();

  /** @nodoc  */
  // (Empty macro in customer release mode; no effect on generated code)
  virtual int Run() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMHybBoundary(); // -> delete can't be called
};

#endif /* CATICGMHybBoundary_h_ */
