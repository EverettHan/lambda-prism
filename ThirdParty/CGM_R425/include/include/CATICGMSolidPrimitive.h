#ifndef CATICGMSolidPrimitive_h_
#define CATICGMSolidPrimitive_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"

class CATBody;
class CATCGMJournalList;
class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMSolidPrimitive;

/**
 * Base class for the operators that create basic topological primitives.
 * <br>Use the derived class <tt>CATICGMSolidXxx</tt> to create the basic topological primitive <tt>Xxx</tt>.
 * <br><tt>CATICGMSolidXxx</tt> follows the global frame of the topological operators.
 *<ul>
 * <li>Create it with the <tt>CATCGMCreateSolidXxx</tt> global function 
 * <li>Run it 
 * <li>Get the result
 * <li>Release the operator with the <tt>Release</tt> method after use.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATICGMSolidPrimitive: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMSolidPrimitive();

  /**
	 * Returns a pointer to the factory of the geometry used in <tt>this</tt> operator.
	 * @return
	 * The pointer to the factory.
	 */
  virtual CATGeoFactory *GetFactory() = 0;

  /**
	 * Returns a pointer to the resulting body created by <tt>this</tt> operator.
	 * @return
	 * The pointer to the body. If you do not want to keep it, use the @href CATICGMContainer#Remove method
	 *  to remove it from the container after the deletion of the operator. 
	 */
  virtual CATBody *GetResult() = 0;

  /**
   * Returns the pointer to the journal.
	 * @return 
	 * The pointer to the journal.
	 */
  virtual CATCGMJournalList *GetReport() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMSolidPrimitive(); // -> delete can't be called
};

#endif /* CATICGMSolidPrimitive_h_ */
