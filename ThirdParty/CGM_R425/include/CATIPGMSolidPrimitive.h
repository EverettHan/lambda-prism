#ifndef CATIPGMSolidPrimitive_h_
#define CATIPGMSolidPrimitive_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATCGMJournalList;
class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMSolidPrimitive;

/**
 * Base class for the operators that create basic topological primitives.
 * <br>Use the derived class <tt>CATSolidXxx</tt> to create the basic topological primitive <tt>Xxx</tt>.
 * <br><tt>CATSolidXxx</tt> follows the global frame of the topological operators.
 *<ul>
 * <li>Create it with the <tt>CATCreateSolidXxx</tt> global function 
 * <li>Run it 
 * <li>Get the result
 * <li>Release the operator with the <tt>Release</tt> method after use.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMSolidPrimitive: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMSolidPrimitive();

  /** @nodoc */
  virtual operator CATBody *() = 0;

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
  virtual ~CATIPGMSolidPrimitive(); // -> delete can't be called
};

#endif /* CATIPGMSolidPrimitive_h_ */
