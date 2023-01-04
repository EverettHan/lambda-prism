#ifndef CATIPGMDynOperator_h_
#define CATIPGMDynOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATCGMActivateDebug;
class CATCGMJournalList;
class CATGeoFactory;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMDynOperator;

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
class ExportedByCATGMOperatorsInterfaces CATIPGMDynOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMDynOperator();

  /**
 * @nodoc
 * Deprecated.
 * Returns a pointer to the body resulting from the boolean operation between the input
 * body and the result of <tt>this</tt> CATIPGMDynOperator.<br>
 * This is available for prism, revol and sweep operator, and allows two operations
 * in one way.
 */
  virtual CATBody *GetBooleanResult() const = 0;

  /**
 * @nodoc
 * Deprecated.
 * Returns a pointer to the topological journal corresponding to the boolean operation after
 * the CATIPGMDynOperator.
 * (see <tt>GetBooleanResult</tt>).
 * <br>Only available if a journal was given at the creation of the operator.
 */
  virtual CATCGMJournalList *GetBooleanJournal() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDynOperator(); // -> delete can't be called
};

#endif /* CATIPGMDynOperator_h_ */
