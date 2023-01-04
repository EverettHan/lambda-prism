#ifndef CATICGMDynOperator_h_
#define CATICGMDynOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"

class CATBody;
class CATCGMActivateDebug;
class CATCGMJournalList;
class CATGeoFactory;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMDynOperator;

/**
* Abstract base class for the operators of filleting, drafting, chamfering, shelling and Boolean operations.
* <br> A topological operation is realized with the appropriate operator. 
* These operators follow the global frame of the topological operators and satisfy the smart mechanism: 
* the input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
* <li>A derived operator is created with a global function.
* It must be
* directly released with the <tt>Release</tt> method.
* It is not streamable. 
*<li>Options can be precised with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method. 
*<li>In both cases, the result is accessed with the <tt>GetResult</tt> method.  
*</ul>
*/
class ExportedByCATGMOperatorsInterfaces CATICGMDynOperator: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMDynOperator();

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMDynOperator(); // -> delete can't be called
};

#endif /* CATICGMDynOperator_h_ */
